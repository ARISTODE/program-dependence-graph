#ifndef PROGRAMDEPENDENCYGRAPH_H_
#define PROGRAMDEPENDENCYGRAPH_H_
#include "LLVMEssentials.hh"
#include "Graph.hh"
#include "PDGCallGraph.hh"
#include "DataDependencyGraph.hh"
#include "ControlDependencyGraph.hh"

namespace pdg
{
  class ProgramDependencyGraph : public llvm::ModulePass
  {
    public:
      static char ID;
      ProgramDependencyGraph() : llvm::ModulePass(ID) {};
      bool runOnModule(llvm::Module &M) override;
      void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
      ProgramGraph *getPDG() { return _PDG; }
      llvm::StringRef getPassName() const override { return "Program Dependency Graph"; }
      FunctionWrapper *getFuncWrapper(llvm::Function &F) { return _PDG->getFuncWrapperMap()[&F]; }
      CallWrapper *getCallWrapper(llvm::CallInst &callInst) { return _PDG->getCallWrapperMap()[&callInst]; }
      void connectInTrees(Tree *src_tree, Tree *dstTree, EdgeType edgeTy);
      void connectOutTrees(Tree *src_tree, Tree *dstTree, EdgeType edgeTy);
      void connectCallerAndCallee(CallWrapper &cw, FunctionWrapper &fw);
      void connectIntraprocDependencies(llvm::Function &F);
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