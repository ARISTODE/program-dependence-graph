#include "ProgramDependencyGraph.hh"
#include <chrono> 

using namespace llvm;

char pdg::ProgramDependencyGraph::ID = 0;
llvm::cl::opt<bool> FieldSensitive("fs", llvm::cl::desc("Field Sensitive"), llvm::cl::value_desc("field_sensitive"), llvm::cl::init(true));

void pdg::ProgramDependencyGraph::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<DataDependencyGraph>();
  AU.addRequired<ControlDependencyGraph>();
  AU.setPreservesAll();
}

bool pdg::ProgramDependencyGraph::runOnModule(Module &M)
{
  auto start = std::chrono::high_resolution_clock::now();
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
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    connectIntraprocDependencies(F);
    connectInterprocDependencies(F);
    func_size++;
  }

  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    connectFormalInTreeWithActualTree(F);
  }

  errs() << "func size: " << func_size << "\n";
  errs() << "Finsh adding dependencies" << "\n";
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  errs() << "building PDG takes: " <<  duration.count() << "\n";
  errs() << "PDG Node size: " << _PDG->numNode() << "\n";
  return false;
}

void pdg::ProgramDependencyGraph::connectInTrees(Tree* src_tree, Tree* dst_tree, EdgeType edge_type)
{
  if (src_tree->size() != dst_tree->size())
    return;
  auto src_tree_root_node = src_tree->getRootNode();
  auto dst_tree_root_node = dst_tree->getRootNode();
  std::queue<std::pair<TreeNode*, TreeNode*>> node_pairs_queue;
  node_pairs_queue.push(std::make_pair(src_tree_root_node, dst_tree_root_node));
  while (!node_pairs_queue.empty())
  {
    auto current_node_pair = node_pairs_queue.front();
    node_pairs_queue.pop();
    TreeNode* src = current_node_pair.first;
    TreeNode* dst = current_node_pair.second;
    assert(src->numOfChild() == dst->numOfChild());
    src->addNeighbor(*dst, edge_type);
    auto src_node_children = src->getChildNodes();
    auto dst_node_children = dst->getChildNodes();
    for (int i = 0; i < src->numOfChild(); i++)
    {
      node_pairs_queue.push(std::make_pair(src_node_children[i], dst_node_children[i]));
    }
  }
}

void pdg::ProgramDependencyGraph::connectOutTrees(Tree* src_tree, Tree* dst_tree, EdgeType edge_type)
{
  if (src_tree->size() != dst_tree->size())
    return;
  auto src_tree_root_node = src_tree->getRootNode();
  auto dst_tree_root_node = dst_tree->getRootNode();
  std::queue<std::pair<TreeNode*, TreeNode*>> node_pairs_queue;
  node_pairs_queue.push(std::make_pair(src_tree_root_node, dst_tree_root_node));
  while (!node_pairs_queue.empty())
  {
    auto current_node_pair = node_pairs_queue.front();
    node_pairs_queue.pop();
    TreeNode* src = current_node_pair.first;
    TreeNode* dst = current_node_pair.second;
    assert(src->numOfChild() == dst->numOfChild());
    if (src->hasWriteAccess())
      src->addNeighbor(*dst, edge_type);
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
  if (call_site_node == nullptr || func_entry_node == nullptr )
    return;
  call_site_node->addNeighbor(*func_entry_node, EdgeType::CALL);
  // don't expand field sensitive connection if not specified
  if (!FieldSensitive)
    return;

  // step 2: connect actual in -> formal in, formal out -> actual out
  auto actual_arg_list = cw.getArgList();
  auto formal_arg_list = fw.getArgList();
  assert(actual_arg_list.size() == formal_arg_list.size() && "cannot connect tree edges due to inequal arg num! (connectCallerandCallee)");
  int num_arg = cw.getArgList().size();
  for (int i = 0; i < num_arg; i++)
  {
    Value *actual_arg = actual_arg_list[i];
    Argument *formal_arg =  formal_arg_list[i];
    // step 2: connect actual in -> formal in
    auto actual_in_tree = cw.getArgActualInTree(*actual_arg);
    auto formal_in_tree = fw.getArgFormalInTree(*formal_arg);
    _PDG->addTreeNodesToGraph(*actual_in_tree);
    connectInTrees(actual_in_tree, formal_in_tree, EdgeType::PARAMETER_IN);
    // step 3: connect actual out -> formal out
    auto actual_out_tree = cw.getArgActualOutTree(*actual_arg);
    auto formal_out_tree = fw.getArgFormalOutTree(*formal_arg);
    _PDG->addTreeNodesToGraph(*actual_out_tree);
    connectOutTrees(formal_out_tree, actual_out_tree, EdgeType::PARAMETER_OUT);
  }

  // step3: connect return value actual in -> formal in, formal out -> actual out
  if (!fw.hasNullRetVal() && !cw.hasNullRetVal())
  {
    Tree *ret_formal_in_tree = fw.getRetFormalInTree();
    Tree *ret_formal_out_tree = fw.getRetFormalOutTree();
    Tree *ret_actual_in_tree = cw.getRetActualInTree();
    Tree *ret_actual_out_tree = cw.getRetActualOutTree();
    connectInTrees(ret_actual_in_tree, ret_formal_in_tree, EdgeType::PARAMETER_IN);
    connectInTrees(ret_actual_out_tree, ret_formal_out_tree, EdgeType::PARAMETER_OUT);
  }

  // step4: connect return value of callee to the call site
  auto ret_insts = fw.getReturnInsts();
  auto call_inst = cw.getCallInst();
  for (auto ret_inst : ret_insts)
  {
    Node *src = _PDG->getNode(*ret_inst);
    Node *dst = _PDG->getNode(*call_inst);
    if (src == nullptr || dst == nullptr)
      continue;
    src->addNeighbor(*dst, EdgeType::DATA_RET);
  }
}

// ===== connect dependencies =====
void pdg::ProgramDependencyGraph::connectIntraprocDependencies(Function &F)
{
  // add control dependency edges
  // TODO: Figure out why control pass will run automatically.
  getAnalysis<ControlDependencyGraph>(F); // add data dependencies for nodes in F
  // connect formal tree with address variables
  FunctionWrapper* func_w = getFuncWrapper(F);
  Node* entry_node = func_w->getEntryNode();
  for (auto arg : func_w->getArgList())
  {
    Tree* formal_in_tree = func_w->getArgFormalInTree(*arg);
    if (!formal_in_tree)
      return;
    Tree* formal_out_tree = func_w->getArgFormalOutTree(*arg);

    entry_node->addNeighbor(*formal_in_tree->getRootNode(), EdgeType::PARAMETER_IN);
    entry_node->addNeighbor(*formal_out_tree->getRootNode(), EdgeType::PARAMETER_OUT);
    connectFormalInTreeWithAddrVars(*formal_in_tree);
    connectFormalOutTreeWithAddrVars(*formal_out_tree);
  }

  if (!func_w->hasNullRetVal())
  {
    connectFormalInTreeWithAddrVars(*func_w->getRetFormalInTree());
    connectFormalOutTreeWithAddrVars(*func_w->getRetFormalOutTree());
  }
}

void pdg::ProgramDependencyGraph::connectInterprocDependencies(Function &F)
{
  auto func_w = getFuncWrapper(F);
  auto call_insts = func_w->getCallInsts();
  for (auto call_inst : call_insts)
  {
    if (_PDG->hasCallWrapper(*call_inst))
    {
      auto call_w = getCallWrapper(*call_inst);
      if (!call_w)
        continue;
      auto call_site_node = _PDG->getNode(*call_inst);
      if (!call_site_node)
        continue;

      if (FieldSensitive)
      {
        for (auto arg : call_w->getArgList())
        {
          Tree *actual_in_tree = call_w->getArgActualInTree(*arg);
          if (!actual_in_tree)
          {
            // errs() << "[WARNING]: empty actual tree for callsite " << *call_inst << "\n";
            return;
          }
          Tree *actual_out_tree = call_w->getArgActualOutTree(*arg);
          call_site_node->addNeighbor(*actual_in_tree->getRootNode(), EdgeType::PARAMETER_IN);
          call_site_node->addNeighbor(*actual_out_tree->getRootNode(), EdgeType::PARAMETER_OUT);
          connectActualInTreeWithAddrVars(*actual_in_tree, *call_inst);
          connectActualOutTreeWithAddrVars(*actual_out_tree, *call_inst);
        }
        // connect return trees
        // TODO: should change the name here. for return value, we should only connect
        // the tree node with vars after the call instruction
        if (!call_w->hasNullRetVal())
        {
          connectActualOutTreeWithAddrVars(*call_w->getRetActualInTree(), *call_inst);
          connectActualOutTreeWithAddrVars(*call_w->getRetActualOutTree(), *call_inst);
        }
      }
      auto called_func_w = getFuncWrapper(*call_w->getCalledFunc());
      connectCallerAndCallee(*call_w, *called_func_w);
    }
  }
}

// ====== connect tree with variables ======
void pdg::ProgramDependencyGraph::connectFormalInTreeWithAddrVars(Tree &formal_in_tree)
{
  TreeNode* root_node = formal_in_tree.getRootNode();
  std::queue<TreeNode*> node_queue;
  node_queue.push(root_node);
   
  while (!node_queue.empty())
  {
    TreeNode* current_node = node_queue.front();
    node_queue.pop();
    TreeNode* parent_node = current_node->getParentNode();
    std::unordered_set<Value*> parent_node_addr_vars;
    if (parent_node != nullptr)
      parent_node_addr_vars = parent_node->getAddrVars();
    for (auto addr_var : current_node->getAddrVars())
    {
      if (!_PDG->hasNode(*addr_var))
        continue;
      auto addr_var_node = _PDG->getNode(*addr_var);
      current_node->addNeighbor(*addr_var_node, EdgeType::PARAMETER_IN);
      auto alias_nodes = addr_var_node->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
      for (auto alias_node : alias_nodes)
      {
        Value* alias_node_val = alias_node->getValue();
        if (alias_node_val == nullptr)
          continue;
        if (parent_node_addr_vars.find(alias_node_val) != parent_node_addr_vars.end())
          continue;
        if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(alias_node_val))
        {
          if (!gep->hasAllZeroIndices())
            continue;
        }
        current_node->addNeighbor(*alias_node, EdgeType::PARAMETER_IN);
      }
      // check if the addr_var is used in call instruction
      // if so, connect the tree node with the actual tree of the call
      // auto call_out_neighbors = addr_var_node->getOutNeighborsWithDepType(EdgeType::DATA_DEF_USE);
      // for (auto call_node : call_out_neighbors)
      // {
      //   if (call_node->getValue() != nullptr)
      //   {
      //     if (CallInst *ci = dyn_cast<CallInst>(call_node->getValue()))
      //     {
      //       auto called_func = pdgutils::getCalledFunc(*ci);
      //       if (called_func != nullptr && !called_func->isDeclaration())
      //       {
      //         auto call_wrapper = getCallWrapper(*ci);
      //         Tree* arg_actual_in_tree = call_wrapper->getArgActualInTree(*addr_var);
      //         if (arg_actual_in_tree != nullptr)
      //         {
      //           auto arg_actual_in_tree_root_node = arg_actual_in_tree->getRootNode();
      //           if (arg_actual_in_tree_root_node != nullptr)
      //             connectTreeNode(*current_node, *arg_actual_in_tree_root_node, EdgeType::PARAMETER_IN);
      //         }
      //       }
      //     }
      //   }
      // }
    }
    
    // stop connecting rest nodes with addr vars if not field sensitive
    if (!FieldSensitive) 
      break;
    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
  }
}

void pdg::ProgramDependencyGraph::connectFormalOutTreeWithAddrVars(Tree &formal_out_tree)
{
  TreeNode *root_node = formal_out_tree.getRootNode();
  std::queue<TreeNode *> node_queue;
  node_queue.push(root_node);
  while (!node_queue.empty())
  {
    TreeNode *current_node = node_queue.front();
    node_queue.pop();
    for (auto addr_var : current_node->getAddrVars())
    {
      if (!_PDG->hasNode(*addr_var))
        continue;
      auto addr_var_node = _PDG->getNode(*addr_var);
      // TODO: add addr variables for formal out tree
      if (pdgutils::hasWriteAccess(*addr_var))
      {
        addr_var_node->addNeighbor(*current_node, EdgeType::PARAMETER_OUT);
        current_node->addAccessTag(AccessTag::DATA_WRITE);
      }
    }

    if(!FieldSensitive)
      break;
    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
  }
}

void pdg::ProgramDependencyGraph::connectActualInTreeWithAddrVars(Tree &actual_in_tree, CallInst &ci)
{
  TreeNode *root_node = actual_in_tree.getRootNode();
  std::set<Instruction*> insts_before_ci = pdgutils::getInstructionBeforeInst(ci);
  std::queue<TreeNode *> node_queue;
  node_queue.push(root_node);
  while (!node_queue.empty())
  {
    TreeNode *current_node = node_queue.front();
    node_queue.pop();
    for (auto addr_var : current_node->getAddrVars())
    {
      // only connect addr_var that are pred to the call site
      if (Instruction *i = dyn_cast<Instruction>(addr_var))
      {
        if (insts_before_ci.find(i) == insts_before_ci.end())
          continue;
      }
      if (!_PDG->hasNode(*addr_var))
        continue;
      auto addr_var_node = _PDG->getNode(*addr_var);
      addr_var_node->addNeighbor(*current_node, EdgeType::PARAMETER_IN);
    }

    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
  }
}

void pdg::ProgramDependencyGraph::connectActualOutTreeWithAddrVars(Tree &actual_out_tree, CallInst &ci)
{
  TreeNode *root_node = actual_out_tree.getRootNode();
  std::set<Instruction *> insts_after_ci = pdgutils::getInstructionAfterInst(ci);
  std::queue<TreeNode *> node_queue;
  node_queue.push(root_node);
  while (!node_queue.empty())
  {
    TreeNode *current_node = node_queue.front();
    node_queue.pop();
    for (auto addr_var : current_node->getAddrVars())
    {
      // only connect with succe insts of call sites
      if (Instruction *i = dyn_cast<Instruction>(addr_var))
      {
        if (insts_after_ci.find(i) == insts_after_ci.end())
          continue;
      }
      if (!_PDG->hasNode(*addr_var))
        continue;
      auto addr_var_node = _PDG->getNode(*addr_var);
      current_node->addNeighbor(*addr_var_node, EdgeType::PARAMETER_OUT);
    }

    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
  }
}

void pdg::ProgramDependencyGraph::connectTreeNode(TreeNode& src_node, TreeNode& dst_node, EdgeType edge_type)
{
  std::queue<std::pair<TreeNode *, TreeNode *>> node_pairs_queue;
  node_pairs_queue.push(std::make_pair(&src_node, &dst_node));
  while (!node_pairs_queue.empty())
  {
    auto current_node_pair = node_pairs_queue.front();
    node_pairs_queue.pop();
    TreeNode *src = current_node_pair.first;
    TreeNode *dst = current_node_pair.second;
    src->addNeighbor(*dst, edge_type);
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
    Tree *formal_in_tree = func_w->getArgFormalInTree(*arg);
    if (!formal_in_tree)
      return;
    connectFormalInTreeWithCallActualNode(*formal_in_tree);
  }
}

void pdg::ProgramDependencyGraph::connectFormalInTreeWithCallActualNode(Tree &formal_in_tree)
{
  TreeNode* root_node = formal_in_tree.getRootNode();
  std::queue<TreeNode*> node_queue;
  node_queue.push(root_node);
   
  while (!node_queue.empty())
  {
    TreeNode* current_node = node_queue.front();
    node_queue.pop();
    TreeNode* parent_node = current_node->getParentNode();
    std::unordered_set<Value*> parent_node_addr_vars;
    if (parent_node != nullptr)
      parent_node_addr_vars = parent_node->getAddrVars();
    for (auto addr_var : current_node->getAddrVars())
    {
      if (!_PDG->hasNode(*addr_var))
        continue;
      auto addr_var_node = _PDG->getNode(*addr_var);
      // check if the addr_var is used in call instruction
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
              Tree* arg_actual_in_tree = call_wrapper->getArgActualInTree(*addr_var);
              if (arg_actual_in_tree != nullptr)
              {
                auto arg_actual_in_tree_root_node = arg_actual_in_tree->getRootNode();
                if (arg_actual_in_tree_root_node != nullptr)
                {
                  connectTreeNode(*current_node, *arg_actual_in_tree_root_node, EdgeType::PARAMETER_IN);
                }
              }
            }
          }
        }
      }
    }
    
    // stop connecting rest nodes with addr vars if not field sensitive
    if (!FieldSensitive) 
      break;
    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
  }
}

static RegisterPass<pdg::ProgramDependencyGraph>
    PDG("pdg", "Program Dependency Graph Construction", false, true);