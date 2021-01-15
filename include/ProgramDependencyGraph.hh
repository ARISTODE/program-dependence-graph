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
      ProgramGraph *getPDG() { return PDG; }
      llvm::StringRef getPassName() const override { return "Program Dependency Graph"; }
      FunctionWrapper *getFuncWrapper(llvm::Function &F) { return PDG->getFuncWrapperMap()[&F]; }
      CallWrapper *getCallWrapper(llvm::CallInst &call_inst) { return PDG->getCallWrapperMap()[&call_inst]; }
      void connectTrees(Tree* src_tree, Tree* dst_tree, EdgeType edge_type);
      void connectCallerAndCallee(CallWrapper* cw, FunctionWrapper* fw);
      void connectIntraprocDependencies(llvm::Function &F);
      void connectInterprocDependencies(llvm::Function &F);
      void connectFormalInTreeWithAddrVars(Tree &formal_in_tree);
      void connectFormalOutTreeWithAddrVars(Tree &formal_out_tree);
      void connectActualInTreeWithAddrVars(Tree &actual_in_tree);
      void connectActualOutTreeWithAddrVars(Tree &actual_out_tree);
  };
}
#endif