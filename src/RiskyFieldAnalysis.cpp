#include "RiskyFieldAnalysis.hh"
// #include "RiskyAPIAnalysis.hh"
#include "KSplitCFG.hh"
/*
This analysis is used to compute a set of risky patterns realted to each shared field between the 
kernel and driver. The followings are a set of classes we define.
1. Used in memory allocation: Resource exhaustion 
2. Involved in I/O operations: e.g., read/write APIs
3. Used as array indices: execute out-of-bounds read/write
4. Used to derive addresses that kernel access: if a field could derive addresses (ptr arithmetic) that kernel may access, then it could leak to wrong/illegal memory access
5. Function pointer: potential for control flow hijacking
6. Used in syncrhonization primitives: causing race conditions/dead locks
7. Security-critical operations: user authentication, privilege checks
*/

char pdg::RiskyFieldAnalysis::ID = 0;
using namespace llvm;

void pdg::RiskyFieldAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<SharedDataAnalysis>();
  // AU.addRequired<RiskyAPIAnalysis>();
  AU.setPreservesAll();
}

std::unordered_set<std::string> sensitiveOperations = {
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

// setup taint edges
std::set<pdg::EdgeType> taintEdges = {
    pdg::EdgeType::PARAMETER_IN,
    // pdg::EdgeType::PARAMETER_OUT,
    // pdg::EdgeType::DATA_ALIAS,
    // EdgeType::DATA_RET,
    // pdg::EdgeType::CONTROL,
    pdg::EdgeType::DATA_STORE_TO,
    pdg::EdgeType::DATA_DEF_USE,
};

std::set<Function *> readFuncsFromFile(std::string fileName, Module &M)
{
  std::set<Function *> ret;
  std::ifstream ReadFile(fileName);
  for (std::string line; std::getline(ReadFile, line);)
  {
      Function *f = M.getFunction(StringRef(line));
      if (!f)
          continue;
      ret.insert(f);
  }
  return ret;
}

bool pdg::RiskyFieldAnalysis::runOnModule(Module &M)
{
  _module = &M;
  _SDA = &getAnalysis<SharedDataAnalysis>();
  _PDG = _SDA->getPDG();
  _callGraph = &PDGCallGraph::getInstance();
  std::error_code EC;
  riskyFieldOS = new raw_fd_ostream("RiskyField.log", EC, sys::fs::OF_Text);
  if (EC)
  {
      delete riskyFieldOS;
      errs() << "cannot open RiskyField.log\n";
      return false;
  }

  riskyFieldTaintOS = new raw_fd_ostream("RiskyFieldTaint.log", EC, sys::fs::OF_Text);
  if (EC)
  {
      delete riskyFieldTaintOS;
      errs() << "cannot open RiskyField.log\n";
      return false;
  }

  auto globalStructDTMap = _SDA->getGlobalStructDTMap();
  for (auto dtPair : globalStructDTMap)
  {
      auto typeTree = dtPair.second;
      std::queue<TreeNode *> nodeQueue;
      nodeQueue.push(typeTree->getRootNode());

      while (!nodeQueue.empty())
      {
          TreeNode *n = nodeQueue.front();
          nodeQueue.pop();
          DIType *nodeDIType = n->getDIType();
          if (nodeDIType == nullptr)
              continue;
          // classify the risky field into different classes
          if (isDriverControlledField(*n))
          {
              numKernelReadDriverUpdatedFields++;
              // classifyRiskyFieldDirectUse(*n);
              classifyRiskyFieldTaint(*n);
          }

          for (auto childNode : n->getChildNodes())
          {
              nodeQueue.push(childNode);
          }
      }
  }

  // TODO: taint the return value of driver interface functions
  // classify the taint based on the data directly passed across the isolation boundary
  auto kernelAPIs = readFuncsFromFile("imported_funcs", M);
  for (auto func : kernelAPIs)
  {
      errs() << "checking boundary func: " << func->getName() << "\n";
      if (_SDA->isDriverFunc(*func))
          continue;

      if (isSensitiveOperation(*func))
      {
          *riskyFieldTaintOS << "Found directly called sensitive ops: " << func->getName() << "\n";
          *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
      }

      auto funcWrapper = _PDG->getFuncWrapper(*func);
      if (!funcWrapper)
          continue;

      auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
      for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
      {
          auto argTree = iter->second;
          auto rootNode = argTree->getRootNode();
          auto argDIType = rootNode->getDIType();
          // struct and struct fields are covered by type taint
          if (argDIType && dbgutils::isStructPointerType(*argDIType))
              continue;

          numKernelAPIParam++;
          std::queue<TreeNode *> nodeQueue;
          nodeQueue.push(argTree->getRootNode());
          while (!nodeQueue.empty())
          {
              TreeNode *n = nodeQueue.front();
              nodeQueue.pop();
              DIType *nodeDIType = n->getDIType();
              if (nodeDIType == nullptr)
                  continue;
              classifyRiskyFieldTaint(*n);
              for (auto childNode : n->getChildNodes())
              {
                  nodeQueue.push(childNode);
              }
          }
      }
  }

  printTaintFieldInfo();
  // printFieldDirectUseClassification(*riskyFieldOS);
  printFieldClassificationTaint(*riskyFieldOS);
  riskyFieldOS->close();
  riskyFieldTaintOS->close();
  return false;
}

bool pdg::RiskyFieldAnalysis::isDriverControlledField(TreeNode &tn)
{
  // only classify for sturct fields
  if (!tn.isStructField())
      return false;

  // init kernel/driver read/write stats
  unsigned driverReadTimes = 0;
  unsigned driverWriteTimes = 0;
  unsigned kernelReadTimes = 0;
  unsigned kernelWriteTimes = 0;

  // all the function pointers exported by the driver are updated in the driver domain (static init)
  if (_SDA->isFuncPtr(tn) && _SDA->isDriverCallBackFuncPtrFieldNode(tn))
      driverWriteTimes += 1;

  auto addrVars = tn.getAddrVars();
  for (auto addrVar : addrVars)
  {
      if (Instruction *i = dyn_cast<Instruction>(addrVar))
      {
          Function *f = i->getFunction();
          // count driver read write times
          if (_SDA->isDriverFunc(*f))
          {
              if (pdgutils::isUpdatedInHeader(*i))
                  continue;
              if (pdgutils::hasWriteAccess(*i))
                  driverWriteTimes++;
              if (pdgutils::hasReadAccess(*i))
                  driverReadTimes++;
          }
          // count kernel read write times
          else if (_SDA->isKernelFunc(*f))
          {
              if (pdgutils::hasReadAccess(*i))
                  kernelReadTimes++;
              if (pdgutils::hasWriteAccess(*i))
                  kernelWriteTimes++;
          }
      }
      if (driverWriteTimes > 0 && kernelReadTimes > 0)
          return true;
  }
  return false;
}

const std::string RED("\033[1;31m");
const std::string YELLOW("\033[1;33m");

std::string colorize(const std::string &str, const std::string &color_code)
{
  return color_code + str + "\033[0m";
}

void pdg::RiskyFieldAnalysis::classifyRiskyFieldDirectUse(TreeNode &tn)
{
  if (!tn.isStructField())
      return;

  std::string accessPathStr = tn.getSrcHierarchyName(false, false);
  auto fieldDIType = tn.getDIType();
  // for a struct field, always getting the child node addr vars as the child
  // node addr vars represet the field value
  auto addrVars = tn.getAddrVars();
  if (tn.getChildNodes().size() > 0)
  {
      auto ptrNode = tn.getChildNodes()[0];
      if (ptrNode)
          addrVars = ptrNode->getAddrVars();
  }

  bool classified = false;
  // classify based on pointer and non-pointer fields
  if (dbgutils::isPointerType(*fieldDIType))
  {
      bool isArithPtrField = false;
      bool isDerefPtrField = false;
      bool isSensitiveOpPtrField = false;
      bool isBranchPtrField = false;

      numPtrField++;
      // classify function pointer (code pointer) and data pointer
      if (dbgutils::isFuncPointerType(*fieldDIType))
      {
          numFuncPtrField++;
          classified = true;
          *riskyFieldOS << "Risky function ptr kernel read locations " << colorize(accessPathStr, YELLOW) << ":\n";
          for (auto addrVar : addrVars)
          {
              if (Instruction *i = dyn_cast<Instruction>(addrVar))
              {
                  auto instFunc = i->getFunction();
                  if (_SDA->isKernelFunc(*instFunc))
                  {
                      *riskyFieldOS << "\t";
                      pdgutils::printSourceLocation(*i, *riskyFieldOS);
                  }
              }
          }
          *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
      }
      else
      {
          // data pointers
          numDataPtrField++;
          for (auto addrVar : addrVars)
          {
              if (Instruction *i = dyn_cast<Instruction>(addrVar))
              {
                  auto instFunc = i->getFunction();
                  if (_SDA->isKernelFunc(*instFunc))
                  {
                      auto addrVarNode = _PDG->getNode(*addrVar);
                      // 1. check if the field is used in pointer arithmetic
                      if (!isArithPtrField && checkPtrValUsedInPtrArithOp(*addrVarNode))
                      {
                          isArithPtrField = true;
                          numPtrArithPtrField++;
                          *riskyFieldOS << "Risky ptr arith (ptr) " << colorize(accessPathStr, YELLOW) << ":\n";
                          pdgutils::printSourceLocation(*i, *riskyFieldOS);
                          *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
                          *riskyFieldOS << "\n";
                      }
                      // 2. check if the ptr field is directly dereferenced
                      if (!isDerefPtrField && pdgutils::hasPtrDereference(*addrVar))
                      {
                          isDerefPtrField = true;
                          numDereferencePtrField++;
                          *riskyFieldOS << "Risky ptr dereference (ptr) " << colorize(accessPathStr, YELLOW) << ":\n";
                          pdgutils::printSourceLocation(*i, *riskyFieldOS);
                          *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
                          *riskyFieldOS << "\n";
                      }
                      // 3. check if used in sensitive operations
                      if (!isSensitiveOpPtrField && checkValUsedInSensitiveOperations(*addrVarNode))
                      {
                          isSensitiveOpPtrField = true;
                          numSensitiveOpPtrField++;
                          *riskyFieldOS << "Risky sensitive op (ptr) " << colorize(accessPathStr, YELLOW) << ":\n";
                          pdgutils::printSourceLocation(*i, *riskyFieldOS);
                          *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
                          *riskyFieldOS << "\n";
                      }
                      // 4. check if used in branch that contain sensitive operations
                      if (!isBranchPtrField && checkValUsedInSenBranchCond(*addrVarNode, *riskyFieldOS))
                      {
                          isBranchPtrField = true;
                          numBranchPtrField++;
                          *riskyFieldOS << "Risky branch (ptr) " << colorize(accessPathStr, YELLOW) << ":\n";
                          pdgutils::printSourceLocation(*i, *riskyFieldOS);
                          *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
                          *riskyFieldOS << "\n";
                      }
                  }
              }
          }
          // mark as classified
          if (isArithPtrField || isDerefPtrField || isSensitiveOpPtrField || isBranchPtrField)
              classified = true;
      }
  }
  else
  {
      bool isArrayIdxField = false;
      bool isArithField = false;
      bool isBranchField = false;
      bool isUsedInSensitiveOp = false;
      for (auto addrVar : addrVars)
      {
          if (Instruction *i = dyn_cast<Instruction>(addrVar))
          {
              auto instFunc = i->getFunction();
              if (_SDA->isKernelFunc(*instFunc))
              {
                  auto addrVarNode = _PDG->getNode(*addrVar);
                  if (!isArrayIdxField && checkValUsedAsArrayIndex(*addrVarNode))
                  {
                      isArrayIdxField = true;
                      numArrayIdxField++;
                      *riskyFieldOS << "Risky array idx " << colorize(accessPathStr, RED) << ":\n";
                      pdgutils::printSourceLocation(*i, *riskyFieldOS);
                      *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
                      *riskyFieldOS << "\n";
                  }

                  if (!isArithField && checkValUsedInPtrArithOp(*addrVarNode))
                  {
                      isArithField = true;
                      numArithField++;
                      *riskyFieldOS << "Risky arith op " << colorize(accessPathStr, RED) << ":\n";
                      pdgutils::printSourceLocation(*i, *riskyFieldOS);
                      *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
                      *riskyFieldOS << "\n";
                  }

                  if (!isBranchField && checkValUsedInSenBranchCond(*addrVarNode, *riskyFieldOS))
                  {
                      isBranchField = true;
                      numSensitiveBranchField++;
                      *riskyFieldOS << "Risky branch " << colorize(accessPathStr, RED) << ":\n";
                      pdgutils::printSourceLocation(*i, *riskyFieldOS);
                      *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
                      *riskyFieldOS << "\n";
                  }

                  if (!isUsedInSensitiveOp && checkValUsedInSensitiveOperations(*addrVarNode))
                  {
                      isUsedInSensitiveOp = true;
                      numSensitiveOpsField++;
                      *riskyFieldOS << "Risky sensitive op " << colorize(accessPathStr, RED) << ":\n";
                      pdgutils::printSourceLocation(*i, *riskyFieldOS);
                      *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
                      *riskyFieldOS << "\n";
                  }
              }
          }
      }
      if (isArrayIdxField || isArithField || isBranchField || isUsedInSensitiveOp)
          classified = true;
  }
  // print unclassified field
  if (!classified)
  {
      std::string funcAttr = "";
      if (dbgutils::isFuncPointerType(*fieldDIType))
      {
          funcAttr = " (fptr) ";
          numUnclassifiedFuncPtrField++;
      }
      numUnclassifiedField++;
      *riskyFieldOS << "Unclassified field: " << funcAttr << colorize(accessPathStr, RED) << "\n";
      for (auto addrVar : addrVars)
      {
          if (auto inst = dyn_cast<Instruction>(addrVar))
          {
              auto f = inst->getFunction();
              if (_SDA->isKernelFunc(*f))
              {
                  pdgutils::printSourceLocation(*inst, *riskyFieldOS);
              }
          }
      }
      *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
      *riskyFieldOS << "\n";
  }
}

// Taint source: the direct read of driver-controlled shared fields in the kernel
void pdg::RiskyFieldAnalysis::classifyRiskyFieldTaint(TreeNode &tn)
{
  // if (!tn.isStructField())
  //     return;
  std::string accessPathStr = tn.getSrcHierarchyName();
//   auto &cfg = KSplitCFG::getInstance();
//   if (!cfg.isBuild())
//       cfg.build(*_module);

  // obtain the address variables representing the field
  auto addrVars = tn.getAddrVars();

  auto fieldDIType = tn.getDIType();
  bool classified = false;
  // classify between pointer and non-pointer
  if (dbgutils::isPointerType(*fieldDIType))
  {
      numPtrField++;
      bool isArithPtrField = false;
      bool isDerefPtrField = false;
      bool isSensitiveOpPtrField = false;
      bool isBranchPtrField = false;
      bool isStructPointerTy = dbgutils::isStructPointerType(*fieldDIType);
      // We only compute taint for data pointers
      if (dbgutils::isFuncPointerType(*fieldDIType))
      {
          numFuncPtrField++;
          classified = true;
      }
      else
      {
          numDataPtrField++;
          for (auto addrVar : addrVars)
          {
              auto addrVarInst = cast<Instruction>(addrVar);
              auto func = addrVarInst->getFunction();
              if (!_SDA->isKernelFunc(*func) || !pdgutils::hasReadAccess(*addrVar))
                  continue;
              auto addrVarNode = _PDG->getNode(*addrVar);
              auto taintNodes = _PDG->findNodesReachedByEdges(*addrVarNode, taintEdges);
              for (auto taintNode : taintNodes)
              {
                  taintNode->setTaint();
                  auto taintVal = taintNode->getValue();
                  if (!taintVal)
                      continue;
                  if (auto taintInst = dyn_cast<Instruction>(taintVal))
                  {
                      auto taintNodeType = taintVal->getType();
                      // if a taint value is pointer, check if the pointer is used in ptr arith operations
                      if (taintNodeType->isPointerTy())
                      {
                          // check if ptr field has pointe arithmetic
                          if (!isStructPointerTy && !isArithPtrField && checkPtrValUsedInPtrArithOp(*taintNode))
                          // if (!isStructPointerTy && checkPtrValUsedInPtrArithOp(*taintNode))
                          {
                              if (taintNode == addrVarNode)
                                  continue;
                              isArithPtrField = true;
                              numPtrArithPtrFieldTaint++;
                              _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "ptr arith"));
                          }
                      }

                      // check if the pointer field is dereferenced
                      if (!isDerefPtrField && pdgutils::hasPtrDereference(*taintVal))
                      // if (pdgutils::hasPtrDereference(*taintVal))
                      {
                          if (taintNode == addrVarNode)
                              continue;
                          isDerefPtrField = true;
                          numDereferencePtrFieldTaint++;
                          classified = true;
                          _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "ptr deref"));
                      }

                      // check if a taint field control sensitive branchs
                      if (!isBranchPtrField && checkValUsedInSenBranchCond(*taintNode, *riskyFieldTaintOS))
                      // if (checkValUsedInSenBranchCond(*taintNode, *riskyFieldTaintOS))
                      {
                          isBranchPtrField = true;
                          numBranchPtrFieldTaint++;
                          classified = true;
                          _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "sensitive branch ptr"));
                      }

                      if (!isSensitiveOpPtrField && checkValUsedInSensitiveOperations(*taintNode))
                      // if (checkValUsedInSensitiveOperations(*taintNode))
                      {
                          isSensitiveOpPtrField = true;
                          numSensitiveOpPtrFieldTaint++;
                          classified = true;
                          _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "sensitive op ptr"));
                      }
                  }
              }
          }
      }
  }
  else
  {
      bool isArrayIdxField = false;
      bool isArithField = false;
      bool isBranchField = false;
      bool isUsedInSensitiveOp = false;
      for (auto addrVar : addrVars)
      {
          auto addrVarInst = cast<Instruction>(addrVar);
          auto func = addrVarInst->getFunction();
          if (!_SDA->isKernelFunc(*func) || !pdgutils::hasReadAccess(*addrVar))
              continue;
          auto addrVarNode = _PDG->getNode(*addrVar);
          auto taintNodes = _PDG->findNodesReachedByEdges(*addrVarNode, taintEdges);
          for (auto taintNode : taintNodes)
          {
              auto taintVal = taintNode->getValue();
              if (!taintVal)
                  continue;

              auto taintNodeType = taintVal->getType();
              if (auto taintInst = dyn_cast<Instruction>(taintVal))
              {
                  // check if a taint value is used as array index
                  if (!isArrayIdxField && checkValUsedAsArrayIndex(*taintNode))
                  // if (checkValUsedAsArrayIndex(*taintNode))
                  {
                      isArrayIdxField = true;
                      classified = true;
                      numArrayIdxFieldTaint++;
                      _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "array idx"));
                  }
                  if (!isArithField && checkValUsedInPtrArithOp(*taintNode))
                  // if (checkValUsedInPtrArithOp(*taintNode))
                  {
                      isArithField = true;
                      classified = true;
                      numArithFieldTaint++;
                      _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "arith op"));
                  }

                  // check if a taint value is used to control sensitive branches
                  if (!isBranchField && checkValUsedInSenBranchCond(*taintNode, *riskyFieldTaintOS))
                  // if (checkValUsedInSenBranchCond(*taintNode, *riskyFieldTaintOS))
                  {
                      isBranchField = true;
                      classified = true;
                      numSensitiveBranchFieldTaint++;
                      _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "sensitive branch"));
                  }
                  // check if a taint value is used in sensitive operations
                  if (!isUsedInSensitiveOp && checkValUsedInSensitiveOperations(*taintNode))
                  // if (checkValUsedInSensitiveOperations(*taintNode))
                  {
                      isUsedInSensitiveOp = true;
                      classified = true;
                      numSensitiveOpsFieldTaint++;
                      _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "sensitive op"));
                  }
              }
          }
      }
  }

  // if a node is not classified into any category, print the kernel locations that read the field
  if (!classified)
  {
      numUnclassifiedFieldTaint++;
  }
  //     std::string funcAttr = "";
  //     if (dbgutils::isFuncPointerType(*fieldDIType))
  //     {
  //         funcAttr = " (fptr) ";
  //         numUnclassifiedFuncPtrFieldTaint++;
  //     }
  //     numUnclassifiedFieldTaint++;
  //     *riskyFieldTaintOS << "Unclassified field (taint): " << funcAttr << colorize(accessPathStr, RED) << "\n";
  //     for (auto addrVar : addrVars)
  //     {
  //         if (auto inst = dyn_cast<Instruction>(addrVar))
  //         {
  //             auto f = inst->getFunction();
  //             if (_SDA->isKernelFunc(*f))
  //             {
  //                 pdgutils::printSourceLocation(*inst, *riskyFieldOS);
  //             }
  //         }
  //     }

  //     *riskyFieldTaintOS << "--------- [End of Case] --------- \n\n";
  // }
}

bool pdg::RiskyFieldAnalysis::checkValUsedAsArrayIndex(Node &n)
{
  auto taintVal = n.getValue();
  if (!taintVal)
      return false;
  for (User *U : taintVal->users())
  {
      if (GetElementPtrInst *GEP = dyn_cast<llvm::GetElementPtrInst>(U))
      {
          // skip gep on struct types
          auto ptrOperand = GEP->getPointerOperand();
          auto ptrOpNode = _PDG->getNode(*ptrOperand);
          if (!ptrOpNode || !ptrOperand)
              continue;
          if (ptrOpNode->getDIType() && dbgutils::isStructPointerType(*ptrOpNode->getDIType()))
              continue;
          if (pdgutils::isStructPointerType(*ptrOperand->getType()))
              continue;
          // Check if taint value is used as an index in the GEP instruction
          for (auto IdxOp = GEP->idx_begin(), E = GEP->idx_end(); IdxOp != E; ++IdxOp)
              if (IdxOp->get() == taintVal)
                  return true;
      }
  }
  return false;
}

bool pdg::RiskyFieldAnalysis::checkIsArrayAccess(Instruction &inst)
{
  if (GetElementPtrInst *gep = dyn_cast<llvm::GetElementPtrInst>(&inst))
  {
      // skip gep on struct types
      // auto ptrOperand = gep->getPointerOperand();
      // auto ptrOpNode = _PDG->getNode(*ptrOperand);
      // if (!ptrOpNode || !ptrOperand)
      //     return false;
      // if ((ptrOpNode->getDIType() && dbgutils::isStructPointerType(*ptrOpNode->getDIType())) || pdgutils::isStructPointerType(*ptrOperand->getType()))
      //     return false;
      // Check if taint value is used as an index in the GEP instruction
      return true;
  }
  // This is not an array access
  return false;
}

bool pdg::RiskyFieldAnalysis::checkValUsedInSenBranchCond(Node &n, raw_fd_ostream &OS)
{
  auto taintVal = n.getValue();
  if (!taintVal)
      return false;
  for (auto user : taintVal->users())
  {
      if (auto li = dyn_cast<LoadInst>(user))
      {
          // check if the loaded value is used in branch
          for (auto u : li->users())
          {
              if (isa<BranchInst>(u) || isa<SwitchInst>(u))
              {
                  auto branchNode = _PDG->getNode(*u);
                  auto branchControlDependentNodes = _PDG->findNodesReachedByEdge(*branchNode, EdgeType::CONTROL);
                  for (auto ctrDepNode : branchControlDependentNodes)
                  {
                      auto depNodeVal = ctrDepNode->getValue();
                      // check for sensitive API calls
                      if (CallInst *ci = dyn_cast<CallInst>(depNodeVal))
                      {
                          auto calledFunc = pdgutils::getCalledFunc(*ci);
                          if (!calledFunc)
                              continue;
                          // some sensitive operations such as BUG() is translated
                          // to inline assembly
                          if (ci->isInlineAsm())
                          {
                              OS << "sen call ASM: " << *ci << "\n";
                              pdgutils::printSourceLocation(*ci, OS);
                              return true;
                          }
                          auto calledFuncName = calledFunc->getName().str();
                          for (auto op : sensitiveOperations)
                          {
                              if (calledFuncName.find(op) != std::string::npos)
                              {
                                  OS << "sen call: " << *ci << "\n";
                                  pdgutils::printSourceLocation(*ci, OS);
                                  return true;
                              }
                          }
                          // check if the call can reach sensitive operations
                          auto calledFuncNode = _callGraph->getNode(*calledFunc);
                          if (auto senOpFunc = canReachSensitiveOperations(*calledFuncNode))
                          {
                              OS << "sen call trans: " << *ci << "\n";
                              OS << "sen op: " << senOpFunc->getName() << "\n";
                              pdgutils::printSourceLocation(*ci, OS);
                              return true;
                          }
                      }

                      // check for array access
                      if (Instruction *i = dyn_cast<Instruction>(depNodeVal))
                      {
                          if (checkIsArrayAccess(*i))
                          {
                              OS << "arrary access in branch: ";
                              pdgutils::printSourceLocation(*i, OS);
                              return true;
                          }
                      }
                  }

                  // return true;
              }
          }
      }
      else if (auto cmpInst = dyn_cast<CmpInst>(user))
      {
          for (auto u : cmpInst->users())
          {
              if (isa<BranchInst>(u) || isa<SwitchInst>(u))
              {
                  auto branchNode = _PDG->getNode(*u);
                  auto branchControlDependentNodes = _PDG->findNodesReachedByEdge(*branchNode, EdgeType::CONTROL);
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
                              OS << "sen call ASM: " << *ci << "\n";
                              pdgutils::printSourceLocation(*ci, OS);
                              return true;
                          }
                          auto calledFuncName = calledFunc->getName().str();
                          for (auto op : sensitiveOperations)
                          {
                              if (calledFuncName.find(op) != std::string::npos)
                              {
                                  OS << "sen call: " << *ci << "\n";
                                  OS << "senstive op: " << op << "\n";
                                  pdgutils::printSourceLocation(*ci, OS);
                                  return true;
                              }
                          }
                          // check if the call can reach sensitive operations
                          auto calledFuncNode = _callGraph->getNode(*calledFunc);
                          if (auto senOpFunc = canReachSensitiveOperations(*calledFuncNode))
                          {
                              OS << "sen call trans: " << *ci << "\n";
                              OS << "sen op: " << senOpFunc->getName() << "\n";
                              pdgutils::printSourceLocation(*ci, OS);
                              // print path
                              std::vector<Node *> callPath;
                              std::unordered_set<Node *> visited;
                              auto curFuncNode = _callGraph->getNode(*ci->getFunction());
                              _callGraph->findPathDFS(curFuncNode, calledFuncNode, callPath, visited);
                              _callGraph->printPath(callPath, OS);
                              return true;
                          }
                      }
                      // check for array access
                      if (Instruction *i = dyn_cast<Instruction>(depNodeVal))
                      {
                          errs() << "dep val: " << *i << "\n";
                          if (checkIsArrayAccess(*i))
                          {
                              OS << "arrary access in branch: ";
                              pdgutils::printSourceLocation(*i, OS);
                              return true;
                          }
                      }
                  }
              }
          }
      }
  }
  return false;
}

bool pdg::RiskyFieldAnalysis::checkPtrValUsedInPtrArithOp(Node &n)
{
  auto nodeVal = n.getValue();
  if (!nodeVal || !nodeVal->getType()->isPointerTy())
      return false;

  for (auto user : nodeVal->users())
  {
      if (auto gep = dyn_cast<GetElementPtrInst>(user))
      {
          auto gepPtrOp = gep->getPointerOperand();
          auto gepPtrTy = gep->getType();
          // check if the the ptr arith is result from a field access, if so, skip
          if (pdgutils::isStructPointerType(*gepPtrTy))
              continue;
          else
          {
              // only if the pointer is used to derive other pointers
              if (gepPtrOp == nodeVal)
                  return true;
          }
      }

      if (isa<OverflowingBinaryOperator>(user))
          return true;

      if (isa<PtrToIntInst>(user))
      {
          for (auto ptrToInstUser : user->users())
          {
              if (isa<OverflowingBinaryOperator>(ptrToInstUser))
                  return true;
          }
      }
  }
  return false;
}

// check if a taint value is used as a buffer
bool pdg::RiskyFieldAnalysis::checkValUsedInPtrArithOp(Node &n)
{
  auto nodeVal = n.getValue();
  if (!nodeVal)
      return false;
  for (User *U : nodeVal->users())
  {
      if (auto gep = dyn_cast<GetElementPtrInst>(U))
      {
          auto gepPtrOp = gep->getPointerOperand();
          auto gepPtrTy = gepPtrOp->getType();
          // check if the the ptr arith is result from a field access, if so, skip
          if (pdgutils::isStructPointerType(*gepPtrTy))
              continue;
          else
              return true;
      }
      // add, mul, sub etc
      if (isa<OverflowingBinaryOperator>(U))
          return true;
  }
  return false;
}

bool pdg::RiskyFieldAnalysis::checkValUsedInSensitiveOperations(Node &n)
{
  auto taintVal = n.getValue();
  if (!taintVal)
      return false;
  for (User *U : taintVal->users())
  {
      if (CallInst *ci = dyn_cast<CallInst>(U))
      {
          auto calledFunc = pdgutils::getCalledFunc(*ci);
          if (!calledFunc)
              continue;
          auto calledFuncName = calledFunc->getName().str();
          for (auto op : sensitiveOperations)
          {
              if (calledFuncName.find(op) != std::string::npos)
                  return true;
          }
      }
  }
  return false;
}

bool pdg::RiskyFieldAnalysis::isSensitiveOperation(Function &F)
{
  auto funcName = F.getName().str();
  for (auto op : sensitiveOperations)
  {
      if (funcName.find(op) != std::string::npos)
          return true;
  }
  return false;
}

Function *pdg::RiskyFieldAnalysis::canReachSensitiveOperations(Node &srcFuncNode)
{
  for (auto senOpFuncName : sensitiveOperations)
  {
      auto func = _module->getFunction(StringRef(senOpFuncName));
      if (!func)
          continue;

      auto funcNode = _callGraph->getNode(*func);
      if (!funcNode)
          continue;
      if (_callGraph->canReach(srcFuncNode, *funcNode))
          return func;
  }
  return nullptr;
}

void pdg::RiskyFieldAnalysis::printTaintFieldInfo()
{
  for (auto tuple : _taintTuples)
  {
      auto srcNode = std::get<0>(tuple);
      auto dstNode = std::get<1>(tuple);
      auto accessPathStr = std::get<2>(tuple);
      auto riskyFieldStr = std::get<3>(tuple);
      printTaintTraceAndConditions(*srcNode, *dstNode, accessPathStr, riskyFieldStr);
  }
}

// helper and print functions
void pdg::RiskyFieldAnalysis::printTaintTraceAndConditions(Node &srcNode, Node &dstNode, std::string accessPathStr, std::string taintType)
{
  // first, use cfg to analyze conditions and verify the riksy operation is reachable
  auto &cfg = KSplitCFG::getInstance();
  if (!cfg.isBuild())
    cfg.build(*_module);

  auto addrVarInst = cast<Instruction>(srcNode.getValue());
  auto taintInst = cast<Instruction>(dstNode.getValue());

  // obtain path conditions
  auto cfgAddrVarNode = cfg.getNode(*addrVarInst);
  auto cfgTaintVarNode = cfg.getNode(*taintInst);
  std::set<Value *> conditionVals;
  cfg.computePathConditionsBetweenNodes(*cfgAddrVarNode, *cfgTaintVarNode, conditionVals);
  *riskyFieldTaintOS << " ----------------------------------- \n";
  *riskyFieldTaintOS << " conditions along path: \n";

  bool isControlledPath = true;
  // check if path conditions are all tainted, which indicates a feasible path
  for (auto v : conditionVals)
  {
      if (!isControlledPath)
          break;
      if (auto inst = dyn_cast<Instruction>(v))
      {
          for (unsigned i = 0, e = inst->getNumOperands(); i != e; ++i)
          {
              llvm::Value *operand = inst->getOperand(i);
              auto opNode = _PDG->getNode(*operand);
              if (!opNode)
                  break;
              if (!opNode->isTaint())
              {
                  isControlledPath = false;
                  break;
              }
              // if a condition is sanity check of the sink value, which is used in risky operations
              // skip this trace
              // check if an operand of the conditions is the taint value.
              // if (isSanityCheck())
          }

          *riskyFieldTaintOS << *inst;
          pdgutils::printSourceLocation(*inst, *riskyFieldTaintOS);
      }
  }

  if (!isControlledPath)
  {
      *riskyFieldTaintOS << "--------- [End of Case] --------- \n\n";
      return;
  }

  numControlTaintTrace++;
  // if all the conditions are tainted, we proceed to compute the taints
  *riskyFieldTaintOS << "Risky " << taintType << " (ptr|taint) " << colorize(accessPathStr, RED) << ":\n";
  *riskyFieldTaintOS << "\ttaint source: ";
  pdgutils::printSourceLocation(*addrVarInst, *riskyFieldTaintOS);
  *riskyFieldTaintOS << "\ttaint sink: ";
  pdgutils::printSourceLocation(*taintInst, *riskyFieldTaintOS);
  printTaintTrace(*addrVarInst, *taintInst, accessPathStr, taintType, *riskyFieldTaintOS);
  auto n = srcNode.getAbstractTreeNode();

  if (n == nullptr)
  {
      n = srcNode.getAbstractTypeTreeNode();
      if (n == nullptr)
      {
          *riskyFieldTaintOS << "--------- [End of Case] --------- \n\n";
          return;
      }
  }

  if (TreeNode *tn = static_cast<TreeNode *>(n))
      _SDA->printDriverUpdateLocations(*tn, *riskyFieldTaintOS);

  *riskyFieldTaintOS << " taint trace: \n";
  std::vector<std::pair<Node *, Edge *>> path;
  std::unordered_set<Node *> visited;
  _PDG->findPathDFS(&srcNode, &dstNode, path, visited, taintEdges);
  _PDG->printPath(path, *riskyFieldTaintOS);

  *riskyFieldTaintOS << "--------- [End of Case] --------- \n\n";
}

void pdg::RiskyFieldAnalysis::printRiskyFieldInfo(raw_ostream &os, const std::string &category, pdg::TreeNode &treeNode, Function &func, Instruction &inst)
{
  os.changeColor(raw_ostream::RED);
  os << "--- [" << category << "] --- ";
  os.resetColor();
  os << treeNode.getSrcHierarchyName(false) << " in func " << func.getName() << "\n";
  pdg::pdgutils::printSourceLocation(inst);
}

void pdg::RiskyFieldAnalysis::printTaintTrace(Instruction &source, Instruction &sink, std::string fieldHierarchyName, std::string flowType, raw_fd_ostream &OS)
{
  auto sourceFunc = source.getFunction();
  auto sourceFuncNode = _callGraph->getNode(*sourceFunc);
  auto sinkFunc = sink.getFunction();
  auto sinkFuncNode = _callGraph->getNode(*sinkFunc);

  auto sourceFuncCallInsts = _callGraph->getCallInstsForFunc(*sourceFunc);
  OS << "Driver call loc: ========================================== \n ";
  unsigned numDriverCall = 0;
  for (auto srcCi : sourceFuncCallInsts)
  {
      // skip header files
      if (pdgutils::isUpdatedInHeader(*srcCi))
          continue;

      auto srcCiFunc = srcCi->getFunction();
      if (_SDA->isDriverFunc(*srcCiFunc))
      {
          numDriverCall++;
          OS << "\t" << srcCiFunc->getName().str() << " | ";
          pdgutils::printSourceLocation(*srcCi, OS);
      }
  }

  if (numDriverCall == 0)
      OS << "empty driver call Locs\n";

  OS << "(field: " << fieldHierarchyName << ")"
     << "\n";
  OS << "flow type: " << flowType << "\n";
  OS << "source inst: " << source << " in func " << sourceFunc->getName() << "\n";
  OS << "sink inst: " << sink << " in func " << sinkFunc->getName() << "\n";
  std::vector<Node *> callPath;
  std::unordered_set<Node *> visited;
  _callGraph->findPathDFS(sourceFuncNode, sinkFuncNode, callPath, visited);
  // consider taint if it propagates through return value
  if (callPath.empty())
  {
      visited.clear();
      _callGraph->findPathDFS(sinkFuncNode, sourceFuncNode, callPath, visited);
  }
  _callGraph->printPath(callPath, OS);
  OS << "<=========================================>\n";
}

void pdg::RiskyFieldAnalysis::printFieldDirectUseClassification(raw_fd_ostream &OS)
{
  OS << "\t\t Number of pointer arithmetic pointer fields: " << numPtrArithPtrField << "\n";
  OS << "\t\t Number of dereference pointer fields: " << numDereferencePtrField << "\n";
  OS << "\t\t Number of sensitive operation pointer fields: " << numSensitiveOpPtrField << "\n";
  OS << "\t\t Number of branch pointer fields: " << numBranchPtrField << "\n";
  OS << "Number of array index fields: " << numArrayIdxField << "\n";
  OS << "Number of sensitive branch fields: " << numSensitiveBranchField << "\n";
  OS << "Number of sensitive operation fields: " << numSensitiveOpsField << "\n";
  OS << "Number of unclassified fields: " << numUnclassifiedField << "\n";
  OS << "Number of unclassified func ptr fields: " << numUnclassifiedFuncPtrField << "\n";
  OS << " <==================================================>\n";
}

void pdg::RiskyFieldAnalysis::printFieldClassificationTaint(raw_fd_ostream &OS)
{
  OS << "Number of kernel read driver updated fields: " << numKernelReadDriverUpdatedFields << "\n";
  OS << "Number of pointer fields: " << numPtrField << "\n";
  OS << "\tNumber of function pointer fields: " << numFuncPtrField << "\n";
  OS << "\tNumber of data pointer fields: " << numDataPtrField << "\n";
  OS << "\t\tNo.pointer arithmetic pointer fields (Taint): " << numPtrArithPtrFieldTaint << "\n";
  OS << "\t\tNo.dereference pointer fields (Taint): " << numDereferencePtrFieldTaint << "\n";
  OS << "\t\tNo.sensitive operation pointer fields (Taint): " << numSensitiveOpPtrFieldTaint << "\n";
  OS << "\t\tNo.branch pointer fields (Taint): " << numBranchPtrFieldTaint << "\n";
  OS << "No.array index fields (Taint): " << numArrayIdxFieldTaint << "\n";
  OS << "No.arith op fields (Taint): " << numArithFieldTaint << "\n";
  OS << "No.sensitive branch fields (Taint): " << numSensitiveBranchFieldTaint << "\n";
  OS << "No.sensitive operation fields (Taint): " << numSensitiveOpsFieldTaint << "\n";
  OS << "No.unclassified fields (Taint): " << numUnclassifiedFieldTaint << "\n";
  OS << "No.unclassified func ptr fields (Taint): " << numUnclassifiedFuncPtrFieldTaint << "\n";
  OS << "No.kernel API params: " << numKernelAPIParam << "\n";
  OS << "No.control taint trace: " << numControlTaintTrace << "\n";
}

static RegisterPass<pdg::RiskyFieldAnalysis>
    RiskyFieldAnalysis("risky-field", "Risky Field Analysis", false, true);