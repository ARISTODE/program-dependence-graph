#include "ControlDependencyGraph.hh"

char pdg::ControlDependencyGraph::ID = 0;

using namespace llvm;
bool pdg::ControlDependencyGraph::runOnFunction(Function &F)
{
  _PDT = &getAnalysis<PostDominatorTreeWrapperPass>().getPostDomTree();
  addControlDepFromEntryNodeToEntryBlock(F);
  addControlDepFromDominatedBlockToDominator(F);
  return false;
}

void pdg::ControlDependencyGraph::addControlDepFromNodeToBB(Node &n, BasicBlock &BB)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  for (auto &inst : BB)
  {
    Node* inst_node = g.getNode(inst);
    // TODO: a special case when gep is used as a operand in load. Fix later
    if (inst_node != nullptr)
      n.addNeighbor(*inst_node, EdgeType::CONTROL);
    // assert(inst_node != nullptr && "cannot find node for inst\n");
  }
}

void pdg::ControlDependencyGraph::addControlDepFromEntryNodeToEntryBlock(Function &F)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  FunctionWrapper* func_w = g.getFuncWrapperMap()[&F];
  addControlDepFromNodeToBB(*func_w->getEntryNode(), F.getEntryBlock());
}

void pdg::ControlDependencyGraph::addControlDepFromDominatedBlockToDominator(Function &F)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  for (auto &BB : F)
  {
    for (auto succ_iter = succ_begin(&BB); succ_iter != succ_end(&BB); succ_iter++)
    {
      BasicBlock* succ_bb = *succ_iter;
      if (!_PDT->dominates(&BB, succ_bb))
      {
        BasicBlock* nearestCommonPostDominator = _PDT->findNearestCommonDominator(&BB, succ_bb);
        if (nearestCommonPostDominator == &BB)
        {
          // get terminator and connect with the basical block
          Instruction *terminator = BB.getTerminator();
          auto term_node = g.getNode(*terminator);
          addControlDepFromNodeToBB(*term_node, *succ_bb);
        }
      }
    }
  }
}

void pdg::ControlDependencyGraph::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<PostDominatorTreeWrapperPass>();
  AU.setPreservesAll();
}

static RegisterPass<pdg::ControlDependencyGraph>
    CDG("cdg", "Control Dependency Graph Construction", false, true);
