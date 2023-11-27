#ifndef _TAINT_UTILS_H_
#define _TAINT_UTILS_H_
#include "LLVMEssentials.hh"
#include "Tree.hh"
#include "PDGCallGraph.hh"
#include "json.hpp"

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
    bool isValUsedInDivByZero(Node &n);
    bool isValueInSensitiveBranch(Node &n, std::string &senOpName);
    bool isValueInSensitiveAPI(Node &n, std::string &senOpName);

    // propagate taints along provided edges
    void propagateTaints(Node &srcNode, std::set<EdgeType> &edgeTypes, std::set<Node *> &taintNodes);

    // helper funcs
    std::string riskyDataTypeToString(RiskyDataType type);
    void printJsonToFile(nlohmann::ordered_json &json, std::string logFileName);
    bool isRiskyFunc(std::string funcName);
    std::string getRiskyClassStr(std::string funcName);
    
    // counting methods
    nlohmann::ordered_json countRiskyAPIClasses(const nlohmann::ordered_json &riskyAPIJsonObjs);
  }
}

#endif