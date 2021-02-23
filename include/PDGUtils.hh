#include "LLVMEssentials.hh"
#include "Tree.hh"
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>

namespace pdg
{
  class TreeNode;

  namespace pdgutils
  {
    llvm::StructType *getStructTypeFromGEP(llvm::GetElementPtrInst &gep);
    int getGEPAccessFieldOffset(llvm::GetElementPtrInst &gep);
    uint64_t getGEPOffsetInBits(llvm::Module &M, llvm::StructType &struct_type, llvm::GetElementPtrInst &gep);
    bool isNodeBitOffsetMatchGEPBitOffset(Node &n, llvm::GetElementPtrInst &gep);
    bool isGEPOffsetMatchDIOffset(llvm::DIType &dt, llvm::GetElementPtrInst &gep);
    llvm::Function* getCalledFunc(llvm::CallInst &call_inst);
    bool hasReadAccess(llvm::Value &v);
    bool hasWriteAccess(llvm::Value &v);
    llvm::inst_iterator getInstIter(llvm::Instruction &i);
    std::set<llvm::Instruction *> getInstructionBeforeInst(llvm::Instruction &i);
    std::set<llvm::Instruction *> getInstructionAfterInst(llvm::Instruction &i);
    std::set<llvm::Value *> computeAddrTakenVarsFromAlloc(llvm::AllocaInst &ai);
    void printTreeNodesLabel(Node* n, llvm::raw_string_ostream &OS, std::string tree_node_type_str);
    llvm::Value *getLShrOnGep(llvm::GetElementPtrInst &gep);
    std::string stripFuncNameVersionNumber(std::string func_name);
    std::string computeTreeNodeID(TreeNode &tree_node);
    std::string stripVersionTag(std::string str);
  } // namespace pdgutils
} // namespace pdg