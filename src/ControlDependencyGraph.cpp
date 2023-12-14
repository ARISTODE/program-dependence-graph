#include "ControlDependencyGraph.hh"

char pdg::ControlDependencyGraph::ID = 0;

using namespace llvm;
bool pdg::ControlDependencyGraph::runOnFunction(Function &F)
{
  auto &call_g = PDGCallGraph::getInstance();
  ProgramGraph &g = ProgramGraph::getInstance();
  Module &M = *F.getParent();
  if (!g.isBuild())
  {
    g.build(M);
    g.bindDITypeToNodes(M);
  }
  // if (!call_g.isBuildFuncNode(F))
  //   return false;
  _PDT = &getAnalysis<PostDominatorTreeWrapperPass>().getPostDomTree();
  addControlDepFromEntryNodeToEntryBlock(F);
  addControlDepFromDominatedBlockToDominator(F);
  return false;
}

void pdg::ControlDependencyGraph::addControlDepFromNodeToBB(Node &n, BasicBlock &BB, EdgeType edge_type)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  for (auto &inst : BB)
  {
    Node* inst_node = g.getNode(inst);
    // TODO: a special case when gep is used as a operand in load. Fix later
    if (inst_node != nullptr)
      n.addNeighbor(*inst_node, edge_type);
    // assert(inst_node != nullptr && "cannot find node for inst\n");
  }
}

void pdg::ControlDependencyGraph::addControlDepFromEntryNodeToEntryBlock(Function &F)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  FunctionWrapper* func_w = g.getFuncWrapperMap()[&F];
  addControlDepFromNodeToBB(*func_w->getEntryNode(), F.getEntryBlock(), EdgeType::CONTROL);
}

void pdg::ControlDependencyGraph::addControlDepFromDominatedBlockToDominator(Function &F)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  for (auto &BB : F)
  {
    for (auto succ_iter = succ_begin(&BB); succ_iter != succ_end(&BB); succ_iter++)
    {
      BasicBlock *succ_bb = *succ_iter;
      // Check if the current basic block is not the same as its successor (loop),
      // and if the successort block doesn't postdominate the current block
      if (&BB == &*succ_bb || !_PDT->dominates(&*succ_bb, &BB))
      {
        // get terminator and connect with the dependent block
        Instruction *terminator = BB.getTerminator();
        // handle switch instruction
        if (SwitchInst *switchI = dyn_cast<SwitchInst>(terminator))
        {
          auto condVal = switchI->getCondition();
          auto condNode = g.getNode(*condVal);
          if (!condNode)
            continue;
          for (unsigned i = 0, numCases = switchI->getNumSuccessors(); i < numCases; ++i)
          {
            BasicBlock *targetBlock = switchI->getSuccessor(i);
            addControlDepFromNodeToBB(*condNode, *targetBlock, EdgeType::CONTROL);
          }

          // Handle the default target block if it exists
          BasicBlock *defaultBlock = switchI->getDefaultDest();
          if (defaultBlock != nullptr)
            addControlDepFromNodeToBB(*condNode, *defaultBlock, EdgeType::CONTROL);
        }

        // handle other branch insts
        if (BranchInst *bi = dyn_cast<BranchInst>(terminator))
        {
          if (!bi->isConditional() || !bi->getCondition())
            break;
          // Node *cond_node = g.getNode(*bi->getCondition());
          // if (!cond_node)
          //   break;
          Node *branch_node = g.getNode(*bi);
          if (branch_node == nullptr)
            break;
          // Initialize a flag to track if a control dependency was added
          bool controlDepAdded = false;
          // Check if succ_bb is post-dominated by BB
          BasicBlock *nearestCommonDominator = _PDT->findNearestCommonDominator(&BB, succ_bb);
          if (!_PDT->dominates(_PDT->getNode(succ_bb), _PDT->getNode(&BB)))
          {
            if (nearestCommonDominator != &BB)
            {
              addControlDepFromNodeToBB(*branch_node, *succ_bb, EdgeType::CONTROL);
              controlDepAdded = true;
            }
          }

          // Check for loop constructs
          if (nearestCommonDominator == &BB && !controlDepAdded)
          {
            addControlDepFromNodeToBB(*branch_node, *succ_bb, EdgeType::CONTROL);
            controlDepAdded = true;
          }

          // for (auto *cur = _PDT->getNode(&*succ_bb); cur != _PDT->getNode(nearestCommonDominator); cur = cur->getIDom())
          // {
          //   // avoid adding dep to all the block that post dominate the BB
          //   if (_PDT->dominates(cur, _PDT->getNode(&BB)))
          //     continue;
          //   addControlDepFromNodeToBB(*branch_node, *cur->getBlock(), EdgeType::CONTROL);
          // }
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
