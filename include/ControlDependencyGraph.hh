#ifndef CONTROLDEPENDENCYGRAPH_H_
#define CONTROLDEPENDENCYGRAPH_H_
#include "Graph.hh"
#include "llvm/Analysis/PostDominators.h"



namespace pdg
{
  class ControlDependencyGraph : public llvm::AnalysisInfoMixin<ControlDependencyGraph>
  {
  public:
    struct Result {
      bool value;
      bool invalidate(llvm::Function &, const llvm::PreservedAnalyses &,
                     llvm::FunctionAnalysisManager::Invalidator &) {
        return false;
      }
    };
    static llvm::AnalysisKey Key;
    
    static llvm::StringRef name() { return "Control Dependency Graph"; }
    Result run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
    void addControlDepFromNodeToBB(Node &n, llvm::BasicBlock &bb, EdgeType edge_type);
    void addControlDepFromEntryNodeToInsts(llvm::Function &F);
    void addControlDepFromDominatedBlockToDominator(llvm::Function &F);
  private:
    llvm::PostDominatorTree *_PDT;
  };
} // namespace pdg

#endif