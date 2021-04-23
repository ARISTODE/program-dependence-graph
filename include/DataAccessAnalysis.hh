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
      DataAccessAnalysis() : llvm::ModulePass(ID) {};
      bool runOnModule(llvm::Module &M) override;
      void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
      llvm::StringRef getPassName() const override { return "Data Access Analysis"; }
      std::set<AccessTag> computeDataAccessTagsForVal(llvm::Value &val);
      void computeExportedFuncsPtrNameMap();
      void computeDataAccessForTreeNode(TreeNode &tree_node);
      void computeDataAccessForTree(Tree* tree);
      void computeIntraProcDataAccess(llvm::Function &F);
      void computeInterProcDataAccess(llvm::Function &F);
      void generateIDLForFunc(llvm::Function &F);
      void generateRpcForFunc(llvm::Function &F);
      void generateIDLFromArgTree(Tree *arg_tree, bool is_ret = false);
      void generateIDLFromTreeNode(TreeNode &tree_node, llvm::raw_string_ostream &fields_projection_str, llvm::raw_string_ostream &nested_struct_projion_str, std::queue<TreeNode *> &node_queue, std::string indent_level);
      void constructGlobalOpStructStr();
      void computeContainerOfLocs(llvm::Function &F);
      std::set<std::string> inferTreeNodeAnnotations(TreeNode &tree_node);
      SharedDataAnalysis *getSDA() { return _SDA; }
      void printContainerOfStats();

    private:
      llvm::Module *_module;
      SharedDataAnalysis* _SDA;
      ProgramGraph *_PDG;
      std::ofstream idl_file;
      std::set<std::string> _seen_func_ops;
      std::string _ops_struct_proj_str;
      std::map<std::string, std::string> _exported_funcs_ptr_name_map;
      std::map<std::string, std::set<std::string>> _global_ops_fields_map;
      std::set<llvm::Instruction*> _container_of_insts;
  };
}

#endif