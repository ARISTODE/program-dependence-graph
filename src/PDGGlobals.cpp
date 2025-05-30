#include "llvm/Support/CommandLine.h"

namespace pdg {
  // Define the global variables that are declared as extern
  // Note: EnableAnalysisStats and DEBUG are defined in ProgramDependencyGraph.cpp
  bool OnlyControlledPath = false;
  bool SingleFuncAnalysis = false;
  std::string TargetFuncNameStr = "";
  
  llvm::cl::opt<std::string> TargetFuncName("target-func", 
    llvm::cl::desc("Target function name for analysis"),
    llvm::cl::init(""));
}