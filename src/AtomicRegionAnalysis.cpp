#include "AtomicRegionAnalysis.hh"

char pdg::AtomicRegionAnalysis::ID = 0;

using namespace llvm;

void pdg::AtomicRegionAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.setPreservesAll();
}

bool pdg::AtomicRegionAnalysis::runOnModule(Module &M)
{
  setupLockMap();
  computeCriticalSections(M);
  computeAtomicOperations(M);
  dumpCS();
  dumpAtomicOps();
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