#ifndef BOUNDARYANALYSIS_H_
#define BOUNDARYANALYSIS_H_
#include "LLVMEssentials.hh"
#include "PDGUtils.hh"
#include <fstream> 

// this pass take the driver side bc file as input and generate a few 
// files used by the data access analysis and atomic region warning generation pass
namespace pdg
{
  class BoundaryAnalysis : public llvm::AnalysisInfoMixin<BoundaryAnalysis>
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
    
    Result run(llvm::Module &M, llvm::ModuleAnalysisManager &MAM);
    void setupBlackListFuncNames();
    void computeDriverImportedFuncs(llvm::Module &M);
    void computeDriverFuncs(llvm::Module &M);
    void computeExportedFuncs(llvm::Module &M);
    void computeExportedFuncSymbols(llvm::Module &M);
    void dumpToFiles();
    void dumpToFile(std::string fileName, std::vector<std::string> &names);
    bool isBlackListFunc(std::string funcName) { return _blackListFuncNames.find(funcName) != _blackListFuncNames.end(); }
    void sanitizeIxgbeGlobalOps();

  private:
    std::set<std::string> _blackListFuncNames;
    std::vector<std::string> _sentinelFields;
    std::vector<std::string> _importedFuncs;
    std::vector<std::string> _exportedFuncs;
    std::vector<std::string> _driverDomainFuncs;
    std::vector<std::string> _exportedFuncPtrs;
    std::vector<std::string> _driverGlobalVarNames;
    std::set<std::string> _exportedFuncSymbols;
    std::set<std::string> _globalOpStructNames;
  };
} // namespace pdg

#endif