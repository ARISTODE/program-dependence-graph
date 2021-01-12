#ifndef PROGRAMDEPENDENCYGRAPH_H_
#define PROGRAMDEPENDENCYGRAPH_H_
#include "LLVMEssentials.hh"
#include "DataDependencyGraph.hh"
#include "Graph.hh"

namespace pdg
{
  class ProgramDependencyGraph : public llvm::ModulePass
  {
    private:
      llvm::Module *_module;
      ProgramGraph* PDG;

    public:
      static char ID;
      ProgramDependencyGraph() : llvm::ModulePass(ID) {};
      bool runOnModule(llvm::Module &M) override;
      void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
      llvm::StringRef getPassName() const override { return "Program Dependency Graph"; }
      void buildPDGForFunc(llvm::Function &F);
      void connectCallerAndCallee(CallWrapper* cw, FunctionWrapper* fw);
      ProgramGraph *getPDG() { return PDG; }
  };
}
#endif