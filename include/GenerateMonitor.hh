#ifndef GENERATE_MONITOR_H_
#define GENERATE_MONITOR_H_
#include "LLVMEssentials.hh"
#include "DebugInfoUtils.hh"
#include "PDGUtils.hh"
#include <unordered_map>
#include <fstream>
#include <functional>

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
    void generateInstrumentFuncDefinitions();
    void collectFuncParamsStructTys(std::unordered_map<llvm::DIType *, std::string> &structTypes, llvm::Function &F);
    llvm::DIType *getDebugTypeForParameter(llvm::Function &F, unsigned paramIndex);
    void collectStructTypes(llvm::DIType *rootTy, std::unordered_map<llvm::DIType *, std::string> &structTypes, std::string offsetStr, std::string &funcName);
    std::string getStructTypeName(llvm::DIType *Ty);
    void generateTypeCastFuncBody(llvm::Function &F);
    void generateTypeCastFuncTop();
    void generateTypeCasts(std::unordered_map<llvm::DIType *, std::string> &structTypes);
    void generateTypeCastFuncBottom();

  private:
    std::ofstream MonitorFile;
  };
}

#endif