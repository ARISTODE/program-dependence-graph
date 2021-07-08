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
      CallWrapper *getCallWrapper(llvm::CallInst &call_inst) { return _PDG->getCallWrapperMap()[&call_inst]; }
      void connectInTrees(Tree *src_tree, Tree *dst_tree, EdgeType edge_type);
      void connectOutTrees(Tree *src_tree, Tree *dst_tree, EdgeType edge_type);
      void connectCallerAndCallee(CallWrapper &cw, FunctionWrapper &fw);
      void connectIntraprocDependencies(llvm::Function &F);
      void connectInterprocDependencies(llvm::Function &F);
      void connectFormalInTreeWithAddrVars(Tree &formal_in_tree);
      void connectFormalOutTreeWithAddrVars(Tree &formal_out_tree);
      void connectActualInTreeWithAddrVars(Tree &actual_in_tree, llvm::CallInst &ci);
      void connectActualOutTreeWithAddrVars(Tree &actual_out_tree, llvm::CallInst &ci);
      void connectTreeNode(TreeNode &src_node, TreeNode &dst_node, EdgeType edge_type);
      void connectFormalInTreeWithActualTree(llvm::Function &F);
      void connectAddrVarsReachableFromInterprocFlow(llvm::Function &F);
      void connectFormalInTreeWithCallActualNode(Tree &formal_in_tree);
      void conntectFormalInTreeWithInterprocReachableAddrVars(Tree &formal_in_tree);
      void connectGlobalTreeWithAddrVars(Tree &global_var_tree);
      std::set<Node*> getAliasNodes(Node &n);

    private:
      llvm::Module *_module;
      ProgramGraph *_PDG;
  };
}


#endif