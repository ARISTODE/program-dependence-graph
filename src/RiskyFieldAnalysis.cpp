#include "RiskyFieldAnalysis.hh"
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
    };

bool pdg::RiskyFieldAnalysis::runOnModule(llvm::Module &M)
{
    _SDA = &getAnalysis<SharedDataAnalysis>();
    _PDG = _SDA->getPDG();
    _callGraph = &PDGCallGraph::getInstance();
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
            // classify the risky field into different classes
            if (isDriverControlledField(*n))
            {
                classifyRiskyField(*n);
            }

            for (auto childNode : n->getChildNodes())
            {
                nodeQueue.push(childNode);
            }
        }
    }
    printFieldClassification();
    return false;
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

// Taint source: the direct read of driver-controlled shared fields in the kernel

void pdg::RiskyFieldAnalysis::classifyRiskyField(TreeNode &tn)
{
    if (!tn.isStructField())
        return;
    numKernelReadDriverUpdatedFields++;
    std::string accessPathStr = tn.getSrcHierarchyName();

    auto addrVars = tn.getAddrVars();
    bool classified = false;
    bool isTaintArray = false;
    bool isTaintBranch = false;
    bool isTaintMemOps = false;
    bool isTaintSensitiveOp = false;

    // setup taint edges
    std::set<EdgeType> taintEdges = {
        EdgeType::PARAMETER_IN,
        EdgeType::PARAMETER_OUT,
        // EdgeType::DATA_ALIAS,
        EdgeType::DATA_RET,
        EdgeType::DATA_DEF_USE,
        EdgeType::CONTROL};

    for (auto addrVar : addrVars)
    {
        auto addrVarNode = _PDG->getNode(*addrVar);
        auto func = addrVarNode->getFunc();
        // only start taint from the kernel uses
        // TODO: here, we should also consider the special case of write access on a pointer field. If 
        // the pointer field is directly updated by the kernel, then the address it write to could be affected 
        // by the driver too. For example, if driver supply a random address in the kerenl, the kernel would write
        // to that address, causing unknown consequences.
        if (!_SDA->isKernelFunc(*func) || !pdgutils::hasReadAccess(*addrVar))
            continue;

        auto taintSourceInst = cast<Instruction>(addrVar);
        auto taintNodes = _PDG->findNodesReachedByEdges(*addrVarNode, taintEdges);
        for (auto taintNode : taintNodes)
        {
            auto taintVal = taintNode->getValue();

            // classify the fields based on taint
            if (!isTaintArray && checkValUsedAsArrayIndex(*taintNode))
            {
                isTaintArray = true;
                if (auto taintInst = dyn_cast<Instruction>(taintVal))
                {
                    printRiskyFieldInfo(errs(), "Risky Index Field", tn, *func, *taintInst);
                    printTaintTrace(*taintSourceInst, *taintInst, accessPathStr, "Idx");
                }
                numArrayIdxField++;
                classified = true;
            }

            // if a field control branchs, which contains
            if (!isTaintBranch && checkValUsedInBranch(*taintNode))
            {
                isTaintBranch = true;
                if (auto taintInst = dyn_cast<Instruction>(taintVal))
                {
                    printRiskyFieldInfo(errs(), "Risky Branch Field", tn, *func, *taintInst);
                    printTaintTrace(*taintSourceInst, *taintInst, accessPathStr, "Branch");
                }
                numSensitiveBranchField++;
            }

            if (!isTaintSensitiveOp && checkValUsedInSensitiveOperations(*taintNode))
            {
                isTaintSensitiveOp = true;
                if (auto taintInst = dyn_cast<Instruction>(taintVal))
                {
                    printRiskyFieldInfo(errs(), "Risky Sensitive Ops Field", tn, *func, *taintInst);
                    printTaintTrace(*taintSourceInst, *taintInst, accessPathStr, "SenOp");
                }
                numSensitiveOpsField++;
                classified = true;
            }

            if (!isTaintMemOps && checkValUsedInPtrArithOp(*taintNode))
            {
                isTaintMemOps = true;
                if (auto taintInst = dyn_cast<Instruction>(taintVal))
                {
                    printRiskyFieldInfo(errs(), "Risky Ptr Arith Field", tn, *func, *taintInst);
                    printTaintTrace(*taintSourceInst, *taintInst, accessPathStr, "PtrArith");
                }
                numPtrArithField++;
                classified = true;
            }
        }
    }

    // if a node is not classified into any category, print the kernel locations that read the field
    if (!classified)
    {
        unclassifiedField++;
        for (auto addrVar : addrVars)
        {
            if (Instruction *i = dyn_cast<Instruction>(addrVar))
            {
                auto instFunc = i->getFunction();
                if (pdgutils::hasReadAccess(*i) && _SDA->isKernelFunc(*instFunc))
                {
                    printRiskyFieldInfo(errs(), "Unclassified Field", tn, *instFunc, *i);
                    errs() << " <===========================================================>\n";
                }
            }
        }
    }
}

bool pdg::RiskyFieldAnalysis::checkValUsedAsArrayIndex(Node &taintNode)
{
    auto taintVal = taintNode.getValue();
    if (!taintVal)
        return false;
    for (User *U : taintVal->users())
    {
        if (GetElementPtrInst *GEP = dyn_cast<llvm::GetElementPtrInst>(U))
        {
            // skip gep on struct types
            auto ptrOperand = GEP->getPointerOperand();
            auto ptrOpNode = _PDG->getNode(*ptrOperand);
            if (!ptrOpNode || !ptrOperand)
                continue;
            if (ptrOpNode->getDIType() && dbgutils::isStructPointerType(*ptrOpNode->getDIType()))
                continue;
            // Check if taint value is used as an index in the GEP instruction
            for (auto IdxOp = GEP->idx_begin(), E = GEP->idx_end(); IdxOp != E; ++IdxOp)
                if (IdxOp->get() == taintVal)
                    return true;
        }
    }
    return false;
}

bool pdg::RiskyFieldAnalysis::checkValUsedInBranch(Node &taintNode)
{
    auto taintVal = taintNode.getValue();
    if (!taintVal)
        return false;
    for (auto user : taintVal->users())
    {
        if (auto li = dyn_cast<LoadInst>(user))
        {
            // check if the loaded value is used in branch
            for (auto u : li->users())
            {
                // if (isa<ICmpInst>(u) || isa<SwitchInst>(u))
                if (isa<BranchInst>(u))
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
                            auto calledFuncName = calledFunc->getName().str();
                            for (auto op : sensitiveOperations)
                            {
                                if (calledFuncName.find(op) != std::string::npos)
                                    return true;
                            }
                        }
                    }
                    // return true;
                }
            }
        }
    }
    return false;
}

// check if a taint value is used as a buffer
bool pdg::RiskyFieldAnalysis::checkValUsedInPtrArithOp(Node &taintNode)
{
    auto taintVal = taintNode.getValue();
    if (!taintVal)
        return false;
    for (User *U : taintVal->users())
    {
        if (auto gep = dyn_cast<GetElementPtrInst>(U))
        {
            auto gepPtrOp = gep->getPointerOperand();
            auto gepPtrOpNode = _PDG->getNode(*gepPtrOp);
            if (!gepPtrOp || !gepPtrOpNode)
                continue;
            // check if the the ptr arith is result from a field access, if so, skip
            if (gepPtrOpNode->getDIType() && dbgutils::isStructPointerType(*gepPtrOpNode->getDIType()))
                continue;
            else
                return true;
        }
    }
    return false;
}

bool pdg::RiskyFieldAnalysis::checkValUsedInSensitiveOperations(Node &taintNode)
{
    auto taintVal = taintNode.getValue();
    if (!taintVal)
        return false;
    for (User *U : taintVal->users())
    {
        if (CallInst *ci = dyn_cast<CallInst>(U))
        {
            auto calledFunc = pdgutils::getCalledFunc(*ci);
            if (!calledFunc)
                continue;
            auto calledFuncName = calledFunc->getName().str();
            for (auto op : sensitiveOperations)
            {
                if (calledFuncName.find(op) != std::string::npos)
                    return true;
            }
        }
    }
    return false;
}

// helper and print functions
void pdg::RiskyFieldAnalysis::printRiskyFieldInfo(raw_ostream &os, const std::string &category, pdg::TreeNode &treeNode, Function &func, Instruction &inst)
{
    os.changeColor(raw_ostream::RED);
    os << "--- [" << category << "] --- ";
    os.resetColor();
    os << treeNode.getSrcHierarchyName(false) << " in func " << func.getName() << "\n";
    pdg::pdgutils::printSourceLocation(inst);
}

void pdg::RiskyFieldAnalysis::printTaintTrace(Instruction &source, Instruction &sink, std::string fieldHierarchyName, std::string flowType)
{
    auto sourceFunc = source.getFunction();
    auto sourceFuncNode = _callGraph->getNode(*sourceFunc);
    auto sinkFunc = sink.getFunction();
    auto sinkFuncNode = _callGraph->getNode(*sinkFunc);

    errs() << "(field: " << fieldHierarchyName << ")"
           << "\n";
    errs() << "flow type: " << flowType << "\n";
    errs() << "source inst: " << source << " in func " << sourceFunc->getName() << "\n";
    pdgutils::printSourceLocation(source);
    errs() << "sink inst: " << sink << " in func " << sinkFunc->getName() << "\n";
    pdgutils::printSourceLocation(sink);
    std::vector<Node *> callPath;
    std::unordered_set<Node *> visited;
    _callGraph->findPathDFS(sourceFuncNode, sinkFuncNode, callPath, visited);
    _callGraph->printPath(callPath);
    errs() << "<=========================================>\n";
}

void pdg::RiskyFieldAnalysis::printFieldClassification()
{
    errs() << "Field Classification Table:\n";
    errs() << "+-----------------------------+\n";
    errs() << "|    Field            |  Count  |\n";
    errs() << "+-----------------------------+\n";
    errs() << "| Kernel Read Driver Updated |  "
           << numKernelReadDriverUpdatedFields << "    |\n";
    errs() << "| Array Index                |  " << numArrayIdxField
           << "    |\n";
    errs() << "| Sensitive Branch           |  " << numSensitiveBranchField
           << "    |\n";
    errs() << "| PtrArith Operations          |  " << numPtrArithField
           << "    |\n";
    errs() << "| Sensitive Operations       |  " << numSensitiveOpsField
           << "    |\n";
    errs() << "| Unclassified               |  " << unclassifiedField
           << "    |\n";
    errs() << "+-----------------------------+\n";
}

static RegisterPass<pdg::RiskyFieldAnalysis>
    RiskyFieldAnalysis("risky-field", "Risky Field Analysis", false, true);