#include "GraphWriter.hh"

char pdg::ProgramDependencyPrinter::ID = 0;
using namespace llvm;

bool pdg::DOTONLYDDG;
bool pdg::DOTONLYCDG;

cl::opt<bool, true> DOTDDG("dot-only-ddg", cl::desc("Only print ddg dependencies"), cl::value_desc("dot print ddg deps"), cl::location(pdg::DOTONLYDDG), cl::init(false));

cl::opt<bool, true> DOTCDG("dot-only-cdg", cl::desc("Only print cdg dependencies"), cl::value_desc("dot print cdg deps"), cl::location(pdg::DOTONLYCDG), cl::init(false));

// Legacy pass registration is removed in favor of new pass manager