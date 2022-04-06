#ifndef DATAACCESSANALYSIS_H_
#define DATAACCESSANALYSIS_H_
#include "SharedDataAnalysis.hh"
#include "llvm/Analysis/CaptureTracking.h"
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
    std::set<pdg::Node *> findCrossDomainParamNode(Node &n, bool is_backward = false);
    void readDriverDefinedGlobalVarNames(std::string file_name);
    void readDriverExportedFuncSymbols(std::string file_name);
    void propagateAllocSizeAnno(llvm::Value &allocator);
    void inferDeallocAnno(llvm::Value &deallocator);
    void computeAllocSizeAnnos(llvm::Module &M);
    void computeDeallocAnnos(llvm::Module &M);
    void computeCollocatedAllocsite(llvm::Module &M);
    void checkCollocatedAllocsite(llvm::Value &alloc_site);
    void computeExportedFuncsPtrNameMap();
    void computeDataAccessForTree(Tree *tree, bool is_ret=false);
    void computeDataAccessForGlobalTree(Tree *tree);
    void computeDataAccessForTreeNode(TreeNode &tree_node, bool is_global_tree_node = false, bool is_ret=false);
    void computeDataAccessForFuncArgs(llvm::Function &F);
    void generateIDLForFunc(llvm::Function &F, bool process_exported_func=false);
    void generateRpcForFunc(llvm::Function &F, bool process_exported_func=false);
    void generateIDLFromGlobalVarTree(llvm::GlobalVariable &gv, Tree *tree);
    void generateIDLFromArgTree(Tree *arg_tree, std::ofstream &output_file, bool is_ret = false, bool is_global = false);
    void generateIDLFromTreeNode(TreeNode &tree_node, llvm::raw_string_ostream &fields_projection_str, llvm::raw_string_ostream &nested_struct_proj_str, std::queue<TreeNode *> &node_queue, std::string indent_level, std::string parent_struct_type_name, bool is_ret = false);
    void constructGlobalOpStructStr();
    void computeContainerOfLocs(llvm::Function &F);
    std::set<std::string> inferTreeNodeAnnotations(TreeNode &tree_node, bool is_ret = false);
    void inferAllocStackForKernelToDriverCalls();
    std::string inferAllocStackAnnotation(TreeNode &tree_node);
    void inferUserAnnotation(TreeNode &tree_node, std::set<std::string> &annotations);
    void inferMayWithin(TreeNode &tree_node, std::set<std::string> &anno_str);
    bool globalVarHasAccessInDriver(llvm::GlobalVariable &gv);
    bool isDriverDefinedGlobal(llvm::GlobalVariable &gv);
    bool containerHasSharedFieldsAccessed(llvm::BitCastInst &bci, std::string struct_type_name);
    bool isExportedFunc(llvm::Function &F);
    std::string computeAllocCallerAnnotation(TreeNode &tree_node);
    std::string computeAllocCalleeAnnotation(TreeNode &tree_node);
    std::string getExportedFuncPtrName(std::string func_name);
    std::set<Node *> findAllocator(TreeNode &tree_node, bool is_forward = false);
    // logging related functions
    void printContainerOfStats();
    void logSkbFieldStats(TreeNode &skb_root_node);
    void logSkbNode(TreeNode &tree_node);
    void countControlData(TreeNode &tree_node);
    bool isUsedInBranchStat(Node &val_node);
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
    std::set<std::string> _driver_exported_func_symbols;
    std::set<Node*> _funcs_reachable_from_boundary;
    std::set<llvm::Function *> _kernel_funcs_regsitered_with_indirect_ptr;
    std::set<llvm::Function *> _transitive_boundary_funcs;
    bool _generating_idl_for_global = false;
  };
}

#endif