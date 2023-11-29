#include "SharedFieldsAnalysis.hh"

char pdg::SharedFieldsAnalysis::ID = 0;

using namespace llvm;

void pdg::SharedFieldsAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.setPreservesAll();
}

// this pass is used to compute shared fields between kernel and driver domain
bool pdg::SharedFieldsAnalysis::runOnModule(Module &M)
{
  _num_wild_cast = 0;
  // step 1: propagates debugging infomration for instructions
  unsigned num_defined_func = 0;
  unsigned num_undefined_func = 0;
  for (auto &F : M)
  {
    if (F.isDeclaration())
    {
      num_undefined_func++;
      continue;
    }
    propagateDebuggingInfoInFunc(F);
    num_defined_func++;
  }
  // step 2: obtain driver side functions
  readDriverFuncs(M);
  // step 3: compute accessed fields in driver/kernel domain
  computeAccessFields(M);
  // step 4: compute shared fields
  computeSharedAccessFields();
  dumpSharedFields();
  errs() << "number of unsafe casting: " << _num_wild_cast << "\n";
  errs() << "func num: " << num_defined_func << " / " << num_undefined_func << "\n";
  return false;
}

void pdg::SharedFieldsAnalysis::getDbgDeclareInstsInFunc(Function &F, std::set<DbgDeclareInst *> &dbg_insts)
{
  // obtain all the dbg declare inst and obtain debugging info
  for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
  {
    if (auto dbg_inst = dyn_cast<DbgDeclareInst>(&*instIter))
      dbg_insts.insert(dbg_inst);
  }
}

void pdg::SharedFieldsAnalysis::propagateDebuggingInfoInFunc(Function &F)
{
  std::set<DbgDeclareInst *> dbg_declare_insts;
  getDbgDeclareInstsInFunc(F, dbg_declare_insts);
  // bind ditype to the top-level pointer (alloca)
  for (auto dbg_declare_inst : dbg_declare_insts)
  {
    auto addr = dbg_declare_inst->getVariableLocation();
    auto DLV = dbg_declare_inst->getVariable(); // di local variable instance
    assert(DLV != nullptr && "cannot find DILocalVariable Node for computing DIType");
    DIType *var_di_type = DLV->getType();
    assert(var_di_type != nullptr && "cannot bind nullptr ditype to node!");
    insertValueDITypePair(addr, nullptr, var_di_type);
  }

  for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
  {
    Instruction &i = *instIter;
    auto dt_pair = computeInstDIType(i);
    if (dt_pair.first != nullptr)
      insertValueDITypePair(&i, dt_pair.second, dt_pair.first);
  }
}

std::pair<llvm::DIType *, llvm::DIType *> pdg::SharedFieldsAnalysis::computeInstDIType(Instruction &i)
{
  if (isa<AllocaInst>(&i))
  {
    if (_inst_ditype_map.find(&i) != _inst_ditype_map.end())
      return std::make_pair(_inst_ditype_map[&i].first, nullptr);
  }
  else if (LoadInst *li = dyn_cast<LoadInst>(&i))
  {
    if (Instruction *load_addr = dyn_cast<Instruction>(li->getPointerOperand()))
    {
      if (_inst_ditype_map.find(load_addr) == _inst_ditype_map.end())
      {
        errs() << "[WARNING]: empty di type on load address in func" << li->getFunction()->getName().str() << "\n";
        errs() << *load_addr << "\n";
        // assert(false);
      }
      DIType *load_addr_di_type = getValDIType(*load_addr);
      if (!load_addr_di_type)
        return std::pair<DIType *, DIType *>(nullptr, nullptr);
      DIType *loaded_val_di_type = dbgutils::getBaseDIType(*load_addr_di_type);
      if (loaded_val_di_type != nullptr)
        return std::make_pair(dbgutils::stripAttributes(*loaded_val_di_type), load_addr_di_type);
      return std::pair<DIType*, DIType*>(nullptr, nullptr);
    }
    else if (GlobalVariable *gv = dyn_cast<GlobalVariable>(li->getPointerOperand()))
    {
      DIType *global_var_di_type = dbgutils::getGlobalVarDIType(*gv);
      if (!global_var_di_type)
        return std::pair<DIType *, DIType *>(nullptr, nullptr);
      return std::make_pair(dbgutils::getBaseDIType(*global_var_di_type), global_var_di_type);
    }
  }
  else if (StoreInst *si = dyn_cast<StoreInst>(&i))
  {
    Value* value_operand = si->getValueOperand();
    Value* pointer_operand = si->getPointerOperand();
    DIType* ptr_op_di_type = getValDIType(*pointer_operand);
    if (ptr_op_di_type == nullptr)
      return std::pair<DIType *, DIType *>(nullptr, nullptr);
    DIType *value_op_di_type = dbgutils::getBaseDIType(*ptr_op_di_type);
    return std::make_pair(value_op_di_type, ptr_op_di_type);
  }
  else if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(&i))
  {
    Value* baseAddr = gep->getPointerOperand();
    auto base_addr_dt = getValDIType(*baseAddr);
    if (!base_addr_dt)
      return std::make_pair(nullptr, nullptr);
    DIType* baseAddrLowestDt = dbgutils::getLowestDIType(*base_addr_dt);
    if (!baseAddrLowestDt)
      return std::make_pair(nullptr, nullptr);
    if (!dbgutils::isStructType(*baseAddrLowestDt))
      return std::make_pair(nullptr, nullptr);
    if (auto dict = dyn_cast<DICompositeType>(baseAddrLowestDt))
    {
      auto di_node_arr = dict->getElements();
      for (unsigned i = 0; i < di_node_arr.size(); ++i)
      {
        DIType *field_di_type = dyn_cast<DIType>(di_node_arr[i]);
        assert(field_di_type != nullptr && "fail to retrive field di type (computeNodeDIType)");
        if (pdgutils::isGEPOffsetMatchDIOffset(*field_di_type, *gep))
          return std::make_pair(field_di_type, baseAddrLowestDt);
      }
    }
  }
  else if (CastInst *castInst = dyn_cast<CastInst>(&i))
  {
    Value *castedVal = castInst->getOperand(0);
    return getValDITypePair(*castedVal);
  }
  return std::make_pair(nullptr, nullptr);
}

void pdg::SharedFieldsAnalysis::insertValueDITypePair(Value *val, DIType* parentDt, DIType *fieldDt)
{
  if (_inst_ditype_map.find(val) != _inst_ditype_map.end())
    _inst_ditype_map[val] = std::make_pair(fieldDt, parentDt);
  else
    _inst_ditype_map.insert(std::make_pair(val, std::make_pair(fieldDt, parentDt)));
}

std::pair<DIType *, DIType *> pdg::SharedFieldsAnalysis::getValDITypePair(Value &val)
{
  if (_inst_ditype_map.find(&val) != _inst_ditype_map.end())
    return _inst_ditype_map[&val];
  return std::pair<DIType *, DIType *>(nullptr, nullptr);
}

DIType *pdg::SharedFieldsAnalysis::getValDIType(Value &val)
{
  if (_inst_ditype_map.find(&val) == _inst_ditype_map.end())
    return nullptr;
  auto pair = _inst_ditype_map[&val];
  return pair.first;
}

void pdg::SharedFieldsAnalysis::readDriverFuncs(Module &M)
{
  std::ifstream ReadFile("driver_funcs");
  for (std::string line; std::getline(ReadFile, line);)
  {
    Function *func = M.getFunction(StringRef(line));
    if (func != nullptr)
      _driver_funcs.insert(func);
  }
}

void pdg::SharedFieldsAnalysis::computeAccessFields(Module &M)
{
  // obtain a list of driver function names
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    if (isDriverFunc(F))
      computeAccessedFieldsInFunc(F, _driver_access_fields);
    else
      computeAccessedFieldsInFunc(F, _kernel_access_fields);
  }
}

void pdg::SharedFieldsAnalysis::printWarningsForUnsafeTypeCastsOnInst(Instruction &i)
{
  Function &F = *i.getFunction();
  for (auto user : i.users())
  {
    if (auto castInst = dyn_cast<CastInst>(user))
    {
      auto casting_type = castInst->getSrcTy();
      auto casted_type = castInst->getDestTy();
      // casting from a non-void ptr type to other types
      if (pdgutils::isStructPointerType(*casting_type) && pdgutils::isStructPointerType(*casted_type))
      {
        // if the casting value doesn't has debugging info, ignore this cast
        if (_inst_ditype_map.find(castInst->getOperand(0)) != _inst_ditype_map.end())
        {
          auto casting_source_type_name = dbgutils::getSourceLevelTypeName(*_inst_ditype_map[castInst->getOperand(0)].first);
          if (casting_source_type_name.find("union") != std::string::npos)
            continue;
          errs() << "casting source type: " << casting_source_type_name << "\n";
          errs() << "potential wild casting that may cause missing shared fields: " << F.getName().str() << " - " << *castInst << "\n";
          _num_wild_cast++;
        }
      }
    }
  }
}

void pdg::SharedFieldsAnalysis::computeAccessedFieldsInFunc(Function &F, std::set<std::string> & access_fields)
{
  for (auto instIter = inst_begin(F); instIter != inst_end(F); ++instIter)
  {
    Instruction* cur_inst = &*instIter;
    if (!isa<LoadInst>(cur_inst) && !isa<StoreInst>(cur_inst) && !isa<GetElementPtrInst>(cur_inst))
      continue;
    // for load, check the load addr. It refers to the loaded field
    if (LoadInst *li = dyn_cast<LoadInst>(cur_inst))
    {
      auto load_addr = li->getPointerOperand();
      auto dt_pair = getValDITypePair(*load_addr);
      if (!dt_pair.first || !dt_pair.second)
        continue;
      access_fields.insert(pdgutils::computeFieldID(*dt_pair.second, *dt_pair.first));
    }
    else if (StoreInst *si = dyn_cast<StoreInst>(cur_inst))
    {
      auto mod_addr = si->getPointerOperand();
      auto dt_pair = getValDITypePair(*mod_addr);
      if (!dt_pair.first || !dt_pair.second)
        continue;
      access_fields.insert(pdgutils::computeFieldID(*dt_pair.second, *dt_pair.first));
    }
    else if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(cur_inst))
    {
      auto gep_base_addr = gep->getPointerOperand();
      auto dt_pair = getValDITypePair(*gep_base_addr);
      if (!dt_pair.first || !dt_pair.second)
        continue;
      access_fields.insert(pdgutils::computeFieldID(*dt_pair.second, *dt_pair.first));
    }
    printWarningsForUnsafeTypeCastsOnInst(*cur_inst);
  }
}

void pdg::SharedFieldsAnalysis::computeSharedAccessFields()
{
  set_intersection(_driver_access_fields.begin(), _driver_access_fields.end(),
                   _kernel_access_fields.begin(), _kernel_access_fields.end(),
                   std::inserter(_shared_fields, _shared_fields.begin()));
}

void pdg::SharedFieldsAnalysis::dumpSharedFields()
{
  for (auto shared_field : _shared_fields)
  {
    errs() << shared_field << "\n";
  }
}

static RegisterPass<pdg::SharedFieldsAnalysis>
    SharedFieldsAnalysis("shared-fields", "Shared Fields Analysis", false, true);