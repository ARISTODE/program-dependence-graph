#ifndef BOUNDARY_POLICY_GEN_H_
#define BOUNDARY_POLICY_GEN_H_
/*
Generate boundary security policies for accessed fields
*/
#include "DataAccessAnalysis.hh"
#include <fstream>
#include <sstream>

namespace pdg
{
  class BoundaryPolicyGeneration : public llvm::ModulePass
  {
  public:
    static char ID;
    BoundaryPolicyGeneration() : llvm::ModulePass(ID){};
    bool runOnModule(llvm::Module &M) override;
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    void generatePoliciesforFunc(llvm::Function &F);
    void generatePoliciesForArgTree(Tree &argTree, std::ofstream &outputFile, bool isRet = false);
    void generatePoliciesForTreeNode(TreeNode &paramTreeNode, std::ofstream &outputFile);
    std::set<llvm::Value *> computeStoreValuesForParamNode(TreeNode &paramTreeNode);

  private:
    std::ofstream _PolicyFile;
    DataAccessAnalysis *_DDA = nullptr;
  
  };
}

#endif