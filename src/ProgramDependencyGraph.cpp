#include "ProgramDependencyGraph.hh"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Debug.h"
#include <chrono>

using namespace llvm;

llvm::AnalysisKey pdg::ProgramDependencyGraph::Key;

cl::opt<bool> FieldSensitive("fs", cl::desc("Field Sensitive"), cl::value_desc("field_sensitive"), cl::init(true));
cl::opt<bool, true> EAS("analysis-stats", cl::desc("enable printing analysis stats"), cl::value_desc("analysis_stats"), cl::location(pdg::EnableAnalysisStats), cl::init(false));
cl::opt<bool, true> DBG("debug-verbose", cl::desc("enable printing verbose debug info"), cl::value_desc("verbose-debug"), cl::location(pdg::DEBUG), cl::init(false));

bool pdg::EnableAnalysisStats;
bool pdg::DEBUG;

pdg::ProgramDependencyGraph::Result pdg::ProgramDependencyGraph::run(Module &M, ModuleAnalysisManager &MAM) {
  auto start = std::chrono::high_resolution_clock::now();
  errs() << "Start building PDG\n";
  _module = &M;
  _PDG = &ProgramGraph::getInstance();

  PTAWrapper &ptaw = PTAWrapper::getInstance();
  PDGCallGraph &call_g = PDGCallGraph::getInstance();
  if (!call_g.isBuild())
    call_g.build(M);

  if (!_PDG->isBuild()) {
    _PDG->build(M);
    _PDG->bindDITypeToNodes(M);
  }

  if (!ptaw.hasPTASetup())
    ptaw.setupPTA(M);

  // connect global tree with addr vars
  for (auto pair : _PDG->getGlobalVarTreeMap()) {
    auto tree = pair.second;
    connectGlobalTreeWithAddrVars(*tree);
  }

  unsigned func_size = 0;
  for (auto &F : M) {
    if (F.isDeclaration() || !_PDG->hasFuncWrapper(F))
      continue;
    connectIntraprocDependencies(F, MAM);
    connectInterprocDependencies(F);
    func_size++;
  }

  errs() << "func size: " << func_size << "\n";
  errs() << "Finish adding dependencies\n";
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  errs() << "building PDG takes: " << duration.count() << "\n";
  errs() << "PDG Node size: " << _PDG->numNode() << "\n";
  return Result{_PDG};
}

void pdg::ProgramDependencyGraph::connectInTrees(Tree *src_tree, Tree *dst_tree, EdgeType edge_type) {
  if (src_tree->size() != dst_tree->size())
    return;
  auto src_tree_root_node = src_tree->getRootNode();
  auto dst_tree_root_node = dst_tree->getRootNode();
  std::queue<std::pair<TreeNode *, TreeNode *>> node_pairs_queue;
  node_pairs_queue.push(std::make_pair(src_tree_root_node, dst_tree_root_node));
  while (!node_pairs_queue.empty()) {
    auto current_node_pair = node_pairs_queue.front();
    node_pairs_queue.pop();
    TreeNode *src = current_node_pair.first;
    TreeNode *dst = current_node_pair.second;
    assert(src->numOfChild() == dst->numOfChild());
    src->addNeighbor(*dst, edge_type);
    auto src_node_children = src->getChildNodes();
    auto dst_node_children = dst->getChildNodes();
    for (int i = 0; i < src->numOfChild(); i++) {
      node_pairs_queue.push(std::make_pair(src_node_children[i], dst_node_children[i]));
    }
  }
}

void pdg::ProgramDependencyGraph::connectOutTrees(Tree *src_tree, Tree *dst_tree, EdgeType edge_type) {
  if (src_tree->size() != dst_tree->size())
    return;
  auto src_tree_root_node = src_tree->getRootNode();
  auto dst_tree_root_node = dst_tree->getRootNode();
  std::queue<std::pair<TreeNode *, TreeNode *>> node_pairs_queue;
  node_pairs_queue.push(std::make_pair(src_tree_root_node, dst_tree_root_node));
  while (!node_pairs_queue.empty()) {
    auto current_node_pair = node_pairs_queue.front();
    node_pairs_queue.pop();
    TreeNode *src = current_node_pair.first;
    TreeNode *dst = current_node_pair.second;
    assert(src->numOfChild() == dst->numOfChild());
    if (src->hasWriteAccess())
      src->addNeighbor(*dst, edge_type);
    auto src_node_children = src->getChildNodes();
    auto dst_node_children = dst->getChildNodes();
    for (int i = 0; i < src->numOfChild(); i++) {
      node_pairs_queue.push(std::make_pair(src_node_children[i], dst_node_children[i]));
    }
  }
}

void pdg::ProgramDependencyGraph::connectCallerAndCallee(CallWrapper &cw, FunctionWrapper &fw) {
  // step 1: connect call site node with the entry node of function
  auto call_site_node = _PDG->getNode(*cw.getCallInst());
  auto func_entry_node = fw.getEntryNode();
  if (call_site_node == nullptr || func_entry_node == nullptr)
    return;
  call_site_node->addNeighbor(*func_entry_node, EdgeType::CONTROLDEP_CALLINV);

  // don't expand field sensitive connection if not specified
  if (!FieldSensitive)
    return;
  
  // step 2: connect actual in -> formal in, formal out -> actual out
  auto actual_arg_list = cw.getArgList();
  auto formal_arg_list = fw.getArgList();
  assert(actual_arg_list.size() == formal_arg_list.size() &&
         "cannot connect tree edges due to unequal arg num! (connectCallerandCallee)");
  
  for (size_t i = 0; i < actual_arg_list.size(); ++i) {
    Value *actual_arg = actual_arg_list[i];
    Argument *formal_arg = formal_arg_list[i];

    auto actual_in_tree = cw.getArgActualInTree(*actual_arg);
    auto formal_in_tree = fw.getArgFormalInTree(*formal_arg);

    if (actual_in_tree && formal_in_tree) {
      _PDG->addTreeNodesToGraph(*actual_in_tree);
      connectInTrees(actual_in_tree, formal_in_tree, EdgeType::PARAMETER_IN);
    }

    auto actual_out_tree = cw.getArgActualOutTree(*actual_arg);
    auto formal_out_tree = fw.getArgFormalOutTree(*formal_arg);

    if (actual_out_tree && formal_out_tree) {
      _PDG->addTreeNodesToGraph(*actual_out_tree);
      connectOutTrees(formal_out_tree, actual_out_tree, EdgeType::PARAMETER_OUT);
    }
  }

  if (!fw.hasNullRetVal() && !cw.hasNullRetVal()) {
    Tree *ret_formal_in_tree = fw.getRetFormalInTree();
    Tree *ret_formal_out_tree = fw.getRetFormalOutTree();
    Tree *ret_actual_in_tree = cw.getRetActualInTree();
    Tree *ret_actual_out_tree = cw.getRetActualOutTree();

    if (ret_formal_in_tree && ret_formal_out_tree && ret_actual_in_tree && ret_actual_out_tree) {
      connectInTrees(ret_actual_in_tree, ret_formal_in_tree, EdgeType::PARAMETER_IN);
      connectInTrees(ret_actual_out_tree, ret_formal_out_tree, EdgeType::PARAMETER_OUT);
    }
  }

  // step4: connect both control/data return edges of callee to the call site
  auto ret_insts = fw.getReturnInsts();
  auto call_inst = cw.getCallInst();
  Node *dst = _PDG->getNode(*call_inst);
  assert(dst != nullptr && "cannot add control edge to call node on nullptr!\n");
  
  // add control return edge
  for (auto ret_inst : ret_insts) {
    Node *src = _PDG->getNode(*ret_inst);
    if (src == nullptr)
      continue;
    src->addNeighbor(*dst, EdgeType::CONTROLDEP_CALLRET);
  }
  
  // add data return edge
  for (auto ret_inst : ret_insts) {
    auto ret_val = ret_inst->getReturnValue();
    Node *src = _PDG->getNode(*ret_val);
    if (src && dst) {
      src->addNeighbor(*dst, EdgeType::DATA_RET);
    }
  }
}

// ===== connect intraprocedural dependencies =====
void pdg::ProgramDependencyGraph::connectIntraprocDependencies(Function &F, ModuleAnalysisManager &MAM) {
  // add control dependency edges
  auto &FAM = MAM.getResult<FunctionAnalysisManagerModuleProxy>(*_module).getManager();
  FAM.getResult<ControlDependencyGraph>(F);
  
  // connect formal tree with address variables
  FunctionWrapper *func_w = getFuncWrapper(F);
  Node *entry_node = func_w->getEntryNode();
  for (auto arg : func_w->getArgList()) {
    Tree *formal_in_tree = func_w->getArgFormalInTree(*arg);
    if (!formal_in_tree)
      return;
    Tree *formal_out_tree = func_w->getArgFormalOutTree(*arg);
    entry_node->addNeighbor(*formal_in_tree->getRootNode(), EdgeType::PARAMETER_IN);
    entry_node->addNeighbor(*formal_out_tree->getRootNode(), EdgeType::PARAMETER_OUT);
    connectFormalInTreeWithAddrVars(*formal_in_tree);
    connectFormalOutTreeWithAddrVars(*formal_out_tree);
  }

  if (!func_w->hasNullRetVal()) {
    connectFormalInTreeWithAddrVars(*func_w->getRetFormalInTree());
    connectFormalOutTreeWithAddrVars(*func_w->getRetFormalOutTree());
  }
}

void pdg::ProgramDependencyGraph::connectInterprocDependencies(Function &F) {
  auto &call_g = PDGCallGraph::getInstance();
  auto func_w = getFuncWrapper(F);
  auto call_insts = func_w->getCallInsts();
  for (auto call_inst : call_insts) {
    if (_PDG->hasCallWrapper(*call_inst)) {
      auto call_w = getCallWrapper(*call_inst);
      auto call_site_node = _PDG->getNode(*call_inst);
      if (!call_w || !call_site_node)
        continue;

      if (call_w->getCalledFunc() && call_w->getCalledFunc()->isVarArg()) 
        continue;

      if (FieldSensitive) {
        for (auto arg : call_w->getArgList()) {
          Tree *actual_in_tree = call_w->getArgActualInTree(*arg);
          if (!actual_in_tree) {
            continue;
          }
          Tree *actual_out_tree = call_w->getArgActualOutTree(*arg);
          connectActualInTreeWithAddrVars(*actual_in_tree, *call_inst);
          connectActualOutTreeWithAddrVars(*actual_out_tree, *call_inst);
        }
        // connect return trees
        if (!call_w->hasNullRetVal()) {
          connectActualOutTreeWithAddrVars(*call_w->getRetActualInTree(), *call_inst);
          connectActualOutTreeWithAddrVars(*call_w->getRetActualOutTree(), *call_inst);
        }
      }

      // direct call
      if (call_w->getCalledFunc() != nullptr) {
        auto called_func_w = getFuncWrapper(*call_w->getCalledFunc());
        connectCallerAndCallee(*call_w, *called_func_w);
      } else {
        // indirect call
        auto ind_called_funcs = call_g.getIndirectCallCandidates(*call_w->getCallInst(), *_module);
        for (auto ind_called_func : ind_called_funcs) {
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
void pdg::ProgramDependencyGraph::connectGlobalTreeWithAddrVars(Tree &globalVarTree) {
  TreeNode *rootNode = globalVarTree.getRootNode();
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);

  while (!nodeQueue.empty()) {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    TreeNode *parentNode = currentNode->getParentNode();
    std::unordered_set<Value *> parentNodeAddrVars;
    if (parentNode != nullptr)
      parentNodeAddrVars = parentNode->getAddrVars();

    for (auto addrVar : currentNode->getAddrVars()) {
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addrVarNode = _PDG->getNode(*addrVar);
      currentNode->addNeighbor(*addrVarNode, EdgeType::PARAMETER_IN);
      auto aliasNodes = addrVarNode->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
      for (auto aliasNode : aliasNodes) {
        Value *aliasNodeVal = aliasNode->getValue();
        if (aliasNodeVal == nullptr)
          continue;
        if (parentNodeAddrVars.find(aliasNodeVal) != parentNodeAddrVars.end())
          continue;
        if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(aliasNodeVal)) {
          if (!gep->hasAllZeroIndices())
            continue;
        }
        currentNode->addNeighbor(*aliasNode, EdgeType::PARAMETER_IN);
        currentNode->addAddrVar(*aliasNodeVal);
      }
    }

    for (auto childNode : currentNode->getChildNodes()) {
      nodeQueue.push(childNode);
    }
  }
}

void pdg::ProgramDependencyGraph::connectFormalInTreeWithAddrVars(Tree &formalInTree) {
  TreeNode *rootNode = formalInTree.getRootNode();
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);

  while (!nodeQueue.empty()) {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    currentNode->computeDerivedAddrVarsFromParent();
    TreeNode *parentNode = currentNode->getParentNode();
    std::unordered_set<Value *> parentNodeAddrVars;
    if (parentNode != nullptr)
      parentNodeAddrVars = parentNode->getAddrVars();

    for (auto childNode : currentNode->getChildNodes()) {
      nodeQueue.push(childNode);
    }

    auto nodeDIType = currentNode->getDIType();
    for (auto addrVar : currentNode->getAddrVars()) {
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addrVarNode = _PDG->getNode(*addrVar);
      currentNode->addNeighbor(*addrVarNode, EdgeType::PARAMETER_IN);
      // adding alias vars to tree's address var set
      auto aliasNodes = getAliasNodes(*addrVarNode);
      for (auto aliasNode : aliasNodes) {
        Value *aliasNodeVal = aliasNode->getValue();
        if (aliasNodeVal == nullptr)
          continue;
        if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(aliasNodeVal)) {
          // Skip confusing aliases for non-struct members
          if (!currentNode->isStructMember() && gep->hasAllZeroIndices())
            continue;
          // remove gep alias that doesn't match the offset.
          if (nodeDIType && !pdgutils::isGEPOffsetMatchDIOffset(*nodeDIType, *gep))
            continue;
        }
        currentNode->addAddrVar(*aliasNodeVal);
        currentNode->addNeighbor(*aliasNode, EdgeType::PARAMETER_IN);
      }
    }
  }
}

void pdg::ProgramDependencyGraph::connectFormalOutTreeWithAddrVars(Tree &formalOutTree) {
  TreeNode *rootNode = formalOutTree.getRootNode();
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);
  while (!nodeQueue.empty()) {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    for (auto addrVar : currentNode->getAddrVars()) {
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addrVarNode = _PDG->getNode(*addrVar);
      if (pdgutils::hasWriteAccess(*addrVar)) {
        addrVarNode->addNeighbor(*currentNode, EdgeType::PARAMETER_OUT);
        currentNode->addAccessTag(AccessTag::DATA_WRITE);
      }
    }

    if (!FieldSensitive)
      break;
    for (auto childNode : currentNode->getChildNodes()) {
      nodeQueue.push(childNode);
    }
  }
}

void pdg::ProgramDependencyGraph::connectActualInTreeWithAddrVars(Tree &actualInTree, CallInst &ci) {
  TreeNode *rootNode = actualInTree.getRootNode();
  std::set<Instruction *> insts_before_ci = pdgutils::getInstructionBeforeInst(ci);
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);
  while (!nodeQueue.empty()) {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    for (auto addrVar : currentNode->getAddrVars()) {
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addrVarNode = _PDG->getNode(*addrVar);
      addrVarNode->addNeighbor(*currentNode, EdgeType::PARAMETER_IN);
    }

    for (auto childNode : currentNode->getChildNodes()) {
      nodeQueue.push(childNode);
    }
  }
}

void pdg::ProgramDependencyGraph::connectActualOutTreeWithAddrVars(Tree &actualOutTree, CallInst &ci) {
  TreeNode *rootNode = actualOutTree.getRootNode();
  std::set<Instruction *> insts_after_ci = pdgutils::getInstructionAfterInst(ci);
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);
  while (!nodeQueue.empty()) {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    for (auto addrVar : currentNode->getAddrVars()) {
      if (Instruction *i = dyn_cast<Instruction>(addrVar)) {
        if (insts_after_ci.find(i) == insts_after_ci.end())
          continue;
      }
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addrVarNode = _PDG->getNode(*addrVar);
      currentNode->addNeighbor(*addrVarNode, EdgeType::PARAMETER_OUT);
    }

    for (auto childNode : currentNode->getChildNodes()) {
      nodeQueue.push(childNode);
    }
  }
}

void pdg::ProgramDependencyGraph::connectTreeNode(TreeNode &src_node, TreeNode &dstNode, EdgeType edgeTy) {
  std::queue<std::pair<TreeNode *, TreeNode *>> node_pairs_queue;
  node_pairs_queue.push(std::make_pair(&src_node, &dstNode));
  while (!node_pairs_queue.empty()) {
    auto current_node_pair = node_pairs_queue.front();
    node_pairs_queue.pop();
    TreeNode *src = current_node_pair.first;
    TreeNode *dst = current_node_pair.second;

    src->addNeighbor(*dst, edgeTy);
    if (src->numOfChild() == dst->numOfChild()) {
      auto src_node_children = src->getChildNodes();
      auto dst_node_children = dst->getChildNodes();
      for (int i = 0; i < src->numOfChild(); i++) {
        node_pairs_queue.push(std::make_pair(src_node_children[i], dst_node_children[i]));
      }
    }
  }
}

void pdg::ProgramDependencyGraph::connectFormalInTreeWithActualTree(Function &F) {
  FunctionWrapper *func_w = getFuncWrapper(F);
  for (auto arg : func_w->getArgList()) {
    Tree *formalInTree = func_w->getArgFormalInTree(*arg);
    if (!formalInTree)
      return;
    connectFormalInTreeWithCallActualNode(*formalInTree);
  }
}

void pdg::ProgramDependencyGraph::connectFormalInTreeWithCallActualNode(Tree &formalInTree) {
  TreeNode *rootNode = formalInTree.getRootNode();
  Function *func = rootNode->getFunc();
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);

  while (!nodeQueue.empty()) {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    TreeNode *parentNode = currentNode->getParentNode();
    std::unordered_set<Value *> parentNodeAddrVars;
    if (parentNode != nullptr)
      parentNodeAddrVars = parentNode->getAddrVars();
    for (auto addrVar : currentNode->getAddrVars()) {
      if (!_PDG->hasNode(*addrVar))
        continue;
      auto addrVarNode = _PDG->getNode(*addrVar);
      // check if the addrVar is used in call instruction
      // if so, connect the tree node with the actual tree of the call
      auto call_out_neighbors_cand = addrVarNode->getOutNeighborsWithDepType(EdgeType::DATA_DEF_USE);
      for (auto call_node : call_out_neighbors_cand) {
        if (call_node->getValue() != nullptr) {
          if (CallInst *ci = dyn_cast<CallInst>(call_node->getValue())) {
            auto called_func = pdgutils::getCalledFunc(*ci);
            if (called_func != nullptr && !called_func->isDeclaration()) {
              auto call_wrapper = getCallWrapper(*ci);
              Tree *arg_actual_in_tree = call_wrapper->getArgActualInTree(*addrVar);
              if (arg_actual_in_tree != nullptr) {
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
    for (auto childNode : currentNode->getChildNodes()) {
      nodeQueue.push(childNode);
    }
  }
}

void pdg::ProgramDependencyGraph::connectAddrVarsReachableFromInterprocFlow(Function &F) {
  FunctionWrapper *func_w = getFuncWrapper(F);
  for (auto arg : func_w->getArgList()) {
    Tree *formalInTree = func_w->getArgFormalInTree(*arg);
    if (!formalInTree)
      return;
    conntectFormalInTreeWithInterprocReachableAddrVars(*formalInTree);
  }
}

void pdg::ProgramDependencyGraph::conntectFormalInTreeWithInterprocReachableAddrVars(Tree &formalInTree) {
  TreeNode *rootNode = formalInTree.getRootNode();
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(rootNode);
  std::set<EdgeType> edgeTypes = {
      EdgeType::PARAMETER_IN,
  };
  Function *currentFunc = formalInTree.getFunc();
  if (currentFunc == nullptr)
    return;
  while (!nodeQueue.empty()) {
    auto currentNode = nodeQueue.front();
    nodeQueue.pop();
    auto reachable_nodes = _PDG->findNodesReachedByEdges(*currentNode, edgeTypes);
    for (auto n : reachable_nodes) {
      if (n->getValue() == nullptr)
        continue;

      if (n->getFunc() == currentFunc)
        currentNode->addAddrVar(*n->getValue());
    }

    for (auto childNode : currentNode->getChildNodes()) {
      nodeQueue.push(childNode);
    }
  }
}

std::set<pdg::Node *> pdg::ProgramDependencyGraph::getAliasNodes(pdg::Node &n) {
  std::queue<Node *> nodeQueue;
  std::set<Node *> seenNodes;
  std::set<Node *> aliasNodes;
  nodeQueue.push(&n);
  while (!nodeQueue.empty()) {
    auto currentNode = nodeQueue.front();
    nodeQueue.pop();
    auto outAliasNodes = currentNode->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
    for (auto aliasNode : outAliasNodes) {
      if (seenNodes.find(aliasNode) != seenNodes.end())
        continue;
      seenNodes.insert(aliasNode);
      nodeQueue.push(aliasNode);
      aliasNodes.insert(aliasNode);
    }
  }
  return aliasNodes;
}