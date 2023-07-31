#ifndef RISKY_API_ANALYSIS_H_
#define RISKY_API_ANALYSIS_H_
#include "SharedDataAnalysis.hh"
#include "SharedFieldsAnalysis.hh"

namespace pdg
{
    class RiskyAPIAnalysis : public llvm::ModulePass
    {
    public:
        static char ID;
        RiskyAPIAnalysis() : llvm::ModulePass(ID){};
        void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
        llvm::StringRef getPassName() const override { return "Risky Field Analysis"; }
        bool runOnModule(llvm::Module &M) override;
        void flagKernelStructWritesSDA(Node &f, int &numKernelStructWrites);
        void flagKernelStructWrites(Node &f, int &numKernelStructWrites, std::set<std::string> &kOnlyField);
        void matchAllocToFree(Node &f);
        bool isSinkMM(Node &f, bool Alloc);
        void flagMemoryManagement(Node &f, int &numAllocs, int &numFrees);
        void computeSensitiveInstructionFromDriverCalls();

    private:
        llvm::Module *_module;
        ProgramGraph *_PDG;
        SharedDataAnalysis *_SDA;
        SharedFieldsAnalysis *_SFA;
        PDGCallGraph *_callGraph;
        // output file
        llvm::raw_fd_ostream *riskyKUpdateAPIOS;
        llvm::raw_fd_ostream *riskyMMAPIOS;
    };

    class ControlPath
    {
    public:
        ControlPath(Node *source, Node *dest) : source(source), dest(dest), controlledPathPercentage(0){};
        Node *getSource() { return source; }
        Node *getDest() { return dest; }
        float getControlledPathPercentage() const { return controlledPathPercentage; } // Added const here
        std::set<llvm::Value *> conditionValues;
        bool operator<(const ControlPath &other) const
        {
            return controlledPathPercentage < other.getControlledPathPercentage();
        }

    private:
        Node *source;
        Node *dest;
        float controlledPathPercentage;
    };
}

#endif