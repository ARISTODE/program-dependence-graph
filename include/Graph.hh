#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "LLVMEssentials.hh"
#include "CallWrapper.hh"
#include "FunctionWrapper.hh"
#include "PDGEnums.hh"
#include <unordered_map>
#include <map>
#include <set>

namespace pdg
{
  class Node;

  class Edge
  {
    private:
      EdgeType _edge_type;
      Node *_source;
      Node *_dst;
    public:
      Edge() = delete;
      Edge(Node *source, Node *dst, EdgeType edge_type)
      {
        _source = source;
        _dst = dst;
        _edge_type = edge_type;
      }
      Edge(const Edge &e) // copy constructor
      {
        _source = e.getSrcNode();
        _dst = e.getDstNode();
        _edge_type = e.getEdgeType();
      }

      EdgeType getEdgeType() const { return _edge_type; }
      Node *getSrcNode() const { return _source; }
      Node *getDstNode() const { return _dst; }
      bool operator<(const Edge &e) const
      {
          return (_source == e.getSrcNode() && _dst == e.getDstNode() && _edge_type == e.getEdgeType());
      }
  };

  class Node
  {
    typedef std::set<Edge> EdgeSet;

  private:
    llvm::Value *_val;
    llvm::Function *_func;
    bool _is_visited;
    EdgeSet _in_edge_set;
    EdgeSet _out_edge_set;
    GraphNodeType _node_type;
    llvm::DIType *_node_di_type;

  public:
    Node(llvm::Value &v, GraphNodeType node_type)
    {
      _val = &v;
      if (auto inst = llvm::dyn_cast<llvm::Instruction>(&v))
        this->_func = inst->getFunction();
      this->_is_visited = false;
      this->_node_type = node_type;
      // _node_di_type = computeNodeDIType(v);
      }
      void addInEdge(Edge e) { _in_edge_set.insert(e); }
      void addOutEdge(Edge e) { _out_edge_set.insert(e); }
      EdgeSet &getInEdgeSet() { return _in_edge_set; }
      EdgeSet &getOutEdgeSet() { return _out_edge_set; }
      GraphNodeType getNodeType() { return _node_type; }
      bool isVisited() { return _is_visited; }
      llvm::Function *getFunc() { return _func; }
      llvm::Value *getValue() { return _val; }
      llvm::DIType* computeNodeDIType(llvm::Value &v);
  };

  class ProgramGraph final
  {
    private:
      std::unordered_map<llvm::Value*, Node*> _inst_node_map;
      std::unordered_map<llvm::Function*, FunctionWrapper*> _func_wrapper_map;
      std::unordered_map<llvm::CallInst*, CallWrapper*> _call_wrapper_map;
      std::unordered_map<llvm::Instruction*, llvm::DIType*> _inst_di_type_map;
      std::vector<Edge> _edge_set;

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

      typedef std::unordered_map<llvm::Value *, Node *> ValueNodeMap;
      typedef std::unordered_map<llvm::Function *, FunctionWrapper *> FuncWrapperMap;
      typedef std::unordered_map<llvm::CallInst *, CallWrapper *> CallWrapperMap;
      typedef std::unordered_map<llvm::Instruction *, llvm::DIType *> InstDIMap;
      ValueNodeMap &getInstNodeMap() { return _inst_node_map; }
      FuncWrapperMap &getFuncWrapperMap() { return _func_wrapper_map; }
      CallWrapperMap &getCallWrapperMap() { return _call_wrapper_map; }
      InstDIMap &getInstDITyMap() { return _inst_di_type_map; }
      void build(llvm::Module &M);
      bool hasNode(llvm::Value &v);
      Node *getNode(llvm::Value &v);
      void addEdge(Edge e) { _edge_set.push_back(e); }
      int numEdge() { return _edge_set.size(); }
      int numNode() { return _inst_node_map.size(); }
      ValueNodeMap::iterator begin() { return _inst_node_map.begin(); }
      ValueNodeMap::iterator end() { return _inst_node_map.end(); }
      void connectNodesByVal(llvm::Value &src, llvm::Value &dst, EdgeType edge_ty);
  };
} // namespace pdg

#endif