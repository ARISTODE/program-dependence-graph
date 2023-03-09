#ifndef MEM_INSTRUMENT_H_
#define MEM_INSTRUMENT_H_
#include "LLVMEssentials.hh"
#include "llvm/IR/IRBuilder.h"
#include "DataAccessAnalysis.hh"
#include "llvm/Analysis/TargetTransformInfo.h"
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
        void insertAddMrrCalls(llvm::Function &F);
        void insertDeleteMrrCalls(llvm::Function &F);
        void insertCheckMrrCalls(llvm::Function &F);
        void setupParameterAccessPolicy(llvm::Function &F);
        void insertFieldAccCheckPolicy(llvm::Function &F);
        void insertMockAttack(llvm::Function &F);
        unsigned computeAccTagforAddr(llvm::Value &addr);

    private:
        DataAccessAnalysis *DAA;
        ProgramGraph *PDG;
        llvm::Module *Module_;
        llvm::FunctionCallee addMrrFunc;
        llvm::FunctionCallee deleteMrrFunc;
        llvm::FunctionCallee checkPtrAccessFunc;
        llvm::FunctionCallee setupArgAccessPolicyFunc;
        llvm::FunctionCallee checkFieldAccessFunc;
    };
}

#endif