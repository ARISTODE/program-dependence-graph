#ifndef GENERATE_MONITOR_H_
#define GENERATE_MONITOR_H_
#include "LLVMEssentials.hh"
#include "DebugInfoUtils.hh"
#include "PDGUtils.hh"
#include <unordered_set>
#include <fstream>

namespace pdg
{
  class GenerateMonitorPass : public llvm::ModulePass
  {
  public:
    static char ID;
    GenerateMonitorPass() : llvm::ModulePass(ID){};
    bool runOnModule(llvm::Module &M) override;
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    void generateHeaders();
    void generateStructDefinitionHeaders();
    void generateInstrumentFuncDefinitions();
    void generateTypeCastFunc(llvm::Function &F);
    void collectFuncParamsStructTys(std::unordered_set<llvm::DIType *> &structTypes, llvm::Function &F);
    llvm::DIType *getDebugTypeForParameter(llvm::Function &F, unsigned paramIndex);
    void collectStructTypes(llvm::DIType *rootTy, std::unordered_set<llvm::DIType *> &structTypes);
    std::string getStructTypeName(llvm::DIType *Ty);
    void generateCastFunction(std::unordered_set<llvm::DIType*>& structTypes);

  private:
    std::ofstream MonitorFile;
  };
}

#endif