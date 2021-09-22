#ifndef DEBUGINFOUTILS_H_
#define DEBUGINFOUTILS_H_
#include "LLVMEssentials.hh"
#include <queue>
#include <set>

namespace pdg
{
  namespace dbgutils
  {
    bool isPointerType(llvm::DIType &dt);
    bool isUnionPointerType(llvm::DIType &dt);
    bool isUnionType(llvm::DIType &dt);
    bool isStructPointerType(llvm::DIType &dt);
    bool isStructType(llvm::DIType &dt);
    bool isStructArrayType(llvm::DIType &dt);
    bool isFuncPointerType(llvm::DIType &dt);
    bool isProjectableType(llvm::DIType &dt);
    bool hasSameDIName(llvm::DIType& d1, llvm::DIType &d2);
    bool isVoidPointerType(llvm::DIType &dt);
    bool isArrayType(llvm::DIType &dt);
    llvm::DIType *getLowestDIType(llvm::DIType &dt);
    llvm::DIType *getBaseDIType(llvm::DIType &dt);
    llvm::DIType *stripAttributes(llvm::DIType &dt);
    llvm::DIType *stripMemberTag(llvm::DIType &dt);
    llvm::DIType *getGlobalVarDIType(llvm::GlobalVariable &gv);
    llvm::DIType *getFuncRetDIType(llvm::Function &F);
    std::string getSourceLevelVariableName(llvm::DINode &dt);
    std::string getSourceLevelTypeName(llvm::DIType &dt, bool is_raw=false);
    std::string getSourceLevelTypeNameWithNoQualifer(llvm::DIType &dt);
    std::string getArgumentName(llvm::Argument &arg);
    std::set<llvm::DbgInfoIntrinsic *> collectDbgInstInFunc(llvm::Function &F);
    std::set<llvm::DIType*> computeContainedStructTypes(llvm::DIType &dt);
    std::string getFuncSigName(llvm::DIType &dt, llvm::Function &F, std::string func_ptr_name);
    unsigned computeDeepCopyFields(llvm::DIType &dt, bool only_count_pointer = false);
  } // namespace dbgutils
} // namespace pdg

#endif