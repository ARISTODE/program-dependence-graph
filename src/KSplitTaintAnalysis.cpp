#include "KSplitTaintAnalysis.hh"
#include "KSplitCFG.hh"

char pdg::KSplitTaintAnalysis::ID = 0;
using namespace llvm;

void pdg::KSplitTaintAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<SharedDataAnalysis>();
  AU.setPreservesAll();
}

// classes of the risky operations
static std::unordered_map<std::string, std::string> RiskyFuncToClassMap = {
    // Memory Management
    {"kmalloc", "memory"},
    {"kzalloc", "memory"},
    {"kfree", "memory"},
    {"vmalloc", "memory"},
    {"vzalloc", "memory"},
    {"vfree", "memory"},
    // Concurrency Management
    {"spin_lock", "concurrency"},
    {"spin_unlock", "concurrency"},
    {"mutex_lock", "concurrency"},
    {"mutex_unlock", "concurrency"},
    // Reference Counting
    {"atomic_inc", "refCount"},
    {"atomic_dec", "refCount"},
    {"kref_get", "refCount"},
    {"kref_put", "refCount"},
    {"kobject_put", "refCount"},
    {"kobject_get", "refCount"},
    // Timer Management
    {"add_timer", "timer"},
    {"mod_timer", "timer"},
    {"del_timer", "timer"},
    {"hrtimer_start", "timer"},
    // I/O Ports Management
    {"inb", "ioPorts"},
    {"outb", "ioPorts"},
    {"ioread32", "ioPorts"},
    {"iowrite32", "ioPorts"},
    // Direct Memory Access (DMA)
    {"dma_alloc_coherent", "dma"},
    {"dma_free_coherent", "dma"},
    {"dma_map_single", "dma"},
    {"dma_unmap_single", "dma"}};

bool pdg::KSplitTaintAnalysis::runOnModule(Module &M)
{
  _module = &M;
  _SDA = &getAnalysis<SharedDataAnalysis>();
  _PDG = _SDA->getPDG();
  _callGraph = &PDGCallGraph::getInstance();
  if (!_callGraph->isBuild())
    _callGraph->build(M);

  taintedPathConds = {};

  // analyze private states update caused by kernel interface invocation
  analyzePrivateStateUpdate(false);
  analyzeRiskyAPICalls(false);
  analyzePrivateStateUpdate(true);
  analyzeRiskyAPICalls(true);
  riskyAPICollector.printStatistics();

  // analyze shared data corruption
  // initTaintSources();
  // propagateTaints();
  // reportTaintResults();
  return false;
}

void pdg::KSplitTaintAnalysis::incrementRiskyAPIFields(std::string &className)
{
  riskyAPICollector.riskyAPIs++;
  if (className == "memory")
    riskyAPICollector.memoryManagement++;
  else if (className == "concurrency")
    riskyAPICollector.concurrencyManagement++;
  else if (className == "refCount")
    riskyAPICollector.referenceCounting++;
  else if (className == "timer")
    riskyAPICollector.timerManagement++;
  else if (className == "ioPorts")
    riskyAPICollector.ioPortsManagement++;
  else if (className == "dma")
    riskyAPICollector.dma++;
}

void pdg::KSplitTaintAnalysis::incrementRiskyAPIFieldsConditional(std::string &className)
{
  riskyAPICollector.riskyAPIsConditional++;
  if (className == "memory")
    riskyAPICollector.memoryManagementConditional++;
  else if (className == "concurrency")
    riskyAPICollector.concurrencyManagementConditional++;
  else if (className == "refCount")
    riskyAPICollector.referenceCountingConditional++;
  else if (className == "timer")
    riskyAPICollector.timerManagementConditional++;
  else if (className == "ioPorts")
    riskyAPICollector.ioPortsManagementConditional++;
  else if (className == "dma")
    riskyAPICollector.dmaConditional++;
}

void pdg::KSplitTaintAnalysis::analyzeRiskyAPICalls(bool conditionals)
{
  auto &cfg = KSplitCFG::getInstance();
  if (!cfg.isBuild())
    cfg.build(*_module);

  for (auto boundaryFunc : _SDA->getBoundaryFuncs())
  {
    if (_SDA->isDriverFunc(*boundaryFunc))
      continue;
    // count directly invoked risky API
    riskyAPICollector.kernelInterfaceAPIs++;
    auto funcName = boundaryFunc->getName().str();
    auto it = RiskyFuncToClassMap.find(funcName);
    if (it != RiskyFuncToClassMap.end())
    {
      riskyAPICollector.directlyInvokedRiskyAPIs++;
      if (conditionals)
      {
        incrementRiskyAPIFieldsConditional(it->second);
      }
      else
      {
        incrementRiskyAPIFields(it->second);
      }
    }

    // count transitively invoked risky APIs
    // TODO: we need to consider path conditions
    auto boundaryFNode = _callGraph->getNode(*boundaryFunc);
    if (!boundaryFNode)
      continue;

    auto transFuncNodes = _callGraph->computeTransitiveClosure(*boundaryFNode);
    for (auto transFuncNode : transFuncNodes)
    {
      auto val = transFuncNode->getValue();

      if (auto transFunc = dyn_cast<Function>(val))
      {
        if (_SDA->isDriverFunc(*transFunc) || boundaryFunc == transFunc)
          continue;

        auto it = RiskyFuncToClassMap.find(transFunc->getName().str());
        if (it != RiskyFuncToClassMap.end())
        {
          if (conditionals)
          {
            Node *cfgTransNode = nullptr;
            Node *cfgBoundaryNode = nullptr;

            BasicBlock& boundaryFBB = boundaryFunc->getEntryBlock();
            auto boundaryFirstInstruction = boundaryFBB.getFirstNonPHIOrDbg();
            cfgBoundaryNode = cfg.getNode(*boundaryFirstInstruction);
          
            if (!transFunc->isDeclaration())
            {
              BasicBlock& transFBB = transFunc->getEntryBlock();
              auto transFirstInstruction = transFBB.getFirstNonPHIOrDbg();
              cfgTransNode = cfg.getNode(*transFirstInstruction);
            }

            else
            {
              std::vector<Node *> callPath;
              std::unordered_set<Node *> visited;
              _callGraph->findPathDFS(boundaryFNode, transFuncNode, callPath, visited);
              cfgTransNode = _PDG->getNode(*_callGraph->getCallGraphInstruction(callPath[callPath.size() - 2], transFuncNode));
            }

            if(!cfgBoundaryNode || !cfgTransNode){
              errs()<<"panic\n";
            }
            
            if (cfgTransNode && cfgBoundaryNode)
            {
              // see if path conditions are shared fields
              std::set<Value *> pathConditions = {};
              cfg.computePathConditionsBetweenNodes(*cfgBoundaryNode, *cfgTransNode, pathConditions);

              if (std::includes(taintedPathConds.begin(), taintedPathConds.end(), pathConditions.begin(), pathConditions.end()))
              {
                riskyAPICollector.transitivelyInvokedRiskyAPIsConditional++;
                incrementRiskyAPIFieldsConditional(it->second);
              }
            }
          }

          else
          {
            riskyAPICollector.transitivelyInvokedRiskyAPIs++;
            incrementRiskyAPIFields(it->second);
          }
        }
      }
    }
  }
}
void pdg::KSplitTaintAnalysis::analyzePrivateStateUpdate(bool conditionals)
{
  // 1. open log file for private states
  std::error_code EC;
  if (conditionals)
  {
    privateStateUpdateLogOS = new raw_fd_ostream("privateStateUpdateConditionals.log", EC, sys::fs::OF_Text);
  }
  else
  {
    privateStateUpdateLogOS = new raw_fd_ostream("privateStateUpdate.log", EC, sys::fs::OF_Text);
  }
  if (EC)
  {
    delete privateStateUpdateLogOS;
    errs() << "cannot open privateState log\n";
    return;
  }

  // obtain cfg, used to check path condition in later steps
  auto &cfg = KSplitCFG::getInstance();
  if (!cfg.isBuild())
    cfg.build(*_module);
  // 2. obtain all the kernel APIs called by the driver, compute store insts reachable by attacker without any checks
  std::set<llvm::Value *> pathCondsCopy;
  do
  {
    pathCondsCopy = taintedPathConds;
    for (auto boundaryF : _SDA->getBoundaryFuncs())
    {
      // only analyze kernel boundary functions
      if (_SDA->isDriverFunc(*boundaryF))
        continue;

      // for each called kernel boundary function, obtain it's transitive closure.
      auto boundaryFNode = _callGraph->getNode(*boundaryF);
      if (!boundaryFNode)
        continue;

      // the first instruction is used to compute control flow path from the boundary func
      // to all reachable store instructions
      auto boundaryFfirstInst = &*inst_begin(boundaryF);
      auto boundaryFfristInstCFGNode = cfg.getNode(*boundaryFfirstInst);

      auto transFuncNodes = _callGraph->computeTransitiveClosure(*boundaryFNode);
      for (auto transFuncNode : transFuncNodes)
      {
        auto val = transFuncNode->getValue();
        if (auto transFunc = dyn_cast<Function>(val))
        {
          // for driver functions called in ping-pong call style, ignore them
          if (_SDA->isDriverFunc(*transFunc))
            continue;
          auto transFuncWrapper = _PDG->getFuncWrapper(*transFunc);
          if (!transFuncWrapper)
            continue;
          auto storeInsts = transFuncWrapper->getStoreInsts();

          for (auto storeInst : storeInsts)
          {
            if (conditionals)
            {
              auto storeInstCFGNode = cfg.getNode(*storeInst);
              std::set<Value *> pathConds;
              cfg.computePathConditionsBetweenNodes(*boundaryFfristInstCFGNode, *storeInstCFGNode, pathConds);
              // if no path condition, we consider this is an attacker directly reachable store inst from the boundary function
              if (std::includes(taintedPathConds.begin(), taintedPathConds.end(), pathConds.begin(), pathConds.end()))
              {
                privateStateUpdateMap[boundaryF].insert(storeInst);
                taintedPathConds.insert(storeInst->getPointerOperand());
                if (!pathConds.empty())
                {
                  errs() << "burger\n";
                }
              }
            }
            else
            {
              privateStateUpdateMap[boundaryF].insert(storeInst);
            }
          }
        }
      }
    }
  } while ((taintedPathConds != pathCondsCopy) && conditionals);
  // 3. for unchecked store insts, classify based on modification on stack/heap objects, and print out the location
  PTAWrapper &ptaw = PTAWrapper::getInstance();
  auto globalTree = _SDA->getGlobalStructDTMap();
  for (auto funcPair : privateStateUpdateMap)
  {
    auto boundaryF = funcPair.first;
    auto reachedStoreInsts = funcPair.second;
    if (!ptaw.hasPTASetup())
      ptaw.setupPTA(*_module);
    for (auto si : reachedStoreInsts)
    {
      if (!si->getDebugLoc())
        continue;
      // TODO: 1. classify based on heap/stack/global, here, we can use SVF to classify
      auto ptrOp = si->getPointerOperand();
      auto ptrOpNode = _PDG->getNode(*ptrOp);
      TreeNode *valDepNode = nullptr;
      for (auto inEdge : ptrOpNode->getInEdgeSet())
      {
        if (inEdge->getEdgeType() == pdg::EdgeType::PARAMETER_IN)
        {
          // global
        }
        if (inEdge->getEdgeType() == pdg::EdgeType::VAL_DEP)
        {
          valDepNode = static_cast<TreeNode *>(inEdge->getSrcNode());
        }
      }
      if (valDepNode)
      {
        std::string fieldId = pdgutils::computeTreeNodeID(*valDepNode);
        if (valDepNode->isShared || _SDA->isSharedFieldID(fieldId))
        {
          continue;
        }
      }

      SVF::NodeID nodeId = ptaw._ander_pta->getPAG()->getValueNode(ptrOp);
      SVF::PointsTo pointsToInfo = ptaw._ander_pta->getPts(nodeId);
      for (auto memObjID = pointsToInfo.begin(); memObjID != pointsToInfo.end(); memObjID++)
      {
        if (ptaw._ander_pta->getPAG()->getObject(*memObjID)->isHeap())
        {
        }
        else if (ptaw._ander_pta->getPAG()->getObject(*memObjID)->isStack())
        {
        }
        else
        {
          // errs() << "stack2\n";
        }
      }
      // 2. classify the usage of the store instruction
      *privateStateUpdateLogOS << " ---------------------------------------------- \n";
      // to achieve this, inspect the updated address (pointer), and check the alias of the pointer
      std::vector<Node *> callPath;
      std::unordered_set<Node *> visited;
      auto sourceFuncNode = _callGraph->getNode(*boundaryF);
      auto sinkFuncNode = _callGraph->getNode(*si->getFunction());
      _callGraph->findPathDFS(sourceFuncNode, sinkFuncNode, callPath, visited);
      _callGraph->printPath(callPath, *privateStateUpdateLogOS);

      *privateStateUpdateLogOS << "Update func: " << si->getFunction()->getName().str() << "\n";
      *privateStateUpdateLogOS << *si << "\n";
      *privateStateUpdateLogOS << "Loc: ";
      pdgutils::printSourceLocation(*si, *privateStateUpdateLogOS);
      *privateStateUpdateLogOS << " --------------- [End of Case] ---------------- \n";
    }
  }
}

void pdg::KSplitTaintAnalysis::initTaintSourcesSharedState()
{
  // add taint sources from shared data
  auto globalStructDTMap = _SDA->getGlobalStructDTMap();
  // 1. (Shared struct field) add all the read locations of shared field to taint sources
  for (auto dtPair : globalStructDTMap)
  {
    auto typeTree = dtPair.second;
    std::queue<TreeNode *> nodeQueue;
    nodeQueue.push(typeTree->getRootNode());
    while (!nodeQueue.empty())
    {
      TreeNode *n = nodeQueue.front();
      nodeQueue.pop();
      DIType *nodeDIType = n->getDIType();
      if (nodeDIType == nullptr)
        continue;
      // classify the risky field into different classes
      // if (isDriverControlledField(*n))
      //     _taintSources.insert(n);

      for (auto childNode : n->getChildNodes())
      {
        nodeQueue.push(childNode);
      }
    }
  }

  // 2. (parameter passed from driver to kernel)
  // auto kernelAPIs = readFuncsFromFile("imported_funcs", M);
  // for (auto func : kernelAPIs)
  // {
  //     if (_SDA->isDriverFunc(*func))
  //         continue;

  //     auto funcWrapper = _PDG->getFuncWrapper(*func);
  //     if (!funcWrapper)
  //         continue;

  //     auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
  //     for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  //     {
  //         auto argTree = iter->second;
  //         auto rootNode = argTree->getRootNode();
  //         auto argDIType = rootNode->getDIType();
  //         // struct and struct fields are covered by type taint
  //         if (argDIType && dbgutils::isStructPointerType(*argDIType))
  //             continue;
  //         _taintSources.insert(rootNode);
  //     }
  // }
}

// void pdg::KSplitTaintAnalysis::propagateTaintsSharedState()
// {
//     // setup taint edges
//     std::set<pdg::EdgeType> taintEdges = {
//         pdg::EdgeType::PARAMETER_IN,
//         // pdg::EdgeType::PARAMETER_OUT,
//         // pdg::EdgeType::DATA_ALIAS,
//         // EdgeType::DATA_RET,
//         // pdg::EdgeType::CONTROL,
//         pdg::EdgeType::DATA_STORE_TO,
//         pdg::EdgeType::DATA_DEF_USE,
//     };

//     for (auto taintSource : _taintSources)
//     {
//     }
// }

// classify the usage of the value represented by the node based on taint analysis
std::set<std::string> pdg::KSplitTaintAnalysis::classifyUsageTaint(pdg::Node &srcNode)
{
  std::set<pdg::EdgeType> taintEdges = {
      pdg::EdgeType::PARAMETER_IN,
      pdg::EdgeType::DATA_STORE_TO,
      pdg::EdgeType::DATA_DEF_USE,
  };

  std::map<RiskyTypes, std::string> riskyTypeToStr = {
      {RiskyTypes::PTRARITH, "ptr arith"},
      {RiskyTypes::ARITHOP, "arith op"},
      {RiskyTypes::PTRDEREF, "ptr deref"},
      {RiskyTypes::SENBRANCH, "sen branch"},
      {RiskyTypes::SENOP, "sen op"},
      {RiskyTypes::ARRAYACC, "array acc"},
  };

  std::set<RiskyTypes> riskyClassificationStrs;
  std::set<std::string> retRiskyClassificationStrs;
  std::string accessPathStr = ""; // TODO: Compute the access path string

  auto taintNodes = _PDG->findNodesReachedByEdges(srcNode, taintEdges);
  std::set<RiskyTypes> processedRiskyTypes;

  for (auto taintNode : taintNodes)
  {
    riskyClassificationStrs.clear();
    auto nodeVal = taintNode->getValue();
    if (!nodeVal)
      continue;

    // Classify the values based on the usage
    auto nodeType = nodeVal->getType();
    if (nodeType->isPointerTy())
    {
      classifyTaintPointerUsage(srcNode, riskyClassificationStrs);
    }
    else
    {
      classifyTaintValUsage(srcNode, riskyClassificationStrs);
    }

    // Classify and record the taint source and sink
    for (auto s : riskyClassificationStrs)
    {
      if (processedRiskyTypes.find(s) == processedRiskyTypes.end())
      {
        processedRiskyTypes.insert(s);
        _taintTuples.insert(std::make_tuple(&srcNode, taintNode, accessPathStr, riskyTypeToStr[s]));
        retRiskyClassificationStrs.insert(riskyTypeToStr[s]);
      }
    }
  }

  return retRiskyClassificationStrs;
}

void pdg::KSplitTaintAnalysis::classifyTaintPointerUsage(pdg::Node &taintNode, std::set<RiskyTypes> &riskyClassificationStrs)
{

  // 1. check for ptr arithmetic
  // check if ptr field has pointe arithmetic
  if (checkPtrValUsedInPtrArithOp(taintNode))
    riskyClassificationStrs.insert(RiskyTypes::PTRARITH);

  if (checkPtrValhasPtrDeref(taintNode))
    riskyClassificationStrs.insert(RiskyTypes::PTRDEREF);

  if (checkValUsedInSenBranchCond(taintNode))
    riskyClassificationStrs.insert(RiskyTypes::SENBRANCH);

  if (checkValUsedInSensitiveOperations(taintNode))
    riskyClassificationStrs.insert(RiskyTypes::SENOP);
}

void pdg::KSplitTaintAnalysis::classifyTaintValUsage(pdg::Node &taintNode, std::set<RiskyTypes> &riskyClassificationStrs)
{
  // 1. check for ptr arithmetic
  // check if value is accessed in array
  if (checkValUsedAsArrayIndex(taintNode))
    riskyClassificationStrs.insert(RiskyTypes::ARRAYACC);

  if (checkValUsedInPtrArithOp(taintNode))
    riskyClassificationStrs.insert(RiskyTypes::ARITHOP);

  if (checkValUsedInSenBranchCond(taintNode))
    riskyClassificationStrs.insert(RiskyTypes::SENBRANCH);

  if (checkValUsedInSensitiveOperations(taintNode))
    riskyClassificationStrs.insert(RiskyTypes::SENOP);
}

bool pdg::KSplitTaintAnalysis::checkPtrValUsedInPtrArithOp(Node &taintNode)
{
  auto nodeVal = taintNode.getValue();
  if (!nodeVal || !nodeVal->getType()->isPointerTy())
    return false;

  for (auto user : nodeVal->users())
  {
    if (auto gep = dyn_cast<GetElementPtrInst>(user))
    {
      auto gepPtrOp = gep->getPointerOperand();
      auto gepPtrTy = gep->getType();
      // check if the the ptr arith is result from a field access, if so, skip
      if (pdgutils::isStructPointerType(*gepPtrTy))
        continue;
      else
      {
        // only if the pointer is used to derive other pointers
        if (gepPtrOp == nodeVal)
          return true;
      }
    }

    if (isa<OverflowingBinaryOperator>(user))
      return true;

    if (isa<PtrToIntInst>(user))
    {
      for (auto ptrToInstUser : user->users())
      {
        if (isa<OverflowingBinaryOperator>(ptrToInstUser))
          return true;
      }
    }
  }
  return false;
}

bool pdg::KSplitTaintAnalysis::checkPtrValhasPtrDeref(pdg::Node &taintNode)
{
  auto nodeVal = taintNode.getValue();
  if (!nodeVal || !nodeVal->getType()->isPointerTy())
    return false;

  for (auto user : nodeVal->users())
  {
    if (isa<LoadInst>(user))
      return true;
  }
  return false;
}

bool pdg::KSplitTaintAnalysis::checkValUsedAsArrayIndex(pdg::Node &taintNode)
{
  auto nodeVal = taintNode.getValue();
  if (!nodeVal)
    return false;

  for (auto user : nodeVal->users())
  {
    if (GetElementPtrInst *gep = dyn_cast<llvm::GetElementPtrInst>(user))
    {
      // skip gep on struct types
      auto ptrOperand = gep->getPointerOperand();
      auto ptrOpNode = _PDG->getNode(*ptrOperand);
      if (!ptrOpNode || !ptrOperand)
        continue;
      if (ptrOpNode->getDIType() && dbgutils::isStructPointerType(*ptrOpNode->getDIType()))
        continue;
      if (pdgutils::isStructPointerType(*ptrOperand->getType()))
        continue;
      // Check if taint value is used as an index in the GEP instruction
      for (auto IdxOp = gep->idx_begin(), E = gep->idx_end(); IdxOp != E; ++IdxOp)
      {
        if (IdxOp->get() == nodeVal)
          return true;
      }
    }
  }
  return false;
}

bool pdg::KSplitTaintAnalysis::checkValUsedInPtrArithOp(pdg::Node &taintNode)
{
  auto nodeVal = taintNode.getValue();
  if (!nodeVal)
    return false;

  for (auto user : nodeVal->users())
  {
    if (auto gep = dyn_cast<GetElementPtrInst>(user))
    {
      auto gepPtrOp = gep->getPointerOperand();
      auto gepPtrTy = gepPtrOp->getType();
      // check if the the ptr arith is result from a field access, if so, skip
      if (pdgutils::isStructPointerType(*gepPtrTy))
        continue;
      else
        return true;
    }
    // add, mul, sub etc
    if (isa<OverflowingBinaryOperator>(user))
      return true;
  }
  return false;
}

bool pdg::KSplitTaintAnalysis::checkValUsedInSensitiveOperations(pdg::Node &taintNode)
{

  auto nodeVal = taintNode.getValue();
  if (!nodeVal)
    return false;

  for (auto user : nodeVal->users())
  {
    if (CallInst *ci = dyn_cast<CallInst>(user))
    {
      auto calledFunc = pdgutils::getCalledFunc(*ci);
      if (!calledFunc)
        continue;
      auto calledFuncName = calledFunc->getName().str();
      for (auto mapIter : RiskyFuncToClassMap)
      {
        auto riskyFuncName = mapIter.first;
        if (calledFuncName.find(riskyFuncName) != std::string::npos)
          return true;
      }
    }
  }
  return false;
}

bool pdg::KSplitTaintAnalysis::checkValUsedInSenBranchCond(pdg::Node &taintNode)
{
  auto nodeVal = taintNode.getValue();
  if (!nodeVal)
    return false;

  for (auto user : nodeVal->users())
  {
    if (auto cmpInst = dyn_cast<CmpInst>(user))
    {
      for (auto u : cmpInst->users())
      {
        if (isa<BranchInst>(u) || isa<SwitchInst>(u))
        {
          auto branchNode = _PDG->getNode(*u);
          auto branchControlDependentNodes = _PDG->findNodesReachedByEdge(*branchNode, EdgeType::CONTROL);
          for (auto ctrDepNode : branchControlDependentNodes)
          {
            auto depNodeVal = ctrDepNode->getValue();
            if (CallInst *ci = dyn_cast<CallInst>(depNodeVal))
            {
              auto calledFunc = pdgutils::getCalledFunc(*ci);
              if (!calledFunc)
                continue;
              // some sensitive operations such as BUG() is translated
              // to inline assembly
              if (ci->isInlineAsm())
                return true;
              auto calledFuncName = calledFunc->getName().str();
              for (auto mapIter : RiskyFuncToClassMap)
              {
                auto riskyFuncName = mapIter.first;
                if (calledFuncName.find(riskyFuncName) != std::string::npos)
                  return true;
              }
              // check if the call can reach sensitive operations
              auto calledFuncNode = _callGraph->getNode(*calledFunc);
              if (canReachSensitiveOperations(*calledFuncNode))
                return true;
            }
          }
        }
      }
    }
  }

  return false;
}

bool pdg::KSplitTaintAnalysis::canReachSensitiveOperations(pdg::Node &callerNode)
{
  for (auto mapIter : RiskyFuncToClassMap)
  {
    auto riskyFuncName = mapIter.first;
    auto func = _module->getFunction(StringRef(riskyFuncName));
    if (!func)
      continue;

    auto riskyFuncNode = _callGraph->getNode(*func);
    if (!riskyFuncNode)
      continue;
    if (_callGraph->canReach(callerNode, *riskyFuncNode))
      return true;
  }
  return false;
}

static RegisterPass<pdg::KSplitTaintAnalysis>
    RiskyFieldAnalysis("ksplit-taint", "KSplit Taint Analysis", false, true);