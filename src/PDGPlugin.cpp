#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/FunctionPropertiesAnalysis.h"

#include "ProgramDependencyGraph.hh"
#include "DataDependencyGraph.hh"
#include "ControlDependencyGraph.hh"

using namespace llvm;

namespace {

// Pass printer for PDG
class PDGPrinterPass : public PassInfoMixin<PDGPrinterPass> {
public:
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &MAM) {
    auto PDGResult = MAM.getResult<pdg::ProgramDependencyGraph>(M);
    // TODO: Add dot printing logic here
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

// Pipeline parsing callback
bool parsePDGPipeline(StringRef Name, ModulePassManager &MPM,
                      ArrayRef<PassBuilder::PipelineElement>) {
  if (Name == "pdg") {
    MPM.addPass(RequireAnalysisPass<pdg::ProgramDependencyGraph, Module>());
    return true;
  }
  if (Name == "dot-pdg") {
    MPM.addPass(PDGPrinterPass());
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
            
            // Register pipeline parsing
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement> Pipeline) {
                  return parsePDGPipeline(Name, MPM, Pipeline);
                });
          }};
}