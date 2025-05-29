#ifndef LLVMESSENTIALS_H_
#define LLVMESSENTIALS_H_
// include the core functionalities needed by all passes
#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/DebugProgramInstruction.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/GraphWriter.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/ADT/GraphTraits.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/IR/Operator.h"

// opt option shared among passes
namespace pdg
{
  extern bool EnableAnalysisStats;
  extern bool OnlyControlledPath;
  extern bool DEBUG;
  extern bool SingleFuncAnalysis;
  extern std::string TargetFuncNameStr;
  extern llvm::cl::opt<std::string> TargetFuncName;
}
#endif