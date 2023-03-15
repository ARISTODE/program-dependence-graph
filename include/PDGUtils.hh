#ifndef PDGUTILS_H_
#define PDGUTILS_H_
#include "LLVMEssentials.hh"
#include "llvm/Demangle/Demangle.h"
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
    uint64_t getGEPOffsetInBits(llvm::Module &M, llvm::StructType &structTy, llvm::GetElementPtrInst &gep);
    bool isNodeBitOffsetMatchGEPBitOffset(Node &n, llvm::GetElementPtrInst &gep);
    bool isGEPOffsetMatchDIOffset(llvm::DIType &dt, llvm::GetElementPtrInst &gep);
    llvm::Function* getCalledFunc(llvm::CallInst &callInst);
    bool hasReadAccess(llvm::Value &v);
    bool hasWriteAccess(llvm::Value &v);
    bool isSentinelType(llvm::GlobalVariable &gv);
    bool isUserOfSentinelTypeVal(llvm::Value &v);
    bool isVoidPointerHasMultipleCasts(TreeNode &treeNode);
    bool hasAsmWriteAccess(llvm::InlineAsm &ia);
    bool isWriteAccessAsmOpcode(std::string opCode);
    bool hasPtrArith(TreeNode &treeNode, bool isSharedData=false);
    bool isTreeNodeValUsedAsOffset(TreeNode &treeNode);
    bool isValueUsedAsOffset(llvm::Value &gep);
    bool isStructPointerType(llvm::Type &type);
    bool isDoublePointer(llvm::Value &val);
    llvm::Instruction* getNextInst(llvm::Instruction &i);
    llvm::Function* getNescheckVersionFunc(llvm::Module& M, std::string funcName);
    llvm::inst_iterator getInstIter(llvm::Instruction &i);
    std::set<llvm::Instruction *> getInstructionBeforeInst(llvm::Instruction &i);
    std::set<llvm::Instruction *> getInstructionAfterInst(llvm::Instruction &i);
    std::set<llvm::Value *> computeAddrTakenVarsFromAlloc(llvm::AllocaInst &ai);
    std::set<llvm::Value *> computeAliasForRetVal(llvm::Value &val, llvm::Function &func);
    std::set<std::string> splitStr(std::string split_str, std::string delimiter);
    llvm::AliasResult queryAliasUnderApproximate(llvm::Value &v1, llvm::Value &v2);
    void printTreeNodesLabel(Node* n, llvm::raw_string_ostream &OS, std::string treeNodeTyStr);
    llvm::Value *getLShrOnGep(llvm::GetElementPtrInst &gep);
    std::string stripFuncNameVersionNumber(std::string funcName);
    std::string stripNescheckPostfix(std::string funcName);
    std::string getSourceFuncName(std::string funcName);
    std::string computeTreeNodeID(TreeNode &treeNode);
    std::string computeFieldID(llvm::DIType &parentDt, llvm::DIType &fieldDt);
    std::string stripVersionTag(std::string str);
    std::string ltrim(std::string str);
    std::string rtrim(std::string str);
    std::string trimStr(std::string str);
    std::string constructAnnoStr(std::set<std::string> &annotations);
    bool isMainFunc(llvm::Function &F);
    bool isFileExist(std::string fileName);
    bool isSkbNode(TreeNode& treeNode);
    bool isPrecedeInst(llvm::Instruction &i1, llvm::Instruction &i2, llvm::Function &F);
    void printTreeNodeAddrVars(TreeNode &treeNode);
    std::string getDemangledName(const char *mangledName);
    void readLinesFromFile(std::set<std::string> &lines, std::string fileName);
  } // namespace pdgutils
} // namespace pdg
#endif