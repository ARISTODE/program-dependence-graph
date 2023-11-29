#include "MemInstrument.hh"

using namespace llvm;

char pdg::MemInstrumentPass::ID = 0;

void pdg::MemInstrumentPass::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.addRequired<DataAccessAnalysis>();
    AU.setPreservesAll();
}

bool pdg::MemInstrumentPass::runOnModule(Module &M)
{
    DAA = &getAnalysis<DataAccessAnalysis>();
    PDG = DAA->getPDG();
    Module_ = &M;
    addInstrumentFuncsDeclaration(M);
    // reads boundary API
    std::set<std::string> boundaryAPINames;
    pdgutils::readLinesFromFile(boundaryAPINames, "boundaryAPI");
    nlohmann::json moduleJSONObj;
    std::ofstream policyJSONFile("AccPolicy.json");
    for (auto &F : M)
    {
        if (F.isDeclaration())
            continue;
        // the file contains all the demangled function name, for C++ applications
        // we need to demangled the name first before checking whether it is listed
        // as an API.
        auto mangledFuncName = F.getName().str();
        std::string demangledFuncName = pdgutils::getDemangledName(mangledFuncName.data());
        if (demangledFuncName.empty())
            demangledFuncName = mangledFuncName;
        if (boundaryAPINames.find(demangledFuncName) == boundaryAPINames.end())
            continue;
        DAA->generateJSONObjectForFunc(F, moduleJSONObj);
        // add policy instrumentation setup function
        setupParameterAccessPolicy(F);
        // add policy instrumentation checking functions
        insertFieldAccCheckPolicy(F);
    }
    // store the json object
    policyJSONFile << moduleJSONObj.dump(2);
    policyJSONFile.close();

    std::error_code EC;
    llvm::raw_fd_ostream OS("module.bc", EC, llvm::sys::fs::F_None);
    WriteBitcodeToFile(M, OS);
    OS.flush();
    return true;
}

void pdg::MemInstrumentPass::addInstrumentFuncsDeclaration(Module &M)
{
    std::string setupArgPolicyFuncName = "_Z20setupArgAccessPolicyPvjPc";
    std::string checkFieldAccessFuncName = "_Z22checkFieldAccessPolicyPvjPc";
    auto &Ctx = M.getContext();
    setupArgAccessPolicyFunc = M.getOrInsertFunction(setupArgPolicyFuncName,
                                                     Type::getVoidTy(Ctx),
                                                     Type::getInt8PtrTy(Ctx),
                                                     Type::getInt32Ty(Ctx),
                                                     Type::getInt8PtrTy(Ctx));

    checkFieldAccessFunc = M.getOrInsertFunction(checkFieldAccessFuncName,
                                                 Type::getVoidTy(Ctx),
                                                 Type::getInt8PtrTy(Ctx),
                                                 Type::getInt32Ty(Ctx),
                                                 Type::getInt8PtrTy(Ctx));
}

unsigned pdg::MemInstrumentPass::computeAccTagforAddr(Value &val)
{
    bool hasReadAccess = pdgutils::hasReadAccess(val);
    bool hasWriteAccess = pdgutils::hasWriteAccess(val);
    if (hasReadAccess && hasWriteAccess)
        return 3;
    if (hasReadAccess)
        return 1;
    if (hasWriteAccess)
        return 2;
    // no access, which is very unlikely
    return 0;
}

void pdg::MemInstrumentPass::setupParameterAccessPolicy(llvm::Function &F)
{
    // this function sets up the access policy for each parameter of the function
    // the access policy is stored in a map, which is used to check whether a memory access is permitted
    // by the memory model.
    if (!PDG->hasFuncWrapper(F))
        return;
    auto &Ctx = Module_->getContext();
    for (auto argI = F.arg_begin(); argI != F.arg_end(); ++argI)
    {
        auto arg = &*argI;
        if (pdgutils::isStructPointerType(*arg->getType()))
        {
            // for each field, insert an instrumentation to record the access policy of the field
            auto funcStartInst = &*inst_begin(F);
            IRBuilder<> Builder(funcStartInst);
            FunctionType *funcTy = setupArgAccessPolicyFunc.getFunctionType();
            Type *ptrTy = funcTy->getParamType(0);
            Value *ptrVal = Builder.CreatePointerCast(arg, ptrTy);
            Type *argTy = funcTy->getParamType(1);
            Value *argIdxVal = Builder.CreateIntCast(ConstantInt::get(Type::getInt32Ty(Ctx), arg->getArgNo()), argTy, true);
            auto funcName = F.getName().str();
            GlobalVariable* strGlobal = Module_->getGlobalVariable(funcName);
            if (!strGlobal)
            {
                Constant *strConstant = ConstantDataArray::getString(Ctx, funcName);
                strGlobal = new GlobalVariable(*Module_, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
            }
            Value *funcNameVal = Builder.CreateConstGEP2_32(strGlobal->getValueType(), strGlobal, 0, 0);
            Builder.CreateCall(setupArgAccessPolicyFunc, {ptrVal, argIdxVal, funcNameVal});
        }
        // also, obtian the field access information and dump it to file
        // this file would be loaded at runtime to setup the access policy for each field
        // DAA->dumpFieldOffsetAccessMapToFile(*argRootNode, "fieldAccFile.map");
    }
}

/*
insert instrumentation to check whether a load or store instruction touches
field address that have assoicated policy, if so, check whether the load or store
obeys the computed access policy
*/
void pdg::MemInstrumentPass::insertFieldAccCheckPolicy(Function &F)
{
    auto &Ctx = Module_->getContext();
    auto funcName = F.getName().str();
    // obtain function type
    FunctionType *funcTy = checkFieldAccessFunc.getFunctionType();
    std::unordered_set<Instruction*> mustInstrumentInsts;
    computeMustInstrumentInsts(F, mustInstrumentInsts);
    auto funcW = PDG->getFuncWrapper(F);
    errs() << "(" << F.getName().str() << ") instrument inst count: " << mustInstrumentInsts.size() << " - " << (funcW->getLoadInsts().size() + funcW->getStoreInsts().size()) << "\n";
    for (auto inst : mustInstrumentInsts)
    {
        if (LoadInst *li = dyn_cast<LoadInst>(inst))
        {
            auto loadAddr = li->getPointerOperand();
            // check if the load address is in mrr, and also check whether the access tag is
            // 1 (read) or 3 (read/write)
            auto nextInst = li->getNextNonDebugInstruction();
            IRBuilder<> Builder(nextInst);
            Type *ptrTy = funcTy->getParamType(0);
            Value *ptrVal = Builder.CreatePointerCast(loadAddr, ptrTy);
            Type *accTagTy = funcTy->getParamType(1);
            Value *accTagVal = Builder.CreateIntCast(ConstantInt::get(Type::getInt32Ty(Ctx), 1), accTagTy, true);
            GlobalVariable *strGlobal = Module_->getGlobalVariable(funcName);
            if (!strGlobal)
            {
                Constant *strConstant = ConstantDataArray::getString(Ctx, funcName);
                strGlobal = new GlobalVariable(*Module_, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
            }
            Value *funcNameVal = Builder.CreateConstGEP2_32(strGlobal->getValueType(), strGlobal, 0, 0);
            Builder.CreateCall(checkFieldAccessFunc, {ptrVal, accTagVal, funcNameVal});
        }

        if (StoreInst *si = dyn_cast<StoreInst>(inst))
        {
            auto storeAddr = si->getPointerOperand();
            // check if the store address is in mrr, and check whether the access tag is
            // 2 (write) or 3 (read/write)
            auto nextInst = si->getNextNonDebugInstruction();
            IRBuilder<> Builder(nextInst);
            Type *ptrTy = funcTy->getParamType(0);
            Value *ptrVal = Builder.CreatePointerCast(storeAddr, ptrTy);
            Type *accTagTy = funcTy->getParamType(1);
            Value *accTagVal = Builder.CreateIntCast(ConstantInt::get(Type::getInt32Ty(Ctx), 2), accTagTy, true);
            GlobalVariable *strGlobal = Module_->getGlobalVariable(funcName);
            if (!strGlobal)
            {
                Constant *strConstant = ConstantDataArray::getString(Ctx, funcName);
                strGlobal = new GlobalVariable(*Module_, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
            }
            Value *funcNameVal = Builder.CreateConstGEP2_32(strGlobal->getValueType(), strGlobal, 0, 0);
            Builder.CreateCall(checkFieldAccessFunc, {ptrVal, accTagVal, funcNameVal});
        }
    }
}

void pdg::MemInstrumentPass::computeMustInstrumentInsts(Function &F, std::unordered_set<Instruction *> &mustInstrumentInsts)
{
    // step 1: iterate through all the instructions in the Function and its transitive closure
    auto funcWrapper = PDG->getFuncWrapper(F);
    if (!funcWrapper)
        return;
    auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
    for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
    {
        auto argTree = iter->second;
        auto rootNode = argTree->getRootNode();
        std::queue<TreeNode *> nodeQ;
        nodeQ.push(rootNode);
        while (!nodeQ.empty())
        {
            TreeNode *curNode = nodeQ.front();
            nodeQ.pop();
            // enqueue all child nodes
            for (auto childNode : curNode->getChildNodes())
            {
                if (curNode->getDepth() < 3)
                    nodeQ.push(childNode);
            }
            for (auto addrVar : curNode->getAddrVars())
            {
                for (auto user : addrVar->users())
                {
                    if (isa<LoadInst>(user))
                        mustInstrumentInsts.insert(cast<Instruction>(user));
                    else if (StoreInst *si = dyn_cast<StoreInst>(user))
                    {
                        if (si->getPointerOperand() == addrVar)
                            mustInstrumentInsts.insert(cast<Instruction>(user));
                    }
                }
            }
        }
    }
}

// inserting store instructions that does not exist in the original program
void pdg::MemInstrumentPass::insertMockAttack(Function &F)
{
    for (auto instI = inst_begin(F); instI != inst_end(F); instI++)
    {
        auto inst = &*instI;
        if (LoadInst *li = dyn_cast<LoadInst>(inst))
        {
            auto loadAddr = li->getPointerOperand();
            auto nextInst = li->getNextNonDebugInstruction();
            IRBuilder<> Builder(nextInst);
            Builder.CreateStore(li, loadAddr);
        }
    }
}

static RegisterPass<pdg::MemInstrumentPass> X("mem-instrument", "memory read/write instrument pass");