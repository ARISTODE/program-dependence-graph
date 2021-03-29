#include "TaintBoundaryAnalysis.hh"

char pdg::TaintBoundaryAnalysis::ID = 0;

using namespace llvm;

void pdg::TaintBoundaryAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<ProgramDependencyGraph>();
  AU.setPreservesAll();
}

bool pdg::TaintBoundaryAnalysis::runOnModule(Module &M)
{
  _module = &M;
  _PDG = getAnalysis<ProgramDependencyGraph>().getPDG();
  _call_graph = &PDGCallGraph::getInstance();
  identifyTaintSources();
  propagateTaints();
  computeBoundaryFuncs();
  dumpBoundaryFuncs();
  return false;
}

void pdg::TaintBoundaryAnalysis::identifyTaintSources()
{
  for (auto node_iter = _PDG->begin(); node_iter != _PDG->end(); ++node_iter)
  {
    auto node_type = (*node_iter)->getNodeType();
    if (node_type == GraphNodeType::INST_ANNO_GLOBAL || node_type == GraphNodeType::INST_ANNO_LOCAL)
    {
      for (auto in_edge : (*node_iter)->getInEdgeSet())
      {
        if (in_edge->getEdgeType() == EdgeType::ANNO_VAR)
        {
          _taint_sources.insert(in_edge->getSrcNode());
        }
      }
    }
  }

  for (auto taint_node : _taint_sources)
  {
    errs() << *taint_node->getValue() << "\n";
  }
}

void pdg::TaintBoundaryAnalysis::propagateTaints()
{
  for (auto taint_source : _taint_sources)
  {
    std::set<EdgeType> edge_types = {
        EdgeType::DATA_DEF_USE,
        EdgeType::CONTROLDEP_CALLINV,
        EdgeType::CONTROLDEP_CALLRET,
        EdgeType::PARAMETER_IN,
        EdgeType::DATA_ALIAS,
        EdgeType::DATA_RET};

    auto reachable_nodes = _PDG->findNodesReachableByEdges(*taint_source, edge_types);
    for (auto node : reachable_nodes)
    {
      Function* node_func = node->getFunc();
      if (node_func != nullptr)
        _taint_funcs.insert(node_func);
    }
  }
}

void pdg::TaintBoundaryAnalysis::computeBoundaryFuncs()
{
  for (auto taint_func : _taint_funcs)
  {
    Node* func_node = _call_graph->getNode(*taint_func);
    if (func_node == nullptr)
      continue;
    auto callees = func_node->getOutNeighborsWithDepType(EdgeType::CONTROLDEP_CALLINV);
    auto callers = func_node->getInNeighborsWithDepType(EdgeType::CONTROLDEP_CALLINV);
    for (auto callee : callees)
    {
      Value* callee_val = callee->getValue();
      assert(callee_val != nullptr && "error processing nullptr func in PDGCallGraph! \n");
      Function* callee_func = cast<Function>(callee_val);
      if (_taint_funcs.find(callee_func) == _taint_funcs.end())
      {
        _tainted_boundary_funcs.insert(taint_func->getName().str());
        _untainted_boundary_funcs.insert(callee_func->getName().str());
      }
    }

    for (auto caller : callers)
    {
      Value* caller_val = caller->getValue();
      assert(caller_val != nullptr && "error processing nullptr func in PDGCallGraph! \n");
      Function* caller_func = cast<Function>(caller_val);
      if (_taint_funcs.find(caller_func) == _taint_funcs.end())
      {
        _untainted_boundary_funcs.insert(caller_func->getName().str());
        _tainted_boundary_funcs.insert(taint_func->getName().str());
      }
    }
  }
}

void pdg::TaintBoundaryAnalysis::dumpBoundaryFuncs()
{
  dumpToFile("imported_funcs", _untainted_boundary_funcs);
  dumpToFile("exported_funcs", _tainted_boundary_funcs);
  std::set<std::string> taint_func_names;
  for (auto _taint_func : _taint_funcs)
  {
    taint_func_names.insert(_taint_func->getName().str());
  }
  dumpToFile("driver_funcs", taint_func_names);
}

void pdg::TaintBoundaryAnalysis::dumpToFile(std::string file_name, std::set<std::string> &names)
{
  std::ofstream output_file(file_name);
  for (auto name: names)
  {
    output_file << name << "\n";
  }
  output_file.close();
}

static RegisterPass<pdg::TaintBoundaryAnalysis>
    TaintBoundaryAnalysis("taint-boundary", "Taint Boundary Analysis", false, true);