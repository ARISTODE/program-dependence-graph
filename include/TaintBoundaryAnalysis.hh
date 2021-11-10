#ifndef TAINTBOUNDARYANALYSIS_H_
#define TAINTBOUNDARYANALYSIS_H_
#include "LLVMEssentials.hh"
#include "ProgramDependencyGraph.hh"
#include <fstream> 

// this pass take the driver side bc file as input and generate a few 
// files used by the data access analysis and atomic region warning generation pass
namespace pdg
{
  class TaintBoundaryAnalysis : public llvm::ModulePass
  {
  public:
    static char ID;
    TaintBoundaryAnalysis() : llvm::ModulePass(ID){};
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Boundary Analysis"; }
    bool runOnModule(llvm::Module &M) override;
    void identifyTaintSources();
    void propagateTaints();
    void propagateTaintSlices();
    void computeBoundaryFuncs();
    void dumpBoundaryFuncs();
    void dumpToFile(std::string file_name, std::set<std::string> &names);

  private:
    llvm::Module* _module;
    std::set<Node*> _taint_sources;
    std::set<Node*> _taint_nodes;
    std::set<llvm::Function*> _taint_funcs;
    ProgramGraph* _PDG;
    PDGCallGraph* _call_graph;
    std::set<std::string> _tainted_boundary_funcs;
    std::set<std::string> _untainted_boundary_funcs;
  };
} // namespace pdg

#endif