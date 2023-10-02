#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "LLVMEssentials.hh"
#include "PDGNode.hh"
#include "PDGEdge.hh"
#include "Tree.hh"
#include "CallWrapper.hh"
#include "FunctionWrapper.hh"
#include "PDGEnums.hh"
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>

namespace pdg
{
  class Node;
  class Edge;

  class GenericGraph
  {
  public:
    using PathVecs = std::vector<std::vector<llvm::Value *>>;
    typedef std::unordered_map<llvm::Value *, Node *> ValueNodeMap;
    typedef std::set<Edge *> EdgeSet;
    typedef std::set<Node *> NodeSet;
    ValueNodeMap::iterator val_node_map_begin() { return _valNodeMap.begin(); }
    ValueNodeMap::iterator val_node_map_end() { return _valNodeMap.end(); }
    GenericGraph() = default;
    NodeSet::iterator begin() { return _nodeSet.begin(); }
    NodeSet::iterator end() { return _nodeSet.end(); }
    NodeSet::iterator begin() const { return _nodeSet.begin(); }
    NodeSet::iterator end() const { return _nodeSet.end(); }
    virtual void build(llvm::Module &M) = 0;
    void addEdge(Edge &e) { _edgeSet.insert(&e); }
    void addNode(Node &n) { _nodeSet.insert(&n); }
    Node *getNode(llvm::Value &v);
    bool hasNode(llvm::Value &v);
    int numEdge() { return _edgeSet.size(); }
    int numNode() { return _valNodeMap.size(); }
    void setIsBuild() { _isBuild = true; }
    bool isBuild() { return _isBuild; }
    bool canReach(Node &src, Node &dst, std::set<EdgeType> &includeEdgeTypes, std::set<std::vector<llvm::Function *>> *allPaths, bool recordPath);
    void dfs(Node *currentNode, Node &dst, std::set<EdgeType> &includeEdgeTypes, std::unordered_set<Node *> &visited, std::vector<llvm::Function *> &currentPath, std::set<std::vector<llvm::Function *>> *allPaths, bool recordPath);
    std::unordered_set<Node *> findNodesReachedByEdge(Node &src, EdgeType edgeTy);
    std::unordered_set<Node *> findNodesReachedByEdges(Node &src, std::set<EdgeType> &edgeTypes, bool isBackward = false);
    bool findPathDFS(Node *src, Node *dst, std::vector<std::pair<Node *, Edge *>> &path, std::unordered_set<Node *> &visited, std::set<EdgeType> &edgeTypes);
    PathVecs computePaths(Node &src, Node &sink); // compute all pathes
    void computePathsHelper(PathVecs &path_vecs, Node &src, Node &sink, std::vector<llvm::Value *> cur_path, std::unordered_set<llvm::Value *> visited_vals, bool &found_path);
    void printPath(std::vector<std::pair<Node *, Edge *>> &path, llvm::raw_fd_ostream &OS);
    void convertPathToString(std::vector<std::pair<Node *, Edge *>> &path, llvm::raw_string_ostream &ss);
    ValueNodeMap &getValueNodeMap() { return _valNodeMap; }

  protected:
    ValueNodeMap _valNodeMap;
    EdgeSet _edgeSet;
    NodeSet _nodeSet;
    bool _isBuild = false;
  };

  class ProgramGraph : public GenericGraph
  {
  public:
    typedef std::unordered_map<llvm::Function *, FunctionWrapper *> FuncWrapperMap;
    typedef std::unordered_map<llvm::CallInst *, CallWrapper *> CallWrapperMap;
    typedef std::unordered_map<Node *, llvm::DIType *> NodeDIMap;
    typedef std::unordered_map<llvm::GlobalVariable*, Tree*> GlobalVarTreeMap;

    ProgramGraph() = default;
    ProgramGraph(const ProgramGraph &) = delete;
    ProgramGraph(ProgramGraph &&) = delete;
    ProgramGraph &operator=(const ProgramGraph &) = delete;
    ProgramGraph &operator=(ProgramGraph &&) = delete;
    static ProgramGraph &getInstance()
    {
      static ProgramGraph g{};
      return g;
    }

    FuncWrapperMap &getFuncWrapperMap() { return _func_wrapper_map; }
    CallWrapperMap &getCallWrapperMap() { return _call_wrapper_map; }
    NodeDIMap &getNodeDIMap() { return _node_di_type_map; }
    GlobalVarTreeMap &getGlobalVarTreeMap() { return _global_var_tree_map; }
    void build(llvm::Module &M) override;
    void buildGlobalVariables(llvm::Module &M);
    void buildFunctions(llvm::Module &M);
    void buildFunctionInstructions(llvm::Function &F, FunctionWrapper *func_w);
    void buildCallGraphAndCallSites(llvm::Module &M);
    void handleCallSites(llvm::Module &M, llvm::CallInst *ci);
    void bindDITypeToNodes(llvm::Module &M);
    void bindDITypeToLocalVariables(FunctionWrapper *fw);
    void bindDITypeToInstructions(llvm::Function &F);
    void bindDITypeToGlobalVariables(llvm::Module &M);
    llvm::DIType *computeNodeDIType(Node &n);
    bool hasFuncWrapper(llvm::Function &F) { return _func_wrapper_map.find(&F) != _func_wrapper_map.end(); }
    bool hasCallWrapper(llvm::CallInst &ci) { return _call_wrapper_map.find(&ci) != _call_wrapper_map.end(); }
    FunctionWrapper *getFuncWrapper(llvm::Function &F) { return _func_wrapper_map[&F]; }
    CallWrapper *getCallWrapper(llvm::CallInst &ci) { return _call_wrapper_map[&ci]; }
    void addTreeNodesToGraph(Tree &tree);
    void addFormalTreeNodesToGraph(FunctionWrapper &func_w);
    std::unordered_set<llvm::Value *> &getAllocators() { return _allocators; }
    std::set<llvm::Value *> &getDeallocators() { return _deallocators; }
    
  private:
    FuncWrapperMap _func_wrapper_map;
    CallWrapperMap _call_wrapper_map;
    GlobalVarTreeMap _global_var_tree_map;
    NodeDIMap _node_di_type_map;
    std::unordered_set<llvm::Value *> _allocators;
    std::set<llvm::Value *> _deallocators;
  };
} // namespace pdg

#endif