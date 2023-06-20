#ifndef DEBUGINFOUTILS_H_
#define DEBUGINFOUTILS_H_
#include "LLVMEssentials.hh"
#include <queue>
#include <unordered_set>
#include <set>

namespace pdg
{
  namespace dbgutils
  {
    bool isPointerType(llvm::DIType &dt);
    bool isPrimitiveType(llvm::DIType &dt);
    bool isCompositeType(llvm::DIType &dt);
    bool isCompositePointerType(llvm::DIType &dt);
    bool isUnionPointerType(llvm::DIType &dt);
    bool isUnionType(llvm::DIType &dt);
    bool isStructPointerType(llvm::DIType &dt);
    bool isStructType(llvm::DIType &dt);
    bool isStructArrayType(llvm::DIType &dt);
    bool isFuncPointerType(llvm::DIType &dt);
    bool isProjectableType(llvm::DIType &dt);
    bool hasSameDITypeName(llvm::DIType& d1, llvm::DIType &d2);
    bool isVoidPointerType(llvm::DIType &dt);
    bool isArrayType(llvm::DIType &dt);
    bool isAllocableObjType(llvm::DIType &dt);
    bool isCharPointer(llvm::DIType &dt);
    bool isRecursiveType(llvm::DIType &dt);
    llvm::DIType *getLowestDIType(llvm::DIType &dt);
    llvm::DIType *getBaseDIType(llvm::DIType &dt);
    llvm::DIType *stripAttributes(llvm::DIType &dt);
    llvm::DIType *stripMemberTag(llvm::DIType &dt);
    llvm::DIType *stripMemberTagAndAttributes(llvm::DIType &dt);
    llvm::DIType *getGlobalVarDIType(llvm::GlobalVariable &gv);
    llvm::DIType *getFuncRetDIType(llvm::Function &F);
    std::string getArrayTypeStr(llvm::DIType &dt);
    std::string getSourceLevelVariableName(llvm::DINode &dt);
    std::string getSourceLevelTypeName(llvm::DIType &dt, bool isRaw=false);
    std::string getSourceLevelTypeNameWithNoQualifer(llvm::DIType &dt);
    std::string getArgumentName(llvm::Argument &arg);
    unsigned computeFieldOffsetInBytes(llvm::DIType &dt);
    std::set<llvm::DbgInfoIntrinsic *> collectDbgInstInFunc(llvm::Function &F);
    std::set<llvm::DIType*> computeContainedStructTypes(llvm::DIType &dt);
    std::string getFuncSigName(llvm::DIType &dt, llvm::Function &F, std::string funcPtrName);
    unsigned computeDeepCopyFields(llvm::DIType &dt, bool onlyCountPointer = false);
    unsigned computeStructTypeStorageSize(llvm::DIType &dt, unsigned depth = 1);
  } // namespace dbgutils
} // namespace pdg

#endif