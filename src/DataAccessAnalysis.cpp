#include "DataAccessAnalysis.hh"

using namespace llvm;

char pdg::DataAccessAnalysis::ID = 0;

cl::opt<bool> SharedDataFlag("sd", llvm::cl::desc("turn on shared data optimization"), llvm::cl::init(true), llvm::cl::value_desc("shared_data"));

void pdg::DataAccessAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<SharedDataAnalysis>();
  AU.setPreservesAll();
}

void patchStringAnnotation(std::string &field_type_name, std::string &anno_str)
{
  if (anno_str == "[string]")
  {
    field_type_name = "string *";
    anno_str = "";
  }
}

bool pdg::DataAccessAnalysis::runOnModule(Module &M)
{
  _module = &M;
  _SDA = &getAnalysis<SharedDataAnalysis>();
  _PDG = _SDA->getPDG();
  _call_graph = &PDGCallGraph::getInstance();
  _ksplit_stats = &KSplitStats::getInstance();
  computeExportedFuncsPtrNameMap();
  readDriverDefinedGlobalVarNames("driver_globalvar_names");
  readDriverExportedFuncSymbols("driver_exported_func_symbols");
  _idl_file.open("kernel.idl");
  _global_var_access_info.open("global_var_access_info.idl");
  unsigned total_num_funcs = 0;
  // intra-procedural analysis
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    computeDataAccessForFuncArgs(F);
    computeContainerOfLocs(F);
    total_num_funcs++;
    // computeInterProcDataAccess(F);
  }

  computeAllocSizeAnnos(M);
  computeDeallocAnnos(M);

  _idl_file << "module kernel {\n";
  std::vector<std::string> boundary_func_names(_SDA->getBoundaryFuncNames().begin(), _SDA->getBoundaryFuncNames().end());
  std::sort(boundary_func_names.begin(), boundary_func_names.end());
  for (auto func_name : boundary_func_names)
  {
    auto F = M.getFunction(func_name);
    if (F == nullptr || F->isDeclaration())
      continue;
    generateIDLForFunc(*F);
  }
  _ksplit_stats->increaseTotalFuncSize(total_num_funcs);

  // genereate additional func call stubs for kernel funcs registered on the driver side
  EnableAnalysisStats = false;
  for (auto F : _kernel_funcs_regsitered_with_indirect_ptr)
  {
    if (F->isDeclaration())
      continue;
    generateIDLForFunc(*F, true);
  }
  EnableAnalysisStats = true;
  
  // generate rpc_export stub for functions exported form driver through export_symbol
  for (auto s : _driver_exported_func_symbols)
  {
    Function* F = M.getFunction(StringRef(s));
    if (F == nullptr || F->isDeclaration())
      continue;
    generateIDLForFunc(*F, true);
  }

  // debug stats for total func counts
  if (EnableAnalysisStats)
    errs() << "Funcs reachable from boundary: " << total_num_funcs << "\n";

  constructGlobalOpStructStr();
  _idl_file << _ops_struct_proj_str << "\n";

  _idl_file << "\n};\n";

  // generate IDL for global variables
  for (auto pair : _PDG->getGlobalVarTreeMap())
  {
    Tree *tree = pair.second;
    if (!globalVarHasAccessInDriver(*pair.first))
      continue;
    if (isDriverDefinedGlobal(*pair.first))
      continue;
    computeDataAccessForGlobalTree(tree);
    generateIDLFromGlobalVarTree(*pair.first, tree);
  }

  errs() << "Finish analyzing data access info.";
  _idl_file.close();

  if (EnableAnalysisStats)
    _ksplit_stats->printStats();

  return false;
}

std::set<pdg::Node *> pdg::DataAccessAnalysis::findCrossDomainParamNode(Node &n, bool is_backward)
{
  std::queue<Node *> node_queue;
  std::set<EdgeType> search_edge_types = {
      EdgeType::PARAMETER_IN,
      EdgeType::DATA_ALIAS};
  node_queue.push(&n);
  std::set<Node *> seen_nodes;
  std::set<Node*> cross_domain_nodes;
  while (!node_queue.empty())
  {
    auto current_node = node_queue.front();
    node_queue.pop();
    if (seen_nodes.find(current_node) != seen_nodes.end())
      continue;
    seen_nodes.insert(current_node);
    Node::EdgeSet edge_set;
    if (is_backward)
      edge_set = current_node->getInEdgeSet();
    else
      edge_set = current_node->getOutEdgeSet();

    for (auto edge : edge_set)
    {
      if (search_edge_types.find(edge->getEdgeType()) == search_edge_types.end())
        continue;
      Node *target_node = nullptr;
      if (is_backward)
        target_node = edge->getSrcNode();
      else
        target_node = edge->getDstNode();
      if (target_node->getNodeType() == GraphNodeType::FORMAL_IN)
        cross_domain_nodes.insert(target_node);
      else
        node_queue.push(target_node);
    }
  }
  return cross_domain_nodes;
}

void pdg::DataAccessAnalysis::readDriverDefinedGlobalVarNames(std::string file_name)
{
  std::ifstream ReadFile(file_name);
  for (std::string line; std::getline(ReadFile, line);)
  {
    _driver_defined_globalvar_names.insert(line);
  }
}

void pdg::DataAccessAnalysis::readDriverExportedFuncSymbols(std::string file_name)
{
  std::ifstream ReadFile(file_name);
  for (std::string line; std::getline(ReadFile, line);)
  {
    _driver_exported_func_symbols.insert(line);
  }
}

void pdg::DataAccessAnalysis::propagateAllocSizeAnno(Value &allocator)
{
  std::string alloc_str = "alloc";
  std::string size_str = "<{{";
  if (CallInst *ci = dyn_cast<CallInst>(&allocator))
  {
    // get size operand
    auto size_operand = ci->getArgOperand(0);
    assert(size_operand != nullptr && "allocator has null size operand!\n");
    if (ConstantInt *cons_int = dyn_cast<ConstantInt>(size_operand))
    {
      auto alloc_size = cons_int->getSExtValue();
      size_str += std::to_string(alloc_size);
    }

    // get GP flag
    if (ci->data_operands_size() > 1)
    {
      auto gp_flag_operand = ci->getArgOperand(1);
      assert(gp_flag_operand != nullptr && "allocator has null gp operand!\n");
      if (ConstantInt *cons_int = dyn_cast<ConstantInt>(size_operand))
      {
        auto gp_flag = cons_int->getSExtValue();
        size_str += std::string("}}, {{") + std::to_string(gp_flag);
      }
      else
        size_str += std::string("}}, {{") + std::string("(DEFAULT_GFP_FLAGS)");

      size_str += "}}>";
    }
  }

  auto val_node = _PDG->getNode(allocator);
  assert(val_node != nullptr && "cannot generate size anno str for null node\n");
  alloc_str += size_str;
  // in this case, the allocated object escaped.
  auto alias_nodes = _PDG->findNodesReachedByEdge(*val_node, EdgeType::DATA_ALIAS);
  alias_nodes.insert(val_node);
  for (auto alias_node : alias_nodes)
  {
    alias_node->dump();
    if (alias_node->isAddrVarNode())
    {
      auto param_tree_node = alias_node->getAbstractTreeNode();
      TreeNode *tn = (TreeNode *)param_tree_node;
      tn->setAllocStr(alloc_str + "(caller)");
    }
    else
    {
      // in this case, the allocated object is passed across isolation boundary.
      // the tracking is path insensitive. If two functions are called in different branches, both function woul have the alloca attributes created for the received parameter
      auto cross_domain_param_nodes = findCrossDomainParamNode(*alias_node);
      for (auto n : cross_domain_param_nodes)
      {
        if (n != nullptr)
        {
          TreeNode *tn = (TreeNode *)n;
          tn->setAllocStr(alloc_str + "(callee)");
        }
      }
    }
  }
}

void pdg::DataAccessAnalysis::inferDeallocAnno(Value &deallocator)
{
  // check if any address variable is passed to a deallocation function.
  if (CallInst *ci = dyn_cast<CallInst>(&deallocator))
  {
    auto freed_object = ci->getOperand(0);
    assert(freed_object != nullptr && "cannot infer dealloc annotation for nullptr!\n");
    auto freed_object_node = _PDG->getNode(*freed_object);
    if (freed_object_node->isAddrVarNode())
    {
      auto param_node = freed_object_node->getAbstractTreeNode();
      auto backward_cross_domain_param_nodes = findCrossDomainParamNode(*param_node, true);
      // perform backward search to identify the parameter tree node that should contain the dealloc attribute.
      for (auto n : backward_cross_domain_param_nodes)
      {
        if (n != nullptr)
        {
          TreeNode *tn = (TreeNode *)n;
          tn->setAllocStr("dealloc(caller)");
        }
      }
    }
  }
}

void pdg::DataAccessAnalysis::computeAllocSizeAnnos(Module &M)
{
  auto allocators = _PDG->getAllocators();
  for (auto allocator : allocators)
  {
    propagateAllocSizeAnno(*allocator);
  }
}

void pdg::DataAccessAnalysis::computeDeallocAnnos(Module &M)
{
  auto deallocators = _PDG->getDeallocators();
  for (auto deallocator : deallocators)
  {
    inferDeallocAnno(*deallocator);
  }
}

void pdg::DataAccessAnalysis::computeExportedFuncsPtrNameMap()
{
  std::ifstream driverExportFuncs("exported_funcs");
  std::ifstream driverExportFuncPtrs("exported_func_ptrs");
  for (std::string line1, line2; std::getline(driverExportFuncPtrs, line1), std::getline(driverExportFuncs, line2);)
  {
    // in some cases, a function pointer exported from driver may point to a kernel function
    // in this case, we don't treat this exported pointer as a interface function.
    Function *pointed_func = _module->getFunction(line2);
    if (pointed_func == nullptr || pointed_func->isDeclaration())
      continue;
    _exported_funcs_ptr_name_map[line1] = line2; // key: registered driver side function, value: the registered function pointer name
  }
}

std::set<pdg::AccessTag> pdg::DataAccessAnalysis::computeDataAccessTagsForVal(Value &val)
{
  std::set<AccessTag> acc_tags;
  if (pdgutils::hasReadAccess(val))
    acc_tags.insert(AccessTag::DATA_READ);
  if (pdgutils::hasWriteAccess(val))
    acc_tags.insert(AccessTag::DATA_WRITE);
  return acc_tags;
}

void pdg::DataAccessAnalysis::computeDataAccessForTreeNode(TreeNode &tree_node, bool is_global_tree_node, bool is_ret)
{
  auto func = tree_node.getFunc();
  DomainTag boundary_func_domain_tag = DomainTag::NO_DOMAIN;

  if (func != nullptr)
    boundary_func_domain_tag = computeFuncDomainTag(*func);

  std::string parent_node_type_name = "";
  TreeNode *parent_node = tree_node.getParentNode();
  if (parent_node != nullptr)
    parent_node_type_name = dbgutils::getSourceLevelTypeName(*(parent_node->getDIType()), true);

  std::string field_var_name = dbgutils::getSourceLevelVariableName(*tree_node.getDIType());
  bool is_sentinel_type = _SDA->isSentinelField(field_var_name);
  // special hanlding for function pointers and sentinel type
  if (is_sentinel_type)
    tree_node.addAccessTag(AccessTag::DATA_READ);

  for (auto addr_var : tree_node.getAddrVars())
  {
    for (auto user : addr_var->users())
    {
      if (StoreInst *st = dyn_cast<StoreInst>(user))
      {
        auto val_op = st->getValueOperand();
        if (Function *f = dyn_cast<Function>(val_op))
        {
          auto func_name = f->getName().str();
          _exported_funcs_ptr_name_map.insert(std::make_pair(field_var_name, func_name));
        }
      }
    }
  }

  if (tree_node.getDIType() != nullptr && (dbgutils::isFuncPointerType(*tree_node.getDIType())))
  {
    std::string func_ptr_name = parent_node_type_name + "_" + field_var_name;
    if (_exported_funcs_ptr_name_map.find(func_ptr_name) != _exported_funcs_ptr_name_map.end())
    {
      tree_node.addAccessTag(AccessTag::DATA_READ);
      auto parent_node = tree_node.getParentNode();
      while (parent_node != nullptr)
      {
        parent_node->addAccessTag(AccessTag::DATA_READ);
        parent_node = parent_node->getParentNode();
      }
    }
  }

  // intra proc access tags
  auto addr_vars = tree_node.getAddrVars();
  for (auto addr_var : addr_vars)
  {
    if (Instruction *i = dyn_cast<Instruction>(addr_var))
    {
      // checking for globals
      if (is_global_tree_node && !_SDA->isDriverFunc(*(i->getFunction())))
        continue;
    }

    auto acc_tags = computeDataAccessTagsForVal(*addr_var);
    for (auto acc_tag : acc_tags)
    {
      tree_node.addAccessTag(acc_tag);
    }
  }

  bool has_intra_access = false;
  if (tree_node.getAccessTags().size() != 0)
    has_intra_access = true;

  // inter proc access
  bool only_has_cross_domain_access = true;
  std::set<EdgeType> edge_types = {
      EdgeType::PARAMETER_IN,
      EdgeType::DATA_RET,
  };
  auto parameter_in_nodes = _PDG->findNodesReachedByEdges(tree_node, edge_types);
  for (auto n : parameter_in_nodes)
  {
    if (n->getValue() != nullptr)
    {
      if (Instruction *i = dyn_cast<Instruction>(n->getValue()))
      {
        auto inst_func = i->getFunction();
        if (inst_func == func)
          tree_node.addAddrVar(*i);

        DomainTag func_tag = computeFuncDomainTag(*inst_func);
        // assumption when computing access for global variable
        if (is_global_tree_node && !_SDA->isDriverFunc(*(i->getFunction())))
          continue;
        // optimization for cross domain data accesses
        if (boundary_func_domain_tag != DomainTag::NO_DOMAIN && func_tag != boundary_func_domain_tag && !is_ret)
          continue;
      }

      only_has_cross_domain_access = false;
      auto acc_tags = computeDataAccessTagsForVal(*n->getValue());
      for (auto acc_tag : acc_tags)
      {
        tree_node.addAccessTag(acc_tag);
      }
    }
  }

  // reconnecting address nodes found by inter procedural call
  for (auto child_node : tree_node.getChildNodes())
  {
    child_node->computeDerivedAddrVarsFromParent();
    for (auto addr_var : child_node->getAddrVars())
    {
      auto addr_var_node = _PDG->getNode(*addr_var);
      child_node->addNeighbor(*addr_var_node, EdgeType::PARAMETER_IN);
    }
  }

  if (only_has_cross_domain_access && !has_intra_access)
    tree_node.setCanOptOut(true);
}

void pdg::DataAccessAnalysis::computeDataAccessForTree(Tree *tree, bool is_ret)
{
  TreeNode *root_node = tree->getRootNode();
  assert(root_node != nullptr && "cannot compute access info for empty tree!");
  std::queue<TreeNode *> node_queue;
  node_queue.push(root_node);
  while (!node_queue.empty())
  {
    TreeNode *current_node = node_queue.front();
    node_queue.pop();
    computeDataAccessForTreeNode(*current_node, false, is_ret);
    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
  }
}

void pdg::DataAccessAnalysis::computeDataAccessForGlobalTree(Tree *tree)
{
  TreeNode *root_node = tree->getRootNode();
  assert(root_node != nullptr && "cannot compute access info for empty tree!");
  std::queue<TreeNode *> node_queue;
  node_queue.push(root_node);
  while (!node_queue.empty())
  {
    TreeNode *current_node = node_queue.front();
    node_queue.pop();
    bool is_accessed_in_driver = false;
    for (auto addr_var : current_node->getAddrVars())
    {
      if (Instruction *i = dyn_cast<Instruction>(addr_var))
      {
        auto func = i->getFunction();
        if (_SDA->isDriverFunc(*func))
        {
          is_accessed_in_driver = true;
          break;
        }
      }
    }

    if (!is_accessed_in_driver)
      continue;

    computeDataAccessForTreeNode(*current_node, true);
    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
  }
}

void pdg::DataAccessAnalysis::computeDataAccessForFuncArgs(Function &F)
{
  // errs() << "compute intra for func: " << F.getName() << "\n";
  auto func_wrapper_map = _PDG->getFuncWrapperMap();
  if (func_wrapper_map.find(&F) == func_wrapper_map.end())
    return;
  FunctionWrapper *fw = func_wrapper_map[&F];
  // compute for return value access info
  auto arg_ret_tree = fw->getRetFormalInTree();
  computeDataAccessForTree(arg_ret_tree, true);
  // compute arg access info
  auto arg_tree_map = fw->getArgFormalInTreeMap();
  for (auto iter = arg_tree_map.begin(); iter != arg_tree_map.end(); iter++)
  {
    Tree *arg_tree = iter->second;
    computeDataAccessForTree(arg_tree);
  }
}

/*
Four cases:
1. pointer to simple type
2. simple type
3. pointer to aggregate type
4. aggregate type
*/
void pdg::DataAccessAnalysis::generateIDLFromTreeNode(TreeNode &tree_node, raw_string_ostream &fields_projection_str, raw_string_ostream &nested_struct_proj_str, std::queue<TreeNode *> &node_queue, std::string indent_level, std::string parent_struct_type_name, bool is_ret)
{
  DIType *node_di_type = tree_node.getDIType();
  assert(node_di_type != nullptr && "cannot generate IDL for node with null DIType\n");
  std::string root_di_type_name = dbgutils::getSourceLevelTypeName(*node_di_type);
  std::string root_di_type_name_raw = dbgutils::getSourceLevelTypeName(*node_di_type, true);
  DIType *node_lowest_di_type = dbgutils::getLowestDIType(*node_di_type);
  if (!node_lowest_di_type || !dbgutils::isProjectableType(*node_lowest_di_type))
    return;
  // generate idl for each field
  for (auto child_node : tree_node.getChildNodes())
  {
    DIType *field_di_type = child_node->getDIType();
    DIType *field_lowest_di_type = dbgutils::getLowestDIType(*field_di_type);
    std::string field_lowest_di_type_name = "";
    if (field_lowest_di_type != nullptr)
      field_lowest_di_type_name = dbgutils::getSourceLevelTypeName(*field_lowest_di_type, true);

    auto field_var_name = dbgutils::getSourceLevelVariableName(*field_di_type);
    auto field_type_name = dbgutils::getSourceLevelTypeName(*field_di_type, true);

    if (EnableAnalysisStats)
    {
      if (field_di_type->isBitField())
        _ksplit_stats->increaseTotalBitfield();
    }

    // check for access tags, if none, no need to put this field in projection
    bool is_global_func_op_struct = (_SDA->isGlobalOpStruct(field_lowest_di_type_name));
    bool is_func_ptr_type = dbgutils::isFuncPointerType(*field_di_type);
    if (child_node->getAccessTags().size() == 0 && !is_func_ptr_type)
      continue;

    if (EnableAnalysisStats)
    {
      if (dbgutils::isUnionPointerType(*field_di_type) || dbgutils::isUnionType(*field_di_type))
        _ksplit_stats->increaseTotalUnionNum();
    }

    if (EnableAnalysisStats)
      _ksplit_stats->increaseFieldsFieldAccess();

    // check for shared fields
    std::string field_id = pdgutils::computeTreeNodeID(*child_node);
    auto global_struct_di_type_names = _SDA->getGlobalStructDITypeNames();
    bool isGlobalStructField = (global_struct_di_type_names.find(root_di_type_name) != global_struct_di_type_names.end());
    bool is_sentinel_field = _SDA->isSentinelField(field_var_name);
    if (SharedDataFlag && !_SDA->isSharedFieldID(field_id) && !is_func_ptr_type && !isGlobalStructField && !is_sentinel_field)
      continue;

    // check for pointer arithmetic
    if (pdgutils::hasPtrArith(*child_node))
      _ksplit_stats->increasePtrArithNum();

    if (EnableAnalysisStats)
      _ksplit_stats->increaseFieldsSharedData();

    if (child_node->getCanOptOut() == true && !is_global_func_op_struct && !is_func_ptr_type)
    {
      _ksplit_stats->increaseFieldsBoundaryOpt();
      continue;
    }

    auto bw = 0;

    if (field_di_type->isBitField())
    {
      bw = field_di_type->getSizeInBits();
      if (EnableAnalysisStats)
        _ksplit_stats->increaseSharedBitfield();
    }

    field_di_type = dbgutils::stripMemberTag(*field_di_type);
    field_di_type = dbgutils::stripAttributes(*field_di_type);

    // compute access attributes
    auto annotations = inferTreeNodeAnnotations(*child_node);
    // handle attribute for return value. The in attr should be eliminated if return val is not alias of arguments
    if (is_ret)
    {
      auto it = annotations.find("[in]");
      annotations.erase(it, annotations.end());
    }

    std::string anno_str = "";
    for (auto anno : annotations)
      anno_str += anno;

    // collect fields stat
    if (EnableAnalysisStats)
    {
      _ksplit_stats->collectStats(*field_di_type, annotations);
      if (pdgutils::isVoidPointerHasMultipleCasts(*child_node))
      {
        errs() << "find void pointer casted to multiple types: " << _current_processing_func << " - " << field_id << "\n";
        _ksplit_stats->increaseUnhandledVoidPtrNum();
      }
    }

    if (is_sentinel_field)
    {
      fields_projection_str << indent_level << "array<" << field_type_name << ", "
                            << "null> " << field_var_name << ";\n";
      node_queue.push(child_node);
    }
    else if (dbgutils::isStructPointerType(*field_di_type))
    {
      std::string field_name_prefix = "";
      if (_SDA->isGlobalOpStruct(field_lowest_di_type_name))
      {
        field_name_prefix = "global_";
        parent_struct_type_name = "";
      }
      std::string ptr_postfix = "";
      while (!field_type_name.empty() && field_type_name.back() == '*')
      {
        ptr_postfix += "*";
        field_type_name.pop_back();
      }

      fields_projection_str << indent_level
                            << "projection "
                            << parent_struct_type_name
                            << "_"
                            << field_name_prefix
                            << field_type_name
                            << ptr_postfix
                            << " "
                            << field_var_name
                            << ";\n";
      node_queue.push(child_node);
    }
    else if (dbgutils::isProjectableType(*field_di_type))
    {
      std::string nested_fields_str;
      raw_string_ostream nested_fields_proj(nested_fields_str);

      std::string nested_struct_str;
      raw_string_ostream field_nested_struct_proj(nested_struct_str);

      generateIDLFromTreeNode(*child_node, nested_fields_proj, field_nested_struct_proj, node_queue, indent_level + "\t", field_type_name, is_ret);

      if (!nested_fields_proj.str().empty())
      {
        fields_projection_str << indent_level << "projection " << field_type_name << " " << field_var_name << ";\n";
        nested_struct_proj_str
            << indent_level
            << "projection < struct "
            << field_type_name
            << "> " << field_type_name << " {\n"
            << nested_fields_proj.str()
            << indent_level
            << "}"
            << "\n";

        nested_struct_proj_str << field_nested_struct_proj.str();
      }

      if (!field_var_name.empty())
      {
        fields_projection_str << indent_level
                              << "projection "
                              << field_type_name
                              << " "
                              << field_var_name
                              << ";\n";
      }
    }
    else if (dbgutils::isFuncPointerType(*field_di_type))
    {
      std::string func_ptr_name = parent_struct_type_name + "_" + field_var_name;
      if (_exported_funcs_ptr_name_map.find(func_ptr_name) == _exported_funcs_ptr_name_map.end())
        continue;
      std::string exported_func_name = _exported_funcs_ptr_name_map[func_ptr_name];
      Function *called_func = _module->getFunction(exported_func_name);
      if (called_func == nullptr)
        continue;
      fields_projection_str << indent_level << "rpc_ptr " << func_ptr_name << " " << field_var_name << ";\n";
    }
    else
    {
      patchStringAnnotation(field_type_name, anno_str);
      fields_projection_str << indent_level << field_type_name << " " << anno_str << " " << field_var_name << ((bw > 0) ? (" : " + to_string(bw)) : "") << ";\n";
    }
  }
}

void pdg::DataAccessAnalysis::generateIDLFromGlobalVarTree(GlobalVariable &gv, Tree *tree)
{
  if (!tree)
    return;
  TreeNode *root_node = tree->getRootNode();
  DIType *root_node_di_type = root_node->getDIType();
  assert(root_node_di_type != nullptr && "cannot generate projection for global with null di type\n");
  DIType *root_node_lowest_di_type = dbgutils::getLowestDIType(*root_node_di_type);
  // handle non-projectable types: int/float etc. 
  if (!root_node_lowest_di_type || !dbgutils::isProjectableType(*root_node_lowest_di_type))
  {
    auto type_name = dbgutils::getSourceLevelTypeName(*root_node_di_type);
    auto var_name = gv.getName().str();
    std::string anno = "";
    std::set<AccessTag> acc_tags;
    for (auto addr_var : root_node->getAddrVars())
    {
      for (auto user : addr_var->users())
      {
        if (Instruction *i = dyn_cast<Instruction>(user))
        {
          auto func = i->getFunction();
          if (!_SDA->isDriverFunc(*func))
            continue;
          if (LoadInst *li = dyn_cast<LoadInst>(user))
          {
            if (li->getPointerOperand() == &gv)
              acc_tags.insert(AccessTag::DATA_READ);
          }
          else if (StoreInst *si = dyn_cast<StoreInst>(user))
          {
            if (si->getPointerOperand() == &gv)
              acc_tags.insert(AccessTag::DATA_WRITE);
          }
        }
      }
    }
    // compute get/set attribute
    for (auto acc_tag : acc_tags)
    {
      if (acc_tag == AccessTag::DATA_READ)
        anno += "[get]";
      if (acc_tag == AccessTag::DATA_WRITE)
        anno += "[set]";
    }
    _idl_file << "\tglobal " << anno << " " << type_name << " " << var_name << "\n";
  }
  else
    generateIDLFromArgTree(tree, _idl_file, false, true);
}

void pdg::DataAccessAnalysis::generateIDLFromArgTree(Tree *arg_tree, std::ofstream &output_file, bool is_ret, bool is_global)
{
  if (!arg_tree)
    return;
  TreeNode *root_node = arg_tree->getRootNode();
  DIType *root_node_di_type = root_node->getDIType();

  if (EnableAnalysisStats)
  {
    _ksplit_stats->increaseFieldsDeepCopy(dbgutils::computeDeepCopyFields(*root_node_di_type));
    _ksplit_stats->increaseTotalPtrNum(dbgutils::computeDeepCopyFields(*root_node_di_type, true));
    if (dbgutils::isPointerType(*root_node_di_type))
      _ksplit_stats->increaseTotalPtrNum();
  }

  DIType *root_node_lowest_di_type = dbgutils::getLowestDIType(*root_node_di_type);
  if (!root_node_lowest_di_type || !dbgutils::isProjectableType(*root_node_lowest_di_type))
    return;
  std::queue<TreeNode *> node_queue;
  // generate root projection
  node_queue.push(root_node);
  while (!node_queue.empty())
  {
    TreeNode *current_node = node_queue.front();
    TreeNode *parent_node = current_node->getParentNode();
    node_queue.pop();
    DIType *node_di_type = current_node->getDIType();
    DIType *node_lowest_di_type = dbgutils::getLowestDIType(*node_di_type);
    // check if node needs projection
    if (!node_lowest_di_type || !dbgutils::isProjectableType(*node_lowest_di_type))
      continue;
    // get the type / variable name for the pointer field
    auto proj_type_name = dbgutils::getSourceLevelTypeName(*node_di_type, true);
    while (proj_type_name.back() == '*')
    {
      proj_type_name.pop_back();
    }
    auto proj_var_name = dbgutils::getSourceLevelVariableName(*node_di_type);
    if (current_node->isRootNode())
    {
      if (current_node->getDILocalVar() != nullptr)
        proj_var_name = dbgutils::getSourceLevelVariableName(*current_node->getDILocalVar());
    }
    std::string s;
    raw_string_ostream fields_projection_str(s);
    std::string ss;
    raw_string_ostream nested_struct_projection_str(ss);

    // for pointer to aggregate type, retrive the child node(pointed object), and generate projection
    if (dbgutils::isPointerType(*dbgutils::stripMemberTag(*node_di_type)) && !current_node->getChildNodes().empty())
      current_node = current_node->getChildNodes()[0];
    generateIDLFromTreeNode(*current_node, fields_projection_str, nested_struct_projection_str, node_queue, "\t\t", proj_type_name, is_ret);
    // handle funcptr ops struct specifically
    output_file << nested_struct_projection_str.str();
    if (_SDA->isGlobalOpStruct(proj_type_name))
    {
      if (_global_ops_fields_map.find(proj_type_name) == _global_ops_fields_map.end())
        _global_ops_fields_map.insert(std::make_pair(proj_type_name, std::set<std::string>()));

      auto accessed_field_names = pdgutils::splitStr(fields_projection_str.str(), ";");
      for (auto field_name : accessed_field_names)
      {
        _global_ops_fields_map[proj_type_name].insert(field_name);
      }
    }
    else
    {
      if (proj_var_name.empty())
        proj_var_name = proj_type_name;
      // concat ret preifx
      if (is_ret)
        proj_var_name = "ret_" + proj_var_name;

      // parent_struct name
      std::string parent_struct_type_name = "";
      if (parent_node != nullptr)
        parent_struct_type_name = dbgutils::getSourceLevelTypeName(*parent_node->getDIType(), true);
      if (!parent_struct_type_name.empty())
        parent_struct_type_name += "_";

      // union / struct prefix generation
      std::string type_prefix = "struct";
      if (dbgutils::isUnionPointerType(*node_di_type))
        type_prefix = "union";

      std::string global_keyword_prefix = "";
      if (is_global)
        global_keyword_prefix = "global ";

      output_file << "\t"
                  << global_keyword_prefix
                  << "projection < "
                  << type_prefix
                  << " "
                  << proj_type_name
                  << " > "
                  << parent_struct_type_name
                  << proj_var_name
                  << " {\n"
                  << fields_projection_str.str()
                  << "\t}\n";
    }
  }
}

static std::list<std::string> ioremap_fns = {
    "ioremap_nocache",
    "ioremap",
    "pci_ioremap_bar",
    "pci_iomap",
};

//std::string pdg::DataAccessAnalysis::handleIoRemap(Function &F, std::string &ret_type_str)
std::string handleIoRemap(Function &F, std::string &ret_type_str)
{
  auto fname = F.getName().str();

  if ((std::find(ioremap_fns.begin(), ioremap_fns.end(), fname) != ioremap_fns.end()) && (ret_type_str == "void*"))
  {
    // Add ioremap annotation
    return " [ioremap(caller)] ";
  }
  return "";
}

void pdg::DataAccessAnalysis::generateRpcForFunc(Function &F, bool process_exported_func)
{
  FunctionWrapper *fw = _PDG->getFuncWrapperMap()[&F];
  std::string rpc_str = "";
  // generate function rpc stub
  // first generate for return value
  DIType *func_ret_di_type = fw->getReturnValDIType();
  std::string ret_type_str = "";
  std::string anno_str = "";
  if (func_ret_di_type != nullptr)
  {
    ret_type_str = dbgutils::getSourceLevelTypeName(*func_ret_di_type, true);
    if (dbgutils::isStructPointerType(*func_ret_di_type))
      ret_type_str = "projection ret_" + ret_type_str;

    auto ret_tree_formal_in_root_node = fw->getRetFormalInTree()->getRootNode();
    if (ret_tree_formal_in_root_node != nullptr)
    {
      auto ret_annotations = inferTreeNodeAnnotations(*ret_tree_formal_in_root_node, true);

      if (EnableAnalysisStats)
      {
        _ksplit_stats->collectStats(*func_ret_di_type, ret_annotations);
        if (dbgutils::isUnionPointerType(*func_ret_di_type) || dbgutils::isUnionType(*func_ret_di_type))
          _ksplit_stats->increaseTotalUnionNum();
      }

      for (auto anno : ret_annotations)
      {
        anno_str += anno;
      }
      if (pdgutils::isVoidPointerHasMultipleCasts(*ret_tree_formal_in_root_node))
      {
        errs() << "find void pointer casted to multiple types: " << F.getName() << " - " << "ret value" << "\n";
        _ksplit_stats->increaseUnhandledVoidPtrNum();
      }
    }
  }
  else
  {
    ret_type_str = "void";
  }

  // determine the rpc repfix call
  // determine called func name. Need to switch to indirect call name if the function is exported
  std::string rpc_prefix = "rpc";
  std::string called_func_name = F.getName().str();
  called_func_name = pdgutils::stripFuncNameVersionNumber(called_func_name);
  // handle exported func. Switch name and rpc prefix
  if (!_SDA->isKernelFunc(F))
  {
    rpc_prefix = "rpc_ptr";
    called_func_name = getExportedFuncPtrName(called_func_name); // TODO: fix the problem when multiple global ops have same type
  }

  if (_driver_exported_func_symbols.find(called_func_name) != _driver_exported_func_symbols.end())
  {
      rpc_prefix = "rpc_export";
  }

  auto ioremap_ann = handleIoRemap(F, ret_type_str);

  rpc_str = rpc_prefix + " " + ret_type_str + ioremap_ann + " " + anno_str + " " + called_func_name + "( ";
  auto arg_list = fw->getArgList();
  for (unsigned i = 0; i < arg_list.size(); i++)
  {
    auto arg = arg_list[i];
    auto formal_in_tree = fw->getArgFormalInTree(*arg);
    if (!formal_in_tree)
      continue;
    TreeNode *root_node = formal_in_tree->getRootNode();
    DIType *arg_di_type = root_node->getDIType();
    DIType *arg_lowest_di_type = dbgutils::getLowestDIType(*arg_di_type);
    auto arg_name = dbgutils::getSourceLevelVariableName(*root_node->getDILocalVar());
    auto arg_type_name = dbgutils::getSourceLevelTypeName(*arg_di_type, true);
    std::string arg_lowest_type_name = "";
    if (arg_lowest_di_type != nullptr)
      arg_lowest_type_name = dbgutils::getSourceLevelTypeName(*arg_lowest_di_type, true);

    if (dbgutils::isStructPointerType(*arg_di_type) || dbgutils::isUnionPointerType(*arg_di_type))
    {
      std::string ptr_postfix = "";
      while (!arg_type_name.empty() && arg_type_name.back() == '*')
      {
        ptr_postfix += "*";
        arg_type_name.pop_back();
      }

      if (_SDA->isGlobalOpStruct(arg_lowest_type_name))
      {
        arg_type_name = std::string("projection ") + std::string("_global_") + arg_lowest_type_name + ptr_postfix;
      }
      else
      {
        arg_type_name = "projection " + arg_name + ptr_postfix;
      }
    }
    else if (dbgutils::isFuncPointerType(*arg_di_type))
    {
      arg_type_name = "rpc_ptr";
      arg_name = arg_name + " " + arg_name;
      // TODO: for function pointer that are not defined by global structs, we need to handle differently.
    }

    auto annotations = inferTreeNodeAnnotations(*root_node);
    std::string anno_str = "";
    for (auto anno : annotations)
      anno_str += anno;

    patchStringAnnotation(arg_type_name, anno_str);
    inferUserAnnotation(*root_node, anno_str);

    rpc_str = rpc_str + arg_type_name + " " + anno_str + " " + arg_name;

    if (EnableAnalysisStats)
    {
      _ksplit_stats->collectStats(*arg_di_type, annotations);
      if (dbgutils::isUnionPointerType(*arg_di_type) || dbgutils::isUnionType(*arg_di_type))
        _ksplit_stats->increaseTotalUnionNum();
    }
    if (pdgutils::isVoidPointerHasMultipleCasts(*root_node))
    {
      _ksplit_stats->increaseUnhandledVoidPtrNum();
      errs() << "find void pointer casted to multiple types: " << F.getName() << " - " << arg_name << "\n";
    }

    if (i != arg_list.size() - 1)
      rpc_str += ", ";
  }
  rpc_str += " ) ";
  _idl_file << rpc_str;
}

bool pdg::DataAccessAnalysis::isExportedFunc(Function &F)
{
  for (auto p : _exported_funcs_ptr_name_map)
  {
    if (p.second == F.getName().str())
      return true;
  }
  return false;
}

void pdg::DataAccessAnalysis::generateIDLForFunc(Function &F, bool process_exported_func)
{
  _current_processing_func = F.getName().str();
  auto func_wrapper_map = _PDG->getFuncWrapperMap();
  auto func_iter = func_wrapper_map.find(&F);
  assert(func_iter != func_wrapper_map.end() && "no function wrapper found (IDL-GEN)!");
  auto fw = func_iter->second;
  // process exported funcs later in special manner
  if (isExportedFunc(F) && !process_exported_func)
  {
    _kernel_funcs_regsitered_with_indirect_ptr.insert(&F);
    return;
  }
  generateRpcForFunc(F, process_exported_func);
  errs() << "generating idl for: " << F.getName() << "\n";
  _idl_file << "{\n";
  // generate projection for return value
  auto ret_arg_tree = fw->getRetFormalInTree();
  if (dbgutils::getFuncRetDIType(F) != nullptr)
    generateIDLFromArgTree(ret_arg_tree, _idl_file, true, false);
  //generate projection for each argument
  auto arg_tree_map = fw->getArgFormalInTreeMap();
  for (auto iter = arg_tree_map.begin(); iter != arg_tree_map.end(); iter++)
  {
    auto arg_tree = iter->second;
    generateIDLFromArgTree(arg_tree, _idl_file, false, false);
  }
  _idl_file << "}\n";
}

void pdg::DataAccessAnalysis::inferUserAnnotation(TreeNode &tree_node, std::string &anno_str)
{
  // get all alias of the argument
  std::set<EdgeType> edge_types = {EdgeType::PARAMETER_IN, EdgeType::DATA_ALIAS};
  auto alias_nodes = _PDG->findNodesReachedByEdges(tree_node, edge_types);
  for (auto node : alias_nodes)
  {
    auto out_neighbor_nodes = node->getOutNeighbors();
    for (auto neighbor_node : out_neighbor_nodes)
    {
      auto val = neighbor_node->getValue();
      if (val == nullptr)
        continue;
      if (CallInst *ci = dyn_cast<CallInst>(val))
      {
        auto called_func = pdgutils::getCalledFunc(*ci);
        if (called_func == nullptr)
          continue;
        std::string called_func_name = called_func->getName();
        called_func_name = pdgutils::stripFuncNameVersionNumber(called_func_name);
        if (called_func_name == "_copy_from_user" || called_func_name == "_copy_to_user")
          anno_str.append("[user]");
      }
    }
  }
}

std::set<std::string> pdg::DataAccessAnalysis::inferTreeNodeAnnotations(TreeNode &tree_node, bool is_ret)
{
  std::set<std::string> annotations;
  if (tree_node.isRootNode())
  {
    if (_SDA->isFieldUsedInStringOps(tree_node))
      annotations.insert("[string]");
    if (tree_node.getAccessTags().size() == 0)
    {
      bool is_used = false;
      for (auto addr_var : tree_node.getAddrVars())
      {
        if (!addr_var->user_empty())
        {
          is_used = true;
          break;
        }
      }
      if (!is_used)
        annotations.insert("[unused]");
    }
  }
  // for field, also check for global use info for this field
  else
  {
    auto field_id = pdgutils::computeTreeNodeID(tree_node);
    if (_SDA->isStringFieldID(field_id))
      annotations.insert("[string]");
  }

  if (!is_ret)
  {
    for (auto acc_tag : tree_node.getAccessTags())
    {
      if (acc_tag == AccessTag::DATA_READ)
        annotations.insert("[in]");
      if (acc_tag == AccessTag::DATA_WRITE)
        annotations.insert("[out]");
    }
  }

  // infer the alloc/dealloc string.
  if (!tree_node.getAllocStr().empty())
    annotations.insert(tree_node.getAllocStr());
  if (!tree_node.getDeallocStr().empty())
    annotations.insert(tree_node.getDeallocStr());

  return annotations;
}

bool pdg::DataAccessAnalysis::globalVarHasAccessInDriver(GlobalVariable &gv)
{
  for (auto user : gv.users())
  {
    if (Instruction *i = dyn_cast<Instruction>(user))
    {
      auto func = i->getFunction();
      if (_SDA->isDriverFunc(*func))
        return true;
    }
  }
  return false;
}

bool pdg::DataAccessAnalysis::isDriverDefinedGlobal(GlobalVariable &gv)
{
  auto global_var_name = gv.getName().str();
  if (_driver_defined_globalvar_names.find(global_var_name) != _driver_defined_globalvar_names.end())
    return true;
  return false;
}

bool pdg::DataAccessAnalysis::containerHasSharedFieldsAccessed(BitCastInst &bci)
{
  auto bci_node = _PDG->getNode(bci);
  assert(bci_node != nullptr && "cannot find node for container_of bitcast inst\n");
  auto alias_nodes = bci_node->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
  alias_nodes.insert(bci_node);
  for (auto alias_node : alias_nodes)
  {
    auto alias_val = alias_node->getValue();
    for (auto out_neighbor : alias_node->getOutNeighbors())
    {
      auto out_neighbor_val = out_neighbor->getValue();
      if (out_neighbor_val == nullptr)
        continue;
      if (isa<GetElementPtrInst>(out_neighbor_val))
      {
        auto container_dt = bci_node->getDIType();
        auto dt = out_neighbor->getDIType();
        if (container_dt == nullptr || dt == nullptr)
          continue;
        auto container_type_name = dbgutils::getSourceLevelTypeName(*container_dt);
        auto field_type_name = dbgutils::getSourceLevelTypeName(*dt);
        std::string id = container_type_name + field_type_name;
        if (_SDA->isSharedStructType(id))
          return true;
      }
    }
  }
  return false;
}

void pdg::DataAccessAnalysis::constructGlobalOpStructStr()
{
  for (auto pair : _global_ops_fields_map)
  {
    std::string proj_type_name = pair.first;
    std::string proj_field_str = "";
    for (auto field_name : pair.second)
    {
      proj_field_str = proj_field_str + "\t" + field_name + ";\n";
    }
    std::string proj_str = "projection < struct " + proj_type_name + " > " + "_global_" + proj_type_name + " {\n" + proj_field_str + "}\n";
    _ops_struct_proj_str += proj_str;
  }
}

void pdg::DataAccessAnalysis::computeContainerOfLocs(Function &F)
{
  for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); ++inst_iter)
  {
    if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(&*inst_iter))
    {
      int gep_access_offset = pdgutils::getGEPAccessFieldOffset(*gep);
      if (gep_access_offset >= 0)
        continue;
      // check the next instruction
      if (EnableAnalysisStats)
        _ksplit_stats->increaseTotalContainerof();
      Instruction *next_i = gep->getNextNonDebugInstruction();
      if (BitCastInst *bci = dyn_cast<BitCastInst>(next_i))
      {
        auto inst_node = _PDG->getNode(*bci);
        if (inst_node != nullptr)
        {
          auto node_di_type = inst_node->getDIType();
          if (node_di_type == nullptr)
            continue;
          std::string di_type_name = dbgutils::getSourceLevelTypeName(*node_di_type, true);
          if (_SDA->isSharedStructType(di_type_name))
          {
            if (!containerHasSharedFieldsAccessed(*bci))
              continue;
            errs() << "hello\n";
            _container_of_insts.insert(bci);
            if (EnableAnalysisStats)
            {
              _ksplit_stats->increaseSharedContainerof();
              if (DEBUG)
                errs() << "shared container_of: " << F.getName() << " - " << di_type_name << " - " << *bci << "\n";
            }
          }
        }
      }
    }
  }
}

void pdg::DataAccessAnalysis::printContainerOfStats()
{
  errs() << " ============== container of stats =============\n";
  errs() << "num of container_of access shared states: " << _container_of_insts.size() << "\n";
  for (auto i : _container_of_insts)
  {
    errs() << "container_of: " << i->getFunction()->getName() << " -- " << *i << "\n";
  }
  errs() << " ===============================================\n";
}

// ksplit stats collect
void pdg::KSplitStats::collectStats(DIType &dt, std::set<std::string> &annotations)
{
  if (dbgutils::isVoidPointerType(dt))
  {
    increaseVoidPtrNum();
    increaseSharedPtrNum();
  }
  else if (dbgutils::isUnionPointerType(dt))
  {
    increaseSharedUnionNum();
    increaseSharedPtrNum();
  }
  else if (dbgutils::isArrayType(dt))
    increaseArrayNum();
  else if (dbgutils::isFuncPointerType(dt))
    increaseFuncPtrNum();
  else if (annotations.find("[string]") != annotations.end())
    increaseStringNum();
  else if (dbgutils::isPointerType(dt))
    increaseSharedPtrNum();
}

pdg::DomainTag pdg::DataAccessAnalysis::computeFuncDomainTag(Function &F)
{
  if (_SDA->isDriverFunc(F))
    return DomainTag::DRIVER_DOMAIN;
  else
    return DomainTag::KERNEL_DOMAIN;
}

std::string pdg::DataAccessAnalysis::getExportedFuncPtrName(std::string func_name)
{
  for (auto p : _exported_funcs_ptr_name_map)
  {
    if (p.second == func_name)
      return p.first;
  }
  return func_name;
}

static RegisterPass<pdg::DataAccessAnalysis>
    DAA("daa", "Data Access Analysis Pass", false, true);
