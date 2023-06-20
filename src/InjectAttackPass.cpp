#include "InjectAttackPass.hh"

using namespace llvm;

bool pdg::InjectAttackPass::runOnFunction(Function &F)
{
    // Check if the current function is one of the target functions
    if (std::find(targetFuncs.begin(), targetFuncs.end(), F.getName().str()) == targetFuncs.end())
        return false;
    // Instrument the function
    return instrumentFunction(F);
}

bool isDerivedFromArgument(Value *V, std::unordered_map<Value *, bool> &memo)
{
    // If the result is already in the memo, return it
    auto memoIt = memo.find(V);
    if (memoIt != memo.end())
    {
        return memoIt->second;
    }

    // If V is an Argument, return true
    if (isa<Argument>(V))
    {
        memo[V] = true;
        return true;
    }

    // If V is a derived value (e.g., from an instruction)
    if (auto *I = dyn_cast<Instruction>(V))
    {
        for (auto &operand : I->operands())
        {
            if (isDerivedFromArgument(operand, memo))
            {
                memo[V] = true;
                return true;
            }
        }
    }

    memo[V] = false;
    return false;
}

bool pdg::InjectAttackPass::instrumentFunction(Function &F)
{
    Module *M = F.getParent();
    LLVMContext &Ctx = M->getContext();

    // Get the attack injector functions
    FunctionCallee replacePointerInvalidValue = M->getOrInsertFunction("inject_DC1_replacePointerInvalidVal", Type::getVoidTy(Ctx), Type::getInt8PtrTy(Ctx));
    FunctionCallee replacePointerSameType = M->getOrInsertFunction("inject_DC3_replacePointerSameType", Type::getVoidTy(Ctx), Type::getInt8PtrTy(Ctx), Type::getInt32Ty(Ctx));
    FunctionCallee injectOutOfBoundsAccess = M->getOrInsertFunction("inject_DC3_replacePointerDifferntType", Type::getVoidTy(Ctx), Type::getInt8PtrTy(Ctx), Type::getInt32Ty(Ctx));

    bool modified = false;

    std::unordered_map<Value *, bool> memo;
    // Iterate through the basic blocks and instructions
    for (BasicBlock &BB : F)
    {
        for (Instruction &I : BB)
        {
            // Check if the instruction is a StoreInst or LoadInst
            if (isa<StoreInst>(&I) || isa<LoadInst>(&I))
            {
                // Check if the pointer operand is derived from the argument
                Value *pointer_value = I.getOperand(0);
                if (isDerivedFromArgument(pointer_value, memo))
                {
                    IRBuilder<> builder(&I);
                    // Insert the call to the attack injector functions

                    // Consider the attacks happens right after the function run, the check must be comprehensive such that the alternation would be captured. So we also need to instrument the instructions in the attack function, which is really wired.

                    modified = true;
                }
            }
        }
    }
    return modified;
}

char pdg::InjectAttackPass::ID = 0;
static RegisterPass<pdg::InjectAttackPass> X("inject-attacks", "Inject Attack Pass");