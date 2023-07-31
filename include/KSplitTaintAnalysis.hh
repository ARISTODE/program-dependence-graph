#ifndef _KSPLIT_TAINT_ANALYSIS_
#define _KSPLIT_TAINT_ANALYSIS_
#include "SharedDataAnalysis.hh"

namespace pdg
{
    // risky types enum
    enum class RiskyTypes
    {
        PTRARITH,
        PTRDEREF,
        ARRAYACC,
        ARITHOP,
        SENOP,
        SENBRANCH,
    };

    // stats collecting classes
    class RiskyAPIStatsCollector
    {
    public:
        // Statistics fields for a specific subsystem
        int kernelInterfaceAPIs = 0;
        int riskyAPIs = 0;
        int directlyInvokedRiskyAPIs = 0;
        int transitivelyInvokedRiskyAPIs = 0;
        int memoryManagement = 0;
        int concurrencyManagement = 0;
        int referenceCounting = 0;
        int timerManagement = 0;
        int ioPortsManagement = 0;
        int dma = 0;

        // Corresponding conditional versions
        int transitivelyInvokedRiskyAPIsConditional = 0;
        int memoryManagementConditional = 0;
        int concurrencyManagementConditional = 0;
        int referenceCountingConditional = 0;
        int timerManagementConditional = 0;
        int ioPortsManagementConditional = 0;
        int dmaConditional = 0;

        // Method to print the collected statistics
        void printStatistics() const
        {
            std::cout << "Risky Kernel API Statistics:\n";
            std::cout << "  No. kernel interface APIs: " << kernelInterfaceAPIs << "\n";
            std::cout << "  No. risky APIs: " << riskyAPIs << "\n";
            std::cout << "  No. directly invoked risky APIs: " << directlyInvokedRiskyAPIs  << "\n";
            std::cout << "  No. transitively invoked risky APIs: " << transitivelyInvokedRiskyAPIs << " (Conditional: " << transitivelyInvokedRiskyAPIsConditional << ")\n";
            std::cout << "  - Memory management: " << memoryManagement << " (Conditional: " << memoryManagementConditional << ")\n";
            std::cout << "  - Concurrency management: " << concurrencyManagement << " (Conditional: " << concurrencyManagementConditional << ")\n";
            std::cout << "  - Reference counting: " << referenceCounting << " (Conditional: " << referenceCountingConditional << ")\n";
            std::cout << "  - Timer management: " << timerManagement << " (Conditional: " << timerManagementConditional << ")\n";
            std::cout << "  - I/O ports management: " << ioPortsManagement << " (Conditional: " << ioPortsManagementConditional << ")\n";
            std::cout << "  - DMA: " << dma << " (Conditional: " << dmaConditional << ")\n";
        }
    };

    // analysis pass
    class KSplitTaintAnalysis : public llvm::ModulePass
    {
    public:
        static char ID;
        KSplitTaintAnalysis() : llvm::ModulePass(ID){};
        void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
        llvm::StringRef getPassName() const override { return "KSplit taint analysis"; }
        bool runOnModule(llvm::Module &M) override;
        void analyzeRiskyAPICalls();
        void analyzePrivateStateUpdate();
        void analyzeSharedStateCorruption();
        void propagateTaintsPrivateState();

        void initTaintSourcesSharedState();
        void propagateTaintsSharedState();

        std::set<std::string> classifyUsageTaint(Node &srcNode);
        void classifyTaintPointerUsage(Node &taintNode, std::set<RiskyTypes> &riskyClassificationStrs);
        void classifyTaintValUsage(Node &taintNode, std::set<RiskyTypes> &riskyClassificationStrs);
        // classification helpers
        bool checkPtrValUsedInPtrArithOp(Node &taintNode);
        bool checkPtrValhasPtrDeref(Node &taintNode);
        bool checkValUsedAsArrayIndex(Node &taintNode);
        // generic field checks
        bool checkValUsedInPtrArithOp(Node &taintNode);
        bool checkValUsedInSenBranchCond(Node &taintNode);
        bool checkValUsedInSecurityChecks(Node &taintNode);
        bool checkValUsedInSensitiveOperations(Node &taintNode);

        bool canReachSensitiveOperations(Node &callerNode);

        void incrementRiskyAPIFields(std::string& className);
        void reportTaintResults();

        // private states set
        std::unordered_set<llvm::StoreInst *> storeInstsUpdatePrivateStates;
        llvm::DenseMap<llvm::Function *, std::unordered_set<llvm::StoreInst *>> privateStateUpdateMap;
        RiskyAPIStatsCollector riskyAPICollector;

    private:
        std::set<std::tuple<Node *, Node *, std::string, std::string>> _taintTuples;
        llvm::Module *_module;
        ProgramGraph *_PDG;
        SharedDataAnalysis *_SDA;
        PDGCallGraph *_callGraph;
        std::unordered_set<Node *> _taintSources;
        std::unordered_map<Node *, std::vector<Node *>> _taintMap; // map taint trace to taint sink node
        llvm::raw_fd_ostream *privateStateUpdateLogOS;
    };


}

#endif