#include "Graph.hh"

using namespace llvm;

void pdg::ProgramGraph::build(Module &M)
{
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
    }
    func_w->buildFormalTreeForArgs();
    _func_wrapper_map.insert(std::make_pair(&F, func_w));
  }

  // handle call sites
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    FunctionWrapper *func_w = new FunctionWrapper(&F);
    auto call_insts_in_func = func_w->getCallInsts();
    for (auto ci : call_insts_in_func)
    {
      auto called_func = pdgutils::getCalledFunc(*ci);
      if (called_func == nullptr)
        continue;
      if (!hasFuncWrapper(*called_func))
        continue;
      CallWrapper *cw = new CallWrapper(*ci);
      FunctionWrapper* callee_fw = getFuncWrapper(*called_func);
      cw->buildActualTreeForArgs(*callee_fw);
      _call_wrapper_map.insert(std::make_pair(ci, cw));
    }
  }
}

bool pdg::ProgramGraph::hasNode(Value &v)
{
  return (_val_node_map.find(&v) != _val_node_map.end());
}

pdg::Node *pdg::ProgramGraph::getNode(Value &v)
{
  if (!hasNode(v))
    return nullptr;
  return _val_node_map[&v];
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
      DIType* node_di_type = computeNodeDIType(n);
      n->setDIType(*node_di_type);
    }
  }
}

DIType *pdg::ProgramGraph::computeNodeDIType(Node *n)
{
  // TODO: global variable

  // local variable 
  Function* func = n->getFunc();
  if (!func)
    return nullptr;
  Value* val = n->getValue();
  if (!val) return nullptr;

  // alloc inst
  if (isa<AllocaInst>(val))
    return n->getDIType();
  // load inst
  if (LoadInst *li = dyn_cast<LoadInst>(val))
  {
    if (Instruction *load_addr = dyn_cast<Instruction>(li->getPointerOperand()))
    {
      Node* load_addr_node = getNode(*load_addr);
      DIType* load_addr_di_type = load_addr_node->getDIType();
      // DIType* retDIType = DIUtils::stripAttributes(sourceInstDIType);
      DIType *loaded_val_di_type = dbgutils::getLowestDIType(*load_addr_di_type);
      return loaded_val_di_type;
    }

    if (GlobalVariable *gv = dyn_cast<GlobalVariable>(li->getPointerOperand()))
    {
      DIType *global_var_di_type = dbgutils::getGlobalVarDIType(*gv);
      if (!global_var_di_type)
        return nullptr;
      return dbgutils::getLowestDIType(*global_var_di_type);
    }
  }
  // gep inst
  if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(val))
  {
    Value* base_addr = gep->getPointerOperand();
    Node* base_addr_node = getNode(*base_addr);
    DIType* base_addr_di_type = base_addr_node->getDIType();
    if (!base_addr_di_type)
      return nullptr;
    bool is_struct_or_struct_ptr = dbgutils::isStructType(*base_addr_di_type) || dbgutils::isStructPointerType(*base_addr_di_type);
    if (!is_struct_or_struct_ptr)
      return nullptr;
    DIType* base_addr_lowest_di_type = dbgutils::getLowestDIType(*base_addr_di_type);
    auto di_node_arr = dyn_cast<DICompositeType>(base_addr_lowest_di_type)->getElements();
    for (unsigned i = 0; i < di_node_arr.size(); ++i)
    {
      DIType *field_di_type = dyn_cast<DIType>(di_node_arr[i]);
      assert(field_di_type != nullptr && "fail to retrive field di type (computeNodeDIType)");
      if (pdgutils::isGEPOffsetMatchDIOffset(*field_di_type, *gep))
        return field_di_type;
    }
  }
  // cast inst
  if (CastInst *cast_inst = dyn_cast<CastInst>(val))
  {
    Value *casted_val = cast_inst->getOperand(0);
    Node* casted_val_node = getNode(*casted_val);
    return casted_val_node->getDIType();
  }

  // default
  return nullptr;
}