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

  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;

    for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
    {
      Instruction *curInst = &*instIter;
      auto curInstNode = getNode(*curInst);
      // normal case connect inst with next instruction
      auto nextInst = instIter->getNextNonDebugInstruction();
      if (nextInst)
      {
        // Assuming your Node class has an addEdge method
        auto nextInstNode = getNode(*nextInst);
        curInstNode->addNeighbor(*nextInstNode, EdgeType::CONTROL_FLOW);
      }

      if (curInst->isTerminator())
      {
        for (auto succId = 0; succId < curInst->getNumSuccessors(); ++succId)
        {
          auto succBB = curInst->getSuccessor(succId);
          auto firstBBInst = succBB->getFirstNonPHI();
          auto firstBBInstNode = getNode(*firstBBInst);
          if (firstBBInstNode)
          {
            curInstNode->addNeighbor(*firstBBInstNode, EdgeType::CONTROL_FLOW);
          }
        }
      }

      // callinst: connect inst with the first instruction in the called function
      if (CallInst *ci = dyn_cast<CallInst>(curInst))
      {
        auto calledFunc = pdgutils::getCalledFunc(*ci);
        if (!calledFunc)
          continue;
        if (calledFunc->isDeclaration())
          continue;
        auto beginInstIter = inst_begin(*calledFunc);
        auto beginInst = &*beginInstIter;
        auto beginInstNode = getNode(*beginInst);
        curInstNode->addNeighbor(*beginInstNode, EdgeType::CONTROL_FLOW);

        // handle all the return instructions in the called functions
        for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
        {
          auto i = &*instIter;
          if (isa<ReturnInst>(i))
          {
            auto returnInstNode = getNode(*i);
            returnInstNode->addNeighbor(*curInstNode, EdgeType::CONTROL_FLOW);
          }
        }
      }

      // branch/switch inst: connect inst with all the instructions in the BB
      if (BranchInst *bi = dyn_cast<BranchInst>(curInst))
      {
        for (auto successor : bi->successors())
        {
          auto nextInst = &successor->front(); // first instruction in the BB
          auto nextInstNode = getNode(*nextInst);
          curInstNode->addNeighbor(*nextInstNode, EdgeType::CONTROL_FLOW);
        }
      }
      // switch inst
      if (SwitchInst *si = dyn_cast<SwitchInst>(curInst))
      {
        for (auto successorNum = 0; successorNum < si->getNumSuccessors(); successorNum++)
        {
          auto successor = si->getSuccessor(successorNum);
          auto nextInst = &successor->front();
          auto nextInstNode = getNode(*nextInst);
          curInstNode->addNeighbor(*nextInstNode, EdgeType::CONTROL_FLOW);
        }
      }
    }
  }

  // connectControlFlowEdges(M);
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

void pdg::KSplitCFG::computePathConditionsBetweenNodes(Node &srcNode, Node &dstNode, std::set<Value*> &conditionValues)
{
  std::unordered_set<Node*> visited;
  std::vector<std::pair<Node*, Edge*>> path;
  std::set<EdgeType> edgeTypes = {EdgeType::CONTROL_FLOW};
  findPathDFS(&srcNode, &dstNode, path, visited, edgeTypes);
  
  // return value
  for (auto p : path)
  {
    auto node = p.first;
    auto nodeVal = node->getValue();

    if (!nodeVal)
      continue;

    if (auto inst = dyn_cast<Instruction>(nodeVal))
    {
      if (auto *BI = dyn_cast<BranchInst>(inst))
      {
        // This is a branch instruction, get its condition
        if (BI->isConditional())
        {
          conditionValues.insert(BI->getCondition());
        }
      }
      else if (auto *SI = dyn_cast<SwitchInst>(inst))
      {
        // This is a switch instruction, get its condition
        conditionValues.insert(SI->getCondition());
      }
    }
  }
}