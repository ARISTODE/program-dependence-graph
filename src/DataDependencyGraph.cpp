#include "DataDependencyGraph.hh"

char pdg::DataDependencyGraph::ID = 0;

using namespace llvm;
void pdg::DataDependencyGraph::addAliasEdges(Instruction &inst)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  Function* func = inst.getFunction();
  auto inst_mem_loc = MemoryLocation::getOrNone(&inst); // get optional type
  if (!inst_mem_loc)
    return;
  for (auto inst_iter = inst_begin(func); inst_iter != inst_end(func); inst_iter++)
  {
    if (&inst == &*inst_iter)
      continue;
    auto tmp_inst_mem_loc = MemoryLocation::getOrNone(&*inst_iter);
    if (!tmp_inst_mem_loc)
      continue;
    AliasResult anders_aa_result = _anders_aa->query(*inst_mem_loc, *tmp_inst_mem_loc);
    if (anders_aa_result != NoAlias)
    {
      Node* src = g.getNode(inst);
      Node* dst = g.getNode(*inst_iter);
      if (src == nullptr || dst == nullptr)
        continue;
      src->addNeighbor(*dst, EdgeType::DATA_ALIAS);
    }
  }
  return;
}

void pdg::DataDependencyGraph::addDefUseEdges(Instruction &inst)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  for (auto user : inst.users())
  {
    Node *src = g.getNode(inst);
    Node *dst = g.getNode(*user);
    if (src == nullptr || dst == nullptr)
      continue;
    src->addNeighbor(*dst, EdgeType::DATA_DEF_USE);
  }
}

void pdg::DataDependencyGraph::addRAWEdges(Instruction &inst)
{
  if (!isa<LoadInst>(&inst))
    return;

  ProgramGraph &g = ProgramGraph::getInstance();
  auto dep_res = _mem_dep_res->getDependency(&inst);
  auto dep_inst = dep_res.getInst();

  if (!dep_inst)
    return;
  if (!isa<StoreInst>(dep_inst))
    return;

  Node *src = g.getNode(inst);
  Node *dst = g.getNode(*dep_inst);
  if (src == nullptr || dst == nullptr)
    return;
  dst->addNeighbor(*src, EdgeType::DATA_RAW);
}

bool pdg::DataDependencyGraph::runOnFunction(Function &F)
{
  _anders_aa = &getAnalysis<CFLAndersAAWrapperPass>().getResult();
  _mem_dep_res = &getAnalysis<MemoryDependenceWrapperPass>().getMemDep();
  for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); inst_iter++)
  {
    addDefUseEdges(*inst_iter);
    addRAWEdges(*inst_iter);
    addAliasEdges(*inst_iter);
  }
  return false;
}

void pdg::DataDependencyGraph::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<CFLAndersAAWrapperPass>();
  AU.addRequired<MemoryDependenceWrapperPass>();
  AU.setPreservesAll();
}

static RegisterPass<pdg::DataDependencyGraph>
    DDG("ddg", "Data Dependency Graph Construction", false, true);