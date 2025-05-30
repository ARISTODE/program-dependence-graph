#include "PTAWrapper.hh"

using namespace llvm;

void pdg::PTAWrapper::setupPTA(Module &M)
{
  // SVF functionality disabled - requires SVF installation
  _ander_pta = reinterpret_cast<void*>(0x1); // Mark as "setup" with dummy pointer
  errs() << "PTAWrapper::setupPTA - SVF functionality disabled (stub)\n";
}

AliasResult pdg::PTAWrapper::queryAlias(Value &v1, Value &v2)
{
  // Return no alias as fallback
  errs() << "PTAWrapper::queryAlias - SVF functionality disabled, returning NoAlias\n";
  return AliasResult::NoAlias;
}