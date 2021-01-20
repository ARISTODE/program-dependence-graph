#include "PDGNode.hh"

using namespace llvm;

void pdg::Node::addNeighbor(Node &neighbor, EdgeType edge_type)
{
  Edge *edge = new Edge(this, &neighbor, edge_type);
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

std::set<pdg::Node *> pdg::Node::getOutNeighbors()
{
  std::set<Node *> out_neighbors;
  for (auto edge : _out_edge_set)
  {
    out_neighbors.insert(edge->getDstNode());
  }
  return out_neighbors;
}