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
        void generateKernelProgImports();
        void generateFuncArgRefCopyMaps(llvm::Function &F);
        void generateArgRefCopyMaps(std::string argName, std::string argTypeName);
        std::string createEbpfMapForType(llvm::DIType &dt);
        void generatePerfOutput();
        void generateEbpfMapOnFunc(llvm::Function &F);
        void generateEbpfMapOnArg(Tree &argTree);
        void generateEbpfKernelEntryProgOnFunc(llvm::Function &F);
        void generateEbpfKernelEntryProgOnArg(Tree &argTree, unsigned argIdx);
        void updateRefMap(std::string fieldTypeStr, std::string fieldName, std::string fieldHierarchyName, std::string typeCopyMap);
        void updateCopyMap(std::string fieldTypeStr, std::string fieldName, std::string fieldHierarchyName, std::string typeCopyMap);
        void generateEbpfFieldAccRules(Tree &argTree, std::string argUpdatedCopyName, std::string argCopyName);
        std::string retriveFieldFromRefMap(std::string fieldTypeStr, std::string fieldName, std::string typeRefMap);
        std::string retriveFieldFromCopyMap(std::string fieldTypeStr, std::string fieldName, std::string typeCopyMap);
        void generateEbpfAccessChecksOnArg(Tree &argTree, unsigned argIdx);
        void generateEbpfKernelExitProg(llvm::Function &F);
        void generateEbpfUserProg(llvm::Function &F);
        void generateUserProgImports(std::string kernelProgFileName);
        void generateProbeAttaches(llvm::Function &F);
        void generateTracePrint();
        void generateAttacks(std::string argTypeName, std::string argName, Tree &argTree);
        std::string extractFuncArgStr(llvm::Function &F);
        void generateFuncStructDefinition(llvm::Function &F);
        void generateStructDefString(TreeNode &structNode);
        std::string switchType(std::string typeStr);

    private:
        DataAccessAnalysis *DAA;
        ProgramGraph *PDG;
        std::ofstream EbpfKernelFile;
        std::ofstream EbpfUserspaceFile;
        std::unordered_set<std::string> mapNames;
        std::unordered_set<std::string> structDefNames;
        std::unordered_set<std::string> mapTypes;
        bool hasPtrMap = false;
    };
}

#endif