#ifndef BOUNDARYANALYSIS_H_
#define BOUNDARYANALYSIS_H_
#include "LLVMEssentials.hh"
#include "PDGUtils.hh"
#include <fstream> 

// this pass take the driver side bc file as input and generate a few 
// files used by the data access analysis and atomic region warning generation pass
namespace pdg
{
  class BoundaryAnalysis : public llvm::ModulePass
  {
  public:
    static char ID;
    BoundaryAnalysis() : llvm::ModulePass(ID){};
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Boundary Analysis"; }
    bool runOnModule(llvm::Module &M) override;
    void setupBlackListFuncNames();
    void computeDriverImportedFuncs(llvm::Module &M);
    void computeDriverFuncs(llvm::Module &M);
    void computeExportedFuncs(llvm::Module &M);
    void computeExportedFuncSymbols(llvm::Module &M);
    void dumpToFiles();
    void dumpToFile(std::string file_name, std::vector<std::string> &names);
    bool isBlackListFunc(std::string func_name) { return _black_list_func_names.find(func_name) != _black_list_func_names.end(); }

  private:
    std::set<std::string> _black_list_func_names;
    std::vector<std::string> _sentinel_fields;
    std::vector<std::string> _imported_funcs;
    std::vector<std::string> _exported_funcs;
    std::vector<std::string> _driver_domain_funcs;
    std::vector<std::string> _exported_func_ptrs;
    std::vector<std::string> _driver_globalvar_names;
    std::set<std::string> _exported_func_symbols;
    std::set<std::string> _global_op_struct_names;
  };
} // namespace pdg

#endif