#include "PDGUtils.hh"

using namespace llvm;

static std::set<std::string> dataWriteLibFuncs = {
  "__memcpy"
};

static std::set<std::string> asmWriteOpcode = {
  "bts"
};

StructType *pdg::pdgutils::getStructTypeFromGEP(GetElementPtrInst &gep)
{
  Value *baseAddr = gep.getPointerOperand();
  if (baseAddr->getType()->isPointerTy())
  {
    if (StructType *struct_type = dyn_cast<StructType>(baseAddr->getType()->getPointerElementType()))
      return struct_type;
  }
  return nullptr;
}

Function *pdg::pdgutils::getNescheckVersionFunc(Module &M, std::string func_name)
{
  Function* nescheck_func = M.getFunction(func_name);
  if (nescheck_func == nullptr || nescheck_func->isDeclaration())
  {
    std::string nescheck_func_name = func_name + "_nesCheck";
    nescheck_func = M.getFunction(nescheck_func_name);
    if (nescheck_func == nullptr || nescheck_func->isDeclaration())
      return nullptr;
  }
  return nescheck_func;
}

uint64_t pdg::pdgutils::getGEPOffsetInBits(Module& M, StructType &struct_type, GetElementPtrInst &gep)
{
  // get the accessed struct member offset from the gep instruction
  int gep_offset = getGEPAccessFieldOffset(gep);
  if (gep_offset == INT_MIN)
    return INT_MIN;
  // use the struct layout to figure out the offset in bits
  auto const &data_layout = M.getDataLayout();
  auto const struct_layout = data_layout.getStructLayout(&struct_type);
  if (gep_offset >= struct_type.getNumElements())
  {
    // errs() << "dubious gep access outof bound: " << gep << " in func " << gep.getFunction()->getName() << "\n";
    return INT_MIN;
  }
  uint64_t field_bit_offset = struct_layout->getElementOffsetInBits(gep_offset);
  // check if the gep may be used for accessing bit fields
  // if (isGEPforBitField(gep))
  // {
  //   // compute the accessed bit offset here
  //   if (auto LShrInst = dyn_cast<LShrOperator>(getLShrOnGep(gep)))
  //   {
  //     auto LShrOffsetOp = LShrInst->getOperand(1);
  //     if (ConstantInt *constInst = dyn_cast<ConstantInt>(LShrOffsetOp))
  //     {
  //       fieldOffsetInBits += constInst->getSExtValue();
  //     }
  //   }
  // }
  return field_bit_offset;
}

int pdg::pdgutils::getGEPAccessFieldOffset(GetElementPtrInst &gep)
{
  int operand_num = gep.getNumOperands();
  Value *last_idx = gep.getOperand(operand_num - 1);
  // cast the last_idx to int type
  if (ConstantInt *constInt = dyn_cast<ConstantInt>(last_idx))
  {
    auto access_idx = constInt->getSExtValue();
    if (access_idx < 0)
      return INT_MIN;
    return access_idx;
  }
  return INT_MIN;
}

bool pdg::pdgutils::isGEPOffsetMatchDIOffset(DIType &dt, GetElementPtrInst &gep)
{
  StructType *struct_ty = getStructTypeFromGEP(gep);
  if (!struct_ty)
    return false;
  Module &module = *(gep.getFunction()->getParent());
  uint64_t gep_bit_offset = getGEPOffsetInBits(module, *struct_ty, gep);

  if (gep_bit_offset < 0)
    return false;

  Value* lshr_op_inst = getLShrOnGep(gep);
  if (lshr_op_inst != nullptr)
  {
    if (auto lshr = dyn_cast<BinaryOperator>(lshr_op_inst))
    {
      if (lshr->getOpcode() == BinaryOperator::LShr)
      {
        auto shift_bits = lshr->getOperand(1); // constant int in llvm
        if (ConstantInt *ci = dyn_cast<ConstantInt>(shift_bits))
          gep_bit_offset += ci->getZExtValue(); // add the value as an unsigned integer
      }
    }
  }
  uint64_t di_type_bit_offset = dt.getOffsetInBits();
  
  if (gep_bit_offset == di_type_bit_offset)
    return true;
  return false;
}

bool pdg::pdgutils::isNodeBitOffsetMatchGEPBitOffset(Node &n, GetElementPtrInst &gep)
{
  StructType *struct_ty = getStructTypeFromGEP(gep);
  if (struct_ty == nullptr)
    return false;
  Module &module = *(gep.getFunction()->getParent());
  uint64_t gep_bit_offset = pdgutils::getGEPOffsetInBits(module, *struct_ty, gep);
  DIType* node_di_type = n.getDIType();
  if (node_di_type == nullptr || gep_bit_offset == INT_MIN)
    return false;
  uint64_t node_bit_offset = node_di_type->getOffsetInBits();
  if (gep_bit_offset == node_bit_offset)
    return true;
  return false;
}

// a wrapper func that strip pointer casts
Function *pdg::pdgutils::getCalledFunc(CallInst &call_inst)
{
  auto called_val = call_inst.getCalledOperand();
  if (!called_val)
    return nullptr;
  if (Function *func = dyn_cast<Function>(called_val->stripPointerCasts()))
    return func;
  return nullptr;
}

// check access type
bool pdg::pdgutils::hasReadAccess(Value &v)
{
  for (auto user : v.users())
  {
    if (isa<LoadInst>(user))
      return true;
    if (auto gep = dyn_cast<GetElementPtrInst>(user))
    {
      if (gep->getPointerOperand() == &v)
        return true;
    }
  }
  return false;
}

bool pdg::pdgutils::hasWriteAccess(Value &v)
{
  for (auto user : v.users())
  {
    if (auto si = dyn_cast<StoreInst>(user))
    {
      if (!isa<Argument>(si->getValueOperand()) && si->getPointerOperand() == &v)
        return true;
    }

    if (CallInst *ci = dyn_cast<CallInst>(user))
    {
      if (InlineAsm *ia = dyn_cast<InlineAsm>(ci->getCalledOperand()))
      {
        return hasAsmWriteAccess(*ia);
      }

      auto called_func = getCalledFunc(*ci);
      if (called_func == nullptr)
        continue;
      if (dataWriteLibFuncs.find(called_func->getName().str()) != dataWriteLibFuncs.end())
        return true;
    }
  }
  return false;
}

// ==== inst iterator related funcs =====

inst_iterator pdg::pdgutils::getInstIter(Instruction &i)
{
  Function *f = i.getFunction();
  for (auto inst_iter = inst_begin(f); inst_iter != inst_end(f); inst_iter++)
  {
    if (&*inst_iter == &i)
      return inst_iter;
  }
  return inst_end(f);
}

std::set<Instruction *> pdg::pdgutils::getInstructionBeforeInst(Instruction &i)
{
  Function *f = i.getFunction();
  auto stop = getInstIter(i);
  std::set<Instruction *> insts_before;
  for (auto inst_iter = inst_begin(f); inst_iter != inst_end(f); inst_iter++)
  {
    if (inst_iter == stop)
      return insts_before;
    insts_before.insert(&*inst_iter);
  }
  return insts_before;
}

std::set<Instruction *> pdg::pdgutils::getInstructionAfterInst(Instruction &i)
{
  Function *f = i.getFunction();
  std::set<Instruction *> insts_after;
  auto start = getInstIter(i);
  if (start == inst_end(f))
    return insts_after;
  start++;
  for (auto inst_iter = start; inst_iter != inst_end(f); inst_iter++)
  {
    insts_after.insert(&*inst_iter);
  }
  return insts_after;
}

std::set<Value *> pdg::pdgutils::computeAddrTakenVarsFromAlloc(AllocaInst &ai)
{
  std::set<Value *> addr_taken_vars;
  for (auto user : ai.users())
  {
    if (isa<LoadInst>(user))
      addr_taken_vars.insert(user);
  }
  return addr_taken_vars;
}

std::set<Value *> pdg::pdgutils::computeAliasForRetVal(Value &val, Function &F)
{
  std::set<Value *> ret;
  std::queue<Value *> val_queue;
  val_queue.push(&val);
  while (!val_queue.empty())
  {
    Value *cur_val = val_queue.front();
    val_queue.pop();

    for (auto instI = inst_begin(F); instI != inst_end(F); ++instI)
    {
      if (cur_val == &*instI)
        continue;
      if (queryAliasUnderApproximate(*cur_val, *instI) != NoAlias)
      {
        if (ret.find(&*instI) == ret.end())
        {
          ret.insert(&*instI);
          val_queue.push(&*instI);
        }
      }
    }
  }
  return ret;
}

std::set<std::string> pdg::pdgutils::splitStr(std::string split_str, std::string delimiter)
{
  std::set<std::string> ret_strs;
  size_t pos = 0;
  std::string token;
  while ((pos = split_str.find(delimiter)) != std::string::npos)
  {
    token = trimStr(split_str.substr(0, pos));
    ret_strs.insert(token);
    split_str.erase(0, pos + delimiter.length());
  }
  return ret_strs;
}

AliasResult pdg::pdgutils::queryAliasUnderApproximate(Value &v1, Value &v2)
{
  if (!v1.getType()->isPointerTy() || !v2.getType()->isPointerTy())
    return NoAlias;
  // check bit cast
  if (BitCastInst *bci = dyn_cast<BitCastInst>(&v1))
  {
    if (bci->getOperand(0) == &v2)
      return MustAlias;
  }
  // handle load instruction
  if (LoadInst *li = dyn_cast<LoadInst>(&v1))
  {
    auto load_addr = li->getPointerOperand();
    for (auto user : load_addr->users())
    {
      if (LoadInst *li = dyn_cast<LoadInst>(user))
      {
        if (li == &v2)
          return MustAlias;
      }

      if (StoreInst *si = dyn_cast<StoreInst>(user))
      {
        if (si->getPointerOperand() == load_addr)
        {
          if (si->getValueOperand() == &v2)
            return MustAlias;
        }
      }
    }
  }
  // handle gep
  if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(&v1))
  {
    if (gep->getPointerOperand() == &v2)
      return MustAlias;
  }
  return NoAlias;
}

void pdg::pdgutils::printTreeNodesLabel(Node *node, raw_string_ostream &OS, std::string tree_node_type_str)
{
  TreeNode *n = static_cast<TreeNode *>(node);
  int tree_node_depth = n->getDepth();
  DIType *node_di_type = n->getDIType();
  if (!node_di_type)
    return;
  std::string field_type_name = dbgutils::getSourceLevelTypeName(*node_di_type);
  OS << tree_node_type_str << " | " << tree_node_depth << " | " << field_type_name;
}

std::string pdg::pdgutils::stripFuncNameVersionNumber(std::string func_name)
{
  auto deli_pos = func_name.find('.');
  if (deli_pos == std::string::npos)
    return func_name;
  return func_name.substr(0, deli_pos);
}

std::string pdg::pdgutils::stripNescheckPostfix(std::string func_name)
{
  auto str_ref = StringRef(func_name);
  auto pos = str_ref.find("_nesCheck");
  if (pos != StringRef::npos)
    return str_ref.substr(0, pos).str();
  return func_name;
}

std::string pdg::pdgutils::getSourceFuncName(std::string func_name)
{
  return stripNescheckPostfix(stripFuncNameVersionNumber(func_name));
}

std::string pdg::pdgutils::computeTreeNodeID(TreeNode &tree_node)
{
  std::string parent_type_name = "";
  std::string node_field_name = "";
  TreeNode *parent_node = tree_node.getParentNode();
  if (parent_node != nullptr)
  {
    auto parent_di_type = dbgutils::stripMemberTag(*parent_node->getDIType());
    if (parent_di_type != nullptr)
      parent_type_name = dbgutils::getSourceLevelTypeName(*parent_di_type);
  }

  if (!tree_node.getDIType())
    return parent_type_name;
  DIType *node_di_type = dbgutils::stripAttributes(*tree_node.getDIType());
  node_field_name = dbgutils::getSourceLevelVariableName(*node_di_type);

  return trimStr(parent_type_name + node_field_name);
}

std::string pdg::pdgutils::computeFieldID(DIType &parent_dt, DIType &field_dt)
{
  auto parent_type_name = dbgutils::getSourceLevelTypeName(parent_dt, true);
  auto field_name = dbgutils::getSourceLevelVariableName(field_dt);
  if (parent_type_name.empty() || field_name.empty())
    return "";
  return trimStr(parent_type_name + field_name);
}

std::string pdg::pdgutils::stripVersionTag(std::string str)
{
  size_t pos = 0;
  size_t nth = 2;
  while (nth > 0)
  {
    pos = str.find(".", pos + 1);
    if (pos == std::string::npos)
      return str;
    nth--;
  }

  if (pos != std::string::npos)
    return str.substr(0, pos);
  return str;
}

Value *pdg::pdgutils::getLShrOnGep(GetElementPtrInst &gep)
{
  for (auto u : gep.users())
  {
    if (LoadInst *li = dyn_cast<LoadInst>(u))
    {
      for (auto user : li->users())
      {
        if (isa<BinaryOperator>(user))
          return user;
      }
    }
  }
  return nullptr;
}

std::string pdg::pdgutils::ltrim(std::string s)
{
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

std::string pdg::pdgutils::rtrim(std::string s)
{
  s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

std::string pdg::pdgutils::trimStr(std::string s)
{
  return ltrim(rtrim(s));
}

std::string pdg::pdgutils::constructAnnoStr(std::set<std::string> &annotations)
{
  std::string anno_str = "";
  for (auto anno_iter = annotations.begin(); anno_iter != annotations.end(); ++anno_iter)
  {
    anno_str += *anno_iter;
    if (std::next(anno_iter) != annotations.end())
      anno_str += ",";
  }
  if (!anno_str.empty())
    anno_str = "[" + anno_str + "]";
  return anno_str;
}

bool pdg::pdgutils::isSentinelType(GlobalVariable &gv)
{
  Type *ty = gv.getType();
  if (auto t = dyn_cast<PointerType>(ty))
    ty = t->getPointerElementType();
  // first check if this is an array type
  if (ArrayType *arr_ty = dyn_cast<ArrayType>(ty))
  {
    if (!arr_ty->getElementType()->isAggregateType())
      return false;
    auto arr_len = arr_ty->getNumElements();
    if (!gv.hasInitializer())
      return false;
    auto initializer = gv.getInitializer();
    // check if all elements other than the last one has non zero value
    bool non_zero_prev = true;
    for (unsigned i = 0; i < arr_ty->getNumElements() - 1; ++i)
    {
      if (initializer->getAggregateElement(i)->isZeroValue())
      {
        non_zero_prev = false;
        break;
      }
    }
    // check if the last element is zero value
    auto last_ele = initializer->getAggregateElement(arr_len - 1);
    if (non_zero_prev && last_ele->isZeroValue())
      return true;
  }
  return false;
}

bool pdg::pdgutils::isVoidPointerHasMultipleCasts(TreeNode &tree_node)
{
  std::set<Type *> casted_types;
  auto di_type = tree_node.getDIType();
  if (di_type == nullptr)
    return false;
  if (!dbgutils::isVoidPointerType(*di_type))
    return false;

  unsigned cast_count = 0;
  for (auto addr_var : tree_node.getAddrVars())
  {
    for (auto user : addr_var->users())
    {
      if (isa<BitCastInst>(user))
      {
        auto casted_type = user->getType();
        if (casted_types.find(casted_type) == casted_types.end())
        {
          casted_types.insert(casted_type);
          cast_count += 1;
        }
      }
    }
  }

  if (cast_count > 1) // the default would be 1 (void*), if only one casted type is used, then the number would be 2.
  {
    for (auto t : casted_types)
    {
      errs() << "casted type: " << *t << "\n";
    }
    return true;
  }
  return false;
}

bool pdg::pdgutils::hasAsmWriteAccess(InlineAsm &ia)
{
  auto asm_str = ia.getAsmString();
  auto op_code = asm_str.substr(0, asm_str.find(" "));
  if (isWriteAccessAsmOpcode(op_code))
    return true;
  return false;
}

bool pdg::pdgutils::isWriteAccessAsmOpcode(std::string op_code)
{
  return (asmWriteOpcode.find(op_code) != asmWriteOpcode.end());
}

bool pdg::pdgutils::isUserOfSentinelTypeVal(Value &v)
{
  if (ConstantExpr *ce = dyn_cast<ConstantExpr>(&v))
  {
    Instruction *i = ce->getAsInstruction();
    for (auto op_iter = i->op_begin(); op_iter != i->op_end(); ++op_iter)
    {
      if (GlobalVariable *gv = dyn_cast<GlobalVariable>(*op_iter))
      {
        if (isSentinelType(*gv))
          return true;
      }
    }
  }
  return false;
}

bool pdg::pdgutils::hasPtrArith(TreeNode &tree_node, bool is_shared_data)
{
  // auto &ksplit_stats = KSplitStats::getInstance();
  auto field_id = pdgutils::computeTreeNodeID(tree_node);

  // check if a field is
  for (auto addr_var : tree_node.getAddrVars())
  {
    // check if a field is used to derive pointer arithmetic for other field
    if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(addr_var))
    {
      if (gep->getType()->isStructTy())
        continue;
      for (auto user : gep->users())
      {
        if (isa<GetElementPtrInst>(user))
          return true;
        // {
        //   if (is_shared_data)
        //   {
        //     ksplit_stats.increasePtrGEPArithSDNum();
        //     // errs() << "SD find ptr arith (gep): " << field_id << " - " << gep->getFunction()->getName() << "\n";
        //   }
        //   else
        //   {
        //     ksplit_stats.increasePtrGEPArithDaaNum();
        //     // errs() << "DAA find ptr arith (gep): " << field_id << " - " << gep->getFunction()->getName() << "\n";
        //   }
        //   return true;
        // }
      }
    }

    // check if a field is directly used in pointer arithmetic computation
    for (auto user : addr_var->users())
    {
      if (auto var_user = dyn_cast<PtrToIntInst>(user))
      {
        // if (is_shared_data)
        // {
        //   errs() << "SD find ptr arith (ptrtoint): " << field_id << " - " << var_user->getFunction()->getName() << "\n";
        //   ksplit_stats.increasePtrtoIntArithSDNum();
        // }
        // else
        // {
        //   errs() << "DAA find ptr arith (ptrtoint): " << field_id << " - " << var_user->getFunction()->getName() << "\n";
        //   ksplit_stats.increasePtrtoIntArithDaaNum();
        // }
        return true;
      }
    }
  }
  return false;
}

bool pdg::pdgutils::isStructPointerType(Type &ty)
{
  if (!ty.isPointerTy())
    return false;
  auto ele_type = ty.getPointerElementType();
  if (ele_type->isStructTy())
    return true;
  return false;
}

bool pdg::pdgutils::isFileExist(std::string file_name)
{
  std::ifstream in_file(file_name);
  return in_file.good();
}

bool pdg::pdgutils::isSkbNode(TreeNode &tree_node)
{
  auto tree = tree_node.getTree();
  auto root_node = tree->getRootNode();
  auto root_node_dt = root_node->getDIType();
  std::string root_di_type_name_raw = dbgutils::getSourceLevelTypeName(*root_node_dt, true);
  return (root_di_type_name_raw == "sk_buff*" || root_di_type_name_raw == "skb_buff");
}
