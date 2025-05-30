#ifndef PROGRAMDEPENDENCYGRAPH_H_
#define PROGRAMDEPENDENCYGRAPH_H_
#include "LLVMEssentials.hh"
#include "Graph.hh"
#include "PDGCallGraph.hh"
#include "DataDependencyGraph.hh"
#include "ControlDependencyGraph.hh"
#include "PTAWrapper.hh"

namespace pdg
{
  class ProgramDependencyGraph : public llvm::AnalysisInfoMixin<ProgramDependencyGraph>
  {
    public:
      struct Result {
        ProgramGraph* PDG;
        bool invalidate(llvm::Module &, const llvm::PreservedAnalyses &,
                       llvm::ModuleAnalysisManager::Invalidator &) {
          return false;
        }
      };
      static llvm::AnalysisKey Key;
      
      Result run(llvm::Module &M, llvm::ModuleAnalysisManager &MAM);
      ProgramGraph *getPDG() { return _PDG; }
      static llvm::StringRef name() { return "Program Dependency Graph"; }
      FunctionWrapper *getFuncWrapper(llvm::Function &F) { return _PDG->getFuncWrapperMap()[&F]; }
      CallWrapper *getCallWrapper(llvm::CallInst &call_inst) { return _PDG->getCallWrapperMap()[&call_inst]; }
      void connectGlobalVarWithUses();
      void connectInTrees(Tree *src_tree, Tree *dst_tree, EdgeType edge_type);
      void connectOutTrees(Tree *src_tree, Tree *dst_tree, EdgeType edge_type);
      void connectCallerAndCallee(CallWrapper &cw, FunctionWrapper &fw);
      void connectIntraprocDependencies(llvm::Function &F, llvm::ModuleAnalysisManager &MAM);
      void connectInterprocDependencies(llvm::Function &F);
      void connectFormalInTreeWithAddrVars(Tree &formalInTree);
      void connectFormalOutTreeWithAddrVars(Tree &formalOutTree);
      void connectActualInTreeWithAddrVars(Tree &actualInTree, llvm::CallInst &ci);
      void connectActualOutTreeWithAddrVars(Tree &actualOutTree, llvm::CallInst &ci);
      void connectTreeNode(TreeNode &src_node, TreeNode &dstNode, EdgeType edgeTy);
      void connectFormalInTreeWithActualTree(llvm::Function &F);
      void connectAddrVarsReachableFromInterprocFlow(llvm::Function &F);
      void connectFormalInTreeWithCallActualNode(Tree &formalInTree);
      void conntectFormalInTreeWithInterprocReachableAddrVars(Tree &formalInTree);
      void connectGlobalTreeWithAddrVars(Tree &globalVarTree);
      std::set<Node*> getAliasNodes(Node &n);

    private:
      llvm::Module *_module;
      ProgramGraph *_PDG;
  };
}


#endif