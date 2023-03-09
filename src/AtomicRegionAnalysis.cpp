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
  _ksplitStats = _DAA->getKSplitStats();
  _funcs_need_sync_stub_gen = _SDA->computeBoundaryTransitiveClosure();
  _callGraph = &PDGCallGraph::getInstance();

  _warning_cs_count = 0;
  _warning_atomic_op_count = 0;
  _cs_warning_count = 0;
  setupFenceNames();
  setupLockMap();
  setupLockInstanceMap();
  computeBoundaryObjects(M);
  computeCriticalSections(M);
  computeAtomicOperations(M);
  computeWarningCS();
  computeWarningAtomicOps();
  errs() << "CS Warning: " << _warning_cs_count << " / " << _critical_sections.size() << "\n";
  errs() << "Atomic Operations Warning: " << _warning_atomic_op_count << " / " << _atomic_operations.size() << "\n";
  return false;
}

void pdg::AtomicRegionAnalysis::generateSyncStubsForAtomicRegions()
{
  _sync_stub_file.open("kernel.idl", std::ios_base::app);
  _sync_stub_file << "// Atomic Regions Sync Stubs\n";
  // for critical sections
  for (auto tree_pair : _sync_data_inst_tree_map)
  {
    Tree *tree = tree_pair.second;
    Instruction *cs_begin_inst = tree_pair.first;
    std::string current_func_name = cs_begin_inst->getFunction()->getName().str();
    CallInst *lock_call_inst = cast<CallInst>(cs_begin_inst);
    std::string lock_call_name = pdgutils::getCalledFunc(*lock_call_inst)->getName();
    lock_call_name = pdgutils::stripFuncNameVersionNumber(lock_call_name);
    std::string unlock_call_name = _lock_map[lock_call_name];
    auto rootNode = tree->getRootNode();
    auto di_type = rootNode->getDIType();
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
    // _sync_stub_file << "<============== rpc generate for func " << cs_begin_inst->getFunction()->getName().str() << "================>\n";
    _sync_stub_file << "\trpc shared_lock_begin_" << lock_call_name << "_" << current_func_name << "( projection " << di_type_name << "* " << di_type_name << ") {\n";
    _sync_stub_file << read_proj_str.str();
    _sync_stub_file << "\t};\n";
    _sync_stub_file << "\trpc shared_lock_end_" << unlock_call_name << "_" << current_func_name << "( projection " << di_type_name << "* " << di_type_name << ") {\n";
    _sync_stub_file << write_proj_str.str();
    _sync_stub_file << "\t};\n";
  }
  // _sync_stub_file << "}\n";

  // atomic operations
  for (auto atomic_op : _warning_shared_atomic_ops)
  {
    /*
    1. generate lock/unlock
    2. generate 
    */

  }

  _sync_stub_file.close();
}

void pdg::AtomicRegionAnalysis::setupFenceNames()
{
  _fence_names.insert("mfence");
  _fence_names.insert("sfence");
}

void pdg::AtomicRegionAnalysis::setupLockMap()
{
  _lock_map.insert(std::make_pair("rtnl_lock", "rtnl_unlock"));
  _lock_map.insert(std::make_pair("mutex_lock", "mutex_unlock"));
  _lock_map.insert(std::make_pair("_raw_spin_lock", "_raw_spin_unlock"));
  _lock_map.insert(std::make_pair("_raw_spin_lock_irq", "_raw_spin_unlock_irq"));
  _lock_map.insert(std::make_pair("rcu_read_lock", "rcu_read_unlock"));
  _lock_map.insert(std::make_pair("rcu_read_lock_bh", "rcu_read_unlock_bh"));
  _lock_map.insert(std::make_pair("kfree_rcu", "kfree_rcu_end")); // this is dummy pair for rcu
  _lock_map.insert(std::make_pair("rcu_assign_pointer", "dummy"));
  _lock_map.insert(std::make_pair("read_seqcount_begin", "read_seqcount_retry"));
  _lock_map.insert(std::make_pair("write_seqcount_begin", "write_seqcount_end"));
}

void pdg::AtomicRegionAnalysis::setupLockInstanceMap()
{
  _lock_instance_map.insert("struct mutex");
  _lock_instance_map.insert("struct spinlock");
  _lock_instance_map.insert("spinlock_t");
}

void pdg::AtomicRegionAnalysis::computeBoundaryObjects(Module &M)
{
  // collect all the arguments passed across interface functions and global variables
  auto boundary_funcs = _SDA->getBoundaryFuncs();
  for (auto f : boundary_funcs)
  {
    if (f->isDeclaration() || f->empty())
      continue;
    auto func_w = _SDA->getPDG()->getFuncWrapper(*f);
    for (auto &arg : f->args())
    {
      if (arg.getType()->isPointerTy())
      {
        auto argTree = func_w->getArgFormalInTree(arg);
        if (!argTree)
          continue;
        auto rootNode = argTree->getRootNode();
        if (rootNode != nullptr)
          _boundary_arg_nodes.insert(rootNode);
      }
    }
  }

  for (auto &global_var : M.getGlobalList())
  {
    if (!global_var.getType()->isPointerTy())
      continue;
    auto global_root_node = _SDA->getPDG()->getNode(global_var);
    if (global_root_node != nullptr)
      _boundary_arg_nodes.insert(global_root_node);
  }
}

pdg::AtomicRegionAnalysis::CSMap pdg::AtomicRegionAnalysis::computeCSInFunc(Function &F)
{
  CSMap ret_cs_map;
  for (inst_iterator instIter = inst_begin(F); instIter != inst_end(F); instIter++)
  {
    // 1. find all lock instruction that call to acquire a lock
    if (!isLockInst(*instIter))
      continue;
    CallInst *lock_call_inst = cast<CallInst>(&*instIter);
    // 2. find reachable unlock insts
    std::vector<Instruction *> unlock_insts;
    for (auto tmp_inst_iter = instIter; tmp_inst_iter != inst_end(F); tmp_inst_iter++)
    {
      Function *called_func = pdgutils::getCalledFunc(*lock_call_inst);
      if (called_func == nullptr)
        continue;
      auto lock_inst_name = pdgutils::stripFuncNameVersionNumber(called_func->getName());
      if (isUnlockInst(*tmp_inst_iter, lock_inst_name))
        unlock_insts.push_back(&*tmp_inst_iter);
    }
    // 3. insert lock/unlock pair
    for (Instruction *unlock_inst : unlock_insts)
    {
      ret_cs_map.insert(std::make_pair(&*instIter, unlock_inst));
    }
  }

  return ret_cs_map;
}

void pdg::AtomicRegionAnalysis::computeCriticalSections(Module &M)
{
  for (auto F : _funcs_need_sync_stub_gen)
  {
    if (F->isDeclaration())
      continue;
    auto cs_in_func = computeCSInFunc(*F); // find cs in each defined functions
    _critical_sections.insert(cs_in_func.begin(), cs_in_func.end());
    if (EnableAnalysisStats)
    {
      for (auto cs : cs_in_func)
      {
        // _ksplitStats->increaseTotalCS();
        _ksplitStats->_total_CS += 1;
        auto cs_lock_inst = cast<CallInst>(cs.first);
        if (isRcuLockInst(*cs_lock_inst))
          _ksplitStats->_total_rcu += 1;
        if (isSeqLockInst(*cs_lock_inst))
          _ksplitStats->_total_seqlock += 1;
      }
    }
  }
}

void pdg::AtomicRegionAnalysis::computeAtomicOperations(Module &M)
{
  for (auto F : _funcs_need_sync_stub_gen)
  {
    if (F->isDeclaration())
      continue;
    for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
    {
      if (isAtomicOperation(*instIter))
      {
        _atomic_operations.insert(&*instIter);
        if (EnableAnalysisStats)
          _ksplitStats->_total_atomic_op += 1;
        // _ksplitStats->increaseTotalAtomicOps();
      }
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
  {
    cs_end_iter++;
  }

  std::set<Instruction *> ret;
  cs_begin_iter++;
  if (cs_begin_iter == inst_end(f))
    return ret;
  // search for call inst, inspect all the instructions in the
  // callee
  while (cs_begin_iter != cs_end_iter)
  {
    if (CallInst *ci = dyn_cast<CallInst>(&*cs_begin_iter))
    {
      auto called_func = pdgutils::getCalledFunc(*ci);
      if (called_func != nullptr && !called_func->isDeclaration())
      {
        for (auto it = inst_begin(called_func); it != inst_end(called_func); ++it)
        {
          ret.insert(&*it);
        }
      }
    }
    ret.insert(&*cs_begin_iter);
    cs_begin_iter++;
  }
  return ret;
}

bool pdg::AtomicRegionAnalysis::isRcuLock(CallInst &lock_call_inst)
{
  auto called_func = pdgutils::getCalledFunc(lock_call_inst);
  if (called_func == nullptr)
    return false;
  auto funcName = pdgutils::stripFuncNameVersionNumber(called_func->getName().str());
  if (funcName == "rcu_read_lock")
    return true;
  return false;
}

void pdg::AtomicRegionAnalysis::computeWarningCS()
{
  ProgramGraph *G = _SDA->getPDG();
  // PDGCallGraph &CG = PDGCallGraph::getInstance();
  for (auto cs_pair : _critical_sections)
  {
    bool cs_warning = false;
    bool has_nested_lock = false;
    bool is_shared_lock = false;
    auto lock_inst = cs_pair.first;
    // collect instructions in critical sections
    auto insts_in_cs = computeInstsInCS(cs_pair);
    _insts_in_CS.insert(insts_in_cs.begin(), insts_in_cs.end());

    if (!isa<CallInst>(lock_inst))
      continue;
    Function *cur_func = lock_inst->getFunction();
    // if (!_SDA->isDriverFunc(*cur_func))
    //   continue;
    CallInst *lock_call_inst = cast<CallInst>(lock_inst);
    auto used_lock = getUsedLock(*lock_call_inst);
    // identify shared rcu lock
    if (isRcuLock(*lock_call_inst))
    {
      // find rcu_dereference call
      auto rcu_dereference_inst = findRcuDereferenceInst(insts_in_cs);
      if (!rcu_dereference_inst)
        continue;
      // if rcu_dereference is found
      auto dereferenced_object = rcu_dereference_inst->getOperand(0);
      assert(dereferenced_object != nullptr && "cannot find rcu shared lock on null object! \n");
      auto object_node = _SDA->getPDG()->getNode(*dereferenced_object);
      if (object_node != nullptr)
      {
        DIType *dt = object_node->getDIType();
        if (dt != nullptr)
        {
          auto type_name = dbgutils::getSourceLevelTypeName(*dt);
          if (_SDA->isSharedStructType(type_name))
            is_shared_lock = true;
          // TODO: need to find write sync stub at the other side for the same type
        }
      }
    }
    // we aim to handle spin_lock and mutex_lock correctly for now
    else
    {
      // empty lock instance
      if (used_lock == nullptr)
      {
        errs() << "[Warning]: potential shared lock - " << cur_func->getName() << " - " << *lock_call_inst << "\n";
        if (isRtnlLockInst(*lock_call_inst))
          is_shared_lock = true;
      }
      else
      {
        auto used_lock_node = G->getNode(*used_lock);
        if (used_lock_node == nullptr)
          continue;
        std::set<EdgeType> edgeTypes;
        edgeTypes.insert(EdgeType::DATA_ALIAS);
        auto lock_node_alias = used_lock_node->getNeighborsWithDepType(edgeTypes);
        for (auto aliasNode : lock_node_alias)
        {
          if (aliasNode->isAddrVarNode())
          {
            TreeNode *abstract_treeNode = (TreeNode *)aliasNode->getAbstractTreeNode();
            auto fieldId = pdgutils::computeTreeNodeID(*abstract_treeNode);
            if (_SDA->isSharedFieldID(fieldId) && isKernelLockInstance(fieldId))
            {
              is_shared_lock = true;
              break;
            }
          }
        }
      }
    }

    if (!is_shared_lock)
      continue;
    // speicial handle for kfree_rcu. No need to handle this, only need to identify where
    // it is used.
    if (isKfreeRcuInst(*lock_call_inst))
      continue;

    for (auto inst : insts_in_cs)
    {
      bool inst_access_shared_state = false;
      // detect nested lock here
      if (EnableAnalysisStats)
      {
        if (isLockInst(*inst))
        {
          _ksplitStats->_total_nest_lock += 1;
          has_nested_lock = true;
        }
      }

      // std::set<std::string> modified_names;
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

      // if shared fields is accessed
      if (accessed_node->isAddrVarNode())
      {
        TreeNode *abstract_treeNode = (TreeNode *)accessed_node->getAbstractTreeNode();
        auto fieldId = pdgutils::computeTreeNodeID(*abstract_treeNode);
        if (_SDA->isSharedFieldID(fieldId))
        {
          cs_warning = true;
          inst_access_shared_state = true;
        }
      }
      else
      {
        // check if shared struct type is accessed
        auto dt = accessed_node->getDIType();
        if (dt != nullptr)
        {
          auto type_name = dbgutils::getSourceLevelTypeName(*dt);
          if (_SDA->isSharedStructType(type_name))
          {
            cs_warning = true;
            inst_access_shared_state = true;
          }
        }
      }

      // check if a modified value could be a pointer alias of boundary pointers
      // auto has_boundary_alias = hasBoundaryAliasNodes(*accessed_val);
      if (inst_access_shared_state)
      {
        for (auto in_neighbor : accessed_node->getInNeighborsWithDepType(EdgeType::PARAMETER_IN))
        {
          TreeNode *formal_param_in_node = (TreeNode *)in_neighbor;
          formal_param_in_node->setAccessInAtomicRegion();
          if (_sync_data_inst_tree_map.find(cs_pair.first) == _sync_data_inst_tree_map.end())
            _sync_data_inst_tree_map.insert(std::make_pair(cs_pair.first, formal_param_in_node->getTree()));
        }
      }
    }
    // compute number of warning cs
    if (EnableAnalysisStats)
    {
      if (cs_warning)
      {
        _warning_cs_count++;
        // _ksplitStats->increaseSharedCS();
        _ksplitStats->_shared_CS += 1;
        if (isRcuLockInst(*cs_pair.first))
        {
          _ksplitStats->_shared_rcu += 1;
        }
        if (isSeqLockInst(*cs_pair.first))
        {
          _ksplitStats->_shared_seqlock += 1;
        }
        if (has_nested_lock)
        {
          _ksplitStats->_shared_nest_lock += 1;
          // errs() << "nested lock: " << lock_inst->getFunction()->getName() << "\n";
        }
      }
    }
  }
}

void pdg::AtomicRegionAnalysis::computeWarningAtomicOps()
{
  ProgramGraph *PDG = _SDA->getPDG();
  for (auto atomic_op : _atomic_operations)
  {
    auto modified_var = atomic_op->getOperand(0);
    Node *valNode = PDG->getNode(*modified_var);
    if (valNode == nullptr)
      continue;
    std::set<std::string> modified_names;
    computeModifedNames(*valNode, modified_names);
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
    std::string parentStructTypeName;
    std::string modified_field_name;
    bool isShared = false;
    auto aliasNodes = valNode->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
    auto in_alias = valNode->getInNeighborsWithDepType(EdgeType::DATA_ALIAS);
    aliasNodes.insert(valNode);
    aliasNodes.insert(in_alias.begin(), in_alias.end());
    for (auto aliasNode : aliasNodes)
    {
      // errs() << "atomic warn: " << atomic_op->getFunction()->getName() << " - " << *aliasNode->getValue() << "\n";
      // check in edges and see if it is addr variable
      for (auto in_edge : aliasNode->getInEdgeSet())
      {
        if (in_edge->getEdgeType() != EdgeType::VAL_DEP)
          continue;
        TreeNode *treeNode = static_cast<TreeNode *>(in_edge->getSrcNode());
        // only consider struct field access cases
        if (!treeNode->isStructMember())
          continue;
        auto fieldId = pdgutils::computeTreeNodeID(*treeNode);
        if (_SDA->isSharedFieldID(fieldId))
        {
          isShared = true;
          break;
        }
      }

      if (isShared)
      {
        auto funcName = atomic_op->getFunction()->getName().str();
        funcName = pdgutils::stripFuncNameVersionNumber(funcName);
        // if (_processed_func_names.find(funcName) == _processed_func_names.end())
        // {
        //   _processed_func_names.insert(funcName);
        _warning_atomic_op_count++;

        if (DEBUG)
        {
          printWarningAtomicOp(*atomic_op, modified_names, "TYPE");
          // auto dst_func_node = _callGraph->getNode(*atomic_op->getFunction());
          // for (auto boundary_f : _SDA->getBoundaryFuncs())
          // {
          //   auto boundary_func_node = _callGraph->getNode(*boundary_f);
          //   _callGraph->printPaths(*boundary_func_node, *dst_func_node);
          // }
        }

        // if (EnableAnalysisStats)
        // {
        //   _ksplitStats->_shared_atomic_op += 1;
        //   errs() << "shared atomic op: " << atomic_op->getFunction()->getName() << " - " << *atomic_op << "\n";
        //   for (auto name : modified_names)
        //   {
        //     errs() << "\t op name: " << name << "\n";
        //   }
        //   _warning_shared_atomic_ops.insert(atomic_op);
        // }
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
  auto aliasNodes = node.getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
  aliasNodes.insert(&node);
  for (auto aliasNode : aliasNodes)
  {
    for (auto in_edge : aliasNode->getInEdgeSet())
    {
      if (in_edge->getEdgeType() == EdgeType::VAL_DEP) // check if connected with shared filed
      {
        TreeNode *treeNode = static_cast<TreeNode *>(in_edge->getSrcNode());
        if (!treeNode->getDIType())
          continue;
        std::string fieldId = pdgutils::computeTreeNodeID(*treeNode);
        modified_names.insert(fieldId);
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

bool pdg::AtomicRegionAnalysis::isRcuLockInst(Instruction &i)
{
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    auto called_func = pdgutils::getCalledFunc(*ci);
    if (called_func == nullptr)
      return false;
    std::string lock_call_name = called_func->getName().str();
    lock_call_name = pdgutils::stripFuncNameVersionNumber(lock_call_name);
    if (lock_call_name == "rcu_read_lock")
      return true;
  }
  return false;
}

bool pdg::AtomicRegionAnalysis::isKfreeRcuInst(Instruction &i)
{
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    auto called_func = pdgutils::getCalledFunc(*ci);
    if (called_func == nullptr)
      return false;
    std::string lock_call_name = called_func->getName().str();
    lock_call_name = pdgutils::stripFuncNameVersionNumber(lock_call_name);
    if (lock_call_name == "kfree_rcu")
      return true;
  }
  return false;
}

bool pdg::AtomicRegionAnalysis::isRtnlLockInst(Instruction &i)
{
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    auto called_func = pdgutils::getCalledFunc(*ci);
    if (called_func == nullptr)
      return false;
    std::string lock_call_name = called_func->getName().str();
    lock_call_name = pdgutils::stripFuncNameVersionNumber(lock_call_name);
    if (lock_call_name == "rtnl_lock")
      return true;
  }
  return false;
}

bool pdg::AtomicRegionAnalysis::isSeqLockInst(Instruction &i)
{
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    auto called_func = pdgutils::getCalledFunc(*ci);
    if (called_func == nullptr)
      return false;
    std::string lock_call_name = called_func->getName().str();
    lock_call_name = pdgutils::stripFuncNameVersionNumber(lock_call_name);
    if (lock_call_name == "read_seqcount_begin" || lock_call_name == "write_seqcount_begin")
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

bool pdg::AtomicRegionAnalysis::isAtomicFenceString(std::string str)
{
  return (_fence_names.find(str) != _fence_names.end());
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
      if (isAtomicFenceString(asm_str))
        _ksplitStats->_total_barrier += 1;
      // _ksplitStats->increaseTotalBarrier();
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

bool pdg::AtomicRegionAnalysis::isKernelLockInstance(std::string fieldId)
{
  return (_lock_instance_map.find(fieldId) != _lock_instance_map.end());
}

bool pdg::AtomicRegionAnalysis::hasBoundaryAliasNodes(llvm::Value &v)
{
  std::set<Node *> ret;
  auto PDG = _SDA->getPDG();
  auto valNode = PDG->getNode(v);
  if (valNode == nullptr)
    return false;
  std::set<EdgeType> edgeTypes = {
      EdgeType::DATA_ALIAS,
      EdgeType::PARAMETER_IN};
  for (auto n : _boundary_arg_nodes)
  {
    if (PDG->canReach(*n, *valNode, edgeTypes))
      return true;
  }
  return false;
}

void pdg::AtomicRegionAnalysis::printWarningCS(pdg::AtomicRegionAnalysis::CSPair cs_pair, Value &v, Function &f, std::set<std::string> &modified_names, std::string source_type)
{
  errs() << " ============  CS Warning [ " << _cs_warning_count << " ] ============\n";
  errs() << "Function: " << f.getName() << "\n";
  errs() << "cs begin: " << *cs_pair.first << "\n";
  errs() << "cs end: " << *cs_pair.second << "\n";
  errs() << "modified var: " << v << "\n";
  for (auto fieldName : modified_names)
  {
    errs() << "modified name: " << fieldName << "\n";
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
  for (auto fieldName : modified_names)
  {
    errs() << "modified name: " << fieldName << "\n";
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
  TreeNode *rootNode = tree->getRootNode();
  DIType *rootNodeDt = rootNode->getDIType();
  DIType *rootNodeLowestDt = dbgutils::getLowestDIType(*rootNodeDt);
  if (!rootNodeLowestDt || !dbgutils::isProjectableType(*rootNodeLowestDt))
    return;
  std::queue<TreeNode *> nodeQueue;
  // generate root projection
  nodeQueue.push(rootNode);
  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    DIType *nodeDt = currentNode->getDIType();
    DIType *nodeLowestDt = dbgutils::getLowestDIType(*nodeDt);
    // check if node needs projection
    if (!nodeLowestDt || !dbgutils::isProjectableType(*nodeLowestDt))
      continue;
    // get the type / variable name for the pointer field
    auto projTyName = dbgutils::getSourceLevelTypeName(*nodeDt, true);
    while (projTyName.back() == '*')
    {
      projTyName.pop_back();
    }
    auto projVarName = dbgutils::getSourceLevelVariableName(*nodeDt);
    if (currentNode->isRootNode())
    {
      if (currentNode->getDILocalVar() != nullptr)
        projVarName = dbgutils::getSourceLevelVariableName(*currentNode->getDILocalVar());
    }

    // for pointer to aggregate type, retrive the child node(pointed object), and generate projection
    if (dbgutils::isPointerType(*dbgutils::stripMemberTag(*nodeDt)) && !currentNode->getChildNodes().empty())
      currentNode = currentNode->getChildNodes()[0];
    // errs() << "generate idl for node: " << projTyName << "\n";

    std::string nested_read_fields_ss;
    std::string nested_write_fields_ss;
    raw_string_ostream nested_read_proj_str(nested_read_fields_ss);
    raw_string_ostream nested_write_proj_str(nested_write_fields_ss);
    generateSyncStubProjFromTreeNode(*currentNode, nested_read_proj_str, nested_write_proj_str, nodeQueue, "\t\t\t");
    // handle funcptr ops struct specifically
    if (projVarName.empty())
      projVarName = projTyName;
    // concat ret preifx
    read_proj_str << "\t\tprojection_begin < struct "
                  << projTyName
                  << " > "
                  << projVarName
                  << " {\n"
                  << nested_read_proj_str.str()
                  << "\t\t}\n";

    write_proj_str << "\t\t\tprojection_end < struct "
                   << projTyName
                   << " > "
                   << projVarName
                   << " {\n"
                   << nested_write_proj_str.str()
                   << "\t\t}\n";
  }
}

void pdg::AtomicRegionAnalysis::generateSyncStubProjFromTreeNode(TreeNode &treeNode, raw_string_ostream &read_proj_str, raw_string_ostream &write_proj_str, std::queue<TreeNode *> &nodeQueue, std::string indentLevel)
{
  DIType *nodeDt = treeNode.getDIType();
  assert(nodeDt != nullptr && "cannot generate IDL for node with null DIType\n");
  std::string root_di_type_name = dbgutils::getSourceLevelTypeName(*nodeDt);
  std::string root_di_type_name_raw = dbgutils::getSourceLevelTypeName(*nodeDt, true);
  DIType *nodeLowestDt = dbgutils::getLowestDIType(*nodeDt);
  if (!nodeLowestDt || !dbgutils::isProjectableType(*nodeLowestDt))
    return;
  // generate idl for each field
  for (auto childNode : treeNode.getChildNodes())
  {
    DIType *field_di_type = childNode->getDIType();
    auto field_var_name = dbgutils::getSourceLevelVariableName(*field_di_type);
    auto acc_tags = childNode->getAccessTags();
    // check for access tags, if none, no need to put this field in projection
    if (acc_tags.size() == 0 && !dbgutils::isFuncPointerType(*field_di_type))
      continue;
    // check for shared fields
    std::string fieldId = pdgutils::computeTreeNodeID(*childNode);
    auto global_struct_di_type_names = _SDA->getGlobalStructDITypeNames();
    bool isGlobalStructField = (global_struct_di_type_names.find(root_di_type_name) != global_struct_di_type_names.end());

    bool is_sentinel_field = _SDA->isSentinelField(field_var_name);
    if (!_SDA->isSharedFieldID(fieldId) && !dbgutils::isFuncPointerType(*field_di_type) && !isGlobalStructField && !is_sentinel_field)
      continue;

    if (!treeNode.isAccessedInAtomicRegion())
      continue;

    auto field_type_name = dbgutils::getSourceLevelTypeName(*field_di_type, true);
    field_di_type = dbgutils::stripMemberTag(*field_di_type);
    // compute access attributes
    auto annotations = _DAA->inferTreeNodeAnnotations(treeNode);
    std::string annoStr = "";
    for (auto anno : annotations)
      annoStr += anno;

    if (is_sentinel_field)
    {
      if (acc_tags.find(AccessTag::DATA_READ) != acc_tags.end())
        read_proj_str << indentLevel << "array<" << field_type_name << ", "
                      << "null> " << field_var_name << ";\n";
      if (acc_tags.find(AccessTag::DATA_WRITE) != acc_tags.end())
        write_proj_str << indentLevel << "array<" << field_type_name << ", "
                       << "null> " << field_var_name << ";\n";
      nodeQueue.push(childNode);
    }
    else if (dbgutils::isStructPointerType(*field_di_type))
    {

      if (acc_tags.find(AccessTag::DATA_READ) != acc_tags.end())
        read_proj_str << indentLevel
                      << "projection "
                      << field_type_name
                      << (field_type_name.back() == '*' ? "*" : " ")
                      << " "
                      << field_var_name
                      << ";\n";
      if (acc_tags.find(AccessTag::DATA_WRITE) != acc_tags.end())
        write_proj_str << indentLevel
                       << "projection "
                       << field_type_name
                       << (field_type_name.back() == '*' ? "*" : " ")
                       << " "
                       << field_var_name
                       << ";\n";
      nodeQueue.push(childNode);
    }
    else if (dbgutils::isFuncPointerType(*field_di_type))
    {
      std::string funcPtrName = field_var_name;
      if (acc_tags.find(AccessTag::DATA_READ) != acc_tags.end())
        // TODO: correct format later
        read_proj_str << indentLevel << "rpc_ptr " << funcPtrName << " " << field_var_name << ";\n";
      if (acc_tags.find(AccessTag::DATA_WRITE) != acc_tags.end())
        write_proj_str << indentLevel << "rpc_ptr " << funcPtrName << " " << field_var_name << ";\n";
    }
    else
    {
      if (acc_tags.find(AccessTag::DATA_READ) != acc_tags.end())
        read_proj_str << indentLevel << field_type_name << " " << annoStr << " " << field_var_name << ";\n";
      if (acc_tags.find(AccessTag::DATA_WRITE) != acc_tags.end())
        write_proj_str << indentLevel << field_type_name << " " << annoStr << " " << field_var_name << ";\n";
    }
  }
}

// std::set<pdg::Node*> pdg::AtomicRegionAnalysis::findNextCheckpoints(std::set<Instruction *> &checkpoints, Instruction &cur_inst)
// {
//   auto cur_inst_cfg_node = _ksplit_cfg->getNode(cur_inst);
//   bool is_lock_inst = false;
//   // if current inst is lock inst, search for unlock instruction
//   if (CallInst *ci = dyn_cast<CallInst>(&cur_inst))
//   {
//     auto called_func = pdgutils::getCalledFunc(*ci);
//     if (called_func != nullptr && called_func->isDeclaration())
//     {
//       std::string calleeName = pdgutils::stripFuncNameVersionNumber(called_func->getName().str());
//       if (_lock_map.find(calleeName) != _lock_map.end())
//       {
//         is_lock_inst = true;
//         auto unlock_inst_name = _lock_map[calleeName];
//         return _ksplit_cfg->searchCallNodes(*cur_inst_cfg_node, unlock_inst_name);
//       }
//     }
//   }
//   // otherwise, search for lock instruction
//   else
//   {
//     // TODO: use spin_lock for test right now.
//     return _ksplit_cfg->searchCallNodes(*cur_inst_cfg_node, "spin_lock");
//   }
// }

// // the idea is to find a shared state update outside of critical region.
// void pdg::AtomicRegionAnalysis::printCodeRegionsUpdateSharedStates(Module &M)
// {
//   ProgramGraph *PDG = _SDA->getPDG();
//   // scan through all the instructions and find the shared state update outside of critical region
//   for (auto &F : M)
//   {
//     if (F.isDeclaration())
//       continue;
//     for (auto instIter = inst_begin(F); instIter != inst_end(F); ++instIter)
//     {
//       if (_insts_in_CS.find(&*instIter) != _insts_in_CS.end())
//         continue;
//       auto node = PDG->getNode(*instIter);
//       assert(node != nullptr && "printCodeRegionsUpdateSharedStates cannot get instruction node\n");
//       if (!pdgutils::hasWriteAccess(*instIter))
//         continue;
//       for (auto in_edge : node->getInEdgeSet())
//       {
//         // check if this instruction corresponds to a type tree node
//         if (in_edge->getEdgeType() == EdgeType::VAL_DEP)
//         {
//           auto in_neighbor = in_edge->getSrcNode();
//           TreeNode* tn = (TreeNode*)in_neighbor;
//           if (!tn->isStructMember())
//             continue;
//           if (_SDA->isTreeNodeShared(*tn))
//             errs() << "Find shared field update outside critical section: " << F.getName() << " - " << pdgutils::computeTreeNodeID(*tn) << "\n";
//         }
//       }
//     }
//   }
// }

llvm::Value *pdg::AtomicRegionAnalysis::getUsedLock(CallInst &lock_inst)
{
  // we only consider lock instructions that take a lock instance as argument
  if (lock_inst.getNumArgOperands() == 0)
    return nullptr;
  // use pattern on IR to track down the lock (O0 optimization level)
  if (auto used_lock_cast_inst = dyn_cast<BitCastInst>(lock_inst.getOperand(0)))
  {
    auto used_lock = used_lock_cast_inst->getOperand(0);
    if (auto gep = dyn_cast<GetElementPtrInst>(used_lock))
    {
      if (auto li = dyn_cast<LoadInst>(gep->getPointerOperand()))
        return li;
    }
  }
  else
    return lock_inst.getOperand(0);
  return nullptr;
}

Instruction *pdg::AtomicRegionAnalysis::findRcuDereferenceInst(std::set<Instruction *> insts_in_cs)
{
  for (auto inst : insts_in_cs)
  {
    if (CallInst *ci = dyn_cast<CallInst>(inst))
    {
      auto called_func = pdgutils::getCalledFunc(*ci);
      if (called_func == nullptr)
        continue;
      std::string calleeName = pdgutils::getSourceFuncName(called_func->getName().str());
      if (calleeName == "rcu_dereference_lvds")
        return ci;
    }
  }
  return nullptr;
}

static RegisterPass<pdg::AtomicRegionAnalysis>
    AtomicRegionAnalysis("atomic-region", "Compute Atomic Regions", false, true);
