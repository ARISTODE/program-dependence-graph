#include "DataAccessAnalysis.hh"

using namespace llvm;

char pdg::DataAccessAnalysis::ID = 0;

bool pdg::DataAccessAnalysis::runOnModule(Module &M)
{
  _module = &M;
  PDG = getAnalysis<ProgramDependencyGraph>().getPDG();
  // intra-procedural analysis
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    // computeIntraProcDataAccess(F);
  }
  // inter-procedural analysis 
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    // auto call_chain = uti
  }

  return false;
}

void pdg::DataAccessAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<ProgramDependencyGraph>();
  AU.setPreservesAll();
}


static RegisterPass<pdg::DataAccessAnalysis>
    PDG("-daa", "Data Access Analysis Pass", false, true);