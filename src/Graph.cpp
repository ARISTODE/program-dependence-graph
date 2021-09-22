#include "Graph.hh"

using namespace llvm;

static std::set<std::string> KernelAllocators = {
    "kzalloc",
    "kmalloc",
    "kvzalloc",
    "vzalloc",
    "__kmalloc",
    "alloc_netdev",
    "alloc_netdev_mqs",
};

static std::set<std::string> KernelDeAllocators = {
    "kfree"
};

// Generic Graph
bool pdg::GenericGraph::hasNode(Value &v)
{
  return (_val_node_map.find(&v) != _val_node_map.end());
}

pdg::Node *pdg::GenericGraph::getNode(Value &v)
{
  if (!hasNode(v))
    return nullptr;
  return _val_node_map[&v];
}

// ===== Graph Traversal =====

// DFS search
bool pdg::GenericGraph::canReach(pdg::Node &src, pdg::Node &dst)
{
  // TODO: prune by call graph rechability, improve traverse efficiency
  if (canReach(src, dst, {}))
    return true;
  return false;
}

bool pdg::GenericGraph::canReach(pdg::Node &src, pdg::Node &dst, std::set<EdgeType> include_edge_types)
{
  if (&src == &dst)
    return true;

  std::set<Node *> visited;
  std::stack<Node *> node_queue;
  node_queue.push(&src);

  while (!node_queue.empty())
  {
    auto current_node = node_queue.top();
    node_queue.pop();
    if (visited.find(current_node) != visited.end())
      continue;
    visited.insert(current_node);
    if (current_node == &dst)
      return true;
    for (auto out_edge : current_node->getOutEdgeSet())
    {
      // exclude path
      if (include_edge_types.find(out_edge->getEdgeType()) == include_edge_types.end())
        continue;
      node_queue.push(out_edge->getDstNode());
    }
  }
  return false;
}

std::set<pdg::Node *> pdg::GenericGraph::findNodesReachedByEdge(pdg::Node &src, EdgeType edge_type)
{
  std::set<Node *> ret;
  std::queue<Node *> node_queue;
  node_queue.push(&src);
  std::set<Node*> visited;
  while (!node_queue.empty())
  {
    Node *current_node = node_queue.front();
    node_queue.pop();
    if (visited.find(current_node) != visited.end())
      continue;
    visited.insert(current_node);
    ret.insert(current_node);
    for (auto out_edge : current_node->getOutEdgeSet())
    {
      if (edge_type != out_edge->getEdgeType())
        continue;
      node_queue.push(out_edge->getDstNode());
    }
  }
  return ret;
}

std::set<pdg::Node *> pdg::GenericGraph::findNodesReachedByEdges(pdg::Node &src, std::set<EdgeType> &edge_types, bool is_backward)
{
  std::set<Node *> ret;
  std::queue<Node *> node_queue;
  node_queue.push(&src);
  std::set<Node *> visited;
  while (!node_queue.empty())
  {
    Node *current_node = node_queue.front();
    node_queue.pop();
    if (visited.find(current_node) != visited.end())
      continue;
    visited.insert(current_node);
    ret.insert(current_node);
    Node::EdgeSet edge_set;
    if (is_backward)
      edge_set = current_node->getInEdgeSet();
    else 
      edge_set = current_node->getOutEdgeSet();
    for (auto edge : edge_set)
    {
      if (edge_types.find(edge->getEdgeType()) == edge_types.end())
        continue;
      node_queue.push(edge->getDstNode());
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

    _val_node_map.insert(std::pair<Value *, Node *>(&global_var, n));
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
    for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); inst_iter++)
    {
      Node *n = new Node(*inst_iter, GraphNodeType::INST);
      _val_node_map.insert(std::pair<Value *, Node *>(&*inst_iter, n));
      func_w->addInst(*inst_iter);
      addNode(*n);
      // identify possible heap allocator/dealloctor. Used for inferring alloc/dealloc attributes in IDL generation.
      if (CallInst *ci = dyn_cast<CallInst>(&*inst_iter))
      {
        auto called_func = pdgutils::getCalledFunc(*ci);
        if (called_func != nullptr)
        {
          std::string called_func_name = called_func->getName().str();
          called_func_name = pdgutils::stripFuncNameVersionNumber(called_func_name);
          if (KernelAllocators.find(called_func_name) != KernelAllocators.end())
            _allocators.insert(ci);
          if (KernelDeAllocators.find(called_func_name) != KernelDeAllocators.end())
            _deallocators.insert(ci);
        }
      }
      // identify array allocated on stack. If the array is passed across isolation domain, also need to annotate the array with alloc attribute
      if (AllocaInst *ai = dyn_cast<AllocaInst>(&*inst_iter))
      {
        if (ai->getAllocatedType()->isArrayTy())
          _allocators.insert(ai);
      }
    }
    func_w->buildFormalTreeForArgs();
    func_w->buildFormalTreesForRetVal();
    addFormalTreeNodesToGraph(*func_w);
    addNode(*func_w->getEntryNode());
    _func_wrapper_map.insert(std::make_pair(&F, func_w));
  }

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
        continue;
      if (!hasFuncWrapper(*called_func))
        continue;
      CallWrapper *cw = new CallWrapper(*ci);
      FunctionWrapper *callee_fw = getFuncWrapper(*called_func);
      cw->buildActualTreeForArgs(*callee_fw);
      cw->buildActualTreesForRetVal(*callee_fw);
      _call_wrapper_map.insert(std::make_pair(ci, cw));
    }
  }
  _is_build = true;
}

void pdg::ProgramGraph::bindDITypeToNodes(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    FunctionWrapper *fw = _func_wrapper_map[&F];
    auto dbg_declare_insts = fw->getDbgDeclareInsts();
    // bind ditype to the top-level pointer (alloca)
    for (auto dbg_declare_inst : dbg_declare_insts)
    {
      auto addr = dbg_declare_inst->getVariableLocation();
      Node *addr_node = getNode(*addr);
      if (!addr_node)
        continue;
      auto DLV = dbg_declare_inst->getVariable(); // di local variable instance
      assert(DLV != nullptr && "cannot find DILocalVariable Node for computing DIType");
      DIType *var_di_type = DLV->getType();
      assert(var_di_type != nullptr && "cannot bind nullptr ditype to node!");
      addr_node->setDIType(*var_di_type);
      _node_di_type_map.insert(std::make_pair(addr_node, var_di_type));
    }

    for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); inst_iter++)
    {
      Instruction &i = *inst_iter;
      Node* n = getNode(i);
      assert(n != nullptr && "cannot compute node di type for null node!\n");
      DIType* node_di_type = computeNodeDIType(*n);
      n->setDIType(*node_di_type);
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
    if (n.getDIType() == nullptr)
    {
      for (auto inst_iter = inst_begin(func); inst_iter != inst_end(func); ++inst_iter)
      {
        if (&*inst_iter == val)
          continue;
        if (AllocaInst *ai = dyn_cast<AllocaInst>(&*inst_iter))
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
      auto global_type = gv->getType();

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
    Value* base_addr = gep->getPointerOperand();
    Node* base_addr_node = getNode(*base_addr);
    if (!base_addr_node)
      return nullptr;
    DIType* base_addr_di_type = base_addr_node->getDIType();
    if (!base_addr_di_type)
      return nullptr;

    DIType* base_addr_lowest_di_type = dbgutils::getLowestDIType(*base_addr_di_type);
    if (!base_addr_lowest_di_type)
      return nullptr;
    if (!dbgutils::isStructType(*base_addr_lowest_di_type))
      return nullptr;
    // TODO: here we assume negative offset always move to the parent structure, and no other unsafe use.
    // should verify this assumption is valid.
    // if (pdgutils::getGEPAccessFieldOffset(*gep) < 0)
    //   return base_addr_lowest_di_type;
    if (auto dict = dyn_cast<DICompositeType>(base_addr_lowest_di_type))
    {
      auto di_node_arr = dict->getElements();
      for (unsigned i = 0; i < di_node_arr.size(); ++i)
      {
        DIType *field_di_type = dyn_cast<DIType>(di_node_arr[i]);
        assert(field_di_type != nullptr && "fail to retrive field di type (computeNodeDIType)");
        if (pdgutils::isGEPOffsetMatchDIOffset(*field_di_type, *gep))
          return field_di_type;
      }
    }
  }
  // cast inst
  if (CastInst *cast_inst = dyn_cast<CastInst>(val))
  {
    Value *casted_val = cast_inst->getOperand(0);
    Node* casted_val_node = getNode(*casted_val);
    if (!casted_val_node)
      return nullptr;
    return casted_val_node->getDIType();
  }

  // default
  return nullptr;
}

void pdg::ProgramGraph::addTreeNodesToGraph(pdg::Tree &tree)
{
  TreeNode* root_node = tree.getRootNode();
  std::queue<TreeNode*> node_queue;
  node_queue.push(root_node);
  while (!node_queue.empty())
  {
    TreeNode* current_node = node_queue.front();
    node_queue.pop();
    addNode(*current_node);
    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
  }
}

void pdg::ProgramGraph::addFormalTreeNodesToGraph(FunctionWrapper &func_w)
{
  for (auto arg : func_w.getArgList())
  {
    Tree* formal_in_tree = func_w.getArgFormalInTree(*arg);
    Tree* formal_out_tree = func_w.getArgFormalOutTree(*arg);
    if (!formal_in_tree || !formal_out_tree)
      return;
    addTreeNodesToGraph(*formal_in_tree);
    addTreeNodesToGraph(*formal_out_tree);
  }
}