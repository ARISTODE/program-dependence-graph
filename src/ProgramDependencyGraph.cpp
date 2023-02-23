#include "ProgramDependencyGraph.hh"
#include <chrono> 

using namespace llvm;

char pdg::ProgramDependencyGraph::ID = 0;

cl::opt<bool> FieldSensitive("fs", cl::desc("Field Sensitive"), cl::value_desc("field_sensitive"), cl::init(true));
cl::opt<bool, true> EAS("analysis-stats", cl::desc("enable printing analysis stats"), cl::value_desc("analysis_stats"), cl::location(pdg::EnableAnalysisStats), cl::init(false));
cl::opt<bool, true> DBG("debug-verbose", cl::desc("enable printing verbose debug info"), cl::value_desc("verbose-debug"), cl::location(pdg::DEBUG), cl::init(false));

bool pdg::EnableAnalysisStats;
bool pdg::DEBUG;

void pdg::ProgramDependencyGraph::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<DataDependencyGraph>();
  AU.addRequired<ControlDependencyGraph>();
  AU.setPreservesAll();
}

bool pdg::ProgramDependencyGraph::runOnModule(Module &M)
{
  _module = &M;
  _PDG = &ProgramGraph::getInstance();

  PTAWrapper &ptaw = PTAWrapper::getInstance();
  PDGCallGraph &call_g = PDGCallGraph::getInstance();
  if (!call_g.isBuild())
    call_g.build(M);

  if (!_PDG->isBuild())
  {
    _PDG->build(M);
    _PDG->bindDITypeToNodes(M);
  }

  if (!ptaw.hasPTASetup())
    ptaw.setupPTA(M);
  unsigned func_size = 0;

  // connect global tree with addr vars
  for (auto pair : _PDG->getGlobalVarTreeMap())
  {
    auto tree = pair.second;
    connectGlobalTreeWithAddrVars(*tree);
  }

  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    connectIntraprocDependencies(F);
    connectInterprocDependencies(F);
    // this is a simplification from caller's formal tree to call site actual trees
    // we use this to quickly reach from formal tree to any parameter pass to 
    // callees through parameter_in edge
    connectFormalInTreeWithActualTree(F);
    func_size++;
  }

  // errs() << "connecting interproc addrvar\n";
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    connectAddrVarsReachableFromInterprocFlow(F);
    // connectInterprocDependencies(F);
    connectFormalInTreeWithActualTree(F);
    // connectIntraprocDependencies(F);
  }
  errs() << "func size: " << func_size << "\n";
  errs() << "PDG Node size: " << _PDG->numNode() << "\n";
  return false;
}

void pdg::ProgramDependencyGraph::connectInTrees(Tree *src_tree, Tree *dstTree, EdgeType edgeTy)
{
  if (src_tree->size() != dstTree->size())
    return;
  auto src_tree_root_node = src_tree->getRootNode();
  auto dst_tree_root_node = dstTree->getRootNode();
  std::queue<std::pair<TreeNode *, TreeNode *>> node_pairs_queue;
  node_pairs_queue.push(std::make_pair(src_tree_root_node, dst_tree_root_node));
  while (!node_pairs_queue.empty())
  {
    auto current_node_pair = node_pairs_queue.front();
    node_pairs_queue.pop();
    TreeNode *src = current_node_pair.first;
    TreeNode *dst = current_node_pair.second;
    assert(src->numOfChild() == dst->numOfChild());
    src->addNeighbor(*dst, edgeTy);
    auto src_node_children = src->getChildNodes();
    auto dst_node_children = dst->getChildNodes();
    for (int i = 0; i < src->numOfChild(); i++)
    {
      node_pairs_queue.push(std::make_pair(src_node_children[i], dst_node_children[i]));
    }
  }
}

void pdg::ProgramDependencyGraph::connectOutTrees(Tree *src_tree, Tree *dstTree, EdgeType edgeTy)
{
  if (src_tree->size() != dstTree->size())
    return;
  auto src_tree_root_node = src_tree->getRootNode();
  auto dst_tree_root_node = dstTree->getRootNode();
  std::queue<std::pair<TreeNode *, TreeNode *>> node_pairs_queue;
  node_pairs_queue.push(std::make_pair(src_tree_root_node, dst_tree_root_node));
  while (!node_pairs_queue.empty())
  {
    auto current_node_pair = node_pairs_queue.front();
    node_pairs_queue.pop();
    TreeNode *src = current_node_pair.first;
    TreeNode *dst = current_node_pair.second;
    assert(src->numOfChild() == dst->numOfChild());
    if (src->hasWriteAccess())
      src->addNeighbor(*dst, edgeTy);
    auto src_node_children = src->getChildNodes();
    auto dst_node_children = dst->getChildNodes();
    for (int i = 0; i < src->numOfChild(); i++)
    {
      node_pairs_queue.push(std::make_pair(src_node_children[i], dst_node_children[i]));
    }
  }
}

void pdg::ProgramDependencyGraph::connectCallerAndCallee(CallWrapper &cw, FunctionWrapper &fw)
{
  // step 1: connect call site node with the entry node of function
  auto call_site_node = _PDG->getNode(*cw.getCallInst());
  auto func_entry_node = fw.getEntryNode();
  if (call_site_node == nullptr || func_entry_node == nullptr)
    return;
  call_site_node->addNeighbor(*func_entry_node, EdgeType::CALL);
  // don't expand field sensitive connection if not specified
  if (!FieldSensitive)
    return;
  // step 2: connect actual in -> formal in, formal out -> actual out
  auto actual_arg_list = cw.getArgList();
  auto formal_arg_list = fw.getArgList();
  assert(actual_arg_list.size() == formal_arg_list.size() && "cannot connect tree edges due to unequal arg num! (connectCallerandCallee)");
  int num_arg = cw.getArgList().size();
  for (int i = 0; i < num_arg; i++)
  {
    Value *actual_arg = actual_arg_list[i];
    Argument *formal_arg = formal_arg_list[i];
    // step 2: connect actual in -> formal in
    auto actualInTree = cw.getArgActualInTree(*actual_arg);
    auto formalInTree = fw.getArgFormalInTree(*formal_arg);
    if (!actualInTree || !formalInTree)
      continue;
    _PDG->addTreeNodesToGraph(*actualInTree);
    // connect actual in and formal in trees
    connectInTrees(actualInTree, formalInTree, EdgeType::PARAMETER_IN);

    // step 3: connect actual out -> formal out
    auto actualOutTree = cw.getArgActualOutTree(*actual_arg);
    auto formalOutTree = fw.getArgFormalOutTree(*formal_arg);
    if (!actualOutTree || !formalOutTree)
      continue;
    _PDG->addTreeNodesToGraph(*actualOutTree);
    connectOutTrees(formalOutTree, actualOutTree, EdgeType::PARAMETER_OUT);
  }

  // step3: connect return value actual in -> formal in, formal out -> actual out
  if (!fw.hasNullRetVal() && !cw.hasNullRetVal())
  {
    Tree *ret_formal_in_tree = fw.getRetFormalInTree();
    Tree *ret_formal_out_tree = fw.getRetFormalOutTree();
    Tree *ret_actual_in_tree = cw.getRetActualInTree();
    Tree *ret_actual_out_tree = cw.getRetActualOutTree();
    if (!ret_formal_in_tree || !ret_formal_out_tree || !ret_actual_in_tree || !ret_actual_out_tree)
      return;
    connectInTrees(ret_actual_in_tree, ret_formal_in_tree, EdgeType::PARAMETER_IN);
    connectInTrees(ret_actual_out_tree, ret_formal_out_tree, EdgeType::PARAMETER_OUT);
  }

  // step4: connect return value of callee to the call site
  auto ret_insts = fw.getReturnInsts();
  auto callInst = cw.getCallInst();
  for (auto ret_inst : ret_insts)
  {
    auto ret_val = ret_inst->getReturnValue();
    Node *src = _PDG->getNode(*ret_val);
    Node *dst = _PDG->getNode(*callInst);
    if (src == nullptr || dst == nullptr)
      continue;
    src->addNeighbor(*dst, EdgeType::DATA_RET);
  }
}

// ===== connect intraprocedural dependencies =====
void pdg::ProgramDependencyGraph::connectIntraprocDependencies(Function &F)
{
  // add control dependency edges
  getAnalysis<ControlDependencyGraph>(F); // add data dependencies for nodes in F
  // connect formal tree with address variables
  FunctionWrapper *func_w = getFuncWrapper(F);
  Node *entry_node = func_w->getEntryNode();
  for (auto arg : func_w->getArgList())
  {
    Tree *formalInTree = func_w->getArgFormalInTree(*arg);
    if (!formalInTree)
      return;
    Tree *formalOutTree = func_w->getArgFormalOutTree(*arg);
    entry_node->addNeighbor(*formalInTree->getRootNode(), EdgeType::PARAMETER_IN);
    entry_node->addNeighbor(*formalOutTree->getRootNode(), EdgeType::PARAMETER_OUT);
    connectFormalInTreeWithAddrVars(*formalInTree);
    connectFormalOutTreeWithAddrVars(*formalOutTree);
  }

  if (!func_w->hasNullRetVal())
  {
    connectFormalInTreeWithAddrVars(*func_w->getRetFormalInTree());
    connectFormalOutTreeWithAddrVars(*func_w->getRetFormalOutTree());
  }
}

void pdg::ProgramDependencyGraph::connectInterprocDependencies(Function &F)
{
  auto &call_g = PDGCallGraph::getInstance();
  auto func_w = getFuncWrapper(F);
  auto call_insts = func_w->getCallInsts();
  for (auto callInst : call_insts)
  {
    if (_PDG->hasCallWrapper(*callInst))
    {
      auto call_w = getCallWrapper(*callInst);
      auto call_site_node = _PDG->getNode(*callInst);
      if (!call_w || !call_site_node)
        continue;

      if (call_w->getCalledFunc() && call_w->getCalledFunc()->isVarArg()) 
        continue;

      if (FieldSensitive)
      {
        for (auto arg : call_w->getArgList())
        {
          Tree *actualInTree = call_w->getArgActualInTree(*arg);
          if (!actualInTree)
          {
            // errs() << "[WARNING]: empty actual tree for callsite " << *callInst << " in func " << F.getName() << "\n";
            continue;
          }
          Tree *actualOutTree = call_w->getArgActualOutTree(*arg);
          call_site_node->addNeighbor(*actualInTree->getRootNode(), EdgeType::PARAMETER_IN);
          call_site_node->addNeighbor(*actualOutTree->getRootNode(), EdgeType::PARAMETER_OUT);
          connectActualInTreeWithAddrVars(*actualInTree, *callInst);
          connectActualOutTreeWithAddrVars(*actualOutTree, *callInst);
        }
        // connect return trees
        // TODO: should change the name here. for return value, we should only connect
        // the tree node with vars after the call instruction
        if (!call_w->hasNullRetVal())
        {
          connectActualOutTreeWithAddrVars(*call_w->getRetActualInTree(), *callInst);
          connectActualOutTreeWithAddrVars(*call_w->getRetActualOutTree(), *callInst);
        }
      }

      // direct call
      if (call_w->getCalledFunc() != nullptr)
      {
        auto called_func_w = getFuncWrapper(*call_w->getCalledFunc());
        connectCallerAndCallee(*call_w, *called_func_w);
      }
      else
      {
        // indirect call
        auto ind_called_funcs = call_g.getIndirectCallCandidates(*call_w->getCallInst(), *_module);
        for (auto ind_called_func : ind_called_funcs)
        {
          if (ind_called_func->isDeclaration() || ind_called_func->isVarArg())
            continue;
          auto called_func_w = getFuncWrapper(*ind_called_func);
          connectCallerAndCallee(*call_w, *called_func_w);
        }
      }
    }
  }
}

// ====== connect tree with variables ======
void pdg::ProgramDependencyGraph::connectGlobalTreeWithAddrVars(Tree &globalVarTree)
{
  TreeNode *rootNode = globalVarTree.getRootNode();
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);

  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    TreeNode *parentNode = currentNode->getParentNode();
    std::unordered_set<Value *> parent_node_addr_vars;
    if (parentNode != nullptr)
      parent_node_addr_vars = parentNode->getAddrVars();

    for (auto addrVar : currentNode->getAddrVars())
    {
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addr_var_node = _PDG->getNode(*addrVar);
      currentNode->addNeighbor(*addr_var_node, EdgeType::PARAMETER_IN);
      auto alias_nodes = addr_var_node->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
      for (auto alias_node : alias_nodes)
      {
        Value *alias_node_val = alias_node->getValue();
        if (alias_node_val == nullptr)
          continue;
        if (parent_node_addr_vars.find(alias_node_val) != parent_node_addr_vars.end())
          continue;
        if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(alias_node_val))
        {
          if (!gep->hasAllZeroIndices())
            continue;
        }
        currentNode->addNeighbor(*alias_node, EdgeType::PARAMETER_IN);
        currentNode->addAddrVar(*alias_node_val);
      }
    }

    for (auto child_node : currentNode->getChildNodes())
    {
      nodeQueue.push(child_node);
    }
  }
}

void pdg::ProgramDependencyGraph::connectFormalInTreeWithAddrVars(Tree &formalInTree)
{
  TreeNode *rootNode = formalInTree.getRootNode();
  Function *current_func = formalInTree.getFunc();
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);

  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    currentNode->computeDerivedAddrVarsFromParent();
    TreeNode *parentNode = currentNode->getParentNode();
    std::unordered_set<Value *> parent_node_addr_vars;
    if (parentNode != nullptr)
      parent_node_addr_vars = parentNode->getAddrVars();

    for (auto addrVar : currentNode->getAddrVars())
    {
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addr_var_node = _PDG->getNode(*addrVar);
      currentNode->addNeighbor(*addr_var_node, EdgeType::PARAMETER_IN);
      // adding alias vars to tree's address var set
      auto alias_nodes = getAliasNodes(*addr_var_node);
      for (auto alias_node : alias_nodes)
      {
        Value *alias_node_val = alias_node->getValue();
        if (alias_node_val == nullptr)
          continue;
        if (parent_node_addr_vars.find(alias_node_val) != parent_node_addr_vars.end())
          continue;
        if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(alias_node_val))
        {
          if (!currentNode->isStructMember())
          {
            // when finding alias for non-sturct member field, if a gep instruction is found with (0,0) indices,
            // it means the first element in the object/buffer. We need to skip this because it will confuse
            // access analysis and causing false positives for the accesses on the container object.
            if (gep->hasAllZeroIndices())
              continue;
          }
        }
        currentNode->addAddrVar(*alias_node_val);
        currentNode->addNeighbor(*alias_node, EdgeType::PARAMETER_IN);
      }
    }

    // stop connecting rest nodes with addr vars if not field sensitive
    if (!FieldSensitive)
      break;
    for (auto child_node : currentNode->getChildNodes())
    {
      nodeQueue.push(child_node);
    }
  }
}

void pdg::ProgramDependencyGraph::connectFormalOutTreeWithAddrVars(Tree &formalOutTree)
{
  TreeNode *rootNode = formalOutTree.getRootNode();
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
      auto addr_var_node = _PDG->getNode(*addrVar);
      // TODO: add addr variables for formal out tree
      if (pdgutils::hasWriteAccess(*addrVar))
      {
        addr_var_node->addNeighbor(*currentNode, EdgeType::PARAMETER_OUT);
        currentNode->addAccessTag(AccessTag::DATA_WRITE);
      }
    }

    if (!FieldSensitive)
      break;
    for (auto child_node : currentNode->getChildNodes())
    {
      nodeQueue.push(child_node);
    }
  }
}

void pdg::ProgramDependencyGraph::connectActualInTreeWithAddrVars(Tree &actualInTree, CallInst &ci)
{
  TreeNode *rootNode = actualInTree.getRootNode();
  std::set<Instruction *> insts_before_ci = pdgutils::getInstructionBeforeInst(ci);
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);
  // TODO: test for ixgbe probe
  bool ixgbeProbeFlag = (ci.getFunction()->getName() == "ixgbe_probe");

  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    for (auto addrVar : currentNode->getAddrVars())
    {
      // only connect addrVar that are pred to the call site
      if (Instruction *i = dyn_cast<Instruction>(addrVar))
      {
        if (insts_before_ci.find(i) == insts_before_ci.end())
          continue;
      }
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addr_var_node = _PDG->getNode(*addrVar);
      auto alias_nodes = addr_var_node->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
      // connect addr var node with parameter_in node
      addr_var_node->addNeighbor(*currentNode, EdgeType::PARAMETER_IN);
      for (auto alias_node : alias_nodes)
      {
        auto alias_node_val = alias_node->getValue();
        if (alias_node_val != nullptr)
        {
          alias_node->addNeighbor(*currentNode, EdgeType::PARAMETER_IN);
          currentNode->addAddrVar(*alias_node_val);
        }
      }
    }

    for (auto child_node : currentNode->getChildNodes())
    {
      nodeQueue.push(child_node);
    }
  }
}

void pdg::ProgramDependencyGraph::connectActualOutTreeWithAddrVars(Tree &actualOutTree, CallInst &ci)
{
  TreeNode *rootNode = actualOutTree.getRootNode();
  std::set<Instruction *> insts_after_ci = pdgutils::getInstructionAfterInst(ci);
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);
  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    for (auto addrVar : currentNode->getAddrVars())
    {
      // only connect with succe insts of call sites
      if (Instruction *i = dyn_cast<Instruction>(addrVar))
      {
        if (insts_after_ci.find(i) == insts_after_ci.end())
          continue;
      }
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addr_var_node = _PDG->getNode(*addrVar);
      currentNode->addNeighbor(*addr_var_node, EdgeType::PARAMETER_OUT);
    }

    for (auto child_node : currentNode->getChildNodes())
    {
      nodeQueue.push(child_node);
    }
  }
}

void pdg::ProgramDependencyGraph::connectTreeNode(TreeNode &src_node, TreeNode &dstNode, EdgeType edgeTy)
{
  std::queue<std::pair<TreeNode *, TreeNode *>> node_pairs_queue;
  node_pairs_queue.push(std::make_pair(&src_node, &dstNode));
  while (!node_pairs_queue.empty())
  {
    auto current_node_pair = node_pairs_queue.front();
    node_pairs_queue.pop();
    TreeNode *src = current_node_pair.first;
    TreeNode *dst = current_node_pair.second;

    src->addNeighbor(*dst, edgeTy);
    if (src->numOfChild() == dst->numOfChild())
    {
      auto src_node_children = src->getChildNodes();
      auto dst_node_children = dst->getChildNodes();
      for (int i = 0; i < src->numOfChild(); i++)
      {
        node_pairs_queue.push(std::make_pair(src_node_children[i], dst_node_children[i]));
      }
    }
  }
}

void pdg::ProgramDependencyGraph::connectFormalInTreeWithActualTree(Function &F)
{
  FunctionWrapper *func_w = getFuncWrapper(F);
  for (auto arg : func_w->getArgList())
  {
    Tree *formalInTree = func_w->getArgFormalInTree(*arg);
    if (!formalInTree)
      return;
    connectFormalInTreeWithCallActualNode(*formalInTree);
  }
}

void pdg::ProgramDependencyGraph::connectFormalInTreeWithCallActualNode(Tree &formalInTree)
{
  TreeNode *rootNode = formalInTree.getRootNode();
  Function *func = rootNode->getFunc();
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);

  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    TreeNode *parentNode = currentNode->getParentNode();
    std::unordered_set<Value *> parent_node_addr_vars;
    if (parentNode != nullptr)
      parent_node_addr_vars = parentNode->getAddrVars();
    for (auto addrVar : currentNode->getAddrVars())
    {
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addr_var_node = _PDG->getNode(*addrVar);
      // check if the addrVar is used in call instruction
      // if so, connect the tree node with the actual tree of the call
      auto call_out_neighbors_cand = addr_var_node->getOutNeighborsWithDepType(EdgeType::DATA_DEF_USE);
      for (auto call_node : call_out_neighbors_cand)
      {
        if (call_node->getValue() != nullptr)
        {
          if (CallInst *ci = dyn_cast<CallInst>(call_node->getValue()))
          {
            auto called_func = pdgutils::getCalledFunc(*ci);
            if (called_func != nullptr && !called_func->isDeclaration())
            {
              auto call_wrapper = getCallWrapper(*ci);
              Tree *arg_actual_in_tree = call_wrapper->getArgActualInTree(*addrVar);
              if (arg_actual_in_tree != nullptr)
              {
                auto arg_actual_in_tree_root_node = arg_actual_in_tree->getRootNode();
                if (arg_actual_in_tree_root_node != nullptr)
                  connectTreeNode(*currentNode, *arg_actual_in_tree_root_node, EdgeType::PARAMETER_IN);
              }
            }
          }
        }
      }
    }
    // stop connecting rest nodes with addr vars if not field sensitive
    if (!FieldSensitive)
      break;
    for (auto child_node : currentNode->getChildNodes())
    {
      nodeQueue.push(child_node);
    }
  }
}

void pdg::ProgramDependencyGraph::connectAddrVarsReachableFromInterprocFlow(Function &F)
{
  FunctionWrapper *func_w = getFuncWrapper(F);
  for (auto arg : func_w->getArgList())
  {
    Tree *formalInTree = func_w->getArgFormalInTree(*arg);
    if (!formalInTree)
      return;
    conntectFormalInTreeWithInterprocReachableAddrVars(*formalInTree);
  }
}

void pdg::ProgramDependencyGraph::conntectFormalInTreeWithInterprocReachableAddrVars(Tree &formalInTree)
{
  TreeNode *rootNode = formalInTree.getRootNode();
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);
  std::set<EdgeType> edgeTypes = {
      EdgeType::PARAMETER_IN,
      // EdgeType::DATA_RET,
  };
  Function *current_func = formalInTree.getFunc();
  if (current_func == nullptr)
    return;
  while (!nodeQueue.empty())
  {
    auto currentNode = nodeQueue.front();
    nodeQueue.pop();
    auto reachable_nodes = _PDG->findNodesReachedByEdges(*currentNode, edgeTypes);
    for (auto n : reachable_nodes)
    {
      if (n->getValue() == nullptr)
        continue;
      if (n->getFunc() == current_func)
      {
        // if (currentNode->getDIType() != nullptr && !dbgutils::isPointerType(*currentNode->getDIType()))
        // {
        //   auto parentNode = currentNode->getParentNode();
        //   // TODO: need to change pdg construction later
        //   if (parentNode != nullptr)
        //   {
        //     parentNode->addAddrVar(*n->getValue());
        //   }
        // }
        // else
          currentNode->addAddrVar(*n->getValue());
      }
    }

    for (auto child_node : currentNode->getChildNodes())
    {
      nodeQueue.push(child_node);
    }
  }
}

std::set<pdg::Node *> pdg::ProgramDependencyGraph::getAliasNodes(pdg::Node &n)
{
  std::queue<Node *> nodeQueue;
  std::set<Node *> seen_nodes;
  std::set<Node *> alias_nodes;
  nodeQueue.push(&n);
  while (!nodeQueue.empty())
  {
    auto currentNode = nodeQueue.front();
    nodeQueue.pop();
    auto out_alias_neighbors = currentNode->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
    for (auto alias_node : out_alias_neighbors)
    {
      if (seen_nodes.find(alias_node) != seen_nodes.end())
        continue;
      seen_nodes.insert(alias_node);
      nodeQueue.push(alias_node);
      alias_nodes.insert(alias_node);
    }
  }
  return alias_nodes;
}

static RegisterPass<pdg::ProgramDependencyGraph>
    PDG("pdg", "Program Dependency Graph Construction", false, true);