#include "Graph.hh"

using namespace llvm;
// Generic Graph
bool pdg::GenericGraph::hasNode(Value &v)
{
  return (_val_node_map.find(&v) != _val_node_map.end());
}

pdg::Node *pdg::GenericGraph::getNode(Value &v)
{
  if (!hasNode(v))
    return nullptr;
  return _val_node_map[&v];
}

// ===== Graph Traversal =====

// DFS search
bool pdg::GenericGraph::canReach(pdg::Node &src, pdg::Node &dst)
{
  // TODO: prune by call graph rechability, improve traverse efficiency
  if (canReach(src, dst, {}))
    return true;
  return false;
}

bool pdg::GenericGraph::canReach(pdg::Node &src, pdg::Node &dst, std::set<EdgeType> include_edge_types)
{
  if (&src == &dst)
    return true;

  std::set<Node *> visited;
  std::stack<Node *> node_queue;
  node_queue.push(&src);

  while (!node_queue.empty())
  {
    auto current_node = node_queue.top();
    node_queue.pop();
    if (current_node == nullptr)
      continue;
    if (visited.find(current_node) != visited.end())
      continue;
    visited.insert(current_node);
    if (current_node == &dst)
      return true;
    for (auto out_edge : current_node->getOutEdgeSet())
    {
      // exclude path
      if (include_edge_types.find(out_edge->getEdgeType()) == include_edge_types.end())
        continue;
      node_queue.push(out_edge->getDstNode());
    }
  }
  return false;
}

std::set<pdg::Node *> pdg::GenericGraph::findNodesReachedByEdge(pdg::Node &src, EdgeType edge_type)
{
  std::set<Node *> ret;
  std::queue<Node *> node_queue;
  node_queue.push(&src);
  std::set<Node*> visited;
  while (!node_queue.empty())
  {
    Node *current_node = node_queue.front();
    node_queue.pop();
    if (visited.find(current_node) != visited.end())
      continue;
    visited.insert(current_node);
    ret.insert(current_node);
    for (auto out_edge : current_node->getOutEdgeSet())
    {
      if (edge_type != out_edge->getEdgeType())
        continue;
      node_queue.push(out_edge->getDstNode());
    }
  }
  return ret;
}

std::set<pdg::Node *> pdg::GenericGraph::findNodesReachedByEdges(pdg::Node &src, std::set<EdgeType> &edge_types, bool is_backward)
{
  std::set<Node *> ret;
  std::queue<Node *> node_queue;
  node_queue.push(&src);
  std::set<Node *> visited;
  while (!node_queue.empty())
  {
    Node *current_node = node_queue.front();
    node_queue.pop();
    if (visited.find(current_node) != visited.end())
      continue;
    visited.insert(current_node);
    ret.insert(current_node);
    Node::EdgeSet edge_set;
    if (is_backward)
      edge_set = current_node->getInEdgeSet();
    else 
      edge_set = current_node->getOutEdgeSet();
    for (auto edge : edge_set)
    {
      if (edge_types.find(edge->getEdgeType()) == edge_types.end())
        continue;
      node_queue.push(edge->getDstNode());
    }
  }
  return ret;
}