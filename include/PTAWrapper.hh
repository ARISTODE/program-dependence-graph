#ifndef _PTAWRAPPER_H_
#define _PTAWRAPPER_H_
#include "LLVMEssentials.hh"
// #include "SVF-FE/PAGBuilder.h"
// #include "WPA/Andersen.h"
// #include "SVF-FE/LLVMUtil.h"


// namespace pdg
// {
//   class PTAWrapper final
//   {
//   public:
//     PTAWrapper() = default;
//     PTAWrapper(const PTAWrapper &) = delete;
//     PTAWrapper(PTAWrapper &&) = delete;
//     PTAWrapper &operator=(const PTAWrapper &) = delete;
//     PTAWrapper &operator=(PTAWrapper &&) = delete;
//     static PTAWrapper &getInstance()
//     {
//       static PTAWrapper ptaw{};
//       return ptaw;
//     }
//     void setupPTA(llvm::Module &M);
//     bool hasPTASetup() { return (_ander_pta != nullptr); }
//     llvm::AliasResult queryAlias(llvm::Value &v1, llvm::Value &v2);

//   private:
//     SVF::AndersenWaveDiff *_ander_pta;
//   };
// } // namespace pdg

#endif