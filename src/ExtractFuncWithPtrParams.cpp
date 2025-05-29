#include "ExtractFuncWithPtrParams.hh"


using namespace llvm;

char pdg::ExtractFuncWithPtrParamsPass::ID = 0;

void pdg::ExtractFuncWithPtrParamsPass::getAnalysisUsage(AnalysisUsage &AU) const
{
    AU.setPreservesAll();
}

bool pdg::ExtractFuncWithPtrParamsPass::runOnModule(Module &M)
{
    // PDGCallGraph &call_g = PDGCallGraph::getInstance();
    // if (!call_g.isBuild())
    // {
    //     call_g.build(M);
    // }

    std::ofstream outFile("boundaryAPI");
    for (auto &F : M)
    {
        if (F.isDeclaration() || pdgutils::isMainFunc(F))
            continue;

        for (auto argIter = F.arg_begin(); argIter != F.arg_end(); argIter++)
        {
            auto arg = &*argIter;
            // should also check if it contain a pointer field. But coersion may avoid this problem
            if (pdgutils::isStructPointerType(*arg->getType()))
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