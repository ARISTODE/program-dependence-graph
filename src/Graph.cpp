// #include "Graph.hh"
#include "PDGCallGraph.hh"

using namespace llvm;

static std::set<std::string> KernelAllocators = {
    "kzalloc",
    "kmalloc",
    "kvzalloc",
    "vzalloc",
    "__kmalloc",
    "alloc_netdev",
    "alloc_netdev_mqs",
    "alloc_etherdev_mqs"
};

static std::set<std::string> KernelDeAllocators = {
    "kfree"
};

// Generic Graph
bool pdg::GenericGraph::hasNode(Value &v)
{
  return (_valNodeMap.find(&v) != _valNodeMap.end());
}

pdg::Node *pdg::GenericGraph::getNode(Value &v)
{
  if (!hasNode(v))
    return nullptr;
  return _valNodeMap[&v];
}

// ===== Graph Traversal =====

// DFS search
bool pdg::GenericGraph::canReach(pdg::Node &src, pdg::Node &dst)
{
  std::set<EdgeType> edgeTypes;
  if (canReach(src, dst, edgeTypes))
    return true;
  return false;
}

bool pdg::GenericGraph::canReach(pdg::Node &src, pdg::Node &dst, std::set<EdgeType> &exclude_edge_types)
{
  // self-reachability
  if (&src == &dst)
    return true;

  std::set<Node *> visited;
  std::stack<Node *> nodeQueue;
  nodeQueue.push(&src);

  while (!nodeQueue.empty())
  {
    auto currentNode = nodeQueue.top();
    nodeQueue.pop();
    if (currentNode == nullptr)
      continue;
    if (visited.find(currentNode) != visited.end())
      continue;
    visited.insert(currentNode);
    if (currentNode == &dst)
      return true;
    for (auto out_edge : currentNode->getOutEdgeSet())
    {
      // exclude path
      if (exclude_edge_types.find(out_edge->getEdgeType()) != exclude_edge_types.end())
        continue;
      nodeQueue.push(out_edge->getDstNode());
    }
  }
  return false;
}

std::set<pdg::Node *> pdg::GenericGraph::findNodesReachedByEdge(pdg::Node &src, EdgeType edgeTy)
{
  std::set<Node *> ret;
  std::queue<Node *> nodeQueue;
  nodeQueue.push(&src);
  std::set<Node*> visited;
  while (!nodeQueue.empty())
  {
    Node *currentNode = nodeQueue.front();
    nodeQueue.pop();
    if (visited.find(currentNode) != visited.end())
      continue;
    visited.insert(currentNode);
    ret.insert(currentNode);
    for (auto out_edge : currentNode->getOutEdgeSet())
    {
      if (edgeTy != out_edge->getEdgeType())
        continue;
      nodeQueue.push(out_edge->getDstNode());
    }
  }
  return ret;
}

std::set<pdg::Node *> pdg::GenericGraph::findNodesReachedByEdges(pdg::Node &src, std::set<EdgeType> &edgeTypes, bool isBackward)
{
  std::set<Node *> ret;
  std::queue<Node *> nodeQueue;
  nodeQueue.push(&src);
  std::set<Node *> visited;
  while (!nodeQueue.empty())
  {
    Node *currentNode = nodeQueue.front();
    nodeQueue.pop();
    if (visited.find(currentNode) != visited.end())
      continue;
    visited.insert(currentNode);
    ret.insert(currentNode);
    Node::EdgeSet edgeSet;
    if (isBackward)
      edgeSet = currentNode->getInEdgeSet();
    else 
      edgeSet = currentNode->getOutEdgeSet();
    for (auto edge : edgeSet)
    {
      if (edgeTypes.find(edge->getEdgeType()) == edgeTypes.end())
        continue;
      if (isBackward)
        nodeQueue.push(edge->getSrcNode());
      else
        nodeQueue.push(edge->getDstNode());
    }
  }
  return ret;
}

// PDG Specific
void pdg::ProgramGraph::build(Module &M)
{
  // build node for global variables
  for (auto &global_var : M.getGlobalList())
  {
    auto global_var_type = global_var.getType();
    if (global_var.isConstant())
      continue;
    // if (!global_var_type->isPointerTy() && !global_var_type->isStructTy())
    //   continue;
    DIType* global_var_di_type = dbgutils::getGlobalVarDIType(global_var);
    if (global_var_di_type == nullptr)
      continue;
    TreeNode * n = new TreeNode(global_var, GraphNodeType::GLOBAL_VAR);
    // add addr var for global
    n->addAddrVar(global_var);

    _valNodeMap.insert(std::pair<Value *, Node *>(&global_var, n));
    addNode(*n);
    Tree* global_tree = new Tree(global_var);
    global_tree->setRootNode(*n);
    global_tree->build();
    _global_var_tree_map.insert(std::make_pair(&global_var, global_tree));
  }

  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    FunctionWrapper *func_w = new FunctionWrapper(&F);
    for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
    {
      Node *n = new Node(*instIter, GraphNodeType::INST);
      _valNodeMap.insert(std::pair<Value *, Node *>(&*instIter, n));
      func_w->addInst(*instIter);
      addNode(*n);
      if (CallInst *ci = dyn_cast<CallInst>(&*instIter))
      {
        auto called_func = pdgutils::getCalledFunc(*ci);
        if (called_func != nullptr)
        {
          std::string calleeName = called_func->getName().str();
          calleeName = pdgutils::stripFuncNameVersionNumber(calleeName);
        }
      }
    }
    func_w->buildFormalTreeForArgs();
    func_w->buildFormalTreesForRetVal();
    addFormalTreeNodesToGraph(*func_w);
    addNode(*func_w->getEntryNode());
    _func_wrapper_map.insert(std::make_pair(&F, func_w));
  }

  // build call graph
  auto &call_g = PDGCallGraph::getInstance();
  if (!call_g.isBuild())
    call_g.build(M);
  // handle call sites
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    if (!hasFuncWrapper(F))
      continue;
    
    FunctionWrapper *func_w = getFuncWrapper(F);
    auto call_insts = func_w->getCallInsts();
    for (auto ci : call_insts)
    {
      auto called_func = pdgutils::getCalledFunc(*ci);
      if (called_func == nullptr)
      {
        // handle indirect call
        auto ind_call_candidates = call_g.getIndirectCallCandidates(*ci, M);
        if (ind_call_candidates.size() > 0)
          called_func = *ind_call_candidates.begin();
        // continue;
      }
      if (!hasFuncWrapper(*called_func))
        continue;
      CallWrapper *cw = new CallWrapper(*ci);
      FunctionWrapper *callee_fw = getFuncWrapper(*called_func);
      cw->buildActualTreeForArgs(*callee_fw);
      cw->buildActualTreesForRetVal(*callee_fw);
      _call_wrapper_map.insert(std::make_pair(ci, cw));
    }
  }
  _isBuild = true;
}

void pdg::ProgramGraph::bindDITypeToNodes(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    FunctionWrapper *fw = _func_wrapper_map[&F];
    auto dbgDeclareInsts = fw->getDbgDeclareInsts();
    // bind ditype to the top-level pointer (alloca)
    for (auto dbgInst : dbgDeclareInsts)
    {
      auto addr = dbgInst->getVariableLocation();
      Node *addr_node = getNode(*addr);
      if (!addr_node)
        continue;
      auto DLV = dbgInst->getVariable(); // di local variable instance
      assert(DLV != nullptr && "cannot find DILocalVariable Node for computing DIType");
      DIType *var_di_type = DLV->getType();
      assert(var_di_type != nullptr && "cannot bind nullptr ditype to node!");
      addr_node->setDIType(*var_di_type);
      _node_di_type_map.insert(std::make_pair(addr_node, var_di_type));
    }

    for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
    {
      Instruction &i = *instIter;
      Node* n = getNode(i);
      assert(n != nullptr && "cannot compute node di type for null node!\n");
      DIType* nodeDt = computeNodeDIType(*n);
      n->setDIType(*nodeDt);
    }
  }

  for (auto &global_var : M.getGlobalList())
  {
    Node *global_node = getNode(global_var);
    if (global_node != nullptr)
    {
      auto dt = dbgutils::getGlobalVarDIType(global_var);
      global_node->setDIType(*dt);
    }
  }
}

DIType *pdg::ProgramGraph::computeNodeDIType(Node &n)
{
  // local variable 
  Function* func = n.getFunc();
  if (!func)
    return nullptr;
  Value *val = n.getValue();
  if (!val)
    return nullptr;

  // alloc inst
  if (isa<AllocaInst>(val))
  {
    // this is used to borrow di type form other struct poiter types
    if (n.getDIType() == nullptr)
    {
      for (auto instIter = inst_begin(func); instIter != inst_end(func); ++instIter)
      {
        if (&*instIter == val)
          continue;
        if (AllocaInst *ai = dyn_cast<AllocaInst>(&*instIter))
        {
          if (ai->getType() == val->getType())
          {
            Node *alloca_n = getNode(*ai);
            DIType* alloca_node_dt = alloca_n->getDIType();
            if (alloca_node_dt != nullptr && dbgutils::isStructPointerType(*alloca_node_dt))
              return alloca_node_dt;
          }
        }
      }
    }
    else
    {
      return n.getDIType();
    }
  }
  // load inst
  if (LoadInst *li = dyn_cast<LoadInst>(val))
  {
    if (Instruction *load_addr = dyn_cast<Instruction>(li->getPointerOperand()))
    {
      Node* load_addr_node = getNode(*load_addr);
      if (!load_addr_node)
        return nullptr;
      DIType* load_addr_di_type = load_addr_node->getDIType();
      if (!load_addr_di_type)
        return nullptr;
      // DIType* retDIType = DIUtils::stripAttributes(sourceInstDIType);
      DIType *loaded_val_di_type = dbgutils::getBaseDIType(*load_addr_di_type);
      if (loaded_val_di_type != nullptr)
        return dbgutils::stripAttributes(*loaded_val_di_type);
      return loaded_val_di_type;
    }

    if (GlobalVariable *gv = dyn_cast<GlobalVariable>(li->getPointerOperand()))
    {
      DIType *global_var_di_type = dbgutils::getGlobalVarDIType(*gv);
      if (!global_var_di_type)
        return nullptr;
      // auto global_type = gv->getType();
      return dbgutils::getBaseDIType(*global_var_di_type);
    }
  }

  // store inst
  if (StoreInst *st = dyn_cast<StoreInst>(val))
  {
    Value* value_operand = st->getValueOperand();
    Value* pointer_operand = st->getPointerOperand();
    Node* value_op_node = getNode(*value_operand);
    Node* ptr_op_node = getNode(*pointer_operand);
    if (value_op_node == nullptr || ptr_op_node == nullptr)
      return nullptr;
    
    if (value_op_node->getDIType() != nullptr)
      return nullptr;

    DIType* ptr_op_di_type = ptr_op_node->getDIType();
    if (ptr_op_di_type == nullptr)
      return nullptr;
    DIType *value_op_di_type = dbgutils::getBaseDIType(*ptr_op_di_type);
    if (value_op_di_type == nullptr)
      return nullptr;
    value_op_di_type = dbgutils::stripAttributes(*value_op_di_type);
    value_op_node->setDIType(*value_op_di_type);
    return value_op_di_type;
  }

  // gep inst
  if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(val))
  {
    Value* baseAddr = gep->getPointerOperand();
    Node* baseAddrNode = getNode(*baseAddr);
    if (!baseAddrNode)
      return nullptr;
    DIType* baseAddrDt = baseAddrNode->getDIType();
    if (!baseAddrDt)
      return nullptr;

    DIType* baseAddrLowestDt = dbgutils::getLowestDIType(*baseAddrDt);
    if (!baseAddrLowestDt)
      return nullptr;
    if (!dbgutils::isStructType(*baseAddrLowestDt))
      return nullptr;
    // TODO: here we assume negative offset always move to the parent structure, and no other unsafe use.
    // should verify this assumption is valid.
    // if (pdgutils::getGEPAccessFieldOffset(*gep) < 0)
    //   return baseAddrLowestDt;
    if (auto dict = dyn_cast<DICompositeType>(baseAddrLowestDt))
    {
      auto di_node_arr = dict->getElements();
      for (unsigned i = 0; i < di_node_arr.size(); ++i)
      {
        DIType *fieldDt = dyn_cast<DIType>(di_node_arr[i]);
        assert(fieldDt != nullptr && "fail to retrive field di type (computeNodeDIType)");
        if (pdgutils::isGEPOffsetMatchDIOffset(*fieldDt, *gep))
          return fieldDt;
      }
    }
  }
  // cast inst
  if (CastInst *castInst = dyn_cast<CastInst>(val))
  {
    Value *castedVal = castInst->getOperand(0);
    Node* castedValNode = getNode(*castedVal);
    if (!castedValNode)
      return nullptr;
    return castedValNode->getDIType();
  }

  // default
  return nullptr;
}

void pdg::ProgramGraph::addTreeNodesToGraph(pdg::Tree &tree)
{
  TreeNode* rootNode = tree.getRootNode();
  assert(rootNode && "cannot add tree nodes to graph, nullptr root node\n");
  std::queue<TreeNode*> nodeQueue;
  nodeQueue.push(rootNode);
  while (!nodeQueue.empty())
  {
    TreeNode* currentNode = nodeQueue.front();
    nodeQueue.pop();
    addNode(*currentNode);
    for (auto childNode : currentNode->getChildNodes())
    {
      nodeQueue.push(childNode);
    }
  }
}

void pdg::ProgramGraph::addFormalTreeNodesToGraph(FunctionWrapper &func_w)
{
  for (auto arg : func_w.getArgList())
  {
    Tree* formalInTree = func_w.getArgFormalInTree(*arg);
    Tree* formalOutTree = func_w.getArgFormalOutTree(*arg);
    if (!formalInTree || !formalOutTree)
      return;
    addTreeNodesToGraph(*formalInTree);
    addTreeNodesToGraph(*formalOutTree);
  }
}
