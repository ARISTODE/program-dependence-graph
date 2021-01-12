#include "DataDependencyGraph.hh"

using namespace llvm;

char pdg::DataDependencyGraph::ID = 0;

void pdg::DataDependencyGraph::addAliasEdges(Instruction &inst)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  Function* func = inst.getFunction();
  auto inst_mem_loc = MemoryLocation::getOrNone(&inst); // get optional type
  if (!inst_mem_loc)
    return;
  for (auto inst_iter = inst_begin(func); inst_iter != inst_end(func); inst_iter++)
  {
    auto tmp_inst_mem_loc = MemoryLocation::getOrNone(&*inst_iter);
    if (!tmp_inst_mem_loc)
      continue;
    AliasResult anders_aa_result = andersAA->query(*inst_mem_loc, *tmp_inst_mem_loc);
    if (anders_aa_result != NoAlias)
      g.connectNodesByVal(inst, *inst_iter, EdgeType::DATA_ALIAS) ;
  }
  return;
}

void pdg::DataDependencyGraph::addDefUseEdges(Instruction &inst)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  for (auto user : inst.users())
  {
    g.connectNodesByVal(inst, *user, EdgeType::DATA_DEF_USE);
  }
}

void pdg::DataDependencyGraph::addRAWEdges(Instruction &inst)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  // TODO: use memory SSA or memdep analysis to figure out more accurate RAW dependencies
  if (StoreInst *si = dyn_cast<StoreInst>(&inst))
  {
    Value* pointer_val = si->getPointerOperand();
    for (auto user : pointer_val->users())
    {
      if (isa<LoadInst>(user))
      {
        g.connectNodesByVal(*si, *user, EdgeType::DATA_RAW);
      }
    }
  }
}

bool pdg::DataDependencyGraph::runOnFunction(Function &F)
{
  andersAA = &getAnalysis<CFLAndersAAWrapperPass>().getResult();

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
  AU.setPreservesAll();
}

static RegisterPass<pdg::DataDependencyGraph>
    DDG("ddg", "Data Dependency Graph Construction", false, true);