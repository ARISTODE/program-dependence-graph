#ifndef PDGUTILS_H_
#define PDGUTILS_H_
#include "LLVMEssentials.hh"
#include "Tree.hh"
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <fstream>

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
    bool isSentinelType(llvm::GlobalVariable &gv);
    bool isUserOfSentinelTypeVal(llvm::Value &v);
    bool isVoidPointerHasMultipleCasts(TreeNode &tree_node);
    bool hasAsmWriteAccess(llvm::InlineAsm &ia);
    bool isWriteAccessAsmOpcode(std::string op_code);
    bool hasPtrArith(TreeNode &tree_node, bool is_shared_data=false);
    bool isStructPointerType(llvm::Type &type);
    llvm::Instruction* getNextInst(llvm::Instruction &i);
    llvm::Function* getNescheckVersionFunc(llvm::Module& M, std::string func_name);
    llvm::inst_iterator getInstIter(llvm::Instruction &i);
    std::set<llvm::Instruction *> getInstructionBeforeInst(llvm::Instruction &i);
    std::set<llvm::Instruction *> getInstructionAfterInst(llvm::Instruction &i);
    std::set<llvm::Value *> computeAddrTakenVarsFromAlloc(llvm::AllocaInst &ai);
    std::set<llvm::Value *> computeAliasForRetVal(llvm::Value &val, llvm::Function &func);
    std::set<std::string> splitStr(std::string split_str, std::string delimiter);
    llvm::AliasResult queryAliasUnderApproximate(llvm::Value &v1, llvm::Value &v2);
    void printTreeNodesLabel(Node* n, llvm::raw_string_ostream &OS, std::string tree_node_type_str);
    llvm::Value *getLShrOnGep(llvm::GetElementPtrInst &gep);
    std::string stripFuncNameVersionNumber(std::string func_name);
    std::string stripNescheckPostfix(std::string func_name);
    std::string getSourceFuncName(std::string func_name);
    std::string computeTreeNodeID(TreeNode &tree_node);
    std::string computeFieldID(llvm::DIType &parent_dt, llvm::DIType &field_dt);
    std::string stripVersionTag(std::string str);
    std::string ltrim(std::string str);
    std::string rtrim(std::string str);
    std::string trimStr(std::string str);
    bool isFileExist(std::string file_name);
    bool isSkbNode(TreeNode& tree_node);
  } // namespace pdgutils
} // namespace pdg
#endif