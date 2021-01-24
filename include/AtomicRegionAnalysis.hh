#ifndef ATOMICREGIONANALYSIS_H_
#define ATOMICREGIONANALYSIS_H_
#include "LLVMEssentials.hh"
#include "PDGUtils.hh"
#include "SharedDataAnalysis.hh"
#include <map>
#include <set>

namespace pdg
{
  class AtomicRegionAnalysis : public llvm::ModulePass
  {
  public:
    using CSPair = std::pair<llvm::Instruction *, llvm::Instruction *>;
    using CSMap = std::map<llvm::Instruction *, llvm::Instruction *>;
    using LockMap = std::map<std::string, std::string>;
    using AtomicOpSet = std::set<llvm::Instruction *>;
    static char ID;
    AtomicRegionAnalysis() : llvm::ModulePass(ID){};
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Atomic Region Analysis"; }
    bool runOnModule(llvm::Module &M) override;
    CSMap &getCSMap() { return _critical_sections; }
    AtomicOpSet &getAtomicOpSet() {return _atomic_operations;}
    CSMap computeCSInFunc(llvm::Function &F);
    void setupLockMap();
    void computeCriticalSections(llvm::Module &M);
    void computeAtomicOperations(llvm::Module &M);
    void computeWarningCS();
    void computeWarningAtomicOps();
    void printWarningCS(CSPair cs_pair, llvm::Instruction &i, std::set<std::string> &modified_names);
    void printWarningAtomicOp(llvm::Instruction &i, std::set<std::string> &modified_names);
    bool isLockInst(llvm::Instruction &i);
    bool isUnlockInst(llvm::Instruction &i);
    bool isAtomicAsmString(std::string str);
    bool isAtomicOperation(llvm::Instruction &i);
    void dumpCS();
    void dumpAtomicOps();
    std::set<llvm::Instruction*> computeInstsInCS(CSPair cs_pair);

  private:
    SharedDataAnalysis* _SDA;
    CSMap _critical_sections;
    LockMap _lock_map;
    AtomicOpSet _atomic_operations;
    int _warning_cs_count;
    int _warning_atomic_op_count;
    int _cs_warning_count;
  };
} // namespace pdg

#endif