#ifndef PDGCALLGRAPH_H_
#define PDGCALLGRAPH_H_
#include "LLVMEssentials.hh"
#include "Graph.hh"
#include "PDGUtils.hh"

namespace pdg
{
  class CallGraphInstruction;

  class PDGCallGraph : public GenericGraph
  {
  public:
    using PathVecs = std::vector<std::vector<llvm::Function *>>;
    std::unordered_set<Node*> buildFuncNodes;
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
    // bool canReach(Node &src, Node &sink);
    bool canReach(Node &src, Node &sink);
    bool findPathDFS(Node *src, Node *dst, std::vector<Node *> &path, std::unordered_set<Node *> &visited);
    bool canReach(Node &src, Node &sink, std::set<std::vector<llvm::Function *>> &allPaths, bool recordPath);
    void bfs(Node *currentNode, Node &sink, std::unordered_set<Node *> &visited, std::vector<llvm::Function *> &currentPath, std::set<std::vector<llvm::Function *>> &allPaths, bool recordPath);
    void printPath(const std::vector<Node *> &path, llvm::raw_fd_ostream &OS);
    void dump();
    void printPaths(Node &src, Node &sink);
    PathVecs computePaths(Node &src, Node &sink); // compute all pathes
    void computePathsHelper(PathVecs &path_vecs, Node &src, Node &sink, std::vector<llvm::Function *> cur_path, std::unordered_set<llvm::Function *> visited_funcs, bool &found_path);
    std::vector<Node*> computeTransitiveClosure(Node &src);
    void setupExcludeFuncs();
    void setupExportedFuncs();
    void setupDriverFuncs();
    bool isExcludeFunc(llvm::Function &F);
    bool isExportedFunc(llvm::Function &F);
    bool isDriverFunc(llvm::Function &F);
    void setupBuildFuncNodes(llvm::Module &M);
    bool isBuildFuncNode(llvm::Function &F);
    std::set<CallGraphInstruction> getCallGraphInstructions(){return _callGraphInstructions;}
    llvm::Instruction* getCallGraphInstruction(Node* parent, Node* child);
    void insertCallInstPair(llvm::Function &F, llvm::CallInst &ci);
    std::unordered_set<llvm::CallInst*> getFunctionCallSites(llvm::Function &F);

  private:
    std::set<std::string> _exclude_func_names;
    std::set<std::string> _exported_func_names;
    std::set<std::string> _driver_func_names;
    std::unordered_map<llvm::Function *, std::unordered_set<llvm::CallInst *>> _callInstMap;
    std::set<CallGraphInstruction> _callGraphInstructions;
  };



class CallGraphInstruction {
public:
    CallGraphInstruction(Node* parent, Node* child, llvm::Instruction* inst)
        : parent(parent), child(child), inst(inst) {
    }

    llvm::Instruction* getInstruction() const { return inst; }
    Node* getParent() const { return parent; }
    Node* getChild() const { return child; }
    bool operator<(const CallGraphInstruction& other) const {
        return std::tie(parent, child, inst) < std::tie(other.parent, other.child, other.inst);
    }

private:
    Node* parent;
    Node* child;
    llvm::Instruction* inst;
};

} // namespace pdg

#endif