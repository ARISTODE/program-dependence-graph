#ifndef SHARED_DATA_ANALYSIS_H_
#define SHARED_DATA_ANALYSIS_H_ 
#include "LLVMEssentials.hh"
#include "ProgramDependencyGraph.hh"
#include "KSplitStatsCollector.hh"
#include <set>
#include <unordered_set>
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
    void setupStrOps();
    void setupExportedFuncPtrFieldNames();
    void readDriverGlobalStrucTypes();
    void setupKernelFuncs(llvm::Module &M);
    std::set<llvm::Function *> &getDriverFuncs() { return _driverDomainFuncs; }
    bool isDriverFunc(llvm::Function &F) { return (_driverDomainFuncs.find(&F) != _driverDomainFuncs.end()); }
    bool isKernelFunc(llvm::Function &F) {return (_kernelDomainFuncs.find(&F) != _kernelDomainFuncs.end());}
    std::set<llvm::Function *> &getKernelFuncs() { return _kernelDomainFuncs; }
    bool isKernelFuncName(std::string funcName) { return (_kernel_domain_func_names.find(funcName) != _kernel_domain_func_names.end()); }
    void setupBoundaryFuncs(llvm::Module &M);
    std::set<llvm::Function *> &getBoundaryFuncs() { return _boundary_funcs; }
    std::set<std::string> &getBoundaryFuncNames() { return _boundary_func_names; }
    std::set<std::string> &getSentinelFields() { return _sentinelFields; }
    std::set<std::string> &getGlobalOpStructNames() { return _driver_func_op_struct_names; }
    std::set<std::string> &getSharedStructTypeNames() { return _shared_struct_type_names; }
    bool isSentinelField(std::string &s) { return _sentinelFields.find(s) != _sentinelFields.end(); }
    bool isGlobalOpStruct(std::string &s) { return _driver_func_op_struct_names.find(s) != _driver_func_op_struct_names.end(); }
    std::set<llvm::Function *> readFuncsFromFile(std::string fileName, llvm::Module &M, std::string dir = "");
    std::unordered_set<llvm::Function *> computeBoundaryTransitiveClosure();
    std::unordered_set<llvm::Function *> computeKernelInterfaceFuncTransitiveClosure();
    bool isBoundaryFuncName(std::string funcName) { return _boundary_func_names.find(funcName) != _boundary_func_names.end(); }
    void computeSharedStructDITypes();
    void computeGlobalStructTypeNames();
    void buildTreesForSharedStructDIType(llvm::Module &M);
    void connectTypeTreeToAddrVars(Tree &tree);
    void computeVarsWithStructDITypeInFunc(llvm::DIType &dt, llvm::Function &F, std::set<llvm::Value *> &vars);
    std::set<llvm::Value *> computeVarsWithStructDITypeInModule(llvm::DIType &dt, llvm::Module &M);
    bool isStructFieldNode(TreeNode &treeNode);
    bool isTreeNodeShared(TreeNode &treeNode);
    bool isFieldUsedInStringOps(TreeNode &treeNode);
    bool isStringFieldID(std::string fieldId) { return _string_op_names.find(fieldId) != _string_op_names.end(); }
    bool isSharedFieldID(std::string fieldId, std::string field_type_name="");
    bool isSharedStructType(std::string s) { return _shared_struct_type_names.find(s) != _shared_struct_type_names.end(); }
    // void computeSharedDataVars();
    void computeSharedFieldID();
    void computeSharedGlobalVars();
    std::set<std::string> getGlobalStructDITypeNames() { return _global_struct_di_type_names; }
    void dumpSharedFieldID();
    void readSentinelFields();
    void readGlobalFuncOpStructNames();
    llvm::Function *getModuleInitFunc(llvm::Module &M);
    ProgramGraph *getPDG() { return _PDG; }
    
    // functions for finding functions access a specific type of data
    void findKernelFuncsAccessType(std::string targetDtName, std::unordered_set<llvm::Function *> &funcs);

    // some side tests
    void printPingPongCalls(llvm::Module &M);
    void dumpSharedTypes(std::string fileName);
    // shared fields access stats
    void collectSharedFieldsAccessStats();
    void countReadWriteAccessTimes(TreeNode &treeNode);
    void printDriverUpdateLocations(TreeNode &treeNode, llvm::raw_fd_ostream &OS);
    void getDriverUpdateLocStr(TreeNode &treeNode, llvm::raw_string_ostream &ss);
    std::string getFieldTypeStr(TreeNode &treeNode);
    bool usedInBranch(TreeNode &treeNode);
    bool isFuncPtr(TreeNode &treeNode);
    bool isDriverCallBackFuncPtrFieldNode(TreeNode &treeNode);
    std::map<llvm::DIType *, Tree *> getGlobalStructDTMap() { return _global_struct_di_type_map; }

  private:
    ProgramGraph *_PDG;
    llvm::Module* _module;
    PDGCallGraph* _callGraph;
    KSplitStats* _ksplitStats;
    std::set<llvm::GlobalVariable *> _shared_global_vars;
    std::set<llvm::DIType *> _shared_struct_di_types;
    std::set<llvm::Function *> _driverDomainFuncs;
    std::set<llvm::Function *> _kernelDomainFuncs;
    std::set<std::string> _kernel_domain_func_names;
    std::set<llvm::Function *> _boundary_funcs;
    std::set<std::string> _boundary_func_names;
    std::map<llvm::DIType *, Tree *> _global_struct_di_type_map;
    std::set<std::string> _shared_field_id;
    std::set<std::string> _string_field_id;
    std::set<std::string> _string_op_names;
    std::set<std::string> _global_struct_di_type_names;
    std::set<std::string> _shared_struct_type_names;
    std::set<std::string> _driver_func_op_struct_names;
    std::set<std::string> _driver_global_struct_types;
    std::set<std::string> _sentinelFields;
    std::set<std::string> exportedFuncPtrFieldNames;
  };
} // namespace pdg
#endif