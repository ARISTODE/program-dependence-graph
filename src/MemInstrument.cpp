#include "MemInstrument.hh"

using namespace llvm;

char pdg::MemInstrumentPass::ID = 0;

cl::opt<std::string> TargetFuncName("target-instrument-func-name", cl::desc("target function name to generaete ebpf program"));

void pdg::MemInstrumentPass::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.addRequired<SharedDataAnalysis>();
    AU.setPreservesAll();
}

bool pdg::MemInstrumentPass::runOnModule(Module &M)
{
    SDA = &getAnalysis<SharedDataAnalysis>();
    PDG = SDA->getPDG();
    addInstrumentFuncsDeclaration(M);
    errs() << "Target func name: " << TargetFuncName << "\n";
    for (auto &F : M)
    {
        if (F.isDeclaration())
            continue;
        if (F.getName() != TargetFuncName)
            continue;
        // setup legit address for the target function
        // insertMemSetupCall(F);
        // insert memory instrumentation for load/store instruction
        auto &callGraph = PDGCallGraph::getInstance();
        auto funcNode = callGraph.getNode(F);
        assert(funcNode != nullptr && "cannot compute transitive closure for null func");
        auto transCalledFuncs = callGraph.computeTransitiveClosure(*funcNode);
        insertMemAccessCall(transCalledFuncs);
    }
    std::error_code EC;
    llvm::raw_fd_ostream OS("module.bc", EC, llvm::sys::fs::F_None);
    WriteBitcodeToFile(M, OS);
    OS.flush();
    return true;
}

void pdg::MemInstrumentPass::addInstrumentFuncsDeclaration(Module &M)
{
    auto &Ctx = M.getContext();
    // insert the memory setup function declaration
    setupLegalMemoryFn = M.getOrInsertFunction("_setup_legal_memory", Type::getVoidTy(Ctx));
    // insert memory check function declaration
    checkMemReadFn = M.getOrInsertFunction("_check_is_legal_memory_read", Type::getVoidTy(Ctx), Type::getInt8PtrTy(Ctx));
    checkMemWriteFn = M.getOrInsertFunction("_check_is_legal_memory_write", Type::getVoidTy(Ctx), Type::getInt8PtrTy(Ctx));
}

void pdg::MemInstrumentPass::insertMemSetupCall(Function &F)
{
    // _setup_legit_memory(void* base_addr, vector<int> offsets)
    // obtain the first basicblock of the target function
    auto instIter = inst_begin(F);
    Instruction *firstInst = &*instIter;
    // use IRBuilder to insert call to the setup memory function
    IRBuilder<> IRBuilder(firstInst);
}

void pdg::MemInstrumentPass::insertMemAccessCall(std::vector<pdg::Node *> &memInstrumentFuncNodes)
{
    for (auto funcNode : memInstrumentFuncNodes)
    {
        auto val = funcNode->getValue();
        if (Function *f = dyn_cast<Function>(val))
        {
            for (auto instIter = inst_begin(*f); instIter != inst_end(*f); ++instIter)
            {
                auto inst = &*instIter;
                auto instNode = PDG->getNode(*inst);
                // if (!instNode->isAddrVarNode())
                //     continue;
                if (LoadInst *li = dyn_cast<LoadInst>(inst))
                {
                    // insert call to check the load address
                    auto loadAddr = li->getPointerOperand();
                    IRBuilder<> Builder(li);
                    FunctionType *funcTy = checkMemReadFn.getFunctionType();
                    Type* castFromType = li->getPointerOperand()->getType();
                    Type *addrTy = funcTy->getParamType(0);
                    Value *val = Builder.CreatePointerCast(li->getPointerOperand(), addrTy);
                    Builder.CreateCall(checkMemReadFn, {val});
                }
                else if (StoreInst *si = dyn_cast<StoreInst>(inst))
                {
                    // insert call to check the written address
                    auto storeAddr = si->getPointerOperand();
                    IRBuilder<> Builder(si);
                    FunctionType *funcTy = checkMemWriteFn.getFunctionType();
                    Type* castFromType = si->getPointerOperand()->getType();
                    Type *addrTy= funcTy->getParamType(0);
                    Value *val = Builder.CreatePointerCast(si->getPointerOperand(), addrTy);
                    Builder.CreateCall(checkMemWriteFn, {val});
                }
            }
        }
    }
}

static RegisterPass<pdg::MemInstrumentPass> X("mem-instrument", "memory read/write instrument pass");