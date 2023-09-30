#ifndef _RISKY_BOUNDARY_FUNC_ANALYSIS_
#define _RISKY_BOUNDARY_FUNC_ANALYSIS_
#include "LLVMEssentials.hh"
#include "SharedDataAnalysis.hh"
#include "TaintUtils.hh"
#include "KSplitCFG.hh"
#include "json.hpp"

/*
This pass implements the analysis to quantify the attack surface related to the boundary functions that are used
by a malicious driver. The key idea is to iterate through all the boudnary kernel functions exported to driver, 
and analyze what kind of sensitive operations it can reach.
*/


namespace pdg
{
  class RiskyBoundaryAPIAnalysis : public llvm::ModulePass
  {

  public:
    static char ID;
    RiskyBoundaryAPIAnalysis() : llvm::ModulePass(ID){};
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Risky Boundary API Analysis"; }
    bool runOnModule(llvm::Module &M) override;
    // private states update
    using StoreJsonMap = std::map<llvm::StoreInst *, nlohmann::ordered_json>;
    using StoreCondMap = std::map<llvm::StoreInst *, std::set<llvm::Value *>>;
    void analyzeKernelPrivateStatesUpdate();
    void analyzeBoundaryFuncStateUpdates(llvm::Function *boundaryFunc, StoreJsonMap &storeInstsJsonMap, StoreCondMap &storeInstCondMap);
    void calculateFixedPointForPrivateStateUpdates(StoreJsonMap &storeInstJsonMap, StoreCondMap &storeInstCondMap);
    // helper funcs for the fix point calculation
    std::queue<llvm::StoreInst*> initializeQueue(const StoreCondMap &storeInstCondMap);
    bool isPathControllable(llvm::StoreInst *si, const StoreCondMap &storeInstCondMap);
    std::set<Node*> propagateTaintsForPointerOperand(llvm::StoreInst *si);
    void enqueueAffectedStores(const std::set<Node*> &taintNodes, const StoreCondMap &storeInstCondMap, std::queue<llvm::StoreInst*> &siQueue);

    // risky apis invoked by the driver
    void analyzeRiskyBoundaryKernelAPIs(nlohmann::ordered_json &riskyAPIJsonObjs);
    void handleDirectRiskyAPI(llvm::Function *boundaryFunc, nlohmann::ordered_json &riskyAPIJsonObjs, unsigned &caseID);
    void handleTransitiveRiskyAPI(llvm::Function *boundaryFunc, nlohmann::ordered_json &riskyAPIJsonObjs, unsigned &caseID);

  private:
    llvm::Module *_module;
    ProgramGraph *_PDG;
    SharedDataAnalysis *_SDA;
    PDGCallGraph *_callGraph;
    KSplitCFG *_CFG;
  };

}

#endif