#ifndef DATAACCESSANALYSIS_H_
#define DATAACCESSANALYSIS_H_
#include "ProgramDependencyGraph.hh"

namespace pdg
{
  class DataAccessAnalysis : public llvm::ModulePass 
  {
    private:
      llvm::Module * _module;
      ProgramGraph *PDG;

    public: 
      static char ID;
      DataAccessAnalysis() : llvm::ModulePass(ID) {};
      bool runOnModule(llvm::Module &M) override;
      void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
      llvm::StringRef getPassName() const override { return "Data Access Analysis"; }
  };
}

#endif