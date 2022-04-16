#include "DataAccessAnalysis.hh"

std::map<std::string, std::string> primitive_type_map {
  {"long long int", "u64"},
  {"long long int*", "u64*"},
  {"long long", "u64"},
  {"long long*", "u64*"},
  {"long int", "u64"},
  {"long int*", "u64*"},
  {"long unsigned int", "u64"},
  {"long unsigned int*", "u64*"},
  {"long long unsigned int", "u64"},
};

using namespace llvm;

char pdg::DataAccessAnalysis::ID = 0;

cl::opt<bool> SharedDataFlag("sd", llvm::cl::desc("turn on shared data optimization"), llvm::cl::init(true), llvm::cl::value_desc("shared_data"));

void pdg::DataAccessAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<SharedDataAnalysis>();
  AU.setPreservesAll();
}

void patchStringAnnotation(std::string &field_type_name, std::set<std::string> &annotations)
{
  auto it = annotations.find("string");
  if (it != annotations.end())
  {
    annotations.erase(it, annotations.end());
    field_type_name = "string *";
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
  // _global_var_access_info.open("global_var_access_info.idl");
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
  // count total func size
  if (EnableAnalysisStats)
    _ksplit_stats->_total_func_size += total_num_funcs;
  // compute collocated sites
  computeCollocatedAllocsite(M);

  errs() << "Finish analyzing data access info.";

  return false;
}

// API for generating IDL for boundary funcs and global variables
void pdg::DataAccessAnalysis::generateSyncStubsForBoundaryFunctions(Module &M)
{
  _idl_file.open("kernel.idl");
  _idl_file << "// Sync stubs for boundary functions\n";
  _idl_file << "module kernel {\n";
  std::vector<std::string> boundary_func_names(_SDA->getBoundaryFuncNames().begin(), _SDA->getBoundaryFuncNames().end());
  _transitive_boundary_funcs = _SDA->computeBoundaryTransitiveClosure();
  std::sort(boundary_func_names.begin(), boundary_func_names.end());
  for (auto func_name : boundary_func_names)
  {
    // need to concate the _nesCheck postfix, because nescheck change the signature
    Function* nescheck_func = pdgutils::getNescheckVersionFunc(M, func_name);
    if (nescheck_func == nullptr || nescheck_func->isDeclaration())
      continue;
    generateIDLForFunc(*nescheck_func);
  }

  // genereate additional func call stubs for kernel funcs registered on the driver side
  // EnableAnalysisStats = false;
  for (auto F : _kernel_funcs_regsitered_with_indirect_ptr)
  {
    if (F == nullptr || F->isDeclaration())
      continue;
    generateIDLForFunc(*F, true);
  }
  // generate rpc_export stub for functions exported form driver through export_symbol
  for (auto s : _driver_exported_func_symbols)
  {
    Function* func = M.getFunction(StringRef(s));
    if (func == nullptr || func->isDeclaration())
      continue;
    generateIDLForFunc(*func, true);
    // Function *F = M.getFunction(StringRef(s));
    // Function *nescheck_func = pdgutils::getNescheckVersionFunc(M, F->getName().str());
    // if (nescheck_func == nullptr || nescheck_func->isDeclaration())
    //   continue;
    // generateIDLForFunc(*nescheck_func, true);
  }

  constructGlobalOpStructStr();
  _idl_file << _ops_struct_proj_str << "\n";
  _idl_file << "\n}\n";
  _idl_file.close();
}

void pdg::DataAccessAnalysis::generateSyncStubsForGlobalVars()
{
  _idl_file.open("kernel.idl", std::ios_base::app);
  // generate IDL for global variables
  _idl_file << "// Sync stubs for global variables\n";
  _generating_idl_for_global = true;
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
  _generating_idl_for_global = false;
  _idl_file.close();
}

std::set<pdg::Node *> pdg::DataAccessAnalysis::findCrossDomainParamNode(Node &n, bool is_backward)
{
  std::queue<Node *> node_queue;
  std::set<EdgeType> search_edge_types = {
      EdgeType::PARAMETER_IN,
      EdgeType::DATA_ALIAS,
      EdgeType::DATA_RET};
  node_queue.push(&n);
  std::set<Node *> seen_nodes;
  std::set<Node *> cross_domain_nodes;
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
  // first composing the allocator string in format alloc<{{size, GP_FLAG}}>
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
  // if any alias is address variable of the parameter tree, then we consider the allocated
  // object need to be allocated at the caller side.
  for (auto alias_node : alias_nodes)
  {
    // alias_node->dump();
    if (alias_node->isAddrVarNode())
    {
      auto param_tree_node = alias_node->getAbstractTreeNode();
      TreeNode *tn = (TreeNode *)param_tree_node;
      tn->setAllocStr(alloc_str + "(caller)");
    }
    else
    {
      // in this case, the allocated object is passed across isolation boundary.
      // the tracking is path insensitive. If two functions are called in different branches, both function would have the alloc attributes created for the received parameter
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

void pdg::DataAccessAnalysis::computeCollocatedAllocsite(Module &M)
{
  auto allocators = _PDG->getAllocators();
  for (auto allocator : allocators)
  {
    checkCollocatedAllocsite(*allocator);
  }
}

void pdg::DataAccessAnalysis::checkCollocatedAllocsite(Value &alloc_site)
{
  // first identify cast instruction
  for (auto user : alloc_site.users())
  {
    if (auto bi = dyn_cast<BitCastInst>(user))
    {
      // TODO: we need to somehow issue warnings for users
    }
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
  {
    tree_node.is_sentinel = true;
    tree_node.addAccessTag(AccessTag::DATA_READ);
  }

  // check for special cases:
  // 1. check if current field is stored with a function address. If so, add the function to exported function list
  // 2. check whether a new object is stored to the current node's address. If this is true and current node is a struct pointer, mark all fields to be synchronized.
  // 3. detect variadic gep accesses. If this case happen, we might fail to detect some field accesses
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

        // add a function and check whether this value is newly allocated
        // here the strategy is mark all the fields
        if (isa<GlobalVariable>(val_op))
        {
          for (auto child_node : tree_node.getChildNodes())
          {
            child_node->addAccessTag(AccessTag::DATA_READ);
          }
          // stop processing since we find a new object stored to this address
          return;
        }
      }
      if (MemCpyInst *mci = dyn_cast<MemCpyInst>(user))
      {
        auto dst_val = mci->getDest();
        auto src_val = mci->getSource()->stripPointerCasts();
        // TODO: we should switch the logic to detect whether a new
        // object is stored copied to the passed pointer
        if (isa<GlobalVariable>(src_val))
        {
          // mark the whole tree as read
          auto tree = tree_node.getTree();
          tree->addAccessForAllNodes(AccessTag::DATA_READ);
          // stop processing since we find a new object stored to this address
          return;
        }
      }
      if (_transitive_boundary_funcs.find(func) == _transitive_boundary_funcs.end())
        continue;
      // detect variadic gep accesses
      if (auto gep = dyn_cast<GetElementPtrInst>(user))
      {
        if (!gep->hasAllConstantIndices())
        {
          if (pdgutils::isStructPointerType(*gep->getPointerOperand()->getType()))
          {
            errs() << "[Warning]: GEP has variadic idx. May miss field access - " << gep->getFunction()->getName() << "\n";
          }
        }
      }
    }
  }

  // consider exported function pointers are all accessed
  // if (tree_node.getDIType() != nullptr && (dbgutils::isFuncPointerType(*tree_node.getDIType())))
  // {
  //   std::string func_ptr_rpc_ref = parent_node_type_name + "_" + field_var_name;
  //   if (_exported_funcs_ptr_name_map.find(func_ptr_rpc_ref) != _exported_funcs_ptr_name_map.end())
  //   {
  //     tree_node.addAccessTag(AccessTag::DATA_READ);
  //     auto parent_node = tree_node.getParentNode();
  //     while (parent_node != nullptr)
  //     {
  //       parent_node->addAccessTag(AccessTag::DATA_READ);
  //       parent_node = parent_node->getParentNode();
  //     }
  //   }
  // }

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
      if (addr_var_node != nullptr)
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
/*
This function takes a tree node as input, and then generate the IDL for this node.
If a node is a struct or union, then the code would generate a projection for this struct, based on it's fields information
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
    if (!field_di_type) // void retrun value etc
      continue;
    DIType *field_lowest_di_type = dbgutils::getLowestDIType(*field_di_type);
    std::string field_lowest_di_type_name = "";
    if (field_lowest_di_type != nullptr)
      field_lowest_di_type_name = dbgutils::getSourceLevelTypeName(*field_lowest_di_type, true);

    auto field_var_name = dbgutils::getSourceLevelVariableName(*field_di_type);
    auto field_type_name = dbgutils::getSourceLevelTypeName(*field_di_type, true);

    // check for access tags, if none, no need to put this field in projection
    bool is_func_ptr_type = dbgutils::isFuncPointerType(*field_di_type);
    if (child_node->getAccessTags().size() == 0 && !is_func_ptr_type)
      continue;

    bool is_global_func_op_struct = (_SDA->isGlobalOpStruct(field_lowest_di_type_name));
    // check for shared fields
    std::string field_id = pdgutils::computeTreeNodeID(*child_node);
    auto global_struct_di_type_names = _SDA->getGlobalStructDITypeNames();
    bool isGlobalStructField = (global_struct_di_type_names.find(root_di_type_name) != global_struct_di_type_names.end());
    /* 1. filter out private fields
       2. overapproximiate for function pointer (sync all func ptr across)
       3. global struct field
       4. inferred sentiinel fields
       5. anonymous union (as shared fields only consider struct)
    */
    if (SharedDataFlag && !_SDA->isSharedFieldID(field_id) && !is_func_ptr_type && !isGlobalStructField && child_node->is_sentinel && field_type_name == "union")
      continue;
    // collect shared field stat
    child_node->is_shared = true;
    // countControlData(*child_node);
    auto access_tags = child_node->getAccessTags();

    // opt out field
    if (EnableAnalysisStats && !_generating_idl_for_global)
    {
      if (child_node->getCanOptOut() == true && !is_global_func_op_struct && !is_func_ptr_type)
      {
        _ksplit_stats->_fields_removed_boundary_opt += 1;
        continue;
      }
    }

    //  collect bit field stats
    auto bw = 0;
    if (field_di_type->isBitField())
      bw = field_di_type->getSizeInBits();

    field_di_type = dbgutils::stripMemberTag(*field_di_type);
    field_di_type = dbgutils::stripAttributes(*field_di_type);
    // compute access attributes
    auto annotations = inferTreeNodeAnnotations(*child_node);
    // infer may_within attribute
    // inferMayWithin(*child_node, annotations);
    // count inferred string
    // if (EnableAnalysisStats && !_generating_idl_for_global)
    //   _ksplit_stats->collectInferredStringStats(annotations);
    // handle attribute for return value. The in attr should be eliminated if return val is not alias of arguments
    if (is_ret)
    {
      auto it = annotations.find("in");
      annotations.erase(it, annotations.end());
    }

    // construct annotation string
    if (child_node->is_sentinel)
    {
      // null terminated arraies
      fields_projection_str << indent_level << "array<" << field_type_name << ", "
                            << "null> " << field_var_name << ";\n";
      node_queue.push(child_node);
    }
    else if (child_node->isSeqPtr() && !dbgutils::isArrayType(*field_di_type)) // leave sized array to be handled by default generation
    {
      std::string element_proj_type_str = field_lowest_di_type_name;
      if (dbgutils::isStructType(*field_lowest_di_type))
      {
        element_proj_type_str = "projection " + field_lowest_di_type_name;
        node_queue.push(child_node);
      }
      if (dbgutils::isStructPointerType(*field_di_type))
        element_proj_type_str += "*";

      fields_projection_str << indent_level << "array<" << element_proj_type_str << ", "
                            << "size_unknown> " << field_var_name << ";\n";
    }
    else if (dbgutils::isStructPointerType(*field_di_type))
    {
      if (!_SDA->isSharedStructType(field_lowest_di_type_name))
        continue;
      // handle self-reference type such as linked list
      if (field_lowest_di_type_name == root_di_type_name_raw)
      {
        fields_projection_str
            << indent_level
            << "projection " << field_lowest_di_type_name << "* "
            << field_var_name
            << ";\n";
        continue;
      }

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

      // handle nested struct
      std::string projected_container_str = "struct";
      if (dbgutils::isUnionType(*field_di_type))
      {
        projected_container_str = "union";
        // TODO: need to resolve union types (both tag and anonymous)
        // fields_projection_str << indent_level << "[anon_union]"
        //                       << "\n";
      }
      else
      {
        // for struct, generate projection for the nested struct
        generateIDLFromTreeNode(*child_node, nested_fields_proj, field_nested_struct_proj, node_queue, indent_level + "\t", field_type_name, is_ret);
      }

      // if (dbgutils::isUnionType(*field_di_type))
      // {
      //   if (field_var_name.empty())
      //     field_var_name = "[anon_union]";
      // }
      if (!nested_fields_proj.str().empty())
      {
        // if nested struct is global op struct, then create reference and don't generate nested struct)
        if (_SDA->isGlobalOpStruct(field_lowest_di_type_name))
        {
          if (_global_ops_fields_map.find(field_lowest_di_type_name) == _global_ops_fields_map.end())
            _global_ops_fields_map.insert(std::make_pair(field_lowest_di_type_name, std::set<std::string>()));

          auto accessed_field_names = pdgutils::splitStr(nested_fields_proj.str(), ";");
          for (auto field_name : accessed_field_names)
          {
            _global_ops_fields_map[field_lowest_di_type_name].insert(field_name);
          }
          // only produce a reference to global definition
          fields_projection_str << indent_level
                            << "projection "
                            << parent_struct_type_name
                            << "_"
                            << "global_"
                            << field_type_name
                            << "* "
                            << field_var_name
                            << ";\n";
        }
        else
        {
          // if is anonymous struct/union, directly generate projection inside the current projection
          if (field_var_name.empty())
          {
            fields_projection_str 
            << indent_level << "{\n" 
            << nested_fields_proj.str() 
            << indent_level << "}\n";
          }
          else
          {
            // named union/struct, generate a separate projection
            field_type_name = field_var_name;
            fields_projection_str << indent_level << "projection " << field_type_name << " " << field_var_name << ";\n";
            nested_struct_proj_str
                << indent_level
                << "projection < "
                << projected_container_str << " "
                << field_type_name
                << "> " << field_type_name << " {\n"
                << nested_fields_proj.str()
                << indent_level
                << "}\n";
          }

          nested_struct_proj_str << field_nested_struct_proj.str();
        }
      }
    }
    else if (dbgutils::isFuncPointerType(*field_di_type))
    {
      std::string func_ptr_rpc_ref = parent_struct_type_name + "_" + field_var_name;
      if (_exported_funcs_ptr_name_map.find(func_ptr_rpc_ref) == _exported_funcs_ptr_name_map.end())
        continue;
      std::string exported_func_name = _exported_funcs_ptr_name_map[func_ptr_rpc_ref];
      Function *called_func = _module->getFunction(exported_func_name);
      if (called_func == nullptr)
        continue;
      
      // if the defintion doesn't exist yet, recording the func name, the def will be genereated later
      // if (_exist_func_defs.find(exported_func_name) == _exist_func_defs.end())
      //   _exist_func_defs.insert(exported_func_name);
      // else
      //   func_ptr_rpc_ref = exported_func_name; // if exist def is found, replace the def
      fields_projection_str << indent_level << "rpc_ptr " << exported_func_name << " " << field_var_name << ";\n";
    }
    else
    {
      patchStringAnnotation(field_type_name, annotations);
      if (primitive_type_map.find(field_type_name) != primitive_type_map.end())
        field_type_name = primitive_type_map[field_type_name];
      std::string anno_str = pdgutils::constructAnnoStr(annotations);
      fields_projection_str << indent_level << field_type_name << " " << anno_str << " " << field_var_name << ((bw > 0) ? (" : " + to_string(bw)) : "") << ";\n"; // consider bitfield handling
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
    _idl_file << "global " << anno << " " << type_name << " " << var_name << ";\n";
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
  if (!root_node_di_type)
    return;
  // collect root node stats
  // _ksplit_stats->_fields_field_analysis += 1;
  // _ksplit_stats->_fields_shared_analysis += 1;
  // if (EnableAnalysisStats && !is_global)
  // {
  //   auto root_type_name = dbgutils::getSourceLevelTypeName(*root_node_di_type, true);
  // collect deep copy field stats
  auto deep_copy_fields_num = dbgutils::computeDeepCopyFields(*root_node_di_type);
  auto deep_copy_ptr_num = dbgutils::computeDeepCopyFields(*root_node_di_type, true);
  _ksplit_stats->_fields_deep_copy += deep_copy_fields_num; // transitively count the number of field
  _ksplit_stats->_total_ptr_num += deep_copy_ptr_num;       // transitively count the number of pointer field in this type

  DIType *root_node_lowest_di_type = dbgutils::getLowestDIType(*root_node_di_type);
  if (!root_node_lowest_di_type || !dbgutils::isProjectableType(*root_node_lowest_di_type))
    return;
  std::queue<TreeNode *> node_queue;
  // generate root projection
  node_queue.push(root_node);
  while (!node_queue.empty())
  {
    // retrive node and obtian its di type
    TreeNode *current_node = node_queue.front();
    TreeNode *parent_node = current_node->getParentNode();
    node_queue.pop();
    DIType *node_di_type = current_node->getDIType();
    DIType *node_lowest_di_type = dbgutils::getLowestDIType(*node_di_type);
    // check if node needs projection
    if (!node_lowest_di_type || !dbgutils::isProjectableType(*node_lowest_di_type))
      continue;
    // no IDL generation for non-shared data type. If a type is not shared, all the sub-fields are not shared
    std::string node_lowest_di_type_name_raw = dbgutils::getSourceLevelTypeName(*node_lowest_di_type, true);
    // filter out non-shared struct
    if (dbgutils::isStructType(*node_lowest_di_type) && !current_node->isRootNode() && !_SDA->isSharedStructType(node_lowest_di_type_name_raw))
      continue;
    // get the type / variable name for the pointer field
    auto proj_type_name = dbgutils::getSourceLevelTypeName(*node_di_type, true);
    while (proj_type_name.back() == '*')
    {
      proj_type_name.pop_back();
    }
    // for non-root node, the node must be a field. Thus, we retrive the field name through the node di type itself
    auto proj_var_name = dbgutils::getSourceLevelVariableName(*node_di_type);
    // for root node, the name is the variable's name. We retrive it through DILocalVar.
    if (current_node->isRootNode())
    {
      if (current_node->getDILocalVar() != nullptr)
      {
        proj_var_name = dbgutils::getSourceLevelVariableName(*current_node->getDILocalVar());
        assert(proj_var_name != "" && "cannot find parameter name in generateIDLFromArgTree\n");
      }
    }

    std::string s;
    raw_string_ostream fields_projection_str(s);
    std::string ss;
    // nested struct or union
    raw_string_ostream nested_struct_projection_str(ss);

    // for pointer to aggregate type, retrive the child node(pointed object), and generate projection
    if (dbgutils::isPointerType(*dbgutils::stripMemberTag(*node_di_type)) && !current_node->getChildNodes().empty())
      current_node = current_node->getChildNodes()[0];
    generateIDLFromTreeNode(*current_node, fields_projection_str, nested_struct_projection_str, node_queue, "\t\t", proj_type_name, is_ret);
    output_file << nested_struct_projection_str.str();
    // store encountered global ops definitions
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

      // concat ret preifx for return values
      std::string ret_prefix = "";
      if (is_ret)
        ret_prefix = "ret_";

      output_file << "\t"
                  << global_keyword_prefix
                  << "projection < "
                  << type_prefix
                  << " "
                  << proj_type_name
                  << " > "
                  << ret_prefix
                  << parent_struct_type_name
                  << proj_type_name
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

// std::string pdg::DataAccessAnalysis::handleIoRemap(Function &F, std::string &ret_type_str)
std::string handleIoRemap(Function &F, std::string &ret_type_str)
{
  auto fname = F.getName().str();

  if ((std::find(ioremap_fns.begin(), ioremap_fns.end(), fname) != ioremap_fns.end()) && (ret_type_str == "void*"))
  {
    // Add ioremap annotation
    return "ioremap(caller)";
  }
  return "";
}

void pdg::DataAccessAnalysis::generateRpcForFunc(Function &F, bool process_exported_func)
{
  // need to use this wrapper to handle nescheck rewrittern funcs
  FunctionWrapper *fw = getNescheckFuncWrapper(F); 
  std::string rpc_str = "";
  // generate function rpc stub
  // first generate for return value
  DIType *func_ret_di_type = fw->getReturnValDIType();
  std::string ret_type_str = "";
  std::string ret_anno_str = "";
  // handle return type str
  if (func_ret_di_type != nullptr)
  {
    ret_type_str = dbgutils::getSourceLevelTypeName(*func_ret_di_type, true);
    // TODO: swap primitive type name, should support all types in compiler in future
    if (primitive_type_map.find(ret_type_str) != primitive_type_map.end())
      ret_type_str = primitive_type_map[ret_type_str];
    if (dbgutils::isStructPointerType(*func_ret_di_type) || dbgutils::isStructType(*func_ret_di_type))
      ret_type_str = "projection ret_" + ret_type_str;
    auto ret_tree_formal_in_root_node = fw->getRetFormalInTree()->getRootNode();
    if (ret_tree_formal_in_root_node != nullptr)
    {
      auto ret_annotations = inferTreeNodeAnnotations(*ret_tree_formal_in_root_node, true);
      patchStringAnnotation(ret_type_str, ret_annotations);
      ret_anno_str = pdgutils::constructAnnoStr(ret_annotations);
      // record annotations, used by ksplit collector
      ret_tree_formal_in_root_node->is_shared = true;
      auto ioremap_ann = handleIoRemap(F, ret_type_str);
      if (!ioremap_ann.empty())
      {
        ret_annotations.insert(ioremap_ann);
        ret_tree_formal_in_root_node->is_ioremap = true;
      }
      ret_tree_formal_in_root_node->annotations.insert(ret_annotations.begin(), ret_annotations.end());
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
  called_func_name = pdgutils::getSourceFuncName(called_func_name);
  assert(_exist_func_defs.find(called_func_name) == _exist_func_defs.end() && "duplicate func definition!\n");
  _exist_func_defs.insert(called_func_name);
  // handle exported func called from kernel to driver. Switch name and rpc prefix
  if (!_SDA->isKernelFunc(called_func_name))
  {
    rpc_prefix = "rpc_ptr";
  }
  // indirect call from kernel  to driver
  if (_driver_exported_func_symbols.find(called_func_name) != _driver_exported_func_symbols.end())
  {
    rpc_prefix = "rpc_export";
  }

  // if string annotation is found, change the type name to string
  rpc_str = rpc_prefix + " " + ret_type_str + " " + ret_anno_str + " " + called_func_name + "( ";
  auto arg_list = fw->getArgList();
  for (unsigned i = 0; i < arg_list.size(); i++)
  {
    auto arg = arg_list[i];
    auto formal_in_tree = fw->getArgFormalInTree(*arg);
    if (!formal_in_tree)
      continue;
    TreeNode *root_node = formal_in_tree->getRootNode();
    // countControlData(*root_node);
    // _ksplit_stats->increaseParamNum();
    DIType *arg_di_type = root_node->getDIType();
    DIType *arg_lowest_di_type = dbgutils::getLowestDIType(*arg_di_type);
    auto arg_name = dbgutils::getSourceLevelVariableName(*root_node->getDILocalVar());
    auto arg_type_name = dbgutils::getSourceLevelTypeName(*arg_di_type, true);
    std::string arg_lowest_type_name = "";
    if (arg_lowest_di_type != nullptr)
      arg_lowest_type_name = dbgutils::getSourceLevelTypeName(*arg_lowest_di_type, true);
    if (dbgutils::isStructPointerType(*arg_di_type) || dbgutils::isUnionPointerType(*arg_di_type))
    {
      if (_SDA->isGlobalOpStruct(arg_lowest_type_name))
      {
        arg_type_name = std::string("projection ") + std::string("_global_") + arg_lowest_type_name;
      }
      else
      {
        arg_type_name = "projection " + arg_type_name;
      }
    }
    else if (dbgutils::isFuncPointerType(*arg_di_type))
    {
      arg_type_name = "rpc_ptr";
      if (_exported_funcs_ptr_name_map.find(arg_name) != _exported_funcs_ptr_name_map.end())
        arg_type_name = arg_type_name + " " + _exported_funcs_ptr_name_map[arg_name];
      else
        arg_type_name = arg_type_name + " " + arg_name;
      // auto pointed_funcs = getPointedFuncAtArgIdx(F, i);
      // TODO: for function pointer that are not defined by global structs, we need to handle differently.
      // need to reason about call sites to construct the function definition
    }

    auto annotations = inferTreeNodeAnnotations(*root_node);
    inferUserAnnotation(*root_node, annotations);

    // store annotations in the root node, used by ksplit stats collector
    root_node->is_shared = true;
    root_node->annotations.insert(annotations.begin(), annotations.end());

    // if string annotation is found, change the type name to string
    patchStringAnnotation(arg_type_name, annotations);
    std::string anno_str = pdgutils::constructAnnoStr(annotations);
    // TODO: swap unsupported type name, should support in the IDL compiler in future
    if (primitive_type_map.find(arg_type_name) != primitive_type_map.end())
      arg_type_name = primitive_type_map[arg_type_name];

    // rearrange the location for pointer symbol *
    std::string ptr_postfix = "";
    while (!arg_type_name.empty() && arg_type_name.back() == '*')
    {
      ptr_postfix += "*";
      arg_type_name.pop_back();
    }
    rpc_str = rpc_str + arg_type_name + " " + anno_str + " " + ptr_postfix + arg_name;

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
    // need to consider nesCheck rewrite
    std::string func_name = p.second;
    std::string nescheck_func_name = func_name + "_nesCheck";
    if (nescheck_func_name == F.getName().str() || func_name == F.getName().str())
      return true;
  }
  return false;
}

void pdg::DataAccessAnalysis::generateIDLForFunc(Function &F, bool processing_exported_func)
{
  _current_processing_func = F.getName().str();
  // auto func_wrapper_map = _PDG->getFuncWrapperMap();
  // auto func_iter = func_wrapper_map.find(&F);
  // assert(func_iter != func_wrapper_map.end() && "no function wrapper found (IDL-GEN)!");
  // auto fw = func_iter->second;
  FunctionWrapper *fw = getNescheckFuncWrapper(F);
  // process exported funcs later in special manner because of syntax requirement
  if (isExportedFunc(F) && !processing_exported_func)
  {
    _kernel_funcs_regsitered_with_indirect_ptr.insert(&F);
    return;
  }
  generateRpcForFunc(F, processing_exported_func);
  errs() << "generating idl for: " << F.getName() << "\n";
  _idl_file << "{\n";
  // generate projection for return value
  auto ret_arg_tree = fw->getRetFormalInTree();
  if (fw->getReturnValDIType() != nullptr)
  {
    generateIDLFromArgTree(ret_arg_tree, _idl_file, true, false);
  }
  // generate projection for each argument
  auto arg_tree_map = fw->getArgFormalInTreeMap();
  for (auto iter = arg_tree_map.begin(); iter != arg_tree_map.end(); iter++)
  {
    auto arg_tree = iter->second;
    generateIDLFromArgTree(arg_tree, _idl_file, false, false);
  }
  _idl_file << "}\n";
}

void pdg::DataAccessAnalysis::inferMayWithin(TreeNode &tree_node, std::set<std::string> &anno_str)
{
  // check the tree_node's address variable against other nodes address variables, and determine whether it alias with other nodes
  DIType *cur_node_di_type = tree_node.getDIType();
  if (!cur_node_di_type)
    return;
  if (!dbgutils::isPointerType(*cur_node_di_type))
    return;
  auto parent_node = tree_node.getParentNode();
  if (!parent_node)
    return;

  auto cur_node_addr_vars = tree_node.getAddrVars();
  for (auto child_node : parent_node->getChildNodes())
  {
    if (child_node == &tree_node)
      continue;
    auto field_name = dbgutils::getSourceLevelVariableName(*child_node->getDIType());
    auto child_node_di_type = child_node->getDIType();
    if (!dbgutils::isPointerType(*child_node_di_type))
      continue;
    auto field_id = pdgutils::computeTreeNodeID(*child_node);
    if (!_SDA->isSharedFieldID(field_id))
      continue;
    auto child_node_addr_vars = child_node->getAddrVars();
    // if the address variable overlap with each other, then print within warning
    for (auto cur_node_addr_var : cur_node_addr_vars)
    {
      if (child_node_addr_vars.find(cur_node_addr_var) != child_node_addr_vars.end())
      {
        // construct within string
        std::string may_within_anno = "may_within<self->" + field_name + ", " + "size>";
        anno_str.insert(may_within_anno);
        break;
      }
    }
  }
}

void pdg::DataAccessAnalysis::inferUserAnnotation(TreeNode &tree_node, std::set<std::string> &annotations)
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
        {
          std::string user_anno = "user";
          Value *copy_bytes_size = ci->getArgOperand(2);
          if (TruncInst *ti = dyn_cast<TruncInst>(copy_bytes_size))
          {
            Value* trunced_val = ti->getOperand(0);
            if (LoadInst *li = dyn_cast<LoadInst>(trunced_val))
            {
              Value *value_store_reg = li->getPointerOperand();
              for (auto user : value_store_reg->users())
              {
                if (StoreInst *si = dyn_cast<StoreInst>(user))
                {
                  if (ConstantInt *ci = dyn_cast<ConstantInt>(si->getValueOperand()))
                  {
                    unsigned bytes_size = ci->getZExtValue();
                    user_anno = user_anno + "<{{" + std::to_string(bytes_size) + "}}>";
                  }
                }
              }
            }
          }
          else
          {
            user_anno = user_anno + "<size_unknown>";
          }
          annotations.insert(user_anno);
          tree_node.is_user = true;
        }
      }
      // checking for bounds because this field is used in pointer arithmetic
      // if (LoadInst *li = dyn_cast<LoadInst>(val))
      // {
      //   for (auto user : li->users())
      //   {
      //     if (isa<CastInst>(user))
      //       annotations.insert("[bound_check]");
      //   }
      // }
      // if (isa<CastInst>(val))
      //   annotations.insert("[bound_check]");
    }
  }
}

std::set<std::string> pdg::DataAccessAnalysis::inferTreeNodeAnnotations(TreeNode &tree_node, bool is_ret)
{
  std::set<std::string> annotations;
  if (tree_node.isRootNode())
  {
    // infer string annotation
    DIType *tree_dt = tree_node.getDIType();
    if (tree_dt)
    {
      // check if the node is directly used in some string operations
      if (dbgutils::isCharPointer(*tree_dt))
      {
        if (_SDA->isFieldUsedInStringOps(tree_node))
        {
          annotations.insert("string");
          tree_node.is_string = true;
        }
      }
    }
    // infer unused attribute
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
        annotations.insert("unused");
    }
  }
  // for field, also check for global use info for this field
  else
  {
    auto field_id = pdgutils::computeTreeNodeID(tree_node);
    if (_SDA->isStringFieldID(field_id))
    {
      annotations.insert("string");
      tree_node.is_string = true;
    }
  }

  if (!is_ret)
  {
    auto acc_tags = tree_node.getAccessTags();
    for (auto acc_tag : acc_tags)
    {
      if (acc_tag == AccessTag::DATA_READ)
        annotations.insert("in");
      else if (acc_tag == AccessTag::DATA_WRITE)
        annotations.insert("out");
    }
  }
  return annotations;
}

/*
if an argument is a funciton pointer, check the call sites of the function
and return all the possible functions pointed by the argument
*/
std::set<Function *> pdg::DataAccessAnalysis::getPointedFuncAtArgIdx(Function &F, unsigned arg_idx)
{
  std::set<Function *> ret;
  for (auto user : F.users())
  {
    if (CallInst *ci = dyn_cast<CallInst>(user))
    {
      auto func_ptr_arg = ci->getArgOperand(arg_idx);
      assert(func_ptr_arg != nullptr && "cannot get pointed func at arg idx!\n");
      if (Function* f = dyn_cast<Function>(func_ptr_arg))
        ret.insert(f);
    }
  }
  return ret;
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

pdg::FunctionWrapper* pdg::DataAccessAnalysis::getNescheckFuncWrapper(Function &F)
{
  // get function name
  std::string func_name = F.getName().str();
  // obtain wrapper map
  auto func_wrapper_map = _PDG->getFuncWrapperMap();
  // strip _nesCheck postfix
  auto pos = func_name.find("_nesCheck");
  if (pos != std::string::npos)
  {
    func_name = func_name.substr(0, pos);
    Function *f = _module->getFunction(func_name);
    auto func_iter = func_wrapper_map.find(f);
    assert(func_iter != func_wrapper_map.end() && "no function wrapper found (IDL-GEN)!");
    return func_iter->second;
  }
  // if not end with _nesCheck, return the wrapper for the origin func
  return func_wrapper_map[&F];
}

// bool pdg::DataAccessAnalysis::containerHasSharedFieldsAccessed(BitCastInst &bci, std::string struct_type_name)
// {
//   auto bci_node = _PDG->getNode(bci);
//   assert(bci_node != nullptr && "cannot find node for container_of bitcast inst\n");
//   auto alias_nodes = bci_node->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
//   alias_nodes.insert(bci_node);
//   for (auto alias_node : alias_nodes)
//   {
//     auto alias_val = alias_node->getValue();
//     for (auto out_neighbor : alias_node->getOutNeighbors())
//     {
//       auto out_neighbor_val = out_neighbor->getValue();
//       if (out_neighbor_val == nullptr)
//         continue;
//       // check for fields accesses
//       if (isa<GetElementPtrInst>(out_neighbor_val))
//       {
//         auto dt = out_neighbor->getDIType();
//         // if (container_dt == nullptr || dt == nullptr)
//         //   continue;
//         auto field_type_name = dbgutils::getSourceLevelVariableName(*dt);
//         std::string id = struct_type_name + field_type_name;
//         if (_SDA->isSharedStructType(id))
//           return true;
//       }
//     }
//   }
//   return false;
// }

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
    // find gep that has negative offset
    if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(&*inst_iter))
    {
      int gep_access_offset = pdgutils::getGEPAccessFieldOffset(*gep);
      if (gep_access_offset >= 0)
        continue;
      // check the next instruction
      // errs() << "container of location: " << F.getName() << "\n";
      if (EnableAnalysisStats)
        _ksplit_stats->_total_containerof++;
      Instruction *next_i = gep->getNextNonDebugInstruction();
      if (BitCastInst *bci = dyn_cast<BitCastInst>(next_i))
      {
        bool is_shared_type = false;
        std::string struct_type_name = "";
        Type *cast_type = bci->getType();
        if (cast_type->isPointerTy())
        {
          std::string str;
          llvm::raw_string_ostream(str) << *cast_type;
          auto strs = pdgutils::splitStr(str, ".");
          for (auto s : strs)
          {
            if (_SDA->isSharedStructType(s))
            {
              // is_shared_type = true;
              // struct_type_name = str;
              _ksplit_stats->_shared_containerof++;
            }
          }
        }

        // auto inst_node = _PDG->getNode(*bci);
        // if (inst_node != nullptr)
        // {
        //   if (is_shared_type)
        //   {
        //     if (!containerHasSharedFieldsAccessed(*bci, struct_type_name))
        //       continue;
        //     _container_of_insts.insert(bci);
        //     if (EnableAnalysisStats)
        //     {
        //       _ksplit_stats->_shared_containerof++;
        //       // if (DEBUG)
        //       //   errs() << "shared container_of: " << F.getName() << " - " << di_type_name << " - " << *bci << "\n";
        //     }
        //   }
        // }
      }
    }
  }
}

void pdg::DataAccessAnalysis::logSkbFieldStats(TreeNode &skb_root_node)
{
  Function *current_func = skb_root_node.getFunc();
  assert(current_func != nullptr && "cannot log skb without current function information\n");
  errs() << "logging skb stats in function: " << current_func->getName() << "\n";
  // log deep copy fields using debug info
  DIType *dt = skb_root_node.getDIType();
  unsigned num_deep_copy_fields = dbgutils::computeDeepCopyFields(*dt);
  errs() << "skb deep copy fields: " << num_deep_copy_fields << "\n";
  // Collect Filds related stats with bfs
  std::queue<TreeNode *> node_queue;
  // don't process the tree node, start with all the fields
  unsigned accessed_fields = 0;
  unsigned accessed_shared_fields = 0;
  for (auto child_node : skb_root_node.getChildNodes())
  {
    node_queue.push(child_node);
  }
  while (!node_queue.empty())
  {
    TreeNode *current_node = node_queue.front();
    node_queue.pop();
    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
    // accumulate stats for fields
    if (current_node->isStructMember())
    {
      if (!current_node->getAccessTags().empty())
      {
        accessed_fields++; // accumulate accessed fields
        auto field_id = pdgutils::computeTreeNodeID(*current_node);
        if (_SDA->isSharedFieldID(field_id))
          accessed_shared_fields++; // accumulate accessed shared fields
      }
    }
  }
  errs() << "skb accessed fields: " << accessed_fields << "\n";
  errs() << "skb shared accessed fields: " << accessed_shared_fields << "\n";
}

// void pdg::DataAccessAnalysis::printContainerOfStats()
// {
//   errs() << " ============== container of stats =============\n";
//   errs() << "num of container_of access shared states: " << _container_of_insts.size() << "\n";
//   for (auto i : _container_of_insts)
//   {
//     errs() << "container_of: " << i->getFunction()->getName() << " -- " << *i << "\n";
//   }
//   errs() << " ===============================================\n";
// }

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

bool pdg::DataAccessAnalysis::isUsedInBranchStat(Node &val_node)
{
  // check def-use edges to see if the value is used in any branchstatement
  // normally this step loads value
  auto def_use_neighbors = val_node.getOutNeighborsWithDepType(EdgeType::DATA_DEF_USE);
  for (auto out_neighbor : def_use_neighbors)
  {
    if (!out_neighbor->getValue())
      continue;
    // if (!isa<LoadInst>(out_neighbor->getValue()))
    //   continue;
    // get neighbors that can be reached in two hops, then decide whther this value is directly used in branch
    auto potential_branch_cand = out_neighbor->getOutNeighborsWithDepType(EdgeType::DATA_DEF_USE);
    for (auto n : potential_branch_cand)
    {
      auto val = n->getValue();
      if (!val)
        continue;
      if (isa<BranchInst>(val) || isa<BranchInst>(out_neighbor->getValue()))
        return true;
    }
  }
  return false;
}

static RegisterPass<pdg::DataAccessAnalysis>
    DAA("daa", "Data Access Analysis Pass", false, true);