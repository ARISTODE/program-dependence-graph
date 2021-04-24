#include "AtomicRegionAnalysis.hh"

char pdg::AtomicRegionAnalysis::ID = 0;

using namespace llvm;

void pdg::AtomicRegionAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<DataAccessAnalysis>();
  AU.setPreservesAll();
}

bool pdg::AtomicRegionAnalysis::runOnModule(Module &M)
{
  _DAA = &getAnalysis<DataAccessAnalysis>();
  _SDA = _DAA->getSDA();
  _sync_stub_file.open("cs_sync.idl");
  // _call_graph = &getAnalysis<CallGraphWrapperPass>().getCallGraph();
  _warning_cs_count = 0;
  _warning_atomic_op_count = 0;
  _cs_warning_count = 0;
  setupLockMap();
  computeBoundaryObjects(M);
  computeCriticalSections(M);
  computeAtomicOperations(M);
  computeWarningCS();
  computeWarningAtomicOps();

  _sync_stub_file << "syn_stub_kernel {\n";
  for (auto tree_pair : _sync_data_inst_tree_map)
  {
    Tree* tree = tree_pair.second;
    Instruction* cs_begin_inst = tree_pair.first;
    auto root_node = tree->getRootNode();
    auto di_type = root_node->getDIType();
    auto di_type_name = dbgutils::getSourceLevelTypeName(*di_type, true);
    while (!di_type_name.empty() && di_type_name.back() == '*')
    {
      di_type_name.pop_back();
    }

    std::string read_fields_ss;
    std::string write_fields_ss;
    raw_string_ostream read_proj_str(read_fields_ss);
    raw_string_ostream write_proj_str(write_fields_ss);
    generateSyncStubForTree(tree, read_proj_str, write_proj_str);
    // generate begin stub

    _sync_stub_file << "<============== rpc generate for func " << cs_begin_inst->getFunction()->getName().str() << "================>\n";
    _sync_stub_file << "\trpc shared_lock_begin( projection " << di_type_name << "* " << di_type_name << ") {\n";
    _sync_stub_file << read_proj_str.str();
    _sync_stub_file << "\t};\n";

    _sync_stub_file << "\trpc shared_lock_end( projection " << di_type_name << "* " << di_type_name << ") {\n";
    _sync_stub_file << write_proj_str.str();
    _sync_stub_file << "\t};\n";

  }
  _sync_stub_file << "}\n";
  _sync_stub_file.close();
  errs() << "CS Warning: " << _warning_cs_count << "/" << _critical_sections.size() << "\n";
  errs() << "Atomic Operations Warning: " << _warning_atomic_op_count << "/" << _atomic_operations.size() << "\n";
  return false;
}

void pdg::AtomicRegionAnalysis::setupLockMap()
{
  _lock_map.insert(std::make_pair("mutex_lock", "mutex_unlock"));
  _lock_map.insert(std::make_pair("_raw_spin_lock", "_raw_spin_unlock"));
  _lock_map.insert(std::make_pair("_raw_spin_lock_irq", "_raw_spin_unlock_irq"));
  _lock_map.insert(std::make_pair("rcu_read_lock", "rcu_read_unlock"));
}

void pdg::AtomicRegionAnalysis::computeBoundaryObjects(Module &M)
{
  // collect all the arguments passed across interface functions and global variables
  auto boundary_funcs = _SDA->getBoundaryFuncs();
  for (auto f : boundary_funcs)
  {
    if (f->isDeclaration() || f->empty())
      continue;
    // get the call sites of the boundary function
    // for (auto u : f->users())
    // {
    //   if (CallInst *ci = dyn_cast<CallInst>(u))
    //   {
    //     for (auto arg_iter = ci->arg_begin(); arg_iter != ci->arg_end(); arg_iter++)
    //     {
    //       _boundary_objects.insert(*arg_iter);
    //     }
    //   }
    //   // handle nested bit cast
    //   for (auto uu : u->users())
    //   {
    //     if (CallInst* ci = dyn_cast<CallInst>(uu))
    //     {
    //       for (auto arg_iter = ci->arg_begin(); arg_iter != ci->arg_end(); arg_iter++)
    //       {
    //         _boundary_objects.insert(*arg_iter);
    //       }
    //     }
    //   }
    // }

    for (auto &arg : f->args())
    {
      if (arg.getType()->isPointerTy())
        _boundary_ptrs.insert(&arg);
    }
  }

  // for (auto &global_var : M.getGlobalList())
  // {
  //   if (!global_var.getType()->isPointerTy())
  //     continue;
  //   _boundary_ptrs.insert(&global_var);
  // }
}

pdg::AtomicRegionAnalysis::CSMap pdg::AtomicRegionAnalysis::computeCSInFunc(Function &F)
{
  CSMap ret_cs_map;
  for (inst_iterator inst_iter = inst_begin(F); inst_iter != inst_end(F); inst_iter++)
  {
    // 1. find all lock instruction that call to acquire a lock
    if (!isLockInst(*inst_iter))
      continue;
    CallInst* lock_call_inst = cast<CallInst>(&*inst_iter);
    // 2. find reachable unlock insts
    std::vector<Instruction *> unlock_insts;
    for (auto tmp_inst_iter = inst_iter; tmp_inst_iter != inst_end(F); tmp_inst_iter++)
    {
      auto lock_inst_name = pdgutils::getCalledFunc(*lock_call_inst)->getName();
      if (isUnlockInst(*tmp_inst_iter, lock_inst_name))
        unlock_insts.push_back(&*tmp_inst_iter);
    }
    // 3. insert lock/unlock pair
    for (Instruction *unlock_inst : unlock_insts)
    {
      ret_cs_map.insert(std::make_pair(&*inst_iter, unlock_inst));
    }
  }

  return ret_cs_map;
}

void pdg::AtomicRegionAnalysis::computeCriticalSections(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    auto cs_in_func = computeCSInFunc(F); // find cs in each defined functions
    _critical_sections.insert(cs_in_func.begin(), cs_in_func.end());
  }
}

void pdg::AtomicRegionAnalysis::computeAtomicOperations(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); inst_iter++)
    {
      if (isAtomicOperation(*inst_iter))
        _atomic_operations.insert(&*inst_iter);
    }
  }
}

std::set<Instruction *> pdg::AtomicRegionAnalysis::computeInstsInCS(pdg::AtomicRegionAnalysis::CSPair cs_pair)
{
  Instruction *lock_inst = cs_pair.first;
  Instruction *unlock_inst = cs_pair.second;
  assert(lock_inst->getFunction() == unlock_inst->getFunction() && "error analyzing cs span for multiple functions");

  Function *f = lock_inst->getFunction();
  auto cs_begin_iter = inst_begin(f);
  while (&*cs_begin_iter != lock_inst)
    cs_begin_iter++;
  auto cs_end_iter = inst_begin(f);
  while (&*cs_end_iter != unlock_inst)
    cs_end_iter++;

  std::set<Instruction *> ret;
  cs_begin_iter++;
  if (cs_begin_iter == inst_end(f))
    return ret;

  while (cs_begin_iter != cs_end_iter)
  {
    ret.insert(&*cs_begin_iter);
    cs_begin_iter++;
  }
  return ret;
}

void pdg::AtomicRegionAnalysis::computeWarningCS()
{
  ProgramGraph *G = _SDA->getPDG();
  // PDGCallGraph &CG = PDGCallGraph::getInstance();

  for (auto cs_pair : _critical_sections)
  {
    bool cs_warning = false;
    auto insts_in_cs = computeInstsInCS(cs_pair);
    // errs() << "Critical Section found in func: " << cs_pair.first->getFunction()->getName() << "\n";
    for (auto inst : insts_in_cs)
    {
      std::set<std::string> modified_names;
      Value *accessed_val = nullptr;
      if (LoadInst *li = dyn_cast<LoadInst>(inst))
        accessed_val = li->getPointerOperand();
      if (StoreInst *st = dyn_cast<StoreInst>(inst))
        accessed_val = st->getPointerOperand();
      if (accessed_val == nullptr)
        continue;
      Node *accessed_node = G->getNode(*accessed_val);
      // obtianed the modified value (address)
      if (accessed_node == nullptr)
        continue;
      // computeModifedNames(*val_node, modified_names);
      // Function *f = si->getFunction();
      // scenerio 1: check if a modified value could be a pointer alias of boundary pointers
      auto alias_boundary_ptrs = computeBoundaryAliasPtrs(*accessed_val);
      if (!alias_boundary_ptrs.empty())
      {
        for (auto in_neighbor : accessed_node->getInNeighborsWithDepType(EdgeType::PARAMETER_IN))
        {
          TreeNode *formal_param_in_node = (TreeNode *)in_neighbor;
          formal_param_in_node->setAccessInAtomicRegion();
          if (_sync_data_inst_tree_map.find(cs_pair.first) == _sync_data_inst_tree_map.end())
            _sync_data_inst_tree_map.insert(std::make_pair(cs_pair.first, formal_param_in_node->getTree()));
        }
      }
      //   printWarningCS(cs_pair, *modified_val, *f, modified_names, "ALIAS");
      //   errs() << " ===================== ALIAS PTR ================\n";
      //   for (auto alias_ptr : alias_boundary_ptrs)
      //   {
      //     if (Argument *arg = dyn_cast<Argument>(alias_ptr))
      //     {
      //       Function *boundary_func = arg->getParent();
      //       errs() << boundary_func->getName() << ": " << arg->getArgNo() << " | " << *arg << "\n";
      //       auto n1 = CG.getNode(*boundary_func);
      //       auto n2 = CG.getNode(*f);
      //       if (!n1 || !n2)
      //         continue;
      //       // CG.printPaths(*n1, *n2);
      //     }
      //   }
      //   errs() << " ================================================\n";
      //   _cs_warning_count++;
      //   cs_warning = true;
      // }
      // scenerio 2: check if a modifed value matches shared states naming info
      // else
      // {
      // bool is_addr_var = false;
      // bool is_shared = false;
      // for (auto in_edge : val_node->getInEdgeSet())
      // {
      //   if (in_edge->getEdgeType() == EdgeType::VAL_DEP)
      //   {
      //     is_addr_var = true;
      //     TreeNode *tree_node = static_cast<TreeNode *>(in_edge->getSrcNode());
      //     if (_SDA->isSharedFieldID(pdgutils::computeTreeNodeID(*tree_node)))
      //       is_shared = true;
      //   }
      //   if (is_addr_var && is_shared)
      //     break;
      // }
      // if (!is_addr_var || !is_shared)
      //   continue;

      // printWarningCS(cs_pair, *modified_val, *f, modified_names, "TYPE");
      // _cs_warning_count++;
      cs_warning = true;
      // }
    }
    // compute the number of warning cs
    if (cs_warning)
      _warning_cs_count++;
  }
}

void pdg::AtomicRegionAnalysis::computeWarningAtomicOps()
{
  ProgramGraph *PDG = _SDA->getPDG();
  for (auto atomic_op : _atomic_operations)
  {
    auto modified_var = atomic_op->getOperand(0);
    Node *val_node = PDG->getNode(*modified_var);
    if (val_node == nullptr)
      continue;
    std::set<std::string> modified_names;
    computeModifedNames(*val_node, modified_names);
    if (modified_names.size() >= 2 && modified_names.find("counter") != modified_names.end())
      continue;

    // scenerio 1: check if the accessed var is alias of boundary pointers
    // auto alias_boundary_ptrs = computeBoundaryAliasPtrs(*modified_var);
    // if (!alias_boundary_ptrs.empty())
    // {
    //   _warning_atomic_op_count++;
    //   Instruction* modified_var_inst = cast<Instruction>(modified_var);
    //   printWarningAtomicOp(*modified_var_inst, modified_names, "ALIAS");
    // }
    // else
    // {
    // scenerio 2: check if the accessed var is a shared data
    bool is_shared = false;
    auto alias_nodes = val_node->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
    auto in_alias = val_node->getInNeighborsWithDepType(EdgeType::DATA_ALIAS);
    alias_nodes.insert(val_node);
    alias_nodes.insert(in_alias.begin(), in_alias.end());
    for (auto alias_node : alias_nodes)
    {
      errs() << "atomic warn: " << atomic_op->getFunction()->getName() << " - " << *alias_node->getValue() << "\n";
      for (auto in_edge : alias_node->getInEdgeSet())
      {
        if (in_edge->getEdgeType() != EdgeType::VAL_DEP)
          continue;
        TreeNode *tree_node = static_cast<TreeNode *>(in_edge->getSrcNode());
        // only consider struct field access cases
        if (!_SDA->isStructFieldNode(*tree_node))
          continue;
        auto field_id = pdgutils::computeTreeNodeID(*tree_node);
        if (_SDA->isSharedFieldID(field_id))
          is_shared = true;
        if (!tree_node->getDIType())
          continue;
      }


      if (is_shared)
      {
        auto func_name = atomic_op->getFunction()->getName().str();
        func_name = pdgutils::stripFuncNameVersionNumber(func_name);
        if (_processed_func_names.find(func_name) == _processed_func_names.end())
        {
          _processed_func_names.insert(func_name);
          _warning_atomic_op_count++;
          printWarningAtomicOp(*atomic_op, modified_names, "TYPE");
        }
        break;
      }
    }
    // }
  }
}

void pdg::AtomicRegionAnalysis::computeModifedNames(pdg::Node &node, std::set<std::string> &modified_names)
{
  if (node.getDIType() != nullptr)
    modified_names.insert(dbgutils::getSourceLevelVariableName(*node.getDIType()));
  auto alias_nodes = node.getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
  alias_nodes.insert(&node);
  for (auto alias_node : alias_nodes)
  {
    for (auto in_edge : alias_node->getInEdgeSet())
    {
      if (in_edge->getEdgeType() == EdgeType::VAL_DEP)
      {
        TreeNode *tree_node = static_cast<TreeNode *>(in_edge->getSrcNode());
        if (!tree_node->getDIType())
          continue;
        std::string field_id = pdgutils::computeTreeNodeID(*tree_node);
        modified_names.insert(field_id);
      }
    }
  }
}

bool pdg::AtomicRegionAnalysis::isLockInst(Instruction &i)
{
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    auto called_func = pdgutils::getCalledFunc(*ci);
    if (called_func == nullptr)
      return false;
    std::string lock_call_name = called_func->getName().str();
    lock_call_name = pdgutils::stripFuncNameVersionNumber(lock_call_name);
    if (_lock_map.find(lock_call_name) != _lock_map.end())
      return true;
  }
  return false;
}

bool pdg::AtomicRegionAnalysis::isUnlockInst(Instruction &i, std::string lock_inst_name)
{
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    auto called_func = pdgutils::getCalledFunc(*ci);
    if (called_func == nullptr)
      return false;
    std::string unlock_call_name = called_func->getName().str();
    unlock_call_name = pdgutils::stripFuncNameVersionNumber(unlock_call_name);
    if (_lock_map[lock_inst_name] == unlock_call_name)
      return true;
  }
  return false;
}

bool pdg::AtomicRegionAnalysis::isAtomicAsmString(std::string str)
{
  return (str.find("lock") != std::string::npos);
}

bool pdg::AtomicRegionAnalysis::isAtomicOperation(Instruction &i)
{
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    if (!ci->isInlineAsm())
      return false;
    if (InlineAsm *ia = dyn_cast<InlineAsm>(ci->getCalledOperand()))
    {
      auto asm_str = ia->getAsmString();
      if (isAtomicAsmString(asm_str))
        return true;
    }
  }
  return false;
}

bool pdg::AtomicRegionAnalysis::isAliasOfBoundaryPtrs(Value &v)
{
  PTAWrapper &ptaw = PTAWrapper::getInstance();
  for (auto b_ptr : _boundary_ptrs)
  {
    if (ptaw.queryAlias(v, *b_ptr) != NoAlias)
      return true;
  }
  return false;
}

std::set<Value *> pdg::AtomicRegionAnalysis::computeBoundaryAliasPtrs(llvm::Value &v)
{
  std::set<Value *> alias_ptrs;
  PTAWrapper &ptaw = PTAWrapper::getInstance();
  for (auto b_ptr : _boundary_ptrs)
  {
    if (ptaw.queryAlias(v, *b_ptr) != NoAlias)
      alias_ptrs.insert(b_ptr);
  }
  return alias_ptrs;
}

void pdg::AtomicRegionAnalysis::printWarningCS(pdg::AtomicRegionAnalysis::CSPair cs_pair, Value &v, Function &f, std::set<std::string> &modified_names, std::string source_type)
{
  errs() << " ============  CS Warning [ " << _cs_warning_count << " ] ============\n";
  errs() << "Function: " << f.getName() << "\n";
  errs() << "cs begin: " << *cs_pair.first << "\n";
  errs() << "cs end: " << *cs_pair.second << "\n";
  errs() << "modified var: " << v << "\n";
  for (auto field_name : modified_names)
  {
    errs() << "modified name: " << field_name << "\n";
  }
  errs() << source_type << "\n";
  errs() << " =====================================\n";
}

void pdg::AtomicRegionAnalysis::printWarningAtomicOp(llvm::Instruction &i, std::set<std::string> &modified_names, std::string source_type)
{
  Function *f = i.getFunction();
  errs() << " ============  Atomic Ops Warning [ " << _warning_atomic_op_count << " ] ============\n";
  errs() << "Function: " << f->getName() << "\n";
  errs() << "modified var: " << i << "\n";
  for (auto field_name : modified_names)
  {
    errs() << "modified name: " << field_name << "\n";
  }
  errs() << source_type << "\n";
  errs() << " =====================================\n";
}

void pdg::AtomicRegionAnalysis::dumpCS()
{
  errs() << "  ===================  CRITICAL SECTIONS  ==================\n";
  for (auto cs : _critical_sections)
  {
    auto lock_inst = cs.first;
    auto unlock_inst = cs.second;
    Function *f = lock_inst->getFunction();
    errs() << "Function: " << f->getName() << " || " << *lock_inst << " || " << *unlock_inst << "\n";
  }
}

void pdg::AtomicRegionAnalysis::dumpAtomicOps()
{
  errs() << "  ===================  ATOMIC OPERATIONS  ==================";
  for (auto atomic_op : _atomic_operations)
  {
    Function *f = atomic_op->getFunction();
    errs() << "Function: " << f->getName() << " || " << *atomic_op << "\n";
  }
}

void pdg::AtomicRegionAnalysis::generateSyncStubForTree(Tree *tree, raw_string_ostream &read_proj_str, raw_string_ostream &write_proj_str)
{
  if (!tree)
    return;
  TreeNode* root_node = tree->getRootNode();
  DIType *root_node_di_type = root_node->getDIType();
  DIType *root_node_lowest_di_type = dbgutils::getLowestDIType(*root_node_di_type);
  if (!root_node_lowest_di_type || !dbgutils::isProjectableType(*root_node_lowest_di_type))
    return;
  std::queue<TreeNode *> node_queue;
  // generate root projection
  node_queue.push(root_node);
  while (!node_queue.empty())
  {
    TreeNode *current_node = node_queue.front();
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

    // for pointer to aggregate type, retrive the child node(pointed object), and generate projection
    if (dbgutils::isPointerType(*dbgutils::stripMemberTag(*node_di_type)) && !current_node->getChildNodes().empty())
      current_node = current_node->getChildNodes()[0];
    // errs() << "generate idl for node: " << proj_type_name << "\n";

    std::string nested_read_fields_ss;
    std::string nested_write_fields_ss;
    raw_string_ostream nested_read_proj_str(nested_read_fields_ss);
    raw_string_ostream nested_write_proj_str(nested_write_fields_ss);
    generateSyncStubProjFromTreeNode(*current_node, nested_read_proj_str, nested_write_proj_str, node_queue, "\t\t\t");
    // handle funcptr ops struct specifically
    if (proj_var_name.empty())
      proj_var_name = proj_type_name;
    // concat ret preifx
    read_proj_str << "\t\tprojection_begin < struct "
                    << proj_type_name
                    << " > "
                    << proj_var_name
                    << " {\n"
                    << nested_read_proj_str.str()
                    << "\t\t}\n";

    write_proj_str << "\t\t\tprojection_end < struct "
                    << proj_type_name
                    << " > "
                    << proj_var_name
                    << " {\n"
                    << nested_write_proj_str.str()
                    << "\t\t}\n";
  }
}

void pdg::AtomicRegionAnalysis::generateSyncStubProjFromTreeNode(TreeNode &tree_node, raw_string_ostream &read_proj_str, raw_string_ostream &write_proj_str, std::queue<TreeNode *> &node_queue, std::string indent_level)
{
  DIType *node_di_type = tree_node.getDIType();
  assert(node_di_type != nullptr && "cannot generate IDL for node with null DIType\n");
  std::string root_di_type_name = dbgutils::getSourceLevelTypeName(*node_di_type);
  DIType *node_lowest_di_type = dbgutils::getLowestDIType(*node_di_type);
  if (!node_lowest_di_type || !dbgutils::isProjectableType(*node_lowest_di_type))
    return;
  // generate idl for each field
  for (auto child_node : tree_node.getChildNodes())
  {
    DIType *field_di_type = child_node->getDIType();
    auto field_var_name = dbgutils::getSourceLevelVariableName(*field_di_type);
    auto acc_tags = child_node->getAccessTags();
    // check for access tags, if none, no need to put this field in projection
    if (acc_tags.size() == 0 && !dbgutils::isFuncPointerType(*field_di_type))
      continue;
    // check for shared fields
    std::string field_id = pdgutils::computeTreeNodeID(*child_node);
    auto global_struct_di_type_names = _SDA->getGlobalStructDITypeNames();
    bool isGlobalStructField = (global_struct_di_type_names.find(root_di_type_name) != global_struct_di_type_names.end());

    bool is_sentinel_field = _SDA->isSentinelField(field_var_name);
    if (!_SDA->isSharedFieldID(field_id) && !dbgutils::isFuncPointerType(*field_di_type) && !isGlobalStructField && !is_sentinel_field)
      continue;

    auto field_type_name = dbgutils::getSourceLevelTypeName(*field_di_type, true);
    field_di_type = dbgutils::stripMemberTag(*field_di_type);
    // compute access attributes
    auto annotations =  _DAA->inferTreeNodeAnnotations(tree_node);
    std::string anno_str = "";
    for (auto anno : annotations)
      anno_str += anno;
    
    if (is_sentinel_field)
    {
      if (acc_tags.find(AccessTag::DATA_READ) != acc_tags.end())
        read_proj_str << indent_level << "array<" << field_type_name << ", "
                      << "null> " << field_var_name << ";\n";
      if (acc_tags.find(AccessTag::DATA_WRITE) != acc_tags.end())
        write_proj_str << indent_level << "array<" << field_type_name << ", "
                       << "null> " << field_var_name << ";\n";
      node_queue.push(child_node);
    }
    else if (dbgutils::isStructPointerType(*field_di_type))
    {

      if (acc_tags.find(AccessTag::DATA_READ) != acc_tags.end())
        read_proj_str << indent_level
                              << "projection "
                              << field_type_name
                              << (field_type_name.back() == '*' ? "*" : " ")
                              << " "
                              << field_var_name
                              << ";\n";
      if (acc_tags.find(AccessTag::DATA_WRITE) != acc_tags.end())
        write_proj_str << indent_level
                       << "projection "
                       << field_type_name
                       << (field_type_name.back() == '*' ? "*" : " ")
                       << " "
                       << field_var_name
                       << ";\n";
      node_queue.push(child_node);
    }
    else
    {
      if (acc_tags.find(AccessTag::DATA_READ) != acc_tags.end())
        read_proj_str << indent_level << field_type_name << " " << anno_str << " " << field_var_name << ";\n";
      if (acc_tags.find(AccessTag::DATA_WRITE) != acc_tags.end())
        write_proj_str << indent_level << field_type_name << " " << anno_str << " " << field_var_name << ";\n";
    }
  }
}

static RegisterPass<pdg::AtomicRegionAnalysis>
    AtomicRegionAnalysis("atomic-region", "Compute Atomic Regions", false, true);