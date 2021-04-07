#ifndef DATAACCESSANALYSIS_H_
#define DATAACCESSANALYSIS_H_
#include "SharedDataAnalysis.hh"
#include <fstream>
#include <sstream>

namespace pdg
{
  class KSplitStats
  {
  public:
    KSplitStats() = default;
    void increaseSharedPtr() { _shared_ptr_num++; }
    void increaseSafePtr() { _safe_ptr_num++; }
    void increaseVoidPtrNum() { _void_ptr_num++; }
    void increaseStringNum() { _string_num++; }
    void increaseArrayNum() { _array_num++; }
    void increaseFuncPtrNum() { _func_ptr_num++; }
    void increaseWildPtrNum() { _wild_ptr_num++; }
    void increaseUnknownPtrNum() { _unknown_ptr_num++; }
    void collectStats(llvm::DIType &dt, std::set<std::string> &annotations);
    void printStats();

  private:
    unsigned _shared_ptr_num = 0;
    unsigned _safe_ptr_num = 0;
    unsigned _void_ptr_num = 0;
    unsigned _handled_void_ptr_num = 0;
    unsigned _string_num = 0;
    unsigned _array_num = 0;
    unsigned _wild_ptr_num = 0;
    unsigned _unknown_ptr_num = 0;
    unsigned _func_ptr_num = 0;
  };

  class DataAccessAnalysis : public llvm::ModulePass
  {
  public:
    static char ID;
    DataAccessAnalysis() : llvm::ModulePass(ID){};
    bool runOnModule(llvm::Module &M) override;
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Data Access Analysis"; }
    std::set<AccessTag> computeDataAccessTagsForVal(llvm::Value &val);
    void computeExportedFuncsPtrNameMap();
    void computeDataAccessForTreeNode(TreeNode &tree_node);
    void computeDataAccessForTree(Tree *tree);
    void computeIntraProcDataAccess(llvm::Function &F);
    void computeInterProcDataAccess(llvm::Function &F);
    void generateIDLForFunc(llvm::Function &F);
    void generateRpcForFunc(llvm::Function &F);
    void generateIDLFromArgTree(Tree *arg_tree, bool is_ret = false);
    void generateIDLFromTreeNode(TreeNode &tree_node, llvm::raw_string_ostream &fields_projection_str, llvm::raw_string_ostream &nested_struct_projion_str, std::queue<TreeNode *> &node_queue, std::string indent_level);
    void constructGlobalOpStructStr();
    void computeContainerOfLocs(llvm::Function &F);
    std::set<std::string> inferTreeNodeAnnotations(TreeNode &tree_node);
    bool isAllocator(llvm::Value &val);
    std::string computeAllocCallerAnnotation(TreeNode &tree_node);
    bool isWrittenWithNewObjFromCallee(TreeNode &tree_node);
    std::set<Node *> findAllocator(TreeNode &tree_node);
    void printContainerOfStats();
    KSplitStats *getKSplitStats() { return _ksplit_stats; }
    SharedDataAnalysis *getSDA() { return _SDA; }
    ProgramGraph *getPDG() { return _PDG; }

  private:
    llvm::Module *_module;
    SharedDataAnalysis *_SDA;
    ProgramGraph *_PDG;
    PDGCallGraph *_call_graph;
    std::ofstream idl_file;
    std::set<std::string> _seen_func_ops;
    std::string _ops_struct_proj_str;
    std::map<std::string, std::string> _exported_funcs_ptr_name_map;
    std::map<std::string, std::set<std::string>> _global_ops_fields_map;
    std::set<llvm::Instruction *> _container_of_insts;
    KSplitStats *_ksplit_stats;
  };
}

#endif