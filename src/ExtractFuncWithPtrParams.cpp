#include "ExtractFuncWithPtrParams.hh"


using namespace llvm;

char pdg::ExtractFuncWithPtrParamsPass::ID = 0;

void pdg::ExtractFuncWithPtrParamsPass::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.setPreservesAll();
}

bool pdg::ExtractFuncWithPtrParamsPass::runOnModule(Module &M)
{
    std::ofstream outFile("ptrParamNames.txt");
    for (auto &F : M)
    {
        if (F.isDeclaration())
            continue;

        for (auto argIter = F.arg_begin(); argIter != F.arg_end(); argIter++)
        {
            auto arg = &*argIter;
            // should also check if it contain a pointer field. But coersion may avoid this problem
            if (arg->getType()->isPointerTy())
            {
                outFile << pdgutils::getDemangledName(F.getName().str().data()) << "\n";
                break;
            }
        }
    }
    outFile.close();
    return false;
}

static RegisterPass<pdg::ExtractFuncWithPtrParamsPass> X("extract-ptr-params-func", "extract functions names with ptr parmeters");