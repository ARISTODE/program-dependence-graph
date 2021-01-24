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
  for (auto F : _boundary_funcs)
  {
    if (F->isDeclaration() || F->empty())
      continue;
    FunctionWrapper* fw = _PDG->getFuncWrapper(*F);
    for (auto &arg : F->args())
    {
      DIType* arg_di_type = fw->getArgDIType(arg);
      DIType* arg_lowest_di_type = dbgutils::getLowestDIType(*arg_di_type);
      if (!arg_lowest_di_type)
        continue;
      if (dbgutils::isStructType(*arg_lowest_di_type))
      {
        auto contained_struct_di_types = dbgutils::computeContainedStructTypes(*arg_lowest_di_type);
        _shared_struct_di_types.insert(contained_struct_di_types.begin(), contained_struct_di_types.end());
      }
    }
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
    type_tree->build();
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
    if (!inst_di_type)
      continue;
    if (dbgutils::hasSameDIName(dt, *inst_di_type))
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
      TreeNode* current_tree_node = node_queue.front();
      node_queue.pop();
      if (isTreeNodeShared(*current_tree_node))
        _shared_field_id.insert(pdgutils::computeTreeNodeID(*current_tree_node));

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

static RegisterPass<pdg::SharedDataAnalysis>
    SharedDataAnalysis("shared-data", "Shared Data Analysis", false, true);