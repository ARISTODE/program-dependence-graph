#ifndef SHARED_FIELDS_ANALYSIS_H_
#define SHARED_FIELDS_ANALYSIS_H_
#include "LLVMEssentials.hh"
#include "DebugInfoUtils.hh"
#include "PDGUtils.hh"
#include <set>

        
namespace pdg
{
  class SharedFieldsAnalysis : public llvm::ModulePass 
  {
  public:
    static char ID;
    SharedFieldsAnalysis() : llvm::ModulePass(ID){};
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Shared Fields Analysis"; }
    bool runOnModule(llvm::Module &M) override;
    void getDbgDeclareInstsInFunc(llvm::Function &F, std::set<llvm::DbgDeclareInst *> &dbg_insts);
    void propagateDebuggingInfoInFunc(llvm::Function &F);
    std::pair<llvm::DIType *, llvm::DIType *> computeInstDIType(llvm::Instruction &i);
    void insertValueDITypePair(llvm::Value *val, llvm::DIType* parent_dt, llvm::DIType *dt);
    std::pair<llvm::DIType *, llvm::DIType *> getValDITypePair(llvm::Value &val);
    llvm::DIType *getValDIType(llvm::Value &val);
    void readDriverFuncs(llvm::Module &M);
    bool isDriverFunc(llvm::Function &F) { return _driver_funcs.find(&F) != _driver_funcs.end(); }
    void computeAccessedFieldsInFunc(llvm::Function &F, std::set<std::string>& access_fields);
    void computeAccessFields(llvm::Module &M);
    void computeSharedAccessFields();
    void dumpSharedFields();

  private:
    std::map<llvm::Value *, std::pair<llvm::DIType *, llvm::DIType *>> _inst_ditype_map;
    std::set<std::string> _shared_fields;
    std::set<std::string> _driver_access_fields;
    std::set<std::string> _kernel_access_fields;
    std::set<llvm::Function *> _driver_funcs;
  };
}

#endif