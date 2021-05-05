#ifndef SHARED_DATA_ANALYSIS_H_
#define SHARED_DATA_ANALYSIS_H_
#include "LLVMEssentials.hh"
#include "ProgramDependencyGraph.hh"
#include "KSplitStatsCollector.hh"
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
    void setupStrOps();
    void readDriverGlobalStrucTypes();
    void setupKernelFuncs(llvm::Module &M);
    std::set<llvm::Function *> &getDriverFuncs() { return _driver_domain_funcs; }
    bool isDriverFunc(llvm::Function &F) { return (_driver_domain_funcs.find(&F) != _driver_domain_funcs.end()); }
    std::set<llvm::Function *> &getKernelFuncs() { return _kernel_domain_funcs; }
    bool isKernelFunc(llvm::Function &F) { return (_kernel_domain_funcs.find(&F) != _kernel_domain_funcs.end()); }
    void setupBoundaryFuncs(llvm::Module &M);
    std::set<llvm::Function *> &getBoundaryFuncs() { return _boundary_funcs; }
    std::set<std::string> &getBoundaryFuncNames() { return _boundary_func_names; }
    std::set<std::string> &getSentinelFields() { return _sentinel_fields; }
    std::set<std::string> &getGlobalOpStructNames() { return _global_op_struct_names; }
    bool isSentinelField(std::string &s) { return _sentinel_fields.find(s) != _sentinel_fields.end(); }
    bool isGlobalOpStruct(std::string &s) { return _global_op_struct_names.find(s) != _global_op_struct_names.end(); }
    std::set<llvm::Function *> readFuncsFromFile(std::string file_name, llvm::Module &M);
    std::set<llvm::Function *> computeBoundaryTransitiveClosure();
    void computeSharedStructDITypes();
    void computeGlobalStructTypeNames();
    void buildTreesForSharedStructDIType(llvm::Module &M);
    void connectTypeTreeToAddrVars(Tree &tree);
    void computeVarsWithDITypeInFunc(llvm::DIType &dt, llvm::Function &F, std::set<llvm::Value *> &vars);
    std::set<llvm::Value *> computeVarsWithDITypeInModule(llvm::DIType &dt, llvm::Module &M);
    bool isStructFieldNode(TreeNode &tree_node);
    bool isTreeNodeShared(TreeNode &tree_node);
    bool isFieldUsedInStringOps(TreeNode &tree_node);
    bool isStringFieldID(std::string field_id) { return _string_op_names.find(field_id) != _string_op_names.end(); }
    bool isSharedFieldID(std::string field_id, std::string field_type_name="");
    bool isSharedStructType(std::string s) { return _shared_struct_type_names.find(s) != _shared_struct_type_names.end(); }
    // void computeSharedDataVars();
    void computeSharedFieldID();
    void computeSharedGlobalVars();
    std::set<std::string> getGlobalStructDITypeNames() { return _global_struct_di_type_names; }
    void dumpSharedFieldID();
    void readSentinelFields();
    void readGlobalOpStructNames();
    ProgramGraph *getPDG() { return _PDG; }
    // some side tests
    void printPingPongCalls(llvm::Module &M);
    void dumpSharedTypes(std::string file_name);

  private:
    ProgramGraph *_PDG;
    llvm::Module* _module;
    PDGCallGraph* _call_graph;
    std::set<llvm::GlobalVariable *> _shared_global_vars;
    std::set<llvm::DIType *> _shared_struct_di_types;
    std::set<llvm::Function *> _driver_domain_funcs;
    std::set<llvm::Function *> _kernel_domain_funcs;
    std::set<llvm::Function *> _boundary_funcs;
    std::set<std::string> _boundary_func_names;
    std::map<llvm::DIType *, Tree *> _global_struct_di_type_map;
    std::set<std::string> _shared_field_id;
    std::set<std::string> _string_field_id;
    std::set<std::string> _string_op_names;
    std::set<std::string> _global_struct_di_type_names;
    std::set<std::string> _shared_struct_type_names;
    std::set<std::string> _driver_global_struct_types;
    std::set<std::string> _sentinel_fields;
    std::set<std::string> _global_op_struct_names;
  };
} // namespace pdg
#endif