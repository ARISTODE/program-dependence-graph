#include "AtomicRegionAnalysis.hh"

char pdg::AtomicRegionAnalysis::ID = 0;

using namespace llvm;

void pdg::AtomicRegionAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<SharedDataAnalysis>();
  AU.setPreservesAll();
}

bool pdg::AtomicRegionAnalysis::runOnModule(Module &M)
{
  _SDA = &getAnalysis<SharedDataAnalysis>();
  _warning_cs_count = 0;
  _warning_atomic_op_count = 0;
  _cs_warning_count = 0;
  setupLockMap();
  computeCriticalSections(M);
  computeAtomicOperations(M);
  // dumpCS();
  // dumpAtomicOps();
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
}

pdg::AtomicRegionAnalysis::CSMap pdg::AtomicRegionAnalysis::computeCSInFunc(Function &F)
{
  CSMap ret_cs_map;
  for (inst_iterator inst_iter = inst_begin(F); inst_iter != inst_end(F); inst_iter++)
  {
    // 1. find all lock instruction that call to acquire a lock
    if (!isLockInst(*inst_iter))
      continue;
    // 2. find reachable unlock insts
    std::vector<Instruction *> unlock_insts;
    for (auto tmp_inst_iter = inst_iter; tmp_inst_iter != inst_end(F); tmp_inst_iter++)
    {
      if (isUnlockInst(*tmp_inst_iter))
        unlock_insts.push_back(&*tmp_inst_iter);
    }
    // 3. insert lock/unlock pair
    for (Instruction *unlock_inst : unlock_insts)
    {
      _critical_sections.insert(std::make_pair(&*inst_iter, unlock_inst));
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
  Instruction* lock_inst = cs_pair.first;
  Instruction* unlock_inst = cs_pair.second;
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
  ProgramGraph* G = _SDA->getPDG();
  for (auto cs_pair : _critical_sections)
  {
    bool cs_warning = false;
    auto insts_in_cs = computeInstsInCS(cs_pair);
    for (auto inst : insts_in_cs)
    {
      std::set<std::string> modified_names;
      bool is_addr_var = false;
      bool is_shared = false;
      Node *inst_node = G->getNode(*inst);
      for (auto in_edge : inst_node->getInEdgeSet())
      {
        if (in_edge->getEdgeType() == EdgeType::VAL_DEP)
        {
          is_addr_var = true;
          TreeNode* tree_node = static_cast<TreeNode*>(in_edge->getSrcNode());
          if (_SDA->isSharedFieldID(pdgutils::computeTreeNodeID(*tree_node)))
            is_shared = true;
          if (!tree_node->getDIType())
            continue;
          modified_names.insert(dbgutils::getSourceLevelVariableName(*tree_node->getDIType()));
        }
        if (is_addr_var && is_shared)
          break;
      }
      if (!is_addr_var || !is_shared)
        continue;
      if (pdgutils::hasWriteAccess(*inst))
      {
        _cs_warning_count++;
        cs_warning = true;
        printWarningCS(cs_pair, *inst, modified_names);
      }
    }
    if(cs_warning)
      _warning_cs_count++;
  }
}

void pdg::AtomicRegionAnalysis::computeWarningAtomicOps()
{
  ProgramGraph* PDG = _SDA->getPDG();
  for (auto atomic_op : _atomic_operations)
  {
    auto modified_var = atomic_op->getOperand(0);
    Node* n = PDG->getNode(*modified_var);
    if (!n)
      continue;
    bool is_shared = false;
    std::set<std::string> modified_names;
    for (auto in_edge : n->getInEdgeSet())
    {
      if (in_edge->getEdgeType() != EdgeType::VAL_DEP)
        continue;
      TreeNode* tree_node = static_cast<TreeNode*>(in_edge->getSrcNode());
      if (_SDA->isSharedFieldID(pdgutils::computeTreeNodeID(*tree_node)))
        is_shared = true;
      if (!tree_node->getDIType())
        continue;
      modified_names.insert(dbgutils::getSourceLevelVariableName(*tree_node->getDIType()));
    }

    if (is_shared)
    {
      _warning_atomic_op_count++;
      printWarningAtomicOp(*atomic_op, modified_names);
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

bool pdg::AtomicRegionAnalysis::isUnlockInst(Instruction &i)
{
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    auto called_func = pdgutils::getCalledFunc(*ci);
    if (called_func == nullptr)
      return false;
    std::string unlock_call_name = called_func->getName().str();
    for (auto lock_iter = _lock_map.begin(); lock_iter != _lock_map.end(); lock_iter++)
    {
      if (lock_iter->second == unlock_call_name)
        return true;
    }
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

void pdg::AtomicRegionAnalysis::printWarningCS(pdg::AtomicRegionAnalysis::CSPair cs_pair, Instruction &i, std::set<std::string> &modified_names)
{
  auto lock_inst = cs_pair.first;
  Function* f = lock_inst->getFunction();
  errs() << " ============  CS Warning [ " << _warning_cs_count << " ] ============\n";
  errs() << "Function: " << f->getName() << "\n";
  errs() << "cs begin: " << *cs_pair.first << "\n";
  errs() << "cs end: " << *cs_pair.second << "\n";
  errs() << "modified var: " << i << "\n";
  for (auto field_name : modified_names)
  {
    errs() << "modified name: " << field_name << "\n";
  }
  errs() << " =====================================\n";
}

void pdg::AtomicRegionAnalysis::printWarningAtomicOp(llvm::Instruction &i, std::set<std::string> &modified_names)
{
  Function *f = i.getFunction();
  errs() << " ============  Atomic Ops Warning [ " << _warning_cs_count << " ] ============\n";
  errs() << "Function: " << f->getName() << "\n";
  errs() << "modified var: " << i << "\n";
  for (auto field_name : modified_names)
  {
    errs() << "modified name: " << field_name << "\n";
  }
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