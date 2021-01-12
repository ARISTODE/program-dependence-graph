#include "LLVMEssentials.hh"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

namespace pdg
{
  namespace pdgutils
  {
    llvm::StructType *getStructTypeFromGEP(llvm::GetElementPtrInst &gep);
    int getGEPAccessFieldOffset(llvm::GetElementPtrInst &gep);
    uint64_t getGEPOffsetInBits(llvm::Module &M, llvm::StructType &struct_type, llvm::GetElementPtrInst &gep);
  } // namespace utils
}