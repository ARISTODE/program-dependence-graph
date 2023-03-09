#ifndef EXTRACT_FUNC_WITH_PTR_PARAMS_H_
#define EXTRACT_FUNC_WITH_PTR_PARAMS_H_
#include "MemInstrument.hh"
#include <fstream>

namespace pdg
{
    class ExtractFuncWithPtrParamsPass : public llvm::ModulePass
    {
    public:
        static char ID;
        ExtractFuncWithPtrParamsPass() : llvm::ModulePass(ID){};
        bool runOnModule(llvm::Module &M) override;
        void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    };
}

#endif