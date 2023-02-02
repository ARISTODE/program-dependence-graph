#ifndef EBPF_PROG_GENERATION_H_
#define EBPF_PROG_GENERATION_H_
#include "LLVMEssentials.hh"
#include "DataAccessAnalysis.hh"

namespace pdg
{
    class EbpfGeneration : public llvm::ModulePass
    {
    public:
        static char ID;
        EbpfGeneration() : llvm::ModulePass(ID){};
        bool runOnModule(llvm::Module &M) override;
        void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
        void generateEbpfKernelProg(llvm::Function &F);
        void generateHeaders();
        void generateEbpfKernelEntryProg(llvm::Function &F);
        void generateEbpfKernelEntryRulesForFields(Tree &argTree);
        void generateEbpfKernelExitProg(llvm::Function &F);
        void generateEbpfUserProg(llvm::Function &F, std::string kernelProgFileName);
        void generateUserProgImports();
        void generateProbeAttaches(llvm::Function &F, std::string kernelProgFileName);
        std::string extractFuncArgStr(llvm::Function &F);

    private:
        DataAccessAnalysis *DAA;
        ProgramGraph *PDG;
        std::ofstream EbpfKernelFile;
        std::ofstream EbpfUserspaceFile;
    };
}

#endif