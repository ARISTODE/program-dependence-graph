#ifndef ATOMICREGIONANALYSIS_H_
#define ATOMICREGIONANALYSIS_H_
#include "LLVMEssentials.hh"
#include "llvm/Analysis/CallGraph.h"
#include "PDGUtils.hh"
#include "DataAccessAnalysis.hh"
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
    void setupFenceNames();
    void computeBoundaryObjects(llvm::Module &M);
    void computeCriticalSections(llvm::Module &M);
    void computeAtomicOperations(llvm::Module &M);
    void computeWarningCS();
    void computeWarningAtomicOps();
    void collectBarriersInFunc(llvm::Function &F);
    void computeModifedNames(Node &node, std::set<std::string> &modified_names);
    void printWarningCS(CSPair cs_pair, llvm::Value &v, llvm::Function &f, std::set<std::string> &modified_names, std::string source_type);
    void printWarningAtomicOp(llvm::Instruction &i, std::set<std::string> &modified_names, std::string source_type);
    bool isLockInst(llvm::Instruction &i);
    bool isRcuLockInst(llvm::Instruction &i); // only read is counted for now
    bool isSeqLockInst(llvm::Instruction &i);
    bool isUnlockInst(llvm::Instruction &i, std::string lock_inst_name);
    bool isAtomicFenceString(std::string str);
    bool isAtomicAsmString(std::string str);
    bool isAtomicOperation(llvm::Instruction &i);
    bool isAliasOfBoundaryPtrs(llvm::Value &v);
    std::set<llvm::Value*> computeBoundaryAliasPtrs(llvm::Value &v);
    // sync stub generation
    void generateSyncStubForTree(Tree* tree, llvm::raw_string_ostream &read_proj_str, llvm::raw_string_ostream &write_proj_str);
    void generateSyncStubProjFromTreeNode(TreeNode &tree_node, llvm::raw_string_ostream &read_proj_str, llvm::raw_string_ostream &write_proj_str, std::queue<TreeNode *> &node_queue, std::string indent_level);
    void dumpCS();
    void dumpAtomicOps();
    std::set<llvm::Instruction*> computeInstsInCS(CSPair cs_pair);
    std::set<llvm::Function *> getFuncsNeedSynStubGen() { return _funcs_need_sync_stub_gen; }
    bool isFuncNeedSyncStubGen(llvm::Function &F) { return _funcs_need_sync_stub_gen.find(&F) == _funcs_need_sync_stub_gen.end(); }
    DataAccessAnalysis *getDAA() { return _DAA; }

  private:
    SharedDataAnalysis *_SDA;
    DataAccessAnalysis *_DAA;
    KSplitStats *_ksplit_stats;
    CSMap _critical_sections;
    LockMap _lock_map;
    AtomicOpSet _atomic_operations;
    BoundaryPtrSet _boundary_ptrs;
    PDGCallGraph *_call_graph;
    int _warning_cs_count;
    int _warning_atomic_op_count;
    int _cs_warning_count;
    std::set<std::string> _fence_names;
    std::set<std::string> _processed_func_names;
    std::set<llvm::Function *> _funcs_need_sync_stub_gen;
    std::map<llvm::Instruction *, Tree *> _sync_data_inst_tree_map;
    std::ofstream _sync_stub_file;
  };
} // namespace pdg

#endif