#ifndef DATADEPENDENCYGRAPH_H_
#define DATADEPENDENCYGRAPH_H_
#include "Graph.hh"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/MemoryDependenceAnalysis.h"
#include "llvm/Analysis/MemoryLocation.h"

namespace pdg
{
  class DataDependencyGraph : public llvm::AnalysisInfoMixin<DataDependencyGraph>
  {
  public:
    struct Result {
      bool value;
      bool invalidate(llvm::Module &, const llvm::PreservedAnalyses &,
                     llvm::ModuleAnalysisManager::Invalidator &) {
        return false;
      }
    };
    static llvm::AnalysisKey Key;
    
    static llvm::StringRef name() { return "Data Dependency Graph"; }
    Result run(llvm::Module &M, llvm::ModuleAnalysisManager &MAM);
    void addDefUseEdges(llvm::Instruction &inst);
    void addRAWEdges(llvm::Instruction &inst);
    void addRAWEdgesUnderapproximate(llvm::Instruction &inst);
    void addAliasEdges(llvm::Instruction &inst);
    llvm::AliasResult queryAliasUnderApproximate(llvm::Value &v1, llvm::Value &v2);

  private:
    llvm::MemoryDependenceResults *_mem_dep_res;
  };
} // namespace pdg
#endif
