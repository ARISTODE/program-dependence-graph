#ifndef _TAINT_UTILS_H_
#define _TAINT_UTILS_H_
#include "LLVMEssentials.hh"
#include "Tree.hh"
#include "PDGCallGraph.hh"

namespace pdg
{
  namespace taintutils
  {
    // classification for pointer types
    bool isPointerRead(Node &n);
    bool isPointeeModified(Node &n);
    bool isPointerToArray(Node &n);
    bool isBaseInPointerArithmetic(Node &n);

    // classification for array
    bool checkIsArray(Node &n);
    bool isUsedAsArrayIndex(Node &n);

    // classification for non-pointer type
    bool isValueUsedInArithmetic(Node &n);
    bool isValueInSensitiveBranch(Node &n, std::string &senOpName);
    bool isValueInSensitiveAPI(Node &n, std::string &senOpName);

    // helper funcs
    std::string riskyDataTypeToString(RiskyDataType type);
  }
}

#endif