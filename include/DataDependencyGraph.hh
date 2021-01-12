#ifndef DATADEPENDENCYGRAPH_H_
#define DATADEPENDENCYGRAPH_H_
#include "Graph.hh"
#include "llvm/Analysis/CFLAndersAliasAnalysis.h"
#include "llvm/Analysis/MemoryLocation.h"


namespace pdg
{
  class DataDependencyGraph : public llvm::FunctionPass
  {
  private:
    llvm::CFLAndersAAResult *andersAA;
  public:
    static char ID;
    DataDependencyGraph() : llvm::FunctionPass(ID){};
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Data Dependency Graph"; }
    bool runOnFunction(llvm::Function &F) override;
    void addDefUseEdges(llvm::Instruction &inst);
    void addRAWEdges(llvm::Instruction &inst);
    void addAliasEdges(llvm::Instruction &inst);
  };
} // namespace pdg
#endif