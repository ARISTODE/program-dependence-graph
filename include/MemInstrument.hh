#ifndef MEM_INSTRUMENT_H_
#define MEM_INSTRUMENT_H_
#include "LLVMEssentials.hh"
#include "llvm/IR/IRBuilder.h"
#include "SharedDataAnalysis.hh"
/*
This pass adds calls to 
1. set up initial set of legit memory
2. instrumenting each memory access (e.g., load or store instructions).
- Instrument load instruction:
for each load instruction, obtain the load address, check if the address is in the set of legit 
memory addresses
- Instrument store instruction:
for each store instruction, obtain the written address, check if the address is in the set of legit 
memory addresses
*/

namespace pdg
{
    class MemInstrumentPass : public llvm::ModulePass
    {
    public:
        static char ID;
        MemInstrumentPass() : llvm::ModulePass(ID){};
        bool runOnModule(llvm::Module &M) override;
        void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
        void addInstrumentFuncsDeclaration(llvm::Module &M);
        void insertMemSetupCall(llvm::Function &F);
        void insertMemAccessCall(std::vector<pdg::Node *> &instrumentFuncNodes);

    private:
        SharedDataAnalysis *SDA;
        ProgramGraph *PDG;
        llvm::FunctionCallee setupLegalMemoryFn;
        llvm::FunctionCallee checkMemReadFn;
        llvm::FunctionCallee checkMemWriteFn;
    };
}

#endif