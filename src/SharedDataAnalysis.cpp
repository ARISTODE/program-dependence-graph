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
  _PDG = getAnalysis<ProgramDependencyGraph>().getPDG();
  // read driver/kernel domian funcs
  setupDriverFuncs(M);
  setupKernelFuncs(M);
  // get boundary functions
  setupBoundaryFuncs(M);
  // compute struct type passed through boundary (shared struct type)
  computeSharedStructDITypes();
  // build global tree for each struct type, connect with address variables
  buildTreesForSharedStructDIType(M);
  // generate shared field id
  computeSharedFieldID();
  dumpSharedFieldID();
  printPingPongCalls(M);
  return false;
}

void pdg::SharedDataAnalysis::setupDriverFuncs(Module &M)
{
  _driver_domain_funcs = readFuncsFromFile("driver_funcs", M);
}

void pdg::SharedDataAnalysis::setupKernelFuncs(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    if (_driver_domain_funcs.find(&F) == _driver_domain_funcs.end())
      _kernel_domain_funcs.insert(&F);
  }
}

void pdg::SharedDataAnalysis::setupBoundaryFuncs(Module &M)
{
  auto imported_funcs = readFuncsFromFile("imported_funcs", M);
  auto exported_funcs = readFuncsFromFile("exported_funcs", M);
  _boundary_funcs.insert(imported_funcs.begin(), imported_funcs.end());
  _boundary_funcs.insert(exported_funcs.begin(), exported_funcs.end());
}

std::set<Function *> pdg::SharedDataAnalysis::readFuncsFromFile(std::string file_name, Module &M)
{
  std::set<Function *> ret;
  std::ifstream ReadFile(file_name);
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

void pdg::SharedDataAnalysis::computeSharedStructDITypes()
{
  // case 1: for each struct pointer argument passed in boundary, consider the 
  // struct type as shared
  // for (auto F : _boundary_funcs)
  // {
  //   if (F->isDeclaration() || F->empty())
  //     continue;
  //   FunctionWrapper* fw = _PDG->getFuncWrapper(*F);
  //   for (auto &arg : F->args())
  //   {
  //     DIType* arg_di_type = fw->getArgDIType(arg);
  //     if (arg_di_type == nullptr)
  //       continue;
  //     if (!dbgutils::isStructPointerType(*arg_di_type))
  //       continue;
  //     DIType *arg_lowest_di_type = dbgutils::getLowestDIType(*arg_di_type);
  //     if (!arg_lowest_di_type)
  //       continue;
  //     if (dbgutils::isStructType(*arg_lowest_di_type))
  //       _shared_struct_di_types.insert(arg_lowest_di_type);
  //     // if (!arg_lowest_di_type)
  //     //   continue;
  //     // if (dbgutils::isStructType(*arg_lowest_di_type))
  //     // {
  //     //   auto contained_struct_di_types = dbgutils::computeContainedStructTypes(*arg_lowest_di_type);
  //     //   _shared_struct_di_types.insert(contained_struct_di_types.begin(), contained_struct_di_types.end());
  //     // }
  //   }
  // }

  // case 2: for struct types used in both domian, consider them as shared
  std::set<std::string> driver_struct_type_names;
  for (auto func : _driver_domain_funcs)
  {
    if (func->isDeclaration())
      continue;
    for (auto inst_i = inst_begin(func); inst_i != inst_end(func); inst_i++)
    {
      Node* n = _PDG->getNode(*inst_i);
      if (!n)
        continue;
      DIType* node_di_type = n->getDIType();
      if (StoreInst *si = dyn_cast<StoreInst>(&*inst_i))
      {
        auto val_op = si->getValueOperand()->stripPointerCasts();
        Node* val_n = _PDG->getNode(*val_op);
        if (!val_n)
          continue;
        node_di_type = val_n->getDIType();
      }
      if (!node_di_type)
        continue;
      DIType* lowest_di_type = dbgutils::getLowestDIType(*node_di_type);
      if (lowest_di_type == nullptr)
        continue;
      if (dbgutils::isStructType(*lowest_di_type))
        driver_struct_type_names.insert(dbgutils::getSourceLevelTypeName(*lowest_di_type));
    }
  }
  errs() << " === driver side struct types ===\n";
  for (auto t : driver_struct_type_names)
  {
    errs() << "\t" << t << "\n";
  }
  std::set<std::string> processed_struct_names;
  for (auto func : _kernel_domain_funcs)
  {
    if (func->isDeclaration())
      continue;
    for (auto inst_i = inst_begin(func); inst_i != inst_end(func); inst_i++)
    {
      Node* n = _PDG->getNode(*inst_i);
      if (!n)
        continue;
      DIType* node_di_type = n->getDIType();
      if (!node_di_type)
        continue;
      if (dbgutils::isStructType(*node_di_type) || dbgutils::isStructPointerType(*node_di_type))
      {
        DIType* lowest_di_type = dbgutils::getLowestDIType(*node_di_type);
        assert(lowest_di_type != nullptr && "null lowest di type (computeSharedStructTypes)\n");
        std::string struct_type_name = dbgutils::getSourceLevelTypeName(*lowest_di_type);
        struct_type_name = pdgutils::stripVersionTag(struct_type_name);
        if (processed_struct_names.find(struct_type_name) != processed_struct_names.end())
          continue;
        // errs() << "kernel struct type name: " << struct_type_name << "\n";
        processed_struct_names.insert(struct_type_name);
        if (driver_struct_type_names.find(struct_type_name) != driver_struct_type_names.end())
          _shared_struct_di_types.insert(lowest_di_type);
      }
    }
  }
  errs() << "found " << _shared_struct_di_types.size() << " shared struct types\n";
  errs() << " ==== shared types ====\n";
  for (auto t : _shared_struct_di_types)
  {
    errs() << "\t" << dbgutils::getSourceLevelTypeName(*t) << "\n";
  }
}

void pdg::SharedDataAnalysis::buildTreesForSharedStructDIType(Module &M)
{
  for (auto shared_struct_di_type : _shared_struct_di_types)
  {
    Tree *type_tree = new Tree();
    TreeNode *root_node = new TreeNode(shared_struct_di_type, 0, nullptr, type_tree, GraphNodeType::GLOBAL_TYPE);
    auto vars_with_di_type = computeVarsWithDITypeInModule(*shared_struct_di_type, M);
    for (auto var : vars_with_di_type)
    {
      root_node->addAddrVar(*var);
    }
    type_tree->setRootNode(*root_node);
    type_tree->build(2);
    connectTypeTreeToAddrVars(*type_tree);
    _global_struct_di_type_map.insert(std::make_pair(shared_struct_di_type, type_tree));
  }
}

void pdg::SharedDataAnalysis::connectTypeTreeToAddrVars(Tree &type_tree)
{
  TreeNode *root_node = type_tree.getRootNode();
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
      current_node->addNeighbor(*addr_var_node, EdgeType::VAL_DEP);
    }
    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
  }
}

void pdg::SharedDataAnalysis::computeVarsWithDITypeInFunc(DIType &dt, Function &F, std::set<Value *> &vars)
{
  for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); inst_iter++)
  {
    Node* inst_node = _PDG->getNode(*inst_iter);
    if (!inst_node)
      continue;
    DIType* inst_di_type = inst_node->getDIType();
    if (inst_di_type == nullptr)
      continue;
    // should also consider the pointer to the struct.
    DIType *inst_lowest_di_type = dbgutils::getLowestDIType(*inst_di_type);
    if (inst_lowest_di_type == nullptr)
      continue;
    if (dbgutils::hasSameDIName(dt, *inst_lowest_di_type))
      vars.insert(&*inst_iter);
  }
}

std::set<Value *> pdg::SharedDataAnalysis::computeVarsWithDITypeInModule(DIType &dt, Module &M)
{
  std::set<Value *> vars;
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    computeVarsWithDITypeInFunc(dt, F, vars);
  }
  return vars;
}

bool pdg::SharedDataAnalysis::isStructFieldNode(TreeNode &tree_node)
{
  auto parent_node = tree_node.getParentNode();
  if (!parent_node)
    return false;
  auto parent_node_di_type = parent_node->getDIType();
  if (!parent_node_di_type)
    return false;
  return dbgutils::isStructType(*parent_node_di_type);
}

bool pdg::SharedDataAnalysis::isTreeNodeShared(TreeNode &tree_node)
{
  auto addr_vars = tree_node.getAddrVars();
  bool accessed_in_driver = false;
  bool accessed_in_kernel = false;
  for (auto addr_var : addr_vars)
  {
    if (Instruction *i = dyn_cast<Instruction>(addr_var))
    {
      Function* f = i->getFunction();
      if (_driver_domain_funcs.find(f) != _driver_domain_funcs.end())
        accessed_in_driver = true;
      if (_kernel_domain_funcs.find(f) != _kernel_domain_funcs.end())
        accessed_in_kernel = true;
    }

    if (accessed_in_driver && accessed_in_kernel)
      return true;
  }
  return false;
}

bool pdg::SharedDataAnalysis::isSharedFieldID(std::string field_id)
{
  return (_shared_field_id.find(field_id) != _shared_field_id.end());
}

void pdg::SharedDataAnalysis::computeSharedDataVars()
{
  
}

void pdg::SharedDataAnalysis::computeSharedFieldID()
{
  for (auto dt_tree_pair : _global_struct_di_type_map)
  {
    Tree* tree = dt_tree_pair.second;
    std::queue<TreeNode*> node_queue;
    node_queue.push(tree->getRootNode());
    while (!node_queue.empty())
    {
      TreeNode *current_tree_node = node_queue.front();
      node_queue.pop();
      DIType* node_di_type = current_tree_node->getDIType();
      if (node_di_type == nullptr)
        continue;
      if (isStructFieldNode(*current_tree_node))
      {
        if (dbgutils::isFuncPointerType(*node_di_type) && current_tree_node->getParentNode() != nullptr)
          _shared_field_id.insert(pdgutils::computeTreeNodeID(*current_tree_node));
        else if (isTreeNodeShared(*current_tree_node))
          _shared_field_id.insert(pdgutils::computeTreeNodeID(*current_tree_node));
      }

      for (auto child : current_tree_node->getChildNodes())
      {
        node_queue.push(child);
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

    std::set<Function *> opposite_domain_funcs = _driver_domain_funcs;
    if (_driver_domain_funcs.find(f) != _driver_domain_funcs.end())
      opposite_domain_funcs = _kernel_domain_funcs;
    
    // check if this func can be called from the other domain.
    bool is_called = false;
    for (auto in_neighbor : caller_node->getInNeighbors())
    {
      auto node_val = in_neighbor->getValue();
      if (!isa<Function>(node_val))
        continue;
      Function* caller = cast<Function>(node_val);
      if (opposite_domain_funcs.find(caller) != opposite_domain_funcs.end())
      {
        is_called = true;
        break;
      }
    }

    if (!is_called)
      continue;
    
    std::queue<Node*> node_queue;
    std::unordered_set<Node *> seen_node;
    node_queue.push(caller_node);
    while (!node_queue.empty())
    {
      Node* n = node_queue.front();
      node_queue.pop();
      if (seen_node.find(n) != seen_node.end())
        continue;
      seen_node.insert(n);
      auto node_val = n->getValue();
      if (!isa<Function>(node_val))
        continue;
      Function* called_f = cast<Function>(node_val);
      if (opposite_domain_funcs.find(called_f) != opposite_domain_funcs.end())
      {
        cross_boundary_times++;
        break;
      }

      for (auto out_neighbor : n->getOutNeighbors())
      {
        node_queue.push(out_neighbor);
      }
    }
  }

  errs() << "================  ping pong call stats  ==================\n";
  errs() << "cross boundary times: " << cross_boundary_times << "\n";
  errs() << "num of boundary funcs: " << _boundary_funcs.size() << "\n";
  errs() << "==========================================================\n";
}

static RegisterPass<pdg::SharedDataAnalysis>
    SharedDataAnalysis("shared-data", "Shared Data Analysis", false, true);