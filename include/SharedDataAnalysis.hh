#ifndef SHARED_DATA_ANALYSIS_H_
#define SHARED_DATA_ANALYSIS_H_
#include "LLVMEssentials.hh"
#include "ProgramDependencyGraph.hh"
#include <set>
#include <fstream> 

namespace pdg
{
  class SharedDataAnalysis : public llvm::ModulePass
  {
  public:
    static char ID;
    SharedDataAnalysis() : llvm::ModulePass(ID){};
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Shared Data Analysis"; }
    bool runOnModule(llvm::Module &M) override;
    void setupDriverFuncs(llvm::Module &M);
    void setupKernelFuncs(llvm::Module &M);
    void setupBoundaryFuncs(llvm::Module &M);
    std::set<llvm::Function *> readFuncsFromFile(std::string file_name, llvm::Module &M);
    void computeSharedStructDITypes();
    void buildTreesForSharedStructDIType(llvm::Module &M);
    void connectTypeTreeToAddrVars(Tree &tree);
    void computeVarsWithDITypeInFunc(llvm::DIType &dt, llvm::Function &F, std::set<llvm::Value *> &vars);
    std::set<llvm::Value *> computeVarsWithDITypeInModule(llvm::DIType &dt, llvm::Module &M);
    bool isTreeNodeShared(TreeNode &tree_node);
    bool isSharedFieldID(std::string field_id);
    void computeSharedDataVars();
    void computeSharedFieldID();
    void dumpSharedFieldID();
    ProgramGraph *getPDG() { return _PDG; }

  private:
    ProgramGraph *_PDG;
    std::set<llvm::Value *> _shared_data_vars;
    std::set<llvm::DIType *> _shared_struct_di_types;
    std::set<llvm::Function *> _driver_domain_funcs;
    std::set<llvm::Function *> _kernel_domain_funcs;
    std::set<llvm::Function *> _boundary_funcs;
    std::map<llvm::DIType *, Tree *> _global_struct_di_type_map;
    std::set<std::string> _shared_field_id;
  };
} // namespace pdg
#endif