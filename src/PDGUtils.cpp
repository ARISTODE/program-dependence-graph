#include "PDGUtils.hh"

using namespace llvm;

static std::set<std::string> dataWriteLibFuncs = {
    "__memcpy",
    "snprintf"};

static std::set<std::string> asmWriteOpcode = {
    "bts"};

StructType *pdg::pdgutils::getStructTypeFromGEP(GetElementPtrInst &gep)
{
  Value *baseAddr = gep.getPointerOperand();
  if (baseAddr->getType()->isPointerTy())
  {
    if (StructType *structTy = dyn_cast<StructType>(baseAddr->getType()->getPointerElementType()))
      return structTy;
  }
  return nullptr;
}

Function *pdg::pdgutils::getNescheckVersionFunc(Module &M, std::string funcName)
{
  Function *nescheck_func = M.getFunction(funcName);
  if (nescheck_func == nullptr || nescheck_func->isDeclaration())
  {
    std::string nescheck_func_name = funcName + "_nesCheck";
    nescheck_func = M.getFunction(nescheck_func_name);
    if (nescheck_func == nullptr || nescheck_func->isDeclaration())
      return nullptr;
  }
  return nescheck_func;
}

uint64_t pdg::pdgutils::getGEPOffsetInBits(Module &M, StructType &structTy, GetElementPtrInst &gep)
{
  // get the accessed struct member offset from the gep instruction
  int gep_offset = getGEPAccessFieldOffset(gep);
  if (gep_offset == INT_MIN)
    return INT_MIN;
  // use the struct layout to figure out the offset in bits
  auto const &data_layout = M.getDataLayout();
  auto const struct_layout = data_layout.getStructLayout(&structTy);
  if (gep_offset >= structTy.getNumElements())
  {
    // errs() << "dubious gep access outof bound: " << gep << " in func " << gep.getFunction()->getName() << "\n";
    return INT_MIN;
  }
  uint64_t field_bit_offset = struct_layout->getElementOffsetInBits(gep_offset);
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


  Value *lshr_op_inst = getLShrOnGep(gep);
  if (lshr_op_inst != nullptr)
  {
    if (auto lshr = dyn_cast<BinaryOperator>(lshr_op_inst))
    {
      if (lshr->getOpcode() == BinaryOperator::LShr)
      {
        auto shift_bits = lshr->getOperand(1); // constant int in llvm
        if (ConstantInt *ci = dyn_cast<ConstantInt>(shift_bits))
        {
          gep_bit_offset += ci->getZExtValue(); // add the value as an unsigned integer
          if (dbgutils::getSourceLevelVariableName(dt) == "__pkt_type_offset" && gep.getFunction()->getName() == "skb_checksum_help")
          {
            errs() << "Checking pkt type offset: " << gep_bit_offset << " - " << dt.getOffsetInBits() << " - " << ci->getZExtValue() << "\n";
            errs() << gep << "\n";
          }
          if (dbgutils::getSourceLevelVariableName(dt) == "ip_summed" && gep.getFunction()->getName() == "skb_checksum_help")
          {
            errs() << "ip_summed offset: " << dt.getOffsetInBits() << "\n";
          }
        }
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
  DIType *nodeDt = n.getDIType();
  if (nodeDt == nullptr || gep_bit_offset == INT_MIN)
    return false;
  uint64_t node_bit_offset = nodeDt->getOffsetInBits();
  if (gep_bit_offset == node_bit_offset)
    return true;
  return false;
}

// a wrapper func that strip pointer casts
Function *pdg::pdgutils::getCalledFunc(CallInst &callInst)
{
  auto called_val = callInst.getCalledOperand();
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
    if (isa<CallInst>(user))
      return true;
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

bool pdg::pdgutils::hasPtrDereference(Value &v)
{
  if (!v.getType()->isPointerTy())
    return false;
 
  // ignore cases that load from stack address
  if (isa<AllocaInst>(&v))
    return false;

  for (auto user : v.users())
  {
    if (isa<LoadInst>(user))
      return true;
  }
  return false;  
}

// ==== inst iterator related funcs =====

inst_iterator pdg::pdgutils::getInstIter(Instruction &i)
{
  Function *f = i.getFunction();
  for (auto instIter = inst_begin(f); instIter != inst_end(f); instIter++)
  {
    if (&*instIter == &i)
      return instIter;
  }
  return inst_end(f);
}

std::set<Instruction *> pdg::pdgutils::getInstructionBeforeInst(Instruction &i)
{
  Function *f = i.getFunction();
  auto stop = getInstIter(i);
  std::set<Instruction *> insts_before;
  for (auto instIter = inst_begin(f); instIter != inst_end(f); instIter++)
  {
    if (instIter == stop)
      return insts_before;
    insts_before.insert(&*instIter);
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
  for (auto instIter = start; instIter != inst_end(f); instIter++)
  {
    insts_after.insert(&*instIter);
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

void pdg::pdgutils::printTreeNodesLabel(Node *node, raw_string_ostream &OS, std::string treeNodeTyStr)
{
  TreeNode *n = static_cast<TreeNode *>(node);
  int treeNode_depth = n->getDepth();
  DIType *nodeDt = n->getDIType();
  if (!nodeDt)
    return;
  std::string field_type_name = dbgutils::getSourceLevelTypeName(*nodeDt);
  OS << treeNodeTyStr << " | " << treeNode_depth << " | " << field_type_name;
}

std::string pdg::pdgutils::stripFuncNameVersionNumber(std::string funcName)
{
  auto deli_pos = funcName.find('.');
  if (deli_pos == std::string::npos)
    return funcName;
  return funcName.substr(0, deli_pos);
}

std::string pdg::pdgutils::stripNescheckPostfix(std::string funcName)
{
  auto str_ref = StringRef(funcName);
  auto pos = str_ref.find("_nesCheck");
  if (pos != StringRef::npos)
    return str_ref.substr(0, pos).str();
  return funcName;
}

std::string pdg::pdgutils::getSourceFuncName(std::string funcName)
{
  return stripNescheckPostfix(stripFuncNameVersionNumber(funcName));
}

std::string pdg::pdgutils::computeTreeNodeID(TreeNode &treeNode)
{
  std::string parent_type_name = "";
  std::string node_field_name = "";
  TreeNode *parentNode = treeNode.getParentNode();
  if (parentNode != nullptr)
  {
    auto parent_di_type = dbgutils::stripMemberTag(*parentNode->getDIType());
    if (parent_di_type != nullptr)
      parent_type_name = dbgutils::getSourceLevelTypeName(*parent_di_type);
  }

  if (!treeNode.getDIType())
    return parent_type_name;
  DIType *nodeDt = dbgutils::stripAttributes(*treeNode.getDIType());
  node_field_name = dbgutils::getSourceLevelVariableName(*nodeDt);

  return trimStr(parent_type_name + node_field_name);
}

std::string pdg::pdgutils::computeFieldID(DIType &parentDt, DIType &fieldDt)
{
  auto parent_type_name = dbgutils::getSourceLevelTypeName(parentDt, true);
  auto fieldName = dbgutils::getSourceLevelVariableName(fieldDt);
  if (parent_type_name.empty() || fieldName.empty())
    return "";
  return trimStr(parent_type_name + fieldName);
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
  std::string annoStr = "";
  for (auto anno_iter = annotations.begin(); anno_iter != annotations.end(); ++anno_iter)
  {
    annoStr += *anno_iter;
    if (std::next(anno_iter) != annotations.end())
      annoStr += ",";
  }
  if (!annoStr.empty())
    annoStr = "[" + annoStr + "]";
  return annoStr;
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

bool pdg::pdgutils::isVoidPointerHasMultipleCasts(TreeNode &treeNode)
{
  std::set<Type *> casted_types;
  auto di_type = treeNode.getDIType();
  if (di_type == nullptr)
    return false;
  if (!dbgutils::isVoidPointerType(*di_type))
    return false;

  unsigned cast_count = 0;
  for (auto addrVar : treeNode.getAddrVars())
  {
    for (auto user : addrVar->users())
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
  auto opCode = asm_str.substr(0, asm_str.find(" "));
  if (isWriteAccessAsmOpcode(opCode))
    return true;
  return false;
}

bool pdg::pdgutils::isWriteAccessAsmOpcode(std::string opCode)
{
  return (asmWriteOpcode.find(opCode) != asmWriteOpcode.end());
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

/*
Pointer arithmetic can be used to compute array index access
or index a struct field. 
We need to differentiate two cases, 
*/

// check if a gep instruction is used to index a struct field

bool pdg::pdgutils::isValueUsedAsOffset(Value &v)
{
  for (const User *U : v.users())
  {
    // Check if the use is a GEP instruction
    if (const GetElementPtrInst *GEP = dyn_cast<GetElementPtrInst>(U))
    {
      // if the value is used as the base pointer, then it is not used as an offset
      if (GEP->getPointerOperand() == &v)
        continue;
      errs() << "Value is used as an offset to index into a memory region\n";
      return true;
    }
  }
  return false;
}

bool pdg::pdgutils::isTreeNodeValUsedAsOffset(TreeNode &treeNode)
{
  for (auto addrVar : treeNode.getAddrVars())
  {
    if (isValueUsedAsOffset(*addrVar))
      return true;
  }
  return false;
}

bool pdg::pdgutils::hasPtrArith(TreeNode &treeNode, bool isSharedData)
{
  // auto &ksplit_stats = KSplitStats::getInstance();
  auto fieldID = pdgutils::computeTreeNodeID(treeNode);
  std::string funcName = "";
  if (treeNode.getFunc())
    funcName = treeNode.getFunc()->getName().str();
  // check if a field is used in pointer arithemetic
  for (auto addrVar : treeNode.getAddrVars())
  {
    // check if a field is used to derive pointer for other fields
    if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(addrVar))
    {
      if (gep->getType()->isStructTy())
        continue;
    }

    // check if a field is directly used in pointer arithmetic computation
    for (auto user : addrVar->users())
    {
      if (isa<PtrToIntInst>(user))
      {
        errs() << "find ptr arith on " << fieldID << " in func " << funcName << "\n";
        return true;
      }
      if (isa<GetElementPtrInst>(user))
      {
        errs() << "find ptr arith on " << fieldID << " in func " << funcName << "\n";
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

bool pdg::pdgutils::isDoublePointer(Value &ptr)
{
  if (PointerType *PT = dyn_cast<PointerType>(ptr.getType()))
  {
    if (PointerType *ET = dyn_cast<PointerType>(PT->getElementType()))
    {
      return true;
    }
  }
  return false;
}

bool pdg::pdgutils::isMainFunc(Function &F)
{
  return F.getName() == "main";
}

bool pdg::pdgutils::isFileExist(std::string fileName)
{
  std::ifstream in_file(fileName);
  return in_file.good();
}

bool pdg::pdgutils::isSkbNode(TreeNode &treeNode)
{
  auto tree = treeNode.getTree();
  auto rootNode = tree->getRootNode();
  auto root_node_dt = rootNode->getDIType();
  std::string root_di_type_name_raw = dbgutils::getSourceLevelTypeName(*root_node_dt, true);
  return (root_di_type_name_raw == "sk_buff*" || root_di_type_name_raw == "skb_buff");
}

// check if i1 is precede of i2
bool pdg::pdgutils::isPrecedeInst(Instruction &i1, Instruction &i2, Function &F)
{
  for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
  {
    auto &curInst = *instIter;
    if (&curInst == &i1)
      return true;
    if (&curInst == &i2)
      return false;
  }
  return false;
}

void pdg::pdgutils::printTreeNodeAddrVars(TreeNode &treeNode)
{
  errs() << "tree node addr vars: ";
  for (auto addrVar : treeNode.getAddrVars())
  {
    if (auto inst = dyn_cast<Instruction>(addrVar))
    errs() << "\tfunc name: " << inst->getFunction()->getName()  << *inst <<  "\n";
  }
}

std::string pdg::pdgutils::getDemangledName(const char* mangledName)
{
  int status = 0;
  char* demangledName = llvm::itaniumDemangle(mangledName, nullptr, nullptr, &status);
  if (!demangledName)
    return std::string(mangledName);
  std::string ret(demangledName);
  free(demangledName);
  // Find the beginning of the function name.
  size_t startPos = ret.find_first_not_of(" \t\n\r");
  if (startPos == std::string::npos) {
    return "";
  }
  // Find the end of the function name.
  size_t endPos = ret.find_first_of(" \t\n\r(", startPos);
  if (endPos == std::string::npos) {
    return "";
  }
  // Extract the function name and return it.
  return ret.substr(startPos, endPos - startPos);
}

void pdg::pdgutils::readLinesFromFile(std::set<std::string> &lines, std::string fileName)
{
  std::ifstream file(fileName); // Open file
  if (file.is_open())
  {
    std::string line;
    while (getline(file, line))
    {                   // Read each line
    lines.insert(line); // Insert line into set
    }
    file.close(); // Close file
  }
  else
  {
    errs() << "Unable to open file!" << "\n";
  }
}

bool pdg::pdgutils::containsAnySubstring(const std::string &s, const std::vector<std::string> &S)
{
  for (const std::string &substring : S)
  {
    if (s.find(substring) != std::string::npos)
    {
    return true;
    }
  }
  return false;
}

void pdg::pdgutils::printSourceLocation(Instruction &I, llvm::raw_ostream &OutputStream)
{
  if (const llvm::DebugLoc &debugLoc = I.getDebugLoc())
  {
    unsigned line = debugLoc.getLine();
    unsigned col = debugLoc.getCol();
    llvm::MDNode *scopeNode = debugLoc.getScope();
    std::string filePrefix = "https://gitlab.flux.utah.edu/xcap/xcap-capability-linux/-/blob/llvm_v4.8/";

    if (auto *scope = llvm::dyn_cast<llvm::DIScope>(scopeNode))
    {
      std::string file = scope->getFilename().str();
      OutputStream << filePrefix << file << "#L" << line << "\n";
    }
    else
    {
      OutputStream << "\n";
    }
  }
}

std::string pdg::pdgutils::getSourceLocationStr(Instruction &I)
{
  std::string outStr = "";
  std::string filePrefix = "https://gitlab.flux.utah.edu/xcap/xcap-capability-linux/-/blob/llvm_v4.8/";

  if (const llvm::DebugLoc &debugLoc = I.getDebugLoc())
  {
    unsigned line = debugLoc.getLine();
    // unsigned col = debugLoc.getCol();
    llvm::MDNode *scopeNode = debugLoc.getScope();

    if (auto *scope = llvm::dyn_cast<llvm::DIScope>(scopeNode))
    {
      std::string file = scope->getFilename().str();
      outStr = outStr + filePrefix + file + "#L" + std::to_string(line);
    }
  }

  if (outStr.empty())
  {
    std::string s;
    raw_string_ostream ss(s);
    I.print(ss);
    // obtain function debugging loc
    auto func = I.getFunction();
    auto DISubprog = func->getSubprogram();
    unsigned line = DISubprog->getLine();
    std::string file = DISubprog->getFilename().str();
    outStr = filePrefix + file + "#L" + std::to_string(line) + " | "  + ss.str();
  }

  return outStr;
}

bool pdg::pdgutils::isUpdatedInHeader(Instruction &I)
{
  if (const llvm::DebugLoc &debugLoc = I.getDebugLoc())
  {
    llvm::MDNode *scopeNode = debugLoc.getScope();
    if (auto *scope = llvm::dyn_cast<llvm::DIScope>(scopeNode))
    {
      std::string pathStr = scope->getFilename().str();
      // Find the last occurrence of ".h"
      size_t pos = pathStr.rfind(".h");
      // Check if the last occurrence is at the end of the string
      return pos != std::string::npos && pos == pathStr.length() - 2;
    }
  }
  return false;
}

bool pdg::pdgutils::isFuncDefinedInHeaderFile(Function &F)
{ 
  auto DISubprog = F.getSubprogram();
  auto fileName = DISubprog->getFilename().str();
  if (fileName.empty())
    return false;
  size_t pos = fileName.rfind(".h");
  // Check if the last occurrence is at the end of the string
  return pos != std::string::npos && pos == fileName.length() - 2;
}

unsigned pdg::pdgutils::getFuncUniqueId(const Function &F)
{
  std::string FunctionUniqueId = "";

  // Return type
  FunctionUniqueId += F.getReturnType()->getTypeID();

  // Function name
  FunctionUniqueId += F.getName().str();

  // Parameters
  for (llvm::Function::const_arg_iterator I = F.arg_begin(), E = F.arg_end(); I != E; ++I)
  {
    FunctionUniqueId += I->getType()->getTypeID();
  }

  // Hash the string to get a unique unsigned integer
  std::hash<std::string> hash_fn;
  unsigned hash = hash_fn(FunctionUniqueId);

  return hash;
}

unsigned pdg::pdgutils::computeFieldUniqueId(unsigned funcId, unsigned argIdx, unsigned fieldOffset)
{
  return ((funcId ^ argIdx) << 5) ^ fieldOffset;
}

std::string pdg::pdgutils::edgeTypeToString(EdgeType edgeType)
{
  switch (edgeType) {
    case EdgeType::CALL:
      return "CALL";
    case EdgeType::IND_CALL:
      return "IND_CALL";
    case EdgeType::CONTROL:
      return "CONTROL";
    case EdgeType::CONTROL_FLOW:
      return "CONTROL_FLOW";
    case EdgeType::DATA_DEF_USE:
      return "DATA_DEF_USE";
    case EdgeType::DATA_RAW:
      return "DATA_RAW";
    case EdgeType::DATA_RAW_REV:
      return "DATA_RAW_REV";
    case EdgeType::DATA_READ:
      return "DATA_READ";
    case EdgeType::DATA_MAY_ALIAS:
      return "DATA_MAY_ALIAS";
    case EdgeType::DATA_MUST_ALIAS:
      return "DATA_MUST_ALIAS";
    case EdgeType::DATA_ALIAS:
      return "DATA_ALIAS";
    case EdgeType::DATA_RET:
      return "DATA_RET";
    case EdgeType::DATA_STORE_TO:
      return "DATA_ST";
    case EdgeType::PARAMETER_IN:
      return "PARAMETER_IN";
    case EdgeType::PARAMETER_IN_REV:
      return "PARAMETER_IN_REV";
    case EdgeType::PARAMETER_OUT:
      return "PARAMETER_OUT";
    case EdgeType::PARAMETER_FIELD:
      return "PARAMETER_FIELD";
    case EdgeType::GLOBAL_DEP:
      return "GLOBAL_DEP";
    case EdgeType::VAL_DEP:
      return "VAL_DEP";
    default:
      return "UNKNOWN Edge Type";
  }
}

std::string pdg::pdgutils::nodeTypeToString(GraphNodeType type)
{
  switch (type)
  {
  case GraphNodeType::INST:
      return "INST";
  case GraphNodeType::FORMAL_IN:
      return "FORMAL_IN";
  case GraphNodeType::FORMAL_OUT:
      return "FORMAL_OUT";
  case GraphNodeType::ACTUAL_IN:
      return "ACTUAL_IN";
  case GraphNodeType::ACTUAL_OUT:
      return "ACTUAL_OUT";
  case GraphNodeType::RETURN:
      return "RETURN";
  case GraphNodeType::FUNC_ENTRY:
      return "FUNC_ENTRY";
  case GraphNodeType::GLOBAL_VAR:
      return "GLOBAL_VAR";
  case GraphNodeType::CALL:
      return "CALL";
  case GraphNodeType::GLOBAL_TYPE:
      return "GLOBAL_TYPE";
  case GraphNodeType::FUNC:
      return "FUNC";
  default:
      return "Unknown GraphNodeType";
  }
}
