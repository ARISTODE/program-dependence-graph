#include "PDGNode.hh"

using namespace llvm;

void pdg::Node::addNeighbor(Node &neighbor, EdgeType edgeTy)
{
  if (hasOutNeighborWithEdgeType(neighbor, edgeTy))
    return;
  Edge *edge = new Edge(this, &neighbor, edgeTy);
  addOutEdge(*edge);
  neighbor.addInEdge(*edge);
}

std::set<pdg::Node *> pdg::Node::getInNeighbors()
{
  std::set<Node *> in_neighbors;
  for (auto edge : _in_edge_set)
  {
    in_neighbors.insert(edge->getSrcNode());
  }
  return in_neighbors;
}

std::set<pdg::Node *> pdg::Node::getInNeighborsWithDepType(pdg::EdgeType edgeTy)
{
  std::set<Node *> in_neighbors_with_dep_type;
  for (auto edge : _in_edge_set)
  {
    if (edge->getEdgeType() == edgeTy)
      in_neighbors_with_dep_type.insert(edge->getSrcNode());
  }
  return in_neighbors_with_dep_type;
}

std::set<pdg::Node *> pdg::Node::getOutNeighbors()
{
  std::set<Node *> out_neighbors;
  for (auto edge : _out_edge_set)
  {
    out_neighbors.insert(edge->getDstNode());
  }
  return out_neighbors;
}

std::set<pdg::Node *> pdg::Node::getOutNeighborsWithDepType(pdg::EdgeType edgeTy)
{
  std::set<Node *> out_neighbors_with_dep_type;
  for (auto edge : _out_edge_set)
  {
    if (edge->getEdgeType() == edgeTy)
      out_neighbors_with_dep_type.insert(edge->getDstNode());
  }
  return out_neighbors_with_dep_type;
}

bool pdg::Node::hasInNeighborWithEdgeType(Node &n, EdgeType edgeTy)
{
  for (auto e : _in_edge_set)
  {
    if (e->getSrcNode() == &n && e->getEdgeType() == edgeTy)
      return true;
  }
  return false;
}

bool pdg::Node::hasOutNeighborWithEdgeType(Node &n, EdgeType edgeTy)
{
  for (auto e : _out_edge_set)
  {
    if (e->getDstNode() == &n && e->getEdgeType() == edgeTy)
      return true;
  }
  return false;
}

std::set<pdg::Node *> pdg::Node::getNeighborsWithDepType(std::set<pdg::EdgeType> edgeTypes)
{
  std::set<Node *> ret;
  for (auto edge : _in_edge_set)
  {
    if (edgeTypes.find(edge->getEdgeType()) != edgeTypes.end())
      ret.insert(edge->getSrcNode());
  }

  for (auto edge : _out_edge_set)
  {
    if (edgeTypes.find(edge->getEdgeType()) != edgeTypes.end())
      ret.insert(edge->getDstNode());
  }
  return ret;
}

bool pdg::Node::isAddrVarNode()
{
  for (auto in_edge : _in_edge_set)
  {
    if (in_edge->getEdgeType() == EdgeType::PARAMETER_IN && in_edge->getSrcNode()->getNodeType() == GraphNodeType::FORMAL_IN)
      return true;
  }
  return false;
}

pdg::Node *pdg::Node::getAbstractTreeNode()
{
  for (auto in_edge : _in_edge_set)
  {
    if (in_edge->getEdgeType() == EdgeType::PARAMETER_IN && in_edge->getSrcNode()->getNodeType() == GraphNodeType::FORMAL_IN)
      return in_edge->getSrcNode();
  }
  return nullptr;
}
