#include "RiskyFieldAnalysis.hh"
// #include "RiskyAPIAnalysis.hh"
#include "KSplitCFG.hh"
/*
This analysis is used to compute a set of risky patterns realted to each shared field between the
kernel and driver. The followings are a set of classes we define.
1. Used in memory allocation: Resource exhaustion
2. Involved in I/O operations: e.g., read/write APIs
3. Used as array indices: execute out-of-bounds read/write
4. Used to derive addresses that kernel access: if a field could derive addresses (ptr arithmetic) that kernel may access, then it could leak to wrong/illegal memory access
5. Function pointer: potential for control flow hijacking
6. Used in syncrhonization primitives: causing race conditions/dead locks
7. Security-critical operations: user authentication, privilege checks
*/

char pdg::RiskyFieldAnalysis::ID = 0;
using namespace llvm;

cl::opt<bool, true> ECTP("controlled-taint-path", cl::desc("only select controlled taint path"), cl::value_desc("controlled_taint_path"), cl::location(pdg::OnlyControlledPath), cl::init(true));
bool pdg::OnlyControlledPath;

void pdg::RiskyFieldAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.addRequired<SharedDataAnalysis>();
    AU.addRequired<ControlDependencyGraph>();
    AU.setPreservesAll();
}

std::unordered_set<std::string> sensitiveOperations = {
    "kmalloc",
    "vmalloc",
    "kzalloc",
    "vzalloc",
    "kmem_cache_create",
    "kmem_cache_alloc",
    "kmem_cache_free",
    "kmem_cache_destroy",
    "kfree",
    "vfree",
    "copy_from_user",
    "copy_to_user",
    "memcpy",
    "strcpy",
    "strncpy",
    "memset",
    "kobject_put",
    "kobject_create_and_add",
    "mod_timer"
};

std::set<Function *> readFuncsFromFile(std::string fileName, Module &M, std::string dir)
{
    std::set<Function *> ret;
    sys::fs::file_status status;
    sys::fs::status("boundaryFiles", status);
    if ((!dir.empty() && !sys::fs::exists(status)) || !sys::fs::is_directory(status))
    {
        errs() << "boundary files don't exist, please run boundary analysis pass (-output-boundary-info) first\n";
        return ret;
    }

    std::string filePath = dir + "/" + fileName;
    std::ifstream ReadFile(filePath);
    for (std::string line; std::getline(ReadFile, line);)
    {
        Function *f = M.getFunction(StringRef(line));
        if (!f)
            continue;
        ret.insert(f);
    }
    return ret;
}

bool pdg::RiskyFieldAnalysis::runOnModule(Module &M)
{
    _module = &M;
    _SDA = &getAnalysis<SharedDataAnalysis>();
    _PDG = _SDA->getPDG();
    _callGraph = &PDGCallGraph::getInstance();

    auto kernelInterfaceAPIs = readFuncsFromFile("imported_funcs", M, "boundaryFiles");
    
    // step 1: propagate taint, used by branch checking later
    errs() << "[CIV Analysis]: propagating taints\n";
    // propagateTaints(kernelInterfaceAPIs);
    // step 2: classify fields
    errs() << "[CIV Analysis]: classifying risky data using type\n";
    classifyRiskySharedFields();
    // TODO: taint the return value of driver interface functions
    // classify the taint based on the data directly passed across the isolation boundary
    // step 3: classify parameters passed directly from the interface
    errs() << "[CIV Analysis]: classifying risky data for boundary params\n";
    // classifyRiskyBoundaryParams(kernelInterfaceAPIs);

    // step 4: check return value of driver exported functions
    errs() << "[CIV Analysis]: classifying risky data for drv callbacks\n";
    // classifyDrvCallBackRetval();
    printFieldClassificationTaint();
    printBoundaryStructFieldsClassificationStats();
    return false;
}

std::unordered_set<pdg::Node *> pdg::RiskyFieldAnalysis::findNodesTaintedByEdges(Node &src, std::set<EdgeType> &edgeTypes, bool isBackward)
{
    std::unordered_set<Node *> ret;
    std::queue<Node *> nodeQueue;
    nodeQueue.push(&src);
    std::unordered_set<Node *> visited;
    while (!nodeQueue.empty())
    {
        Node *currentNode = nodeQueue.front();
        nodeQueue.pop();
        if (visited.find(currentNode) != visited.end())
            continue;
        visited.insert(currentNode);
        ret.insert(currentNode);

        Node::EdgeSet edgeSet;
        if (isBackward)
            edgeSet = currentNode->getInEdgeSet();
        else
            edgeSet = currentNode->getOutEdgeSet();
        
        for (auto edge : edgeSet)
        {
            if (edgeTypes.find(edge->getEdgeType()) == edgeTypes.end())
                continue;
            // a specialized processing for call instructions
            // first, the call instruction should still be considered reachable by taint
            // however, we don't want the return value to be tainted, if it's not tainted 
            // by the parameters. So, while the ret stil contains this call inst, we will stop 
            // adding the call inst to the queue to allow it to taint other values.
            // TODO: we should identify which argument is tainted, instead of considering 
            // all arguments are tainted.
            // auto dstNodeVal = edge->getDstNode()->getValue();
            // if (dstNodeVal && isa<CallInst>(dstNodeVal))
            // {
            //     if (auto ci = dyn_cast<CallInst>(dstNodeVal))
            //     {
            //         auto calledFunc = pdgutils::getCalledFunc(*ci);
            //         if (!calledFunc)
            //             continue;;
            //         auto fw = _PDG->getFuncWrapper(*calledFunc);
            //         if (fw && !canParamReachRetVal(*fw))
            //             continue;
            //     }
            // }

            if (isBackward)
                nodeQueue.push(edge->getSrcNode());
            else
                nodeQueue.push(edge->getDstNode());
        }
    }

    return ret;
}

void pdg::RiskyFieldAnalysis::propagateTaints(std::set<Function *> &kernelInterfaceAPIs)
{
    // propagate taints from the shared struct type
    auto globalStructDTMap = _SDA->getGlobalStructDTMap();
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

            for (auto childNode : n->getChildNodes())
            {
                nodeQueue.push(childNode);
            }

            auto nodeType = n->getDIType();
            std::set<EdgeType> taintEdges = {};
            if (dbgutils::isPointerType(*nodeType))
            {
                taintEdges = {
                    EdgeType::DATA_ALIAS,
                    EdgeType::PARAMETER_IN,
                    EdgeType::DATA_STORE_TO,
                    EdgeType::DATA_DEF_USE,
                    EdgeType::DATA_EQUL_OBJ};
            }
            else
            {
                taintEdges = {
                    EdgeType::PARAMETER_IN,
                    EdgeType::DATA_DEF_USE,
                    EdgeType::DATA_EQUL_OBJ,
                    EdgeType::DATA_STORE_TO};
            }

            if (!n->isShared)
                continue;

            auto addrVars = n->getAddrVars();
            for (auto addrVar : addrVars)
            {
                auto addrVarNode = _PDG->getNode(*addrVar);
                auto taintNodes = findNodesTaintedByEdges(*addrVarNode, taintEdges);
                for (auto taintNode : taintNodes)
                {
                    taintNode->setTaint();
                }
            }
        }
    }
    
    // propagate taints from the kernel interfaces, where driver passes data directly through parameters
    // propagate taints from the parameters
    for (auto func : kernelInterfaceAPIs)
    {
        if (_SDA->isDriverFunc(*func))
            continue;

        auto funcWrapper = _PDG->getFuncWrapper(*func);
        if (!funcWrapper)
            continue;

        auto argTreeMap = funcWrapper->getArgFormalInTreeMap();

        for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
        {
            auto argTree = iter->second;
            auto rootNode = argTree->getRootNode();
            auto argDIType = rootNode->getDIType();
            if (!argDIType)
                continue;

            std::set<EdgeType> taintEdges;

            if (dbgutils::isPointerType(*argDIType))
            {
                taintEdges = {
                    EdgeType::DATA_ALIAS,
                    EdgeType::PARAMETER_IN,
                    EdgeType::DATA_DEF_USE,
                    EdgeType::DATA_EQUL_OBJ,
                    EdgeType::DATA_STORE_TO};
            }
            else
            {
                taintEdges = {
                    EdgeType::PARAMETER_IN,
                    EdgeType::DATA_DEF_USE,
                    EdgeType::DATA_EQUL_OBJ,
                    EdgeType::DATA_STORE_TO};
            }

            auto taintNodes = findNodesTaintedByEdges(*rootNode, taintEdges);

            for (auto taintNode : taintNodes)
            {
                taintNode->setTaint();
            }
        }
    }
}

void pdg::RiskyFieldAnalysis::classifyRiskySharedFields()
{
    auto globalStructDTMap = _SDA->getGlobalStructDTMap();
    for (auto dtPair : globalStructDTMap)
    {
        auto typeTree = dtPair.second;
        std::queue<TreeNode *> nodeQueue;
        nodeQueue.push(typeTree->getRootNode());
        // set up JSON object for storing struct field views
        auto rootDIType = typeTree->getRootNode()->getDIType();
        // record general stats about the struct
        nlohmann::ordered_json structStatJson;
        if (rootDIType)
        {
            nlohmann::ordered_json structFieldsJson;
            structStatJson["struct name"] = typeTree->getRootNode()->getSrcName();
        }

        // store classification of struct fields in json array
        nlohmann::ordered_json taintJsonObjs = nlohmann::ordered_json::array();
        std::map<RiskyDataType, unsigned> riskyFieldCounters;

        unsigned numFields = 0;
        unsigned numSharedFields = 0;
        unsigned numKRDUFields = 0;
        unsigned numDrvReadFields = 0;
        while (!nodeQueue.empty())
        {
            TreeNode *n = nodeQueue.front();
            nodeQueue.pop();
            DIType *nodeDIType = n->getDIType();
            if (nodeDIType == nullptr)
                continue;

            for (auto childNode : n->getChildNodes())
            {
                nodeQueue.push(childNode);
            }
            if (n->isStructField())
                numFields++;

            auto fieldTypeName = dbgutils::getSourceLevelVariableName(*n->getDIType());
            auto fieldName = n->getSrcName();
            // classify the risky field into different classes
            if (n->isShared)
            {
                // per struct shared field count
                numSharedFields++;
                // increase the total shared field count
                _numSharedFields++;
            }

            bool hasDrvRead = false;
            if (isDriverControlledField(*n, hasDrvRead))
            {
                _numKernelReadDriverUpdatedFields++;
                numKRDUFields++;
                // record the updated fields
                _KRDUFieldIds.insert(pdgutils::computeTreeNodeID(*n));
                std::set<RiskyDataType> riskyClassifications;
                classifyRiskyField(*n, riskyClassifications, taintJsonObjs);
                // accumulate counters for the current struct
                for (auto riskyDT : riskyClassifications)
                {
                    riskyFieldCounters[riskyDT]++;
                }

                // update the total counter
                updateRiskyFieldCounters(riskyClassifications);
                // record unclassified fields
                if (riskyClassifications.empty())
                {
                    riskyFieldCounters[RiskyDataType::OTHER]++;
                    totalRiskyFieldCounters[RiskyDataType::OTHER]++;
                }
                _caseID++;
            }
            
            // counting driver read fields 
            if (hasDrvRead)
                numDrvReadFields++;
        }

        // propagate struct in JSON format
        structStatJson["No.Fields"] = numFields;
        structStatJson["No.Drv Read fields"] = numDrvReadFields;
        structStatJson["No.Shared fields"] = numSharedFields;
        structStatJson["No.Shared fields"] = numSharedFields;
        structStatJson["No.KRDU fields"] = numKRDUFields;
        structStatJson["No.classified fields"] = numKRDUFields - riskyFieldCounters[RiskyDataType::OTHER];
        structStatJson["No.unclassified fields"] = riskyFieldCounters[RiskyDataType::OTHER];

        for (auto it = riskyFieldCounters.begin(); it != riskyFieldCounters.end(); ++it)
        {
            std::string riskyDTStr = taintutils::riskyDataTypeToString(it->first);
            // record the frequency
            structStatJson[riskyDTStr] = it->second;
        }
        taintJsonObjs.insert(taintJsonObjs.begin(), structStatJson);

        // dump all the json to field
        taintutils::printJsonToFile(taintJsonObjs, "PerStructTaint.json");
    }
}

void pdg::RiskyFieldAnalysis::classifyRiskyBoundaryParams(std::set<Function *> &kernelInterfaceAPIs)
{
    for (auto field : _KRDUFieldIds) 
    {
        errs() << "krdu field: " << field << "\n";
    }

    for (auto func : kernelInterfaceAPIs)
    {
        if (_SDA->isDriverFunc(*func))
            continue;

        auto funcWrapper = _PDG->getFuncWrapper(*func);
        if (!funcWrapper)
            continue;
        
        auto argTreeMap = funcWrapper->getArgFormalInTreeMap();

        // if a risky API is directly invoked by the driver, this is immediate an attack
        if (taintutils::isRiskyFunc(func->getName().str()))
        {
            nlohmann::ordered_json taintJsonObjs = nlohmann::ordered_json::array();
            // add each parameter to the json
            for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
            {
                auto argTree = iter->second;
                auto rootNode = argTree->getRootNode();
                nlohmann::ordered_json directRiskyAPIJson;
                directRiskyAPIJson["id"] = _caseID;
                directRiskyAPIJson["risky"] = "direct-risky-API";
                directRiskyAPIJson["param"] = rootNode->getSrcName();
                directRiskyAPIJson["risky API"] = func->getName().str();
                directRiskyAPIJson["isControl"] = 1;
                directRiskyAPIJson["isTrue"] = "1";
                taintJsonObjs.push_back(directRiskyAPIJson);
                _caseID++;
            }
            taintutils::printJsonToFile(taintJsonObjs, "BoundaryParamTaint.json"); 
        }
        // record number of boundary args
        for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
        {
            auto argTree = iter->second;
            auto rootNode = argTree->getRootNode();
            _numBoundaryArg++;
            // local counters for struct
            auto rootDIType = rootNode->getDIType();
            std::string structTypeName = "";
            if (dbgutils::isStructPointerType(*rootDIType))
                structTypeName = rootNode->getChildNodes()[0]->getTypeName(true);

            unsigned numFields = 0;
            unsigned numKRDUFields = 0;

            nlohmann::ordered_json taintJsonObjs = nlohmann::ordered_json::array();
            std::queue<TreeNode *> nodeQueue;
            nodeQueue.push(rootNode);

            while (!nodeQueue.empty())
            {
                TreeNode *n = nodeQueue.front();
                nodeQueue.pop();
                DIType *nodeDIType = n->getDIType();
                if (nodeDIType == nullptr)
                    continue;

                // skip private fields, and fields that are not read by the kernel
                // if (n->isStructField() && !n->isShared || !n->hasReadAccess())
                bool isKRDUField = _KRDUFieldIds.find(pdgutils::computeTreeNodeID(*n)) != _KRDUFieldIds.end();
                if (n->isStructField())
                {
                    numFields++;
                    // has to be a shared fields, and the fields has to be updated within the 
                    // driver domain
                    if (!isKRDUField)
                        continue;
                    else
                    {
                        numKRDUFields++; // record for this struct
                        _numBoundaryFields++;
                    }
                }

                for (auto childNode : n->getChildNodes())
                {
                    nodeQueue.push(childNode);
                }
                
                std::set<RiskyDataType> riskyClassifications;
                classifyRiskyField(*n, riskyClassifications, taintJsonObjs);
                // update the total counter
                updateRiskyParamCounters(riskyClassifications);
                // record unclassified fields
                if (riskyClassifications.empty())
                {
                    totalRiskyParamCounters[RiskyDataType::OTHER]++;
                }
                else
                {
                    if (n->isRootNode())
                        _numClassifiedBoundaryArg++;
                    if (n->isStructField())
                    {
                        _numClassifiedBoundaryFields++;
                        auto treeNodeID = pdgutils::computeTreeNodeID(*n);
                        if (_sharedStructClassifiedFields[structTypeName].find(treeNodeID) == _sharedStructClassifiedFields[structTypeName].end())
                            _sharedStructClassifiedFields[structTypeName].insert(treeNodeID);
                        
                        for (auto riskyType : riskyClassifications)
                        {
                            _fieldRiskyTypeMap[structTypeName][riskyType].insert(treeNodeID);
                        }
                    }
                }
            }

            // propagate struct in JSON format
            // setting up object to record the shared fields stats
            if (rootDIType && dbgutils::isStructPointerType(*rootDIType))
            {
                _sharedStructTypeRiskyCounts[structTypeName]["Struct"] = structTypeName;
                _sharedStructTypeRiskyCounts[structTypeName]["No.Fields"] = numFields;
                _sharedStructTypeRiskyCounts[structTypeName]["No.KRDU fields"] = numKRDUFields;
                _sharedStructTypeRiskyCounts[structTypeName]["No.classified fields"] = _sharedStructClassifiedFields[structTypeName].size();
                _sharedStructTypeRiskyCounts[structTypeName]["No.unclassified fields"] = numKRDUFields - _sharedStructClassifiedFields[structTypeName].size();
                // update the risky fields associate with each class
            }
                
            _caseID++;
            taintutils::printJsonToFile(taintJsonObjs, "BoundaryParamTaint.json");
            taintutils::printClassifiedDataRecord(taintJsonObjs, "ClassifiedDataRecords.log");
        }
    }

    errs() << "----- Risky data dist: ------ \n";
    errs() << "total: " << totalRiskyParamCounters.size() << "\n";
    for (auto iter : totalRiskyParamCounters)
    {
        errs() << "\t" << pdgutils::riskyDataTypeToString(iter.first) << ": " << std::to_string(iter.second) << "\n";
    }
}

void pdg::RiskyFieldAnalysis::classifyDrvCallBackRetval()
{
    for (auto func : _SDA->getBoundaryFuncs())
    {
        if (!_SDA->isDriverFunc(*func))
            continue;

        auto funcWrapper = _PDG->getFuncWrapper(*func);
        if (!funcWrapper)
            continue;

        auto retFormalTree = funcWrapper->getRetFormalInTree();
        auto retRootNode = retFormalTree->getRootNode();
        if (retRootNode)
        {
            auto retRootDIType = retRootNode->getDIType();
            if (!retRootDIType)
                continue;
            // classify the return value based on the risky use
            auto actualInTreeNodes = retRootNode->getInNeighborsWithDepType(EdgeType::PARAMETER_IN);
            for (auto n : actualInTreeNodes)
            {
                TreeNode *actualTN = static_cast<TreeNode *>(n);
                nlohmann::ordered_json retTaintJsonObjs = nlohmann::ordered_json::array();
                std::set<RiskyDataType> retRiskyClassifications;
                classifyRiskyField(*actualTN, retRiskyClassifications, retTaintJsonObjs);

                // update the total counter
                updateRiskyParamCounters(retRiskyClassifications);

                if (retRiskyClassifications.empty())
                {
                    totalRiskyParamCounters[RiskyDataType::OTHER]++;
                }
                taintutils::printJsonToFile(retTaintJsonObjs, "RetBoundaryParamTaint.json");
            }
        }
        _caseID++;
    }
}

// Function to update counters based on the set of RiskyDataType enums returned
void pdg::RiskyFieldAnalysis::updateRiskyFieldCounters(std::set<pdg::RiskyDataType> &riskyDataTypes)
{
    for (const auto &type : riskyDataTypes)
    {
        totalRiskyFieldCounters[type]++;
    }
}

void pdg::RiskyFieldAnalysis::updateRiskyParamCounters(std::set<pdg::RiskyDataType> &riskyDataTypes)
{
    for (const auto &type : riskyDataTypes)
    {
        totalRiskyParamCounters[type]++;
    }
}

bool pdg::RiskyFieldAnalysis::isDriverControlledField(TreeNode &tn, bool &hasDrvRead)
{
    // only classify for sturct fields
    if (!tn.isStructField())
        return false;

    // init kernel/driver read/write stats
    unsigned driverReadTimes = 0;
    unsigned driverWriteTimes = 0;
    unsigned kernelReadTimes = 0;
    unsigned kernelWriteTimes = 0;

    // all the function pointers exported by the driver are updated in the driver domain (static init)
    if (_SDA->isFuncPtr(tn) && _SDA->isDriverCallBackFuncPtrFieldNode(tn))
        driverWriteTimes += 1;

    auto addrVars = tn.getAddrVars();
    for (auto addrVar : addrVars)
    {
        if (Instruction *i = dyn_cast<Instruction>(addrVar))
        {
            Function *f = i->getFunction();
            // count driver read write times
            if (_SDA->isDriverFunc(*f))
            {
                if (pdgutils::isUpdatedInHeader(*i))
                    continue;
                if (pdgutils::hasWriteAccess(*i))
                    driverWriteTimes++;
                if (pdgutils::hasReadAccess(*i))
                {
                    driverReadTimes++;
                    hasDrvRead = true;
                }
            }
            // count kernel read write times
            else if (_SDA->isKernelFunc(*f))
            {
                if (pdgutils::hasReadAccess(*i))
                    kernelReadTimes++;
                if (pdgutils::hasWriteAccess(*i))
                    kernelWriteTimes++;
            }
        }
        if (driverWriteTimes > 0 && kernelReadTimes > 0)
            return true;
    }
    return false;
}

const std::string RED("\033[1;31m");
const std::string YELLOW("\033[1;33m");

std::string colorize(const std::string &str, const std::string &color_code)
{
    return color_code + str + "\033[0m";
}

// classify Risky pointer type fields
bool pdg::RiskyFieldAnalysis::classifyRiskyPtrField(TreeNode &tn, std::set<pdg::RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs)
{
    // record the field name in struct->fieldname format
    std::string accessPathStr = tn.getSrcHierarchyName(false);
    // obtain the address variables representing the field
    auto fieldDIType = tn.getDIType();
    bool classified = false;
    numPtrField++;
    // classify function ptr
    if (dbgutils::isFuncPointerType(*fieldDIType))
    {
        numFuncPtrField++;
        // TODO: we should discuss if function pointer could cause risky usage in the kernel.
        // Ideally, we should mark this as risky, as the attacker can just supply a pointer and instruct the kernel
        // to call back to that address.
        return true;
    }

    auto addrVars = tn.getAddrVars();
    if (dbgutils::isUnionPointerType(*fieldDIType))
    {
        nlohmann::ordered_json traceJson;
        traceJson["id"] = std::to_string(_caseID);
        traceJson["risky"] = "type-conf";
        if (tn.getFunc())
            traceJson["drv_func"] = tn.getFunc()->getName().str();

        std::string addressLocStr = "";
        for (auto addrVar : addrVars)
        {
            if (auto addrVarInst = dyn_cast<Instruction>(addrVar))
                addressLocStr = addressLocStr + pdgutils::getSourceLocationStr(*addrVarInst) + " | "; 
        }
        if (!addressLocStr.empty())
            traceJson["risky_locs"] = addressLocStr;
        traceJson["acc_path"] = accessPathStr;
        taintJsonObjs.push_back(traceJson);
        return true;
    }

    // if not func ptr, we can conclude this is a data ptr
    numDataPtrField += 1;

    // define taint edges for pointer type data
    std::set<EdgeType> taintEdges = {
        EdgeType::DATA_ALIAS,
        EdgeType::VAL_DEP,
        EdgeType::PARAMETER_IN,
        EdgeType::DATA_DEF_USE_LOAD,
        EdgeType::DATA_DEF_USE_CAST
        };

    // classify for other ptr type
    auto func = tn.getFunc();
    // if (!_SDA->isKernelFunc(*func) || !pdgutils::hasReadAccess(*addrVar))
    if (!func || !_SDA->isKernelFunc(*func))
        return false;

    // for pointer type node, find all the aliasing, and pointer derived from them
    auto taintNodes = findNodesTaintedByEdges(tn, taintEdges);
    // classify based on taint node
    for (auto taintNode : taintNodes)
    {
        auto taintVal = taintNode->getValue();
        if (!taintVal || !isa<Instruction>(taintVal))
            continue;

        if (taintNode->getFunc() && _SDA->isDriverFunc(*taintNode->getFunc()))
            continue; // skip driver uses in functions

        // check for ptr read
        if (riskyClassifications.find(RiskyDataType::PTR_READ) == riskyClassifications.end() && taintutils::isPointerRead(*taintNode))
        {
            auto traceJsonObj = generateTraceJsonObj(tn, *taintNode, accessPathStr, "ptr-read", _caseID, taintEdges, &tn);
            if (!traceJsonObj.empty())
            {
                // if ((traceJsonObj["isControl"] == 1 || traceJsonObj["isDirectControl"] == 1))
                // {
                    riskyClassifications.insert(RiskyDataType::PTR_READ);
                    if (auto taintInst = dyn_cast<Instruction>(taintVal))
                        traceJsonObj["dbg_addr"] = pdgutils::getInstructionString(*taintInst);
                    taintJsonObjs.push_back(traceJsonObj);
                    classified = true;
                // }
            }
        }
        // check for write through ptr
        if (riskyClassifications.find(RiskyDataType::PTR_WRTIE) == riskyClassifications.end() && taintutils::isPointeeModified(*taintNode))
        {
            riskyClassifications.insert(RiskyDataType::PTR_WRTIE);
            auto traceJsonObj = generateTraceJsonObj(tn, *taintNode, accessPathStr, "ptr-write", _caseID, taintEdges, &tn);
            if (!traceJsonObj.empty())
            {
                taintJsonObjs.push_back(traceJsonObj);
                classified = true;
            }
        }

        // check if the ptr could affect a bracnh in the kernel, also check if the branch contains risky operations
        std::string senOpName = "";
        if (riskyClassifications.find(RiskyDataType::CONTROL_VAR) == riskyClassifications.end() && taintutils::isValueInSensitiveBranch(*taintNode, senOpName))
        {
            // if (senOpName != "norm_branch")
            // {
                std::string s = "ptr-sen-branch ( senapi: " + senOpName + ")";
                auto traceJsonObj = generateTraceJsonObj(tn, *taintNode, accessPathStr, s, _caseID, taintEdges, &tn);
                if (!traceJsonObj.empty())
                {
                    // if ((traceJsonObj["isControl"] == 1 || traceJsonObj["isDirectControl"] == 1))
                    // {
                        riskyClassifications.insert(RiskyDataType::CONTROL_VAR);
                        taintJsonObjs.push_back(traceJsonObj);
                        classified = true;
                    // }
                }
            // }
        }

        //  check if the ptr is used in sensitive kernel APIS, such as memory copying, or memory management etc
        if (riskyClassifications.find(RiskyDataType::RISKY_KERNEL_FUNC) == riskyClassifications.end() && taintutils::isValueInSensitiveAPI(*taintNode, senOpName))
        {
            std::string s = "ptr-sen-api (" + senOpName + ")";
            auto traceJsonObj = generateTraceJsonObj(tn, *taintNode, accessPathStr, s, _caseID, taintEdges, &tn);
            if (!traceJsonObj.empty())
            {
                // if ((traceJsonObj["isControl"] == 1 || traceJsonObj["isDirectControl"] == 1))
                // {
                    riskyClassifications.insert(RiskyDataType::RISKY_KERNEL_FUNC);
                    taintJsonObjs.push_back(traceJsonObj);
                    classified = true;
                // }
            }
        }
    }

    return classified;
}

// classify Risky non-pointer type fields
bool pdg::RiskyFieldAnalysis::classifyRiskyNonPtrField(TreeNode &tn, std::set<pdg::RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs)
{
    // record the field name in struct->fieldname format
    std::string accessPathStr = tn.getSrcHierarchyName(false);
    // obtain the address variables representing the field
    auto addrVars = tn.getAddrVars();
    auto fieldDIType = tn.getDIType();
    bool classified = false;

    // define taint edges
    std::set<EdgeType> taintEdges = {
        EdgeType::VAL_DEP,
        EdgeType::PARAMETER_IN,
        EdgeType::DATA_DEF_USE_CAST,
        EdgeType::DATA_DEF_USE_ARITH,
        EdgeType::DATA_EQUL_OBJ,
        EdgeType::DATA_STORE_TO};

    if (dbgutils::isUnionType(*fieldDIType))
    {
        nlohmann::ordered_json traceJson;
        traceJson["id"] = std::to_string(_caseID);
        traceJson["risky"] = "type-conf";
        if (tn.getFunc())
            traceJson["drv_func"] = tn.getFunc()->getName().str();

        traceJson["acc_path"] = accessPathStr;
        std::string addressLocStr = "";
        for (auto addrVar : addrVars)
        {
            if (auto addrVarInst = dyn_cast<Instruction>(addrVar))
                addressLocStr = addressLocStr + pdgutils::getSourceLocationStr(*addrVarInst) + " | ";
        }
        traceJson["risky_locs"] = addressLocStr;
        taintJsonObjs.push_back(traceJson);
        return true;
    }

    // classify for non-ptr type
    auto func = tn.getFunc();
    // if (!_SDA->isKernelFunc(*func) || !pdgutils::hasReadAccess(*addrVar))
    // only focus on the use on the kernel side
    if (!func || !_SDA->isKernelFunc(*func))
        return false;

    auto taintNodes = findNodesTaintedByEdges(tn, taintEdges);
    for (auto taintNode : taintNodes)
    {
        auto taintVal = taintNode->getValue();
        if (!taintVal)
            continue;

        // skip taints in driver functions
        Instruction *taintInst = cast<Instruction>(taintVal);
        // skip driver uses in functions
        if (_SDA->isDriverFunc(*taintInst->getFunction()))
            continue;

        // check if value used as array index or operand of ptr arith
        if (riskyClassifications.find(RiskyDataType::ARR_IDX) == riskyClassifications.end() && taintutils::isUsedAsArrayIndex(*taintNode))
        {
            auto traceJsonObj = generateTraceJsonObj(tn, *taintNode, accessPathStr, "arr-idx", _caseID, taintEdges, &tn);
            if (!traceJsonObj.empty())
            {
                // if (traceJsonObj["isControl"] == 1 || traceJsonObj["isDirectControl"] == 1)
                // {
                    riskyClassifications.insert(RiskyDataType::ARR_IDX);
                    taintJsonObjs.push_back(traceJsonObj);
                    classified = true;
                // }
            }
        }

        // check if value is used in any number arithmetic operations
        if (riskyClassifications.find(RiskyDataType::NUM_ARITH) == riskyClassifications.end() && taintutils::isValueUsedInArithmetic(*taintNode))
        {
            // check if the derived value is used in a branch
            auto arithValTaintNodes = findNodesTaintedByEdges(*taintNode, taintEdges);
            for (auto arithTN : arithValTaintNodes)
            {
                std::string senOpName = "";
                if (taintutils::isValueInSensitiveBranch(*arithTN, senOpName) || taintutils::isValueInSensitiveAPI(*arithTN, senOpName))
                {
                    // if (senOpName == "norm_branch")
                    //     continue;

                    if (auto arithInst = dyn_cast<Instruction>(arithTN->getValue()))
                    {
                        std::string warnStr = "num-arith ( " + senOpName + " )";
                        auto traceJsonObj = generateTraceJsonObj(tn, *taintNode, accessPathStr, warnStr, _caseID, taintEdges, &tn);
                        if (!traceJsonObj.empty())
                        {
                            // if (traceJsonObj["isControl"] == 1 || traceJsonObj["isDirectControl"] == 1)
                            // {
                                riskyClassifications.insert(RiskyDataType::NUM_ARITH);
                                taintJsonObjs.push_back(traceJsonObj);
                                classified = true;
                                break;
                            // }
                        }
                    }
                }
            }
        }

        // check if value is used in divided by 0 operation
        if (riskyClassifications.find(RiskyDataType::DIV_BY_ZERO) == riskyClassifications.end() && taintutils::isValUsedInDivByZero(*taintNode))
        {
            auto traceJsonObj = generateTraceJsonObj(tn, *taintNode, accessPathStr, "div-by-zero", _caseID, taintEdges, &tn);
            if (!traceJsonObj.empty())
            {
                // if ((traceJsonObj["isControl"] == 1 || traceJsonObj["isDirectControl"] == 1))
                // {
                    riskyClassifications.insert(RiskyDataType::DIV_BY_ZERO);
                    taintJsonObjs.push_back(traceJsonObj);
                    classified = true;
                // }
            }
        }

        // check if value is used in kernel branch
        // check if the ptr could affect a bracnh in the kernel, also check if the branch contains risky operations
        std::string senOpName = "";
        if (riskyClassifications.find(RiskyDataType::CONTROL_VAR) == riskyClassifications.end() && taintutils::isValueInSensitiveBranch(*taintNode, senOpName))
        {
            // TODO: check if the branch operation is risky, if so, add the risky operation info to the json
            // if (senOpName != "norm_branch")
            // {
                std::string s = "val-sen-branch (" + senOpName + ")";
                auto traceJsonObj = generateTraceJsonObj(tn, *taintNode, accessPathStr, s, _caseID, taintEdges, &tn);
                if (!traceJsonObj.empty())
                {
                    // if ((traceJsonObj["isControl"] == 1 || traceJsonObj["isDirectControl"] == 1))
                    // {
                        riskyClassifications.insert(RiskyDataType::CONTROL_VAR);
                        taintJsonObjs.push_back(traceJsonObj);
                        classified = true;
                    // }
                }
            // }
        }

        //  check if the value is used in sensitive kernel APIS, such as memory copying, or memory management etc
        senOpName = "";
        if (riskyClassifications.find(RiskyDataType::RISKY_KERNEL_FUNC) == riskyClassifications.end() && taintutils::isValueInSensitiveAPI(*taintNode, senOpName))
        {
            std::string s = "val-sen-api (" + senOpName + ")";
            auto traceJsonObj = generateTraceJsonObj(tn, *taintNode, accessPathStr, s, _caseID, taintEdges, &tn);
            if (!traceJsonObj.empty())
            {
                // if ((traceJsonObj["isControl"] == 1 || traceJsonObj["isDirectControl"] == 1))
                // {
                    riskyClassifications.insert(RiskyDataType::RISKY_KERNEL_FUNC);
                    taintJsonObjs.push_back(traceJsonObj);
                    classified = true;
                // }
            }
        }
    }

    return classified;
}

void pdg::RiskyFieldAnalysis::classifyRiskyField(TreeNode &tn, std::set<pdg::RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs)
{
    // obtain the address variables representing the field
    auto fieldDIType = tn.getDIType();
    bool isPtrFieldClassified = false;
    bool isValFieldClassified = false;

    if (dbgutils::isPointerType(*fieldDIType))
    {
        // classify for pointer type fields
        isPtrFieldClassified = classifyRiskyPtrField(tn, riskyClassifications, taintJsonObjs);
    }
    else
    {
        // classify for non-pointer type fields
        isValFieldClassified = classifyRiskyNonPtrField(tn, riskyClassifications, taintJsonObjs);
    }

    // unclassified field
    if (!isPtrFieldClassified && !isValFieldClassified)
    {
        nlohmann::ordered_json traceJson;
        traceJson["id"] = _caseID;
        traceJson["acc_path"] = tn.getSrcHierarchyName(false);

        std::string readLocs = "";
        std::string updateLocs = "";
        for (auto addrVar : tn.getAddrVars())
        {
            if (auto inst = dyn_cast<Instruction>(addrVar))
            {
                auto f = inst->getFunction();
                // record driver access locations
                if (_SDA->isDriverFunc(*f))
                {
                    std::string drvUpdateLoc = pdgutils::getSourceLocationStr(*inst);
                    updateLocs = updateLocs + " [" + drvUpdateLoc + "], ";
                }

                // record kernel access locations
                if (!_SDA->isDriverFunc(*f))
                {
                    std::string kernelReadLoc = pdgutils::getSourceLocationStr(*inst);
                    readLocs = readLocs + " [" + kernelReadLoc + "], ";
                }
            }
        }

        if (tn.isRootNode())
        {
            // for root node (param), record the function name and location
            auto func = tn.getTree()->getFunc();
            auto DISubprog = func->getSubprogram();
            unsigned line = DISubprog->getLine();
            std::string file = DISubprog->getFilename().str();
            std::string filePrefix = "https://gitlab.flux.utah.edu/xcap/xcap-capability-linux/-/blob/llvm_v4.8/";
            readLocs = filePrefix + file + "#L" + std::to_string(line) + " | " + func->getName().str();
        }

        traceJson["Kernel read"] = readLocs;
        traceJson["Drv update"] = updateLocs;
        taintutils::printJsonToFile(traceJson, "UnclassifiedFields.json");
    }
}

bool pdg::RiskyFieldAnalysis::hasUpdateInDrv(pdg::TreeNode &n)
{
    std::set<EdgeType> edges = {
        EdgeType::PARAMETER_IN,
        EdgeType::DATA_ALIAS,
        EdgeType::DATA_DEF_USE,
        EdgeType::DATA_EQUL_OBJ};

    auto reachedNodes = findNodesTaintedByEdges(n, edges, true);
    for (auto node : reachedNodes)
    {
        if (!node->getValue() || !node->getFunc())
            continue;
        auto func = node->getFunc();
        // skip nodes that are not in driver
        if (!_SDA->isDriverFunc(*func))
            continue;

        if (auto inst = dyn_cast<Instruction>(node->getValue()))
        {
            if (pdgutils::hasWriteAccess(*inst) && !isa<AllocaInst>(inst))
                return true;
        }
    }
    return false;
}

bool pdg::RiskyFieldAnalysis::canParamReachRetVal(pdg::FunctionWrapper &fw)
{
    auto argTreeMap = fw.getArgFormalInTreeMap();
    auto retInsts = fw.getReturnInsts();

    std::set<EdgeType> taintEdges = {
        EdgeType::DATA_ALIAS,
        EdgeType::DATA_DEF_USE,
        EdgeType::DATA_EQUL_OBJ,
        EdgeType::DATA_STORE_TO};

    for (auto retInst : retInsts)
    {
        auto retInstNode = _PDG->getNode(*retInst);
        for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
        {
            auto argTree = iter->second;
            auto rootNode = argTree->getRootNode();
            if (_PDG->canReachIntraproc(*rootNode, *retInstNode, taintEdges))
                return true;
        }
    }

    return false;
}

Function *pdg::RiskyFieldAnalysis::canReachSensitiveOperations(Node &srcFuncNode)
{
    for (auto senOpFuncName : sensitiveOperations)
    {
        auto func = _module->getFunction(StringRef(senOpFuncName));
        if (!func)
            continue;

        auto funcNode = _callGraph->getNode(*func);
        if (!funcNode)
            continue;
        if (_callGraph->canReach(srcFuncNode, *funcNode))
            return func;
    }
    return nullptr;
}

bool pdg::RiskyFieldAnalysis::isDstInstPrecedeOfSrcInst(Node &srcNode, Node &dstNode)
{
    if (!srcNode.getValue() || !dstNode.getValue())
        return false;

    if (auto srcInst = dyn_cast<Instruction>(srcNode.getValue()))
    {
        if (auto dstInst = dyn_cast<Instruction>(dstNode.getValue()))
        {
            if (srcInst->getFunction() == dstInst->getFunction())
            {
                auto srcLineNo = pdgutils::getSourceLineNo(*srcInst);
                auto dstLineNo = pdgutils::getSourceLineNo(*dstInst);
                if (dstLineNo < 0 || srcLineNo < 0)
                    return true;
                if (dstLineNo < srcLineNo)
                    return true;
            }
        }
    }
    return false;
}

void pdg::RiskyFieldAnalysis::populateInterfaceParamTraceInfo(pdg::Node &paramTreeNode, nlohmann::ordered_json &traceJsonObj, Instruction &sinkInst)
{
    // if the source node is a parameter field
    if (TreeNode *paramTN = static_cast<TreeNode *>(&paramTreeNode))
    {
        // print the call site of the function
        Function *kernelBoundaryFunc = paramTN->getTree()->getFunc();
        auto funcCallSites = _callGraph->getFunctionCallSites(*kernelBoundaryFunc);
        std::string drvCallerStr = "";
        std::string callPaths = "";
        std::string drvCallerFuncNames = "";

        for (CallInst *callsite : funcCallSites)
        {
            auto callerFunc = callsite->getFunction();
            if (callerFunc && _SDA->isDriverFunc(*callerFunc) && !pdgutils::isFuncDefinedInHeaderFile(*callerFunc))
            {
                std::string callSiteLocStr = pdgutils::getSourceLocationStr(*callsite);
                std::string callLocStr = "[ " + callerFunc->getName().str() + " | " + callSiteLocStr + " ], ";
                drvCallerStr = drvCallerStr + callLocStr;
                drvCallerFuncNames = drvCallerFuncNames + callerFunc->getName().str() + " ";

                // generate call path from the driver domain that reach the target kernel func
                std::string callPathStr = "";
                auto targetFunc = sinkInst.getFunction();
                auto targetFuncNode = _callGraph->getNode(*targetFunc);
                auto drvFuncNode = _callGraph->getNode(*callerFunc);
                std::vector<Node *> path;
                std::unordered_set<Node *> visited;
                if (_callGraph->findPathDFS(drvFuncNode, targetFuncNode, path, visited))
                {
                    for (size_t i = 0; i < path.size(); ++i)
                    {
                        Node *node = path[i];

                        // Print the node's function name
                        if (Function *f = dyn_cast<Function>(node->getValue()))
                            callPathStr = callPathStr + f->getName().str();

                        if (i < path.size() - 1)
                            callPathStr = callPathStr + "->";
                    }

                    // here, we only consider one valid path
                    if (!callPathStr.empty())
                    {
                        callPaths = callPaths + " [" + callPathStr + "] ";
                        break;
                    }
                }
            }
        }
        traceJsonObj["drv caller (param)"] = drvCallerStr;
        traceJsonObj["kernel_interface_func"] = kernelBoundaryFunc->getName().str();
        traceJsonObj["drv_caller_func_names"] = drvCallerFuncNames;
        traceJsonObj["call path (param)"] = callPaths;
    }
}

void pdg::RiskyFieldAnalysis::populateDrvUpdateLocations(pdg::TreeNode &treeNode, nlohmann::ordered_json &traceJsonObj, Instruction &sinkInst)
{
    std::string drvUpdateLocStr = "";
    raw_string_ostream drvUpdateLocSS(drvUpdateLocStr);
    _SDA->getDriverUpdateLocStr(treeNode, drvUpdateLocSS);
    drvUpdateLocSS.flush();
    traceJsonObj["drv_update_loc(shared field)"] = drvUpdateLocSS.str();

    // compute the call chain from boundary to the target function
    std::string callPathStr = "";
    auto targetFunc = sinkInst.getFunction();
    auto targetFuncNode = _callGraph->getNode(*targetFunc);

    std::string callPaths = "";
    for (auto boundaryFunc : _SDA->getBoundaryFuncs())
    {
        if (_SDA->isDriverFunc(*boundaryFunc))
            continue;
        auto boundaryFuncNode = _callGraph->getNode(*boundaryFunc);
        std::vector<Node *> path;
        std::unordered_set<Node *> visited;
        if (_callGraph->findPathDFS(boundaryFuncNode, targetFuncNode, path, visited))
        {
            for (size_t i = 0; i < path.size(); ++i)
            {
                Node *node = path[i];

                // Print the node's function name
                if (Function *f = dyn_cast<Function>(node->getValue()))
                    callPathStr = callPathStr + f->getName().str();

                if (i < path.size() - 1)
                    callPathStr = callPathStr + "->";
            }

            // here, we only consider one valid path
            if (!callPathStr.empty())
            {
                callPaths = callPaths + " [" + callPathStr + "] ";
                break;
            }
        }
    }
    traceJsonObj["call path (type)"] = callPaths;
}

void pdg::RiskyFieldAnalysis::populatePathChecksInfo(std::vector<std::pair<pdg::Node *, pdg::Edge *>> &taintPath, nlohmann::ordered_json &traceJsonObj)
{
    std::set<EdgeType> ctrlEdge = {EdgeType::CONTROL};
    // obtain path conditions based on control dependences on the tainted ndoes
    std::unordered_set<Node *> totalCtrlNodes;
    for (auto pair : taintPath)
    {
        Node *tn = pair.first;
        auto func = tn->getFunc();
        if (func)
        {
            auto fw = _PDG->getFuncWrapper(*func);
            if (fw)
            {
                if (!fw->hasControlDepBuilt())
                {
                    getAnalysis<ControlDependencyGraph>(*func);
                    fw->setControlDepBuilt();
                }
            }
        }
        auto ctrlDepNodes = findNodesTaintedByEdges(*tn, ctrlEdge, true);
        // erase the starting node
        ctrlDepNodes.erase(ctrlDepNodes.find(tn), ctrlDepNodes.end());
        totalCtrlNodes.insert(ctrlDepNodes.begin(), ctrlDepNodes.end());
    }

    // auto cfgAddrVarNode = cfg.getNode(*addrVarInst);
    // auto cfgTaintVarNode = cfg.getNode(*taintInst);
    // std::set<Value *> conditionVals;
    // cfg.computePathConditionsBetweenNodes(*cfgAddrVarNode, *cfgTaintVarNode, conditionVals);
    traceJsonObj["total_cond_num"] = std::to_string(totalCtrlNodes.size());
    std::string condLocStr = "";

    for (auto ctrlNode : totalCtrlNodes)
    {
        auto ctrlNodeVal = ctrlNode->getValue();
        if (!ctrlNodeVal)
            continue;

        if (Instruction *i = dyn_cast<Instruction>(ctrlNodeVal))
        {
            condLocStr = condLocStr + pdgutils::getSourceLocationStr(*i) + " | ";
        }
    }

    traceJsonObj["total_cond_loc"] = condLocStr;

    bool isControlledPath = true;
    // check if path conditions are all tainted, which indicates a feasible path
    // if path is not controllable, push the JSON to the non trace JSON object
    for (auto ctrlNode : totalCtrlNodes)
    {
        if (!isControlledPath)
            break;

        // check if condition is tainted
        if (!ctrlNode->isTaint())
        {
            isControlledPath = false;
            break;
        }
    }

    if (!isControlledPath)
    {
        traceJsonObj["isControl"] = 0;
    }
    else
    {
        _numControlTaintTrace++;
        traceJsonObj["isControl"] = 1;
    }
}

void pdg::RiskyFieldAnalysis::populateDirectPathChecksInfo(std::vector<std::pair<Node *, Edge *>> &taintPath, pdg::Node &srcNode, pdg::Node &dstNode, nlohmann::ordered_json &traceJsonObj)
{
    std::set<EdgeType> ctrlEdge = {EdgeType::CONTROL};
    std::set<EdgeType> dataEdges = {EdgeType::DATA_ALIAS, EdgeType::DATA_DEF_USE, EdgeType::DATA_EQUL_OBJ, EdgeType::DATA_STORE_TO};

    // obtain path conditions based on control dependences on the tainted ndoes
    std::unordered_set<Node *> totalCtrlNodes;
    for (auto pair : taintPath)
    {
        Node *tn = pair.first;
        auto ctrlDepNodes = findNodesTaintedByEdges(*tn, ctrlEdge, true);
        // erase the starting node
        ctrlDepNodes.erase(ctrlDepNodes.find(tn), ctrlDepNodes.end());
        totalCtrlNodes.insert(ctrlDepNodes.begin(), ctrlDepNodes.end());
    }

    std::string directCtrlDepLocStr = "";
    unsigned numDirectCheck = 0;
    for (auto ctrlNode : totalCtrlNodes)
    {
        auto ctrlNodeVal = ctrlNode->getValue();
        if (!ctrlNodeVal)
            continue;

        if (auto BI = dyn_cast<BranchInst>(ctrlNodeVal))
        {
            if (BI->isUnconditional())
                continue;
            auto condVal = BI->getCondition();
            if (!condVal)
                continue;
            // testing data flow
            if (auto cmpInst = dyn_cast<CmpInst>(condVal))
            {
                for (auto op : cmpInst->operand_values())
                {
                    auto opValNode = _PDG->getNode(*op);
                    if (!opValNode)
                        continue;

                    if (_PDG->canReach(*opValNode, dstNode, dataEdges))
                    {
                        if (auto i = dyn_cast<Instruction>(condVal))
                        {
                            directCtrlDepLocStr = directCtrlDepLocStr + pdgutils::getSourceLocationStr(*i) + " | ";
                            numDirectCheck++;
                        }
                    }
                }
            }
        }
    }

    traceJsonObj["direct_num_cond_checks"] = numDirectCheck;
    traceJsonObj["direct_cond_checks_loc"] = directCtrlDepLocStr;

    if (numDirectCheck == 0)
    {
        _numDirectControlTaintTrace++;
        traceJsonObj["isDirectControl"] = 1;
    }
    else
        traceJsonObj["isDirectControl"] = 0;

    // auto controlDepNodes = _PDG->findNodesReachedByEdges(dstNode, ctrlEdge, true);
    // if (controlDepNodes.size() > 0)
    // {
    //     std::string controlDepLoc = "";
    //     unsigned numCheck = 0;
    //     for (auto cn : controlDepNodes)
    //     {
    //         if (cn == &dstNode)
    //             continue;
    //         if (cn->getValue())
    //         {
    //             if (auto i = dyn_cast<Instruction>(cn->getValue()))
    //             {
    //                 controlDepLoc = controlDepLoc + pdgutils::getSourceLocationStr(*i) + " | ";
    //                 numCheck++;
    //             }
    //         }
    //     }
    //     traceJsonObj["direct_num_cond_checks"] = numCheck;
    //     traceJsonObj["direct_cond_checks_loc"] = controlDepLoc;
    // }
}

// helper and print functions
nlohmann::ordered_json pdg::RiskyFieldAnalysis::generateTraceJsonObj(Node &srcNode, Node &dstNode, std::string accessPathStr, std::string taintType, unsigned caseId, std::set<EdgeType> &taintEdges, TreeNode *tn)
{
    nlohmann::ordered_json traceJsonObj;
    // if both nodes are in the same function, and the dst intruction is ahead of src instruction, this means that
    // the taint edge is backward. This can be caused by pointer alias. We should discard such cases
    if (isDstInstPrecedeOfSrcInst(srcNode, dstNode))
        return traceJsonObj;

    _numTotalTaintTrace++; 
    // first, use cfg to analyze conditions and verify the riksy operation is reachable
    auto &cfg = KSplitCFG::getInstance();
    if (!cfg.isBuild())
        cfg.build(*_module);

    auto sinkInst = cast<Instruction>(dstNode.getValue());

    // create json object for storing traces
    traceJsonObj["id"] = std::to_string(caseId);
    traceJsonObj["risky"] = taintType;
    traceJsonObj["acc_path"] = accessPathStr;

    // if we start tracing from a tree node (parameter)
    if (&srcNode == tn)
    {
        traceJsonObj["src"] = pdgutils::getFuncSourceLocStr(*(tn->getFunc()));
        traceJsonObj["param"] = tn->getTree()->getRootNode()->getSrcName();
    }
    else
    {
        // trace for shared fields
        auto addrVarInst = cast<Instruction>(srcNode.getValue());
        traceJsonObj["src"] = pdgutils::getSourceLocationStr(*addrVarInst);
    }

    traceJsonObj["dst"] = pdgutils::getSourceLocationStr(*sinkInst);
    traceJsonObj["dst_inline"] = pdgutils::getSourceLocationStr(*sinkInst, false);

    auto treeNode = &srcNode;
    if (!treeNode && !tn)
        return traceJsonObj;

    // first, obtain taint path based on data flow
    std::vector<std::pair<Node *, Edge *>> taintPath;
    std::unordered_set<Node *> visited;
    if (_PDG->findPathDFS(&srcNode, &dstNode, taintPath, visited, taintEdges))
    {
        // this will find all the checks along the taint path. Starting from the taint source.
        populatePathChecksInfo(taintPath, traceJsonObj);
        // recursively obtain control dependent nodes from the taint sink inst
        populateDirectPathChecksInfo(taintPath, srcNode, dstNode, traceJsonObj);

        // early terminate if the path is not controlled
        // if (OnlyControlledPath && traceJsonObj["isControl"] != 1 && traceJsonObj["isDirectControl"] != 1)
        //     return traceJsonObj;
    }

    populateInterfaceParamTraceInfo(*treeNode, traceJsonObj, *sinkInst);
    // if the taint source is a shared field, obtain where in driver this field is
    // updated.

    // add driver update locations for fields
    if (tn)
        populateDrvUpdateLocations(*tn, traceJsonObj, *sinkInst);

    // if all the conditions are tainted, we proceed to compute the taints
    // std::string taintTraceStr = "";
    // raw_string_ostream ss(taintTraceStr);
    // _PDG->convertPathToString(taintPath, ss);
    // ss.flush();
    // traceJsonObj["t_trace"] = ss.str();
    traceJsonObj["isTrue"] = "-";
    traceJsonObj["atk_reason"] = "";
    traceJsonObj["defense"] = "";
    // taintTracesJson.push_back(traceJsonObj);
    return traceJsonObj;
}

void pdg::RiskyFieldAnalysis::printRiskyFieldInfo(raw_ostream &os, const std::string &category, pdg::TreeNode &treeNode, Function &func, Instruction &inst)
{
    os.changeColor(raw_ostream::RED);
    os << "--- [" << category << "] --- ";
    os.resetColor();
    os << treeNode.getSrcHierarchyName(false) << " in func " << func.getName().str() << "\n";
    pdg::pdgutils::printSourceLocation(inst);
}

void pdg::RiskyFieldAnalysis::printFieldClassificationTaint()
{
    unsigned numKernelBoundaryFunc = 0;
    unsigned numDrvBoundaryFunc = 0;
    for (auto f : _SDA->getBoundaryFuncs())
    {
        if (_SDA->isDriverFunc(*f))
            numDrvBoundaryFunc++;
        else
            numKernelBoundaryFunc++;
    }

    nlohmann::ordered_json drvGeneralStats;
    drvGeneralStats["Num kernel  boundary func"] = numKernelBoundaryFunc;
    drvGeneralStats["Num boundary parameters"] = _numBoundaryArg;
    drvGeneralStats["Num classified boundary parameters"] = _numClassifiedBoundaryArg;
    drvGeneralStats["Num boundary parameter fields"] = _numBoundaryFields;
    drvGeneralStats["Num classified boundary parameter fields"] = _numClassifiedBoundaryFields;
    drvGeneralStats["Num drv callbacks"] = numDrvBoundaryFunc;
    drvGeneralStats["Num shared struct"] = _SDA->getGlobalStructDTMap().size();
    drvGeneralStats["Shared fields"] = _numSharedFields;
    drvGeneralStats["KRDU fields"] = _numKernelReadDriverUpdatedFields;
    drvGeneralStats["ptr fields"] = numPtrField;
    drvGeneralStats["func ptr fields"] = numFuncPtrField;
    drvGeneralStats["data ptr fields"] = numDataPtrField;
    drvGeneralStats["total taint path"] = _numTotalTaintTrace;
    drvGeneralStats["total taint controlled path"] = _numControlTaintTrace;
    drvGeneralStats["total direct controlled path"] = _numDirectControlTaintTrace;

    for (auto it = totalRiskyFieldCounters.begin(); it != totalRiskyFieldCounters.end(); ++it)
    {
        auto typeStr = taintutils::riskyDataTypeToString(it->first);
        drvGeneralStats[typeStr] = it->second;
    }

    for (auto it = totalRiskyParamCounters.begin(); it != totalRiskyParamCounters.end(); ++it)
    {
        auto typeStr = "PARAM_" + taintutils::riskyDataTypeToString(it->first);
        drvGeneralStats[typeStr] = it->second;
    }

    taintutils::printJsonToFile(drvGeneralStats, "GeneralRiskyDataStat.json");
}

void pdg::RiskyFieldAnalysis::printBoundaryStructFieldsClassificationStats()
{
    unsigned totalFields = 0;
    unsigned totalClassifiedFields = 0;
    unsigned totalKRDUFields = 0;
    std::map<RiskyDataType, int> riskyClassCountMap;

    for (auto iter : _sharedStructTypeRiskyCounts)
    {
        auto jsonObj = iter.second;
        auto structTypeName = jsonObj["Struct"];
        totalFields += jsonObj["No.Fields"].get<int>();
        totalKRDUFields += jsonObj["No.KRDU fields"].get<int>();
        totalClassifiedFields += jsonObj["No.classified fields"].get<int>();

        if (_fieldRiskyTypeMap.find(structTypeName) != _fieldRiskyTypeMap.end())
        {
            for (auto iter : _fieldRiskyTypeMap[structTypeName])
            {
                auto riskyClass = iter.first;
                auto riskyClassFields = iter.second;
                std::string riskyClassStr = pdgutils::riskyDataTypeToString(riskyClass);
                riskyClassCountMap[riskyClass] = riskyClassCountMap[riskyClass] + riskyClassFields.size();
                if (!riskyClassStr.empty())
                    jsonObj[riskyClassStr] = std::to_string(riskyClassFields.size());
            }
        }
        taintutils::printJsonToFile(jsonObj, "BoundaryStructFieldsStats.json");
    }

    // print aggregate stats
    nlohmann::ordered_json overallStatObj;
    overallStatObj["Shared Struct"] = _sharedStructTypeRiskyCounts.size();
    overallStatObj["Shared Fields"] = totalFields;
    overallStatObj["KRDU Fields"] = totalKRDUFields;
    overallStatObj["Classified Fields"] = totalClassifiedFields;
    overallStatObj["Non-Classified Fields"] = totalKRDUFields - totalClassifiedFields;
    for (auto iter : riskyClassCountMap)
    {
        auto riskyClassStr = pdgutils::riskyDataTypeToString(iter.first);
        overallStatObj[riskyClassStr] = iter.second;
    }
    taintutils::printJsonToFile(overallStatObj, "BoundaryStructFieldsStats.json");
}

static RegisterPass<pdg::RiskyFieldAnalysis>
    RiskyFieldAnalysis("risky-field", "Risky Field Analysis", false, true);