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
    bool isExcludeFunc(llvm::Function &F);
    bool isExportedFunc(llvm::Function &F);

  private:
    std::set<std::string> _exclude_func_names;
    std::set<std::string> _exported_func_names;
  };
} // namespace pdg

#endif