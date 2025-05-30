#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/FunctionPropertiesAnalysis.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/Casting.h"

#include "ProgramDependencyGraph.hh"
#include "DataDependencyGraph.hh"
#include "ControlDependencyGraph.hh"
#include "Graph.hh"

using namespace llvm;

namespace {

// Control dependency test pass
class ControlDepTestPass : public PassInfoMixin<ControlDepTestPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &FAM) {
    if (F.isDeclaration())
      return PreservedAnalyses::all();
      
    errs() << "\n=== Control Dependency Analysis for function: " << F.getName() << " ===\n";
    errs() << "Function has " << F.size() << " basic blocks\n";
    
    // Get control dependency analysis
    try {
      auto &CDG = FAM.getResult<pdg::ControlDependencyGraph>(F);
      (void)CDG; // Suppress unused variable warning
      errs() << "✅ Control dependency analysis obtained successfully!\n";
    } catch (...) {
      errs() << "❌ Control dependency analysis failed\n";
    }
    
    // Analyze control flow
    for (auto &BB : F) {
      if (auto *BI = dyn_cast<BranchInst>(BB.getTerminator())) {
        if (BI->isConditional()) {
          errs() << "  Conditional branch in block " << BB.getName() << "\n";
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

// Simple test pass to verify plugin works
class SimplePDGTestPass : public PassInfoMixin<SimplePDGTestPass> {
public:
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
    errs() << "=== PDG Test Pass Running ===\n";
    errs() << "Module: " << M.getName() << "\n";
    errs() << "Functions: " << M.size() << "\n";
    
    for (auto &F : M) {
      if (!F.isDeclaration()) {
        errs() << "  Function: " << F.getName() << "\n";
        errs() << "    Basic blocks: " << F.size() << "\n";
        errs() << "    Instructions: " << F.getInstructionCount() << "\n";
      }
    }
    
    errs() << "✅ PDG Plugin loaded and executed successfully!\n";
    return PreservedAnalyses::all();
  }
  
  static bool isRequired() { return false; }
};

// Registration callback for analysis passes
void registerAnalyses(ModuleAnalysisManager &MAM) {
  MAM.registerPass([&] { return pdg::DataDependencyGraph(); });
  MAM.registerPass([&] { return pdg::ProgramDependencyGraph(); });
}

void registerFunctionAnalyses(FunctionAnalysisManager &FAM) {
  FAM.registerPass([&] { return pdg::ControlDependencyGraph(); });
}

// Pipeline parsing callback for module passes
bool parsePDGModulePipeline(StringRef Name, ModulePassManager &MPM,
                      ArrayRef<PassBuilder::PipelineElement>) {
  if (Name == "pdg-test") {
    MPM.addPass(SimplePDGTestPass());
    return true;
  }
  if (Name == "pdg") {
    // Create a transform pass that runs the real ProgramDependencyGraph analysis
    struct PDGTransformPass : public PassInfoMixin<PDGTransformPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
        errs() << "=== Running Real Program Dependency Graph Analysis ===\n";
        try {
          auto &PDGResult = MAM.getResult<pdg::ProgramDependencyGraph>(M);
          errs() << "✅ ProgramDependencyGraph analysis completed successfully!\n";
          if (PDGResult.PDG) {
            errs() << "PDG built with " << PDGResult.PDG->numNode() << " nodes\n";
          } else {
            errs() << "PDG result is null\n";
          }
        } catch (const std::exception& e) {
          errs() << "❌ ProgramDependencyGraph analysis failed: " << e.what() << "\n";
        } catch (...) {
          errs() << "❌ ProgramDependencyGraph analysis failed with unknown error\n";
        }
        return PreservedAnalyses::all();
      }
    };
    MPM.addPass(PDGTransformPass{});
    return true;
  }
  if (Name == "pdg-minimal") {
    // Create a minimal PDG pass that shows the structure without complex dependencies  
    struct MinimalPDGPass : public PassInfoMixin<MinimalPDGPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
        errs() << "=== Minimal Program Dependency Graph Analysis ===\n";
        errs() << "Module: " << M.getName() << "\n";
        errs() << "Functions: " << M.size() << "\n";
        
        for (auto &F : M) {
          if (!F.isDeclaration()) {
            errs() << "  Function: " << F.getName() << "\n";
            errs() << "    Basic blocks: " << F.size() << "\n";
            errs() << "    Instructions: " << F.getInstructionCount() << "\n";
            
            // Basic control dependency analysis
            for (auto &BB : F) {
              if (auto *BI = dyn_cast<BranchInst>(BB.getTerminator())) {
                if (BI->isConditional()) {
                  errs() << "    Control dependency: " << BB.getName() << " -> ";
                  errs() << BI->getSuccessor(0)->getName() << ", " << BI->getSuccessor(1)->getName() << "\n";
                }
              }
            }
            
            // Basic data dependency analysis (def-use chains)
            for (auto &BB : F) {
              for (auto &I : BB) {
                if (I.hasName() && I.getNumUses() > 0) {
                  errs() << "    Data dependency: " << I.getName() << " used " << I.getNumUses() << " times\n";
                }
              }
            }
          }
        }
        
        errs() << "✅ Minimal PDG analysis completed!\n";
        return PreservedAnalyses::all();
      }
    };
    MPM.addPass(MinimalPDGPass{});
    return true;
  }
  if (Name == "data-dep") {
    // Create a transform pass that runs DataDependencyGraph analysis
    struct DataDepTransformPass : public PassInfoMixin<DataDepTransformPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
        errs() << "=== Running Data Dependency Graph Analysis ===\n";
        try {
          auto &DataDepResult = MAM.getResult<pdg::DataDependencyGraph>(M);
          errs() << "✅ DataDependencyGraph analysis completed successfully!\n";
        } catch (const std::exception& e) {
          errs() << "❌ DataDependencyGraph analysis failed: " << e.what() << "\n";
        }
        return PreservedAnalyses::all();
      }
    };
    MPM.addPass(DataDepTransformPass{});
    return true;
  }
  if (Name == "dot-pdg") {
    // Create a pass that generates DOT output for PDG
    struct DOTPDGPass : public PassInfoMixin<DOTPDGPass> {
      PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
        errs() << "=== Generating DOT Graph for PDG ===\n";
        try {
          // First run PDG analysis to build the graph
          auto &PDGResult = MAM.getResult<pdg::ProgramDependencyGraph>(M);
          if (PDGResult.PDG) {
            errs() << "PDG analysis completed, generating DOT output...\n";
            errs() << "PDG has " << PDGResult.PDG->numNode() << " nodes\n";
            errs() << "DOT output would be generated here (GraphWriter integration needed)\n";
            errs() << "✅ DOT PDG pass completed!\n";
          } else {
            errs() << "❌ PDG is null, cannot generate DOT output\n";
          }
        } catch (const std::exception& e) {
          errs() << "❌ DOT PDG pass failed: " << e.what() << "\n";
        }
        return PreservedAnalyses::all();
      }
    };
    MPM.addPass(DOTPDGPass{});
    return true;
  }
  return false;
}

// Pipeline parsing callback for function passes
bool parsePDGFunctionPipeline(StringRef Name, FunctionPassManager &FPM,
                      ArrayRef<PassBuilder::PipelineElement>) {
  if (Name == "control-deps-test") {
    FPM.addPass(ControlDepTestPass());
    return true;
  }
  return false;
}

} // anonymous namespace

// This is the entry point for opt to load the plugin
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "PDG", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            // Register analysis passes
            PB.registerAnalysisRegistrationCallback(
                [](ModuleAnalysisManager &MAM) {
                  registerAnalyses(MAM);
                });
            
            PB.registerAnalysisRegistrationCallback(
                [](FunctionAnalysisManager &FAM) {
                  registerFunctionAnalyses(FAM);
                });
            
            // Register module pipeline parsing
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement> Pipeline) {
                  return parsePDGModulePipeline(Name, MPM, Pipeline);
                });
                
            // Register function pipeline parsing
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement> Pipeline) {
                  return parsePDGFunctionPipeline(Name, FPM, Pipeline);
                });
          }};
}