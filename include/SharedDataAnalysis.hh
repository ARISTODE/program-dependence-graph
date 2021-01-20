#ifndef SHARED_DATA_ANALYSIS_H_
#define SHARED_DATA_ANALYSIS_H_
#include "LLVMEssentials.hh"
#include <set>

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
    void computeSharedDataVars();
    void computeSharedFieldID();
  private:
    std::set<llvm::Value *> _shared_data_vars;
    std::set<std::string> _shared_field_id;
  };
} // namespace pdg
#endif