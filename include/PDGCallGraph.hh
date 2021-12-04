#ifndef PDGCALLGRAPH_H_
#define PDGCALLGRAPH_H_
#include "LLVMEssentials.hh"
#include "Graph.hh"
#include "PDGUtils.hh"

namespace pdg
{
  class PDGCallGraph : public GenericGraph
  {
  public:
    using PathVecs = std::vector<std::vector<llvm::Function *>>;
    PDGCallGraph() = default;
    PDGCallGraph(const PDGCallGraph &) = delete;
    PDGCallGraph(PDGCallGraph &&) = delete;
    PDGCallGraph &operator=(const PDGCallGraph &) = delete;
    PDGCallGraph &operator=(PDGCallGraph &&) = delete;
    static PDGCallGraph &getInstance()
    {
      static PDGCallGraph g{};
      return g;
    }
    void build(llvm::Module &M) override;
    std::set<llvm::Function *> getIndirectCallCandidates(llvm::CallInst &ci, llvm::Module &M);
    bool isFuncSignatureMatch(llvm::CallInst &ci, llvm::Function &f);
    bool isTypeEqual(llvm::Type &t1, llvm::Type &t2);
    bool canReach(Node &src, Node &sink);
    void dump();
    void printPaths(Node &src, Node &sink);
    PathVecs computePaths(Node &src, Node &sink); // compute all pathes
    void computePathsHelper(PathVecs &path_vecs, Node &src, Node &sink, std::vector<llvm::Function *> cur_path, std::unordered_set<llvm::Function *> visited_funcs, bool &found_path);
    std::vector<Node*> computeTransitiveClosure(Node &src);
    void setupExcludeFuncs();
    void setupExportedFuncs();
    void setupDriverFuncs(llvm::Module &M);
    bool isExcludeFunc(llvm::Function &F);
    bool isExportedFunc(llvm::Function &F);
    // some special handling for boundary functions
    void setupBoundaryFuncs(llvm::Module &M);
    void initializeCommonCallFuncs(llvm::Function &boundary_func, std::set<llvm::Function*> &common_func);
    void collectDriverAccessedGlobalVars(llvm::Function &F);
    std::set<llvm::Function *> &getBoundaryTransFuncs() { return _boundary_trans_funcs; }
    std::set<llvm::Function *> &getTaintedFuncs() { return _taint_funcs; }
    void computeBoundaryTransFuncs();
    llvm::Function *getModuleInitFunc(llvm::Module &M);
    std::set<llvm::Function *> &getBoundaryFuncs() { return _boundary_funcs; }
    std::set<std::string> &getBoundaryFuncNames() { return _boundary_func_names; }
    std::set<llvm::GlobalVariable *> &getAnalysisGlobalVar() { return _global_var_analysis; }
    unsigned evaluateTransClosureSize(llvm::Function &F);
    void computeTaintGlobals();
    void computeTaintFuncs(llvm::Module &M);

  private:
    std::set<std::string> _exclude_func_names;
    std::set<std::string> _exported_func_names;
    std::set<std::string> _boundary_func_names;
    std::set<llvm::Value *> _taint_vals;
    std::set<llvm::Function *> _taint_funcs;
    std::set<llvm::Function *> _driver_domain_funcs;
    std::set<llvm::Function *> _boundary_funcs;
    std::set<llvm::Function *> _boundary_trans_funcs;
    std::set<llvm::GlobalVariable *> _global_var_analysis;
  };
} // namespace pdg

#endif