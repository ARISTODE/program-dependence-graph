#include "LLVMEssentials.hh"
#include "PDGNode.hh"
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
    bool isNodeBitOffsetMatchGEPBitOffset(Node &n, llvm::GetElementPtrInst &gep);
    bool isGEPOffsetMatchDIOffset(llvm::DIType &dt, llvm::GetElementPtrInst &gep);
    llvm::Function* getCalledFunc(llvm::CallInst &call_inst);
    bool hasReadAccess(llvm::Value &v);
    bool hasWriteAccess(llvm::Value &v);
  } // namespace utils
}