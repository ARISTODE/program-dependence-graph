#include "ProgramDependencyGraph.hh"
#include <chrono> 

using namespace llvm;

char pdg::ProgramDependencyGraph::ID = 0;

void pdg::ProgramDependencyGraph::buildPDGForFunc(Function &F)
{
  // analyze data dependencies
  getAnalysis<DataDependencyGraph>(F); // add data dependencies for nodes in F
}

bool pdg::ProgramDependencyGraph::runOnModule(Module &M)
{
  auto start = std::chrono::high_resolution_clock::now();
  PDG = &ProgramGraph::getInstance();
  PDG->build(M);
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    buildPDGForFunc(F);
  }
  errs() << "Finsh adding dependencies" << "\n";
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  errs() << "building PDG takes: " <<  duration.count() << "\n";
  return false;
}

void pdg::ProgramDependencyGraph::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<DataDependencyGraph>();
  AU.setPreservesAll();
}

void pdg::ProgramDependencyGraph::connectCallerAndCallee(CallWrapper* cw, FunctionWrapper* fw)
{
  // step1: connect actual tree with formal tree

  // step2: connect return value of callee tree to the call site

}


static RegisterPass<pdg::ProgramDependencyGraph>
    PDG("pdg", "Program Dependency Graph Construction", false, true);