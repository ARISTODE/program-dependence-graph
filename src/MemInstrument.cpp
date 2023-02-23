#include "MemInstrument.hh"
#include "llvm/Demangle/Demangle.h"


using namespace llvm;

char pdg::MemInstrumentPass::ID = 0;

cl::opt<std::string> TargetFuncName("target-instrument-func-name", cl::desc("target function name to insert instrumentation"));

void pdg::MemInstrumentPass::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.addRequired<DataAccessAnalysis>();
    AU.setPreservesAll();
}

bool pdg::MemInstrumentPass::runOnModule(Module &M)
{
    DAA = &getAnalysis<DataAccessAnalysis>();
    PDG = DAA->getPDG();
    addInstrumentFuncsDeclaration(M);
    Module_ = &M;
    errs() << "Target func name: " << TargetFuncName << "\n";
    for (auto &F : M)
    {
        if (F.isDeclaration())
            continue;
        auto mangledFuncName =  F.getName().str();
        errs() << "mangledName: " <<  mangledFuncName << "\n";
        auto demangledFuncName = getDemangledName(mangledFuncName.data());
        errs() << "demangledName: " << demangledFuncName << "\n";
        if (demangledFuncName == TargetFuncName)
        {
            std::ofstream policyJSONFile("AccPolicy.json");
            DAA->generateJSONObjectForFunc(F, policyJSONFile);
            // add policy instrumentation setup function
            setupParameterAccessPolicy(F);
            // add policy instrumentation checking functions
            insertFieldAccCheckPolicy(F);
            policyJSONFile.close();
            break;
        }
    }

    std::error_code EC;
    llvm::raw_fd_ostream OS("module.bc", EC, llvm::sys::fs::F_None);
    WriteBitcodeToFile(M, OS);
    OS.flush();
    return true;
}

void pdg::MemInstrumentPass::addInstrumentFuncsDeclaration(Module &M)
{
    std::string addMrrNameStr = "_Z6addMRRPvii";
    std::string deleteMrrNameStr = "_Z9deleteMRRPv";
    std::string checkMrrAccessNameStr = "_Z14checkPtrAccessPvi";
    std::string checkFieldAccessFuncName = "_Z22checkFieldAccessPolicyPvj";
    auto &Ctx = M.getContext();
    // insert memory check function declaration
    // addMrr(void*, int, int)
    addMrrFunc = M.getOrInsertFunction(addMrrNameStr, Type::getVoidTy(Ctx), Type::getInt8PtrTy(Ctx), Type::getInt32Ty(Ctx), Type::getInt32Ty(Ctx));
    // deleteMrr(void*)
    deleteMrrFunc = M.getOrInsertFunction(deleteMrrNameStr, Type::getVoidTy(Ctx), Type::getInt8PtrTy(Ctx));
    // checkMrrAccess(void*, int)
    checkPtrAccessFunc = M.getOrInsertFunction(checkMrrAccessNameStr, Type::getVoidTy(Ctx), Type::getInt8PtrTy(Ctx), Type::getInt32Ty(Ctx));
    // monitorFunc = M.getOrInsertFunction("_Z17_monitor_functionii", Type::getVoidTy(Ctx), Type::getInt8Ty(Ctx), Type::getInt8Ty(Ctx));
    setupArgAccessPolicyFunc = M.getOrInsertFunction("_Z20setupArgAccessPolicyPvj", Type::getVoidTy(Ctx), Type::getInt8PtrTy(Ctx), Type::getInt32Ty(Ctx));
    checkFieldAccessFunc = M.getOrInsertFunction(checkFieldAccessFuncName, Type::getVoidTy(Ctx), Type::getInt8PtrTy(Ctx), Type::getInt32Ty(Ctx));
}

void pdg::MemInstrumentPass::insertAddMrrCalls(llvm::Function &F)
{
    auto &Ctx = Module_->getContext();
    // insert at the beginning of function to instrument stack

    // retrive func signature of addMrrFunc
    FunctionType *funcTy = addMrrFunc.getFunctionType();
    Type *addrTy = funcTy->getParamType(0);
    Type *sizeTy = funcTy->getParamType(1);
    Type *accTagTy = funcTy->getParamType(2);
    for (auto instI = inst_begin(F); instI != inst_end(F); ++instI)
    {
        auto inst = &*instI;

        // insert at the beginning of function to instrument global variables

        // insert after each malloc / new operator
        std::string newLibCallStr = "_Znwm";
        if (CallInst *ci = dyn_cast<CallInst>(inst))
        {
            if (!ci->isIndirectCall() && ci->getCalledFunction()->getName() == newLibCallStr)
            {
                auto nextInst = ci->getNextNonDebugInstruction();
                IRBuilder<> Builder(nextInst);
                Value *addrVal = Builder.CreatePointerCast(ci, addrTy);
                Value *sizeVal = Builder.CreateIntCast(ci->getArgOperand(0), sizeTy, true);
                // by default set acc_tag to 0, which means no access
                unsigned accTag = computeAccTagforAddr(*ci);
                Value *accTagVal = Builder.CreateIntCast(ConstantInt::get(Type::getInt32Ty(Ctx), accTag), accTagTy, true);
                Builder.CreateCall(addMrrFunc, {addrVal, sizeVal, accTagVal});
            }
        }

        // insert after pointer arithmetic: base + offset (gep)
        if (auto gep = dyn_cast<GetElementPtrInst>(inst))
        {
            if (!pdgutils::isStructPointerType(*gep->getPointerOperandType()))
                continue;
            auto nextInst = gep->getNextNonDebugInstruction();
            IRBuilder<> Builder(nextInst);
            Value *addrVal = Builder.CreatePointerCast(gep, addrTy);
            const DataLayout &DL = Module_->getDataLayout();
            Type *Ty = gep->getType()->getPointerElementType();
            unsigned int sizeInBytes = (DL.getTypeSizeInBits(Ty) / 8);
            Value *sizeVal = Builder.CreateIntCast(ConstantInt::get(Type::getInt32Ty(Ctx), sizeInBytes), sizeTy, true);
            unsigned accTag = computeAccTagforAddr(*gep);
            Value *accTagVal = Builder.CreateIntCast(ConstantInt::get(Type::getInt32Ty(Ctx), accTag), accTagTy, true);
            Builder.CreateCall(addMrrFunc, {addrVal, sizeVal, accTagVal});
        }
    }
}

void pdg::MemInstrumentPass::insertDeleteMrrCalls(llvm::Function &F)
{
    std::string deleteLibCallStr = "_ZdlPv";
    for (auto instI = inst_begin(F); instI != inst_end(F); ++instI)
    {
        auto inst = &*instI;
        if (CallInst *ci = dyn_cast<CallInst>(inst))
        {
            if (!ci->isIndirectCall() && ci->getCalledFunction()->getName() == deleteLibCallStr)
            {
                auto nextInst = ci->getNextNonDebugInstruction();
                IRBuilder<> Builder(nextInst);
                FunctionType *funcTy = deleteMrrFunc.getFunctionType();
                Type *ptrTy = funcTy->getParamType(0);
                Value *ptrVal = Builder.CreatePointerCast(ci->getArgOperand(0), ptrTy);
                Builder.CreateCall(deleteMrrFunc, {ptrVal});
            }
        }
    }
}

void pdg::MemInstrumentPass::insertCheckMrrCalls(llvm::Function &F)
{
    auto &Ctx = Module_->getContext();
    // this function adds intrumentation to check whether a memory access is permitted by the memory model.
    for (auto instI = inst_begin(F); instI != inst_end(F); ++instI)
    {
        auto inst = &*instI;
        if (LoadInst *li = dyn_cast<LoadInst>(inst))
        {
            auto loadAddr = li->getPointerOperand();
            // check if the load address is in mrr, and also check whether the access tag is
            // 1 (read) or 3 (read/write)
            auto nextInst = li->getNextNonDebugInstruction();
            IRBuilder<> Builder(nextInst);
            FunctionType *funcTy = checkPtrAccessFunc.getFunctionType();
            Type *ptrTy = funcTy->getParamType(0);
            Value *ptrVal = Builder.CreatePointerCast(loadAddr, ptrTy);
            Type *accTagTy = funcTy->getParamType(1);
            Value *accTagVal = Builder.CreateIntCast(ConstantInt::get(Type::getInt32Ty(Ctx), 1), accTagTy, true);
            Builder.CreateCall(checkPtrAccessFunc, {ptrVal, accTagVal});
        }

        if (StoreInst *si = dyn_cast<StoreInst>(inst))
        {
            auto storeAddr = si->getPointerOperand();
            // check if the store address is in mrr, and check whether the access tag is
            // 2 (write) or 3 (read/write)
            auto nextInst = si->getNextNonDebugInstruction();
            IRBuilder<> Builder(nextInst);
            FunctionType *funcTy = checkPtrAccessFunc.getFunctionType();
            Type *ptrTy = funcTy->getParamType(0);
            Value *ptrVal = Builder.CreatePointerCast(storeAddr, ptrTy);
            Type *accTagTy = funcTy->getParamType(1);
            Value *accTagVal = Builder.CreateIntCast(ConstantInt::get(Type::getInt32Ty(Ctx), 2), accTagTy, true);
            Builder.CreateCall(checkPtrAccessFunc, {ptrVal, accTagVal});
        }
    }
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
    auto funcWrapper = PDG->getFuncWrapper(F);
    for (auto argI = F.arg_begin(); argI != F.arg_end(); ++argI)
    {
        auto argFormalInTree = funcWrapper->getArgFormalInTree(*argI);
        // auto argRootNode = argFormalInTree->getRootNode();
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
            Builder.CreateCall(setupArgAccessPolicyFunc, {ptrVal, argIdxVal});
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
    for (auto instI = inst_begin(F); instI != inst_end(F); instI++)
    {
        auto inst = &*instI;
        if (LoadInst *li = dyn_cast<LoadInst>(inst))
        {
            auto loadAddr = li->getPointerOperand();
            // check if the load address is in mrr, and also check whether the access tag is
            // 1 (read) or 3 (read/write)
            auto nextInst = li->getNextNonDebugInstruction();
            IRBuilder<> Builder(nextInst);
            FunctionType *funcTy = checkPtrAccessFunc.getFunctionType();
            Type *ptrTy = funcTy->getParamType(0);
            Value *ptrVal = Builder.CreatePointerCast(loadAddr, ptrTy);
            Type *accTagTy = funcTy->getParamType(1);
            Value *accTagVal = Builder.CreateIntCast(ConstantInt::get(Type::getInt32Ty(Ctx), 1), accTagTy, true);
            Builder.CreateCall(checkFieldAccessFunc, {ptrVal, accTagVal});
        }

        if (StoreInst *si = dyn_cast<StoreInst>(inst))
        {
            auto storeAddr = si->getPointerOperand();
            // check if the store address is in mrr, and check whether the access tag is
            // 2 (write) or 3 (read/write)
            auto nextInst = si->getNextNonDebugInstruction();
            IRBuilder<> Builder(nextInst);
            FunctionType *funcTy = checkPtrAccessFunc.getFunctionType();
            Type *ptrTy = funcTy->getParamType(0);
            Value *ptrVal = Builder.CreatePointerCast(storeAddr, ptrTy);
            Type *accTagTy = funcTy->getParamType(1);
            Value *accTagVal = Builder.CreateIntCast(ConstantInt::get(Type::getInt32Ty(Ctx), 2), accTagTy, true);
            Builder.CreateCall(checkFieldAccessFunc, {ptrVal, accTagVal});
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

std::string pdg::MemInstrumentPass::getDemangledName(const char* mangledName)
{
  int status = 0;
  char* demangledName = llvm::itaniumDemangle(mangledName, nullptr, nullptr, &status);
  if (!demangledName)
    return "";
  std::string ret(demangledName);
  free(demangledName);
  // Find the beginning of the function name.
 
  size_t startPos = ret.find_first_not_of(" \t\n\r");
  if (startPos == std::string::npos) {
    return "";
  }
  // Find the end of the function name.
  size_t endPos = ret.find_first_of(" \t\n\r(", startPos);
  if (endPos == std::string::npos) {
    return "";
  }
  // Extract the function name and return it.
  return ret.substr(startPos, endPos - startPos);
  return ret;
}

static RegisterPass<pdg::MemInstrumentPass> X("mem-instrument", "memory read/write instrument pass");