#include "KSplitCFG.hh"
using namespace llvm;

void pdg::KSplitCFG::connectControlFlowEdges(Module &M)
{
  PDGCallGraph &call_graph = PDGCallGraph::getInstance();
  if (!call_graph.isBuild())
    call_graph.build(M);

  for (auto it = _valNodeMap.begin(); it != _valNodeMap.end(); ++it)
  {
    auto val = it->first;
    auto instNode = it->second;
    Function *cur_func = nullptr;
    if (Instruction *i = dyn_cast<Instruction>(val))
      cur_func = i->getFunction();

    assert(cur_func != nullptr && "cannot connect control flow edges (empty function)");
    auto cur_func_node = call_graph.getNode(*cur_func);
    for (auto out_neighbor : cur_func_node->getOutNeighbors())
    {
      auto val = out_neighbor->getValue();
      if (Function *func = dyn_cast<Function>(val))
      {
        if (func->isDeclaration())
          continue;
        auto instIter = inst_begin(*func);
        auto first_inst = &*instIter;
        auto first_inst_node = _valNodeMap[first_inst];
        instNode->addNeighbor(*first_inst_node, EdgeType::CONTROL_FLOW);
        while (instIter != inst_end(*func))
        {
          if (isa<ReturnInst>(&*instIter))
          {
            auto return_inst_node = _valNodeMap[&*instIter];
            return_inst_node->addNeighbor(*instNode, EdgeType::CONTROL_FLOW);
          }
          instIter++;
        }
      }
    }
    // for all possibly called function, connect the call instruction
    // with the first instruction in the called function
    // else connect the instruction with the next inst
    // handle branch inst
    if (BranchInst *bi = dyn_cast<BranchInst>(val))
    {
      for (auto successor : bi->successors())
      {
        auto next_inst = &successor->front();
        auto next_inst_node = _valNodeMap[next_inst];
        instNode->addNeighbor(*next_inst_node, EdgeType::CONTROL_FLOW);
      }
    }
    else
    {
      // handle normal case
      auto next_inst = bi->getNextNonDebugInstruction();
      auto next_inst_node = _valNodeMap[next_inst];
      instNode->addNeighbor(*next_inst_node, EdgeType::CONTROL_FLOW);
    }
  }
}

void pdg::KSplitCFG::build(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;

    for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
    {
      // add nodes
      Node *n = new Node(*instIter, GraphNodeType::INST);
      _valNodeMap.insert(std::pair<Value *, Node *>(&*instIter, n));
      addNode(*n);
    }
  }

  connectControlFlowEdges(M);
  _isBuild = true;
}

std::set<pdg::Node *> pdg::KSplitCFG::searchCallNodes(pdg::Node &start_node, std::string target_func_name)
{
  std::set<Node *> ret;
  std::queue<Node*> node_q;
  std::set<Node*> seenNodes;
  node_q.push(&start_node);
  seenNodes.insert(&start_node);
  while (!node_q.empty())
  {
    auto cur_node = node_q.front();
    node_q.pop();
    for (auto neighbor : cur_node->getOutNeighbors())
    {
      auto val = neighbor->getValue();
      if (CallInst *ci = dyn_cast<CallInst>(val))
      {
        auto called_func = pdgutils::getCalledFunc(*ci);
        if (called_func == nullptr)
          continue;
        std::string calleeName = pdgutils::stripFuncNameVersionNumber(called_func->getName().str());
        if (calleeName == target_func_name)
          ret.insert(neighbor);
      }
      else
      {
        if (seenNodes.find(neighbor) != seenNodes.end())
          continue;
        seenNodes.insert(neighbor);
        node_q.push(neighbor);
      }
    }
  }
  return ret;
}

std::set<Instruction *> pdg::KSplitCFG::computeNodesBetweenPoints(Instruction &start, Instruction &end)
{
  std::queue<Node*> node_q;
  std::set<Node*> seenNodes;
  auto start_node = _valNodeMap[&start];
  node_q.push(start_node);
  seenNodes.insert(start_node);
  while (!node_q.empty())
  {
  }
}