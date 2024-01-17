#ifndef LOCK_ATTACK_ANALYSIS_H_
#define LOCK_ATTACK_ANALYSIS_H_
#include "LLVMEssentials.hh"
#include "RiskyFieldAnalysis.hh"
#include "RiskyBoundaryAPIAnalysis.hh"
#include "TaintUtils.hh"
#include "KSplitCFG.hh"
#include "json.hpp"

namespace pdg
{
  class LockAttackAnalysis : public llvm::ModulePass
  {
  public:
    static char ID;
    LockAttackAnalysis() : llvm::ModulePass(ID){};
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Analyze attacks relate to lock abusing"; }
    bool runOnModule(llvm::Module &M) override;
    using LockMap = std::map<std::string, std::string>;
    using CSPair = std::pair<llvm::Instruction *, llvm::Instruction *>;
    LockMap _lockMap;
    using CallInstSet = std::unordered_set<llvm::CallInst *>;
    using CSMap = std::map<llvm::Instruction *, llvm::Instruction *>;
    void setupLockMap();

    // helper functions
    void computeLockCallSites(CallInstSet &lockCallSites);
    bool isLockInst(llvm::Instruction &i);
    bool isUnlockInst(llvm::Instruction &i, std::string lockInstName);
    bool hasUnlockInstInSameBB(llvm::CallInst &lockCallInst);
    bool hasUnlockInstUnderSameControlDepVar(llvm::CallInst &lockCallInst, std::string &lockCallName);
    bool isSharedLockCall(llvm::CallInst &lockCS);
    llvm::Value *getUsedLock(llvm::CallInst &lockCS);

    CSMap computeIntraCS(llvm::Function &F);
    CSMap computeIntraCSWithLock(llvm::CallInst &lockCallInst);
    std::set<llvm::Instruction *> computeInstsInCS(CSPair csPair);

    // Atk 1: compute unpaired lock call sites
    CallInstSet computeUnpairedLockCallSites(CallInstSet &lockCallSites);
    void printUnpairedLockCallSites(CallInstSet &unpairedLockCS);
    
    // Atk2: compute lock calls that under conditions
    void computeLockCallSiteUnderConditions(CallInstSet &lockCallSites);

    // Atk3: compute lock region that have linked list access, or loop within
    void computeCSLoop(CallInstSet &lockCallSites);

    // protocol violation related attacks, should move the impl to a separate file later
    void computeKernelInterfaceFuncCSUnderCondition();
    void computeDrvCallBackCallSite();
    void computeCorruptedCallBackRetVal();
    // semantic violation
    void computeBugOnLoc();
    void computeRiskyDirectRefCount(nlohmann::ordered_json &riskyRefCJsons);
    bool isRefCountCall(llvm::CallInst &CI);
    bool isAtomicTRefCount(llvm::CallInst &CI);
    bool isRefCntTRefCount(llvm::CallInst &CI);

  private:
    llvm::Module *_module;
    ProgramGraph *_PDG;
    SharedDataAnalysis *_SDA;
    PDGCallGraph *_callGraph;
    KSplitCFG *_CFG;
  };
}

#endif