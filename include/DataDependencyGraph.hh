#ifndef DATADEPENDENCYGRAPH_H_
#define DATADEPENDENCYGRAPH_H_
#include "Graph.hh"
#include "llvm/Analysis/CFLAndersAliasAnalysis.h"
#include "llvm/Analysis/MemoryDependenceAnalysis.h"
#include "llvm/Analysis/MemoryLocation.h"


namespace pdg
{
  class DataDependencyGraph : public llvm::FunctionPass
  {
  public:
    static char ID;
    DataDependencyGraph() : llvm::FunctionPass(ID){};
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Data Dependency Graph"; }
    bool runOnFunction(llvm::Function &F) override;
    void addDefUseEdges(llvm::Instruction &inst);
    void addRAWEdges(llvm::Instruction &inst);
    void addAliasEdges(llvm::Instruction &inst);
  private:
    llvm::CFLAndersAAResult *_anders_aa;
    llvm::MemoryDependenceResults *_mem_dep_res;
  };
} // namespace pdg
#endif