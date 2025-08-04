#include "RiskyFieldAnalysis.hh"
#include "KSplitCFG.hh"

// Constants for sensitive operations and configurations
namespace {
    const std::unordered_set<std::string> SENSITIVE_OPERATIONS = {
        "kmalloc", "vmalloc", "kzalloc", "vzalloc",
        "kmem_cache_create", "kmem_cache_alloc", "kmem_cache_free", "kmem_cache_destroy",
        "kfree", "vfree", "copy_from_user", "copy_to_user",
        "memcpy", "strcpy", "strncpy", "memset",
        "kobject_put", "kobject_create_and_add", "mod_timer"
    };

    const std::string GITLAB_PREFIX = "https://gitlab.flux.utah.edu/xcap/xcap-capability-linux/-/blob/llvm_v4.8/";
    
    // Edge type sets for different analyses
    const std::set<pdg::EdgeType> POINTER_TAINT_EDGES = {
        pdg::EdgeType::DATA_ALIAS,
        pdg::EdgeType::PARAMETER_IN,
        pdg::EdgeType::DATA_STORE_TO,
        pdg::EdgeType::DATA_DEF_USE,
        pdg::EdgeType::DATA_EQUL_OBJ
    };

    const std::set<pdg::EdgeType> NON_POINTER_TAINT_EDGES = {
        pdg::EdgeType::PARAMETER_IN,
        pdg::EdgeType::DATA_DEF_USE,
        pdg::EdgeType::DATA_EQUL_OBJ,
        pdg::EdgeType::DATA_STORE_TO
    };

    const std::set<pdg::EdgeType> CONTROL_EDGES = {pdg::EdgeType::CONTROL};
}

char pdg::RiskyFieldAnalysis::ID = 0;
using namespace llvm;

cl::opt<bool, true> ECTP("controlled-taint-path", cl::desc("only select controlled taint path"), 
    cl::value_desc("controlled_taint_path"), cl::location(pdg::OnlyControlledPath), cl::init(true));
bool pdg::OnlyControlledPath;

void pdg::RiskyFieldAnalysis::getAnalysisUsage(AnalysisUsage &AU) const {
    AU.addRequired<DataAccessAnalysis>();
    AU.addRequired<ControlDependencyGraph>();
    AU.setPreservesAll();
}

std::set<Function *> readFuncsFromFile(std::string fileName, Module &M, std::string dir) {
    std::set<Function *> ret;
    sys::fs::file_status status;
    sys::fs::status("boundaryFiles", status);
    
    if ((!dir.empty() && !sys::fs::exists(status)) || !sys::fs::is_directory(status)) {
        errs() << "boundary files don't exist, please run boundary analysis pass (-output-boundary-info) first\n";
        return ret;
    }

    std::string filePath = dir + "/" + fileName;
    std::ifstream ReadFile(filePath);
    for (std::string line; std::getline(ReadFile, line);) {
        if (Function *f = M.getFunction(StringRef(line))) {
            ret.insert(f);
        }
    }
    return ret;
}

bool pdg::RiskyFieldAnalysis::runOnModule(Module &M) {
    _module = &M;
    _DAA = &getAnalysis<DataAccessAnalysis>();
    _SDA = _DAA->getSDA();
    _PDG = _SDA->getPDG();
    _callGraph = &PDGCallGraph::getInstance();

    auto kernelInterfaceAPIs = readFuncsFromFile("imported_funcs", M, "boundaryFiles");
    
    // Step 1: Propagate taints for branch checking
    errs() << "[CIV Analysis]: propagating taints\n";
    propagateTaints(kernelInterfaceAPIs);

    // Step 2: Classify parameters passed directly from the interface
    errs() << "[CIV Analysis]: classifying risky data for boundary params\n";
    classifyRiskyBoundaryParams(kernelInterfaceAPIs);

    // Step 3: Check return value of driver exported functions
    errs() << "[CIV Analysis]: classifying risky data for drv callbacks\n";
    classifyRetErrorCode(kernelInterfaceAPIs);
    
    // Print results
    printFieldClassificationTaint();
    printBoundaryStructFieldsClassificationStats();
    
    return false;
}

std::unordered_set<pdg::Node *> pdg::RiskyFieldAnalysis::findNodesTaintedByEdges(
    Node &src, const std::set<EdgeType> &edgeTypes, bool isBackward) {
    
    std::unordered_set<Node *> ret;
    std::queue<Node *> nodeQueue;
    std::unordered_set<Node *> visited;
    
    nodeQueue.push(&src);
    
    while (!nodeQueue.empty()) {
        Node *currentNode = nodeQueue.front();
        nodeQueue.pop();
        
        if (visited.find(currentNode) != visited.end())
            continue;
            
        visited.insert(currentNode);
        ret.insert(currentNode);

        Node::EdgeSet edgeSet = isBackward ? 
            currentNode->getInEdgeSet() : currentNode->getOutEdgeSet();
        
        for (auto edge : edgeSet) {
            if (edgeTypes.find(edge->getEdgeType()) == edgeTypes.end())
                continue;

            Node *nextNode = isBackward ? edge->getSrcNode() : edge->getDstNode();
            nodeQueue.push(nextNode);
        }
    }

    return ret;
}

void pdg::RiskyFieldAnalysis::propagateTaints(std::set<Function *> &kernelInterfaceAPIs) {
    propagateTaintsFromSharedStructs();
    propagateTaintsFromKernelInterfaces(kernelInterfaceAPIs);
}

void pdg::RiskyFieldAnalysis::propagateTaintsFromSharedStructs() {
    auto globalStructDTMap = _SDA->getGlobalStructDTMap();
    for (auto &[_, typeTree] : globalStructDTMap) {
        std::queue<TreeNode *> nodeQueue;
        nodeQueue.push(typeTree->getRootNode());
        
        while (!nodeQueue.empty()) {
            TreeNode *n = nodeQueue.front();
            nodeQueue.pop();
            
            if (!n->getDIType())
                continue;

            for (auto childNode : n->getChildNodes()) {
                nodeQueue.push(childNode);
            }

            if (!n->isShared)
                continue;

            auto taintEdges = dbgutils::isPointerType(*n->getDIType()) ? 
                POINTER_TAINT_EDGES : NON_POINTER_TAINT_EDGES;

            for (auto addrVar : n->getAddrVars()) {
                if (auto addrVarNode = _PDG->getNode(*addrVar)) {
                    auto taintNodes = findNodesTaintedByEdges(*addrVarNode, taintEdges);
                    for (auto taintNode : taintNodes) {
                        taintNode->setTaint();
                    }
                }
            }
        }
    }
}

void pdg::RiskyFieldAnalysis::propagateTaintsFromKernelInterfaces(std::set<Function *> &kernelInterfaceAPIs) {
    for (auto func : kernelInterfaceAPIs) {
        if (_SDA->isDriverFunc(*func))
            continue;

        auto funcWrapper = _PDG->getFuncWrapper(*func);
        if (!funcWrapper)
            continue;

        for (auto &[_, argTree] : funcWrapper->getArgFormalInTreeMap()) {
            auto rootNode = argTree->getRootNode();
            if (!rootNode->getDIType())
                continue;

            auto taintEdges = dbgutils::isPointerType(*rootNode->getDIType()) ?
                POINTER_TAINT_EDGES : NON_POINTER_TAINT_EDGES;

            auto taintNodes = findNodesTaintedByEdges(*rootNode, taintEdges);
            for (auto taintNode : taintNodes) {
                taintNode->setTaint();
            }
        }
    }
}

bool pdg::RiskyFieldAnalysis::isDriverControlledField(TreeNode &tn, bool &hasDrvRead) {
    if (!tn.isStructField())
        return false;

    unsigned driverWriteTimes = 0;
    unsigned kernelReadTimes = 0;

    // Function pointers exported by driver are updated in driver domain
    if (_SDA->isFuncPtr(tn) && _SDA->isDriverCallBackFuncPtrFieldNode(tn))
        driverWriteTimes += 1;

    for (auto addrVar : tn.getAddrVars()) {
        if (auto i = dyn_cast<Instruction>(addrVar)) {
            Function *f = i->getFunction();
            
            if (_SDA->isDriverFunc(*f)) {
                if (!pdgutils::isUpdatedInHeader(*i)) {
                    if (pdgutils::hasWriteAccess(*i))
                        driverWriteTimes++;
                    if (pdgutils::hasReadAccess(*i))
                        hasDrvRead = true;
                }
            }
            else if (_SDA->isKernelFunc(*f) && pdgutils::hasReadAccess(*i)) {
                kernelReadTimes++;
            }
        }
        
        if (driverWriteTimes > 0 && kernelReadTimes > 0)
            return true;
    }
    return false;
}

bool pdg::RiskyFieldAnalysis::isUsedInSensitiveContext(Node &node, std::string &senOpName) {
    return taintutils::isValueInSensitiveBranch(node, senOpName) || 
           taintutils::isValueInSensitiveAPI(node, senOpName);
}

void pdg::RiskyFieldAnalysis::addClassification(
    RiskyDataType type, 
    std::set<RiskyDataType> &classifications,
    nlohmann::ordered_json &jsonObj,
    const std::string &accessPath,
    const std::string &details,
    Node &srcNode,
    Node &dstNode,
    const std::set<EdgeType> &edges) {
    
    classifications.insert(type);
    auto traceObj = generateTraceJsonObj(srcNode, dstNode, accessPath, details, _caseID, edges);
    if (!traceObj.empty()) {
        jsonObj.push_back(traceObj);
    }
}

bool pdg::RiskyFieldAnalysis::classifyRiskyPtrField(
    TreeNode &tn, 
    std::set<RiskyDataType> &riskyClassifications,
    nlohmann::ordered_json &taintJsonObjs) {

    std::string accessPathStr = tn.getSrcHierarchyName(false);
    auto fieldDIType = tn.getDIType();
    bool classified = false;
    numPtrField++;

    // Handle function pointers
    if (dbgutils::isFuncPointerType(*fieldDIType)) {
        numFuncPtrField++;
        return true;
    }

    // Handle union pointers
    if (dbgutils::isUnionPointerType(*fieldDIType)) {
        nlohmann::ordered_json traceJson;
        traceJson["id"] = std::to_string(_caseID);
        traceJson["risky"] = "type-conf";
        if (tn.getFunc()) {
            traceJson["drv_func"] = tn.getFunc()->getName().str();
        }

        std::string addressLocStr;
        for (auto addrVar : tn.getAddrVars()) {
            if (auto addrVarInst = dyn_cast<Instruction>(addrVar)) {
                if (!addressLocStr.empty()) addressLocStr += " | ";
                addressLocStr += pdgutils::getSourceLocationStr(*addrVarInst);
            }
        }
        if (!addressLocStr.empty()) {
            traceJson["risky_locs"] = addressLocStr;
        }
        traceJson["acc_path"] = accessPathStr;
        taintJsonObjs.push_back(traceJson);
        return true;
    }

    // Handle data pointers
    numDataPtrField++;

    auto func = tn.getFunc();
    if (!func || !_SDA->isKernelFunc(*func)) {
        return false;
    }

    std::set<pdg::EdgeType> taintEdges = {
        pdg::EdgeType::DATA_ALIAS,
        pdg::EdgeType::VAL_DEP,
        pdg::EdgeType::PARAMETER_IN,
        pdg::EdgeType::DATA_DEF_USE_LOAD,
        pdg::EdgeType::DATA_DEF_USE_CAST
    };

    auto taintNodes = findNodesTaintedByEdges(tn, taintEdges);
    for (auto taintNode : taintNodes) {
        if (!taintNode->getValue() || !isa<Instruction>(taintNode->getValue())) {
            continue;
        }

        if (taintNode->getFunc() && _SDA->isDriverFunc(*taintNode->getFunc())) {
            continue;
        }

        // Check for pointer read operations
        if (riskyClassifications.find(RiskyDataType::PTR_READ) == riskyClassifications.end() && 
            taintutils::isPointerRead(*taintNode)) {
            addClassification(
                RiskyDataType::PTR_READ,
                riskyClassifications,
                taintJsonObjs,
                accessPathStr,
                "ptr-read",
                tn,
                *taintNode,
                taintEdges
            );
            classified = true;
        }

        // Check for pointer write operations
        if (riskyClassifications.find(RiskyDataType::PTR_WRTIE) == riskyClassifications.end() && 
            taintutils::isPointeeModified(*taintNode)) {
            addClassification(
                RiskyDataType::PTR_WRTIE,
                riskyClassifications,
                taintJsonObjs,
                accessPathStr,
                "ptr-write",
                tn,
                *taintNode,
                taintEdges
            );
            classified = true;
        }

        // Check for control variables
        std::string senOpName;
        if (riskyClassifications.find(RiskyDataType::CONTROL_VAR) == riskyClassifications.end() && 
            isUsedInSensitiveContext(*taintNode, senOpName)) {
            std::string description = "ptr-sen-branch ( senapi: " + senOpName + ")";
            addClassification(
                RiskyDataType::CONTROL_VAR,
                riskyClassifications,
                taintJsonObjs,
                accessPathStr,
                description,
                tn,
                *taintNode,
                taintEdges
            );
            classified = true;
        }

        // Check for risky kernel function usage
        if (riskyClassifications.find(RiskyDataType::RISKY_KERNEL_FUNC) == riskyClassifications.end() && 
            taintutils::isValueInSensitiveAPI(*taintNode, senOpName)) {
            std::string description = "ptr-sen-api (" + senOpName + ")";
            addClassification(
                RiskyDataType::RISKY_KERNEL_FUNC,
                riskyClassifications,
                taintJsonObjs,
                accessPathStr,
                description,
                tn,
                *taintNode,
                taintEdges
            );
            classified = true;
        }
    }

    return classified;
}

bool pdg::RiskyFieldAnalysis::classifyRiskyNonPtrField(
    TreeNode &tn,
    std::set<RiskyDataType> &riskyClassifications,
    nlohmann::ordered_json &taintJsonObjs) {

    std::string accessPathStr = tn.getSrcHierarchyName(false);
    auto fieldDIType = tn.getDIType();
    bool classified = false;

    // Handle union types
    if (dbgutils::isUnionType(*fieldDIType)) {
        nlohmann::ordered_json traceJson;
        traceJson["id"] = std::to_string(_caseID);
        traceJson["risky"] = "type-conf";
        if (tn.getFunc()) {
            traceJson["drv_func"] = tn.getFunc()->getName().str();
        }

        std::string addressLocStr;
        for (auto addrVar : tn.getAddrVars()) {
            if (auto addrVarInst = dyn_cast<Instruction>(addrVar)) {
                if (!addressLocStr.empty()) addressLocStr += " | ";
                addressLocStr += pdgutils::getSourceLocationStr(*addrVarInst);
            }
        }
        traceJson["risky_locs"] = addressLocStr;
        traceJson["acc_path"] = accessPathStr;
        taintJsonObjs.push_back(traceJson);
        return true;
    }

    auto func = tn.getFunc();
    if (!func || !_SDA->isKernelFunc(*func)) {
        return false;
    }

    std::set<pdg::EdgeType> taintEdges = {
        pdg::EdgeType::VAL_DEP,
        pdg::EdgeType::PARAMETER_IN,
        pdg::EdgeType::DATA_DEF_USE_CAST,
        pdg::EdgeType::DATA_DEF_USE_ARITH,
        pdg::EdgeType::DATA_EQUL_OBJ,
        pdg::EdgeType::DATA_STORE_TO
    };

    auto taintNodes = findNodesTaintedByEdges(tn, taintEdges);
    for (auto taintNode : taintNodes) {
        if (!taintNode->getValue()) {
            continue;
        }

        auto taintInst = dyn_cast<Instruction>(taintNode->getValue());
        if (!taintInst || _SDA->isDriverFunc(*taintInst->getFunction())) {
            continue;
        }

        // Check for array index usage
        if (riskyClassifications.find(RiskyDataType::ARR_IDX) == riskyClassifications.end() && 
            taintutils::isUsedAsArrayIndex(*taintNode)) {
            addClassification(
                RiskyDataType::ARR_IDX,
                riskyClassifications,
                taintJsonObjs,
                accessPathStr,
                "arr-idx",
                tn,
                *taintNode,
                taintEdges
            );
            classified = true;
        }

        // Check for arithmetic operations
        if (riskyClassifications.find(RiskyDataType::NUM_ARITH) == riskyClassifications.end() && 
            taintutils::isValueUsedInArithmetic(*taintNode)) {
            auto arithValTaintNodes = findNodesTaintedByEdges(*taintNode, taintEdges);
            for (auto arithTN : arithValTaintNodes) {
                std::string senOpName;
                if (isUsedInSensitiveContext(*arithTN, senOpName)) {
                    std::string description = "num-arith ( " + senOpName + " )";
                    addClassification(
                        RiskyDataType::NUM_ARITH,
                        riskyClassifications,
                        taintJsonObjs,
                        accessPathStr,
                        description,
                        tn,
                        *taintNode,
                        taintEdges
                    );
                    classified = true;
                    break;
                }
            }
        }

        // Check for division by zero
        if (riskyClassifications.find(RiskyDataType::DIV_BY_ZERO) == riskyClassifications.end() && 
            taintutils::isValUsedInDivByZero(*taintNode)) {
            addClassification(
                RiskyDataType::DIV_BY_ZERO,
                riskyClassifications,
                taintJsonObjs,
                accessPathStr,
                "div-by-zero",
                tn,
                *taintNode,
                taintEdges
            );
            classified = true;
        }

        // Check for control variables
        std::string senOpName;
        if (riskyClassifications.find(RiskyDataType::CONTROL_VAR) == riskyClassifications.end() && 
            taintutils::isValueInSensitiveBranch(*taintNode, senOpName)) {
            std::string description = "val-sen-branch (" + senOpName + ")";
            addClassification(
                RiskyDataType::CONTROL_VAR,
                riskyClassifications,
                taintJsonObjs,
                accessPathStr,
                description,
                tn,
                *taintNode,
                taintEdges
            );
            classified = true;
        }

        // Check for risky kernel function usage
        if (riskyClassifications.find(RiskyDataType::RISKY_KERNEL_FUNC) == riskyClassifications.end() && 
            taintutils::isValueInSensitiveAPI(*taintNode, senOpName)) {
            std::string description = "val-sen-api (" + senOpName + ")";
            addClassification(
                RiskyDataType::RISKY_KERNEL_FUNC,
                riskyClassifications,
                taintJsonObjs,
                accessPathStr,
                description,
                tn,
                *taintNode,
                taintEdges
            );
            classified = true;
        }
    }

    return classified;
}

void pdg::RiskyFieldAnalysis::classifyRiskyField(
    TreeNode &tn,
    std::set<RiskyDataType> &riskyClassifications,
    nlohmann::ordered_json &taintJsonObjs) {

    auto fieldDIType = tn.getDIType();
    bool isClassified = false;

    if (dbgutils::isPointerType(*fieldDIType)) {
        isClassified = classifyRiskyPtrField(tn, riskyClassifications, taintJsonObjs);
    } else {
        isClassified = classifyRiskyNonPtrField(tn, riskyClassifications, taintJsonObjs);
    }

    // Handle unclassified fields
    if (!isClassified) {
        recordUnclassifiedField(tn);
    }
}

void pdg::RiskyFieldAnalysis::recordUnclassifiedField(TreeNode &tn) {
    nlohmann::ordered_json traceJson;
    traceJson["id"] = _caseID;
    traceJson["acc_path"] = tn.getSrcHierarchyName(false);

    std::string readLocs, updateLocs;
    for (auto addrVar : tn.getAddrVars()) {
        if (auto inst = dyn_cast<Instruction>(addrVar)) {
            auto f = inst->getFunction();
            std::string locStr = pdgutils::getSourceLocationStr(*inst);

            if (_SDA->isDriverFunc(*f)) {
                if (!updateLocs.empty()) updateLocs += ", ";
                updateLocs += " [" + locStr + "]";
            } else {
                if (!readLocs.empty()) readLocs += ", ";
                readLocs += " [" + locStr + "]";
            }
        }
    }

    // Handle root node (parameter) case
    if (tn.isRootNode()) {
        if (auto func = tn.getTree()->getFunc()) {
            if (auto DISubprog = func->getSubprogram()) {
                std::string file = DISubprog->getFilename().str();
                unsigned line = DISubprog->getLine();
                readLocs = GITLAB_PREFIX + file + "#L" + std::to_string(line) + 
                          " | " + func->getName().str();
            }
        }
    }

    traceJson["Kernel read"] = readLocs;
    traceJson["Drv update"] = updateLocs;
    taintutils::printJsonToFile(traceJson, "UnclassifiedFields.json");
}

void pdg::RiskyFieldAnalysis::classifyRiskyBoundaryParams(std::set<Function *> &kernelInterfaceAPIs) {
    // First handle direct risky API invocations
    for (auto func : kernelInterfaceAPIs) {
        if (_SDA->isDriverFunc(*func)) continue;

        auto funcWrapper = _PDG->getFuncWrapper(*func);
        if (!funcWrapper) continue;

        if (taintutils::isRiskyFunc(func->getName().str())) {
            handleDirectRiskyAPI(*func, *funcWrapper);
            continue;
        }

        // Process each argument tree
        auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
        for (auto &[_, argTree] : argTreeMap) {
            processArgumentTree(*argTree, func->getName().str());
        }
    }

    // Print statistics
    errs() << "----- Risky data dist: ------ \n";
    errs() << "total: " << totalRiskyParamCounters.size() << "\n";
    for (auto &[type, count] : totalRiskyParamCounters) {
        errs() << "\t" << pdgutils::riskyDataTypeToString(type) << ": " 
               << std::to_string(count) << "\n";
    }
}

void pdg::RiskyFieldAnalysis::handleDirectRiskyAPI(
    Function &func, 
    FunctionWrapper &funcWrapper) {
    
    nlohmann::ordered_json taintJsonObjs = nlohmann::ordered_json::array();
    
    for (auto &[_, argTree] : funcWrapper.getArgFormalInTreeMap()) {
        auto rootNode = argTree->getRootNode();
        
        nlohmann::ordered_json directRiskyAPIJson;
        directRiskyAPIJson["id"] = _caseID++;
        directRiskyAPIJson["risky"] = "direct-risky-API";
        directRiskyAPIJson["param"] = rootNode->getSrcName();
        directRiskyAPIJson["risky API"] = func.getName().str();
        directRiskyAPIJson["isControl"] = 1;
        directRiskyAPIJson["isTrue"] = "1";
        
        taintJsonObjs.push_back(directRiskyAPIJson);
    }
    
    taintutils::printJsonToFile(taintJsonObjs, "BoundaryParamTaint.json");
}

void pdg::RiskyFieldAnalysis::processArgumentTree(Tree &argTree, StringRef funcName) {
    auto rootNode = argTree.getRootNode();
    _numBoundaryArg++;

    // Get struct type information
    auto rootDIType = rootNode->getDIType();
    std::string structTypeName;
    if (dbgutils::isStructPointerType(*rootDIType)) {
        structTypeName = rootNode->getChildNodes()[0]->getTypeName(true);
    }

    // Process all nodes in the tree
    unsigned numFields = 0;
    unsigned numKRDUFields = 0;
    nlohmann::ordered_json taintJsonObjs = nlohmann::ordered_json::array();
    
    std::queue<TreeNode *> nodeQueue;
    nodeQueue.push(rootNode);

    while (!nodeQueue.empty()) {
        TreeNode *n = nodeQueue.front();
        nodeQueue.pop();

        if (!n->getDIType()) continue;

        // Process child nodes
        for (auto childNode : n->getChildNodes()) {
            nodeQueue.push(childNode);
        }

        // Handle struct fields
        if (n->isStructField()) {
            numFields++;
            bool isKRDUField = _KRDUFieldIds.find(pdgutils::computeTreeNodeID(*n)) != 
                              _KRDUFieldIds.end();
            
            if (!isKRDUField) continue;
            
            numKRDUFields++;
            _numBoundaryFields++;
        }

        // Classify the field
        std::set<RiskyDataType> riskyClassifications;
        classifyRiskyField(*n, riskyClassifications, taintJsonObjs);
        
        // Update statistics
        updateRiskyParamCounters(riskyClassifications);
        
        if (riskyClassifications.empty()) {
            totalRiskyParamCounters[RiskyDataType::OTHER]++;
        } else {
            updateClassificationStats(*n, riskyClassifications, structTypeName);
        }
    }

    // Update struct statistics if applicable
    if (rootDIType && dbgutils::isStructPointerType(*rootDIType)) {
        updateStructStats(structTypeName, numFields, numKRDUFields);
    }

    _caseID++;
    taintutils::printJsonToFile(taintJsonObjs, "BoundaryParamTaint.json");
}

void pdg::RiskyFieldAnalysis::updateClassificationStats(
    TreeNode &node,
    const std::set<RiskyDataType> &classifications,
    const std::string &structTypeName) {
    
    if (node.isRootNode()) {
        _numClassifiedBoundaryArg++;
    }
    
    if (node.isStructField()) {
        _numClassifiedBoundaryFields++;
        auto treeNodeID = pdgutils::computeTreeNodeID(node);
        
        if (!structTypeName.empty()) {
            _sharedStructClassifiedFields[structTypeName].insert(treeNodeID);
            
            for (auto riskyType : classifications) {
                _fieldRiskyTypeMap[structTypeName][riskyType].insert(treeNodeID);
            }
        }
    }
}

void pdg::RiskyFieldAnalysis::updateStructStats(
    const std::string &structTypeName,
    unsigned numFields,
    unsigned numKRDUFields) {
    
    auto &stats = _sharedStructTypeRiskyCounts[structTypeName];
    stats["Struct"] = structTypeName;
    stats["No.Fields"] = numFields;
    stats["No.KRDU fields"] = numKRDUFields;
    stats["No.classified fields"] = _sharedStructClassifiedFields[structTypeName].size();
    stats["No.unclassified fields"] = numKRDUFields -
                                     _sharedStructClassifiedFields[structTypeName].size();
}

void pdg::RiskyFieldAnalysis::classifyRetErrorCode(std::set<Function *> &kernelInterfaceAPIs) {
    std::set<pdg::EdgeType> taintEdges = {
        pdg::EdgeType::DATA_ALIAS,
        pdg::EdgeType::DATA_STORE_TO,
        pdg::EdgeType::DATA_DEF_USE,
        pdg::EdgeType::DATA_EQUL_OBJ
    };
    
    nlohmann::ordered_json retTaintJsonObjs = nlohmann::ordered_json::array();
    
    // Statistics tracking
    unsigned numOfDrvIFunc = 0;
    unsigned numOfDrvIFuncRetEC = 0;
    unsigned numOfMissingEC = 0;

    for (auto func : _SDA->getBoundaryFuncs()) {
        if (!_SDA->isDriverFunc(*func)) continue;

        auto funcWrapper = _PDG->getFuncWrapper(*func);
        if (!funcWrapper) continue;
        
        numOfDrvIFunc++;

        auto retFormalTree = funcWrapper->getRetFormalInTree();
        auto retRootNode = retFormalTree->getRootNode();
        if (!retRootNode) continue;

        auto retRootNodeFunc = retRootNode->getTree()->getFunc();
        if (!retRootNodeFunc || !_SDA->isDriverFunc(*retRootNodeFunc)) continue;

        auto retRootDIType = retRootNode->getDIType();
        if (!retRootDIType) continue;

        bool isUsedInBranch = analyzeReturnValueUsage(
            *retRootNode,
            *func,
            taintEdges,
            retTaintJsonObjs,
            numOfDrvIFuncRetEC,
            numOfMissingEC
        );

        if (!isUsedInBranch) {
            recordMissingErrorCheck(*func, *retRootNode, retTaintJsonObjs);
            numOfMissingEC++;
        }
    }

    // Add statistics to JSON
    nlohmann::ordered_json statJson;
    statJson["record size"] = retTaintJsonObjs.size();
    statJson["num of drv ifunc"] = numOfDrvIFunc;
    statJson["num of EC drv ifunc"] = numOfDrvIFuncRetEC;
    statJson["num of missing EC call-sites"] = numOfMissingEC;
    retTaintJsonObjs.push_back(statJson);
    
    taintutils::printJsonToFile(retTaintJsonObjs, "RetBoundaryParamTaint.json");
}

bool pdg::RiskyFieldAnalysis::analyzeReturnValueUsage(
    TreeNode &retRootNode,
    Function &func,
    const std::set<EdgeType> &taintEdges,
    nlohmann::ordered_json &retTaintJsonObjs,
    unsigned &numOfDrvIFuncRetEC,
    unsigned &numOfMissingEC) {
    
    bool isUsedInBranch = false;
    auto actualInTreeNodes = retRootNode.getInNeighborsWithDepType(EdgeType::PARAMETER_IN);

    for (auto n : actualInTreeNodes) {
        TreeNode *actualTN = static_cast<TreeNode *>(n);
        
        for (auto addrVar : actualTN->getAddrVars()) {
            auto addrVarNode = _PDG->getNode(*addrVar);
            if (!addrVarNode) continue;

            auto taintNodes = findNodesTaintedByEdges(*addrVarNode, taintEdges);
            for (auto tn : taintNodes) {
                std::string senOpName;
                if (taintutils::isValueInSensitiveBranch(*tn, senOpName)) {
                    nlohmann::ordered_json tmpJson;
                    if (auto inst = dyn_cast<Instruction>(addrVar)) {
                        tmpJson["Ret Loc"] = pdgutils::getSourceLocationStr(*inst);
                    }
                    tmpJson["Drv Interface"] = func.getName().str();
                    retTaintJsonObjs.push_back(tmpJson);
                    numOfDrvIFuncRetEC++;
                    isUsedInBranch = true;
                    break;
                }
            }
            if (isUsedInBranch) break;
        }
        if (isUsedInBranch) break;
    }

    return isUsedInBranch;
}

void pdg::RiskyFieldAnalysis::recordMissingErrorCheck(
    Function &func,
    TreeNode &retRootNode,
    nlohmann::ordered_json &retTaintJsonObjs) {
    
    nlohmann::ordered_json tmpJson;
    tmpJson["missing EC driver func"] = func.getName().str();
    
    unsigned idx = 0;
    auto actualInTreeNodes = retRootNode.getInNeighborsWithDepType(EdgeType::PARAMETER_IN);
    
    for (auto n : actualInTreeNodes) {
        TreeNode *actualTN = static_cast<TreeNode *>(n);
        auto actualTreeFunc = actualTN->getTree()->getFunc();
        if (!actualTreeFunc) continue;

        std::string retStr = "( " + actualTreeFunc->getName().str() + " )";
        
        for (auto addrVar : actualTN->getAddrVars()) {
            if (auto inst = dyn_cast<Instruction>(addrVar)) {
                retStr += " | " + pdgutils::getSourceLocationStr(*inst);
            }
        }
        
        std::string retIdxStr = "missing EC loc " + std::to_string(idx++);
        tmpJson[retIdxStr] = retStr;
    }
    
    retTaintJsonObjs.push_back(tmpJson);
}

void pdg::RiskyFieldAnalysis::printFieldClassificationTaint() {
    // Count boundary functions
    unsigned numKernelBoundaryFunc = 0;
    unsigned numDrvBoundaryFunc = 0;
    for (auto f : _SDA->getBoundaryFuncs()) {
        if (_SDA->isDriverFunc(*f)) {
            numDrvBoundaryFunc++;
        } else {
            numKernelBoundaryFunc++;
        }
    }

    // Prepare general statistics
    nlohmann::ordered_json drvGeneralStats;
    drvGeneralStats["Num kernel boundary func"] = numKernelBoundaryFunc;
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

    // Add risky field statistics
    for (auto &[type, count] : totalRiskyFieldCounters) {
        drvGeneralStats[taintutils::riskyDataTypeToString(type)] = count;
    }

    // Add risky parameter statistics
    for (auto &[type, count] : totalRiskyParamCounters) {
        drvGeneralStats["PARAM_" + taintutils::riskyDataTypeToString(type)] = count;
    }

    taintutils::printJsonToFile(drvGeneralStats, "GeneralRiskyDataStat.json");
}

void pdg::RiskyFieldAnalysis::printBoundaryStructFieldsClassificationStats() {
    unsigned totalFields = 0;
    unsigned totalClassifiedFields = 0;
    unsigned totalKRDUFields = 0;
    std::map<RiskyDataType, int> riskyClassCountMap;

    // Process each struct type
    for (auto &[_, jsonObj] : _sharedStructTypeRiskyCounts) {
        auto structTypeName = jsonObj["Struct"];
        totalFields += jsonObj["No.Fields"].get<int>();
        totalKRDUFields += jsonObj["No.KRDU fields"].get<int>();
        totalClassifiedFields += jsonObj["No.classified fields"].get<int>();

        // Add risky classifications for this struct
        auto it = _fieldRiskyTypeMap.find(structTypeName);
        if (it != _fieldRiskyTypeMap.end()) {
            for (const auto &pair : it->second) {
                const auto &riskyClass = pair.first;
                const auto &riskyClassFields = pair.second;
                riskyClassCountMap[riskyClass] += riskyClassFields.size();
                std::string riskyClassStr = pdgutils::riskyDataTypeToString(riskyClass);
                if (!riskyClassStr.empty()) {
                    jsonObj[riskyClassStr] = std::to_string(riskyClassFields.size());
                }
            }
        }
        taintutils::printJsonToFile(jsonObj, "BoundaryStructFieldsStats.json");
    }

    // Generate overall statistics
    nlohmann::ordered_json overallStatObj;
    overallStatObj["Shared Struct"] = _sharedStructTypeRiskyCounts.size();
    overallStatObj["Shared Fields"] = totalFields;
    overallStatObj["KRDU Fields"] = totalKRDUFields;
    overallStatObj["Classified Fields"] = totalClassifiedFields;
    overallStatObj["Non-Classified Fields"] = totalKRDUFields - totalClassifiedFields;
    
    for (auto &[riskyClass, count] : riskyClassCountMap) {
        overallStatObj[pdgutils::riskyDataTypeToString(riskyClass)] = count;
    }
    
    taintutils::printJsonToFile(overallStatObj, "BoundaryStructFieldsStats.json");
}

static RegisterPass<pdg::RiskyFieldAnalysis>
    RiskyFieldAnalysis("risky-field", "Risky Field Analysis", false, true);
