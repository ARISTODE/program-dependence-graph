#ifndef DATAACCESSANALYSIS_H_
#define DATAACCESSANALYSIS_H_
#include "ProgramDependencyGraph.hh"
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
      void computeDataAccessForTreeNode(TreeNode &tree_node);
      void computeDataAccessForTree(Tree* tree);
      void computeIntraProcDataAccess(llvm::Function &F);
      void computeInterProcDataAccess(llvm::Function &F);
      void generateIDLForFunc(llvm::Function &F);
      void generateRpcForFunc(llvm::Function &F);
      void generateIDLFromArgTree(Tree *arg_tree);
      void generateIDLFromTreeNode(TreeNode &tree_node, llvm::raw_string_ostream &projection_str, std::queue<TreeNode *> &node_queue, std::string indent_level);

    private:
      llvm::Module *_module;
      ProgramGraph *PDG;
      std::ofstream idl_file;
  };
}

#endif