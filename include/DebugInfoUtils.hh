#ifndef DEBUGINFOUTILS_H_
#define DEBUGINFOUTILS_H_
#include "LLVMEssentials.hh"

namespace pdg
{
  namespace dbgutils
  {
    bool isPointerType(llvm::DIType &dt);
    bool isStructType(llvm::DIType &dt);
    bool isUnionType(llvm::DIType &dt);
    bool isStructPointerType(llvm::DIType &dt);
    bool isProjectableType(llvm::DIType &dt);
    llvm::DIType *getLowestDIType(llvm::DIType &dt);
    llvm::DIType *getBaseDIType(llvm::DIType &dt);
    llvm::DIType *stripAttributes(llvm::DIType &dt);
    llvm::DIType *getGlobalVarDIType(llvm::GlobalVariable &gv);
    std::string getSourceLevelVariableName(llvm::DINode &dt);
    std::string getSourceLevelTypeName(llvm::DIType &dt);
  } // namespace dbgutils
} // namespace pdg

#endif