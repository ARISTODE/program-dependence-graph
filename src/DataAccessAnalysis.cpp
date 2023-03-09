#include "DataAccessAnalysis.hh"

std::map<std::string, std::string> primitiveTyMap{
    {"long long int", "u64"},
    {"long long int*", "u64*"},
    {"long long", "u64"},
    {"long long*", "u64*"},
    {"long int", "u64"},
    {"long int*", "u64*"},
    {"long unsigned int", "u64"},
    {"long unsigned int*", "u64*"},
    {"long long unsigned int", "u64"},
};

using namespace llvm;

char pdg::DataAccessAnalysis::ID = 0;

cl::opt<bool> SharedDataFlag("sd", llvm::cl::desc("turn on shared data optimization"), llvm::cl::init(true), llvm::cl::value_desc("shared_data"));

void pdg::DataAccessAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<SharedDataAnalysis>();
  AU.setPreservesAll();
}

void patchStringAnnotation(std::string &field_type_name, std::set<std::string> &annotations)
{
  auto it = annotations.find("string");
  if (it != annotations.end())
  {
    annotations.erase(it, annotations.end());
    field_type_name = "string *";
  }
}

bool pdg::DataAccessAnalysis::runOnModule(Module &M)
{
  _module = &M;
  _SDA = &getAnalysis<SharedDataAnalysis>();
  _PDG = _SDA->getPDG();
  _callGraph = &PDGCallGraph::getInstance();
  _ksplitStats = &KSplitStats::getInstance();
  computeExportedFuncsPtrNameMap();
  readDriverDefinedGlobalVarNames("driver_globalvar_names");
  readDriverExportedFuncSymbols("driver_exported_func_symbols");
  // _globalVarAccessInfo.open("global_var_access_info.idl");
  unsigned total_num_funcs = 0;
  // intra-procedural analysis
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    // create an entry for driver API fields and ptr fields access, this is purely for
    // stats collection
    if (_SDA->isDriverFunc(F))
    {
      _ksplitStats->_drv_api_acc_map.insert(std::make_pair(&F, std::make_tuple(0, 0, 0)));
      _ksplitStats->_drv_api_ptr_acc_map.insert(std::make_pair(&F, std::make_tuple(0, 0, 0)));
    }
    // compute data access for function arguments, used later for IDL generation
    computeDataAccessForFuncArgs(F);
    // computeContainerOfLocs(F);
    total_num_funcs++;
  }

  generateSyncStubsForBoundaryFunctions(M);
  // count total func size
  if (EnableAnalysisStats)
  {
    // print out analysis stats
    _ksplitStats->_total_func_size += total_num_funcs;
    _ksplitStats->printDrvAPIStats();
    _ksplitStats->printDataStats();
  }
  errs() << "number of kernel read driver update fields: " << _kernelRAWDriverFields << "\n";
  errs() << "Finish analyzing data access info.";
  return false;
}

// API for generating IDL for boundary funcs and global variables
void pdg::DataAccessAnalysis::generateSyncStubsForBoundaryFunctions(Module &M)
{
  _idlFile.open("kernel.idl");
  _idlFile << "// Sync stubs for boundary functions\n";
  _idlFile << "module kernel {\n";
  std::vector<std::string> boundaryFuncNames(_SDA->getBoundaryFuncNames().begin(), _SDA->getBoundaryFuncNames().end());
  _transitiveBoundaryFuncs = _SDA->computeBoundaryTransitiveClosure();
  std::sort(boundaryFuncNames.begin(), boundaryFuncNames.end());
  for (auto funcName : boundaryFuncNames)
  {
    // need to concate the _nesCheck postfix, because nescheck change the signature
    Function *nescheck_func = pdgutils::getNescheckVersionFunc(M, funcName);
    if (nescheck_func == nullptr || nescheck_func->isDeclaration())
      continue;
    generateIDLForFunc(*nescheck_func);
  }

  // genereate additional func call stubs for kernel funcs registered on the driver side
  // EnableAnalysisStats = false;
  for (auto F : _kernelFuncsRegisteredWithFuncPtr)
  {
    if (F == nullptr || F->isDeclaration())
      continue;
    generateIDLForFunc(*F, true);
  }
  // generate rpc_export stub for functions exported form driver through export_symbol
  for (auto s : _driverExportedFuncSymbols)
  {
    Function *func = M.getFunction(StringRef(s));
    if (func == nullptr || func->isDeclaration())
      continue;
    generateIDLForFunc(*func, true);
    // Function *F = M.getFunction(StringRef(s));
    // Function *nescheck_func = pdgutils::getNescheckVersionFunc(M, F->getName().str());
    // if (nescheck_func == nullptr || nescheck_func->isDeclaration())
    //   continue;
    // generateIDLForFunc(*nescheck_func, true);
  }

  constructGlobalOpStructStr();
  _idlFile << _opsStructProjStr << "\n";
  _idlFile << "\n}\n";
  _idlFile.close();
}

void pdg::DataAccessAnalysis::generateSyncStubsForGlobalVars()
{
  _idlFile.open("kernel.idl", std::ios_base::app);
  // generate IDL for global variables
  _idlFile << "// Sync stubs for global variables\n";
  _generateingIDLforGlobal = true;
  for (auto pair : _PDG->getGlobalVarTreeMap())
  {
    Tree *tree = pair.second;
    if (!globalVarHasAccessInDriver(*pair.first))
      continue;
    if (isDriverDefinedGlobal(*pair.first))
      continue;
    computeDataAccessForGlobalTree(tree);
    generateIDLFromGlobalVarTree(*pair.first, tree);
  }
  _generateingIDLforGlobal = false;
  _idlFile.close();
}

std::set<pdg::Node *> pdg::DataAccessAnalysis::findCrossDomainParamNode(Node &n, bool isBackward)
{
  std::queue<Node *> nodeQueue;
  std::set<EdgeType> searchEdgeTypes = {
      EdgeType::PARAMETER_IN,
      EdgeType::DATA_ALIAS,
      EdgeType::DATA_RET};
  nodeQueue.push(&n);
  std::set<Node *> seenNodes;
  std::set<Node *> crossDomainNodes;
  while (!nodeQueue.empty())
  {
    auto currentNode = nodeQueue.front();
    nodeQueue.pop();
    if (seenNodes.find(currentNode) != seenNodes.end())
      continue;
    seenNodes.insert(currentNode);
    Node::EdgeSet edgeSet;
    if (isBackward)
      edgeSet = currentNode->getInEdgeSet();
    else
      edgeSet = currentNode->getOutEdgeSet();

    for (auto edge : edgeSet)
    {
      if (searchEdgeTypes.find(edge->getEdgeType()) == searchEdgeTypes.end())
        continue;
      Node *targetNode = nullptr;
      if (isBackward)
        targetNode = edge->getSrcNode();
      else
        targetNode = edge->getDstNode();
      if (targetNode->getNodeType() == GraphNodeType::FORMAL_IN)
        crossDomainNodes.insert(targetNode);
      else
        nodeQueue.push(targetNode);
    }
  }
  return crossDomainNodes;
}

void pdg::DataAccessAnalysis::readDriverDefinedGlobalVarNames(std::string fileName)
{
  std::ifstream ReadFile(fileName);
  for (std::string line; std::getline(ReadFile, line);)
  {
    _driverDefGlobalVarNames.insert(line);
  }
}

void pdg::DataAccessAnalysis::readDriverExportedFuncSymbols(std::string fileName)
{
  std::ifstream ReadFile(fileName);
  for (std::string line; std::getline(ReadFile, line);)
  {
    _driverExportedFuncSymbols.insert(line);
  }
}

bool pdg::DataAccessAnalysis::isSharedAllocator(Value &allocator)
{
  // check whether an allocated object can be passed across isolation boundary
  // step 1: initalize the domain for the alloc site
  // local allocator
  bool ixgbeProbeFlag = false;
  auto curDomain = DomainTag::DRIVER_DOMAIN;
  if (CallInst *ci = dyn_cast<CallInst>(&allocator))
  {
    Function *f = ci->getFunction();
    // eliminate kzalloc* functions, as kzalloc calls __kmalloc internally
    auto funcName = f->getName().str();
    if (funcName.find("kzalloc") != std::string::npos)
      return false;

    if (f->getName() == "ixgbe_probe")
      ixgbeProbeFlag = true;
    // now only tracking driver side allocators
    if (!_SDA->isDriverFunc(*f))
      curDomain = DomainTag::KERNEL_DOMAIN;
    // return false;
  }
  // TODO: consider global variables
  // step 2: check whether the allocator is propagated to the kernel domain
  auto valNode = _PDG->getNode(allocator);
  assert(valNode != nullptr && "cannot generate size anno str for null node\n");
  std::set<EdgeType> searchEdgeTypes = {
      EdgeType::PARAMETER_IN,
      EdgeType::DATA_ALIAS,
      EdgeType::DATA_RET};
  auto reachableNodes = _PDG->findNodesReachedByEdges(*valNode, searchEdgeTypes);
  if (ixgbeProbeFlag)
    errs() << "allocator " << allocator << " reachable node num " << reachableNodes.size() << "\n";
  for (auto node : reachableNodes)
  {
    Function *f = node->getFunc();
    if (f == nullptr)
      continue;
    if (ixgbeProbeFlag)
    {
      if (node->getValue())
        errs() << "ixgbe probe reaching func: " << f->getName() << " - " << *node->getValue() << "\n";
    }
    auto nodeDomain = DomainTag::KERNEL_DOMAIN;
    // find kernel functions
    if (_SDA->isDriverFunc(*f))
      nodeDomain = DomainTag::DRIVER_DOMAIN;
    if (nodeDomain != curDomain)
    {
      if (curDomain == DomainTag::KERNEL_DOMAIN)
        _ksplitStats->_kernelSharedAllocators++;
      else
        _ksplitStats->_driverSharedAllocators++;
      return true;
    }
  }
  return false;
}

std::unordered_set<pdg::Node *> pdg::DataAccessAnalysis::computeSharedAllocators()
{
  std::unordered_set<pdg::Node *> sharedAllocators;
  auto allocators = _PDG->getAllocators();
  for (auto allocator : allocators)
  {
    if (Instruction *i = dyn_cast<Instruction>(allocator))
      errs() << "allocator in func: " << *allocator << " | " << i->getFunction()->getName() << "\n";
    if (isSharedAllocator(*allocator))
      sharedAllocators.insert(_PDG->getNode(*allocator));
  }
  return sharedAllocators;
}

void pdg::DataAccessAnalysis::propagateAllocSizeAnno(Value &allocator)
{
  // first composing the allocator string in format alloc<{{size, GP_FLAG}}>
  std::string alloc_str = "alloc";
  std::string size_str = "<{{";
  if (CallInst *ci = dyn_cast<CallInst>(&allocator))
  {
    Function *f = ci->getFunction();
    // now only tracking driver side allocators
    if (!_SDA->isDriverFunc(*f))
      return;
    // get size operand
    auto size_operand = ci->getArgOperand(0);
    assert(size_operand != nullptr && "allocator has null size operand!\n");
    if (ConstantInt *cons_int = dyn_cast<ConstantInt>(size_operand))
    {
      auto alloc_size = cons_int->getSExtValue();
      size_str += std::to_string(alloc_size);
    }

    // get GP flag
    if (ci->data_operands_size() > 1)
    {
      auto gp_flag_operand = ci->getArgOperand(1);
      assert(gp_flag_operand != nullptr && "allocator has null gp operand!\n");
      if (ConstantInt *cons_int = dyn_cast<ConstantInt>(size_operand))
      {
        auto gp_flag = cons_int->getSExtValue();
        size_str += std::string("}}, {{") + std::to_string(gp_flag);
      }
      else
        size_str += std::string("}}, {{") + std::string("(DEFAULT_GFP_FLAGS)");

      size_str += "}}>";
    }
  }

  auto valNode = _PDG->getNode(allocator);
  assert(valNode != nullptr && "cannot generate size anno str for null node\n");
  alloc_str += size_str;
  // in this case, the allocated object escaped.
  auto aliasNodes = _PDG->findNodesReachedByEdge(*valNode, EdgeType::DATA_ALIAS);
  aliasNodes.insert(valNode);
  // if any alias is address variable of the parameter tree, then we consider the allocated
  // object need to be allocated at the caller side.
  bool passAcrossBoundary = false;
  for (auto aliasNode : aliasNodes)
  {
    // aliasNode->dump();
    if (aliasNode->isAddrVarNode())
    {
      auto param_treeNode = aliasNode->getAbstractTreeNode();
      TreeNode *tn = (TreeNode *)param_treeNode;
      tn->setAllocStr(alloc_str + "(caller)");
      passAcrossBoundary = true;
    }
    else
    {
      // in this case, the allocated object is passed across isolation boundary.
      // the tracking is path insensitive. If two functions are called in different branches, both function would have the alloc attributes created for the received parameter
      auto cross_domain_param_nodes = findCrossDomainParamNode(*aliasNode);
      for (auto n : cross_domain_param_nodes)
      {
        if (n != nullptr)
        {
          TreeNode *tn = (TreeNode *)n;
          tn->setAllocStr(alloc_str + "(callee)");
          passAcrossBoundary = true;
        }
      }
    }
  }
}

void pdg::DataAccessAnalysis::inferDeallocAnno(Value &deallocator)
{
  // check if any address variable is passed to a deallocation function.
  if (CallInst *ci = dyn_cast<CallInst>(&deallocator))
  {
    auto freed_object = ci->getOperand(0);
    assert(freed_object != nullptr && "cannot infer dealloc annotation for nullptr!\n");
    auto freed_object_node = _PDG->getNode(*freed_object);
    if (freed_object_node->isAddrVarNode())
    {
      auto param_node = freed_object_node->getAbstractTreeNode();
      auto backward_cross_domain_param_nodes = findCrossDomainParamNode(*param_node, true);
      // perform backward search to identify the parameter tree node that should contain the dealloc attribute.
      for (auto n : backward_cross_domain_param_nodes)
      {
        if (n != nullptr)
        {
          TreeNode *tn = (TreeNode *)n;
          tn->setAllocStr("dealloc(caller)");
        }
      }
    }
  }
}

void pdg::DataAccessAnalysis::computeAllocSizeAnnos(Module &M)
{
  auto allocators = _PDG->getAllocators();
  for (auto allocator : allocators)
  {
    propagateAllocSizeAnno(*allocator);
  }
}

void pdg::DataAccessAnalysis::computeDeallocAnnos(Module &M)
{
  auto deallocators = _PDG->getDeallocators();
  for (auto deallocator : deallocators)
  {
    inferDeallocAnno(*deallocator);
  }
}

void pdg::DataAccessAnalysis::computeCollocatedAllocsite(Module &M)
{
  auto allocators = _PDG->getAllocators();
  for (auto allocator : allocators)
  {
    checkCollocatedAllocsite(*allocator);
  }
}

void pdg::DataAccessAnalysis::computeExportedFuncsPtrNameMap()
{
  std::ifstream driverExportFuncs("exported_funcs");
  std::ifstream driverExportFuncPtrs("exported_func_ptrs");
  for (std::string line1, line2; std::getline(driverExportFuncPtrs, line1), std::getline(driverExportFuncs, line2);)
  {
    // in some cases, a function pointer exported from driver may point to a kernel function
    // in this case, we don't treat this exported pointer as a interface function.
    Function *pointed_func = _module->getFunction(line2);
    if (pointed_func == nullptr || pointed_func->isDeclaration())
      continue;
    _exportedFuncsPtrNameMap[line1] = line2; // key: registered driver side function, value: the registered function pointer name
  }
}

void pdg::DataAccessAnalysis::computeDataAccessTagsForVal(Value &val, std::set<pdg::AccessTag> &accTags)
{
  if (pdgutils::hasReadAccess(val))
    accTags.insert(AccessTag::DATA_READ);
  if (pdgutils::hasWriteAccess(val))
    accTags.insert(AccessTag::DATA_WRITE);
}

void pdg::DataAccessAnalysis::computeDataAccessTagsForArrayVal(Value &val, std::set<pdg::AccessTag> &accTags)
{
  /*
  In the case of an array field, the elements are accessed using gep (GetElementPtr) instructions.
  We approximate the access behavior of an array based on the access behavior of its individual elements.
  If an element in the array has read access, we consider the entire array to be read, and similarly for write access.
  */
  for (auto user : val.users())
  {
    if (isa<GetElementPtrInst>(user))
    {
      if (pdgutils::hasReadAccess(*user))
        accTags.insert(AccessTag::DATA_READ);
      if (pdgutils::hasWriteAccess(*user))
        accTags.insert(AccessTag::DATA_WRITE);
    }
  }
}

void pdg::DataAccessAnalysis::computeDataAccessForTreeNode(TreeNode &treeNode, bool isGlobalTreeNode, bool isRet)
{
  auto func = treeNode.getFunc();
  // if (_transitiveBoundaryFuncs.find(func) == _transitiveBoundaryFuncs.end())
  //   return;
  if (!treeNode.getDIType())
  {
    // errs() << "[Warning]: processing tree node with null DIType in func " << 
    // func->getName() << " - depth " << treeNode.getDepth() 
    // << " - isRet " << isRet 
    // << " parent var name " << treeNode.getParentNode()->getSrcHierarchyName() << "\n";
    return;
  }

  DomainTag boundary_func_domain_tag = DomainTag::NO_DOMAIN;

  if (func != nullptr)
    boundary_func_domain_tag = computeFuncDomainTag(*func);

  std::string parentNodtTypeName = "";
  TreeNode *parentNode = treeNode.getParentNode();
  if (parentNode != nullptr)
    parentNodtTypeName = dbgutils::getSourceLevelTypeName(*(parentNode->getDIType()), true);

  std::string field_var_name = dbgutils::getSourceLevelVariableName(*treeNode.getDIType());
  bool is_sentinel_type = _SDA->isSentinelField(field_var_name);
  // special hanlding for function pointers and sentinel type
  if (is_sentinel_type)
  {
    treeNode.is_sentinel = true;
    treeNode.addAccessTag(AccessTag::DATA_READ);
  }

  // check for special cases:
  // 1. check if current field is stored with a function address. If so, add the function to exported function list
  // 2. check whether a new object is stored to the current node's address. If this is true and current node is a struct pointer, mark all fields to be synchronized.
  // 3. detect variadic gep accesses. If this case happen, we might fail to detect some field accesses
  for (auto addrVar : treeNode.getAddrVars())
  {
    for (auto user : addrVar->users())
    {
      if (StoreInst *st = dyn_cast<StoreInst>(user))
      {
        auto val_op = st->getValueOperand();
        if (Function *f = dyn_cast<Function>(val_op))
        {
          auto funcName = f->getName().str();
          _exportedFuncsPtrNameMap.insert(std::make_pair(field_var_name, funcName));
        }

        // add a function and check whether this value is newly allocated
        // here the strategy is mark all the fields
        if (isa<GlobalVariable>(val_op))
        {
          for (auto childNode : treeNode.getChildNodes())
          {
            childNode->addAccessTag(AccessTag::DATA_READ);
          }
          // stop processing since we find a new object stored to this address
          break;
        }
      }
      if (MemCpyInst *mci = dyn_cast<MemCpyInst>(user))
      {
        // TODO: we should switch the logic to detect whether a new
        // object is stored copied to the passed pointer
        auto src_val = mci->getSource()->stripPointerCasts();
        if (isa<GlobalVariable>(src_val))
        {
          // mark the whole tree as read
          auto tree = treeNode.getTree();
          tree->addAccessForAllNodes(AccessTag::DATA_READ);
          // stop processing since we find a new object stored to this address
          break;
        }
      }
      // detect variadic gep accesses
      if (auto gep = dyn_cast<GetElementPtrInst>(user))
      {
        if (!gep->hasAllConstantIndices())
        {
          if (pdgutils::isStructPointerType(*gep->getPointerOperand()->getType()))
            errs() << "[Warning]: GEP has variadic idx. May miss field access - " << gep->getFunction()->getName() << "\n";
        }
      }
    }
  }

  // consider exported function pointers are all accessed
  // if (treeNode.getDIType() != nullptr && (dbgutils::isFuncPointerType(*treeNode.getDIType())))
  // {
  //   std::string func_ptr_rpc_ref = parent_node_type_name + "_" + field_var_name;
  //   if (_exportedFuncsPtrNameMap.find(func_ptr_rpc_ref) != _exportedFuncsPtrNameMap.end())
  //   {
  //     treeNode.addAccessTag(AccessTag::DATA_READ);
  //     auto parentNode = treeNode.getParentNode();
  //     while (parentNode != nullptr)
  //     {
  //       parentNode->addAccessTag(AccessTag::DATA_READ);
  //       parentNode = parentNode->getParentNode();
  //     }
  //   }
  // }

  // intra proc access tags
  // auto addrVars = treeNode.getAddrVars();
  // for (auto addrVar : addrVars)
  // {
  //   // skip gep with 0 indices, this could cause false aliasing
  //   if (!treeNode.isStructMember())
  //   {
  //     if (auto gep = dyn_cast<GetElementPtrInst>(addrVar))
  //     {
  //       if (gep->hasAllZeroIndices())
  //         continue;
  //     }
  //   }

  //   if (Instruction *i = dyn_cast<Instruction>(addrVar))
  //   {
  //     // checking for globals
  //     if (isGlobalTreeNode && !_SDA->isDriverFunc(*(i->getFunction())))
  //       continue;
  //   }

  //   // compute access to the addr represented by the treenode
  //   std::set<AccessTag> acc_tags;
  //   computeDataAccessTagsForVal(*addrVar, acc_tags);
  //   for (auto acc_tag : acc_tags)
  //   {
  //     treeNode.addAccessTag(acc_tag);
  //   }
  // }

  bool has_intra_access = false;
  if (treeNode.getAccessTags().size() != 0)
    has_intra_access = true;

  // inter proc access
  bool only_has_cross_domain_access = true;
  std::set<EdgeType> edgeTypes = {
      EdgeType::PARAMETER_IN,
      EdgeType::DATA_ALIAS,
      // EdgeType::DATA_RET
  };

  auto parameterInNodes = _PDG->findNodesReachedByEdges(treeNode, edgeTypes);
  for (auto n : parameterInNodes)
  {
    // compute r/w to the node
    if (n->getValue() != nullptr)
    {
      // skip gep with 0 indices for container object
      if (!treeNode.isStructMember())
      {
        if (auto gep = dyn_cast<GetElementPtrInst>(n->getValue()))
        {
          if (gep->hasAllZeroIndices())
            continue;
        }
      }
      if (Instruction *i = dyn_cast<Instruction>(n->getValue()))
      {
        // errs() << "\t" << *i << " - " << i->getFunction()->getName() << " - " << treeNode.getDepth() << "\n";
        auto inst_func = i->getFunction();
        // DomainTag func_domain_tag = computeFuncDomainTag(*inst_func);
        // optimize by connecting all the nodes in the same isolation domain with the parameter tree node.
        // this avoid frequent query of address variable nodes
        // if (func_domain_tag == boundary_func_domain_tag)
        // {
          treeNode.addAddrVar(*i);
          auto instNode = _PDG->getNode(*i);
          treeNode.addNeighbor(*instNode, EdgeType::PARAMETER_IN);
        // }
        // assumption when computing access for driver side global variables
        if (isGlobalTreeNode && !_SDA->isDriverFunc(*(i->getFunction())))
          continue;
        // only capture accesses in the same domain, if the node reaches back to a different domain, skip
        // if (boundary_func_domain_tag != DomainTag::NO_DOMAIN && func_domain_tag != boundary_func_domain_tag && !isRet)
        //   continue;
        only_has_cross_domain_access = false;
        std::set<AccessTag> acc_tags;
        bool isArrayType = (dbgutils::isArrayType(*treeNode.getDIType()));
        if (isArrayType)
          computeDataAccessTagsForArrayVal(*n->getValue(), acc_tags);
        else
          computeDataAccessTagsForVal(*n->getValue(), acc_tags);
        for (auto acc_tag : acc_tags)
        {
          treeNode.addAccessTag(acc_tag);
          // TODO: this is a temporary fix, because Parameter tree don't have node representing
          // the value of the field address. Need to add this kind of node soon.
          if (parentNode && parentNode->isStructField())
            parentNode->addAccessTag(acc_tag);
        }
      }
    }
  }

  // reconnecting address nodes found by inter procedural call
  for (auto childNode : treeNode.getChildNodes())
  {
    childNode->computeDerivedAddrVarsFromParent();
    for (auto addrVar : childNode->getAddrVars())
    {
      auto addrVarNode = _PDG->getNode(*addrVar);
      if (addrVarNode != nullptr)
        childNode->addNeighbor(*addrVarNode, EdgeType::PARAMETER_IN);
    }
  }

  if (only_has_cross_domain_access && !has_intra_access)
    treeNode.setCanOptOut(true);
}

// check if kernel reads shared fields after driver updates it
void pdg::DataAccessAnalysis::checkCrossDomainRAWforFormalTreeNode(TreeNode &treeNode)
{
  if (!treeNode.getFunc() || treeNode.getDIType() == nullptr)
    return;
  // we only check for struct fields, ignoring the top parameter
  if (!treeNode.isStructField())
    return;

  bool isKernelFunc = !_SDA->isDriverFunc(*treeNode.getFunc());
  bool isPtrField = dbgutils::isPointerType(*treeNode.getDIType());
  auto fieldName = treeNode.getSrcHierarchyName();
  auto fieldID = pdgutils::computeTreeNodeID(treeNode);
  auto accessTags = treeNode.getAccessTags();
  // types of edges to travel for finding reachable nodes
  std::set<EdgeType> edgeSet = {
      EdgeType::PARAMETER_IN,
      EdgeType::DATA_ALIAS,
      EdgeType::DATA_RAW};

  std::string ptrStr = "";
  if (isPtrField)
    ptrStr = "(ptr) ";
  if (isKernelFunc)
  {
    // kernel function
    // find all the shared data read at the kernel domain
    if (accessTags.find(AccessTag::DATA_READ) != accessTags.end())
    {
      std::set<Value *> updateLocs;
      auto backwardReachableNodes = _PDG->findNodesReachedByEdges(treeNode, edgeSet, true);
      for (auto n : backwardReachableNodes)
      {
        // we only check write performed by driver functions
        if (!_SDA->isDriverFunc(*n->getFunc()))
          continue;
        bool hasWriteAccInDrvDomain = false;
        // for founded tree nodes, searching the access to the tree node
        if (!n->getValue())
        {
          if (TreeNode *treeNode = dynamic_cast<TreeNode *>(n))
          {
            for (auto addrVar : treeNode->getAddrVars())
            {
              if (pdgutils::hasWriteAccess(*addrVar))
              {
                updateLocs.insert(addrVar);
                hasWriteAccInDrvDomain = true;
              }
            }
          }
          else
            continue;
        }
        else
        {
          // for address vars nodes
          if (pdgutils::hasWriteAccess(*n->getValue()))
          {
            hasWriteAccInDrvDomain = true;
            updateLocs.insert(n->getValue());
          }
        }

        if (hasWriteAccInDrvDomain)
        {
          if (treeNode.getFunc())
          {
            errs() << ptrStr << "Kernel RAW driver field: " << fieldName << " - "
                   << "Read func: " << treeNode.getFunc()->getName() << " - "
                   << "Update func: " << n->getFunc()->getName() << " - " << treeNode.getDepth() << "\n";
            errs() << "Update locations:\n";
            // if (_visitedSharedFieldIDInRAWAna.find(fieldID) == _visitedSharedFieldIDInRAWAna.end())
            // {
            //   _visitedSharedFieldIDInRAWAna.insert(fieldID);
            _ksplitStats->kernelRAWDriverSharedFields++;
            if (dbgutils::isPointerType(*treeNode.getDIType()))
              _ksplitStats->kernelRAWDriverSharedPtrFields++;
            // }
            for (auto loc : updateLocs)
            {
              if (auto inst = dyn_cast<Instruction>(loc))
                errs() << "\t" << *inst << " - " << inst->getFunction()->getName() << "\n";
            }
            // compute and print out the call path from the update to the read
            // auto srcFuncNode = _callGraph->getNode(*n->getFunc());
            // auto dstFuncNode = _callGraph->getNode(*treeNode.getFunc());
            // auto paths = _callGraph->computePaths(*srcFuncNode, *dstFuncNode);
            // for (auto path : paths)
            // {
            //   errs() << "\t";
            //   auto count = 0;
            //   for (auto func : path)
            //   {
            //     if (count != path.size() - 1)
            //       errs() << func->getName() << "->";
            //     else
            //       errs() << func->getName() << "\n";
            //     count += 1;
            //   }
            // }
          }
          break;
        }
      }
    }
    else
    {
      // for driver function, check if the updates could propagate to the kernel
      if (accessTags.find(AccessTag::DATA_WRITE) != accessTags.end())
      {
        auto reachableNodes = _PDG->findNodesReachedByEdges(treeNode, edgeSet, true);
        for (auto n : reachableNodes)
        {
          // check read performed by kernel domain
          if (_SDA->isDriverFunc(*n->getFunc()))
            continue;
          // TODO: need to investigate why some nodes have null function
          if (!n->getFunc())
          {
            errs() << "find null func node\n";
            assert((n->getValue() != nullptr) && "[ERROR] find null value, null func tree node\n");
            errs() << *n->getValue() << "\n";
            continue;
          }
          bool hasReadInKernelDomain = false;
          if (!n->getValue())
          {
            if (TreeNode *treeNode = dynamic_cast<TreeNode *>(n))
            {
              for (auto addrVar : treeNode->getAddrVars())
              {
                if (pdgutils::hasReadAccess(*addrVar))
                {
                  hasReadInKernelDomain = true;
                  break;
                }
              }
            }
          }
          else
          {
            // for address vars
            if (pdgutils::hasReadAccess(*n->getValue()))
            {
              hasReadInKernelDomain = true;
            }
          }

          if (hasReadInKernelDomain)
          {
            if (treeNode.getFunc())
            {
              errs() << ptrStr << "(D) Kernel RAW driver field: " << fieldName << " - "
                     << "Read func: " << n->getFunc()->getName() << " - "
                     << "Update func: " << treeNode.getFunc()->getName() << "\n";

              _ksplitStats->kernelRAWDriverSharedFields++;
              if (dbgutils::isPointerType(*treeNode.getDIType()))
                _ksplitStats->kernelRAWDriverSharedPtrFields++;
              // if (_visitedSharedFieldIDInRAWAna.find(fieldID) == _visitedSharedFieldIDInRAWAna.end())
              // {
              //   _visitedSharedFieldIDInRAWAna.insert(fieldID);
              //   _kernelRAWDriverFields++;
              // }
            }
            break;
          }
        }
      }
    }
  }
}

void pdg::DataAccessAnalysis::computeFieldReadWriteForTree(Tree *argTree, bool isKernelFunc)
{
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(argTree->getRootNode());
  while (!nodeQueue.empty())
  {
    TreeNode *currentTreeNode = nodeQueue.front();
    nodeQueue.pop();
    if (!currentTreeNode->isShared)
      continue;
    auto fieldID = pdgutils::computeTreeNodeID(*currentTreeNode);
    if (fieldID.empty())
      continue;
    auto fieldName = currentTreeNode->getSrcHierarchyName();
    auto accTags = currentTreeNode->getAccessTags();
    if (isKernelFunc)
    {
      // compute kernel read fields
      if (accTags.find(AccessTag::DATA_READ) != accTags.end())
        _kernelReadSharedFields.insert(fieldID);
    }
    else
    {
      if (accTags.find(AccessTag::DATA_WRITE) != accTags.end())
        _driverUpdateSharedFields.insert(fieldID);
    }

    for (auto childNode : currentTreeNode->getChildNodes())
    {
      nodeQueue.push(childNode);
    }
  }
}

void pdg::DataAccessAnalysis::computeKernelReadSharedFields(Function &F)
{
  auto func_wrapper_map = _PDG->getFuncWrapperMap();
  if (func_wrapper_map.find(&F) == func_wrapper_map.end())
    return;
  FunctionWrapper *fw = func_wrapper_map[&F];
  auto argTreeMap = fw->getArgFormalInTreeMap();
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    Tree *argTree = iter->second;
    computeFieldReadWriteForTree(argTree);
  }
}

void pdg::DataAccessAnalysis::computeDriverUpdateSharedFields(Function &F)
{
  auto func_wrapper_map = _PDG->getFuncWrapperMap();
  if (func_wrapper_map.find(&F) == func_wrapper_map.end())
    return;
  FunctionWrapper *fw = func_wrapper_map[&F];
  auto argTreeMap = fw->getArgFormalInTreeMap();
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    Tree *argTree = iter->second;
    computeFieldReadWriteForTree(argTree, false);
  }
}

void pdg::DataAccessAnalysis::computeKernelReadDriverUpdateFields(Module &M)
{
  for (auto F : _SDA->getBoundaryFuncs())
  {
    // collect kernel read shared fields
    Function *curFunc = F;
    // need to handle specially becuase nescheck rewrite function signature
    if (F->isDeclaration())
    {
      std::string funcName = F->getName().str();
      std::string nesCheckFuncName = funcName + "_nesCheck";
      curFunc = M.getFunction(StringRef(nesCheckFuncName));
      if (curFunc == nullptr || curFunc->isDeclaration())
        continue;
    }
    if (!_SDA->isDriverFunc(*F))
    {
      computeKernelReadSharedFields(*F);
    }
    else
    {
      computeDriverUpdateSharedFields(*F);
    }
  }
}

void pdg::DataAccessAnalysis::computeDataAccessForTree(Tree *tree, bool isRet)
{
  TreeNode *rootNode = tree->getRootNode();
  assert(rootNode != nullptr && "cannot compute access info for empty tree!");
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);
  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    computeDataAccessForTreeNode(*currentNode, false, isRet);
    for (auto childNode : currentNode->getChildNodes())
    {
      nodeQueue.push(childNode);
    }
  }
}

void pdg::DataAccessAnalysis::computeDataAccessForGlobalTree(Tree *tree)
{
  TreeNode *rootNode = tree->getRootNode();
  assert(rootNode != nullptr && "cannot compute access info for empty tree!");
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);
  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    bool is_accessed_in_driver = false;
    for (auto addrVar : currentNode->getAddrVars())
    {
      if (Instruction *i = dyn_cast<Instruction>(addrVar))
      {
        auto func = i->getFunction();
        if (_SDA->isDriverFunc(*func))
        {
          is_accessed_in_driver = true;
          break;
        }
      }
    }

    if (!is_accessed_in_driver)
      continue;

    computeDataAccessForTreeNode(*currentNode, true);
    for (auto childNode : currentNode->getChildNodes())
    {
      nodeQueue.push(childNode);
    }
  }
}

void pdg::DataAccessAnalysis::computeDataAccessForFuncArgs(Function &F)
{
  // errs() << "compute intra for func: " << F.getName() << "\n";
  auto func_wrapper_map = _PDG->getFuncWrapperMap();
  if (func_wrapper_map.find(&F) == func_wrapper_map.end())
    return;
  FunctionWrapper *fw = func_wrapper_map[&F];
  // compute for return value access info
  auto argRetTree = fw->getRetFormalInTree();
  computeDataAccessForTree(argRetTree, true);
  // compute arg access info
  auto argTreeMap = fw->getArgFormalInTreeMap();
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    Tree *argTree = iter->second;
    computeDataAccessForTree(argTree);
  }
}

/*
Four cases:
1. pointer to simple type
2. simple type
3. pointer to aggregate type
4. aggregate type
*/
/*
This function takes a tree node as input, and then generate the IDL for this node.
If a node is a struct or union, then the code would generate a projection for this struct, based on it's fields information
*/
void pdg::DataAccessAnalysis::generateIDLFromTreeNode(TreeNode &treeNode, raw_string_ostream &fieldsProjectionStr, raw_string_ostream &nestedStructProjStr, std::queue<TreeNode *> &nodeQueue, std::string indentLevel, std::string parentStructTypeName, bool isRet)
{
  DIType *nodeDt = treeNode.getDIType();
  assert(nodeDt != nullptr && "cannot generate IDL for node with null DIType\n");
  std::string root_di_type_name = dbgutils::getSourceLevelTypeName(*nodeDt);
  std::string root_di_type_name_raw = dbgutils::getSourceLevelTypeName(*nodeDt, true);
  DIType *nodeLowestDt = dbgutils::getLowestDIType(*nodeDt);

  if (!nodeLowestDt || !dbgutils::isProjectableType(*nodeLowestDt))
    return;

  auto func = treeNode.getFunc();
  auto funcWrapper = _PDG->getFuncWrapper(*func);
  // generate idl for each field
  for (auto childNode : treeNode.getChildNodes())
  {
    DIType *field_di_type = childNode->getDIType();
    if (!field_di_type) // void retrun value etc
      continue;
    DIType *field_lowest_di_type = dbgutils::getLowestDIType(*field_di_type);
    std::string field_lowest_di_type_name = "";
    if (field_lowest_di_type != nullptr)
      field_lowest_di_type_name = dbgutils::getSourceLevelTypeName(*field_lowest_di_type, true);

    auto field_var_name = dbgutils::getSourceLevelVariableName(*field_di_type);
    auto field_type_name = dbgutils::getSourceLevelTypeName(*field_di_type, true);

    // check for access tags, if none, no need to put this field in projection
    bool is_func_ptr_type = dbgutils::isFuncPointerType(*field_di_type);
    if (childNode->getAccessTags().size() == 0 && !is_func_ptr_type)
      continue;

    std::string fieldId = pdgutils::computeTreeNodeID(*childNode);
    bool is_global_func_op_struct = (_SDA->isGlobalOpStruct(field_lowest_di_type_name));
    // check for shared fields
    auto global_struct_di_type_names = _SDA->getGlobalStructDITypeNames();
    // bool isGlobalStructField = (global_struct_di_type_names.find(root_di_type_name) != global_struct_di_type_names.end());
    /* 1. filter out private fields
       2. overapproximiate for function pointer (sync all func ptr across)
       3. global struct field
       4. inferred sentiinel fields
       5. anonymous union (as shared fields only consider struct)
    */
    // if (SharedDataFlag && !_SDA->isSharedFieldID(fieldId) && !is_func_ptr_type && !isGlobalStructField && childNode->is_sentinel && field_type_name == "union")
    if (SharedDataFlag && !_SDA->isSharedFieldID(fieldId) && !is_func_ptr_type)
      continue;

    // collect shared field stat
    childNode->isShared = true;
    if (dbgutils::isPointerType(*field_di_type))
    {
      if (childNode->getChildNodes().size() > 0)
        childNode->getChildNodes()[0]->isShared = true;
    }
    // collect field access stats
    bool isDriverFunc = _SDA->isDriverFunc(*func);
    _ksplitStats->collectDataStats(*childNode, "SAFE", *func, funcWrapper->getArgIdxByFormalInTree(childNode->getTree()), isDriverFunc);
    // check cross domain RAW
    // checkCrossDomainRAWforFormalTreeNode(*childNode);
    // countControlData(*childNode);

    // opt out field
    if (EnableAnalysisStats && !_generateingIDLforGlobal)
    {
      if (childNode->getCanOptOut() == true && !is_global_func_op_struct && !is_func_ptr_type)
      {
        _ksplitStats->_fields_removed_boundary_opt += 1;
        continue;
      }
    }

    //  collect bit field stats
    auto bw = 0;
    if (field_di_type->isBitField())
      bw = field_di_type->getSizeInBits();

    field_di_type = dbgutils::stripMemberTag(*field_di_type);
    field_di_type = dbgutils::stripAttributes(*field_di_type);
    // compute access attributes
    auto annotations = inferTreeNodeAnnotations(*childNode);
    // infer may_within attribute
    // inferMayWithin(*childNode, annotations);
    // count inferred string
    // if (EnableAnalysisStats && !_generateingIDLforGlobal)
    //   _ksplitStats->collectInferredStringStats(annotations);
    // handle attribute for return value. The in attr should be eliminated if return val is not alias of arguments
    if (isRet)
    {
      auto it = annotations.find("in");
      annotations.erase(it, annotations.end());
    }

    // construct annotation string
    if (childNode->is_sentinel)
    {
      // null terminated arraies
      fieldsProjectionStr << indentLevel << "array<" << field_type_name << ", "
                            << "null> " << field_var_name << ";\n";
      nodeQueue.push(childNode);
    }
    else if (childNode->isSeqPtr() && !dbgutils::isArrayType(*field_di_type)) // leave sized array to be handled by default generation
    {
      std::string element_proj_type_str = field_lowest_di_type_name;
      if (field_lowest_di_type && dbgutils::isStructType(*field_lowest_di_type))
      {
        element_proj_type_str = "projection " + field_lowest_di_type_name;
        nodeQueue.push(childNode);
      }
      if (dbgutils::isStructPointerType(*field_di_type))
        element_proj_type_str += "*";

      fieldsProjectionStr << indentLevel << "array<" << element_proj_type_str << ", "
                            << "size_unknown> " << field_var_name << ";\n";
    }
    else if (dbgutils::isStructPointerType(*field_di_type))
    {
      if (!_SDA->isSharedStructType(field_lowest_di_type_name))
        continue;
      // handle self-reference type such as linked list
      if (field_lowest_di_type_name == root_di_type_name_raw)
      {
        fieldsProjectionStr
            << indentLevel
            << "projection " << field_lowest_di_type_name << "* "
            << field_var_name
            << ";\n";
        continue;
      }

      std::string field_name_prefix = "";
      if (_SDA->isGlobalOpStruct(field_lowest_di_type_name))
      {
        field_name_prefix = "global_";
        parentStructTypeName = "";
      }
      std::string ptr_postfix = "";
      while (!field_type_name.empty() && field_type_name.back() == '*')
      {
        ptr_postfix += "*";
        field_type_name.pop_back();
      }

      fieldsProjectionStr << indentLevel
                            << "projection "
                            << parentStructTypeName
                            << "_"
                            << field_name_prefix
                            << field_type_name
                            << ptr_postfix
                            << " "
                            << field_var_name
                            << ";\n";
      nodeQueue.push(childNode);
    }
    else if (dbgutils::isProjectableType(*field_di_type))
    {
      std::string nested_fields_str;
      raw_string_ostream nested_fields_proj(nested_fields_str);

      std::string nested_struct_str;
      raw_string_ostream field_nested_struct_proj(nested_struct_str);

      // handle nested struct
      std::string projected_container_str = "struct";
      if (dbgutils::isUnionType(*field_di_type))
      {
        projected_container_str = "union";
        // TODO: need to resolve union types (both tag and anonymous)
        // fieldsProjectionStr << indentLevel << "[anon_union]"
        //                       << "\n";
      }
      else
      {
        // for struct, generate projection for the nested struct
        generateIDLFromTreeNode(*childNode, nested_fields_proj, field_nested_struct_proj, nodeQueue, indentLevel + "\t", field_type_name, isRet);
      }

      // if (dbgutils::isUnionType(*field_di_type))
      // {
      //   if (field_var_name.empty())
      //     field_var_name = "[anon_union]";
      // }
      if (!nested_fields_proj.str().empty())
      {
        // if nested struct is global op struct, then create reference and don't generate nested struct)
        if (_SDA->isGlobalOpStruct(field_lowest_di_type_name))
        {
          if (_globalOpsFieldsMap.find(field_lowest_di_type_name) == _globalOpsFieldsMap.end())
            _globalOpsFieldsMap.insert(std::make_pair(field_lowest_di_type_name, std::set<std::string>()));

          auto accessedFieldNames = pdgutils::splitStr(nested_fields_proj.str(), ";");
          for (auto fieldName : accessedFieldNames)
          {
            _globalOpsFieldsMap[field_lowest_di_type_name].insert(fieldName);
          }
          // only produce a reference to global definition
          fieldsProjectionStr << indentLevel
                                << "projection "
                                << parentStructTypeName
                                << "_"
                                << "global_"
                                << field_type_name
                                << "* "
                                << field_var_name
                                << ";\n";
        }
        else
        {
          // if is anonymous struct/union, directly generate projection inside the current projection
          if (field_var_name.empty())
          {
            fieldsProjectionStr
                << indentLevel << "{\n"
                << nested_fields_proj.str()
                << indentLevel << "}\n";
          }
          else
          {
            // named union/struct, generate a separate projection
            field_type_name = field_var_name;
            fieldsProjectionStr << indentLevel << "projection " << field_type_name << " " << field_var_name << ";\n";
            nestedStructProjStr
                << indentLevel
                << "projection < "
                << projected_container_str << " "
                << field_type_name
                << "> " << field_type_name << " {\n"
                << nested_fields_proj.str()
                << indentLevel
                << "}\n";
          }

          nestedStructProjStr << field_nested_struct_proj.str();
        }
      }
    }
    else if (dbgutils::isFuncPointerType(*field_di_type))
    {
      std::string func_ptr_rpc_ref = parentStructTypeName + "_" + field_var_name;
      if (_exportedFuncsPtrNameMap.find(func_ptr_rpc_ref) == _exportedFuncsPtrNameMap.end())
        continue;
      std::string exported_func_name = _exportedFuncsPtrNameMap[func_ptr_rpc_ref];
      Function *called_func = _module->getFunction(exported_func_name);
      if (called_func == nullptr)
        continue;

      // if the defintion doesn't exist yet, recording the func name, the def will be genereated later
      // if (_existFuncDefs.find(exported_func_name) == _existFuncDefs.end())
      //   _existFuncDefs.insert(exported_func_name);
      // else
      //   func_ptr_rpc_ref = exported_func_name; // if exist def is found, replace the def
      fieldsProjectionStr << indentLevel << "rpc_ptr " << exported_func_name << " " << field_var_name << ";\n";
    }
    else
    {
      patchStringAnnotation(field_type_name, annotations);
      if (primitiveTyMap.find(field_type_name) != primitiveTyMap.end())
        field_type_name = primitiveTyMap[field_type_name];
      std::string annoStr = pdgutils::constructAnnoStr(annotations);
      fieldsProjectionStr << indentLevel << field_type_name << " " << annoStr << " " << field_var_name << ((bw > 0) ? (" : " + to_string(bw)) : "") << ";\n"; // consider bitfield handling
    }
  }
}

void pdg::DataAccessAnalysis::generateIDLFromGlobalVarTree(GlobalVariable &gv, Tree *tree)
{
  if (!tree)
    return;
  TreeNode *rootNode = tree->getRootNode();
  DIType *rootNodeDt = rootNode->getDIType();
  assert(rootNodeDt != nullptr && "cannot generate projection for global with null di type\n");
  DIType *rootNodeLowestDt = dbgutils::getLowestDIType(*rootNodeDt);
  // handle non-projectable types: int/float etc.
  if (!rootNodeLowestDt || !dbgutils::isProjectableType(*rootNodeLowestDt))
  {
    auto type_name = dbgutils::getSourceLevelTypeName(*rootNodeDt);
    auto var_name = gv.getName().str();
    std::string anno = "";
    std::set<AccessTag> acc_tags;
    for (auto addrVar : rootNode->getAddrVars())
    {
      for (auto user : addrVar->users())
      {
        if (Instruction *i = dyn_cast<Instruction>(user))
        {
          auto func = i->getFunction();
          if (!_SDA->isDriverFunc(*func))
            continue;
          if (LoadInst *li = dyn_cast<LoadInst>(user))
          {
            if (li->getPointerOperand() == &gv)
              acc_tags.insert(AccessTag::DATA_READ);
          }
          else if (StoreInst *si = dyn_cast<StoreInst>(user))
          {
            if (si->getPointerOperand() == &gv)
              acc_tags.insert(AccessTag::DATA_WRITE);
          }
        }
      }
    }
    // compute get/set attribute
    for (auto acc_tag : acc_tags)
    {
      if (acc_tag == AccessTag::DATA_READ)
        anno += "[get]";
      if (acc_tag == AccessTag::DATA_WRITE)
        anno += "[set]";
    }
    _idlFile << "global " << anno << " " << type_name << " " << var_name << ";\n";
  }
  else
    generateIDLFromArgTree(tree, _idlFile, false, true);
}

/*
for function F, generaete JSON object that represent the accesses to its parameters
*/
void pdg::DataAccessAnalysis::generateJSONObjectForFunc(Function &F, std::ofstream &jsonFile)
{
  FunctionWrapper *fw = getNescheckFuncWrapper(F);
  nlohmann::json rootJSONObj;
  // generate projection for each argument
  auto argTreeMap = fw->getArgFormalInTreeMap();
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    auto argTree = iter->second;
    // create json object for policy checking
    unsigned argIdx = fw->getArgIdxByFormalInTree(argTree);
    auto argDIType = argTree->getRootNode()->getDIType();
    // only compute policy for pointer type parameters
    if (argDIType && argTree && dbgutils::isPointerType(*argDIType))
    {
      auto jsonObj = generateJSONObjectFromArgTree(argTree, argIdx);
      rootJSONObj["args"].push_back(jsonObj);
    }
  }
  jsonFile << rootJSONObj.dump();
}

/*
generate JSON file for files, which contains the offset and capability
for each field address.
*/
nlohmann::json pdg::DataAccessAnalysis::generateJSONObjectFromArgTree(Tree *argTree, unsigned argIdx)
{
  // argTree->print();
  // obtain the root node 
  TreeNode *rootNode = argTree->getRootNode();
  DIType *rootNodeDt = rootNode->getDIType();
  assert(rootNodeDt && "cannot generate json object for root node without debugging info\n");
  // for each node, create a JSON object for it
  auto jsonObj = createJSONObjectForNode(*rootNode);
  jsonObj["idx"] = argIdx;
  return jsonObj;
}

nlohmann::json pdg::DataAccessAnalysis::createJSONObjectForNode(TreeNode &treeNode)
{
  // create a JSON object for a given node
  // if the node represent a struct, and it has a pointer field which points to
  // other struct, recursively build JSON object for the pointer field
  nlohmann::json jsonObj;  
  // check if this is a struct field, if so, add the offset info to the json object
  auto nodeDt = treeNode.getDIType();
  if (!nodeDt)
    return jsonObj;

  if (treeNode.isStructField())
  {
    unsigned fieldOffset = dbgutils::computeFieldOffsetInBytes(*nodeDt);
    jsonObj["offset"] = fieldOffset;
  }
  unsigned accCap = computeAccCapForNode(treeNode);
  jsonObj["cap"] = accCap;

  auto structPtrTreeNode = &treeNode;
  if (treeNode.isStructField() && dbgutils::isPointerType(*nodeDt))
    structPtrTreeNode = treeNode.getChildNodes()[0];
  // recursively build for fields if this is a struct pointer
  auto fieldLowestDt = dbgutils::getLowestDIType(*nodeDt);
  if (fieldLowestDt && dbgutils::isStructType(*fieldLowestDt))
  {
    if (structPtrTreeNode->getChildNodes().size() > 0)
    {
      auto structObjTreeNode = structPtrTreeNode->getChildNodes()[0];
      for (auto childNode : structObjTreeNode->getChildNodes())
      {
        // if (childNode->getAccessTags().size() != 0)
          jsonObj["fields"].push_back(createJSONObjectForNode(*childNode));
      }
    }
  }
  return jsonObj;
}

unsigned pdg::DataAccessAnalysis::computeAccCapForNode(TreeNode &treeNode)
{
  auto nodeAccTags = treeNode.getAccessTags();
  bool hasReadAccCap = false;
  bool hasWriteAccCap = false;
  if (nodeAccTags.find(AccessTag::DATA_READ) != nodeAccTags.end())
    hasReadAccCap = true;
  if (nodeAccTags.find(AccessTag::DATA_WRITE) != nodeAccTags.end())
    hasWriteAccCap = true;

  if (hasReadAccCap && hasWriteAccCap)
    return 3;
  if (hasReadAccCap)
    return 1;
  if (hasWriteAccCap)
    return 2;
  // no access, which is very unlikely
  return 0;
}

void pdg::DataAccessAnalysis::generateIDLFromArgTree(Tree *argTree, std::ofstream &outputFile, bool isRet, bool isGlobal)
{
  if (!argTree)
    return;
  TreeNode *rootNode = argTree->getRootNode();
  DIType *rootNodeDt = rootNode->getDIType();
  if (!rootNodeDt)
    return;
  // collect root node stats
  // _ksplitStats->_fields_field_analysis += 1;
  // _ksplitStats->_fields_shared_analysis += 1;
  // if (EnableAnalysisStats && !isGlobal)
  // {
  //   auto root_type_name = dbgutils::getSourceLevelTypeName(*rootNodeDt, true);
  // collect deep copy field stats
  auto deepCopyFieldsNum = dbgutils::computeDeepCopyFields(*rootNodeDt);
  auto deepCopyPtrNum = dbgutils::computeDeepCopyFields(*rootNodeDt, true);
  _ksplitStats->_fieldsDeepCopyNum += deepCopyFieldsNum; // transitively count the number of field
  _ksplitStats->_totalPtrNum += deepCopyPtrNum;          // transitively count the number of pointer field in this type

  DIType *rootNodeLowestDt = dbgutils::getLowestDIType(*rootNodeDt);
  if (!rootNodeLowestDt || !dbgutils::isProjectableType(*rootNodeLowestDt))
    return;
  std::queue<TreeNode *> nodeQueue;
  // generate root projection
  nodeQueue.push(rootNode);
  while (!nodeQueue.empty())
  {
    // retrive node and obtian its di type
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    TreeNode *parentNode = currentNode->getParentNode();
    DIType *nodeDt = currentNode->getDIType();
    DIType *nodeLowestDt = dbgutils::getLowestDIType(*nodeDt);
    // check if node needs projection
    if (!nodeLowestDt || !dbgutils::isProjectableType(*nodeLowestDt))
      continue;
    // no IDL generation for non-shared data type. If a type is not shared, all the sub-fields are not shared
    std::string node_lowest_di_type_name_raw = dbgutils::getSourceLevelTypeName(*nodeLowestDt, true);
    // filter out non-shared struct
    if (dbgutils::isStructType(*nodeLowestDt) && !currentNode->isRootNode() && !_SDA->isSharedStructType(node_lowest_di_type_name_raw))
      continue;
    // get the type / variable name for the pointer field
    auto projTyName = dbgutils::getSourceLevelTypeName(*nodeDt, true);
    while (projTyName.back() == '*')
    {
      projTyName.pop_back();
    }
    // for non-root node, the node must be a field. Thus, we retrive the field name through the node di type itself
    auto projVarName = dbgutils::getSourceLevelVariableName(*nodeDt);
    // for root node, the name is the variable's name. We retrive it through DILocalVar.
    if (currentNode->isRootNode())
    {
      if (currentNode->getDILocalVar() != nullptr)
      {
        // check cross domain RAW
        projVarName = dbgutils::getSourceLevelVariableName(*currentNode->getDILocalVar());
        assert(projVarName != "" && "cannot find parameter name in generateIDLFromArgTree\n");
      }
    }

    std::string s;
    raw_string_ostream fieldsProjectionStr(s);
    std::string ss;
    // nested struct or union
    raw_string_ostream nested_struct_projection_str(ss);

    // for pointer to aggregate type, retrive the child node(pointed object), and generate projection
    if (dbgutils::isPointerType(*dbgutils::stripMemberTag(*nodeDt)) && !currentNode->getChildNodes().empty())
      currentNode = currentNode->getChildNodes()[0];
    generateIDLFromTreeNode(*currentNode, fieldsProjectionStr, nested_struct_projection_str, nodeQueue, "\t\t", projTyName, isRet);
    outputFile << nested_struct_projection_str.str();
    // store encountered global ops definitions
    if (_SDA->isGlobalOpStruct(projTyName))
    {
      if (_globalOpsFieldsMap.find(projTyName) == _globalOpsFieldsMap.end())
        _globalOpsFieldsMap.insert(std::make_pair(projTyName, std::set<std::string>()));

      auto accessedFieldNames = pdgutils::splitStr(fieldsProjectionStr.str(), ";");
      for (auto fieldName : accessedFieldNames)
      {
        _globalOpsFieldsMap[projTyName].insert(fieldName);
      }
    }
    else
    {
      if (projVarName.empty())
        projVarName = projTyName;

      // parent_struct name
      std::string parentStructTypeName = "";
      if (parentNode != nullptr)
        parentStructTypeName = dbgutils::getSourceLevelTypeName(*parentNode->getDIType(), true);
      if (!parentStructTypeName.empty())
        parentStructTypeName += "_";

      // union / struct prefix generation
      std::string typePrefix = "struct";
      if (dbgutils::isUnionPointerType(*nodeDt))
        typePrefix = "union";

      std::string globalKeywordPrefix = "";
      if (isGlobal)
        globalKeywordPrefix = "global ";

      // concat ret preifx for return values
      std::string retPrefix = "";
      if (isRet)
        retPrefix = "ret_";

      outputFile << "\t"
                 << globalKeywordPrefix
                 << "projection < "
                 << typePrefix
                 << " "
                 << projTyName
                 << " > "
                 << retPrefix
                 << parentStructTypeName
                 << projTyName
                 << " {\n"
                 << fieldsProjectionStr.str()
                 << "\t}\n";
    }
  }
}

static std::list<std::string> ioremap_fns = {
    "ioremap_nocache",
    "ioremap",
    "pci_ioremap_bar",
    "pci_iomap",
};

// std::string pdg::DataAccessAnalysis::handleIoRemap(Function &F, std::string &retTyStr)
std::string handleIoRemap(Function &F, std::string &retTyStr)
{
  auto fname = F.getName().str();

  if ((std::find(ioremap_fns.begin(), ioremap_fns.end(), fname) != ioremap_fns.end()) && (retTyStr == "void*"))
  {
    // Add ioremap annotation
    return "ioremap(caller)";
  }
  return "";
}

void pdg::DataAccessAnalysis::generateRpcForFunc(Function &F, bool processExportedFunc)
{
  // need to use this wrapper to handle nescheck rewrittern funcs
  FunctionWrapper *fw = getNescheckFuncWrapper(F);
  std::string rpcStr = "";
  // generate function rpc stub
  // first generate for return value
  DIType *funcRetDt = fw->getReturnValDIType();
  std::string retTyStr = "";
  std::string retAnnoStr = "";
  // handle return type str
  if (funcRetDt != nullptr)
  {
    retTyStr = dbgutils::getSourceLevelTypeName(*funcRetDt, true);
    // TODO: swap primitive type name, should support all types in compiler in future
    if (primitiveTyMap.find(retTyStr) != primitiveTyMap.end())
      retTyStr = primitiveTyMap[retTyStr];
    if (dbgutils::isStructPointerType(*funcRetDt) || dbgutils::isStructType(*funcRetDt))
      retTyStr = "projection ret_" + retTyStr;
    auto retTreeFormalInRootNode = fw->getRetFormalInTree()->getRootNode();
    if (retTreeFormalInRootNode != nullptr)
    {
      auto retAnnotations = inferTreeNodeAnnotations(*retTreeFormalInRootNode, true);
      patchStringAnnotation(retTyStr, retAnnotations);
      retAnnoStr = pdgutils::constructAnnoStr(retAnnotations);
      // record annotations, used by ksplit collector
      retTreeFormalInRootNode->isShared = true;
      auto ioremap_ann = handleIoRemap(F, retTyStr);
      if (!ioremap_ann.empty())
      {
        retAnnotations.insert(ioremap_ann);
        retTreeFormalInRootNode->is_ioremap = true;
      }
      retTreeFormalInRootNode->annotations.insert(retAnnotations.begin(), retAnnotations.end());
    }
  }
  else
  {
    retTyStr = "void";
  }

  // determine the rpc repfix call
  // determine called func name. Need to switch to indirect call name if the function is exported
  std::string rpcPrefix = "rpc";
  std::string calleeName = F.getName().str();
  calleeName = pdgutils::getSourceFuncName(calleeName);
  if (_existFuncDefs.find(calleeName) != _existFuncDefs.end())
  {
    errs() << "[WARNING]: found duplicate func definition " << calleeName << "\n";
    return;
  }
  _existFuncDefs.insert(calleeName);
  // handle exported func called from kernel to driver. Switch name and rpc prefix
  if (!_SDA->isKernelFunc(calleeName))
  {
    rpcPrefix = "rpc_ptr";
  }
  // indirect call from kernel  to driver
  if (_driverExportedFuncSymbols.find(calleeName) != _driverExportedFuncSymbols.end())
  {
    rpcPrefix = "rpc_export";
  }

  // if string annotation is found, change the type name to string
  rpcStr = rpcPrefix + " " + retTyStr + " " + retAnnoStr + " " + calleeName + "( ";
  auto arg_list = fw->getArgList();
  for (unsigned i = 0; i < arg_list.size(); i++)
  {
    auto arg = arg_list[i];
    auto formalInTree = fw->getArgFormalInTree(*arg);
    if (!formalInTree)
      continue;
    TreeNode *rootNode = formalInTree->getRootNode();
    rootNode->isShared = true;
    // countControlData(*rootNode);
    // _ksplitStats->increaseParamNum();
    DIType *argDt = rootNode->getDIType();
    if (dbgutils::isPointerType(*argDt))
      rootNode->getChildNodes()[0]->isShared = true;
    DIType *argLowestDt = dbgutils::getLowestDIType(*argDt);
    auto arg_name = dbgutils::getSourceLevelVariableName(*rootNode->getDILocalVar());
    auto argTyName = dbgutils::getSourceLevelTypeName(*argDt, true);
    std::string argLowestTyName = "";
    if (argLowestDt != nullptr)
      argLowestTyName = dbgutils::getSourceLevelTypeName(*argLowestDt, true);
    if (dbgutils::isStructPointerType(*argDt) || dbgutils::isUnionPointerType(*argDt))
    {
      if (_SDA->isGlobalOpStruct(argLowestTyName))
      {
        argTyName = std::string("projection ") + std::string("_global_") + argLowestTyName;
      }
      else
      {
        argTyName = "projection " + argTyName;
      }
    }
    else if (dbgutils::isFuncPointerType(*argDt))
    {
      argTyName = "rpc_ptr";
      if (_exportedFuncsPtrNameMap.find(arg_name) != _exportedFuncsPtrNameMap.end())
        argTyName = argTyName + " " + _exportedFuncsPtrNameMap[arg_name];
      else
        argTyName = argTyName + " " + arg_name;
      // auto pointed_funcs = getPointedFuncAtArgIdx(F, i);
      // TODO: for function pointer that are not defined by global structs, we need to handle differently.
      // need to reason about call sites to construct the function definition
    }

    auto annotations = inferTreeNodeAnnotations(*rootNode);
    inferUserAnnotation(*rootNode, annotations);

    // store annotations in the root node, used by ksplit stats collector
    rootNode->annotations.insert(annotations.begin(), annotations.end());

    // if string annotation is found, change the type name to string
    patchStringAnnotation(argTyName, annotations);
    std::string annoStr = pdgutils::constructAnnoStr(annotations);
    // TODO: swap unsupported type name, should support in the IDL compiler in future
    if (primitiveTyMap.find(argTyName) != primitiveTyMap.end())
      argTyName = primitiveTyMap[argTyName];

    // rearrange the location for pointer symbol *
    std::string ptr_postfix = "";
    while (!argTyName.empty() && argTyName.back() == '*')
    {
      ptr_postfix += "*";
      argTyName.pop_back();
    }
    rpcStr = rpcStr + argTyName + " " + annoStr + " " + ptr_postfix + arg_name;

    if (i != arg_list.size() - 1)
      rpcStr += ", ";
  }
  rpcStr += " ) ";
  _idlFile << rpcStr;
}

bool pdg::DataAccessAnalysis::isExportedFunc(Function &F)
{
  for (auto p : _exportedFuncsPtrNameMap)
  {
    // need to consider nesCheck rewrite
    std::string funcName = p.second;
    std::string nescheck_func_name = funcName + "_nesCheck";
    if (nescheck_func_name == F.getName().str() || funcName == F.getName().str())
      return true;
  }
  return false;
}

void pdg::DataAccessAnalysis::generateIDLForFunc(Function &F, bool processingExportedFunc)
{
  _currentProcessingFunc = F.getName().str();
  // auto func_wrapper_map = _PDG->getFuncWrapperMap();
  // auto func_iter = func_wrapper_map.find(&F);
  // assert(func_iter != func_wrapper_map.end() && "no function wrapper found (IDL-GEN)!");
  // auto fw = func_iter->second;
  FunctionWrapper *fw = getNescheckFuncWrapper(F);
  // process exported funcs later in special manner because of syntax requirement
  if (isExportedFunc(F) && !processingExportedFunc)
  {
    _kernelFuncsRegisteredWithFuncPtr.insert(&F);
    return;
  }
  generateRpcForFunc(F, processingExportedFunc);
  // errs() << "generating idl for: " << F.getName() << "\n";
  _idlFile << "{\n";
  // generate projection for return value
  auto retArgTree = fw->getRetFormalInTree();
  if (fw->getReturnValDIType() != nullptr)
  {
    generateIDLFromArgTree(retArgTree, _idlFile, true, false);
  }
  // generate projection for each argument
  auto argTreeMap = fw->getArgFormalInTreeMap();
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    auto argTree = iter->second;
    generateIDLFromArgTree(argTree, _idlFile, false, false);
  }
  _idlFile << "}\n";
}

void pdg::DataAccessAnalysis::inferMayWithin(TreeNode &treeNode, std::set<std::string> &annoStr)
{
  // check the treeNode's address variable against other nodes address variables, and determine whether it alias with other nodes
  DIType *cur_node_di_type = treeNode.getDIType();
  if (!cur_node_di_type)
    return;
  if (!dbgutils::isPointerType(*cur_node_di_type))
    return;
  auto parentNode = treeNode.getParentNode();
  if (!parentNode)
    return;

  auto currentNodeAddrVars = treeNode.getAddrVars();
  for (auto childNode : parentNode->getChildNodes())
  {
    if (childNode == &treeNode)
      continue;
    auto fieldName = dbgutils::getSourceLevelVariableName(*childNode->getDIType());
    auto childNodeDt = childNode->getDIType();
    if (!dbgutils::isPointerType(*childNodeDt))
      continue;
    auto fieldId = pdgutils::computeTreeNodeID(*childNode);
    if (!_SDA->isSharedFieldID(fieldId))
      continue;
    auto childNodeAddrVars = childNode->getAddrVars();
    // if the address variable overlap with each other, then print within warning
    for (auto currentNodeAddrVar : currentNodeAddrVars)
    {
      if (childNodeAddrVars.find(currentNodeAddrVar) != childNodeAddrVars.end())
      {
        // construct within string
        std::string may_within_anno = "may_within<self->" + fieldName + ", " + "size>";
        annoStr.insert(may_within_anno);
        break;
      }
    }
  }
}

void pdg::DataAccessAnalysis::inferUserAnnotation(TreeNode &treeNode, std::set<std::string> &annotations)
{
  // get all alias of the argument
  std::set<EdgeType> edgeTypes = {EdgeType::PARAMETER_IN, EdgeType::DATA_ALIAS};
  auto aliasNodes = _PDG->findNodesReachedByEdges(treeNode, edgeTypes);
  for (auto node : aliasNodes)
  {
    auto outNeighborNodes = node->getOutNeighbors();
    for (auto neighborNode : outNeighborNodes)
    {
      auto val = neighborNode->getValue();
      if (val == nullptr)
        continue;
      if (CallInst *ci = dyn_cast<CallInst>(val))
      {
        auto called_func = pdgutils::getCalledFunc(*ci);
        if (called_func == nullptr)
          continue;
        std::string calleeName = called_func->getName();
        calleeName = pdgutils::stripFuncNameVersionNumber(calleeName);
        if (calleeName == "_copy_from_user" || calleeName == "_copy_to_user")
        {
          std::string user_anno = "user";
          Value *copy_bytes_size = ci->getArgOperand(2);
          if (TruncInst *ti = dyn_cast<TruncInst>(copy_bytes_size))
          {
            Value *trunced_val = ti->getOperand(0);
            if (LoadInst *li = dyn_cast<LoadInst>(trunced_val))
            {
              Value *value_store_reg = li->getPointerOperand();
              for (auto user : value_store_reg->users())
              {
                if (StoreInst *si = dyn_cast<StoreInst>(user))
                {
                  if (ConstantInt *ci = dyn_cast<ConstantInt>(si->getValueOperand()))
                  {
                    unsigned bytes_size = ci->getZExtValue();
                    user_anno = user_anno + "<{{" + std::to_string(bytes_size) + "}}>";
                  }
                }
              }
            }
          }
          else
          {
            user_anno = user_anno + "<size_unknown>";
          }
          annotations.insert(user_anno);
          treeNode.isUser = true;
        }
      }
      // checking for bounds because this field is used in pointer arithmetic
      // if (LoadInst *li = dyn_cast<LoadInst>(val))
      // {
      //   for (auto user : li->users())
      //   {
      //     if (isa<CastInst>(user))
      //       annotations.insert("[bound_check]");
      //   }
      // }
      // if (isa<CastInst>(val))
      //   annotations.insert("[bound_check]");
    }
  }
}

std::set<std::string> pdg::DataAccessAnalysis::inferTreeNodeAnnotations(TreeNode &treeNode, bool isRet)
{
  std::set<std::string> annotations;
  if (treeNode.isRootNode())
  {
    // infer string annotation
    DIType *tree_dt = treeNode.getDIType();
    if (tree_dt)
    {
      // check if the node is directly used in some string operations
      if (dbgutils::isCharPointer(*tree_dt))
      {
        if (_SDA->isFieldUsedInStringOps(treeNode))
        {
          annotations.insert("string");
          treeNode.isString = true;
        }
      }
    }
    // infer unused attribute
    if (treeNode.getAccessTags().size() == 0)
    {
      bool isUsed = false;
      for (auto addrVar : treeNode.getAddrVars())
      {
        if (!addrVar->user_empty())
        {
          isUsed = true;
          break;
        }
      }
      if (!isUsed)
        annotations.insert("unused");
    }
  }
  // for field, also check for global use info for this field
  else
  {
    auto fieldId = pdgutils::computeTreeNodeID(treeNode);
    if (_SDA->isStringFieldID(fieldId))
    {
      annotations.insert("string");
      treeNode.isString = true;
    }
  }

  if (!isRet)
  {
    auto acc_tags = treeNode.getAccessTags();
    for (auto acc_tag : acc_tags)
    {
      if (acc_tag == AccessTag::DATA_READ)
        annotations.insert("in");
      else if (acc_tag == AccessTag::DATA_WRITE)
        annotations.insert("out");
    }
  }
  return annotations;
}

/*
if an argument is a funciton pointer, check the call sites of the function
and return all the possible functions pointed by the argument
*/
std::set<Function *> pdg::DataAccessAnalysis::getPointedFuncAtArgIdx(Function &F, unsigned argIdx)
{
  std::set<Function *> ret;
  for (auto user : F.users())
  {
    if (CallInst *ci = dyn_cast<CallInst>(user))
    {
      auto funcPtrArg = ci->getArgOperand(argIdx);
      assert(funcPtrArg != nullptr && "cannot get pointed func at arg idx!\n");
      if (Function *f = dyn_cast<Function>(funcPtrArg))
        ret.insert(f);
    }
  }
  return ret;
}

bool pdg::DataAccessAnalysis::globalVarHasAccessInDriver(GlobalVariable &gv)
{
  for (auto user : gv.users())
  {
    if (Instruction *i = dyn_cast<Instruction>(user))
    {
      auto func = i->getFunction();
      if (_SDA->isDriverFunc(*func))
        return true;
    }
  }
  return false;
}

bool pdg::DataAccessAnalysis::isDriverDefinedGlobal(GlobalVariable &gv)
{
  auto global_var_name = gv.getName().str();
  if (_driverDefGlobalVarNames.find(global_var_name) != _driverDefGlobalVarNames.end())
    return true;
  return false;
}

pdg::FunctionWrapper *pdg::DataAccessAnalysis::getNescheckFuncWrapper(Function &F)
{
  // get function name
  std::string funcName = F.getName().str();
  // obtain wrapper map
  auto func_wrapper_map = _PDG->getFuncWrapperMap();
  // strip _nesCheck postfix
  auto pos = funcName.find("_nesCheck");
  if (pos != std::string::npos)
  {
    funcName = funcName.substr(0, pos);
    Function *f = _module->getFunction(funcName);
    auto func_iter = func_wrapper_map.find(f);
    assert(func_iter != func_wrapper_map.end() && "no function wrapper found (IDL-GEN)!");
    return func_iter->second;
  }
  // if not end with _nesCheck, return the wrapper for the origin func
  return func_wrapper_map[&F];
}

// bool pdg::DataAccessAnalysis::containerHasSharedFieldsAccessed(BitCastInst &bci, std::string structTyName)
// {
//   auto bci_node = _PDG->getNode(bci);
//   assert(bci_node != nullptr && "cannot find node for container_of bitcast inst\n");
//   auto aliasNodes = bci_node->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
//   aliasNodes.insert(bci_node);
//   for (auto aliasNode : aliasNodes)
//   {
//     auto alias_val = aliasNode->getValue();
//     for (auto out_neighbor : aliasNode->getOutNeighbors())
//     {
//       auto out_neighbor_val = out_neighbor->getValue();
//       if (out_neighbor_val == nullptr)
//         continue;
//       // check for fields accesses
//       if (isa<GetElementPtrInst>(out_neighbor_val))
//       {
//         auto dt = out_neighbor->getDIType();
//         // if (container_dt == nullptr || dt == nullptr)
//         //   continue;
//         auto field_type_name = dbgutils::getSourceLevelVariableName(*dt);
//         std::string id = structTyName + field_type_name;
//         if (_SDA->isSharedStructType(id))
//           return true;
//       }
//     }
//   }
//   return false;
// }

void pdg::DataAccessAnalysis::constructGlobalOpStructStr()
{
  for (auto pair : _globalOpsFieldsMap)
  {
    std::string projTyName = pair.first;
    std::string proj_field_str = "";
    for (auto fieldName : pair.second)
    {
      proj_field_str = proj_field_str + "\t" + fieldName + ";\n";
    }
    std::string proj_str = "projection < struct " + projTyName + " > " + "_global_" + projTyName + " {\n" + proj_field_str + "}\n";
    _opsStructProjStr += proj_str;
  }
}

void pdg::DataAccessAnalysis::computeContainerOfLocs(Function &F)
{
  for (auto instIter = inst_begin(F); instIter != inst_end(F); ++instIter)
  {
    // find gep that has negative offset
    if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(&*instIter))
    {
      int gep_access_offset = pdgutils::getGEPAccessFieldOffset(*gep);
      if (gep_access_offset >= 0)
        continue;
      // check the next instruction
      // errs() << "container of location: " << F.getName() << "\n";
      if (EnableAnalysisStats)
        _ksplitStats->_total_containerof++;
      Instruction *next_i = gep->getNextNonDebugInstruction();
      if (BitCastInst *bci = dyn_cast<BitCastInst>(next_i))
      {
        bool isSharedType = false;
        std::string structTyName = "";
        Type *cast_type = bci->getType();
        if (cast_type->isPointerTy())
        {
          std::string str;
          llvm::raw_string_ostream(str) << *cast_type;
          auto strs = pdgutils::splitStr(str, ".");
          for (auto s : strs)
          {
            if (_SDA->isSharedStructType(s))
            {
              isSharedType = true;
              structTyName = str;
              _ksplitStats->_shared_containerof++;
            }
          }
        }

        // auto instNode = _PDG->getNode(*bci);
        // if (instNode != nullptr)
        // {
        //   if (isSharedType)
        //   {
        //     if (!containerHasSharedFieldsAccessed(*bci, structTyName))
        //       continue;
        //     _containerofInsts.insert(bci);
        //     if (EnableAnalysisStats)
        //     {
        //       _ksplitStats->_shared_containerof++;
        //       // if (DEBUG)
        //       //   errs() << "shared container_of: " << F.getName() << " - " << di_type_name << " - " << *bci << "\n";
        //     }
        //   }
        // }
      }
    }
  }
}

void pdg::DataAccessAnalysis::logSkbFieldStats(TreeNode &skb_root_node)
{
  Function *current_func = skb_root_node.getFunc();
  assert(current_func != nullptr && "cannot log skb without current function information\n");
  errs() << "logging skb stats in function: " << current_func->getName() << "\n";
  // log deep copy fields using debug info
  DIType *dt = skb_root_node.getDIType();
  unsigned num_deep_copy_fields = dbgutils::computeDeepCopyFields(*dt);
  errs() << "skb deep copy fields: " << num_deep_copy_fields << "\n";
  // Collect Filds related stats with bfs
  std::queue<TreeNode *> nodeQueue;
  // don't process the tree node, start with all the fields
  unsigned accessed_fields = 0;
  unsigned accessed_shared_fields = 0;
  for (auto childNode : skb_root_node.getChildNodes())
  {
    nodeQueue.push(childNode);
  }
  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    for (auto childNode : currentNode->getChildNodes())
    {
      nodeQueue.push(childNode);
    }
    // accumulate stats for fields
    if (currentNode->isStructMember())
    {
      if (!currentNode->getAccessTags().empty())
      {
        accessed_fields++; // accumulate accessed fields
        auto fieldId = pdgutils::computeTreeNodeID(*currentNode);
        if (_SDA->isSharedFieldID(fieldId))
          accessed_shared_fields++; // accumulate accessed shared fields
      }
    }
  }
  errs() << "skb accessed fields: " << accessed_fields << "\n";
  errs() << "skb shared accessed fields: " << accessed_shared_fields << "\n";
}

// void pdg::DataAccessAnalysis::printContainerOfStats()
// {
//   errs() << " ============== container of stats =============\n";
//   errs() << "num of container_of access shared states: " << _containerofInsts.size() << "\n";
//   for (auto i : _containerofInsts)
//   {
//     errs() << "container_of: " << i->getFunction()->getName() << " -- " << *i << "\n";
//   }
//   errs() << " ===============================================\n";
// }

pdg::DomainTag pdg::DataAccessAnalysis::computeFuncDomainTag(Function &F)
{
  if (_SDA->isDriverFunc(F))
    return DomainTag::DRIVER_DOMAIN;
  else
    return DomainTag::KERNEL_DOMAIN;
}

std::string pdg::DataAccessAnalysis::getExportedFuncPtrName(std::string funcName)
{
  for (auto p : _exportedFuncsPtrNameMap)
  {
    if (p.second == funcName)
      return p.first;
  }
  return funcName;
}

bool pdg::DataAccessAnalysis::isUsedInBranchStat(Node &valNode)
{
  // check def-use edges to see if the value is used in any branchstatement
  // normally this step loads value
  auto def_use_neighbors = valNode.getOutNeighborsWithDepType(EdgeType::DATA_DEF_USE);
  for (auto out_neighbor : def_use_neighbors)
  {
    if (!out_neighbor->getValue())
      continue;
    // if (!isa<LoadInst>(out_neighbor->getValue()))
    //   continue;
    // get neighbors that can be reached in two hops, then decide whther this value is directly used in branch
    auto potential_branch_cand = out_neighbor->getOutNeighborsWithDepType(EdgeType::DATA_DEF_USE);
    for (auto n : potential_branch_cand)
    {
      auto val = n->getValue();
      if (!val)
        continue;
      if (isa<BranchInst>(val) || isa<BranchInst>(out_neighbor->getValue()))
        return true;
    }
  }
  return false;
}

std::map<unsigned, unsigned> pdg::DataAccessAnalysis::getFieldOffsetAccessMap(TreeNode &paramRootNode)
{
  std::map<unsigned, unsigned> fieldOffsetAccMap;
  auto rootNodeDIType = paramRootNode.getDIType();
  if (!dbgutils::isStructPointerType(*rootNodeDIType))
  {
    return fieldOffsetAccMap;
  }

  auto paramObjNode = paramRootNode.getChildNodes().front();
  // don't process the tree node, start with all the fields
  for (auto childNode : paramObjNode->getChildNodes())
  {
    auto fieldNodeDIType = childNode->getDIType();
    // compute field offset
    auto fieldOffset = fieldNodeDIType->getOffsetInBits() / 8;
    // compute field access info
    auto accTags = childNode->getAccessTags();
    auto accTagsSize = accTags.size();
    if (accTagsSize == 0)
      fieldOffsetAccMap[fieldOffset] = 0;
    else if (accTagsSize == 1)
    {
      if (accTags.find(AccessTag::DATA_READ) != accTags.end())
        fieldOffsetAccMap[fieldOffset] = 1;
      else if (accTags.find(AccessTag::DATA_WRITE) != accTags.end())
        fieldOffsetAccMap[fieldOffset] = 2;
    }
    else
    {
      fieldOffsetAccMap[fieldOffset] = 3;
    }
  }
  return fieldOffsetAccMap;
}

void pdg::DataAccessAnalysis::dumpFieldOffsetAccessMapToFile(TreeNode &paramRootNode, std::string fileName)
{
  auto fieldOffsetAccessMap = getFieldOffsetAccessMap(paramRootNode);
  std::ofstream ofs(fileName);
  for (auto p : fieldOffsetAccessMap)
  {
    // output format: field_offset, access_cap
    ofs << p.first << "," << p.second << "\n";
  }
  ofs.close();
}

static RegisterPass<pdg::DataAccessAnalysis>
    DAA("daa", "Data Access Analysis Pass", false, true);