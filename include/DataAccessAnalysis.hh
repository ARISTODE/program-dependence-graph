#ifndef DATAACCESSANALYSIS_H_
#define DATAACCESSANALYSIS_H_
#include "SharedDataAnalysis.hh"
#include <fstream>
#include <sstream>

namespace pdg
{
  class DataAccessAnalysis : public llvm::ModulePass
  {
  public:
    static char ID;
    DataAccessAnalysis() : llvm::ModulePass(ID){};
    bool runOnModule(llvm::Module &M) override;
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Data Access Analysis"; }
    std::set<AccessTag> computeDataAccessTagsForVal(llvm::Value &val);
    pdg::Node *findFirstCrossDomainParamNode(Node &n);
    void readDriverDefinedGlobalVarNames(std::string file_name);
    void propagateAllocSizeAnno(llvm::Value &allocator);
    void computeAllocSizeAnnos(llvm::Module &M);
    void computeExportedFuncsPtrNameMap();
    void computeDataAccessForTree(Tree *tree, bool is_ret=false);
    void computeDataAccessForGlobalTree(Tree *tree);
    void computeDataAccessForTreeNode(TreeNode &tree_node, bool is_global_tree_node = false, bool is_ret=false);
    void computeDataAccessForFuncArgs(llvm::Function &F);
    void generateIDLForFunc(llvm::Function &F, bool is_kernel_func=false);
    void generateRpcForFunc(llvm::Function &F, bool is_kernel_func=false);
    void generateIDLFromGlobalVarTree(llvm::GlobalVariable &gv, Tree *tree);
    void generateIDLFromArgTree(Tree *arg_tree, std::ofstream &output_file, bool is_ret = false);
    void generateIDLFromTreeNode(TreeNode &tree_node, llvm::raw_string_ostream &fields_projection_str, llvm::raw_string_ostream &nested_struct_proj_str, std::queue<TreeNode *> &node_queue, std::string indent_level, std::string parent_struct_type_name);
    void generateRpcStubForIndirectCall(llvm::DIType &dt, std::string arg_name);
    void constructGlobalOpStructStr();
    void computeContainerOfLocs(llvm::Function &F);
    std::set<std::string> inferTreeNodeAnnotations(TreeNode &tree_node, bool is_ret = false);
    bool globalVarHasAccessInDriver(llvm::GlobalVariable &gv);
    bool isDriverDefinedGlobal(llvm::GlobalVariable &gv);
    bool containerHasSharedFieldsAccessed(llvm::BitCastInst &bci);
    std::string computeAllocCallerAnnotation(TreeNode &tree_node);
    std::string computeAllocCalleeAnnotation(TreeNode &tree_node);
    std::set<Node *> findAllocator(TreeNode &tree_node, bool is_forward = false);
    void printContainerOfStats();
    DomainTag computeFuncDomainTag(llvm::Function &F);
    KSplitStats *getKSplitStats() { return _ksplit_stats; }
    SharedDataAnalysis *getSDA() { return _SDA; }
    ProgramGraph *getPDG() { return _PDG; }

  private:
    llvm::Module *_module;
    SharedDataAnalysis *_SDA;
    ProgramGraph *_PDG;
    PDGCallGraph *_call_graph;
    std::ofstream _idl_file;
    std::ofstream _global_var_access_info;
    std::ofstream _sync_stub_file;
    std::set<std::string> _seen_func_ops;
    std::string _ops_struct_proj_str;
    std::map<std::string, std::string> _exported_funcs_ptr_name_map;
    std::map<std::string, std::set<std::string>> _global_ops_fields_map;
    std::set<llvm::Instruction *> _container_of_insts;
    KSplitStats *_ksplit_stats;
    std::string _current_processing_func = "";
    std::set<std::string> _driver_defined_globalvar_names;
    std::set<Node*> _funcs_reachable_from_boundary;
    std::set<llvm::Function *> _kernel_funcs_regsitered_with_indirect_ptr;
  };
}

#endif