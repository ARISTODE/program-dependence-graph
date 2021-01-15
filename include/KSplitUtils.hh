#ifndef KSPLITUTILS_H_
#define KSPLITUTILS_H_
#include "LLVMEssentials.hh"
#include <set>

namespace pdg
{
  namespace ksplitutils
  {
    std::set<llvm::Function*> computeImportedFunction(llvm::Module &M);
  }
}

#endif