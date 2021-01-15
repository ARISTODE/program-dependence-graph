#ifndef NODE_H_
#define NODE_H_
#include "LLVMEssentials.hh"
#include "PDGEdge.hh"
#include "PDGEnums.hh"
#include <set>

namespace pdg
{
  class Edge;
  class Node
  {
    typedef std::set<Edge *> EdgeSet;

  private:
    llvm::Value *_val;
    llvm::Function *_func;
    bool _is_visited;
    EdgeSet _in_edge_set;
    EdgeSet _out_edge_set;
    GraphNodeType _node_type;
    llvm::DIType *_node_di_type;

  public:
    Node(GraphNodeType node_type)
    {
      _node_type = node_type;
      _is_visited = false;
      _func = nullptr;
    }
    Node(llvm::Value &v, GraphNodeType node_type)
    {
      _val = &v;
      if (auto inst = llvm::dyn_cast<llvm::Instruction>(&v))
        _func = inst->getFunction();
      _is_visited = false;
      _node_type = node_type;
    }
    void addInEdge(Edge &e) { _in_edge_set.insert(&e); }
    void addOutEdge(Edge &e) { _out_edge_set.insert(&e); }
    EdgeSet &getInEdgeSet() { return _in_edge_set; }
    EdgeSet &getOutEdgeSet() { return _out_edge_set; }
    void setNodeType(GraphNodeType node_type) { _node_type = node_type; }
    GraphNodeType getNodeType() const { return _node_type; }
    bool isVisited() { return _is_visited; }
    llvm::Function *getFunc() { return _func; }
    llvm::Value *getValue() { return _val; }
    llvm::DIType *getDIType() { return _node_di_type; }
    void setDIType(llvm::DIType &di_type) { _node_di_type = &di_type; }
    void addNeighbor(Node &neighbor, EdgeType edge_type);
  };

} // namespace pdg
#endif