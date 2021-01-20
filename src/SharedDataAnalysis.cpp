#include "SharedDataAnalysis.hh"

char pdg::SharedDataAnalysis::ID = 0;

using namespace llvm;

void pdg::SharedDataAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.setPreservesAll();
}

bool pdg::SharedDataAnalysis::runOnModule(llvm::Module &M)
{
  return false;
}

void pdg::SharedDataAnalysis::computeSharedDataVars()
{
  
}

void pdg::SharedDataAnalysis::computeSharedFieldID()
{
}

static RegisterPass<pdg::SharedDataAnalysis>
    SharedDataAnalysis("-shared-data", "Shared Data Analysis", false, true);