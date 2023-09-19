// #include "Graph.hh"
#include "PDGCallGraph.hh"
#include <thread>

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
void pdg::GenericGraph::dfs(Node *currentNode, Node &dst, std::set<EdgeType> &includeEdgeTypes, std::unordered_set<Node *> &visited, std::vector<llvm::Function *> &currentPath, std::set<std::vector<llvm::Function *>> *allPaths, bool recordPath)
{
  if (currentNode == nullptr || visited.find(currentNode) != visited.end())
    return;

  visited.insert(currentNode);

  if (llvm::Function *currentFunction = currentNode->getFunc())
    currentPath.push_back(currentFunction);

  if (currentNode == &dst && recordPath)
    allPaths->insert(currentPath);
  else
  {
    for (auto out_edge : currentNode->getOutEdgeSet())
    {
      if (includeEdgeTypes.find(out_edge->getEdgeType()) == includeEdgeTypes.end())
        continue;
      dfs(out_edge->getDstNode(), dst, includeEdgeTypes, visited, currentPath, allPaths, recordPath);
    }
  }

  visited.erase(currentNode);

  if (!currentPath.empty())
    currentPath.pop_back();
}

bool pdg::GenericGraph::canReach(Node &src, Node &dst, std::set<EdgeType> &includeEdgeTypes, std::set<std::vector<llvm::Function *>> *allPaths, bool recordPath)
{
  if (&src == &dst)
    return true;

  std::unordered_set<Node *> visited;
  std::vector<llvm::Function *> currentPath;

  dfs(&src, dst, includeEdgeTypes, visited, currentPath, allPaths, recordPath);

  if (recordPath)
    return !allPaths->empty();
  else
    return visited.find(&dst) != visited.end();
}


std::unordered_set<pdg::Node *> pdg::GenericGraph::findNodesReachedByEdge(pdg::Node &src, EdgeType edgeTy)
{
  std::unordered_set<Node *> ret;
  std::queue<Node *> nodeQueue;
  nodeQueue.push(&src);
  std::unordered_set<Node*> visited;
  while (!nodeQueue.empty())
  {
    Node *currentNode = nodeQueue.front();
    nodeQueue.pop();
    if (!currentNode || visited.find(currentNode) != visited.end())
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

std::unordered_set<pdg::Node *> pdg::GenericGraph::findNodesReachedByEdges(pdg::Node &src, std::set<EdgeType> &edgeTypes, bool isBackward)
{
  std::unordered_set<Node *> ret;
  std::queue<Node *> nodeQueue;
  nodeQueue.push(&src);
  std::unordered_set<Node *> visited;
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
      // special processing for def-use edge. Avoiding concluding that operand in call instruction has def-use relation with the return value.
      if (edge->getEdgeType() == EdgeType::DATA_DEF_USE)
      {
        auto dstNodeVal = edge->getDstNode()->getValue();
        // if (isBackward)
        //   dstNodeVal = edge->getSrcNode()->getValue();
        if (dstNodeVal && isa<CallInst>(dstNodeVal))
          continue;
      }
      if (isBackward)
        nodeQueue.push(edge->getSrcNode());
      else
        nodeQueue.push(edge->getDstNode());
    }
  }
  return ret;
}

// PDG Specific
void pdg::ProgramGraph::build(Module &M) {
  buildGlobalVariables(M);
  buildFunctions(M);
  buildCallGraphAndCallSites(M);
  _isBuild = true;
}

void pdg::ProgramGraph::buildGlobalVariables(Module &M)
{
  for (auto &global_var : M.getGlobalList())
  {
    if (global_var.isConstant())
      continue;

    DIType *global_var_di_type = dbgutils::getGlobalVarDIType(global_var);
    if (global_var_di_type == nullptr)
      continue;

    TreeNode *n = new TreeNode(global_var, GraphNodeType::GLOBAL_VAR);
    n->addAddrVar(global_var);

    _valNodeMap.insert(std::pair<Value *, Node *>(&global_var, n));
    addNode(*n);

    Tree *global_tree = new Tree(global_var);
    global_tree->setRootNode(*n);
    global_tree->build();
    _global_var_tree_map.insert(std::make_pair(&global_var, global_tree));
  }
}

void pdg::ProgramGraph::buildFunctions(Module &M)
{
  auto &call_g = PDGCallGraph::getInstance();
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    // if (!call_g.isBuildFuncNode(F))
    //   continue;
    FunctionWrapper *func_w = new FunctionWrapper(&F);
    buildFunctionInstructions(F, func_w);
    func_w->buildFormalTreeForArgs();
    func_w->buildFormalTreesForRetVal();
    addFormalTreeNodesToGraph(*func_w);
    addNode(*func_w->getEntryNode());
    _func_wrapper_map.insert(std::make_pair(&F, func_w));
  }
}

void pdg::ProgramGraph::buildFunctionInstructions(Function &F, FunctionWrapper *func_w)
{
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
}

void pdg::ProgramGraph::buildCallGraphAndCallSites(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty() || !hasFuncWrapper(F))
      continue;

    FunctionWrapper *func_w = getFuncWrapper(F);
    auto call_insts = func_w->getCallInsts();

    for (auto ci : call_insts)
    {
      handleCallSites(M, ci);
    }
  }
}

void pdg::ProgramGraph::handleCallSites(Module &M, CallInst *ci)
{
  auto &call_g = PDGCallGraph::getInstance();
  auto called_func = pdgutils::getCalledFunc(*ci);
  if (called_func == nullptr)
  {
    auto ind_call_candidates = call_g.getIndirectCallCandidates(*ci, M);
    if (ind_call_candidates.size() > 0)
      called_func = *ind_call_candidates.begin();
  }
  if (!called_func || !hasFuncWrapper(*called_func))
    return;

  CallWrapper *cw = new CallWrapper(*ci);
  FunctionWrapper *callee_fw = getFuncWrapper(*called_func);
  cw->buildActualTreeForArgs(*callee_fw);
  cw->buildActualTreesForRetVal(*callee_fw);
  _call_wrapper_map.insert(std::make_pair(ci, cw));
}

void pdg::ProgramGraph::bindDITypeToNodes(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    FunctionWrapper *fw = _func_wrapper_map[&F];
    bindDITypeToLocalVariables(fw);
    bindDITypeToInstructions(F);
  }
  bindDITypeToGlobalVariables(M);
}

void pdg::ProgramGraph::bindDITypeToLocalVariables(FunctionWrapper *fw)
{
  auto dbgDeclareInsts = fw->getDbgDeclareInsts();
  for (auto dbgInst : dbgDeclareInsts)
  {
    auto addr = dbgInst->getVariableLocation();
    Node *addr_node = getNode(*addr);
    if (!addr_node)
      continue;
    auto DLV = dbgInst->getVariable();
    assert(DLV != nullptr && "cannot find DILocalVariable Node for computing DIType");
    DIType *var_di_type = DLV->getType();
    assert(var_di_type != nullptr && "cannot bind nullptr ditype to node!");

    addr_node->setDIType(*var_di_type);
    _node_di_type_map.insert(std::make_pair(addr_node, var_di_type));
  }
}

void pdg::ProgramGraph::bindDITypeToInstructions(Function &F)
{
  for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
  {
    Instruction &i = *instIter;
    Node *n = getNode(i);
    assert(n != nullptr && "cannot compute node di type for null node!\n");
    DIType *nodeDt = computeNodeDIType(*n);
    n->setDIType(*nodeDt);
  }
}

void pdg::ProgramGraph::bindDITypeToGlobalVariables(Module &M)
{
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

// ----
DIType *pdg::ProgramGraph::computeNodeDIType(Node &n)
{
  // local variable
  Function *func = n.getFunc();
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
            DIType *alloca_node_dt = alloca_n->getDIType();
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
      Node *load_addr_node = getNode(*load_addr);
      if (!load_addr_node)
        return nullptr;
      DIType *load_addr_di_type = load_addr_node->getDIType();
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
    Value *value_operand = st->getValueOperand();
    Value *pointer_operand = st->getPointerOperand();
    Node *value_op_node = getNode(*value_operand);
    Node *ptr_op_node = getNode(*pointer_operand);
    if (value_op_node == nullptr || ptr_op_node == nullptr)
      return nullptr;

    if (value_op_node->getDIType() != nullptr)
      return nullptr;

    DIType *ptr_op_di_type = ptr_op_node->getDIType();
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
    Value *baseAddr = gep->getPointerOperand();
    Node *baseAddrNode = getNode(*baseAddr);
    if (!baseAddrNode)
      return nullptr;
    DIType *baseAddrDt = baseAddrNode->getDIType();
    if (!baseAddrDt)
      return nullptr;

    DIType *baseAddrLowestDt = dbgutils::getLowestDIType(*baseAddrDt);
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
    Node *castedValNode = getNode(*castedVal);
    if (!castedValNode)
      return nullptr;
    return castedValNode->getDIType();
  }

  // default
  return nullptr;
}

void pdg::ProgramGraph::addTreeNodesToGraph(pdg::Tree &tree)
{
  TreeNode *rootNode = tree.getRootNode();
  assert(rootNode && "cannot add tree nodes to graph, nullptr root node\n");
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);
  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
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
    Tree *formalInTree = func_w.getArgFormalInTree(*arg);
    Tree *formalOutTree = func_w.getArgFormalOutTree(*arg);
    if (!formalInTree || !formalOutTree)
      return;
    addTreeNodesToGraph(*formalInTree);
    addTreeNodesToGraph(*formalOutTree);
  }
}

bool pdg::GenericGraph::findPathDFS(Node *src, Node *dst, std::vector<std::pair<Node *, Edge *>> &path, std::unordered_set<Node *> &visited, std::set<EdgeType> &edgeTypes)
{
  visited.insert(src);
  if (src == dst)
  {
    path.push_back(std::make_pair(src, nullptr));  // The destination node has no outgoing edge in the path
    return true;
  }

  std::set<Edge *> &edges = src->getOutEdgeSet();
  for (Edge *edge : edges)
  {
    // Check if the edge type is in the set of allowed edge types
    if (edgeTypes.find(edge->getEdgeType()) != edgeTypes.end())
    {
      Node *neighbor = edge->getDstNode();
      if (visited.find(neighbor) == visited.end())
      {
        if (findPathDFS(neighbor, dst, path, visited, edgeTypes))
        {
          path.push_back(std::make_pair(neighbor, edge));
          return true;
        }
      }
    }
  }
  // If we haven't found the path, backtrack and remove the current node and edge from the path
  if (!path.empty())
  {
    path.pop_back();
  }
  return false;
}

void pdg::GenericGraph::printPath(std::vector<std::pair<pdg::Node*, pdg::Edge*>>& path, raw_fd_ostream &OS) {
  for (auto& pair : path) {
    // Get the node and edge from the pair.
    pdg::Node* node = pair.first;
    pdg::Edge* edge = pair.second;

    // Get the instruction from the node.
    Value* val = node->getValue();
    if (!val)
    {
      OS << "empty node edge: " << pdgutils::nodeTypeToString(node->getNodeType()) << " - " << pdgutils::edgeTypeToString(edge->getEdgeType()) << " - ";
      if (edge->getEdgeType() == EdgeType::PARAMETER_IN)
      {
        TreeNode *tn = static_cast<TreeNode *>(node);
        if (tn->getTree())
          OS << tn->getTree()->getRootNode()->getSrcName();
      }
      OS << "\n";
      continue;
    }
    if (auto inst = dyn_cast<Instruction>(val))
    {
      pdgutils::printSourceLocation(*inst, OS);
      if (edge)
      {
        OS << " - Edge type: " << pdgutils::edgeTypeToString(edge->getEdgeType()) << "\n";
      }
      OS << "\t";
      inst->print(OS);
      OS << "\n";
      // If there's an edge, print its type.
    }
  }
}

void pdg::GenericGraph::convertPathToString(std::vector<std::pair<pdg::Node *, pdg::Edge *>> &path, raw_string_ostream &ss)
{
  for (auto &pair : std::vector<std::pair<pdg::Node *, pdg::Edge *>>(path.rbegin(), path.rend()))
  {
    // Get the node and edge from the pair.
    pdg::Node *node = pair.first;
    pdg::Edge *edge = pair.second;
    if (!node || !edge)
      continue;

    // Get the instruction from the node.
    Value *val = node->getValue();
    std::string nodeTypeStr = pdgutils::nodeTypeToString(node->getNodeType());
    std::string edgeTypeStr = pdgutils::edgeTypeToString(edge->getEdgeType());

    // parameter tree node
    if (!val)
    {
      ss << "[ " << nodeTypeStr <<  " || " << edgeTypeStr;

      if (edge->getEdgeType() == EdgeType::PARAMETER_IN)
      {
        TreeNode *tn = static_cast<TreeNode *>(node);
        if (tn->getTree())
          ss << tn->getTree()->getRootNode()->getSrcName() << " ] -> ";
      }
      else
        ss << "] -> ";
    }
    else if (auto inst = dyn_cast<Instruction>(val))
    {
      std::string sourceLocStr = pdgutils::getSourceLocationStr(*inst);
      ss << "[ " << nodeTypeStr << " || " << edgeTypeStr << " || " << sourceLocStr << " ] -> ";
    }
  }
}