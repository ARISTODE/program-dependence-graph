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

void pdg::RiskyFieldAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.addRequired<SharedDataAnalysis>();
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
    if (!dir.empty() && !sys::fs::exists(status) || !sys::fs::is_directory(status))
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
    std::error_code EC;
    riskyFieldOS = new raw_fd_ostream("RiskyField.log", EC, sys::fs::OF_Text);
    if (EC)
    {
        delete riskyFieldOS;
        errs() << "cannot open RiskyField.log\n";
        return false;
    }

    riskyFieldTaintOS = new raw_fd_ostream("RiskyFieldTaint.log", EC, sys::fs::OF_Text);
    if (EC)
    {
        delete riskyFieldTaintOS;
        errs() << "cannot open RiskyField.log\n";
        return false;
    }

    unsigned caseId = 0;

    auto globalStructDTMap = _SDA->getGlobalStructDTMap();
    
    // first step, propagate taint, this is used to 
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

            auto addrVars = n->getAddrVars();
            auto nodeType = n->getDIType();
            std::set<EdgeType> taintEdges = {};
            if (dbgutils::isPointerType(*nodeType))
            {
                taintEdges = {
                    EdgeType::DATA_ALIAS,
                    EdgeType::PARAMETER_IN,
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

            for (auto addrVar : addrVars)
            {
                auto addrVarNode = _PDG->getNode(*addrVar);
                auto taintNodes = _PDG->findNodesReachedByEdges(*addrVarNode, taintEdges);
                for (auto taintNode : taintNodes)
                {
                    taintNode->setTaint();
                }
            }
        }
    }

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
            // classify the risky field into different classes
            if (n->isShared)
            {
                // per struct shared field count
                numSharedFields++;
                // increase the total shared field count
                _numSharedFields++;
            }

            if (isDriverControlledField(*n))
            {
                _numKernelReadDriverUpdatedFields++;
                numKRDUFields++;
                std::set<RiskyDataType> riskyClassifications;
                classifyRiskyField(*n, riskyClassifications, taintJsonObjs, caseId);
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
                caseId++;
            }
        }
        // propagate struct in JSON format
        structStatJson["No.Fields"] = numFields;
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
        taintutils::printJsonToFile(taintJsonObjs, "perStructTaint.json");
    }

    // TODO: taint the return value of driver interface functions
    // classify the taint based on the data directly passed across the isolation boundary

    auto kernelAPIs = readFuncsFromFile("imported_funcs", M, "boundaryFiles");

    // propagate taints from the parameters
    for (auto func : kernelAPIs)
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

            auto taintNodes = _PDG->findNodesReachedByEdges(*rootNode, taintEdges);
            for (auto taintNode : taintNodes)
            {
                taintNode->setTaint();
            }
        }
    }

    for (auto func : kernelAPIs)
    {
        if (_SDA->isDriverFunc(*func))
            continue;

        auto funcWrapper = _PDG->getFuncWrapper(*func);
        if (!funcWrapper)
            continue;

        auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
        // record number of boundary args
        for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
        {
            auto argTree = iter->second;
            auto rootNode = argTree->getRootNode();
            auto argDIType = rootNode->getDIType();
            _numBoundaryArg++;
            // struct and struct fields are covered by type taint
            if (argDIType && dbgutils::isStructPointerType(*argDIType))
                continue;
            _numNonStructBoundaryArg++;
            // if ptr is not updated in driver, no need to analyze it
            if (dbgutils::isPointerType(*argDIType) && !hasUpdateInDrv(*rootNode))
                continue;

            nlohmann::ordered_json taintJsonObjs = nlohmann::ordered_json::array();
            std::set<RiskyDataType> riskyClassifications;
            classifyRiskyField(*rootNode, riskyClassifications, taintJsonObjs, caseId);

            // update the total counter
            updateRiskyParamCounters(riskyClassifications);
            // record unclassified fields
            if (riskyClassifications.empty())
            {
                totalRiskyParamCounters[RiskyDataType::OTHER]++;
            }

            caseId++;
            taintutils::printJsonToFile(taintJsonObjs, "boundaryParamTaint.json");
        }
    }

    // check return value of driver exported functions
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
                classifyRiskyField(*actualTN, retRiskyClassifications, retTaintJsonObjs, caseId);

                // update the total counter
                updateRiskyParamCounters(retRiskyClassifications);

                if (retRiskyClassifications.empty())
                {
                    totalRiskyParamCounters[RiskyDataType::OTHER]++;
                }
                taintutils::printJsonToFile(retTaintJsonObjs, "retBoundaryParamTaint.json");
            }
        }
        caseId++;
    }

    printFieldClassificationTaint(*riskyFieldOS);

    riskyFieldTaintOS->close();
    return false;
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

bool pdg::RiskyFieldAnalysis::isDriverControlledField(TreeNode &tn)
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
                    driverReadTimes++;
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
bool pdg::RiskyFieldAnalysis::classifyRiskyPtrField(TreeNode &tn, std::set<pdg::RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs, unsigned &caseID)
{
    // record the field name in struct->fieldname format
    std::string accessPathStr = tn.getSrcHierarchyName(false);
    // obtain the address variables representing the field
    auto addrVars = tn.getAddrVars();
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
        for (auto addrVar : addrVars)
        {
            auto addrVarNode = _PDG->getNode(*addrVar);
        }
        return true;
    }

    // if not func ptr, we can conclude this is a data ptr
    numDataPtrField += 1;

    // define taint edges
    std::set<EdgeType> taintEdges = {
        EdgeType::DATA_ALIAS,
        EdgeType::PARAMETER_IN,
        EdgeType::DATA_DEF_USE,
        EdgeType::DATA_EQUL_OBJ};

    // classify for other ptr type
    for (auto addrVar : addrVars)
    {
        // only focus on the use on the kernel side
        auto addrVarInst = cast<Instruction>(addrVar);
        auto func = addrVarInst->getFunction();
        if (!_SDA->isKernelFunc(*func) || !pdgutils::hasReadAccess(*addrVar))
            continue;

        // for pointer type node, find all the aliasing, and pointer derived from them
        auto addrVarNode = _PDG->getNode(*addrVar);
        auto taintNodes = _PDG->findNodesReachedByEdges(*addrVarNode, taintEdges);
        
        // classify based on taint node
        for (auto taintNode : taintNodes)
        {
            auto taintVal = taintNode->getValue();
            if (!taintVal)
                continue;

            if (auto taintInst = dyn_cast<Instruction>(taintVal))
            {
                // skip driver uses in functions
                if (_SDA->isDriverFunc(*taintInst->getFunction()))
                    continue;
            }

            // check for ptr read
            if (riskyClassifications.find(RiskyDataType::PTR_READ) == riskyClassifications.end() && taintutils::isPointerRead(*taintNode))
            {
                riskyClassifications.insert(RiskyDataType::PTR_READ);
                auto traceJsonObj = generateTraceJsonObj(*addrVarNode, *taintNode, accessPathStr, "ptr-read", caseID, taintEdges, &tn);
                taintJsonObjs.push_back(traceJsonObj);
                classified = true;
            }
            // check for write through ptr
            if (riskyClassifications.find(RiskyDataType::PTR_WRTIE) == riskyClassifications.end() && taintutils::isPointeeModified(*taintNode))
            {
                riskyClassifications.insert(RiskyDataType::PTR_WRTIE);
                auto traceJsonObj = generateTraceJsonObj(*addrVarNode, *taintNode, accessPathStr, "ptr-write", caseID, taintEdges, &tn);
                taintJsonObjs.push_back(traceJsonObj);
                classified = true;
            }

            // check if the ptr could affect a bracnh in the kernel, also check if the branch contains risky operations
            std::string senOpName = "";
            if (riskyClassifications.find(RiskyDataType::CONTROL_VAR) == riskyClassifications.end() && taintutils::isValueInSensitiveBranch(*taintNode, senOpName))
            {
                riskyClassifications.insert(RiskyDataType::CONTROL_VAR);
                std::string s = "ptr-sen-branch (" + senOpName + ")";
                auto traceJsonObj = generateTraceJsonObj(*addrVarNode, *taintNode, accessPathStr, s, caseID, taintEdges, &tn);
                taintJsonObjs.push_back(traceJsonObj);
                // TODO: check if the branch operation is risky, if so, add the risky operation info to the json
                classified = true;
            }

            //  check if th e ptr is used in sensitive kernel APIS, such as memory copying, or memory management etc
            senOpName = "";
            if (riskyClassifications.find(RiskyDataType::RISKY_KERNEL_FUNC) == riskyClassifications.end() && taintutils::isValueInSensitiveAPI(*taintNode, senOpName))
            {
                riskyClassifications.insert(RiskyDataType::RISKY_KERNEL_FUNC);
                std::string s = "ptr-sen-api (" + senOpName + ")";
                auto traceJsonObj = generateTraceJsonObj(*addrVarNode, *taintNode, accessPathStr, s, caseID, taintEdges, &tn);
                taintJsonObjs.push_back(traceJsonObj);
                classified = true;
            }
        }
    }

    return classified;
}

// classify Risky non-pointer type fields
bool pdg::RiskyFieldAnalysis::classifyRiskyNonPtrField(TreeNode &tn, std::set<pdg::RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs, unsigned &caseID)
{
    // record the field name in struct->fieldname format
    std::string accessPathStr = tn.getSrcHierarchyName(false);
    // obtain the address variables representing the field
    auto addrVars = tn.getAddrVars();
    auto fieldDIType = tn.getDIType();
    bool classified = false;

    // define taint edges
    std::set<EdgeType> taintEdges = {
        EdgeType::PARAMETER_IN,
        EdgeType::DATA_DEF_USE,
        EdgeType::DATA_EQUL_OBJ,
        EdgeType::DATA_STORE_TO};

    // classify for non-ptr type
    for (auto addrVar : addrVars)
    {
        auto addrVarInst = cast<Instruction>(addrVar);
        // only focus on the use on the kernel side
        auto func = addrVarInst->getFunction();
        if (!_SDA->isKernelFunc(*func) || !pdgutils::hasReadAccess(*addrVar))
            continue;
        // for pointer type node, find all the aliasing, and pointer derived from them
        auto addrVarNode = _PDG->getNode(*addrVar);
        auto taintNodes = _PDG->findNodesReachedByEdges(*addrVarNode, taintEdges);

        // set the taints for all the tainted nodes
        // for (auto taintNode : taintNodes)
        // {
        //     taintNode->setTaint();
        // }

        for (auto taintNode : taintNodes)
        {
            auto taintVal = taintNode->getValue();
            if (!taintVal)
                continue;

            // skip taints in driver functions
            if (auto taintInst = dyn_cast<Instruction>(taintVal))
            {
                // skip driver uses in functions
                if (_SDA->isDriverFunc(*taintInst->getFunction()))
                    continue;
            }

            // check if value used as array index or operand of ptr arith
            if (riskyClassifications.find(RiskyDataType::ARR_IDX) == riskyClassifications.end() && taintutils::isUsedAsArrayIndex(*taintNode))
            {
                riskyClassifications.insert(RiskyDataType::ARR_IDX);
                auto traceJsonObj = generateTraceJsonObj(*addrVarNode, *taintNode, accessPathStr, "arr-idx", caseID, taintEdges, &tn);
                taintJsonObjs.push_back(traceJsonObj);
                classified = true;
            }

            // check if value is used in ptr arithmetic
            if (riskyClassifications.find(RiskyDataType::DIV_BY_ZERO) == riskyClassifications.end() && taintutils::isValUsedInDivByZero(*taintNode))
            {
                riskyClassifications.insert(RiskyDataType::DIV_BY_ZERO);
                auto traceJsonObj = generateTraceJsonObj(*addrVarNode, *taintNode, accessPathStr, "div-by-zero", caseID, taintEdges, &tn);
                taintJsonObjs.push_back(traceJsonObj);
                classified = true;
            }

            // check if value is used in kernel branch
            // check if the ptr could affect a bracnh in the kernel, also check if the branch contains risky operations
            std::string senOpName = "";
            if (riskyClassifications.find(RiskyDataType::CONTROL_VAR) == riskyClassifications.end() && taintutils::isValueInSensitiveBranch(*taintNode, senOpName))
            {
                riskyClassifications.insert(RiskyDataType::CONTROL_VAR);
                // TODO: check if the branch operation is risky, if so, add the risky operation info to the json
                std::string s = "val-sen-branch (" + senOpName + ")";
                auto traceJsonObj = generateTraceJsonObj(*addrVarNode, *taintNode, accessPathStr, s, caseID, taintEdges, &tn);
                taintJsonObjs.push_back(traceJsonObj);
                classified = true;
            }

            //  check if th e ptr is used in sensitive kernel APIS, such as memory copying, or memory management etc
            senOpName = "";
            if (riskyClassifications.find(RiskyDataType::RISKY_KERNEL_FUNC) == riskyClassifications.end() && taintutils::isValueInSensitiveAPI(*taintNode, senOpName))
            {
                riskyClassifications.insert(RiskyDataType::RISKY_KERNEL_FUNC);
                std::string s = "val-sen-api (" + senOpName + ")";
                auto traceJsonObj = generateTraceJsonObj(*addrVarNode, *taintNode, accessPathStr, s, caseID, taintEdges, &tn);
                taintJsonObjs.push_back(traceJsonObj);
                classified = true;
            }
        }
    }

    return classified;
}

void pdg::RiskyFieldAnalysis::classifyRiskyField(TreeNode &tn, std::set<pdg::RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs, unsigned &caseID)
{
    // obtain the address variables representing the field
    bool classified = false;
    auto fieldDIType = tn.getDIType();
    bool isPtrFieldClassified = false;
    bool isValFieldClassified = false;

    if (dbgutils::isPointerType(*fieldDIType))
    {
        // classify for pointer type fields
        isPtrFieldClassified = classifyRiskyPtrField(tn, riskyClassifications, taintJsonObjs, caseID);
    }
    else
    {
        // classify for non-pointer type fields
        isValFieldClassified = classifyRiskyNonPtrField(tn, riskyClassifications, taintJsonObjs, caseID);
    }

    // unclassified field
    if (!isPtrFieldClassified && !isValFieldClassified)
    {
        nlohmann::ordered_json traceJson;
        traceJson["id"] = caseID;
        traceJson["acc_path"] = tn.getSrcHierarchyName(false);

        std::string readLocs = "";
        std::string updateLocs = "";
        for (auto addrVar : tn.getAddrVars())
        {
            if (auto inst = dyn_cast<Instruction>(addrVar))
            {
                auto f = inst->getFunction();
                // record driver update locations
                if (_SDA->isDriverFunc(*f) && pdgutils::hasWriteAccess(*inst))
                {
                    std::string drvUpdateLoc = pdgutils::getSourceLocationStr(*inst);
                    updateLocs = updateLocs + " [" + drvUpdateLoc + "], ";
                }

                // record kernel read locations
                if (!_SDA->isDriverFunc(*f) && pdgutils::hasReadAccess(*inst))
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
        taintutils::printJsonToFile(traceJson, "unclassifiedFields.json");
    }
}

bool pdg::RiskyFieldAnalysis::hasUpdateInDrv(pdg::TreeNode &n)
{
    std::set<EdgeType> edges = {
        EdgeType::PARAMETER_IN,
        EdgeType::DATA_ALIAS,
        EdgeType::DATA_DEF_USE,
        EdgeType::DATA_EQUL_OBJ};

    auto treeNodeFunc = n.getTree()->getFunc();

    auto reachedNodes = _PDG->findNodesReachedByEdges(n, edges, true);
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

// helper and print functions
nlohmann::ordered_json pdg::RiskyFieldAnalysis::generateTraceJsonObj(Node &srcNode, Node &dstNode, std::string accessPathStr, std::string taintType, unsigned caseId, std::set<EdgeType> &taintEdges, TreeNode *tn)
{
    // first, use cfg to analyze conditions and verify the riksy operation is reachable
    auto &cfg = KSplitCFG::getInstance();
    if (!cfg.isBuild())
        cfg.build(*_module);

    auto addrVarInst = cast<Instruction>(srcNode.getValue());
    auto taintInst = cast<Instruction>(dstNode.getValue());

    // create json object for storing traces
    nlohmann::ordered_json traceJsonObj;
    traceJsonObj["id"] = std::to_string(caseId);
    traceJsonObj["risky"] = taintType;
    traceJsonObj["acc_path"] = accessPathStr;
    traceJsonObj["src"] = pdgutils::getSourceLocationStr(*addrVarInst);
    traceJsonObj["dst"] = pdgutils::getSourceLocationStr(*taintInst);

    auto parameterTreeNode = srcNode.getAbstractTreeNode();

    if (!parameterTreeNode && !tn)
        return traceJsonObj;

    // if the source node is a parameter field
    if (parameterTreeNode)
    {
        if (TreeNode *tn = static_cast<TreeNode *>(parameterTreeNode))
        {
            // print the call site of the function
            Function *kernelBoundaryFunc = tn->getTree()->getFunc();
            auto funcCallSites = _callGraph->getFunctionCallSites(*kernelBoundaryFunc);
            std::string drvCallerStr = "";
            std::string callPaths = "";

            for (CallInst *callsite : funcCallSites)
            {
                auto callerFunc = callsite->getFunction();
                if (callerFunc && _SDA->isDriverFunc(*callerFunc) && !pdgutils::isFuncDefinedInHeaderFile(*callerFunc))
                {
                    std::string callSiteLocStr = pdgutils::getSourceLocationStr(*callsite);
                    std::string callLocStr = "[ " + callerFunc->getName().str() + " | " + callSiteLocStr + " ], ";
                    drvCallerStr = drvCallerStr + callLocStr;

                    // generate call path from the driver domain that reach the target kernel func

                    std::string callPathStr = "";
                    auto targetFunc = taintInst->getFunction();
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
            traceJsonObj["call path (param)"] = callPaths;
        }
    }

    // add driver update locations for fields
    if (tn)
    {
        std::string drvUpdateLocStr = "";
        raw_string_ostream drvUpdateLocSS(drvUpdateLocStr);
        _SDA->getDriverUpdateLocStr(*tn, drvUpdateLocSS);
        drvUpdateLocSS.flush();
        traceJsonObj["drv_update loc (shared field)"] = drvUpdateLocSS.str();

        // compute the call chain from boundary to the target function
        std::string callPathStr = "";
        auto targetFunc = taintInst->getFunction();
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


    // recursively obtain control dependent nodes from the taint sink inst
    std::set<EdgeType> ctrlEdge = {EdgeType::CONTROL};
    auto controlDepNodes = _PDG->findNodesReachedByEdges(dstNode, ctrlEdge, true);
    if (controlDepNodes.size() > 0)
    {
        std::string controlDepLoc = "";
        unsigned numCheck = 0;
        for (auto cn : controlDepNodes)
        {
            if (cn == &dstNode)
                continue;
            if (cn->getValue())
            {
                if (auto i = dyn_cast<Instruction>(cn->getValue()))
                {
                    controlDepLoc = controlDepLoc + pdgutils::getSourceLocationStr(*i) + " | ";
                    numCheck++;
                }
            }
        }
        traceJsonObj["num condition checks"] = numCheck;
        traceJsonObj["condition checks"] = controlDepLoc;
    }

    // obtain path conditions based on control dependences on the tainted ndoes
    // first, obtain taint path based on data flow
    std::vector<std::pair<Node *, Edge *>> taintPath;
    std::unordered_set<Node *> visited;
    std::unordered_set<Node *> totalCtrlNodes;

    if (_PDG->findPathDFS(&srcNode, &dstNode, taintPath, visited, taintEdges))
    {
        for (auto pair : taintPath)
        {
            Node* tn = pair.first;
            auto ctrlDepNodes = _PDG->findNodesReachedByEdges(*tn, ctrlEdge, true);
            // erase the starting node 
            ctrlDepNodes.erase(ctrlDepNodes.find(tn), ctrlDepNodes.end());
            totalCtrlNodes.insert(ctrlDepNodes.begin(), ctrlDepNodes.end());
        }
    }


    // auto cfgAddrVarNode = cfg.getNode(*addrVarInst);
    // auto cfgTaintVarNode = cfg.getNode(*taintInst);
    // std::set<Value *> conditionVals;
    // cfg.computePathConditionsBetweenNodes(*cfgAddrVarNode, *cfgTaintVarNode, conditionVals);
    traceJsonObj["cond_num"] = std::to_string(totalCtrlNodes.size());
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

    traceJsonObj["cond_loc"] = condLocStr;

    bool isControlledPath = true;
    // check if path conditions are all tainted, which indicates a feasible path
    // if path is not controllable, push the JSON to the non trace JSON object
    for (auto ctrlNode : totalCtrlNodes)
    {
        if (!isControlledPath)
            break;
        
        bool isCurBranchTaint = false;

        // check if condition is tainted
        if (!ctrlNode->isTaint())
        {
            isControlledPath = false;
            break;
        }
    }

    if (!isControlledPath)
    {
        traceJsonObj["isControl"] = "0";
        taintTracesJsonNoConds.push_back(traceJsonObj);
        return traceJsonObj;
    }
    else
        traceJsonObj["isControl"] = "1";

    numControlTaintTrace++;

    // if all the conditions are tainted, we proceed to compute the taints
    std::string taintTraceStr = "";
    raw_string_ostream ss(taintTraceStr);
    _PDG->convertPathToString(taintPath, ss);
    ss.flush();
    traceJsonObj["t_trace"] = ss.str();

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
    os << treeNode.getSrcHierarchyName(false) << " in func " << func.getName() << "\n";
    pdg::pdgutils::printSourceLocation(inst);
}

void pdg::RiskyFieldAnalysis::printFieldClassificationTaint(raw_fd_ostream &OS)
{
    // OS << "Number of kernel read driver updated fields: " << numKernelReadDriverUpdatedFields << "\n";
    // OS << "Number of pointer fields: " << numPtrField << "\n";
    // OS << "\tNumber of function pointer fields: " << numFuncPtrField << "\n";
    // OS << "\tNumber of data pointer fields: " << numDataPtrField << "\n";
    // OS << "\t\tNo.pointer arithmetic pointer fields (Taint): " << numPtrArithPtrFieldTaint << "\n";
    // OS << "\t\tNo.dereference pointer fields (Taint): " << numDereferencePtrFieldTaint << "\n";
    // OS << "\t\tNo.sensitive operation pointer fields (Taint): " << numSensitiveOpPtrFieldTaint << "\n";
    // OS << "\t\tNo.branch pointer fields (Taint): " << numBranchPtrFieldTaint << "\n";
    // OS << "No.array index fields (Taint): " << numArrayIdxFieldTaint << "\n";
    // OS << "No.arith op fields (Taint): " << numArithFieldTaint << "\n";
    // OS << "No.sensitive branch fields (Taint): " << numSensitiveBranchFieldTaint << "\n";
    // OS << "No.sensitive operation fields (Taint): " << numSensitiveOpsFieldTaint << "\n";
    // OS << "No.unclassified fields (Taint): " << numUnclassifiedFieldTaint << "\n";
    // OS << "No.unclassified func ptr fields (Taint): " << numUnclassifiedFuncPtrFieldTaint << "\n";
    // OS << "No.kernel API params: " << numKernelAPIParam << "\n";
    // OS << "No.control taint trace: " << numControlTaintTrace << "\n";

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
    drvGeneralStats["Num non-struct boundary parameters"] = _numNonStructBoundaryArg;
    drvGeneralStats["Num drv callbacks"] = numDrvBoundaryFunc;
    drvGeneralStats["Num shared struct"] = _SDA->getGlobalStructDTMap().size();
    drvGeneralStats["Shared fields"] = _numSharedFields;
    drvGeneralStats["KRDU fields"] = _numKernelReadDriverUpdatedFields;
    drvGeneralStats["ptr fields"] = numPtrField;
    drvGeneralStats["func ptr fields"] = numFuncPtrField;
    drvGeneralStats["data ptr fields"] = numDataPtrField;

    for (auto it = totalRiskyFieldCounters.begin(); it != totalRiskyFieldCounters.end(); ++it)
    {
        auto typeStr = taintutils::riskyDataTypeToString(it->first);
        drvGeneralStats[typeStr] = it->second;
    }
    taintutils::printJsonToFile(drvGeneralStats, "riskyDataStat.json");

    // nlohmann::ordered_json boundaryParamStatJson;
    // boundaryParamStatJson["num boundary arg"] = _numBoundaryArg;
    // for (auto it = totalRiskyParamCounters.begin(); it != totalRiskyParamCounters.end(); ++it)
    // {
    //     auto typeStr = taintutils::riskyDataTypeToString(it->first);
    //     boundaryParamStatJson[typeStr] = it->second;
    // }

    // taintutils::printJsonToFile(boundaryParamStatJson, "riskyDataStat.json");
}

static RegisterPass<pdg::RiskyFieldAnalysis>
    RiskyFieldAnalysis("risky-field", "Risky Field Analysis", false, true);