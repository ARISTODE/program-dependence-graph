#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "ControlDependencyGraph.hh"

using namespace llvm;

namespace pdg {

class ControlDepTestPass : public PassInfoMixin<ControlDepTestPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    if (F.isDeclaration())
      return PreservedAnalyses::all();
      
    errs() << "\n=== Control Dependency Analysis for function: " << F.getName() << " ===\n";
    
    // Get control dependency analysis
    auto &CDG = FAM.getResult<ControlDependencyGraph>(F);
    
    errs() << "Function has " << F.size() << " basic blocks\n";
    
    // Analyze control flow
    for (auto &BB : F) {
      if (auto *BI = dyn_cast<BranchInst>(BB.getTerminator())) {
        if (BI->isConditional()) {
          errs() << "  Conditional branch in block " << BB.getName() << "\n";
          errs() << "    Condition: ";
          BI->getCondition()->print(errs());
          errs() << "\n";
          errs() << "    True successor: " << BI->getSuccessor(0)->getName() << "\n";
          errs() << "    False successor: " << BI->getSuccessor(1)->getName() << "\n";
        }
      }
    }
    
    errs() << "✅ Control dependency analysis completed successfully!\n";
    
    return PreservedAnalyses::all();
  }
  
  static bool isRequired() { return false; }
};

} // namespace pdg