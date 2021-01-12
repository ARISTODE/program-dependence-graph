#include "PDGUtils.hh"

using namespace llvm;

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

uint64_t pdg::pdgutils::getGEPOffsetInBits(Module& M, StructType &struct_type, GetElementPtrInst &gep)
{
  // get the accessed struct member offset from the gep instruction
  int gep_offset = getGEPAccessFieldOffset(gep);
  if (gep_offset == INT_MIN)
    return INT_MIN;
  // use the struct layout to figure out the offset in bits
  auto const &data_layout = M.getDataLayout();
  auto const struct_layout = data_layout.getStructLayout(&struct_type);
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
    return constInt->getSExtValue();
  return INT_MIN;
}