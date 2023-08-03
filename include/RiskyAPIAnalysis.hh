#ifndef RISKY_API_ANALYSIS_H_
#define RISKY_API_ANALYSIS_H_
#include "SharedDataAnalysis.hh"
#include "SharedFieldsAnalysis.hh"
#include "KSplitCFG.hh"

namespace pdg
{
    class KFUpdateControlPath; 

    class RiskyAPIAnalysis : public llvm::ModulePass
    {
    public:
        static char ID;
        RiskyAPIAnalysis() : llvm::ModulePass(ID){};
        void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
        llvm::StringRef getPassName() const override { return "Risky Field Analysis"; }
        bool runOnModule(llvm::Module &M) override;
        void flagKernelStructWritesSDA(Node &f, int &numKernelStructWrites);
        std::set<KFUpdateControlPath> flagKernelStructWrites(Node &f, Node &API, int &numKernelStructWrites, std::set<std::string> &kOnlyField);
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
        KSplitCFG *_CFG;
        // output file
        llvm::raw_fd_ostream *riskyKUpdateAPIOS;
        llvm::raw_fd_ostream *riskyMMAPIOS;
        llvm::raw_fd_ostream *riskyKUpdateCountOS;
    };

    class KFUpdateControlPath
    {
    public:
        KFUpdateControlPath(Node *source, Node *dest) : source(source), dest(dest), controlledConditionalPercentage(0), updateInstructions({}){};
        Node *getSource() const{ return source; }
        Node *getDest() const{ return dest; }
        std::set<std::tuple<llvm::Instruction*, std::string>> getUpdateInstructions() {return updateInstructions;}
        float getControlledConditionalPercentage() const { return controlledConditionalPercentage; } // Added const here
        std::set<llvm::Value*> conditionValues;
        bool operator<(const KFUpdateControlPath &other) const
        {
            return controlledConditionalPercentage < other.getControlledConditionalPercentage();
        }
        void addUpdateInstruction(llvm::Instruction* i, std::string fieldID){updateInstructions.insert(tuple<llvm::Instruction*, std::string>(i,fieldID));}
        void setControlledConditionalPercentage(float controlledConditionalPercentage) {this->controlledConditionalPercentage = controlledConditionalPercentage; } // Added const here

    private:
        Node *source;
        Node *dest;
        float controlledConditionalPercentage;
        std::set<std::tuple<llvm::Instruction*, std::string>> updateInstructions;
    };
}

#endif