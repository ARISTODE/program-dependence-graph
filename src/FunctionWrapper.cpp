#include "FunctionWrapper.hh"

using namespace llvm;

void pdg::FunctionWrapper::addInst(Instruction &i)
{
  if (AllocaInst *ai = dyn_cast<AllocaInst>(&i))
    _alloca_insts.push_back(ai);
  if (StoreInst *si = dyn_cast<StoreInst>(&i))
    _store_insts.push_back(si);
  if (LoadInst *li = dyn_cast<LoadInst>(&i))
    _load_insts.push_back(li);
  if (DbgDeclareInst *dbi = dyn_cast<DbgDeclareInst>(&i))
    _dbg_declare_insts.push_back(dbi);
  if (CallInst *ci = dyn_cast<CallInst>(&i))
  {
    if (!isa<DbgDeclareInst>(&i))
      _call_insts.push_back(ci);
  }
  if (ReturnInst *reti = dyn_cast<ReturnInst>(&i))
    _return_insts.push_back(reti);
}

DIType *pdg::FunctionWrapper::getArgDIType(Argument &arg)
{
  for (auto dbg_declare_inst : _dbg_declare_insts)
  {
    DILocalVariable *di_local_var = dbg_declare_inst->getVariable();
    if (!di_local_var)
      continue;
    if (di_local_var->getArg() == arg.getArgNo() + 1 && !di_local_var->getName().empty() && di_local_var->getScope()->getSubprogram() == _func->getSubprogram())
      return di_local_var->getType();
  }
  return nullptr;
}

void pdg::FunctionWrapper::buildFormalTreeForArgs()
{
  for (auto arg : _arg_list)
  {
    DILocalVariable* di_local_var = getArgDILocalVar(*arg);
    Value* arg_alloca_inst = getArgAllocaInst(*arg);
    if (di_local_var == nullptr || arg_alloca_inst == nullptr)
    {
      errs() << "empty di local var: " << _func->getName().str() << (di_local_var == nullptr) << " - " << (arg_alloca_inst == nullptr) << "\n";
      continue;
    }
    Tree *arg_formal_in_tree = new Tree(*arg);
    TreeNode *formal_in_root_node = new TreeNode(*arg, di_local_var->getType(), 0, nullptr, arg_formal_in_tree, GraphNodeType::FORMAL_IN);
    formal_in_root_node->setDILocalVariable(*di_local_var);
    formal_in_root_node->addAddrVar(*arg_alloca_inst);
    arg_formal_in_tree->setRootNode(*formal_in_root_node);
    arg_formal_in_tree->build();
    _arg_formal_in_tree_map.insert(std::make_pair(arg, arg_formal_in_tree));
    // build formal_out tree by copying fromal_in tree

    Tree* formal_out_tree = new Tree(*arg_formal_in_tree);
    formal_out_tree->setBaseVal(*arg);
    TreeNode* formal_out_root_node = formal_out_tree->getRootNode();
    // copy address variables
    for (auto addr_var : formal_in_root_node->getAddrVars())
    {
      formal_out_root_node->addAddrVar(*addr_var);
    }
    formal_out_tree->setTreeNodeType(GraphNodeType::FORMAL_OUT);
    formal_out_tree->build();
    _arg_formal_out_tree_map.insert(std::make_pair(arg, formal_out_tree));
  }
}

DILocalVariable *pdg::FunctionWrapper::getArgDILocalVar(Argument &arg)
{
  for (auto dbg_declare_inst : _dbg_declare_insts)
  {
    DILocalVariable *di_local_var = dbg_declare_inst->getVariable();
    if (!di_local_var)
      continue;
    // if (di_local_var->getArg() == arg.getArgNo() + 1 && !di_local_var->getName().empty() && di_local_var->getScope()->getSubprogram() == _func->getSubprogram())
    if (di_local_var->getArg() == arg.getArgNo() + 1 && !di_local_var->getName().empty() && di_local_var->getScope()->getSubprogram() == _func->getSubprogram())
      return di_local_var;
  }
  return nullptr;
}

Value *pdg::FunctionWrapper::getArgAllocaInst(Argument &arg)
{
  for (auto dbg_declare_inst : _dbg_declare_insts)
  {
    DILocalVariable *di_local_var = dbg_declare_inst->getVariable();
    if (!di_local_var)
      continue;
    if (di_local_var->getArg() == arg.getArgNo() + 1 && !di_local_var->getName().empty() && di_local_var->getScope()->getSubprogram() == _func->getSubprogram())
    {
      if (AllocaInst* ai = dyn_cast<AllocaInst>(dbg_declare_inst->getVariableLocation()))
        return dbg_declare_inst->getVariableLocation();
    }
  }
  return nullptr;
}

pdg::Tree *pdg::FunctionWrapper::getArgFormalInTree(Argument& arg)
{
  auto iter = _arg_formal_in_tree_map.find(&arg);
  if (iter == _arg_formal_in_tree_map.end())
    return nullptr;
  // assert(iter != _arg_formal_in_tree_map.end() && "cannot find formal tree for arg");
  return _arg_formal_in_tree_map[&arg];
}

pdg::Tree *pdg::FunctionWrapper::getArgFormalOutTree(Argument& arg)
{
  auto iter = _arg_formal_out_tree_map.find(&arg);
  if (iter == _arg_formal_out_tree_map.end())
    return nullptr;
  return _arg_formal_out_tree_map[&arg];
}