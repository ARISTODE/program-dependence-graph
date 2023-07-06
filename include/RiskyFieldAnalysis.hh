#ifndef RISKY_FIELD_ANALYSIS_H_
#define RISKY_FIELD_ANALYSIS_H_
#include "SharedDataAnalysis.hh"

namespace pdg
{
    class RiskyFieldAnalysis : public llvm::ModulePass
    {
        public:
            static char ID;
            RiskyFieldAnalysis() : llvm::ModulePass(ID){};
            void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
            llvm::StringRef getPassName() const override { return "Risky Field Analysis"; }
            bool runOnModule(llvm::Module &M) override;
            bool isDriverControlledField(TreeNode &tn);
            void classifyRiskyField(TreeNode &tn);
            bool checkValUsedAsArrayIndex(Node &n);
            bool checkValUsedInPtrArithOp(Node &n);
            bool checkValUsedInBranch(Node &n);
            bool checkValUsedInSecurityChecks(Node &n);
            bool checkValUsedInSensitiveOperations(Node &n);
            void printRiskyFieldInfo(llvm::raw_ostream &os, const std::string &category, TreeNode &treeNode, llvm::Function &func, llvm::Instruction &inst);
            void printTaintTrace(llvm::Instruction &source, llvm::Instruction &sink, std::string fieldHierarchyName, std::string flowType);
            void printFieldClassification();

        private:
            ProgramGraph *_PDG;
            SharedDataAnalysis *_SDA;
            PDGCallGraph *_callGraph;
            // stats counting
            unsigned numKernelReadDriverUpdatedFields = 0;
            unsigned unclassifiedField = 0;
            unsigned numArrayIdxField = 0;
            unsigned numSensitiveBranchField = 0;
            unsigned numPtrArithField = 0;
            unsigned numSensitiveOpsField = 0;
    };
}

#endif