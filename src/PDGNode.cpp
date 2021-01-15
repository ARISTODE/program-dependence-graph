#include "PDGNode.hh"

using namespace llvm;

void pdg::Node::addNeighbor(Node &neighbor, EdgeType edge_type)
{
  Edge *edge = new Edge(this, &neighbor, edge_type);
  addOutEdge(*edge);
  neighbor.addInEdge(*edge);
}