#include "TaintUtils.hpp"

using namespace llvm;

static std::unordered_set<std::string> sensitiveOperations = {
    // "malloc",
    // "free",
    "kmalloc",
    "vmalloc",
    "kzalloc",
    "vzalloc",
    "kmem_cache_create",
    "kmem_cache_alloc",
    "kmem_cache_free",
    "kmem_cache_destroy",
    "kfree",
    "vfree",
    "copy_from_user",
    "copy_to_user",
    "memcpy",
    "strcpy",
    "strncpy",
    "memset",
    "kobject_put",
    "kobject_create_and_add",
};

// check if the pointer is dereferneced
bool pdg::taintutils::isPointerRead(Node &n)
{
  auto nodeVal = n.getValue();
  if (nodeVal && nodeVal->getType()->isPointerTy())
    return pdgutils::hasPtrDereference(*nodeVal);
  return false;
}

// check if the pointed value is modified
bool pdg::taintutils::isPointeeModified(Node &n)
{
  auto nodeVal = n.getValue();
  if (nodeVal && nodeVal->getType()->isPointerTy())
    return pdgutils::hasWriteAccess(*nodeVal);
  return false;
}

// check if this pointer points to an array
bool pdg::taintutils::isPointerToArray(Node &n)
{
  // we should check if any pointer arithmetic operations is performed on this value to read array content
  auto nodeVal = n.getValue();
  if (!nodeVal)
    return false;

  auto valType = nodeVal->getType();
  if (valType->isPointerTy() && !pdgutils::isStructPointerType(*valType))
  {
    for (auto user : nodeVal->users())
    {
      // check gep arithmetic
      if (isa<GetElementPtrInst>(user))
        return true;
    }
  }
  return false;
}

// in addition to check gep, we also check ptrtoint here
bool pdg::taintutils::isBaseInPointerArithmetic(Node &n)
{
  // we should check if any pointer arithmetic operations is performed on this value to read array content
  auto nodeVal = n.getValue();
  if (!nodeVal)
    return false;

  auto valType = nodeVal->getType();
  if (valType->isPointerTy() && !pdgutils::isStructPointerType(*valType))
  {
    for (auto user : nodeVal->users())
    {
      // check gep arithmetic
      if (isa<GetElementPtrInst>(user) || isa<PtrToIntInst>(user))
        return true;
    }
  }
  return false;
}

// classification for array
bool pdg::taintutils::checkIsArray(Node &n)
{
  auto nodeVal = n.getValue();
  auto valType = nodeVal->getType();
  return valType->isArrayTy();
}

bool pdg::taintutils::isUsedAsArrayIndex(Node &n)
{
  // used as the second operand in gep
  auto nodeVal = n.getValue();
  if (!nodeVal)
    return false;

  for (auto user : nodeVal->users())
  {
    if (auto gep = dyn_cast<GetElementPtrInst>(user))
    {
      if (gep->getPointerOperand() != nodeVal)
        return true;
    }
  }
  return false;
}

// classification for non-pointer type
bool pdg::taintutils::isValueUsedInArithmetic(Node &n)
{
  auto nodeVal = n.getValue();
  if (!nodeVal)
    return false;

  for (auto user : nodeVal->users())
  {
    // add, mul, sub etc
    if (isa<OverflowingBinaryOperator>(user))
      return true;
  }
  return false;
}

bool pdg::taintutils::isValueInSensitiveBranch(Node &n, std::string &senOpName)
{
  ProgramGraph &PDG = ProgramGraph::getInstance();
  PDGCallGraph &callGraph = PDGCallGraph::getInstance();
  auto nodeVal = n.getValue();
  if (!nodeVal)
    return false;
  for (auto user : nodeVal->users())
  {
    if (auto cmpInst = dyn_cast<CmpInst>(user))
    {
      for (auto u : cmpInst->users())
      {
        if (isa<BranchInst>(u) || isa<SwitchInst>(u))
        {
          auto branchNode = PDG.getNode(*u);
          auto branchControlDependentNodes = PDG.findNodesReachedByEdge(*branchNode, EdgeType::CONTROL);
          for (auto ctrDepNode : branchControlDependentNodes)
          {
            auto depNodeVal = ctrDepNode->getValue();
            if (CallInst *ci = dyn_cast<CallInst>(depNodeVal))
            {
              auto calledFunc = pdgutils::getCalledFunc(*ci);
              if (!calledFunc)
                continue;
              // some sensitive operations such as BUG() is translated
              // to inline assembly
              if (ci->isInlineAsm())
              {
                senOpName = "inline_asm";
                return true;
              }
              auto calledFuncName = calledFunc->getName().str();
              // we only check if a sensitive API is directly enabled in the branch
              for (auto op : sensitiveOperations)
              {
                if (calledFuncName.find(op) != std::string::npos)
                {
                  senOpName = op;
                  return true;
                }
              }
              // check if the call can reach sensitive operations
              // auto calledFuncNode = callGraph->getNode(*calledFunc);
              // if (auto senOpFunc = canReachSensitiveOperations(*calledFuncNode))
              //   return true;
            }
          }
        }
      }
    }
  }
  return false;
}

bool pdg::taintutils::isValueInSensitiveAPI(Node &n, std::string &senOpName)
{
  auto nodeVal = n.getValue();
  if (!nodeVal)
    return false;

  for (auto user : nodeVal->users())
  {
    if (CallInst *ci = dyn_cast<CallInst>(user))
    {
      auto calledFunc = pdgutils::getCalledFunc(*ci);
      if (!calledFunc)
        continue;
      auto calledFuncName = calledFunc->getName().str();
      for (auto op : sensitiveOperations)
      {
        if (calledFuncName.find(op) != std::string::npos)
        {
          senOpName = op;
          return true;
        }
      }
    }
  }
  return false;
}

std::string pdg::taintutils::riskyDataTypeToString(pdg::RiskyDataType type)
{
  switch (type)
  {
  case RiskyDataType::PTR_READ:
    return "PTR_READ";
  case RiskyDataType::PTR_WRTIE:
    return "PTR_WRITE";
  case RiskyDataType::PTR_BUFFER:
    return "PTR_BUFFER";
  case RiskyDataType::PTR_ARITH_BASE:
    return "PTR_ARITH_BASE";
  case RiskyDataType::ARR_BUFFER:
    return "ARR_BUFFER";
  case RiskyDataType::ARR_IDX:
    return "ARR_IDX";
  case RiskyDataType::NUM_ARITH:
    return "NUM_ARITH";
  case RiskyDataType::CONTROL_SENBRANCH:
    return "CONTROL_SENB_RANCH";
  case RiskyDataType::SEN_API:
    return "SEN_API";
  case RiskyDataType::FUNC_PTR:
    return "FUNC_PTR";
  case RiskyDataType::OTHER:
    return "UNCLASSIFY";
  default:
    return "";
  }
}