#include "GraphWriter.hh"

char pdg::ProgramDependencyPrinter::ID = 0;
static llvm::RegisterPass<pdg::ProgramDependencyPrinter>
    PDGPrinter("dot-pdg",
               "Print instruction-level program dependency graph of "
               "function to 'dot' file",
               false, false);