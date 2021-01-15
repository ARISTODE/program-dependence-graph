#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "LLVMEssentials.hh"
#include "PDGNode.hh"
#include "PDGEdge.hh"
#include "CallWrapper.hh"
#include "FunctionWrapper.hh"
#include "PDGEnums.hh"
#include <unordered_map>
#include <map>
#include <set>

namespace pdg
{
  class Node;
  class Edge;
  class ProgramGraph final
  {
    typedef std::unordered_map<llvm::Value *, Node *> ValueNodeMap;
    typedef std::unordered_map<llvm::Function *, FunctionWrapper *> FuncWrapperMap;
    typedef std::unordered_map<llvm::CallInst *, CallWrapper *> CallWrapperMap;
    typedef std::unordered_map<Node *, llvm::DIType *> NodeDIMap;

  private:
    ValueNodeMap _val_node_map;
    FuncWrapperMap _func_wrapper_map;
    CallWrapperMap _call_wrapper_map;
    NodeDIMap _node_di_type_map;
    std::vector<Edge *> _edge_set;

  public:
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

    ValueNodeMap::iterator begin() { return _val_node_map.begin(); }
    ValueNodeMap::iterator end() { return _val_node_map.end(); }
    ValueNodeMap &getValueNodeMap() { return _val_node_map; }
    FuncWrapperMap &getFuncWrapperMap() { return _func_wrapper_map; }
    CallWrapperMap &getCallWrapperMap() { return _call_wrapper_map; }
    NodeDIMap &getNodeDIMap() { return _node_di_type_map; }
    void build(llvm::Module &M);
    bool hasNode(llvm::Value &v);
    bool hasFuncWrapper(llvm::Function &F) { return _func_wrapper_map.find(&F) != _func_wrapper_map.end(); }
    bool hasCallWrapper(llvm::CallInst &ci) { return _call_wrapper_map.find(&ci) != _call_wrapper_map.end(); }
    Node *getNode(llvm::Value &v);
    FunctionWrapper *getFuncWrapper(llvm::Function &F) { return _func_wrapper_map[&F]; }
    CallWrapper *getCallWrapper(llvm::CallInst &ci) { return _call_wrapper_map[&ci]; }
    void addEdge(Edge &e) { _edge_set.push_back(&e); }
    int numEdge() { return _edge_set.size(); }
    int numNode() { return _val_node_map.size(); }
    void bindDITypeToNodes(llvm::Module &M);
    llvm::DIType* computeNodeDIType(Node* n);
  };
} // namespace pdg

#endif