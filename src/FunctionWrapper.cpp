#include "FunctionWrapper.hh"

using namespace llvm;

void pdg::FunctionWrapper::addInst(Instruction &i)
{
  if (AllocaInst *ai = dyn_cast<AllocaInst>(&i))
    _allocaInsts.push_back(ai);
  if (StoreInst *si = dyn_cast<StoreInst>(&i))
    _storeInsts.push_back(si);
  if (LoadInst *li = dyn_cast<LoadInst>(&i))
    _loadInsts.push_back(li);
  if (DbgDeclareInst *dbi = dyn_cast<DbgDeclareInst>(&i))
    _dbgDeclareInsts.push_back(dbi);
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    if (!isa<DbgDeclareInst>(&i))
      _callInsts.push_back(ci);
  }
  if (UnreachableInst *unreachableInst = dyn_cast<UnreachableInst>(&i))
    _unreachableInsts.push_back(unreachableInst);
  if (ReturnInst *reti = dyn_cast<ReturnInst>(&i))
    _returnInsts.push_back(reti);
}

DIType *pdg::FunctionWrapper::getArgDIType(Argument &arg)
{
  for (auto dbg_declare_inst : _dbgDeclareInsts)
  {
    DILocalVariable *di_local_var = dbg_declare_inst->getVariable();
    if (!di_local_var)
      continue;
    if (di_local_var->getArg() == arg.getArgNo() + 1 && !di_local_var->getName().str().empty() && di_local_var->getScope()->getSubprogram() == _func->getSubprogram())
      return di_local_var->getType();
  }
  return nullptr;
}

void pdg::FunctionWrapper::buildFormalTreeForArgs()
{
  for (auto arg : _argList)
  {
    DILocalVariable *di_local_var = getArgDILocalVar(*arg);
    AllocaInst *arg_alloca_inst = getArgAllocaInst(*arg);
    if (di_local_var == nullptr || arg_alloca_inst == nullptr)
    {
      if (DEBUG)
        errs() << "empty di local var: " << _func->getName().str() << (di_local_var == nullptr) << " - " << (arg_alloca_inst == nullptr) << "\n";
      continue;
    }
    Tree *arg_formal_in_tree = new Tree(*arg);
    TreeNode *formal_in_root_node = new TreeNode(*_func, di_local_var->getType(), 0, nullptr, arg_formal_in_tree, GraphNodeType::FORMAL_IN);
    formal_in_root_node->setDILocalVariable(*di_local_var);
    auto addr_taken_vars = pdgutils::computeAddrTakenVarsFromAlloc(*arg_alloca_inst);
    for (auto addr_taken_var : addr_taken_vars)
    {
      formal_in_root_node->addAddrVar(*addr_taken_var);
      // TODO: add alias
    }
    arg_formal_in_tree->setRootNode(*formal_in_root_node);
    arg_formal_in_tree->build();
    _argFormalInTreeMap.insert(std::make_pair(arg, arg_formal_in_tree));
    // build formal_out tree by copying fromal_in tree

    Tree *formalOutTree = new Tree(*arg_formal_in_tree);
    formalOutTree->setBaseVal(*arg);
    TreeNode *formal_out_root_node = formalOutTree->getRootNode();
    // copy address variables
    for (auto addrVar : formal_in_root_node->getAddrVars())
    {
      formal_out_root_node->addAddrVar(*addrVar);
    }
    formalOutTree->setTreeNodeType(GraphNodeType::FORMAL_OUT);
    formalOutTree->build();
    _argFormalOutTreeMap.insert(std::make_pair(arg, formalOutTree));
  }
}

void pdg::FunctionWrapper::buildFormalTreesForRetVal()
{
  Tree *ret_formal_in_tree = new Tree();
  DIType *funcRetDt = dbgutils::getFuncRetDIType(*_func);
  TreeNode *ret_formal_in_tree_root_node = new TreeNode(*_func, funcRetDt, 0, nullptr, ret_formal_in_tree, GraphNodeType::FORMAL_IN);
  for (auto ret_inst : _returnInsts)
  {
    auto ret_val = ret_inst->getReturnValue();
    if (ret_val != nullptr)
    {
      auto alias_vals = pdgutils::computeAliasForRetVal(*ret_val, *_func);
      ret_formal_in_tree_root_node->addAddrVar(*ret_val);
      for (auto alias_val : alias_vals)
      {
        ret_formal_in_tree_root_node->addAddrVar(*alias_val);
      }
    }
  }
  ret_formal_in_tree->setRootNode(*ret_formal_in_tree_root_node);
  ret_formal_in_tree->build();
  if ((_retValFormalInTree = ret_formal_in_tree))
  {

    Tree *ret_formal_out_tree = new Tree(*ret_formal_in_tree);
    TreeNode *ret_formal_out_tree_root_node = ret_formal_out_tree->getRootNode();
    // copy address variables
    for (auto addrVar : ret_formal_in_tree_root_node->getAddrVars())
    {
      ret_formal_out_tree_root_node->addAddrVar(*addrVar);
    }
    ret_formal_out_tree->setTreeNodeType(GraphNodeType::FORMAL_OUT);
    ret_formal_out_tree->build();
    _retValFormalOutTree = ret_formal_out_tree;
  }
}

DILocalVariable *pdg::FunctionWrapper::getArgDILocalVar(Argument &arg)
{
  for (auto dbg_declare_inst : _dbgDeclareInsts)
  {
    DILocalVariable *di_local_var = dbg_declare_inst->getVariable();
    if (!di_local_var)
      continue;
    // if (di_local_var->getArg() == arg.getArgNo() + 1 && !di_local_var->getName().str().empty() && di_local_var->getScope()->getSubprogram() == _func->getSubprogram())
    if (di_local_var->getArg() == arg.getArgNo() + 1 && !di_local_var->getName().str().empty() && di_local_var->getScope()->getSubprogram() == _func->getSubprogram())
      return di_local_var;
  }
  return nullptr;
}

AllocaInst *pdg::FunctionWrapper::getArgAllocaInst(Argument &arg)
{
  for (auto dbg_declare_inst : _dbgDeclareInsts)
  {
    DILocalVariable *di_local_var = dbg_declare_inst->getVariable();
    if (!di_local_var)
      continue;
    if (di_local_var->getArg() == arg.getArgNo() + 1 && !di_local_var->getName().str().empty() && di_local_var->getScope()->getSubprogram() == _func->getSubprogram())
    {
      if (AllocaInst *ai = dyn_cast<AllocaInst>(dbg_declare_inst->getVariableLocation()))
        return ai;
    }
  }
  return nullptr;
}

pdg::Tree *pdg::FunctionWrapper::getArgFormalInTree(Argument &arg)
{
  auto iter = _argFormalInTreeMap.find(&arg);
  if (iter == _argFormalInTreeMap.end())
    return nullptr;
  // assert(iter != _argFormalInTreeMap.end() && "cannot find formal tree for arg");
  return _argFormalInTreeMap[&arg];
}

pdg::Tree *pdg::FunctionWrapper::getArgFormalOutTree(Argument &arg)
{
  auto iter = _argFormalOutTreeMap.find(&arg);
  if (iter == _argFormalOutTreeMap.end())
    return nullptr;
  return _argFormalOutTreeMap[&arg];
}

std::set<Value *> pdg::FunctionWrapper::computeAddrVarDerivedFromArg(Argument &arg)
{
  auto arg_formal_in_tree = getArgFormalInTree(arg);
  std::set<Value *> ret;
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(arg_formal_in_tree->getRootNode());
  while (!nodeQueue.empty())
  {
    TreeNode *currentNode = nodeQueue.front();
    nodeQueue.pop();
    for (auto addrVar : currentNode->getAddrVars())
    {
      ret.insert(addrVar);
    }
    for (auto childNode : currentNode->getChildNodes())
    {
      nodeQueue.push(childNode);
    }
  }
  return ret;
}

int pdg::FunctionWrapper::getArgIdxByFormalInTree(pdg::Tree *tree)
{
  int idx = 0;
  for (auto iter : _argFormalInTreeMap)
  {
    if (iter.second == tree)
      return idx;
    idx++;
  }
  return -1;
}

DIType *pdg::FunctionWrapper::getReturnValDIType()
{
  return _retValFormalInTree->getRootNode()->getDIType();
}