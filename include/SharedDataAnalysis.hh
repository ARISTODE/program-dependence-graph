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
    void setupStrOps();
    void readDriverGlobalStrucTypes();
    std::set<llvm::Function *> &getDriverFuncs() { return _driver_domain_funcs; }
    void setupKernelFuncs(llvm::Module &M);
    std::set<llvm::Function *> &getKernelFuncs() { return _kernel_domain_funcs; }
    void setupBoundaryFuncs(llvm::Module &M);
    void setupServerFuncs(llvm::Module &M);
    std::set<llvm::Function *> &getBoundaryFuncs() { return _boundary_funcs; };
    std::set<llvm::Function *> readFuncsFromFile(std::string file_name, llvm::Module &M);
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
    bool isSharedFieldID(std::string field_id);
    bool isSharedStructType(std::string s) { return _shared_struct_type_names.find(s) != _shared_struct_type_names.end(); }
    // void computeSharedDataVars();
    void computeSharedFieldID();
    std::set<std::string> getGlobalStructDITypeNames() { return _global_struct_di_type_names; }
    void dumpSharedFieldID();
    ProgramGraph *getPDG() { return _PDG; }
    // some side tests
    void printPingPongCalls(llvm::Module &M);
    void dumpSharedTypes(std::string file_name);
    std::set<llvm::Function *> getServerFuncs() { return _server_funcs; }

  private:
    ProgramGraph *_PDG;
    llvm::Module* _module;
    std::set<llvm::Value *> _shared_data_vars;
    std::set<llvm::DIType *> _shared_struct_di_types;
    std::set<llvm::Function *> _driver_domain_funcs;
    std::set<llvm::Function *> _kernel_domain_funcs;
    std::set<llvm::Function *> _boundary_funcs;
    std::map<llvm::DIType *, Tree *> _global_struct_di_type_map;
    std::set<std::string> _shared_field_id;
    std::set<std::string> _string_field_id;
    std::set<std::string> _string_op_names;
    std::set<std::string> _global_struct_di_type_names;
    std::set<std::string> _shared_struct_type_names;
    std::set<std::string> _driver_global_struct_types;
    std::set<llvm::Function *> _server_funcs;
  };
} // namespace pdg
#endif