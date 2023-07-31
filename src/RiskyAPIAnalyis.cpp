#include "RiskyAPIAnalysis.hh"
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

char pdg::RiskyAPIAnalysis::ID = 0;
using namespace llvm;

void pdg::RiskyAPIAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.addRequired<SharedDataAnalysis>();
    AU.addRequired<SharedFieldsAnalysis>();
    AU.setPreservesAll();
}

std::vector<std::string> allocatorNames = {
    "kmalloc",
    "kzalloc",
    "vmalloc",
    "vzalloc",
    "kmem_cache_alloc"};

std::vector<std::string> deallocatorNames = {
    "kfree",
    "vfree",
    "kmem_cache_free"};

bool pdg::RiskyAPIAnalysis::runOnModule(llvm::Module &M)
{
    _module = &M;
    _SDA = &getAnalysis<SharedDataAnalysis>();
    _SFA = &getAnalysis<SharedFieldsAnalysis>();
    _PDG = _SDA->getPDG();
    _callGraph = &PDGCallGraph::getInstance();

    std::error_code EC;
    riskyKUpdateAPIOS = new raw_fd_ostream("RiskyKUpdateAPI.log", EC, sys::fs::OF_Text);
    riskyMMAPIOS = new raw_fd_ostream("RiskyMMAPI.log", EC, sys::fs::OF_Text);
    if (EC)
    {
        delete riskyKUpdateAPIOS;
        errs() << "cannot open RiskyField.log\n";
        return false;
    }

    computeSensitiveInstructionFromDriverCalls();
    // for (auto f:_SDA->getBoundaryFuncs()){
    //     errs()<<f->getName()<<"\n";
    // }
    return false;
}

// void pdg::RiskyFieldAnalysis::flagKernelStructWritesSDA(Node &f, int &numKernelStructWrites)
// {
//     Value *v = f.getValue();
//     if (Function *f = dyn_cast<Function>(v))
//     {
//         // see if function is kernel function
//         if (_SDA->isKernelFunc(*f))
//         {
//             for (auto &bb : *f)
//             {
//                 for (auto &i : bb)
//                 {
//                     // see if it is an update
//                     if (StoreInst *si = dyn_cast<StoreInst>(&i))
//                     {
//                         if (auto siNode = _PDG->getNode(*si->getPointerOperand()))
//                         {
//                             if (siNode->isAddrVarNode())
//                             {
//                                 TreeNode *siTreeNode = (TreeNode *)siNode->getAbstractTreeNode();
//                                 auto siTreeNodeId = pdgutils::computeTreeNodeID(*siTreeNode);
//                                 if (siTreeNode->isStructField() && !_SDA->isSharedFieldID(siTreeNodeId))
//                                 {
//                                     numKernelStructWrites++;
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// uses old Shared Field Analysis
void pdg::RiskyAPIAnalysis::flagKernelStructWrites(Node &f, int &numKernelStructWrites, std::set<std::string> &kOnlyField)
{
    // setup taint edges
    std::set<pdg::EdgeType> taintEdges = {
        pdg::EdgeType::PARAMETER_IN,
        // pdg::EdgeType::PARAMETER_OUT,
        // pdg::EdgeType::DATA_ALIAS,
        // EdgeType::DATA_RET,
        // pdg::EdgeType::CONTROL,
        pdg::EdgeType::DATA_STORE_TO,
        pdg::EdgeType::DATA_DEF_USE,
    };

    Value *v = f.getValue();
    if (Function *f = dyn_cast<Function>(v))
    {
        for (auto &bb : *f)
        {
            for (auto &i : bb)
            {
                if (StoreInst *si = dyn_cast<StoreInst>(&i))
                {
                    // compute debugging type
                    auto mod_addr = si->getPointerOperand();
                    auto dt_pair = _SFA->getValDITypePair(*mod_addr);
                    if (dt_pair.first && dt_pair.second)
                    {
                        // compute and check
                        auto accessFieldID = pdgutils::computeFieldID(*dt_pair.second, *dt_pair.first);
                        if (accessFieldID.empty())
                        {
                            continue;
                        }
                        auto kAccessFields = _SFA->get_kernel_access_fields();
                        auto dAccessFields = _SFA->get_driver_access_fields();
                        // check if field in kernel acess and not in shared, this means exclusive kernel update
                        if (kAccessFields.find(accessFieldID) != kAccessFields.end() && dAccessFields.find(accessFieldID) == dAccessFields.end())
                        {

                            numKernelStructWrites++;
                            kOnlyField.insert(accessFieldID);
                            *riskyKUpdateAPIOS << accessFieldID << "\n";
                            pdgutils::printSourceLocation(*si, *riskyKUpdateAPIOS);
                        }
                    }
                    // when find an update to kernel private field, propagate taints from the update address.
                    auto modAddrNode =  _PDG->getNode(*mod_addr);
                    auto taintNodes = _PDG->findNodesReachedByEdges(*modAddrNode, taintEdges);
                    // set the taint
                    for (auto taintNode : taintNodes)
                    {
                        taintNode->setTaint();
                    }
                }
            }
        }
    }
}

void pdg::RiskyAPIAnalysis::matchAllocToFree(Node &f)
{
    PTAWrapper &ptaw = PTAWrapper::getInstance();
    if (Function *fun = dyn_cast<Function>(f.getValue()))
    {
        for (inst_iterator instIter = inst_begin(fun); instIter != inst_end(fun); instIter++)
        {
            // 1. find all allocator instructions
            if (CallInst *ii_call_inst = dyn_cast<CallInst>(&*instIter))
            {
                Function *iiCalledFun = pdgutils::getCalledFunc(*ii_call_inst);
                if (iiCalledFun == nullptr || !pdgutils::containsAnySubstring(iiCalledFun->getName().str(), allocatorNames))
                {
                    continue;
                }

                CallInst *alloc_call_inst = ii_call_inst;
                // 2. find reachable free
                std::vector<Instruction *> free_insts;
                for (auto tmp_inst_iter = instIter; tmp_inst_iter != inst_end(fun); tmp_inst_iter++)
                {
                    if (CallInst *tii_call_inst = dyn_cast<CallInst>(&*tmp_inst_iter))
                    {
                        Function *tiiCalledFun = pdgutils::getCalledFunc(*tii_call_inst);
                        if (tiiCalledFun == nullptr || pdgutils::containsAnySubstring(tiiCalledFun->getName().str(), deallocatorNames))
                        {
                            free_insts.push_back(&*tmp_inst_iter);
                        }
                    }
                }

                // 3. Insert alloc/free pair if they share a function argument
                for (Instruction *free_inst : free_insts)
                {
                    CallInst *free_call_inst = dyn_cast<CallInst>(free_inst);
                    for (unsigned int i = 0; i < alloc_call_inst->getNumArgOperands(); i++)
                    {
                        for (unsigned int j = 0; j < free_call_inst->getNumArgOperands(); j++)
                        {
                            Value *alloc_arg = alloc_call_inst->getArgOperand(i);
                            Value *free_arg = free_call_inst->getArgOperand(j);
                            errs() << alloc_arg << ", " << free_arg << "\n";
                            auto andersAAresult = ptaw.queryAlias(*alloc_arg, *free_arg);
                            if (andersAAresult != NoAlias)
                            {
                                errs() << "free matches lock\n";
                            }
                        }
                    }
                }
            }
        }
    }
}

bool pdg::RiskyAPIAnalysis::isSinkMM(Node &f, bool Alloc)
{
    for (auto n : _callGraph->computeTransitiveClosure(f))
    {
        std::string functionName = n->getValue()->getName().str();
        if (functionName == f.getValue()->getName().str())
        {
            continue;
        }
        else if (pdgutils::containsAnySubstring(functionName, allocatorNames) && Alloc)
        {
            return false;
        }
        else if (pdgutils::containsAnySubstring(functionName, deallocatorNames) && !Alloc)
        {
            return false;
        }
    }
    return true;
}

void pdg::RiskyAPIAnalysis::flagMemoryManagement(Node &f, int &numAllocs, int &numFrees)
{

    // matchAllocToFree(f);
    for (auto n : f.getOutNeighbors())
    {
        std::string functionName = n->getValue()->getName().str();
        if (pdgutils::containsAnySubstring(functionName, allocatorNames))
        {
            // Check if there exists a path without a matching "free" from the "alloc"
            // bool missingFree = checkMissingFreePath(f);
            // if (missingFree)
            //{
            if (isSinkMM(*n, true))
            {
                *riskyMMAPIOS << "Memory Operation: " << functionName << "\n";
                pdgutils::printSourceLocation(*(_callGraph->getCallGraphInstruction(&f, n)), *riskyMMAPIOS);
                numAllocs++;
            }
            // Flag the memory management operation as risky
            // Perform further actions as needed
            //}
        }
        else if (pdgutils::containsAnySubstring(functionName, deallocatorNames))
        {

            // Check if the "free" takes a parameter that is not allocated
            // bool invalidFreeParam = checkInvalidFreeParameter(f);
            // if (invalidFreeParam)
            //{
            if (isSinkMM(*n, false))
            {
                *riskyMMAPIOS << "Memory Operation: " << functionName << "\n";
                pdgutils::printSourceLocation(*(_callGraph->getCallGraphInstruction(&f, n)), *riskyMMAPIOS);
                numFrees++;
            }
            // Flag the memory management operation as risky
            // Perform further actions as needed
            //}
        }
    }
}

void pdg::RiskyAPIAnalysis::computeSensitiveInstructionFromDriverCalls()
{
    errs() << " ##################################################### \n";
    errs() << "Start compute sensitive memory operations\n";
    int APICount = 0;
    int UpdateKFieldCount = 0;
    int MMCount = 0;
    int totalNumKernelStructWrites = 0;
    int FreeOnly = 0;
    int AllocOnly = 0;
    int directMMcalls = 0;


    std::set<ControlPath> kUpdatePaths = {};
    // errs() << "kernel API, number alloc nodes reachable, number of dealloc nodes reachable\n";
    // errs() << "kernel API, number kernel only fields writes reachable\n";
    // find functions accessible from driver to kernel
    std::set<std::string> kOnlyFields = {};
    for (auto f : _SDA->getBoundaryFuncs())
    {


        auto fNode = _callGraph->getNode(*f);
        if (f->isDeclaration())
            continue;
        if (!_SDA->isBoundaryFuncName(f->getName().str()))
            continue;
        if (_SDA->isDriverFunc(*f))
            continue;
        // now we know we have a kernel function that is called
        else
        {
            // make sure a driver calls the kernel function, this ensures we have an API
            bool calledByDriver = false;
            for (auto callNode : fNode->getInNeighbors())
            {
                if (Function *callFunc = dyn_cast<Function>(callNode->getValue()))
                {
                    if (_SDA->isDriverFunc(*callFunc))
                    {
                        calledByDriver = true;
                        APICount++;
                    }
                }
            }

            // if we have an API run analysis on transitive closure
            if (calledByDriver)
            {
                if (pdgutils::containsAnySubstring(fNode->getValue()->getName(), allocatorNames) || pdgutils::containsAnySubstring(fNode->getValue()->getName(), deallocatorNames))
                    {
                        if (dyn_cast<Function>(fNode->getValue()) && ((*fNode, true) || isSinkMM(*fNode, false)))
                        {
                            errs() << "Direct MMCall: " << fNode->getValue()->getName() << "\n";
                            directMMcalls++;
                        }
                }
                int totalNumAllocs = 0;
                int totalNumFrees = 0;
                bool UpdateKField = false;
                bool MM = false;
                for (auto reachableNode : _callGraph->computeTransitiveClosure(*fNode))
                {
                    int numKernelStructWrites = 0;
                    int numAllocs = 0;
                    int numFrees = 0;
                    flagKernelStructWrites(*reachableNode, numKernelStructWrites, kOnlyFields);
                    flagMemoryManagement(*reachableNode, numAllocs, numFrees);
                    if (numKernelStructWrites > 0)
                    {
                        UpdateKField = true;
                        totalNumKernelStructWrites += numKernelStructWrites;
                        std::vector<Node *> callPath;
                        std::unordered_set<Node *> visited;
                        *riskyKUpdateAPIOS << "Number of Kernel Struct Updates: " << numKernelStructWrites << "\n";
                        _callGraph->findPathDFS(fNode, reachableNode, callPath, visited);
                        _callGraph->printPath(callPath, *riskyKUpdateAPIOS);
                        *riskyKUpdateAPIOS << "***********************************************************\n";
                        riskyKUpdateAPIOS->flush();
                    }
                    if (numAllocs > 0 || numFrees > 0)
                    {
                        MM = true;
                        totalNumFrees += numFrees;
                        totalNumAllocs += numAllocs;
                        std::vector<Node *> callPath;
                        std::unordered_set<Node *> visited;
                        _callGraph->findPathDFS(fNode, reachableNode, callPath, visited);
                        _callGraph->printPath(callPath, *riskyMMAPIOS);
                        *riskyMMAPIOS << "***********************************************************\n";
                        riskyMMAPIOS->flush();
                    }
                }
                // errs() <<fNode->getValue()->getName()<< ", Allocs:"<< totalNumAllocs<< "\n";
                // errs()<<fNode->getValue()->getName()<< ", Frees:"<< totalNumFrees << "\n";
                if (totalNumFrees > 0 && totalNumAllocs == 0)
                {
                    FreeOnly++;
                    errs() << "FOnly" << fNode->getValue()->getName() << "\n";
                }
                else if (totalNumFrees == 0 && totalNumAllocs > 0)
                {
                    AllocOnly++;
                    errs() << "KOnly" << fNode->getValue()->getName() << "\n";
                }

                if (UpdateKField)
                    UpdateKFieldCount++;
                if (MM)
                    MMCount++;

                // errs() << f->getName() << "," << std::to_string(numKernelStructWrites) << "\n";
            }
        }
    }
    errs() << "Kernel Private Fields: " << (_SFA->get_kernel_access_fields().size() - _SFA->get_shared_fields().size()) << "\n";
    errs() << "Kernel APIs: " << APICount << "\n";
    errs() << "Kernel APIs updaing kernel fields: " << UpdateKFieldCount << "\n";
    errs() << "Kernel Private Fields Updates Reachable: " << totalNumKernelStructWrites << "\n";
    errs() << "Updateable Kernel Private Fields: " << kOnlyFields.size() << "\n";

    errs() << "MM Count: " << MMCount << "\n";
    errs() << "Free Only: " << FreeOnly << "\n";
    errs() << "Alloc Only: " << AllocOnly << "\n";
    errs() << "Direct Calls: " << directMMcalls << "\n";
    riskyKUpdateAPIOS->close();
    riskyMMAPIOS->close();
}

static RegisterPass<pdg::RiskyAPIAnalysis>
    RiskyFieldAnalysis("risky-API", "Risky API Analysis", false, true);