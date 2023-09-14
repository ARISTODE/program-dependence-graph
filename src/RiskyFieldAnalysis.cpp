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

std::set<Function *> readFuncsFromFile(std::string fileName, Module &M, std::string dir)
{
    std::set<Function *> ret;
    sys::fs::file_status status;
    sys::fs::status("boundaryFiles", status);
    if (!dir.empty() && !sys::fs::exists(status) || !sys::fs::is_directory(status))
    {
        errs() << "boundary files don't exist, please run boundary analysis pass (-output-boundary-info) first\n";
        return ret;
    }

    std::string filePath = dir + "/" + fileName;
    std::ifstream ReadFile(filePath);
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

          for (auto childNode : n->getChildNodes())
          {
              nodeQueue.push(childNode);
          }
          // classify the risky field into different classes
          if (isDriverControlledField(*n))
          {
              numKernelReadDriverUpdatedFields++;
              // classifyRiskyFieldDirectUse(*n);
              classifyRiskyFieldTaint(*n);
          }
      }
  }

  // TODO: taint the return value of driver interface functions
  // classify the taint based on the data directly passed across the isolation boundary
  auto kernelAPIs = readFuncsFromFile("imported_funcs", M, "boundaryFiles");
  for (auto func : kernelAPIs)
  {
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
    // if (driverWriteTimes > 0 && kernelReadTimes > 0)
    if (driverWriteTimes > 0 || driverReadTimes > 0 && kernelReadTimes > 0 || kernelWriteTimes > 0)
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
                      std::string senOpName = "";
                      if (!isSensitiveOpPtrField && checkValUsedInSensitiveOperations(*addrVarNode, senOpName))
                      {
                          isSensitiveOpPtrField = true;
                          numSensitiveOpPtrField++;
                          *riskyFieldOS << "Risky sensitive op (ptr) " << colorize(accessPathStr, YELLOW) << ":\n";
                          pdgutils::printSourceLocation(*i, *riskyFieldOS);
                          *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
                          *riskyFieldOS << "\n";
                      }
                      // 4. check if used in branch that contain sensitive operations
                      std::string senTypeStr = "";
                      if (!isBranchPtrField && checkValUsedInSenBranchCond(*addrVarNode, *riskyFieldOS, senTypeStr))
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

                  std::string senTypeStr = "";
                  if (!isBranchField && checkValUsedInSenBranchCond(*addrVarNode, *riskyFieldOS, senTypeStr))
                  {
                      isBranchField = true;
                      numSensitiveBranchField++;
                      *riskyFieldOS << "Risky branch " << colorize(accessPathStr, RED) << ":\n";
                      pdgutils::printSourceLocation(*i, *riskyFieldOS);
                      *riskyFieldOS << " --------------------- [End of Case] -------------------------\n";
                      *riskyFieldOS << "\n";
                  }

                std::string senOpName = "";
                  if (!isUsedInSensitiveOp && checkValUsedInSensitiveOperations(*addrVarNode, senOpName))
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
  std::string accessPathStr = tn.getSrcHierarchyName(false);
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
      bool isUsedInAsm = false;
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
                      std::string senTypeStr = "";
                      if (!isBranchPtrField && checkValUsedInSenBranchCond(*taintNode, *riskyFieldTaintOS, senTypeStr))
                      // if (checkValUsedInSenBranchCond(*taintNode, *riskyFieldTaintOS))
                      {
                          isBranchPtrField = true;
                          numBranchPtrFieldTaint++;
                          classified = true;
                          std::string taintTypeStr = "sensitive branch ptr " + senTypeStr;
                          _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, taintTypeStr));
                      }

                      std::string senOpName = "";
                      if (!isSensitiveOpPtrField && checkValUsedInSensitiveOperations(*taintNode, senOpName))
                      // if (checkValUsedInSensitiveOperations(*taintNode))
                      {
                          isSensitiveOpPtrField = true;
                          numSensitiveOpPtrFieldTaint++;
                          classified = true;
                          _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "sensitive op ptr " + senOpName));
                      }

                      if (!isUsedInAsm && checkValUsedInInlineAsm(*taintNode))
                      {
                        isUsedInAsm = true;
                        numSensitiveOpPtrFieldTaint++;
                        classified = true;
                        _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "inline Asm Ptr"));
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
      bool isUsedInAsm = false;
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
              taintNode->setTaint();

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
                  std::string senTypeStr = "";
                  if (!isBranchField && checkValUsedInSenBranchCond(*taintNode, *riskyFieldTaintOS, senTypeStr))
                  // if (checkValUsedInSenBranchCond(*taintNode, *riskyFieldTaintOS))
                  {
                      isBranchField = true;
                      classified = true;
                      numSensitiveBranchFieldTaint++;
                      std::string taintTypeStr = "sensitive branch " + senTypeStr;
                      _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, taintTypeStr));
                  }
                  // check if a taint value is used in sensitive operations
                  std::string senOpName = "";
                  if (!isUsedInSensitiveOp && checkValUsedInSensitiveOperations(*taintNode, senOpName))
                  // if (checkValUsedInSensitiveOperations(*taintNode))
                  {
                      isUsedInSensitiveOp = true;
                      classified = true;
                      numSensitiveOpsFieldTaint++;
                      _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "sensitive op " + senOpName));
                  }

                  if (!isUsedInAsm && checkValUsedInInlineAsm(*taintNode))
                  {
                      isUsedInAsm = true;
                      numSensitiveOpPtrFieldTaint++;
                      classified = true;
                      _taintTuples.insert(std::make_tuple(addrVarNode, taintNode, accessPathStr, "inline Asm"));
                  }
              }
          }
      }
  }

  // if a node is not classified into any category, print the kernel locations that read the field
  if (!classified)
  {
      numUnclassifiedFieldTaint++;
      nlohmann::ordered_json unclassifiedFieldJson;
      unclassifiedFieldJson["id"] = unclassifiedFieldCount;
      unclassifiedFieldCount++;
      unclassifiedFieldJson["field"] = accessPathStr;
      std::string readLocs = "";
      std::string updateLocs = "";
      for (auto addrVar : addrVars)
      {
          if (auto inst = dyn_cast<Instruction>(addrVar))
          {
              auto f = inst->getFunction();
              // record driver update locations
              if (_SDA->isDriverFunc(*f) && pdgutils::hasWriteAccess(*inst))
              {
                  std::string drvUpdateLoc = pdgutils::getSourceLocationStr(*inst);
                  updateLocs = updateLocs + " [" + drvUpdateLoc + "], ";
              }

              // record kernel read locations
              if (!_SDA->isDriverFunc(*f) && pdgutils::hasReadAccess(*inst))
              {
                  std::string kernelReadLoc = pdgutils::getSourceLocationStr(*inst);
                  readLocs = readLocs + " [" + kernelReadLoc + "], ";
              }
          }
      }

      if (tn.isRootNode())
      {
        // for root node (param), record the function name and location
        auto func = tn.getTree()->getFunc();
        auto DISubprog = func->getSubprogram();
        unsigned line = DISubprog->getLine();
        std::string file = DISubprog->getFilename().str();
        std::string filePrefix = "https://gitlab.flux.utah.edu/xcap/xcap-capability-linux/-/blob/llvm_v4.8/";
        readLocs = filePrefix + file + "#L" + std::to_string(line) + " | " + func->getName().str();
      }

      unclassifiedFieldJson["Kernel read"] = readLocs;
      unclassifiedFieldJson["Drv update"] = updateLocs;
      unclassifiedFieldsJson.push_back(unclassifiedFieldJson);
  }
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
      auto ptrOperand = gep->getPointerOperand();
      auto ptrOpNode = _PDG->getNode(*ptrOperand);
      if (!ptrOpNode || !ptrOperand)
          return false;
      if ((ptrOpNode->getDIType() && dbgutils::isStructPointerType(*ptrOpNode->getDIType())) || pdgutils::isStructPointerType(*ptrOperand->getType()))
          return false;
      // Check if taint value is used as an index in the GEP instruction
      return true;
  }
  // This is not an array access
  return false;
}

bool pdg::RiskyFieldAnalysis::checkValUsedInSenBranchCond(Node &n, raw_fd_ostream &OS, std::string &senTypeStr)
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
                              OS << "array access in branch: ";
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
                              senTypeStr = "inline asm";
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
                                  senTypeStr = "sen op";
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
                              senTypeStr = "trans sen op";
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
                    //   if (Instruction *i = dyn_cast<Instruction>(depNodeVal))
                    //   {
                    //       if (checkIsArrayAccess(*i))
                    //       {
                    //           OS << "arrary access in branch: ";
                    //           senTypeStr = "array access";
                    //           pdgutils::printSourceLocation(*i, OS);
                    //           return true;
                    //       }
                    //   }
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

bool pdg::RiskyFieldAnalysis::checkValUsedInInlineAsm(Node &n)
{
    auto taintVal = n.getValue();
    if (!taintVal)
        return false;
    for (User *U : taintVal->users())
    {
        if (CallInst *ci = dyn_cast<CallInst>(U))
        {
            if (ci->isInlineAsm())
                return true;
        }
    }
    return false;
}

bool pdg::RiskyFieldAnalysis::checkValUsedInSensitiveOperations(Node &n, std::string &senOpName)
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
              {
                  senOpName = op;
                  return true;
              }
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
    unsigned caseId = 0;
    for (auto tuple : _taintTuples)
    {
        auto srcNode = std::get<0>(tuple);
        auto dstNode = std::get<1>(tuple);
        auto accessPathStr = std::get<2>(tuple);
        auto riskyFieldStr = std::get<3>(tuple);
        printTaintTraceAndConditions(*srcNode, *dstNode, accessPathStr, riskyFieldStr, caseId);
        caseId++;
    }
    
    // create and output log files
    SmallString<128> dirPath("logs");
    if (!sys::fs::exists(dirPath))
    {
        std::error_code EC = sys::fs::create_directory(dirPath, true, sys::fs::perms::all_all);
        if (EC)
        {
            std::cerr << "Error: Failed to create directory. " << EC.message() << "\n";
        }
    }

    SmallString<128> jsonTraceCondFilePath = dirPath;
    sys::path::append(jsonTraceCondFilePath, "traceCond.json");

    std::ofstream jsonTraceCondFile(jsonTraceCondFilePath.c_str());
    if (!jsonTraceCondFile.is_open()) {
        std::cerr << "Error: Failed to open json trace file.\n";
    }
    jsonTraceCondFile << taintTracesJson.dump(2);
    jsonTraceCondFile.close();

    SmallString<128> jsonTraceNoCondFilePath = dirPath;
    sys::path::append(jsonTraceNoCondFilePath, "traceNoCond.json");
    std::ofstream jsonTraceNoCondFile(jsonTraceNoCondFilePath.c_str());
    if (!jsonTraceNoCondFile.is_open()) {
        std::cerr << "Error: Failed to open json no cond trace file.\n";
    }
    jsonTraceNoCondFile << taintTracesJsonNoConds.dump(2);
    jsonTraceNoCondFile.close();

    errs() << "dumping unclassified fields\n";
    SmallString<128> jsonUnclassifiedFieldFilePath = dirPath;
    sys::path::append(jsonUnclassifiedFieldFilePath , "unclassifiedFields.json");
    std::ofstream jsonTraceUnclassified(jsonUnclassifiedFieldFilePath.c_str());
    if (!jsonTraceUnclassified.is_open()) {
        std::cerr << "Error: Failed to open json unclassified trace file.\n";
    }
    jsonTraceUnclassified << unclassifiedFieldsJson.dump(2);
    jsonTraceUnclassified.close();
}

// helper and print functions
void pdg::RiskyFieldAnalysis::printTaintTraceAndConditions(Node &srcNode, Node &dstNode, std::string accessPathStr, std::string taintType, unsigned caseId)
{
    // first, use cfg to analyze conditions and verify the riksy operation is reachable
    auto &cfg = KSplitCFG::getInstance();
    if (!cfg.isBuild())
        cfg.build(*_module);

    auto addrVarInst = cast<Instruction>(srcNode.getValue());
    auto taintInst = cast<Instruction>(dstNode.getValue());

    // create json object for storing traces
    nlohmann::ordered_json traceJsonObj;
    traceJsonObj["id"] = std::to_string(caseId);
    traceJsonObj["risky"] = taintType;
    traceJsonObj["acc_path"] = accessPathStr;
    traceJsonObj["src"] = pdgutils::getSourceLocationStr(*addrVarInst);
    traceJsonObj["dst"] = pdgutils::getSourceLocationStr(*taintInst);

    // compute the call chain from boundary to the target function
    std::string callPathStr = "";
    auto targetFunc = taintInst->getFunction();
    auto targetFuncNode = _callGraph->getNode(*targetFunc);

    std::string callPaths = "";
    for (auto boundaryFunc : _SDA->getBoundaryFuncs())
    {
        if (_SDA->isDriverFunc(*boundaryFunc))
            continue;
        auto boundaryFuncNode = _callGraph->getNode(*boundaryFunc);
        std::vector<Node *> path;
        std::unordered_set<Node *> visited;
        if (_callGraph->findPathDFS(boundaryFuncNode, targetFuncNode, path, visited))
        {
            for (size_t i = 0; i < path.size(); ++i)
            {
                Node *node = path[i];

                // Print the node's function name
                if (Function *f = dyn_cast<Function>(node->getValue()))
                    callPathStr = callPathStr + f->getName().str();

                if (i < path.size() - 1)
                    callPathStr = callPathStr + "->";
            }

            // here, we only consider one valid path
            if (!callPathStr.empty())
            {
                callPaths = callPaths + " [" + callPathStr + "] ";
                break;
            }
        }
    }
    traceJsonObj["call path"] = callPaths;

    // obtain path conditions
    auto cfgAddrVarNode = cfg.getNode(*addrVarInst);
    auto cfgTaintVarNode = cfg.getNode(*taintInst);
    std::set<Value *> conditionVals;
    cfg.computePathConditionsBetweenNodes(*cfgAddrVarNode, *cfgTaintVarNode, conditionVals);
    traceJsonObj["cond_num"] = std::to_string(conditionVals.size());

    bool isControlledPath = true;
    // check if path conditions are all tainted, which indicates a feasible path
    for (auto v : conditionVals)
    {
        if (!isControlledPath)
            break;
        bool isCurBranchTaint = false;
        auto condInstNode = _PDG->getNode(*v);

        if (!condInstNode)
            continue;
        
        // check if condition is tainted
        if (!condInstNode->isTaint())
        {
            isControlledPath = false;
            break;
        }
    }


    if (!isControlledPath)
    {
        traceJsonObj["isControl"] = "0";
        taintTracesJsonNoConds.push_back(traceJsonObj);
        return;
    }
    else
        traceJsonObj["isControl"] = "1";

    numControlTaintTrace++;
    // if all the conditions are tainted, we proceed to compute the taints
    auto parameterTreeNode = srcNode.getAbstractTreeNode();
    auto typeTreeNode = srcNode.getAbstractTypeTreeNode();

    if (!parameterTreeNode && !typeTreeNode)
    {
        return;
    }

    // if the source node is a parameter
    if (parameterTreeNode)
    {
        if (TreeNode *tn = static_cast<TreeNode *>(parameterTreeNode))
        {
            // print the call site of the function
            Function* kernelBoundaryFunc = tn->getTree()->getFunc();
            auto funcCallSites = _callGraph->getFunctionCallSites(*kernelBoundaryFunc);
            std::string drvCallerStr = "";
            for (CallInst *callsite : funcCallSites)
            {
                auto callerFunc = callsite->getFunction();
                if (callerFunc && _SDA->isDriverFunc(*callerFunc) && !pdgutils::isFuncDefinedInHeaderFile(*callerFunc))
                {
                    std::string callSiteLocStr = pdgutils::getSourceLocationStr(*callsite);
                    std::string callLocStr = "[ " + callerFunc->getName().str() + " | " + callSiteLocStr + " ], ";
                    drvCallerStr = drvCallerStr + callLocStr;
                }
            }

            traceJsonObj["drv caller (param)"] = drvCallerStr;
        }
    }

    // add driver update locations for fields
    if (typeTreeNode)
    {
        if (TreeNode *tn = static_cast<TreeNode *>(typeTreeNode))
        {
            std::string drvUpdateLocStr = "";
            raw_string_ostream drvUpdateLocSS(drvUpdateLocStr);
            _SDA->getDriverUpdateLocStr(*tn, drvUpdateLocSS);
            drvUpdateLocSS.flush();
            traceJsonObj["drv_update loc (shared field)"] = drvUpdateLocSS.str();
        }
    }
    
    // add kernel read locations for shared fields, and check if the read can be reached from the boundary
    if (typeTreeNode)
    {
        if (TreeNode *tn = static_cast<TreeNode *>(typeTreeNode))
        {
        }
    }

    std::vector<std::pair<Node *, Edge *>> path;
    std::unordered_set<Node *> visited;
    _PDG->findPathDFS(&srcNode, &dstNode, path, visited, taintEdges);
    std::string taintTraceStr = "";
    raw_string_ostream ss(taintTraceStr);
    _PDG->convertPathToString(path, ss);
    ss.flush();
    traceJsonObj["t_trace"] = ss.str();

    traceJsonObj["isTrue"] = "-";
    traceJsonObj["atk_reason"] = "";
    traceJsonObj["defense"] = "";
    taintTracesJson.push_back(traceJsonObj);
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

    auto sourceFuncCallSites = _callGraph->getFunctionCallSites(*sourceFunc);
    OS << "Driver call loc: ========================================== \n ";
    unsigned numDriverCall = 0;
    for (auto srcCi : sourceFuncCallSites)
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

    //   OS << "(field: " << fieldHierarchyName << ")"
    //      << "\n";
    //   OS << "flow type: " << flowType << "\n";
    //   OS << "source inst: " << source << " in func " << sourceFunc->getName() << "\n";
    //   OS << "sink inst: " << sink << " in func " << sinkFunc->getName() << "\n";
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

void pdg::RiskyFieldAnalysis::getTraceStr(Instruction &source, Instruction &sink, std::string fieldHierarchyName, std::string flowType, raw_string_ostream &OS)
{
    auto sourceFunc = source.getFunction();
    auto sourceFuncNode = _callGraph->getNode(*sourceFunc);
    auto sinkFunc = sink.getFunction();
    auto sinkFuncNode = _callGraph->getNode(*sinkFunc);
    std::vector<Node *> callPath;
    std::unordered_set<Node *> visited;
    _callGraph->findPathDFS(sourceFuncNode, sinkFuncNode, callPath, visited);
    // consider taint if it propagates through return value
    if (callPath.empty())
    {
        visited.clear();
        _callGraph->findPathDFS(sinkFuncNode, sourceFuncNode, callPath, visited);
    }

    // for (auto node : callPath)
    // {
    //     std::string s = "";
    //     auto nodeVal = node->getValue();
    //     if (auto i = dyn_cast<Instruction>(nodeVal))
    //     {
    //         auto instLoc = pdgutils::getSourceLocationStr(*i);
    //         s += instLoc;
    //     }
    //     OS << path << "\n";
    // }
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