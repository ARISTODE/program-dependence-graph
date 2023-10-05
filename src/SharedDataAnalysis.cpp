#include "SharedDataAnalysis.hh"

char pdg::SharedDataAnalysis::ID = 0;

using namespace llvm;

void pdg::SharedDataAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<ProgramDependencyGraph>();
  AU.setPreservesAll();
}

bool pdg::SharedDataAnalysis::runOnModule(llvm::Module &M)
{
  _module = &M;
  _PDG = getAnalysis<ProgramDependencyGraph>().getPDG();
  _callGraph = &PDGCallGraph::getInstance();
  _ksplitStats = &KSplitStats::getInstance();
  fieldStatsFile.open("fieldAccessStats.csv");
  riskyPatternLog.open("riskyPatterns.txt");
  // read driver/kernel domian funcs
  setupStrOps();
  readSentinelFields();
  // insert driver global ops shared struct type
  readGlobalFuncOpStructNames();
  setupDriverFuncs(M);
  setupKernelFuncs(M);
  setupExportedFuncPtrFieldNames();
  // get boundary functions
  setupBoundaryFuncs(M);
  // compute struct type passed through boundary (shared struct type)
  readDriverGlobalStrucTypes();
  computeSharedStructDITypes();
  computeGlobalStructTypeNames();
  // build global tree for each struct type, connect with address variables
  buildTreesForSharedStructDIType(M);
  // generate shared field id
  computeSharedFieldID();
  // dumpSharedFieldID();
  _ksplitStats->printSoKClassifiedFields();
  errs() << "number of shared fields: " << _shared_field_id.size() << "\n";
  // computeSharedGlobalVars();
  if (!pdgutils::isFileExist("shared_struct_types"))
    dumpSharedTypes("shared_struct_types");
  // printPingPongCalls(M);
  // collect shared fields detail access stats
  fieldStatsFile.close();
  errs() << "Shared fields computation finished\n";
  return false;
}

void pdg::SharedDataAnalysis::setupStrOps()
{
  _string_op_names.insert("strcpy");
  _string_op_names.insert("strncpy");
  _string_op_names.insert("strlen");
  _string_op_names.insert("strlcpy");
  _string_op_names.insert("strcmp");
  _string_op_names.insert("strchr");
  _string_op_names.insert("strncmp");
  _string_op_names.insert("strpbrk");
  _string_op_names.insert("kobject_set_name");
}

void pdg::SharedDataAnalysis::setupExportedFuncPtrFieldNames()
{
  std::ifstream driverExportedFuncPtrNames("exported_func_ptrs");
  for (std::string line; std::getline(driverExportedFuncPtrNames, line);)
  {
    exportedFuncPtrFieldNames.insert(line);
  }
}

void pdg::SharedDataAnalysis::setupDriverFuncs(Module &M)
{
  _driverDomainFuncs = readFuncsFromFile("driver_funcs", M, "boundaryFiles");
}

void pdg::SharedDataAnalysis::readDriverGlobalStrucTypes()
{
  ifstream driver_global_struct_types("driver_global_struct_types");
  for (std::string line; std::getline(driver_global_struct_types, line);)
  {
    _driver_global_struct_types.insert(line);
  }
}

void pdg::SharedDataAnalysis::setupKernelFuncs(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    // a special case is that driver function has module number concatenated, e.g., ixgbe_write_reg.5
    // neet to exclude such functions
    std::string funcName = F.getName().str();
    // ixgbe_write_reg.5 -> ixgbe_write_reg
    funcName = pdgutils::stripFuncNameVersionNumber(funcName);
    auto func = M.getFunction(StringRef(funcName));
    if (func == nullptr)
      continue;
    if (_driverDomainFuncs.find(func) == _driverDomainFuncs.end())
    {
      _kernelDomainFuncs.insert(func);
      _kernel_domain_func_names.insert(func->getName().str());
    }
  }
}

void pdg::SharedDataAnalysis::setupBoundaryFuncs(Module &M)
{
  auto imported_funcs = readFuncsFromFile("imported_funcs", M, "boundaryFiles");
  auto exported_funcs = readFuncsFromFile("exported_funcs", M, "boundaryFiles");

  if (EnableAnalysisStats)
  {
    auto &ksplit_stats = KSplitStats::getInstance();
    ksplit_stats._kernel_to_driver_func_call += exported_funcs.size();
    ksplit_stats._driver_to_kernel_func_call += imported_funcs.size();
  }

  _boundary_funcs.insert(imported_funcs.begin(), imported_funcs.end());
  _boundary_funcs.insert(exported_funcs.begin(), exported_funcs.end());
  // module init functions
  Function *init_func = getModuleInitFunc(M);
  if (init_func != nullptr)
    _boundary_funcs.insert(init_func);

  for (auto bf : _boundary_funcs)
  {
    _boundary_func_names.insert(bf->getName().str());
  }
}

std::set<Function *> pdg::SharedDataAnalysis::readFuncsFromFile(std::string fileName, Module &M, std::string dir)
{
  std::set<Function *> ret;
  sys::fs::file_status status;
  sys::fs::status("boundaryFiles", status);
  if (!dir.empty() && !sys::fs::exists(status) || !sys::fs::is_directory(status))
  {
    errs() << "boundary files don't exist, please run boundary analysis pass (-output-boundary-info) first\n";
    return ret;
  }


  auto fullPath = dir + "/" + fileName;
  std::ifstream ReadFile(fullPath);
  for (std::string line; std::getline(ReadFile, line);)
  {
    Function *f = M.getFunction(StringRef(line));
    if (!f)
      continue;
    if (f->isDeclaration() || f->empty())
      continue;
    ret.insert(f);
  }
  return ret;
}

std::unordered_set<Function *> pdg::SharedDataAnalysis::computeBoundaryTransitiveClosure()
{
  std::unordered_set<Function *> boundary_trans_funcs;
  for (auto boundary_func : _boundary_funcs)
  {
    if (_callGraph->isExcludeFunc(*boundary_func))
    {
      errs() << "found exclude func " << boundary_func->getName() << "\n";
      continue;
    }
    auto func_node = _callGraph->getNode(*boundary_func);
    assert(func_node != nullptr && "cannot get function node for computing transitive closure!");
    auto trans_func_nodes = _callGraph->computeTransitiveClosure(*func_node);
    for (auto n : trans_func_nodes)
    {
      if (Function *trans_func = dyn_cast<Function>(n->getValue()))
        boundary_trans_funcs.insert(trans_func);
    }
  }
  return boundary_trans_funcs;
}
/*
Basically, we can both driver side and kernel side code. Then
compute the intersaction of struct types used by both sides.
*/
void pdg::SharedDataAnalysis::computeSharedStructDITypes()
{
  std::set<std::string> driver_struct_type_names;
  for (auto func : _driverDomainFuncs)
  {
    if (func->isDeclaration())
      continue;
    for (auto inst_i = inst_begin(func); inst_i != inst_end(func); inst_i++)
    {
      Node *n = _PDG->getNode(*inst_i);
      if (!n)
        continue;
      DIType *nodeDt = n->getDIType();
      if (StoreInst *si = dyn_cast<StoreInst>(&*inst_i))
      {
        auto val_op = si->getValueOperand()->stripPointerCasts();
        Node *val_n = _PDG->getNode(*val_op);
        if (!val_n)
          continue;
        nodeDt = val_n->getDIType();
      }
      if (!nodeDt)
        continue;
      DIType *lowest_di_type = dbgutils::getLowestDIType(*nodeDt);
      if (lowest_di_type == nullptr)
        continue;
      if (dbgutils::isStructType(*lowest_di_type))
      {
        std::string di_type_name = dbgutils::getSourceLevelTypeName(*lowest_di_type, true);
        if (!di_type_name.empty())
          driver_struct_type_names.insert(pdgutils::stripVersionTag(di_type_name));
      }
    }
  }
  // errs() << " === driver side struct types ===\n";
  // for (auto t : driver_struct_type_names)
  // {
  //   errs() << "\t" << t << "\n";
  // }
  std::set<std::string> processed_struct_names;
  for (auto func : _kernelDomainFuncs)
  {
    if (func->isDeclaration())
      continue;
    for (auto inst_i = inst_begin(func); inst_i != inst_end(func); inst_i++)
    {
      Node *n = _PDG->getNode(*inst_i);
      if (!n)
        continue;
      DIType *nodeDt = n->getDIType();
      if (!nodeDt)
        continue;
      if (dbgutils::isStructType(*nodeDt) || dbgutils::isStructPointerType(*nodeDt))
      {
        DIType *lowest_di_type = dbgutils::getLowestDIType(*nodeDt);
        assert(lowest_di_type != nullptr && "null lowest di type (computeSharedStructTypes)\n");
        std::string structTyName = dbgutils::getSourceLevelTypeName(*lowest_di_type, true);
        structTyName = pdgutils::stripVersionTag(structTyName);
        if (processed_struct_names.find(structTyName) != processed_struct_names.end())
          continue;
        processed_struct_names.insert(structTyName);
        // check if driver side has the same di type, if so, add the type as shared type accessed by both driver and kernel
        if (driver_struct_type_names.find(structTyName) != driver_struct_type_names.end())
          _shared_struct_di_types.insert(lowest_di_type);
      }
    }
  }

  // for parameters passed across isolation boundary, if it's a struct type, then we need to consider this type as
  // shared data type. However, this steps seems unecessary, because the above step should include all the shared data types
  // computed in this step.
  // for (auto f : _boundary_funcs)
  // {
  //   if (f->isDeclaration())
  //     continue;
  //   auto fw = _PDG->getFuncWrapper(*f);
  //   for (auto arg : fw->getArgList())
  //   {
  //     auto argDt = fw->getArgDIType(*arg);
  //     auto argLowestDt = dbgutils::getLowestDIType(*argDt);
  //     if (argLowestDt != nullptr)
  //     {
  //       if (dbgutils::isStructType(*argLowestDt))
  //         _shared_struct_di_types.insert(argLowestDt);
  //     }
  //   }

  //   auto ret_val_di_type = fw->getReturnValDIType();
  //   auto ret_val_lowest_di_type = dbgutils::getLowestDIType(*ret_val_di_type);
  //   if (ret_val_lowest_di_type != nullptr)
  //   {
  //     if (dbgutils::isStructType(*ret_val_lowest_di_type))
  //       _shared_struct_di_types.insert(ret_val_lowest_di_type);
  //   }
  // }
}

void pdg::SharedDataAnalysis::computeGlobalStructTypeNames()
{
  for (auto &global_var : _module->getGlobalList())
  {
    SmallVector<DIGlobalVariableExpression *, 4> sv;
    if (!global_var.hasInitializer())
      continue;
    DIGlobalVariable *di_gv = nullptr;
    global_var.getDebugInfo(sv);
    for (auto di_expr : sv)
    {
      if (di_expr->getVariable()->getName() == global_var.getName())
        di_gv = di_expr->getVariable(); // get global variable from global expression
    }
    if (di_gv == nullptr)
      continue;
    auto gv_di_type = di_gv->getType();
    if (gv_di_type == nullptr)
      continue;
    auto gv_lowest_di_type = dbgutils::getLowestDIType(*gv_di_type);
    if (gv_lowest_di_type == nullptr || gv_lowest_di_type->getTag() != dwarf::DW_TAG_structure_type)
      continue;
    _global_struct_di_type_names.insert("struct " + dbgutils::getSourceLevelTypeName(*gv_di_type, true));
  }
}

void pdg::SharedDataAnalysis::buildTreesForSharedStructDIType(Module &M)
{
  for (auto shared_struct_di_type : _shared_struct_di_types)
  {
    Tree *type_tree = new Tree();
    TreeNode *rootNode = new TreeNode(shared_struct_di_type, 0, nullptr, type_tree, GraphNodeType::GLOBAL_TYPE);
    std::string shared_struct_type_name = dbgutils::getSourceLevelTypeName(*shared_struct_di_type, true);
    if (!shared_struct_type_name.empty())
      _shared_struct_type_names.insert(shared_struct_type_name);
    // this finds all the variable (global/local) in the code that have the struct type.
    // we will analylze the accesses to these variables to determine shared fields.
    auto vars = computeVarsWithStructDITypeInModule(*shared_struct_di_type, M);
    for (auto var : vars)
    {
      rootNode->addAddrVar(*var);
    }
    type_tree->setRootNode(*rootNode);
    type_tree->build(2);
    connectTypeTreeToAddrVars(*type_tree);
    _global_struct_di_type_map.insert(std::make_pair(shared_struct_di_type, type_tree));
  }
}

void pdg::SharedDataAnalysis::connectTypeTreeToAddrVars(Tree &type_tree)
{
  TreeNode *rootNode = type_tree.getRootNode();
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);
  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    for (auto addrVar : currentNode->getAddrVars())
    {
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addrVarNode = _PDG->getNode(*addrVar);
      currentNode->addNeighbor(*addrVarNode, EdgeType::VAL_DEP);
    }
    for (auto childNode : currentNode->getChildNodes())
    {
      nodeQueue.push(childNode);
    }
  }
}

void pdg::SharedDataAnalysis::computeVarsWithStructDITypeInFunc(DIType &dt, Function &F, std::set<Value *> &vars)
{
  for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
  {
    Node *instNode = _PDG->getNode(*instIter);
    if (!instNode)
      continue;
    DIType *instDt = instNode->getDIType();
    if (instDt == nullptr)
      continue;
    // should also consider the pointer to the struct.
    DIType *instLowestDt = dbgutils::getLowestDIType(*instDt);
    if (!instLowestDt || !dbgutils::isProjectableType(*instLowestDt))
      continue;
    if (dbgutils::hasSameDITypeName(dt, *instLowestDt))
    {
      vars.insert(&*instIter);
    }
  }
}

std::set<Value *> pdg::SharedDataAnalysis::computeVarsWithStructDITypeInModule(DIType &dt, Module &M)
{
  std::set<Value *> vars;
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    computeVarsWithStructDITypeInFunc(dt, F, vars);
  }
  return vars;
}

bool pdg::SharedDataAnalysis::isStructFieldNode(TreeNode &treeNode)
{
  auto parentNode = treeNode.getParentNode();
  if (!parentNode)
    return false;
  auto parentNodeDt = parentNode->getDIType();
  if (!parentNodeDt)
    return false;
  return dbgutils::isStructType(*parentNodeDt);
}

bool pdg::SharedDataAnalysis::isTreeNodeShared(TreeNode &treeNode)
{
  auto dt = treeNode.getDIType();
  bool accessed_in_driver = false;
  bool accessed_in_kernel = false;

  // the assumption is that driver updates the call back exported by it at initialization phase
  if (dt && dbgutils::isFuncPointerType(*dt) && isDriverCallBackFuncPtrFieldNode(treeNode))
  {
    accessed_in_driver = true;
  }

  auto addrVars = treeNode.getAddrVars();
  for (auto addrVar : addrVars)
  {
    if (Instruction *i = dyn_cast<Instruction>(addrVar))
    {
      Function *f = i->getFunction();
      if (_driverDomainFuncs.find(f) != _driverDomainFuncs.end())
      {
        accessed_in_driver = true;
      }
      if (_kernelDomainFuncs.find(f) != _kernelDomainFuncs.end())
      {
        accessed_in_kernel = true;
      }
    }
  }

  if (accessed_in_driver && accessed_in_kernel)
    return true;
  return false;
}

bool pdg::SharedDataAnalysis::isFieldUsedInStringOps(TreeNode &treeNode)
{
  std::set<EdgeType> edgeTypes = {EdgeType::PARAMETER_IN, EdgeType::DATA_ALIAS};
  auto reach_nodes = _PDG->findNodesReachedByEdges(treeNode, edgeTypes);
  for (auto node : reach_nodes)
  {
    if (node->getValue() != nullptr)
    {
      for (auto user : node->getValue()->users())
      {
        if (CallInst *ci = dyn_cast<CallInst>(user))
        {
          auto called_func = pdgutils::getCalledFunc(*ci);
          if (called_func == nullptr)
            continue;
          std::string calleeName = called_func->getName().str();
          calleeName = pdgutils::stripFuncNameVersionNumber(calleeName);
          if (_string_op_names.find(calleeName) != _string_op_names.end())
            return true;
        }
      }
    }
  }
  return false;
}

bool pdg::SharedDataAnalysis::isSharedFieldID(std::string fieldId, std::string field_type_name)
{
  if (fieldId.empty())
    return false;
  return (_shared_field_id.find(fieldId) != _shared_field_id.end());
}

void pdg::SharedDataAnalysis::computeSharedFieldID()
{
  for (auto dt_tree_pair : _global_struct_di_type_map)
  {
    // auto di_type_name = dbgutils::getSourceLevelTypeName(*dt_tree_pair.first);
    // di_type_name = "struct." + di_type_name;
    // auto gb = _module->getNamedValue(StringRef(di_type_name));

    Tree *tree = dt_tree_pair.second;
    std::queue<TreeNode *> nodeQueue;
    nodeQueue.push(tree->getRootNode());
    // setting up map for collecting fields access stat
    auto sharedStructDIType = dbgutils::getLowestDIType(*tree->getRootNode()->getDIType());
    assert(sharedStructDIType != nullptr && "cannot collect fields access stats for empty struct di type\n");
    auto sharedStructName = dbgutils::getSourceLevelTypeName(*sharedStructDIType);

    while (!nodeQueue.empty())
    {
      TreeNode *currentTreeNode = nodeQueue.front();
      nodeQueue.pop();
      DIType *nodeDIType = currentTreeNode->getDIType();
      if (nodeDIType == nullptr)
        continue;

      bool isPtrType = dbgutils::isPointerType(*nodeDIType);
      bool isFuncPtrType = dbgutils::isFuncPointerType(*nodeDIType);
      bool hasReadByKernel = false;
      bool hasUpdateByDriver = false;
      // counting for shared struct fields
      if (currentTreeNode->isStructField())
      {
        if (isTreeNodeShared(*currentTreeNode))
        {
          currentTreeNode->isShared = true;
          auto fieldID = pdgutils::computeTreeNodeID(*currentTreeNode);
          if (!fieldID.empty())
            _shared_field_id.insert(fieldID);
          // check whether a shared field is used in string operation.
          if (isFieldUsedInStringOps(*currentTreeNode))
            _string_field_id.insert(fieldID);
          // check whether a field is used in pointer arithmetic
          if (DEBUG)
          {
            if (pdgutils::hasPtrArith(*currentTreeNode, true))
              errs() << "find ptr arith in sd: " << fieldID << "\n";
          }
          // collect read/write accesses in driver/kernel domain
          countReadWriteAccessTimes(*currentTreeNode);
        }
      }

      for (auto child : currentTreeNode->getChildNodes())
      {
        nodeQueue.push(child);
      }
    }
  }
  _shared_field_id.insert("struct inodei_rdev");
  _shared_field_id.insert("struct inodedevt");
  _shared_field_id.insert("struct filef_inode");
}

void pdg::SharedDataAnalysis::computeSharedGlobalVars()
{
  for (auto &global_var : _module->getGlobalList())
  {
    bool used_in_kernel = false;
    bool used_in_driver = false;
    for (auto user : global_var.users())
    {
      if (Instruction *i = dyn_cast<Instruction>(user))
      {
        auto func = i->getFunction();
        if (_kernelDomainFuncs.find(func) != _kernelDomainFuncs.end())
          used_in_kernel = true;
        else
          used_in_driver = true;
      }
      if (used_in_kernel && used_in_driver)
      {
        _shared_global_vars.insert(&global_var);
        break;
      }
    }
  }
}

void pdg::SharedDataAnalysis::dumpSharedFieldID()
{
  errs() << "dumping shared field id\n";
  for (auto id : _shared_field_id)
  {
    errs() << id << "\n";
  }
}

void pdg::SharedDataAnalysis::readSentinelFields()
{
  sys::fs::file_status status;
  sys::fs::status("boundaryFiles", status);
  if (!sys::fs::exists(status) || !sys::fs::is_directory(status))
  {
    errs() << "boundary files don't exist, please run boundary analysis pass (-output-boundary-info) first\n";
    return;
  }

  std::ifstream ReadFile("boundaryFiles/sentinel_fields");
  for (std::string line; std::getline(ReadFile, line);)
  {
    _sentinelFields.insert(line);
  }
}

void pdg::SharedDataAnalysis::readGlobalFuncOpStructNames()
{
  sys::fs::file_status status;
  sys::fs::status("boundaryFiles", status);
  if (!sys::fs::exists(status) || !sys::fs::is_directory(status))
  {
    errs() << "boundary files don't exist, please run boundary analysis pass (-output-boundary-info) first\n";
    return;
  }

  std::ifstream ReadFile("boundaryFiles/global_op_struct_names");
  for (std::string line; std::getline(ReadFile, line);)
  {
    _driver_func_op_struct_names.insert(line);
    _shared_struct_type_names.insert(line);
  }
}

void pdg::SharedDataAnalysis::printPingPongCalls(Module &M)
{
  auto &call_g = PDGCallGraph::getInstance();
  if (!call_g.isBuild())
    call_g.build(M);
  unsigned cross_boundary_times = 0;
  for (auto f : _boundary_funcs)
  {
    if (f->isDeclaration())
      continue;
    auto caller_node = call_g.getNode(*f);
    if (!caller_node)
      continue;

    std::set<Function *> opposite_domain_funcs = _driverDomainFuncs;
    if (_driverDomainFuncs.find(f) != _driverDomainFuncs.end())
      opposite_domain_funcs = _kernelDomainFuncs;

    // check if this func can be called from the other domain.
    bool is_called = false;
    for (auto in_neighbor : caller_node->getInNeighbors())
    {
      auto node_val = in_neighbor->getValue();
      if (!isa<Function>(node_val))
        continue;
      Function *caller = cast<Function>(node_val);
      if (opposite_domain_funcs.find(caller) != opposite_domain_funcs.end())
      {
        is_called = true;
        break;
      }
    }

    if (!is_called)
      continue;

    std::queue<Node *> nodeQueue;
    std::unordered_set<Node *> seen_node;
    nodeQueue.push(caller_node);
    while (!nodeQueue.empty())
    {
      Node *n = nodeQueue.front();
      nodeQueue.pop();
      if (seen_node.find(n) != seen_node.end())
        continue;
      seen_node.insert(n);
      auto node_val = n->getValue();
      if (!isa<Function>(node_val))
        continue;
      Function *called_f = cast<Function>(node_val);
      if (opposite_domain_funcs.find(called_f) != opposite_domain_funcs.end())
      {
        cross_boundary_times++;
        break;
      }

      for (auto out_neighbor : n->getOutNeighbors())
      {
        nodeQueue.push(out_neighbor);
      }
    }
  }

  errs() << "================  ping pong call stats  ==================\n";
  errs() << "cross boundary times: " << cross_boundary_times << "\n";
  errs() << "num of boundary funcs: " << _boundary_funcs.size() << "\n";
  errs() << "==========================================================\n";
}

void pdg::SharedDataAnalysis::dumpSharedTypes(std::string fileName)
{
  std::ofstream outputFile(fileName);
  for (auto shared_struct_type : _shared_struct_type_names)
  {
    if (!shared_struct_type.empty())
      outputFile << shared_struct_type << "\n";
  }
  outputFile.close();
}

Function *pdg::SharedDataAnalysis::getModuleInitFunc(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    std::string funcName = F.getName().str();
    if (funcName.find("_init_module") != std::string::npos)
      return &F;
  }
  return nullptr;
}

void pdg::SharedDataAnalysis::countReadWriteAccessTimes(TreeNode &treeNode)
{
  // treeNode is shared

  if (!treeNode.isStructField())
    return;
  // init kernel/driver read/write stats
  unsigned driverReadTimes = 0;
  unsigned driverWriteTimes = 0;
  unsigned kernelReadTimes = 0;
  unsigned kernelWriteTimes = 0;

  if (isFuncPtr(treeNode) && isDriverCallBackFuncPtrFieldNode(treeNode))
  {
    driverWriteTimes += 1;
  }

  auto addrVars = treeNode.getAddrVars();
  for (auto addrVar : addrVars)
  {
    if (Instruction *i = dyn_cast<Instruction>(addrVar))
    {
      Function *f = i->getFunction();
      // count driver read write times
      if (_driverDomainFuncs.find(f) != _driverDomainFuncs.end())
      {
        if (pdgutils::hasWriteAccess(*i))
          driverWriteTimes++;
        if (pdgutils::hasReadAccess(*i))
          driverReadTimes++;
      }
      // count kernel read write times
      else if (_kernelDomainFuncs.find(f) != _kernelDomainFuncs.end())
      {
        if (pdgutils::hasReadAccess(*i))
          kernelReadTimes++;
        if (pdgutils::hasWriteAccess(*i))
          kernelWriteTimes++;
      }
    }
  }

  // collect pointer type fields stats
  auto nodeDIType = treeNode.getDIType();
  bool isPtrType = dbgutils::isPointerType(*nodeDIType);
  bool isFuncPtrType = dbgutils::isFuncPointerType(*nodeDIType);

  // detect fields only updated by driver and read by the kernel
  //if (kernelReadTimes != 0 && !isPtrType)
  if (kernelReadTimes != 0 && driverWriteTimes != 0)
  {
    if (isPtrType)
    {
      if (isFuncPtrType)
      {
        _ksplitStats->funcPtrNum++;
        // if (driverWriteTimes > 0)
        //   _ksplitStats->DCFuncPtrNum++;
        // if (driverReadTimes > 0)
        //   _ksplitStats->DLFuncPtrNum++;
      }
      else
      {
        _ksplitStats->dataPtrNum++;
        // if (driverWriteTimes > 0)
        //   _ksplitStats->DCDataPtrNum++;
        // if (driverReadTimes > 0)
        //   _ksplitStats->DLDataPtrNum++;
      }
    }
    else
    {
      // classify non-ptr fields
      // std::string fieldTypeStr = getFieldTypeStr(treeNode);
      // auto fieldName = treeNode.getSrcHierarchyName(false);
      // detectDrvAttacksOnField(treeNode);
      // computeTaintOnField(treeNode);
    }
  }
}

// print out the update locations of a field in driver domain
void pdg::SharedDataAnalysis::printDriverUpdateLocations(TreeNode &treeNode, raw_fd_ostream &OS)
{
  OS << "Driver Update Locations ( " << treeNode.getSrcHierarchyName(false) << " ): \n";
  for (auto addrVar : treeNode.getAddrVars())
  {
    if (auto inst = dyn_cast<Instruction>(addrVar))
    {
      // igonore cases in which header path is updated in the header files
      if (pdgutils::isUpdatedInHeader(*inst))
        continue;
      auto func = inst->getFunction();
      if (isDriverFunc(*func) && pdgutils::hasWriteAccess(*inst))
      {
        OS << "\t(" << func->getName() << ") ";
        pdgutils::printSourceLocation(*inst, OS);
      }
    }
  }
  OS << " \n ============================================= \n\n";
}

void pdg::SharedDataAnalysis::getDriverUpdateLocStr(TreeNode &treeNode, raw_string_ostream &ss)
{
  for (auto addrVar : treeNode.getAddrVars())
  {
    if (auto inst = dyn_cast<Instruction>(addrVar))
    {
      // igonore cases in which header path is updated in the header files
      if (pdgutils::isUpdatedInHeader(*inst))
        continue;
      auto func = inst->getFunction();
      if (isDriverFunc(*func) && pdgutils::hasWriteAccess(*inst))
      {
        auto sourceLocStr = pdgutils::getSourceLocationStr(*inst);
        ss << "[ (" << func->getName() << ") " << sourceLocStr << " ], ";
      }
    }
  }
}

std::string pdg::SharedDataAnalysis::getFieldTypeStr(TreeNode &treeNode)
{
  std::string ret = "";
  auto &ksplitStats = KSplitStats::getInstance();
  // first check branch conditions
  auto dt = treeNode.getDIType();
  if (dbgutils::isPointerType(*dt))
  {
    ret += "ptr|";
    ksplitStats.numRWPtr++;
    if (isFuncPtr(treeNode))
    {
      ksplitStats.numRWFuncPtr++;
      ret += "fp|";
    }
    if (usedInBranch(treeNode))
    {
      ksplitStats.numRWPtrCondVar++;
      ret += "cond|";
    }
    if (pdgutils::isTreeNodeValUsedAsOffset(treeNode))
    {
      ksplitStats.numRWPtrInPtrArith++;
      ret += "ptrari|";
    }
  }
  else
  {
    ksplitStats.numRWNonPtr++;
    // non pointer type
    if (usedInBranch(treeNode))
    {
      ksplitStats.numRWNonPtrCondVar++;
      ret += "cond|";
    }
    if (pdgutils::isTreeNodeValUsedAsOffset(treeNode))
    {
      ksplitStats.numRWNonPtrInPtrArith++;
      ret += "ptrari|";
    }
  }
  return ret;
}

bool pdg::SharedDataAnalysis::isFuncPtr(TreeNode &treeNode)
{
  auto dt = treeNode.getDIType();
  if (!dt)
    return false;
  if (dbgutils::isFuncPointerType(*dt))
    return true;
  return false;
}

bool pdg::SharedDataAnalysis::isDriverCallBackFuncPtrFieldNode(TreeNode &treeNode)
{
  if (!treeNode.isStructField())
    return false;

  auto parentTypeName = treeNode.getParentNode()->getTypeName(true);
  auto fieldName = treeNode.getSrcName();
  std::string funcOpID = parentTypeName + "_" + fieldName;

  if (exportedFuncPtrFieldNames.find(funcOpID) != exportedFuncPtrFieldNames.end())
    return true;
  return false;
}

bool pdg::SharedDataAnalysis::usedInBranch(TreeNode &treeNode)
{
  for (auto addrVar : treeNode.getAddrVars())
  {
    for (auto user : addrVar->users())
    {
      if (isa<BranchInst>(user))
        return true;
    }
  }
  return false;
}

// ----- detect attacks ------

// the tree node is already detected to be updated in driver and read in kernel
// void pdg::SharedDataAnalysis::detectDrvAttacksOnField(TreeNode &treeNode)
// {
//   auto addrVars = treeNode.getAddrVars();
//   bool isRiskyBound = false;
//   bool isRiskyCond = false;
//   bool isRiskyCondFunc = false;
//   bool isUsedInRiskyAPI = false;

//   // detect shared lock field
//   if (treeNode.isSharedLockField())
//   {
//     _ksplitStats->riskyLockField++;
//     auto addrVar = *addrVars.begin();
//     auto inst = cast<Instruction>(addrVar);
//     auto func = inst->getFunction();
//     printRiskyFieldInfo(errs(), "Risky Lock Field", treeNode, *func, *inst);
//     printDriverUpdateLocations(treeNode);
//   }

//   // check for risky bound field and risky cond field, these two are mutual exclusive
//   // if a field is classified as risky bound, it cannot classified as risky cond.
//   for (auto addrVar : addrVars)
//   {
//     if (isRiskyCond || isRiskyBound || isUsedInRiskyAPI)
//       break;

//     if (auto inst = dyn_cast<Instruction>(addrVar))
//     {
//       auto func = inst->getFunction();
//       auto funcNode = _callGraph->getNode(*func);

//       if (isDriverFunc(*func))
//         continue;

//       auto addrVarNode = _PDG->getNode(*addrVar);
//       if (!addrVarNode->isAddrVarNode())
//         continue;

//       if (!isRiskyBound && detectIsAddrVarUsedAsIndex(*addrVar))
//       {
//         isRiskyBound = true;
//         printRiskyFieldInfo(errs(), "Risky Bound Field", treeNode, *func, *inst);
//         printDriverUpdateLocations(treeNode);

//         if (checkRAWDriverUpdate(*addrVarNode))
//         {
//           errs().indent(20);
//           errs() << "RAW shared bound field: ";
//           errs() << treeNode.getSrcHierarchyName(false) << "\n";
//           _ksplitStats->riskyBoundRAWField++;
//         }
//       }

//       if (!isRiskyCond && detectIsAddrVarUsedInCond(*addrVar))
//       {
//         printRiskyFieldInfo(errs(), "Risky Cond Field", treeNode, *func, *inst);
//         printDriverUpdateLocations(treeNode);

//         isRiskyCond = true;
//         _ksplitStats->riskyCondField++;

//         if (checkRAWDriverUpdate(*addrVarNode))
//         {
//           errs().indent(20);
//           errs() << "RAW shared cond field: ";
//           errs() << treeNode.getSrcHierarchyName(false) << "\n";
//           _ksplitStats->riskyCondRAWField++;
//         }

//         if (!isRiskyCondFunc)
//         {
//           if (dbgutils::isFuncPointerType(*treeNode.getDIType()) && isDriverCallBackFuncPtrFieldNode(treeNode))
//           {
//             errs().indent(20);
//             errs() << "shared cond func field\n";
//             _ksplitStats->riskyCondFuncField++;
//             isRiskyCondFunc = true;
//           }
//         }
//       }

//       if (!isUsedInRiskyAPI && detectIsAddrVarUsedInSensitiveAPI(*addrVar))
//       {
//         isUsedInRiskyAPI = true;
//         _ksplitStats->riskyFieldUsedInSensitiveAPI++;
//       }
//     }
//   }
// }

// /*
// Check if a driver updated field used to index buffer in the kernel domain
// */
// bool pdg::SharedDataAnalysis::detectIsAddrVarUsedAsIndex(Value &addrVar, bool countTaint)
// {
//   for (auto user : addrVar.users())
//   {
//     // check the load instruction that reads from the address,
//     // determine if the loaded value is used as index in array or pointer arithmetic
//     // gep (addr) -> load gep -> used as index (used as the offset operand )
//     if (auto li = dyn_cast<LoadInst>(user))
//     {
//       for (auto u : li->users())
//       {
//         if (auto gep = dyn_cast<GetElementPtrInst>(u))
//         {
//           auto ptrOperand = gep->getPointerOperand();
//           auto ptrValNode = _PDG->getNode(*ptrOperand);
//           // this check whether the field is is used in pointer arithmetic, excluding the cases in which the field is a
//           // struct pointer.
//           if (ptrValNode->getDIType() && !dbgutils::isStructPointerType(*ptrValNode->getDIType()))
//           {
//             if (li == ptrOperand)
//             {
//               if (countTaint)
//                 _ksplitStats->riskyPtrArithFieldTaint++;
//               else
//                 _ksplitStats->riskyPtrArithField++;
//             }
//             else
//             {
//               if (countTaint)
//                 _ksplitStats->riskyIndexFieldTaint++;
//               else
//                 _ksplitStats->riskyIndexField++;
//             }
//             return true;
//           }
//         }
//       }
//     }
//   }
//   return false;
// }

// bool pdg::SharedDataAnalysis::detectIsAddrVarUsedInCond(Value &addrVar)
// {
//   for (auto user : addrVar.users())
//   {
//     if (auto li = dyn_cast<LoadInst>(user))
//     {
//       // check if the loaded value is used in branch
//       for (auto u : li->users())
//       {
//         if (isa<ICmpInst>(u) || isa<SwitchInst>(u))
//           return true;
//       }
//     }
//   }
//   return false;
// }

// bool pdg::SharedDataAnalysis::detectIsAddrVarUsedInSensitiveAPI(Value &addrVar)
// {
//   for (auto user : addrVar.users())
//   {
//     if (CallInst *ci = dyn_cast<CallInst>(user))
//     {
//       auto calledFunc = pdgutils::getCalledFunc(*ci);
//       if (!calledFunc)
//         continue;
//       auto calledFuncName = calledFunc->getName().str();
//       for (auto op : sensitiveOperations)
//       {
//         if (calledFuncName.find(op) != std::string::npos)
//           return true;
//       }
//     }
//   }
//   return false;
// }

// bool pdg::SharedDataAnalysis::checkRAWDriverUpdate(Node &node)
// {
//   std::set<EdgeType> edgeTypes = {EdgeType::PARAMETER_IN,
//                                   EdgeType::DATA_ALIAS};
//   auto nodes = _PDG->findNodesReachedByEdges(node, edgeTypes, true);
//   for (auto node : nodes)
//   {
//     if (!node->getValue())
//       continue;
//     if (isa<Instruction>(node->getValue()))
//     {
//       auto func = node->getFunc();
//       if (isDriverFunc(*func))
//       {
//         if (pdgutils::hasWriteAccess(*node->getValue()))
//           return true;
//       }
//     }
//   }
//   return false;
// }

// void pdg::SharedDataAnalysis::findGlobalAlias(Node &node, std::unordered_set<Node *> &aliasNodes)
// {
//   std::set<EdgeType> searchEdgeTypes = {
//       EdgeType::PARAMETER_IN,
//       EdgeType::DATA_ALIAS};
//   auto ret = _PDG->findNodesReachedByEdges(node, searchEdgeTypes);
//   aliasNodes.insert(ret.begin(), ret.end());
// }

// void pdg::SharedDataAnalysis::computeTaintOnField(TreeNode &treeNode)
// {
//   // TODO: skip func ptr now for sannity check
//   // if (dbgutils::isFuncPointerType(*treeNode.getDIType()))
//   //   return;

//   std::unordered_set<Node *> aliasNodes;
//   bool taintSenAPI = false;
//   bool taintCond = false;
//   bool taintPtrArith = false;

//   for (auto addrVar : treeNode.getAddrVars())
//   {
//     if (taintSenAPI || taintCond || taintPtrArith)
//       break;
//     auto addrVarNode = _PDG->getNode(*addrVar);
//     findGlobalAlias(*addrVarNode, aliasNodes);
//     Instruction* srcInst = cast<Instruction>(addrVar);
//     Function *srcFunc = srcInst->getFunction();
//     // only start the taint from the fields accessed in kernel
//     if (isDriverFunc(*srcFunc))
//       continue;
//     computeExplicitFlowTaintedOnNode(*addrVarNode, *srcInst, treeNode.getSrcHierarchyName(), taintSenAPI, taintCond, taintPtrArith);
//     for (auto aliasNode : aliasNodes)
//     {
//       if (aliasNode == addrVarNode)
//         continue;
//       if (!aliasNode->getValue() || aliasNode->getValue()->getType() != addrVar->getType())
//         continue;
//       // skip driver alias
//       auto aliasNodeFunc = aliasNode->getFunc();
//       if (aliasNodeFunc && isDriverFunc(*aliasNodeFunc))
//         continue;
//       computeExplicitFlowTaintedOnNode(*aliasNode, *srcInst, treeNode.getSrcHierarchyName(), taintSenAPI, taintCond, taintPtrArith);
//       // computeImplicitFlowTaintedOnField(*aliasNode, *srcInst, treeNode.getSrcHierarchyName(), isTainted);
//     }
//   }
// }

// // assume the tree node (field) is updated by driver and read by kernel
// void pdg::SharedDataAnalysis::computeExplicitFlowTaintedOnNode(Node &node, Instruction &srcInst, std::string fieldAccessPath, bool &taintSenAPI, bool &taintCond, bool &taintPtrArith)
// {
//   // taint nodes found through def_use edge
//   std::set<EdgeType> defUseEdges = {
//       EdgeType::PARAMETER_IN,
//       EdgeType::DATA_DEF_USE};

//   auto defUseNodes = _PDG->findNodesReachedByEdges(node, defUseEdges);
//   for (auto defUseNode : defUseNodes)
//   {
//     // if (isTainted)
//     //   break;
//     auto taintVal = defUseNode->getValue();
//     // if (!taintVal || taintVal == &srcInst)
//     if (!taintVal)
//       continue;

//     auto taintNode = _PDG->getNode(*taintVal);
//     auto taintFunc = taintNode->getFunc();
//     if (isDriverFunc(*taintFunc))
//       continue;

//     if (!taintSenAPI && detectIsAddrVarUsedInSensitiveAPI(*taintVal))
//     {
//       taintSenAPI = true;
//       _ksplitStats->riskyFieldUsedInSensitiveAPITaint++;
//       // if (defUseNode != &node)
//       //   printTaintTrace(srcInst, *taintCI, fieldAccessPath, "Explicit SenOp");
//     }

//     // if (LoadInst *li = dyn_cast<LoadInst>(taintVal))
//     // {
//     //   // check memory read
//     //   for (auto user : li->users())
//     //   {
//     //     if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(user))
//     //     {
//     //       if (!pdgutils::isStructPointerType(*gep->getPointerOperandType()))
//     //       {
//     //         // printTaintTrace(srcInst, *li, fieldAccessPath, "Explicit Mem Read Acc");
//     //         if (!isTainted)
//     //         {
//     //           isTainted = true;
//     //         }
//     //       }
//     //     }
//     //   }
//     // }

//     // if (StoreInst *si = dyn_cast<StoreInst>(taintVal))
//     // {
//     //   // check memory update
//     //   if (si->getPointerOperand() == taintVal)
//     //   {
//     //     // printTaintTrace(srcInst, *si, fieldAccessPath, "Explicit Mem Write Acc");
//     //     if (!isTainted)
//     //     {
//     //       isTainted = true;
//     //     }
//     //   }
//     // }

//     // check for buffer access / ptr arithmetic
//     if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(taintVal))
//     {
//       if (!taintPtrArith && detectIsAddrVarUsedAsIndex(*gep, true))
//       {
//         taintPtrArith = true;
//         if (defUseNode != &node)
//           printTaintTrace(srcInst, *gep, fieldAccessPath, "Explicit PtrAri");
//       }
//     }

//     if (!taintCond && detectIsAddrVarUsedInCond(*taintVal))
//     {
//       // check if branch condition is affected
//       taintCond = true;
//       _ksplitStats->riskyCondFieldTaint++;
//       if (Instruction *taintI = dyn_cast<Instruction>(taintVal))
//       {
//         if (defUseNode != &node)
//           printTaintTrace(srcInst, *taintI, fieldAccessPath, "Explicit Branch");
//       }
//     }
//   }
// }

// void pdg::SharedDataAnalysis::computeImplicitFlowTaintedOnField(Node &node, Instruction &srcInst, std::string fieldAccessPath, bool &taintSenAPI, bool &taintCond, bool &taintPtrArith)
// {
//   std::set<EdgeType> searchEdgeTypes = {
//       EdgeType::CONTROL};

//   auto nodeVal = node.getValue();
//   for (auto user : nodeVal->users())
//   {
//     if (auto li = dyn_cast<LoadInst>(user))
//     {
//       for (auto liUser : li->users())
//       {
//         // check if the field value is used in any branch.
//         // TODO: we should potentially also check the address itself too.
//         if (isa<ICmpInst>(liUser))
//         {
//           for (auto icmpUser : liUser->users())
//           {
//             // check if the cmp instruction value is used in branch condition evaluation
//             if (isa<BranchInst>(icmpUser))
//             {
//               auto branchUserNode = _PDG->getNode(*icmpUser);
//               // search instructions that are reachable through CONTROL_DEP Edge
//               auto taintNodes = _PDG->findNodesReachedByEdges(*branchUserNode, searchEdgeTypes);
//               for (auto taintNode : taintNodes)
//               {
//                 if (taintNode == branchUserNode)
//                   continue;
//                 auto taintVal = taintNode->getValue();
//                 if (CallInst *CI = dyn_cast<CallInst>(taintVal))
//                 {
//                   auto calledFunc = pdgutils::getCalledFunc(*CI);
//                   if (!calledFunc)
//                     continue;
//                   auto calledFuncName = calledFunc->getName().str();
//                   for (auto op : sensitiveOperations)
//                   {
//                     if (calledFuncName.find(op) != std::string::npos)
//                     {
//                       printTaintTrace(srcInst, *CI, fieldAccessPath, "Implicit Dep - Sen Op");
//                     }
//                   }
//                 }
//               }
//             }
//           }
//         }
//       }
//     }
//   }
// }

static RegisterPass<pdg::SharedDataAnalysis>
    SharedDataAnalysis("shared-data", "Shared Data Analysis", false, true);