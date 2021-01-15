#include "ProgramDependencyGraph.hh"
#include <chrono> 

using namespace llvm;

char pdg::ProgramDependencyGraph::ID = 0;

bool pdg::ProgramDependencyGraph::runOnModule(Module &M)
{
  auto start = std::chrono::high_resolution_clock::now();
  _module = &M;
  PDG = &ProgramGraph::getInstance();
  PDG->build(M);
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    connectIntraprocDependencies(F);
    connectInterprocDependencies(F);
  }
  errs() << "Finsh adding dependencies" << "\n";
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  errs() << "building PDG takes: " <<  duration.count() << "\n";
  return false;
}

void pdg::ProgramDependencyGraph::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<DataDependencyGraph>();
  AU.setPreservesAll();
}

void pdg::ProgramDependencyGraph::connectTrees(Tree* src_tree, Tree* dst_tree, EdgeType edge_type)
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

void pdg::ProgramDependencyGraph::connectCallerAndCallee(CallWrapper* cw, FunctionWrapper* fw)
{
  // step 1: connect call site node with the entry node of function
  auto call_site_node = PDG->getNode(*cw->getCallInst());
  auto func_entry_node = fw->getEntryNode();
  if (call_site_node == nullptr || func_entry_node == nullptr )
    return;
  call_site_node->addNeighbor(*func_entry_node, EdgeType::CALL);

  auto actual_arg_list = cw->getArgList();
  auto formal_arg_list = fw->getArgList();
  assert(actual_arg_list.size() == formal_arg_list.size() && "cannot connect tree edges due to inequal arg num! (connectCallerandCallee)");
  int num_arg = cw->getArgList().size();
  for (int i = 0; i < num_arg; i++)
  {
    Value *actual_arg = actual_arg_list[i];
    Argument *formal_arg =  formal_arg_list[i];
    // step 2: connect actual in -> formal in
    auto actual_in_tree = cw->getArgActualInTree(*actual_arg);
    auto formal_in_tree = fw->getArgFormalInTree(*formal_arg);
    connectTrees(actual_in_tree, formal_in_tree, EdgeType::PARAMETER_IN);
    // step 3: connect actual out -> formal out
    auto actual_out_tree = cw->getArgActualOutTree(*actual_arg);
    auto formal_out_tree = fw->getArgFormalOutTree(*formal_arg);
    connectTrees(actual_out_tree, formal_out_tree, EdgeType::PARAMETER_OUT);
  }

  // step4: connect return value of callee to the call site
  auto ret_insts = fw->getReturnInsts();
  auto call_inst = cw->getCallInst();
  for (auto ret_inst : ret_insts)
  {
    Node *src = PDG->getNode(*ret_inst);
    Node *dst = PDG->getNode(*call_inst);
    if (src == nullptr || dst == nullptr)
      continue;
    src->addNeighbor(*dst, EdgeType::DATA_RET);
  }
}

// ===== connect dependencies =====
void pdg::ProgramDependencyGraph::connectIntraprocDependencies(Function &F)
{
  // analyze data dependencies
  //getAnalysis<ControlDependencyGraph>(F); // add data dependencies for nodes in F
  getAnalysis<DataDependencyGraph>(F); // add data dependencies for nodes in F
}

void pdg::ProgramDependencyGraph::connectInterprocDependencies(Function &F)
{
  auto func_w = getFuncWrapper(F);
  auto call_insts = func_w->getCallInsts();
  for (auto call_inst : call_insts)
  {
    if (PDG->hasCallWrapper(*call_inst))
    {
      auto call_w = getCallWrapper(*call_inst);
      connectCallerAndCallee(call_w, func_w);
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
    for (auto addr_var : current_node->getAddrVars())
    {
      if (!PDG->hasNode(*addr_var))
        continue;
      auto addr_var_node = PDG->getNode(*addr_var);
      current_node->addNeighbor(*addr_var_node, EdgeType::PARAMETER_IN);
    }

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
      if (!PDG->hasNode(*addr_var))
        continue;
      auto addr_var_node = PDG->getNode(*addr_var);
      // TODO: add addr variables for formal out tree
      if (pdgutils::hasWriteAccess(*addr_var))
        addr_var_node->addNeighbor(*current_node, EdgeType::PARAMETER_OUT);
    }

    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
  }
}

// void pdg::ProgramDependencyGraph::connectActualInTreeWithAddrVars(Tree *actual_in_tree)
// {
// }

// void pdg::ProgramDependencyGraph::connectActualOutTreeWithAddrVars(Tree *actual_out_tree)
// {
// }

static RegisterPass<pdg::ProgramDependencyGraph>
    PDG("pdg", "Program Dependency Graph Construction", false, true);