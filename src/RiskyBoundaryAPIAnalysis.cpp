#include "RiskyBoundaryAPIAnalysis.hh"

char pdg::RiskyBoundaryAPIAnalysis::ID = 0;
using namespace llvm;

void pdg::RiskyBoundaryAPIAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<SharedDataAnalysis>();
  AU.setPreservesAll();
}

static std::set<pdg::EdgeType> PtrValTaintPropEdges = {
    pdg::EdgeType::PARAMETER_IN,
    pdg::EdgeType::DATA_DEF_USE,
    pdg::EdgeType::DATA_ALIAS,
    pdg::EdgeType::DATA_STORE_TO,
    pdg::EdgeType::DATA_RAW,
};

static std::set<pdg::EdgeType> ValTaintPropEdges = {
    pdg::EdgeType::PARAMETER_IN,
    pdg::EdgeType::DATA_DEF_USE,
    pdg::EdgeType::DATA_STORE_TO,
    pdg::EdgeType::DATA_EQUL_OBJ,
};

bool pdg::RiskyBoundaryAPIAnalysis::runOnModule(Module &M)
{
  // # setup basic utitlities
  _module = &M;
  _SDA = &getAnalysis<SharedDataAnalysis>();
  _PDG = _SDA->getPDG();
  _callGraph = &PDGCallGraph::getInstance();
  if (!_callGraph->isBuild())
    _callGraph->build(M);

  _CFG = &KSplitCFG::getInstance();
  if (!_CFG->isBuild())
    _CFG->build(M);

  // analyze private states update
  // analyzeKernelPrivateStatesUpdate();
  for (auto boundaryFunc : _SDA->getBoundaryFuncs())
  {
    // only propagate through kernel boundary func
    if (_SDA->isDriverFunc(*boundaryFunc))
      continue;
    propagateBoundaryParameterTaints(boundaryFunc);
  }

  // analyze the risky kernel boundary APIs
  nlohmann::ordered_json riskyAPIJsonObjs = nlohmann::json::array();
  analyzeRiskyBoundaryKernelAPIs(riskyAPIJsonObjs);
  taintutils::printJsonToFile(riskyAPIJsonObjs, "RiskyBoundaryAPI.json");
  auto classificationJson = countRiskyAPIClasses(riskyAPIJsonObjs);
  taintutils::printJsonToFile(classificationJson, "BoundaryAPICounts.json");
  return false;
}

// propagate taints through parameters passed across isolation boundary
// this allowuing us to track the path conditions that are controlled by the attacker
void pdg::RiskyBoundaryAPIAnalysis::propagateBoundaryParameterTaints(Function *boundaryFunc)
{
  auto funcW = _PDG->getFuncWrapper(*boundaryFunc);
  if (!funcW)
    return;

  for (auto arg : funcW->getArgList())
  {
    Tree *formalInTree = funcW->getArgFormalInTree(*arg);
    if (!formalInTree)
      continue;
    // For each node in the tree, propagate taints through the node
    std::set<Node*> taintNodes;
    taintutils::propagateTaints(*formalInTree->getRootNode(), ValTaintPropEdges, taintNodes);
  }
}

// handle the analysis of kernel risky API that are directly invoked by the driver
void pdg::RiskyBoundaryAPIAnalysis::handleDirectRiskyAPI(Function *boundaryFunc, nlohmann::ordered_json &riskyAPIJsonObjs, unsigned &caseID)
{
  nlohmann::ordered_json kernelAPIJson;
  auto funcName = boundaryFunc->getName().str();
  kernelAPIJson["id"] = caseID;
  caseID++;
  kernelAPIJson["kernel boundary func name"] = funcName;
  kernelAPIJson["Risky API Class"] = taintutils::getRiskyClassStr(funcName);
  kernelAPIJson["Direct Risky Kernel API"] = 1;

  std::string driverCallerFuncNameStr = "";
  auto funcCallSites = _callGraph->getFunctionCallSites(*boundaryFunc);
  for (auto CS : funcCallSites)
  {
    auto callerFunc = CS->getFunction();
    if (!_SDA->isDriverFunc(*callerFunc))
      continue;

    auto callerFuncName = callerFunc->getName().str();
    std::string callSiteSrcLoc = pdgutils::getSourceLocationStr(*CS);
    driverCallerFuncNameStr += callerFuncName + "(" + callSiteSrcLoc + ")" + " | ";
  }

  kernelAPIJson["driver callers"] = driverCallerFuncNameStr;
  riskyAPIJsonObjs.push_back(kernelAPIJson);
}

// handle the analysis of transitivley called risky kernel APIs
void pdg::RiskyBoundaryAPIAnalysis::handleTransitiveRiskyAPI(Function *boundaryFunc, nlohmann::ordered_json &riskyAPIJsonObjs, unsigned &caseID)
{
  // case 2: analyze transitively invoked risky kernel APIs
  auto boundaryFNode = _callGraph->getNode(*boundaryFunc);
  if (!boundaryFNode)
    return;

  auto funcName = boundaryFunc->getName().str();
  auto transFuncNodes = _callGraph->computeTransitiveClosure(*boundaryFNode);
  for (auto transFuncNode : transFuncNodes)
  {
    auto val = transFuncNode->getValue();

    if (Function *transFunc = dyn_cast<Function>(val))
    {
      // skip driver functions
      if (_SDA->isDriverFunc(*transFunc) || boundaryFunc == transFunc)
        continue;
      // find all risky kernel APIs transitively invoked
      auto transFuncName = transFunc->getName().str();
      if (taintutils::isRiskyFunc(transFuncName))
      {
        // setup JSON object for the current kernel boundary func
        nlohmann::ordered_json kernelAPIJson;
        // populate basic info
        kernelAPIJson["id"] = caseID;
        caseID++;
        kernelAPIJson["kernel boundary func name"] = funcName;
        kernelAPIJson["risky func"] = transFuncName;
        kernelAPIJson["Risky API Class"] = taintutils::getRiskyClassStr(transFuncName);
        // populate call path
        std::vector<Node *> callPath;
        std::unordered_set<Node *> visited;
        auto boundaryKernelFuncCallNode = _callGraph->getNode(*boundaryFunc);
        // obtain all the driver caller of this kernel function
        auto funcCallSites = _callGraph->getFunctionCallSites(*boundaryFunc);
        std::string callPathStr = "";
        for (auto CS : funcCallSites)
        {
          auto callerFunc = CS->getFunction();
          // skip kernel caller
          if (!_SDA->isDriverFunc(*callerFunc))
            continue;
          auto driverBoundaryCallNode = _callGraph->getNode(*callerFunc);
          auto transFuncCallNode = _callGraph->getNode(*transFunc);
          if (_callGraph->findPathDFS(boundaryKernelFuncCallNode, transFuncCallNode, callPath, visited))
          {
            callPath.insert(callPath.begin(), driverBoundaryCallNode);
            std::string s = _callGraph->generatePathStr(callPath);
            callPathStr = callPathStr + "( [" + std::to_string(callPath.size()) + "]" + s + " )";
            // obtain path conditions
            // the path conditions are collected by starting from the first instruction of the boundary kernel function
            // to the call site of the risky operation
            auto firstBoundaryFuncInst = &*inst_begin(*boundaryFunc);
            auto firstBoundaryFuncInstControlNode = _CFG->getNode(*firstBoundaryFuncInst);
            auto riskyFuncCallSites = _callGraph->getFunctionCallSites(*transFunc);
            for (auto riskyFuncCS : riskyFuncCallSites)
            {
              auto riskyFuncCSControlNode = _CFG->getNode(*riskyFuncCS);
              std::set<Value *> pathConditions = {};
              _CFG->computePathConditionsBetweenNodes(*firstBoundaryFuncInstControlNode, *riskyFuncCSControlNode, pathConditions);
              bool isControllablePath = true;
              for (auto cond : pathConditions)
              {
                if (!_PDG->getNode(*cond))
                  continue;
                if (!_PDG->getNode(*cond)->isTaint())
                {
                  isControllablePath = false;
                  break;
                }
              }

              if (isControllablePath)
                kernelAPIJson["Is Controlled Path"] = 1;
              else
              {
                if (kernelAPIJson["Is Controlled Path"] != 0)
                  kernelAPIJson["Is Controlled Path"] = 0;
              }

              if (pathConditions.size() > 0)
                kernelAPIJson["No. path cond"] = pathConditions.size();
            }
          }
          visited.clear();
          callPath.clear();
        }

        if (!callPathStr.empty())
          kernelAPIJson["call path"] = callPathStr;

        // compute driver call site, e.g., which driver function transitively invoke this risky kernel API
        riskyAPIJsonObjs.push_back(kernelAPIJson);
      }
    }
  }
}

void pdg::RiskyBoundaryAPIAnalysis::analyzeRiskyBoundaryKernelAPIs(nlohmann::ordered_json &riskyAPIJsonObjs)
{
  unsigned caseID = 0;
  for (auto boundaryFunc : _SDA->getBoundaryFuncs())
  {
    // only analyze kernel boundary functions
    if (_SDA->isDriverFunc(*boundaryFunc))
      continue;

    auto funcName = boundaryFunc->getName().str();
    // case 1: analyze risky kernel API directly invoked by the driver
    if (taintutils::isRiskyFunc(funcName))
    {
      handleDirectRiskyAPI(boundaryFunc, riskyAPIJsonObjs, caseID);
    }
    else
    {
      handleTransitiveRiskyAPI(boundaryFunc, riskyAPIJsonObjs, caseID);
    }
  }
}

void pdg::RiskyBoundaryAPIAnalysis::analyzeBoundaryFuncStateUpdates(llvm::Function *boundaryFunc, StoreJsonMap &storeInstJsonMap, StoreCondMap &storeInstCondMap)
{
  auto boundaryFNode = _callGraph->getNode(*boundaryFunc);
  if (!boundaryFNode)
    return;

  // setup SVF util, for querying object types later
  PTAWrapper &ptaw = PTAWrapper::getInstance();
  if (!ptaw.hasPTASetup())
    ptaw.setupPTA(*_module);

  auto funcName = boundaryFunc->getName().str();
  auto transFuncNodes = _callGraph->computeTransitiveClosure(*boundaryFNode);
  for (auto transFuncNode : transFuncNodes)
  {
    auto val = transFuncNode->getValue();

    if (Function *transFunc = dyn_cast<Function>(val))
    {
      // skip driver functions
      if (_SDA->isDriverFunc(*transFunc) || boundaryFunc == transFunc)
        continue;
      auto funcName = transFunc->getName().str();
      // inspect all the store instructions in the transitively invoked function
      auto funcWrapper = _PDG->getFuncWrapper(*transFunc);
      if (!funcWrapper)
        continue;
      auto storeInsts = funcWrapper->getStoreInsts();
      for (auto si : storeInsts)
      {
        auto ptrOp = si->getPointerOperand();
        auto ptrOpNode = _PDG->getNode(*ptrOp);
        // each store inst require a json obj to store the stats
        nlohmann::ordered_json storeInstJson;
        // step 1: analyze the store inst, and check what memory region it may accesses
        storeInstJson["func"] = funcName;
        storeInstJson["Src Loc"] = pdgutils::getSourceLocationStr(*si);
        std::string memType = "";
        for (auto inEdge : ptrOpNode->getInEdgeSet())
        {
          if (inEdge->getEdgeType() == pdg::EdgeType::VAL_DEP)
          {
            if (TreeNode *valDepNode = static_cast<TreeNode *>(inEdge->getSrcNode()))
            {
              if (valDepNode->isShared)
                continue;
            }
          }
          else if (inEdge->getEdgeType() == pdg::EdgeType::PARAMETER_IN)
          {
            auto srcNodeTy = inEdge->getSrcNode()->getNodeType();
            if (srcNodeTy == GraphNodeType::FORMAL_IN)
              memType = "heap";
            else if (srcNodeTy == GraphNodeType::GLOBAL_VAR)
              memType = "global";
          }
        }

        SVF::NodeID nodeId = ptaw._ander_pta->getPAG()->getValueNode(ptrOp);
        SVF::PointsTo pointsToInfo = ptaw._ander_pta->getPts(nodeId);
        for (auto memObjID = pointsToInfo.begin(); memObjID != pointsToInfo.end(); memObjID++)
        {
          if (ptaw._ander_pta->getPAG()->getObject(*memObjID)->isHeap())
            memType = "heap";
        }

        if (memType.empty())
          memType = "stack";

        storeInstJson["update mem type"] = memType;

        // store the driver func that transitively invoke this store inst
        auto funcCallSites = _callGraph->getFunctionCallSites(*boundaryFunc);
        std::string drvCallerStr = "";
        for (auto CS : funcCallSites)
        {
          auto callerFunc = CS->getFunction();
          // skip kernel caller
          if (!_SDA->isDriverFunc(*callerFunc))
            continue;
          std::string s = callerFunc->getName().str();
          drvCallerStr = drvCallerStr + "(" + s + " ) | ";
        }
        storeInstJson["driver caller"] = drvCallerStr;

        // step 2: compute the path conditions required to reach this store inst
        auto firstBoundaryFuncInst = &*inst_begin(*boundaryFunc);
        auto firstBoundaryFuncInstControlNode = _CFG->getNode(*firstBoundaryFuncInst);
        auto SIControlNode = _CFG->getNode(*si);
        std::set<Value *> pathConditions = {};
        _CFG->computePathConditionsBetweenNodes(*firstBoundaryFuncInstControlNode, *SIControlNode, pathConditions);

        // step 3: if no path conditions required, or all path conditions are tainted, propagate the taints from the updated
        // address, and taint all the nodes that can be derived from the updated address
        bool isControlled = true;
        for (auto cond : pathConditions)
        {
          if (!_PDG->getNode(*cond)->isTaint())
            isControlled = false;
        }
        storeInstJson["No. path cond"] = pathConditions.size();
        // step 4: if path conditions are not met, append this to a queue, and perform a fix point computation later
        if (isControlled)
        {
          storeInstJson["Is Controlled Path"] = 1;
          std::set<Node *> taintNodes;
          taintutils::propagateTaints(*ptrOpNode, PtrValTaintPropEdges, taintNodes);
        }
        else
        {
          // track the store inst with the path conditions required to reach the store inst only record the ones that are not controllable at the beginning.
          // then iteratively taint the nodes and update the controllable path in the fix point calculation
          storeInstCondMap[si] = pathConditions;
          storeInstJson["Is Controlled Path"] = 0;
        }

        // store the json to a map
        storeInstJsonMap[si] = storeInstJson;
      }
    }
  }
}

void pdg::RiskyBoundaryAPIAnalysis::calculateFixedPointForPrivateStateUpdates(StoreJsonMap &storeInstJsonMap, StoreCondMap &storeInstCondMap)
{
  std::queue<StoreInst *> siQueue = initializeQueue(storeInstCondMap);

  while (!siQueue.empty())
  {
    StoreInst *si = siQueue.front();
    siQueue.pop();

    if (isPathControllable(si, storeInstCondMap))
    {
      auto taintNodes = propagateTaintsForPointerOperand(si);
      enqueueAffectedStores(taintNodes, storeInstCondMap, siQueue);
      storeInstJsonMap[si]["Is Controlled Path"] = 1;
    }
  }
}

std::queue<StoreInst *> pdg::RiskyBoundaryAPIAnalysis::initializeQueue(const StoreCondMap &storeInstCondMap)
{
  std::queue<StoreInst *> siQueue;
  for (const auto &entry : storeInstCondMap)
  {
    siQueue.push(entry.first);
  }
  return siQueue;
}

bool pdg::RiskyBoundaryAPIAnalysis::isPathControllable(StoreInst *si, const StoreCondMap &storeInstCondMap)
{
  bool isControllable = true;
  for (auto cond : storeInstCondMap.at(si))
  {
    if (!_PDG->getNode(*cond)->isTaint())
    {
      isControllable = false;
      break;
    }
  }
  return isControllable;
}

std::set<pdg::Node *> pdg::RiskyBoundaryAPIAnalysis::propagateTaintsForPointerOperand(StoreInst *si)
{
  auto ptrOp = si->getPointerOperand();
  auto ptrOpNode = _PDG->getNode(*ptrOp);
  std::set<Node *> taintNodes;
  taintutils::propagateTaints(*ptrOpNode, PtrValTaintPropEdges, taintNodes);
  return taintNodes;
}

void pdg::RiskyBoundaryAPIAnalysis::enqueueAffectedStores(const std::set<pdg::Node *> &taintNodes, const StoreCondMap &storeInstCondMap, std::queue<StoreInst *> &siQueue)
{
  for (Node *node : taintNodes)
  {
    auto taintVal = node->getValue();
    for (const auto &entry : storeInstCondMap)
    {
      if (entry.second.find(taintVal) != entry.second.end())
      {
        siQueue.push(entry.first);
      }
    }
  }
}

// counting private states update
// this function analyze the private states that are transitively updated by each boundary kernel function
void pdg::RiskyBoundaryAPIAnalysis::analyzeKernelPrivateStatesUpdate()
{
  for (auto boundaryFunc : _SDA->getBoundaryFuncs())
  {
    // only analyze kernel boundary functions
    if (_SDA->isDriverFunc(*boundaryFunc))
      continue;
    // compute the private states updated, and store in JSON object
    StoreJsonMap storeInstJsonMap;
    StoreCondMap storeInstCondMap;
    analyzeBoundaryFuncStateUpdates(boundaryFunc, storeInstJsonMap, storeInstCondMap);
    calculateFixedPointForPrivateStateUpdates(storeInstJsonMap, storeInstCondMap);

    // output private states update
    nlohmann::ordered_json privateStatesUpdateJsons = nlohmann::ordered_json::array();
    for (auto &entry : storeInstJsonMap)
    {
      privateStatesUpdateJsons.push_back(entry.second);
    }
    taintutils::printJsonToFile(privateStatesUpdateJsons, "privateStatesUpdate.json");
  }
}

// counting methods
nlohmann::ordered_json pdg::RiskyBoundaryAPIAnalysis::countRiskyAPIClasses(const nlohmann::ordered_json &riskyAPIJsonObjs)
{
  // Create an unordered_map to store the count of each Risky API Class
  std::unordered_map<std::string, int> riskyAPIClassCount;

  // Iterate through the JSON array
  for (const auto &jsonObj : riskyAPIJsonObjs)
  {
    // Check for existence of the key "Risky API Class" in the JSON object
    auto it = jsonObj.find("Risky API Class");
    if (it == jsonObj.end())
    {
      // Log an error message and continue to the next iteration
      std::cerr << "Error: 'Risky API Class' key not found in JSON object." << std::endl;
      continue;
    }

    // Extract the "Risky API Class" value from each JSON object
    std::string riskyAPIClass = jsonObj.at("Risky API Class").get<std::string>();

    // Increment the count for this Risky API Class
    riskyAPIClassCount[riskyAPIClass]++;
  }

  // Create a JSON object to store the counts
  nlohmann::ordered_json outputJson;

  for (const auto &pair : riskyAPIClassCount)
  {
    outputJson[pair.first] = pair.second;
  }

  return outputJson;
}

static RegisterPass<pdg::RiskyBoundaryAPIAnalysis>
    RiskyFieldAnalysis("risky-boundary", "KSplit Taint Analysis", false, true);