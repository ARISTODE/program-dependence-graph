#include "DebugInfoUtils.hh"

using namespace llvm;

static std::map<std::string, std::string> typeSwitchMap = {
    {"_Bool", "bool"},
    {"char", "s8"},
    {"signed char", "s8"},
    {"unsigned char", "u8"},
    {"short", "u16"},
    {"short int", "s16"},
    {"signed short", "s16"},
    {"unsigned short", "u16"},
    {"signed short int", "s16"},
    {"unsigned short int", "u16"},
    {"int", "s32"},
    {"signed", "s32"},
    {"unsigned int", "u32"},
    {"long", "s32"},
    {"long int", "s32"},
    {"signed long", "s32"},
    {"signed long int", "s32"},
    {"unsigned long", "u32"},
    {"unsigned long int", "u32"},
    {"long long unsigned int", "u64"},
    {"long long", "s64"},
    {"long long int", "s64"},
    {"signed long long", "s64"},
    {"signed long long int", "s64"},
    {"unsigned long long", "u64"},
    {"unsigned long long int", "u64"},
    {"long unsigned int", "u64"},
};

// ===== check types =====
bool pdg::dbgutils::isPointerType(DIType &dt)
{
  auto d = stripMemberTag(dt);
  d = stripAttributes(*d);
  if (d == nullptr)
    return false;
  return (d->getTag() == dwarf::DW_TAG_pointer_type);
}

bool pdg::dbgutils::isStructType(DIType &dt)
{
  return (dt.getTag() == dwarf::DW_TAG_structure_type);
}

bool pdg::dbgutils::isUnionPointerType(DIType& dt)
{
  auto d = stripMemberTag(dt);
  d = stripAttributes(*d);
  if (isPointerType(*d))
  {
    DIType *lowest_di_type = getLowestDIType(*d);
    if (lowest_di_type == nullptr)
      return false;
    if (isUnionType(*lowest_di_type))
      return true;
  }
  return false;
}

bool pdg::dbgutils::isUnionType(DIType& dt)
{
  auto d = stripMemberTag(dt);
  d = stripAttributes(*d);
  return (d->getTag() == dwarf::DW_TAG_union_type);
}

bool pdg::dbgutils::isStructPointerType(DIType &dt)
{
  if (isPointerType(dt))
  {
    DIType *lowest_di_type = getLowestDIType(dt);
    if (lowest_di_type == nullptr)
      return false;
    if (isStructType(*lowest_di_type))
      return true;
  }
  return false;
}

bool pdg::dbgutils::isFuncPointerType(DIType &dt)
{
  DIType* di = stripMemberTag(*stripAttributes(dt));
  if (!isPointerType(*di))
    return false;
  // if (di->getTag() == dwarf::DW_TAG_subroutine_type || isa<DISubroutineType>(di) || isa<DISubprogram>(di))
  //   return true;
  auto lowest_di_type = getLowestDIType(*di);
  if (lowest_di_type != nullptr)
    return (lowest_di_type->getTag() == dwarf::DW_TAG_subroutine_type) || isa<DISubroutineType>(lowest_di_type) || isa<DISubprogram>(lowest_di_type);
  return false;
}

bool pdg::dbgutils::isProjectableType(DIType &dt)
{
  return (isStructType(dt) || isUnionType(dt));
}

bool pdg::dbgutils::isVoidPointerType(DIType &dt)
{
  DIType *d1 = stripMemberTag(dt);
  if (d1->getTag() == dwarf::DW_TAG_pointer_type)
  {
    auto baseTy = getBaseDIType(*d1);
    if (baseTy == nullptr)
      return true;
  }
  return false;
}

bool pdg::dbgutils::isArrayType(DIType &dt)
{
  DIType* d = stripMemberTag(dt);
  d = stripAttributes(*d);
  if (d != nullptr)
    return (d->getTag() == dwarf::DW_TAG_array_type);
  return false;
}

bool pdg::dbgutils::hasSameDIName(DIType &d1, DIType &d2)
{
  std::string d1_name = dbgutils::getSourceLevelTypeName(d1);
  std::string d2_name = dbgutils::getSourceLevelTypeName(d2);
  return (d1_name == d2_name);
}

// ===== derived types related operations =====
DIType *pdg::dbgutils::getBaseDIType(DIType &dt)
{
  if (DIDerivedType *derived_ty = dyn_cast<DIDerivedType>(&dt))
    return derived_ty->getBaseType();
  if (DICompositeType *dct = dyn_cast<DICompositeType>(&dt))
    return dct->getBaseType();
  return nullptr;
}

DIType *pdg::dbgutils::getLowestDIType(DIType &dt)
{
  DIType *current_dt = &dt;
  if (!current_dt)
    return nullptr;
  while (isa<DIDerivedType>(current_dt) || isa<DICompositeType>(current_dt))
  {
    if (auto derived_dt = dyn_cast<DIDerivedType>(current_dt))
      current_dt = derived_dt->getBaseType();
    else if (auto composite_dt = dyn_cast<DICompositeType>(current_dt))
    {
      if (composite_dt->getBaseType() == nullptr)
        break;
      current_dt = composite_dt->getBaseType();
    }
    if (!current_dt) // could happen for a pointer to void pointer etc
      break;
  }
  return current_dt;
}

DIType *pdg::dbgutils::stripAttributes(DIType &dt)
{
  DIType *current_dt = &dt;
  assert(current_dt != nullptr && "cannot strip attr on null di type!");
  auto type_tag = dt.getTag();
  while (type_tag == dwarf::DW_TAG_typedef ||
         type_tag == dwarf::DW_TAG_const_type ||
         type_tag == dwarf::DW_TAG_volatile_type)
  {
    if (DIDerivedType *didt = dyn_cast<DIDerivedType>(current_dt))
    {
      DIType *baseTy = didt->getBaseType();
      if (baseTy == nullptr)
        return current_dt;
      current_dt = baseTy;
      type_tag = current_dt->getTag();
    }
  }
  return current_dt;
}

DIType *pdg::dbgutils::stripMemberTag(DIType &dt)
{
  auto type_tag = dt.getTag();
  if (type_tag == dwarf::DW_TAG_member)
    return getBaseDIType(dt);
  return &dt;
}

// ===== get the source level naming information for variable or types ===== 
std::string pdg::dbgutils::getSourceLevelVariableName(DINode &di_node)
{
  DINode* node_ptr = &di_node;
  if (!node_ptr)
    return "";

  if (DILocalVariable *di_var = dyn_cast<DILocalVariable>(&di_node))
    return di_var->getName().str();

  // get field name
  if (DIType *dt = dyn_cast<DIType>(&di_node))
  {
    auto type_tag = dt->getTag();
    switch (type_tag)
    {
      case dwarf::DW_TAG_member:
      {
        return dt->getName().str();
      }
      case dwarf::DW_TAG_structure_type:
        return dt->getName().str();
      case dwarf::DW_TAG_typedef:
        return dt->getName().str();
      default:
        return dt->getName().str();
    }
  }
  return "";
}

std::string pdg::dbgutils::getSourceLevelTypeName(DIType &dt, bool is_raw)
{
  auto type_tag = dt.getTag();
  if (!type_tag)
    return "";
  switch (type_tag)
  {
  case dwarf::DW_TAG_pointer_type:
  {
    auto base_type = getBaseDIType(dt);
    if (!base_type)
      return "void*";
    return getSourceLevelTypeName(*base_type, is_raw) + "*";
  }
  case dwarf::DW_TAG_member:
  {
    auto base_type = getBaseDIType(dt);
    if (!base_type)
      return "void";
    std::string base_type_name = getSourceLevelTypeName(*base_type, is_raw);
    if (base_type_name == "struct" || base_type_name == "union" && !is_raw)
      base_type_name = base_type_name + dt.getName().str();
    return base_type_name;
  }
  // assert(!type_name.empty() && !var_name.empty() && "cannot generation idl from empty var/type name!");
  case dwarf::DW_TAG_structure_type:
  {
    if (dt.getName().empty())
      return is_raw ? "" : "struct";
    return is_raw ? dt.getName().str() : "struct " + dt.getName().str();
  }
  case dwarf::DW_TAG_array_type:
  {
    DICompositeType *dct = cast<DICompositeType>(&dt);
    auto elements = dct->getElements();
    if (elements.size() == 1)
    {
      auto element_dt = getLowestDIType(*dct);
      if (element_dt != nullptr)
      {
        auto total_size = dct->getSizeInBits();
        auto element_size = element_dt->getSizeInBits();
        auto element_type_name = getSourceLevelTypeName(*element_dt, is_raw);
        if (total_size != 0 && element_size != 0)
        {
          auto element_count = total_size / element_size;
          std::string arr_field_str = "array< " + element_type_name + ", " + std::to_string(element_count) + ">";
          return arr_field_str;
        }
        else if (total_size == 0)
        {
          std::string arr_field_str = "array<" + element_type_name + ", 0>";
          return arr_field_str;
        }
      }
    }
    return "array";
  }
  case dwarf::DW_TAG_const_type:
  {
    auto base_type = getBaseDIType(dt);
    if (!base_type)
      return "const nullptr";
    if (is_raw)
      return getSourceLevelTypeName(*base_type, is_raw);
    else
      return "const " + getSourceLevelTypeName(*base_type, is_raw);
  }
  case dwarf::DW_TAG_typedef:
  {
    auto base_type = getBaseDIType(dt);
    if (!base_type)
      return "";
    if (base_type->getName().str().empty())
      return dt.getName().str();
    return getSourceLevelTypeName(*getBaseDIType(dt), is_raw);
  }
  case dwarf::DW_TAG_enumeration_type:
  {
    auto base_type = getBaseDIType(dt);
    if (!base_type)
      return "s32";
    return getSourceLevelTypeName(*getBaseDIType(dt), is_raw);
  }
  case dwarf::DW_TAG_union_type:
  {
    if (dt.getName().empty())
      return is_raw ? "" : "union";
    return is_raw ? dt.getName().str() : "union " + dt.getName().str();
  }
  default:
  {
    // if (typeSwitchMap.find(dt.getName().str()) != typeSwitchMap.end())
    //   return typeSwitchMap[dt.getName().str()];
    if (dt.getName().str() == "_Bool") {
	return "bool";
    }
    return dt.getName().str();
  }
  }
  return "";
}

// compute di type for value
DIType *pdg::dbgutils::getGlobalVarDIType(GlobalVariable &gv)
{
  SmallVector<DIGlobalVariableExpression *, 5> GVs;
  gv.getDebugInfo(GVs);
  if (GVs.size() == 0)
    return nullptr;
  for (auto GV : GVs)
  {
    DIGlobalVariable *digv = GV->getVariable();
    return digv->getType();
  }
  return nullptr;
}

DIType *pdg::dbgutils::getFuncRetDIType(Function &F)
{
  SmallVector<std::pair<unsigned, MDNode *>, 4> MDs;
  F.getAllMetadata(MDs);
  for (auto &MD : MDs)
  {
    MDNode *N = MD.second;
    if (DISubprogram *subprogram = dyn_cast<DISubprogram>(N))
    {
      auto *sub_routine = subprogram->getType();
      const auto &type_ref = sub_routine->getTypeArray();
      if (F.arg_size() >= type_ref.size())
        break;
      // const auto &ArgTypeRef = TypeRef[0];
      // DIType *Ty = ArgTypeRef->resolve();
      // return Ty;
      return type_ref[0];
    }
  }
  return nullptr;
}

std::set<DIType *> pdg::dbgutils::computeContainedStructTypes(DIType &dt)
{
  std::set<DIType* > contained_struct_di_types;
  if (!isStructType(dt))
    return contained_struct_di_types;
  std::queue<DIType*> type_queue;
  type_queue.push(&dt);
  int current_tree_height = 0;
  int max_tree_height = 5;
  while (current_tree_height < max_tree_height)
  {
    current_tree_height++;
    int queue_size = type_queue.size();
    while (queue_size > 0)
    {
      queue_size--;
      DIType *current_di_type = type_queue.front();
      type_queue.pop();
      if (!isStructType(*current_di_type))
        continue;
      if (contained_struct_di_types.find(current_di_type) != contained_struct_di_types.end())
        continue;
      if (getSourceLevelTypeName(*current_di_type).compare("struct") == 0) // ignore anonymous struct
        continue;
      contained_struct_di_types.insert(current_di_type);
      auto di_node_arr = dyn_cast<DICompositeType>(current_di_type)->getElements();
      for (unsigned i = 0; i < di_node_arr.size(); i++)
      {
        DIType *field_di_type = dyn_cast<DIType>(di_node_arr[i]);
        DIType* field_lowest_di_type = getLowestDIType(*field_di_type);
        if (!field_lowest_di_type)
          continue;
        if (isStructType(*field_lowest_di_type))
          type_queue.push(field_lowest_di_type);
      }
    }
  }
  return contained_struct_di_types;
}

std::string pdg::dbgutils::getFuncSigName(DIType &dt, Function &F, std::string func_ptr_name)
{
  std::string func_type_str = "";
  auto lowest_di_type = getLowestDIType(dt);
  if (lowest_di_type == nullptr)
    return "void";
  if (DISubroutineType *subRoutine = dyn_cast<DISubroutineType>(lowest_di_type))
  {
    const auto &type_ref_arr = subRoutine->getTypeArray();
    // generate name string for return value
    DIType *ret_di_ty = type_ref_arr[0];
    if (ret_di_ty == nullptr)
      func_type_str += "void ";
    else
      func_type_str += getSourceLevelTypeName(*ret_di_ty);

    // generate name string for function pointer 
    func_type_str += " (";
    if (!func_ptr_name.empty())
      func_type_str += "*";
    func_type_str += func_ptr_name;
    // if (!funcName.empty())
    //   func_type_str = func_type_str + "_" + funcName;
    func_type_str += ")";
    // generate name string for arguments in fucntion pointer signature
    func_type_str += "(";
    for (int i = 1; i < type_ref_arr.size(); ++i)
    {
      DIType *d = type_ref_arr[i];
      // retrieve naming info from debugging information for each argument
      std::string arg_name = getSourceLevelVariableName(*d);

      unsigned argNum = i - 1;
      unsigned count = 0;
      for (auto argI = F.arg_begin(); argI != F.arg_end(); ++argI)
      {
        if (count == argNum)
        {
          arg_name = getArgumentName(*argI);
          break;
        }
        count++;
      }

      if (d == nullptr) // void type
        func_type_str += "void ";
      else // normal types
      {
        if (DIDerivedType *dit = dyn_cast<DIDerivedType>(d))
        {
          auto baseType = dit->getBaseType();
          if (!baseType)
          {
            // if a DIderived type has a null base type, this normally 
            // represent a void pointer
            func_type_str += "void* ";
          }
          else if (baseType->getTag() == dwarf::DW_TAG_structure_type)
          {
            std::string arg_type_name = getSourceLevelTypeName(*d);
            // if (F != nullptr && actualArgHasAllocator(*F, i - 1))
            //   arg_type_name = "alloc[callee] " + arg_type_name;
            if (arg_type_name.back() == '*')
            {
              arg_type_name.pop_back();
              arg_type_name = arg_type_name + "_" + func_ptr_name + "*";
            }
            else
            {
              arg_type_name = arg_type_name + "_" + func_ptr_name;
            }

            std::string struct_name = arg_type_name + " " + arg_name;
            if (struct_name != " ")
              func_type_str = func_type_str + "projection " + struct_name;
          }
          else
            func_type_str = func_type_str + getSourceLevelTypeName(*d) + " " + arg_name;
        }
        else
          func_type_str = func_type_str + getSourceLevelTypeName(*d);
      }

      if (i < type_ref_arr.size() - 1 && !getSourceLevelTypeName(*d).empty())
        func_type_str += ", ";
    }
    func_type_str += ")";
    return func_type_str;
  }
  return "void";
}

std::string pdg::dbgutils::getArgumentName(llvm::Argument &arg)
{
  Function *F = arg.getParent();
  auto dbg_insts = collectDbgInstInFunc(*F);
  std::vector<DbgInfoIntrinsic *> dbgInstList(dbg_insts.begin(), dbg_insts.end());
  SmallVector<std::pair<unsigned, MDNode *>, 20> func_MDs;
  for (auto dbgInst : dbgInstList)
  {
    DILocalVariable *DLV = nullptr;
    if (auto declareInst = dyn_cast<DbgDeclareInst>(dbgInst))
      DLV = declareInst->getVariable();
    if (auto valueInst = dyn_cast<DbgValueInst>(dbgInst))
      DLV = valueInst->getVariable();
    if (!DLV)
      continue;
    if (DLV->getArg() == arg.getArgNo() + 1 && !DLV->getName().empty() && DLV->getScope()->getSubprogram() == F->getSubprogram())
      return DLV->getName().str();
  }

  return "";
}

std::set<DbgInfoIntrinsic *> pdg::dbgutils::collectDbgInstInFunc(Function &F)
{
  std::set<DbgInfoIntrinsic *> ret;
  for (auto instI = inst_begin(&F); instI != inst_end(&F); ++instI)
  {
    if (DbgInfoIntrinsic *dbi = dyn_cast<DbgInfoIntrinsic>(&*instI))
      ret.insert(dbi);
  }
  return ret;
}

unsigned pdg::dbgutils::computeDeepCopyFields(DIType &dt, bool only_count_pointer)
{
  std::queue<DIType*> type_queue;
  std::set<DIType*> seen_types;
  type_queue.push(&dt);
  unsigned field_num = 0;
  while (!type_queue.empty())
  {
    DIType* cur_dt = type_queue.front();
    type_queue.pop();
    DIType* lowest_dt = getLowestDIType(*cur_dt);
    if (lowest_dt == nullptr || !isStructType(*lowest_dt))
      continue;
    if (seen_types.find(lowest_dt) != seen_types.end())
      continue;
    seen_types.insert(lowest_dt);
    auto di_node_arr = dyn_cast<DICompositeType>(lowest_dt)->getElements();
    for (unsigned i = 0; i < di_node_arr.size(); ++i)
    {
      DIType *field_di_type = dyn_cast<DIType>(di_node_arr[i]);
      DIType *field_lowest_di_type = getLowestDIType(*field_di_type);

      if (only_count_pointer)
      {
        if (isPointerType(*field_di_type))
          field_num++;
      }
      else
        field_num++;

      if (field_lowest_di_type == nullptr)
        continue;
      if (isStructType(*field_lowest_di_type))
        type_queue.push(field_lowest_di_type);
    }
  }
  return field_num;
}