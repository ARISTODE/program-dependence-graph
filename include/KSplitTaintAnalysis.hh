#ifndef _KSPLIT_TAINT_ANALYSIS_
#define _KSPLIT_TAINT_ANALYSIS_
#include "SharedDataAnalysis.hh"
#include "json.hpp"

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
        int riskyAPIsConditional = 0;
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
            std::cout << "  No. kernel interface APIs, " << kernelInterfaceAPIs << "\n";
            std::cout << "  No. risky APIs, " << riskyAPIs << "\n";
            std::cout << "  No. risky APIs with conditionals enforced, " << riskyAPIsConditional << "\n";
            std::cout << "  No. directly invoked risky APIs, " << directlyInvokedRiskyAPIs << "\n";
            std::cout << "  No. transitively invoked risky APIs, " << transitivelyInvokedRiskyAPIs << "\n";
            std::cout << "  No. transitively invoked risky APIs Conditional, " << transitivelyInvokedRiskyAPIsConditional << "\n";
            std::cout << "  - Memory management, " << memoryManagement << "\n";
            std::cout << "  - Memory management Conditonal, " << memoryManagementConditional << "\n";
            std::cout << "  - Concurrency management, " << concurrencyManagement << "\n";
            std::cout << "  - Concurrency management conditional, " << concurrencyManagementConditional << "\n";
            std::cout << "  - Reference counting, " << referenceCounting << "\n";
            std::cout << "  - Reference counting conditional, " << referenceCountingConditional << "\n";
            std::cout << "  - Timer management, " << timerManagement << "\n";
            std::cout << "  - Timer management conditional," << timerManagementConditional << "\n";
            std::cout << "  - I/O ports management, " << ioPortsManagement << "\n";
            std::cout << "  - I/O ports management conditional, " << ioPortsManagementConditional << "\n";
            std::cout << "  - DMA, " << dma << "\n";
            std::cout << "  - DMA conditional, " << dmaConditional << "\n";
        }

        void writeStatistics(llvm::raw_fd_ostream &statsOS) const
        {

            statsOS << "Risky Kernel API Statistics:\n";
            statsOS << "  No. kernel interface APIs, " << kernelInterfaceAPIs << "\n";
            statsOS << "  No. risky APIs, " << riskyAPIs << "\n";
            statsOS << "  No. risky APIs with conditionals enforced, " << riskyAPIs << "\n";
            statsOS << "  No. directly invoked risky APIs, " << directlyInvokedRiskyAPIs << "\n";
            statsOS << "  No. transitively invoked risky APIs, " << transitivelyInvokedRiskyAPIs << "\n";
            statsOS << "  No. transitively invoked risky APIs Conditional, " << transitivelyInvokedRiskyAPIsConditional << "\n";
            statsOS << "  - Memory management, " << memoryManagement << "\n";
            statsOS << "  - Memory management Conditonal, " << memoryManagementConditional << "\n";
            statsOS << "  - Concurrency management, " << concurrencyManagement << "\n";
            statsOS << "  - Concurrency management conditional, " << concurrencyManagementConditional << "\n";
            statsOS << "  - Reference counting, " << referenceCounting << "\n";
            statsOS << "  - Reference counting conditional, " << referenceCountingConditional << "\n";
            statsOS << "  - Timer management, " << timerManagement << "\n";
            statsOS << "  - Timer management conditional," << timerManagementConditional << "\n";
            statsOS << "  - I/O ports management, " << ioPortsManagement << "\n";
            statsOS << "  - I/O ports management conditional, " << ioPortsManagementConditional << "\n";
            statsOS << "  - DMA, " << dma << "\n";
            statsOS << "  - DMA conditional, " << dma << "\n";
        }
    };

    class RiskyKPUpdateCollector
    {
    public:
        int taintedStateCount = 0;
        int taintedStateCountConditional = 0;

        // Statistics fields for a specific subsystem
        int kernelPrivateUpdates = 0;
        int stackUpdate = 0;
        int globalUpdate = 0;
        int heapUpdate = 0;
        int numPrivate = 0;

        // Corresponding conditional versions
        int kernelPrivateUpdatesConditional = 0;
        int stackUpdateConditional = 0;
        int globalUpdateConditional = 0;
        int heapUpdateConditional = 0;

        // Method to print the collected statistics
        void printStatistics() const
        {
            std::cout << "Risky Kernel private state update statistics\n";
            std::cout << "-  No. Tainted Kernel Private States, " << taintedStateCount << "\n";
            std::cout << "-  No. Tainted Kernel Private States Conditional, " << taintedStateCount << "\n";
            std::cout << "-  No. Tainted Kernel Private Updates, " << kernelPrivateUpdates << "\n";
            std::cout << "-  No. Tainted Kernel Private Updates Conditional, " << kernelPrivateUpdatesConditional << "\n";
            std::cout << "-  No. Tainted Kernel Private Stack Updates, " << stackUpdate << "\n";
            std::cout << "-  No. Tainted Kernel Private Stack Updates Conditional, " << stackUpdateConditional << "\n";
            std::cout << "-  No. Tainted Kernel Private Global Updates, " << globalUpdate << "\n";
            std::cout << "-  No. Tainted Kernel Private Global Updates Conditional, " << globalUpdateConditional << "\n";
            std::cout << "-  No. Tainted Kernel Private Heap Updates, " << heapUpdate << "\n";
            std::cout << "-  No. Tainted Kernel Private Heap Updates Conditional, " << heapUpdateConditional << "\n";
        }

        void writeStatistics(llvm::raw_fd_ostream &statsOS) const
        {
            statsOS << "Risky Kernel private state update statistics\n";
            statsOS << "-  No. Tainted Kernel Private States, " << taintedStateCount << "\n";
            statsOS << "-  No. Tainted Kernel Private States Conditional, " << taintedStateCount << "\n";
            statsOS << "-  No. Tainted Kernel Private Updates, " << kernelPrivateUpdates << "\n";
            statsOS << "-  No. Tainted Kernel Private Updates Conditional, " << kernelPrivateUpdatesConditional << "\n";
            statsOS << "-  No. Tainted Kernel Private Stack Updates, " << stackUpdate << "\n";
            statsOS << "-  No. Tainted Kernel Private Stack Updates Conditional, " << stackUpdateConditional << "\n";
            statsOS << "-  No. Tainted Kernel Private Global Updates, " << globalUpdate << "\n";
            statsOS << "-  No. Tainted Kernel Private Global Updates Conditional, " << globalUpdateConditional << "\n";
            statsOS << "-  No. Tainted Kernel Private Heap Updates, " << heapUpdate << "\n";
            statsOS << "-  No. Tainted Kernel Private Heap Updates Conditional, " << heapUpdateConditional << "\n";
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
        void analyzeRiskyAPICalls(bool conditionals);
        void analyzePrivateStateUpdate(bool conditionals);
        void analyzePrivateStateUpdateWithConditionals();
        void analyzeSharedStateCorruption();
        void propagateTaintsPrivateState();

        void writeControlFlowJSONFiles();

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

        void incrementRiskyAPIFields(std::string &className);
        void incrementRiskyAPIFieldsConditional(std::string &className);
        void reportTaintResults();

        // private states set
        std::unordered_set<llvm::StoreInst *> storeInstsUpdatePrivateStates;
        llvm::DenseMap<llvm::Function *, std::unordered_set<llvm::StoreInst *>> privateStateUpdateMap;
        llvm::DenseMap<llvm::Function *, std::unordered_set<llvm::StoreInst *>> privateStateUpdateConditionalMap;
        RiskyAPIStatsCollector riskyAPICollector;
        RiskyKPUpdateCollector riskyKPUpdateCollector;

    private:
        std::set<std::tuple<Node *, Node *, std::string, std::string>> _taintTuples;
        llvm::Module *_module;
        ProgramGraph *_PDG;
        SharedDataAnalysis *_SDA;
        PDGCallGraph *_callGraph;
        std::unordered_set<Node *> _taintSources;
        std::unordered_map<Node *, std::vector<Node *>> _taintMap; // map taint trace to taint sink node
        int idAPI = 0;
        int idKPU = 0;
        nlohmann::json riskyAPIJson = nlohmann::json::array();
        nlohmann::json privateStateUpdateJson = nlohmann::json::array();
        llvm::raw_fd_ostream *statsAPIOS;
        llvm::raw_fd_ostream *statsKPUOS;
        std::set<llvm::Value *> taintedPathConds;
    };

}

#endif