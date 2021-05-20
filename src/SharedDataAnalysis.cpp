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
  _call_graph = &PDGCallGraph::getInstance();
  // read driver/kernel domian funcs
  setupStrOps();
  readSentinelFields();
  readGlobalOpStructNames();
  setupDriverFuncs(M);
  setupKernelFuncs(M);
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
  computeSharedGlobalVars();
  if (!pdgutils::isFileExist("shared_struct_types"))
    dumpSharedTypes("shared_struct_types");
  // printPingPongCalls(M);
  return false;
}

void pdg::SharedDataAnalysis::setupStrOps()
{
  _string_op_names.insert("strcpy");
  _string_op_names.insert("strncpy");
  _string_op_names.insert("strlen");
  _string_op_names.insert("strlcpy");
  _string_op_names.insert("strcmp");
  _string_op_names.insert("strncmp");
  _string_op_names.insert("kobject_set_name");
}

void pdg::SharedDataAnalysis::setupDriverFuncs(Module &M)
{
  _driver_domain_funcs = readFuncsFromFile("driver_funcs", M);
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
    if (_driver_domain_funcs.find(&F) == _driver_domain_funcs.end())
      _kernel_domain_funcs.insert(&F);
  }
}

void pdg::SharedDataAnalysis::setupBoundaryFuncs(Module &M)
{
  auto imported_funcs = readFuncsFromFile("imported_funcs", M);
  auto exported_funcs = readFuncsFromFile("exported_funcs", M);

  if (EnableAnalysisStats)
  {
    auto &ksplit = KSplitStats::getInstance();
    ksplit.increaseKernelToDriverCallNum(exported_funcs.size());
    ksplit.increaseDriverToKernelCallNum(imported_funcs.size());
  }

  _boundary_funcs.insert(imported_funcs.begin(), imported_funcs.end());
  _boundary_funcs.insert(exported_funcs.begin(), exported_funcs.end());
  for (auto bf : _boundary_funcs)
  {
    _boundary_func_names.insert(bf->getName().str());
  }
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

std::set<Function *> pdg::SharedDataAnalysis::computeBoundaryTransitiveClosure()
{
  std::set<Function*> boundary_trans_funcs;
  for (auto boundary_func : _boundary_funcs)
  {
    if (_call_graph->isExcludeFunc(*boundary_func))
    {
      errs() << "found exclude func " << boundary_func->getName() << "\n";
      continue;
    }
    auto func_node = _call_graph->getNode(*boundary_func);
    assert(func_node != nullptr && "cannot get function node for computing transitive closure!");
    auto trans_func_nodes = _call_graph->computeTransitiveClosure(*func_node);
    for (auto n : trans_func_nodes)
    {
      if (Function *trans_func = dyn_cast<Function>(n->getValue()))
        boundary_trans_funcs.insert(trans_func);
    }
  }
  return boundary_trans_funcs;
}

void pdg::SharedDataAnalysis::computeSharedStructDITypes()
{
  std::set<std::string> driver_struct_type_names;
  for (auto func : _driver_domain_funcs)
  {
    if (func->isDeclaration())
      continue;
    for (auto inst_i = inst_begin(func); inst_i != inst_end(func); inst_i++)
    {
      Node *n = _PDG->getNode(*inst_i);
      if (!n)
        continue;
      DIType *node_di_type = n->getDIType();
      if (StoreInst *si = dyn_cast<StoreInst>(&*inst_i))
      {
        auto val_op = si->getValueOperand()->stripPointerCasts();
        Node *val_n = _PDG->getNode(*val_op);
        if (!val_n)
          continue;
        node_di_type = val_n->getDIType();
      }
      if (!node_di_type)
        continue;
      DIType *lowest_di_type = dbgutils::getLowestDIType(*node_di_type);
      if (lowest_di_type == nullptr)
        continue;
      if (dbgutils::isStructType(*lowest_di_type))
      {
        std::string di_type_name = dbgutils::getSourceLevelTypeName(*lowest_di_type, true);
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
  for (auto func : _kernel_domain_funcs)
  {
    if (func->isDeclaration())
      continue;
    for (auto inst_i = inst_begin(func); inst_i != inst_end(func); inst_i++)
    {
      Node *n = _PDG->getNode(*inst_i);
      if (!n)
        continue;
      DIType *node_di_type = n->getDIType();
      if (!node_di_type)
        continue;
      if (dbgutils::isStructType(*node_di_type) || dbgutils::isStructPointerType(*node_di_type))
      {
        DIType *lowest_di_type = dbgutils::getLowestDIType(*node_di_type);
        assert(lowest_di_type != nullptr && "null lowest di type (computeSharedStructTypes)\n");
        std::string struct_type_name = dbgutils::getSourceLevelTypeName(*lowest_di_type, true);
        struct_type_name = pdgutils::stripVersionTag(struct_type_name);
        if (processed_struct_names.find(struct_type_name) != processed_struct_names.end())
          continue;
        processed_struct_names.insert(struct_type_name);
        // check driver global type
        bool is_driver_global_struct_type = (_driver_global_struct_types.find(struct_type_name) != _driver_global_struct_types.end());

        if (driver_struct_type_names.find(struct_type_name) != driver_struct_type_names.end() || is_driver_global_struct_type)
          _shared_struct_di_types.insert(lowest_di_type);
      }
    }
  }

  for (auto f : _boundary_funcs)
  {
    if (f->isDeclaration())
      continue;
    auto fw = _PDG->getFuncWrapper(*f);
    for (auto arg : fw->getArgList())
    {
      auto arg_di_type = fw->getArgDIType(*arg);
      auto arg_lowest_di_type = dbgutils::getLowestDIType(*arg_di_type);
      if (arg_lowest_di_type != nullptr)
      {
        if (dbgutils::isStructType(*arg_lowest_di_type))
          _shared_struct_di_types.insert(arg_lowest_di_type);
      }
    }
  }
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
    TreeNode *root_node = new TreeNode(shared_struct_di_type, 0, nullptr, type_tree, GraphNodeType::GLOBAL_TYPE);
    std::string shared_struct_type_name = dbgutils::getSourceLevelTypeName(*shared_struct_di_type, true);
    _shared_struct_type_names.insert(shared_struct_type_name);
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
    Node *inst_node = _PDG->getNode(*inst_iter);
    if (!inst_node)
      continue;
    DIType *inst_di_type = inst_node->getDIType();
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
  // Function* driver_func = nullptr;
  // Function* kernel_func = nullptr;
  for (auto addr_var : addr_vars)
  {
    if (Instruction *i = dyn_cast<Instruction>(addr_var))
    {
      Function *f = i->getFunction();
      if (_driver_domain_funcs.find(f) != _driver_domain_funcs.end())
      {
        accessed_in_driver = true;
        // driver_func = f;
      }
      if (_kernel_domain_funcs.find(f) != _kernel_domain_funcs.end())
      {
        accessed_in_kernel = true;
        // kernel_func = f;
      }
    }

    if (accessed_in_driver && accessed_in_kernel)
      return true;
  }
  return false;
}

bool pdg::SharedDataAnalysis::isFieldUsedInStringOps(TreeNode &tree_node)
{
  auto addr_vars = tree_node.getAddrVars();
  for (auto addr_var : addr_vars)
  {
    for (auto user : addr_var->users())
    {
      if (CallInst *ci = dyn_cast<CallInst>(user))
      {
        auto called_func = pdgutils::getCalledFunc(*ci);
        if (called_func == nullptr)
          continue;
        std::string called_func_name = called_func->getName().str();
        if (_string_op_names.find(called_func_name) != _string_op_names.end())
          return true;
      }
    }
  }
  return false;
}

bool pdg::SharedDataAnalysis::isSharedFieldID(std::string field_id, std::string field_type_name)
{
  bool is_shared_id = (_shared_field_id.find(field_id) != _shared_field_id.end());
  // bool is_shared_struct_type = isSharedStructType(field_type_name);
  // return (is_shared_id || is_shared_struct_type && !field_type_name.empty());
  return is_shared_id;
}

void pdg::SharedDataAnalysis::computeSharedFieldID()
{
  for (auto dt_tree_pair : _global_struct_di_type_map)
  {
    // auto di_type_name = dbgutils::getSourceLevelTypeName(*dt_tree_pair.first);
    // di_type_name = "struct." + di_type_name;
    // auto gb = _module->getNamedValue(StringRef(di_type_name));

    Tree *tree = dt_tree_pair.second;
    std::queue<TreeNode *> node_queue;
    node_queue.push(tree->getRootNode());
    while (!node_queue.empty())
    {
      TreeNode *current_tree_node = node_queue.front();
      node_queue.pop();
      DIType *node_di_type = current_tree_node->getDIType();
      if (node_di_type == nullptr)
        continue;
      if (isStructFieldNode(*current_tree_node))
      {
        if (dbgutils::isFuncPointerType(*node_di_type) && current_tree_node->getParentNode() != nullptr)
          _shared_field_id.insert(pdgutils::computeTreeNodeID(*current_tree_node));
        else if (isTreeNodeShared(*current_tree_node))
        {
          auto field_id = pdgutils::computeTreeNodeID(*current_tree_node);
          _shared_field_id.insert(field_id);
          if (isFieldUsedInStringOps(*current_tree_node))
            _string_field_id.insert(field_id);
        }
        // here, we also check if a field is used as a string in any string manipulation functions
      }

      for (auto child : current_tree_node->getChildNodes())
      {
        node_queue.push(child);
      }
    }
  }
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
        if (_kernel_domain_funcs.find(func) != _kernel_domain_funcs.end())
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
  std::ifstream ReadFile("sentinel_fields");
  for (std::string line; std::getline(ReadFile, line);)
  {
    _sentinel_fields.insert(line);
  }
}

void pdg::SharedDataAnalysis::readGlobalOpStructNames()
{
  std::ifstream ReadFile("global_op_struct_names");
  for (std::string line; std::getline(ReadFile, line);)
  {
    _global_op_struct_names.insert(line);
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
      Function *caller = cast<Function>(node_val);
      if (opposite_domain_funcs.find(caller) != opposite_domain_funcs.end())
      {
        is_called = true;
        break;
      }
    }

    if (!is_called)
      continue;

    std::queue<Node *> node_queue;
    std::unordered_set<Node *> seen_node;
    node_queue.push(caller_node);
    while (!node_queue.empty())
    {
      Node *n = node_queue.front();
      node_queue.pop();
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
        node_queue.push(out_neighbor);
      }
    }
  }

  errs() << "================  ping pong call stats  ==================\n";
  errs() << "cross boundary times: " << cross_boundary_times << "\n";
  errs() << "num of boundary funcs: " << _boundary_funcs.size() << "\n";
  errs() << "==========================================================\n";
}

void pdg::SharedDataAnalysis::dumpSharedTypes(std::string file_name)
{
  std::ofstream output_file(file_name);
  for (auto shared_struct_type : _shared_struct_type_names)
  {
    if (!shared_struct_type.empty())
      output_file << shared_struct_type << "\n";
  }
  output_file.close();
}

static RegisterPass<pdg::SharedDataAnalysis>
    SharedDataAnalysis("shared-data", "Shared Data Analysis", false, true);