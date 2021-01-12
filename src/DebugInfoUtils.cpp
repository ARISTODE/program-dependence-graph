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
  switch (type_tag)
  {
  case dwarf::DW_TAG_structure_type:
    return "struct " + dt.getName().str();
  case dwarf::DW_TAG_array_type:
  {
    DICompositeType *dct = cast<DICompositeType>(&dt);
    auto elements = dct->getElements();
    if (elements.size() == 1)
    {
      // TODO: compute the array size based on new api
      // DISubrange *di_subr = cast<DISubrange>(elements[0]);
      // int count = di_subr->getCount().first->getSExtValue();
      std::string base_type_name = getSourceLevelTypeName(*getBaseDIType(dt));
      return "array<" + base_type_name + ", " + "0" + ">";
    }
    return "array";
  }
  default:
    return dt.getName().str();
    break;
  }
  return "";
}
