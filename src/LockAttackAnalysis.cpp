#include "LockAttackAnalysis.hh"
#include "llvm/Analysis/LoopInfo.h"


char pdg::LockAttackAnalysis::ID = 0;
using namespace llvm;

void pdg::LockAttackAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<SharedDataAnalysis>();
  AU.setPreservesAll();
}

bool pdg::LockAttackAnalysis::runOnModule(Module &M)
{
  _module = &M;
  _SDA = &getAnalysis<SharedDataAnalysis>();
  _PDG = _SDA->getPDG();
  _callGraph = &PDGCallGraph::getInstance();
  _CFG = &KSplitCFG::getInstance();
  if (!_CFG->isBuild())
    _CFG->build(*_module);

  setupLockMap();
  CallInstSet lockCallSites;
  computeLockCallSites(lockCallSites);

  // finding atk1 -> unpaired locks
  // auto unpairedLockCS = computeUnpairedLockCallSites(lockCallSites);

  // find atk2 -> locks under conditions
  computeLockCallSiteUnderConditions(lockCallSites);

  // find atk3 -> loop within CS
  computeCSLoop(lockCallSites);

  // protocol violation detection
  computeKernelInterfaceFuncCSUnderCondition();
  computeDrvCallBackCallSite();
  return false;
}

void pdg::LockAttackAnalysis::setupLockMap()
{
  _lockMap.insert(std::make_pair("rtnl_lock", "rtnl_unlock"));
  // _lockMap.insert(std::make_pair("mutex_lock", "mutex_unlock"));
  // _lockMap.insert(std::make_pair("_raw_spin_lock", "_raw_spin_unlock"));
  // _lockMap.insert(std::make_pair("_raw_spin_lock_irq", "_raw_spin_unlock_irq"));
  _lockMap.insert(std::make_pair("_raw_spin_lock_irqsave", "_raw_spin_unlock_irqrestore"));
  // _lockMap.insert(std::make_pair("_raw_read_lock_irqsave", "_raw_read_unlock_irq"));
  // _lockMap.insert(std::make_pair("_raw_write_lock_irqsave", "_raw_write_unlock_irq"));
  // _lockMap.insert(std::make_pair("local_irq_enable", "local_irq_restore"));
}

void pdg::LockAttackAnalysis::computeLockCallSites(pdg::LockAttackAnalysis::CallInstSet &lockCallSites)
{
  for (auto iter : _lockMap)
  {
    auto lockName = iter.first;
    Function *lockFunc = _module->getFunction(StringRef(lockName));
    if (!lockFunc)
      continue;

    auto boundaryTransFuncs = _SDA->computeBoundaryTransitiveClosure();
    auto callSites = _callGraph->getFunctionCallSites(*lockFunc);
    for (auto callSite : callSites)
    {
      auto func = callSite->getFunction();
      if (boundaryTransFuncs.find(func) == boundaryTransFuncs.end() && !_SDA->isDriverFunc(*func))
        continue;
      lockCallSites.insert(callSite);
    }
  }
}

bool pdg::LockAttackAnalysis::isLockInst(Instruction &i)
{
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    auto calledFunc = pdgutils::getCalledFunc(*ci);
    if (calledFunc == nullptr)
      return false;
    std::string lockCallName = calledFunc->getName().str();
    lockCallName = pdgutils::stripFuncNameVersionNumber(lockCallName);
    if (_lockMap.find(lockCallName) != _lockMap.end())
      return true;
  }
  return false;
}

bool pdg::LockAttackAnalysis::isUnlockInst(Instruction &i, std::string lockInstName)
{
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    auto calledFunc = pdgutils::getCalledFunc(*ci);
    if (calledFunc == nullptr)
      return false;
    std::string unlockCallName = calledFunc->getName().str();
    unlockCallName = pdgutils::stripFuncNameVersionNumber(unlockCallName);

    if (_lockMap[lockInstName] == unlockCallName)
      return true;
  }
  return false;
}

bool pdg::LockAttackAnalysis::hasUnlockInstInSameBB(CallInst &lockCallInst)
{
  Function *calledFunc = pdgutils::getCalledFunc(lockCallInst);
  if (calledFunc == nullptr)
    return false;
  // obtain the lock function name
  auto lockCallName = pdgutils::stripFuncNameVersionNumber(calledFunc->getName().str());
  auto BB = lockCallInst.getParent();
  for (auto &inst : *BB)
  {
    if (&inst == &lockCallInst)
      continue;

    if (auto ci = dyn_cast<CallInst>(&inst))
    {
      auto calledFunc = pdgutils::getCalledFunc(*ci);
      if (calledFunc == nullptr)
        continue;
      auto calledFuncName = pdgutils::stripFuncNameVersionNumber(calledFunc->getName().str());
      if (_lockMap[lockCallName] == calledFuncName)
        return true;
    }
  }
  return false;
}

pdg::LockAttackAnalysis::CSMap pdg::LockAttackAnalysis::computeIntraCS(Function &F)
{
  CSMap ret;
  
  for (inst_iterator instIter = inst_begin(F); instIter != inst_end(F); instIter++)
  {
    // 1. find all lock instruction that call to acquire a lock
    if (!isLockInst(*instIter))
      continue;
    CallInst *lockCallInst = cast<CallInst>(&*instIter);
    Function *calledFunc = pdgutils::getCalledFunc(*lockCallInst);
    if (calledFunc == nullptr)
      return ret;
    // obtain the lock function name
    auto lockInstName = pdgutils::stripFuncNameVersionNumber(calledFunc->getName().str());
    // 2. find reachable unlock insts
    std::vector<Instruction *> unlockInsts;
    for (auto tmpInstIter = instIter; tmpInstIter != inst_end(F); tmpInstIter++)
    {
      if (isUnlockInst(*tmpInstIter, lockInstName))
        ret.insert(std::make_pair(&*instIter, &*tmpInstIter));
    }
  }

  return ret;
}

pdg::LockAttackAnalysis::CSMap pdg::LockAttackAnalysis::computeIntraCSWithLock(CallInst &lockCallInst)
{
  CSMap ret;

  auto F = lockCallInst.getFunction();
  auto instIter = inst_begin(*F);
  // 1. find the call inst
  while (&*instIter != &lockCallInst)
  {
    instIter++;
  }

  Function *calledFunc = pdgutils::getCalledFunc(lockCallInst);
  if (calledFunc == nullptr)
    return ret;
 
  auto lockInstName = pdgutils::stripFuncNameVersionNumber(calledFunc->getName().str());

  // 2. find unlock that can be reached from the lock
  std::vector<Instruction *> unlockInsts;
  for (auto tmpInstIter = instIter; tmpInstIter != inst_end(F); tmpInstIter++)
  {
    if (isUnlockInst(*tmpInstIter, lockInstName))
      ret.insert(std::make_pair(&*instIter, &*tmpInstIter));
  }

  return ret;
}

std::set<Instruction *> pdg::LockAttackAnalysis::computeInstsInCS(pdg::LockAttackAnalysis::CSPair csPair)
{
  Instruction *lockInst = csPair.first;
  Instruction *unlockInst = csPair.second;
  assert(lockInst->getFunction() == unlockInst->getFunction() && "error analyzing cs span for multiple functions");

  Function *f = lockInst->getFunction();
  auto lockInstIter = inst_begin(f);
  while (&*lockInstIter != lockInst)
    lockInstIter++;
  auto unlockInstIter = inst_begin(f);
  while (&*unlockInstIter != unlockInst)
  {
    unlockInstIter++;
  }

  std::set<Instruction *> ret;
  lockInstIter++;
  if (lockInstIter == inst_end(f))
    return ret;
  // search for call inst, inspect all the instructions in the
  // callee
  while (lockInstIter != unlockInstIter)
  {
    // skipped called function for now
    // if (CallInst *ci = dyn_cast<CallInst>(&*lockInstIter))
    // {
    //   auto called_func = pdgutils::getCalledFunc(*ci);
    //   if (called_func != nullptr && !called_func->isDeclaration())
    //   {
    //     for (auto it = inst_begin(called_func); it != inst_end(called_func); ++it)
    //     {
    //       ret.insert(&*it);
    //     }
    //   }
    // }
    ret.insert(&*lockInstIter);
    lockInstIter++;
  }
  return ret;
}

/*
Atk1
- This analysis computes lock call sites that don't have paired unlock calls.
- such functions can be invoked by corrupted driver to lock the kernel and never unlock, causing deadlock
*/
pdg::LockAttackAnalysis::CallInstSet pdg::LockAttackAnalysis::computeUnpairedLockCallSites(pdg::LockAttackAnalysis::CallInstSet &lockCallSites)
{
  CallInstSet ret;
  for (auto lockCallSite : lockCallSites)
  {
    std::set<Node *> CFGReachedNode;
    auto lockCSCFGNode = _CFG->getNode(*lockCallSite);
    _CFG->computeIntraprocControlFlowReachedNodes(*lockCSCFGNode, CFGReachedNode);
    bool hasIntraPairedUnlock = false;
    for (auto cfgNode : CFGReachedNode)
    {
      auto nodeVal = cfgNode->getValue();
      if (!nodeVal)
        continue;
      if (CallInst *ci = dyn_cast<CallInst>(nodeVal))
      {
        auto calledFunc = pdgutils::getCalledFunc(*ci);
        if (!calledFunc)
          continue;
        if (calledFunc->getName().str() == "rtnl_unlock")
        {
          hasIntraPairedUnlock = true;
          break;
        }
      }
    }
    if (!hasIntraPairedUnlock)
      ret.insert(lockCallSite);
  }
  return ret;
}

/*Atk2: finding lock calls that guarded by conditions*/
void pdg::LockAttackAnalysis::computeLockCallSiteUnderConditions(pdg::LockAttackAnalysis::CallInstSet &lockCallSites)
{
  nlohmann::ordered_json atkJsons = nlohmann::ordered_json::array();
  std::set<EdgeType> ctrlEdge = {EdgeType::CONTROL};
  for (auto lockCS : lockCallSites)
  {
    if (hasUnlockInstInSameBB(*lockCS))
      continue;

    nlohmann::ordered_json lockUnderCondJson;
    auto lockName = pdgutils::getCalledFunc(*lockCS)->getName().str();
    // obtain PDG node for the call site
    auto lockCSNode = _PDG->getNode(*lockCS);
    // use control dep (backward) to obtain the condition guarding the lock call
    auto controlDepNodes = _PDG->findNodesReachedByEdges(*lockCSNode, ctrlEdge, true);
    auto it = controlDepNodes.find(lockCSNode);
    if (it != controlDepNodes.end())
      controlDepNodes.erase(it);

    if (controlDepNodes.size() > 0)
    {
      lockUnderCondJson["Lock name"] = lockName;
      lockUnderCondJson["Lock Inst Loc"] = pdgutils::getSourceLocationStr(*lockCS);
      std::string condLocStr = "";
      for (auto ctrlDepNode : controlDepNodes)
      {
        auto ctrlNodeVal = ctrlDepNode->getValue();
        if (!ctrlNodeVal)
            continue;

        if (Instruction *i = dyn_cast<Instruction>(ctrlNodeVal))
          condLocStr += pdgutils::getSourceLocationStr(*i) + " | ";
      }
      
      lockUnderCondJson["Cond Lock"] = condLocStr;
      atkJsons.push_back(lockUnderCondJson);
    }
  }

  // add stats at the beginning
  nlohmann::ordered_json statJson;
  statJson["No. entry"] = atkJsons.size();
  atkJsons.insert(atkJsons.begin(), statJson);

  // print out the JSON
  taintutils::printJsonToFile(atkJsons, "lockGuardedByCond.json");
}

void pdg::LockAttackAnalysis::computeCSLoop(pdg::LockAttackAnalysis::CallInstSet &lockCallSites)
{
  nlohmann::ordered_json atkJsons = nlohmann::ordered_json::array();

  for (auto lockCS : lockCallSites)
  {
    // compute critical section
    auto intraCSMap = computeIntraCSWithLock(*lockCS);
    
    // obtain loop info in the function
    auto func = lockCS->getFunction();
    DominatorTree DT(*func);
    LoopInfo LI(DT);

    for (auto csPair : intraCSMap)
    {
      auto instsInCS = computeInstsInCS(csPair);
      nlohmann::ordered_json loopCSJson;
      auto lockName = pdgutils::getCalledFunc(*lockCS)->getName().str();

      for (auto inst : instsInCS)
      {
        if (BranchInst *BI = dyn_cast<BranchInst>(inst))
        {
          if (LI.isLoopHeader(BI->getParent()))
          {
            loopCSJson["Lock Name"] = lockName;
            loopCSJson["Lock loc"] = pdgutils::getSourceLocationStr(*csPair.first);
            loopCSJson["Loop loc"] = pdgutils::getSourceLocationStr(*inst);
            loopCSJson["loop form"] = "Loop";
          }
        }

        if (auto gep = dyn_cast<GetElementPtrInst>(inst))
        {
          auto gepOffset = pdgutils::getGEPAccessFieldOffset(*gep);
          if (gepOffset < 0)
          {
            loopCSJson["Lock Name"] = lockName;
            loopCSJson["Lock loc"] = pdgutils::getSourceLocationStr(*csPair.first);
            loopCSJson["Loop loc"] = pdgutils::getSourceLocationStr(*inst);
            loopCSJson["loop form"] = "list iteration/container_of";
          }
        }
      }

      if (!loopCSJson.empty())
        atkJsons.push_back(loopCSJson);
    }
  }

  // add stats at the beginning
  nlohmann::ordered_json statJson;
  statJson["No. entry"] = atkJsons.size();
  atkJsons.insert(atkJsons.begin(), statJson);

  // print to file
  taintutils::printJsonToFile(atkJsons, "CSLoop.json");
}

// protocol violation related attacks, should move the impl to a separate file later
void pdg::LockAttackAnalysis::computeKernelInterfaceFuncCSUnderCondition()
{
  nlohmann::ordered_json atkJsons = nlohmann::ordered_json::array();
  // step1: obtain driver boundary functions
  auto kernelInterfaceFuncs = _SDA->getBoundaryFuncs();

  CallInstSet kernelFuncCSs;
  for (auto f : kernelInterfaceFuncs)
  {
    // skip driver boundary function
    if (_SDA->isDriverFunc(*f))
      continue;
    // step 2: obtain the driver call sites of the kernel interface functions
    auto callSites = _callGraph->getFunctionCallSites(*f);
    for (auto callSite : callSites)
    {
      auto callerFunc = callSite->getFunction();

      if (_SDA->isDriverFunc(*callerFunc))
        kernelFuncCSs.insert(callSite);
    }
  }

  // step 3: check if the kernel interface function call sites are under conditions
  std::set<EdgeType> ctrlEdge = {EdgeType::CONTROL};
  for (auto CS : kernelFuncCSs)
  {
    // obtain PDG node for the call site
    auto callSiteNode = _PDG->getNode(*CS);
    // use control dep (backward) to obtain the condition guarding the lock call
    auto controlDepNodes = _PDG->findNodesReachedByEdges(*callSiteNode, ctrlEdge, true);
    auto it = controlDepNodes.find(callSiteNode);
    if (it != controlDepNodes.end())
      controlDepNodes.erase(it);
    // when there is a check for the call site
    if (controlDepNodes.size() > 0)
    {
       nlohmann::ordered_json csJson;
       std::string condLocStr = "";
       for (auto ctrlDepNode : controlDepNodes)
       {
         auto ctrlNodeVal = ctrlDepNode->getValue();
         if (!ctrlNodeVal)
           continue;

         if (Instruction *i = dyn_cast<Instruction>(ctrlNodeVal))
           condLocStr += pdgutils::getSourceLocationStr(*i) + " | ";
       }
       csJson["Cond loc"] = condLocStr;
       csJson["Call site loc"] = pdgutils::getSourceLocationStr(*CS);
       atkJsons.push_back(csJson);
    }
  }

  // add stats at the beginning
  nlohmann::ordered_json statJson;
  statJson["No. entry"] = atkJsons.size();
  atkJsons.insert(atkJsons.begin(), statJson);
  // print to file
  taintutils::printJsonToFile(atkJsons, "ConditionalKernelICall.json");
}

void pdg::LockAttackAnalysis::computeDrvCallBackCallSite()
{
  nlohmann::ordered_json atkJsons = nlohmann::ordered_json::array();

  for (auto F : _SDA->getBoundaryFuncs())
  {
    if (!_SDA->isDriverFunc(*F))
      continue;

    auto drvFuncCallSites = _callGraph->getFunctionCallSites(*F);
    for (auto CS : drvFuncCallSites)
    {
      // only check for kernel funcs
      if (_SDA->isDriverFunc(*CS->getFunction()))
        continue;
      nlohmann::ordered_json csJson;
      csJson["Ret loc"] = pdgutils::getSourceLocationStr(*CS);
      csJson["Drv func"] = F->getName().str();
      csJson["Drv func loc"] = pdgutils::getFuncSourceLocStr(*F);
      atkJsons.push_back(csJson);
    }
  }

  taintutils::printJsonToFile(atkJsons, "DrvCallBackRetLoc.json");
}

static RegisterPass<pdg::LockAttackAnalysis>
    LockAttackAnalysis("lock-atk-analysis", "KSplit Lock Attack Analysis", false, true);