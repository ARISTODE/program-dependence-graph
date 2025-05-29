#include "ProgramDependencyGraph.hh"
#include <unordered_map>
#include <fstream>
#include <sstream>

namespace pdg
{
    struct InjectAttackPass : public llvm::FunctionPass
    {
        static char ID;
        std::vector<std::string> targetFuncs;
        InjectAttackPass() : llvm::FunctionPass(ID)
        {
            std::vector<std::string> targetFuncs;
            std::ifstream infile("target_functions.txt");
            std::string line;
            while (std::getline(infile, line))
            {
                targetFuncs.push_back(line);
            }
        }
        bool runOnFunction(llvm::Function &F) override;
        bool instrumentFunction(llvm::Function &F);
        bool isDerivedFromArgument(llvm::Value *v, std::unordered_map<llvm::Value *, bool> &memo);
    };
}