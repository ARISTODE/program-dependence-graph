#ifndef ATOMICREGIONANALYSIS_H_
#define ATOMICREGIONANALYSIS_H_
#include "LLVMEssentials.hh"
#include "llvm/Analysis/CallGraph.h"
#include "PDGUtils.hh"
#include "SharedDataAnalysis.hh"
#include "PDGCallGraph.hh"
#include <map>
#include <unordered_set>

namespace pdg
{
  class AtomicRegionAnalysis : public llvm::ModulePass
  {
  public:
    using CSPair = std::pair<llvm::Instruction *, llvm::Instruction *>;
    using CSMap = std::map<llvm::Instruction *, llvm::Instruction *>;
    using LockMap = std::map<std::string, std::string>;
    using AtomicOpSet = std::unordered_set<llvm::Instruction *>;
    using BoundaryPtrSet = std::unordered_set<llvm::Value *>;
    static char ID;
    AtomicRegionAnalysis() : llvm::ModulePass(ID){};
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Atomic Region Analysis"; }
    bool runOnModule(llvm::Module &M) override;
    CSMap &getCSMap() { return _critical_sections; }
    AtomicOpSet &getAtomicOpSet() {return _atomic_operations;}
    CSMap computeCSInFunc(llvm::Function &F);
    void setupLockMap();
    void computeBoundaryObjects(llvm::Module &M);
    void computeCriticalSections(llvm::Module &M);
    void computeAtomicOperations(llvm::Module &M);
    void computeWarningCS();
    void computeWarningAtomicOps();
    void computeModifedNames(Node &node, std::set<std::string> &modified_names);
    void printWarningCS(CSPair cs_pair, llvm::Value &v, llvm::Function &f, std::set<std::string> &modified_names, std::string source_type);
    void printWarningAtomicOp(llvm::Instruction &i, std::set<std::string> &modified_names, std::string source_type);
    bool isLockInst(llvm::Instruction &i);
    bool isUnlockInst(llvm::Instruction &i, std::string lock_inst_name);
    bool isAtomicAsmString(std::string str);
    bool isAtomicOperation(llvm::Instruction &i);
    bool isAliasOfBoundaryPtrs(llvm::Value &v);
    std::set<llvm::Value*> computeBoundaryAliasPtrs(llvm::Value &v);
    void dumpCS();
    void dumpAtomicOps();
    std::set<llvm::Instruction*> computeInstsInCS(CSPair cs_pair);

  private:
    SharedDataAnalysis* _SDA;
    CSMap _critical_sections;
    LockMap _lock_map;
    AtomicOpSet _atomic_operations;
    BoundaryPtrSet _boundary_ptrs;
    llvm::CallGraph *_call_graph;
    int _warning_cs_count;
    int _warning_atomic_op_count;
    int _cs_warning_count;
    std::set<std::string> processed_func_names;
  };
} // namespace pdg

#endif