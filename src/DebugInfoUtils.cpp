#include "DebugInfoUtils.hh"

using namespace llvm;

// ===== check types =====
bool pdg::dbgutils::isPointerType(DIType &dt)
{
  return (dt.getTag() == dwarf::DW_TAG_pointer_type);
}

bool pdg::dbgutils::isStructType(DIType &dt)
{
  return (dt.getTag() == dwarf::DW_TAG_structure_type);
}

bool pdg::dbgutils::isUnionType(DIType& dt)
{
  return (dt.getTag() == dwarf::DW_TAG_union_type);
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

bool pdg::dbgutils::isProjectableType(DIType &dt)
{
  return (isStructType(dt) || isUnionType(dt));
}

// ===== derived types related operations =====
DIType *pdg::dbgutils::getBaseDIType(DIType &dt)
{
  if (DIDerivedType *derived_ty = dyn_cast<DIDerivedType>(&dt))
    return derived_ty->getBaseType();
  return nullptr;
}

DIType *pdg::dbgutils::getLowestDIType(DIType &dt)
{
  DIType *current_dt = &dt;
  while (DIDerivedType *derived_dt = dyn_cast<DIDerivedType>(current_dt))
  {
    current_dt = derived_dt->getBaseType();
    if (current_dt == nullptr) // could happen for a pointer to void pointer etc
      return nullptr;
  }
  return current_dt;
}

DIType *pdg::dbgutils::stripAttributes(DIType &dt)
{
  DIType *current_dt = &dt;
  auto type_tag = dt.getTag();
  while (type_tag == dwarf::DW_TAG_typedef ||
         type_tag == dwarf::DW_TAG_const_type ||
         type_tag == dwarf::DW_TAG_volatile_type)
  {
    if (DIDerivedType *didt = dyn_cast<DIDerivedType>(current_dt))
    {
      DIType *baseTy = didt->getBaseType();
      if (baseTy == nullptr)
        return nullptr;
      current_dt = baseTy;
      type_tag = current_dt->getTag();
    }
  }
  return current_dt;
}

// ===== get the source level naming information for variable or types ===== 
std::string pdg::dbgutils::getSourceLevelVariableName(DINode &di_node)
{
  if (DILocalVariable *di_var = dyn_cast<DILocalVariable>(&di_node))
  {
    return di_var->getName().str();
  }

  // get field name
  if (DIType *dt = dyn_cast<DIType>(&di_node))
  {
    auto type_tag = dt->getTag();
    if (type_tag == dwarf::DW_TAG_member)
      return dt->getName().str();
  }

  return "";
}

std::string pdg::dbgutils::getSourceLevelTypeName(DIType &dt)
{
  auto type_tag = dt.getTag();
  if (!type_tag)
    return "";
  switch (type_tag)
  {
  case dwarf::DW_TAG_pointer_type:
  {
    // errs() << "1\n";
    auto base_type = getBaseDIType(dt);
    if (!base_type)
      return "nullptr";
    return getSourceLevelTypeName(*base_type) + "*";
  }
  case dwarf::DW_TAG_member:
  {
    // errs() << "2\n";
    auto base_type = getBaseDIType(dt);
    if (!base_type)
      return "null";
    std::string base_type_name = getSourceLevelTypeName(*base_type);
    if (base_type_name == "struct")
      base_type_name = "struct " + dt.getName().str();
    return base_type_name;
  }
  // assert(!type_name.empty() && !var_name.empty() && "cannot generation idl from empty var/type name!");
  case dwarf::DW_TAG_structure_type:
  {
    // errs() << "3\n";
    return "struct " + dt.getName().str();
  }
  case dwarf::DW_TAG_array_type:
  {
    // DICompositeType *dct = cast<DICompositeType>(&dt);
    // auto elements = dct->getElements();
    // if (elements.size() == 1)
    // {
    //   // TODO: compute the array size based on new api
    //   DISubrange *di_subr = cast<DISubrange>(elements[0]);
    //   int count = di_subr->getCount().first->getSExtValue();
    //   auto lowest_di_type = getLowestDIType(dt);
    //   if (!lowest_di_type) 
    //     return "";
    //   std::string base_type_name = getSourceLevelTypeName(*lowest_di_type);
    //   return "array<" + base_type_name + ", " + "0" + ">";
    // }
    return "array";
  }
  case dwarf::DW_TAG_const_type:
  {
    auto base_type = getBaseDIType(dt);
    if (!base_type)
      return "const nullptr";
    return "const " + getSourceLevelTypeName(*base_type);
  }
  default:
    return dt.getName().str();
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