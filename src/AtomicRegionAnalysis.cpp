#include "AtomicRegionAnalysis.hh"

char pdg::AtomicRegionAnalysis::ID = 0;

using namespace llvm;

void pdg::AtomicRegionAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<SharedDataAnalysis>();
  // AU.addRequired<CallGraphWrapperPass>();
  AU.setPreservesAll();
}

bool pdg::AtomicRegionAnalysis::runOnModule(Module &M)
{
  _SDA = &getAnalysis<SharedDataAnalysis>();
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
      if (!isa<StoreInst>(inst))
        continue;
      // obtianed the modified value (address)
      StoreInst *si = cast<StoreInst>(inst);
      auto modified_val = si->getPointerOperand();
      Node *val_node = G->getNode(*modified_val);
      if (val_node == nullptr)
        continue;
      computeModifedNames(*val_node, modified_names);
      Function *f = si->getFunction();
      // scenerio 1: check if a modified value could be a pointer alias of boundary pointers
      // auto alias_boundary_ptrs = computeBoundaryAliasPtrs(*modified_val);
      // if (!alias_boundary_ptrs.empty())
      // {
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
      bool is_addr_var = false;
      bool is_shared = false;
      for (auto in_edge : val_node->getInEdgeSet())
      {
        if (in_edge->getEdgeType() == EdgeType::VAL_DEP)
        {
          is_addr_var = true;
          TreeNode *tree_node = static_cast<TreeNode *>(in_edge->getSrcNode());
          if (_SDA->isSharedFieldID(pdgutils::computeTreeNodeID(*tree_node)))
            is_shared = true;
        }
        if (is_addr_var && is_shared)
          break;
      }
      if (!is_addr_var || !is_shared)
        continue;

      printWarningCS(cs_pair, *modified_val, *f, modified_names, "TYPE");
      _cs_warning_count++;
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
        if (processed_func_names.find(func_name) == processed_func_names.end())
        {
          processed_func_names.insert(func_name);
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

// bool pdg::AtomicRegionAnalysis::isAliasOfBoundaryPtrs(Value &v)
// {
//   PTAWrapper &ptaw = PTAWrapper::getInstance();
//   for (auto b_ptr : _boundary_ptrs)
//   {
//     if (ptaw.queryAlias(v, *b_ptr) != NoAlias)
//       return true;
//   }
//   return false;
// }

// std::set<Value *> pdg::AtomicRegionAnalysis::computeBoundaryAliasPtrs(llvm::Value &v)
// {
//   std::set<Value *> alias_ptrs;
//   PTAWrapper &ptaw = PTAWrapper::getInstance();
//   for (auto b_ptr : _boundary_ptrs)
//   {
//     if (ptaw.queryAlias(v, *b_ptr) != NoAlias)
//       alias_ptrs.insert(b_ptr);
//   }
//   return alias_ptrs;
// }

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

static RegisterPass<pdg::AtomicRegionAnalysis>
    AtomicRegionAnalysis("atomic-region", "Compute Atomic Regions", false, true);