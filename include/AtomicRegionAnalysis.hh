#ifndef ATOMICREGIONANALYSIS_H_
#define ATOMICREGIONANALYSIS_H_
#include "LLVMEssentials.hh"
#include "PDGUtils.hh"
#include <map>
#include <set>

namespace pdg
{
  class AtomicRegionAnalysis : public llvm::ModulePass
  {
  public:
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
    bool isLockInst(llvm::Instruction &i);
    bool isUnlockInst(llvm::Instruction &i);
    bool isAtomicAsmString(std::string str);
    bool isAtomicOperation(llvm::Instruction &i);
    void dumpCS();
    void dumpAtomicOps();

  private:
    CSMap _critical_sections;
    LockMap _lock_map;
    AtomicOpSet _atomic_operations;
  };
} // namespace pdg

#endif