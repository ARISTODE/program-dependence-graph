#ifndef _KSPLIT_CFG_H_
#define _KSPLIT_CFG_H_
#include "Graph.hh"
#include "PDGCallGraph.hh"

namespace pdg
{
  class KSplitCFG : public GenericGraph
  {
    public:
      KSplitCFG() = default;
      KSplitCFG(const KSplitCFG &) = delete;
      KSplitCFG(KSplitCFG &&) = delete;
      KSplitCFG &operator=(const KSplitCFG &) = delete;
      KSplitCFG &operator=(KSplitCFG &&) = delete;
      static KSplitCFG &getInstance()
      {
        static KSplitCFG cfg{};
        return cfg;
      }
      void build(llvm::Module &M) override;
      void connectControlFlowEdges(llvm::Module &M);
      bool isBuild() { return _isBuild; }
      std::set<Node *> searchCallNodes(Node &start_node, std::string calleeName);
      std::set<llvm::Instruction *> computeNodesBetweenPoints(llvm::Instruction &start, llvm::Instruction &end);

    private:
      bool _isBuild = false;

  };
}

#endif
