
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/ADT/StringMap.h"
#include "llvm/IR/LLVMContext.h"

#include "llvm/Transforms/Instrumentation.h"
#include "llvm/Analysis/MemoryBuiltins.h"
#include "llvm/Analysis/TargetFolder.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Intrinsics.h"

#include "llvm/IR/ValueSymbolTable.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/DebugInfo.h"

#include "llvm/IR/DerivedTypes.h"
#include "AnalysisState.hpp"
#include "AtomicRegionAnalysis.hh"

#include <list>
#include <time.h>

using namespace llvm;

#define IS_DEBUGGING 1
#define IS_NAIVE 0

#define DEBUG_TYPE "nescheck"

#define CONTAINS(v, e) (std::find(v.begin(), v.end(), e) != v.end())

unsigned int NesCheckFunctionCounter = 0;
unsigned int NesCheckCCuredSafePtrs = 0;
unsigned int NesCheckCCuredSeqPtrs = 0;
unsigned int NesCheckCCuredDynPtrs = 0;
unsigned int ChecksConsidered = 0;
unsigned int ChecksAdded = 0;
unsigned int ChecksAlwaysTrue = 0;
unsigned int ChecksAlwaysFalse = 0;
unsigned int ChecksSkippedForSafe = 0;
unsigned int ChecksUnable = 0;
unsigned int FunctionSignaturesRewritten = 0;
unsigned int FunctionCallSitesRewritten = 0;
unsigned int MetadataTableLookups = 0;
unsigned int MetadataTableUpdates = 0;
unsigned int NesCheckVariablesWithMetadataTableEntries = 0;

/*
STATISTIC(NesCheckFunctionCounter, "Number of functions found");
STATISTIC(NesCheckCCuredSafePtrs, "Number of SAFE pointers found");
STATISTIC(NesCheckCCuredSeqPtrs, "Number of SEQ pointers found");
STATISTIC(NesCheckCCuredDynPtrs, "Number of DYN pointers found");
STATISTIC(ChecksConsidered, "Checks considered");
STATISTIC(ChecksAdded, "Checks added");
STATISTIC(ChecksAlwaysTrue, "Checks always true (memory bugs)");
STATISTIC(ChecksAlwaysFalse, "Checks always false (unnecessary)");
STATISTIC(ChecksSkippedForSafe, "Checks skipped (SAFE pointer)");
STATISTIC(ChecksUnable, "Bounds checks unable to add");
STATISTIC(FunctionSignaturesRewritten, "Function signatures rewritten");
STATISTIC(FunctionCallSitesRewritten, "Function call sites rewritten");
STATISTIC(MetadataTableLookups, "Metadata table lookups");
STATISTIC(MetadataTableUpdates, "Metadata table updates");
STATISTIC(NesCheckVariablesWithMetadataTableEntries, "Variables with metadata table entries");
*/
typedef IRBuilder<> BuilderTy;
//typedef IRBuilder<true, TargetFolder> BuilderTy;

namespace NesCheck
{
  class NesCheckPass : public ModulePass
  {

  public:
    NesCheckPass() : ModulePass(ID) {}
    static char ID; // Pass identification, replacement for typeid
    StringRef getPassName() const override { return "NesCheckPass"; }
    std::set<Value *> getSafePtrs() { return SafePtrs; }
    std::set<Value *> getSeqPtrs() { return SeqPtrs; }
    std::set<Value *> getWildPtrs() { return WildPtrs; }

  private:
    Module *CurrentModule;
    const DataLayout *CurrentDL;
    ObjectSizeOffsetEvaluator *ObjSizeEval;
    BuilderTy *Builder;
    std::set<Value *> SafePtrs;
    std::set<Value *> SeqPtrs;
    std::set<Value *> WildPtrs;
    std::set<Value *> UnknownPtrs;
    std::set<pdg::Node *> ProcessedNodes;
    pdg::AtomicRegionAnalysis *_ARA;
    pdg::DataAccessAnalysis *_DDA;
    pdg::ProgramGraph* _PDG;
    std::set<std::string> BoundaryFuncNames;
    pdg::KSplitStats *_ksplit_stats;

    AnalysisState TheState;
    Type *MySizeType;
    ConstantInt *UnknownSizeConstInt;

    std::vector<std::string> WhitelistedFunctions;
    bool isCurrentFunctionWhitelisted = false;                   // function excluded from both analysis and instrumentation
    bool isCurrentFunctionWhitelistedForInstrumentation = false; // function excluded from instrumentation but included in analysis

    BasicBlock *TrapBB = nullptr;

    std::vector<Instruction *> InstrumentationWorkList;
    std::vector<Function *> FunctionsAddedWithNewReturnType;
    std::vector<Function *> FunctionsToRemove;

    Function *MyPrintErrorLineFn;
    Function *MyPrintCheckFn;
    Function *setMetadataFunction;
    Function *lookupMetadataFunction;

    // counts the number of pointer indirection for a type (e.g. for "int**" would be 2)
    int countIndirections(Type *T)
    {
      if (!(T->isPointerTy()))
        return 0;
      PointerType *innerT = dyn_cast_or_null<PointerType>(T);
      return countIndirections(innerT->getElementType()) + 1;
    }
    // unwraps a pointer until the innermost type
    Type *unwrapPointer(Type *T)
    {
      if (!(T->isPointerTy()))
        return T;
      PointerType *innerT = dyn_cast_or_null<PointerType>(T);
      return unwrapPointer(innerT->getElementType());
    }

    Value *lookupMetadataTableEntry(Value *Ptr, Instruction *CurrInst)
    {
      if (isCurrentFunctionWhitelistedForInstrumentation)
      {
        errs() << "\tSKIPPING Metadata Table lookup for " << *Ptr << " because of whitelisting\n";
        Value *lookedupsize = ConstantInt::get(MySizeType, 10000);
        TheState.SetSizeForPointerVariable(Ptr, lookedupsize);
        return lookedupsize;
      }

      errs() << "\tInjecting Metadata Table lookup for " << *Ptr << "\n";
      Instruction *ptrcast = (Instruction *)Builder->CreatePtrToInt(Ptr, CurrentDL->getIntPtrType(Ptr->getType()));

      ptrcast->removeFromParent();

      ptrcast->insertAfter(CurrInst);

      if (lookupMetadataFunction != NULL)
      {
        CallInst *call = Builder->CreateCall(lookupMetadataFunction, ptrcast);
        errs() << "\tPtrcast at " << ptrcast << "\n";
        call->removeFromParent();
        call->insertAfter(ptrcast);
        ++MetadataTableLookups;
        TheState.SetSizeForPointerVariable(Ptr, (Value *)call);
        TheState.SetHasMetadataTableEntry(Ptr);
        return (Value *)call;
      }

      return 0;
    }

    void setMetadataTableEntry(Value *Ptr, Value *Size, Instruction *CurrInst)
    {
      if (isCurrentFunctionWhitelistedForInstrumentation)
      {
        errs() << "\tSKIPPING Metadata Table update for " << *Ptr << " because of whitelisting\n";
        return;
      }
      errs() << "\tInjecting Metadata Table update for " << *Ptr << "\n";
      Value *P = Builder->CreatePtrToInt(Ptr, CurrentDL->getIntPtrType(Ptr->getType()));
      Value *addr = ConstantInt::get(MySizeType, (long)((const void *)CurrInst));
      if (setMetadataFunction != NULL)
      {
        Builder->CreateCall(setMetadataFunction, {P, Size, addr});
        ++MetadataTableUpdates;
        TheState.SetHasMetadataTableEntry(Ptr);
      }
    }

    Value *getSizeForValue(Value *v)
    {
      Value *size = ConstantInt::get(MySizeType, 0);
      SizeOffsetEvalType SizeOffset = ObjSizeEval->compute(v);
      if (ObjSizeEval->knownSize(SizeOffset))
      {
        // errs() << "\tUsing Size from ObjSizeEval = " << *(SizeOffset.first) << "\n";
        size = SizeOffset.first;
      }
      else
      {
        Type *t = v->getType();
        // if (!isa<Function>(v))
          // errs() << "\tUsing manual Size (ObjSizeEval failed) for " << *v << " - type:" << *t << "\n";
        // else
          // errs() << "\tUsing manual Size (ObjSizeEval failed) for " << ((Function *)v)->getName() << " - type:" << *t << "\n";

        if (t->isPointerTy())
          t = ((PointerType *)t)->getElementType();
        if (ArrayType *arrT = dyn_cast<ArrayType>(t))
        {
          // errs() << "\t\tarray[" << arrT->getNumElements() << " x " << *(arrT->getElementType()) << "]\n";
          Value *arraysize = ConstantInt::get(MySizeType, arrT->getNumElements());
          Value *totalsize = ConstantInt::get(arraysize->getType() /*MySizeType*/, CurrentDL->getTypeAllocSize(arrT->getElementType()));
          totalsize = Builder->CreateMul(totalsize, arraysize);
          size = Builder->CreateIntCast(totalsize, MySizeType, false);
        }
        else if (isa<FunctionType>(t))
        {
          // errs() << "\t\t" << *t << " is a FunctionType\n";
          size = ConstantInt::get(MySizeType, 8); // hardcode size to pointer size (i.e., 8)
        }
        else if ((isa<CallInst>(v) || isa<InvokeInst>(v)) && v->getType()->isPointerTy())
        {
          // errs() << "\t\t" << *t << " is a CallInst/InvokeInst returning a pointer type\n";
          // if this is a call to an unininstrumented function that returns a pointer, we don't have info
          size = UnknownSizeConstInt;
        }
        else
        {
          // errs() << "\t\t" << *t << " is not a special-case type for manual sizing\n";
          // last attempt at getting size (for structs)
          if (t->isSized())
            size = ConstantInt::get(MySizeType, CurrentDL->getTypeAllocSize(t));
        }
        // errs() << "\tManual Size is " << *size << "\n";
      }

      return size;
    }

    Value *getOffsetForGEPInst(GetElementPtrInst *GEPInstr)
    {

      // Vector indices are not handled by ObjectOffsetSizeEvaluator (LLVM 6)
      // TODO - Check if ObjectOffsetInstructionVisitor will work
      if (!GEPInstr->getType()->isVectorTy())
      {
        // if ObjSizeEval can directly calculate the offset for us, let's use that
        SizeOffsetEvalType SizeOffset = ObjSizeEval->compute(GEPInstr);
        if (ObjSizeEval->knownOffset(SizeOffset))
        {
          // errs() << "\tUsing Offset from ObjSizeEval = " << *(SizeOffset.second) << "\n";
          return SizeOffset.second;
        }
        // else, let's use the GEP functions
        APInt Off(CurrentDL->getPointerTypeSizeInBits(GEPInstr->getType()), 0);
        if (GEPInstr->accumulateConstantOffset(*CurrentDL, Off))
        {
          // errs() << "\tUsing Offset from GEP.accumulateConstantOffset() = " << Off << "\n";
          return ConstantInt::get(MySizeType, Off);
        }

        // as a last resort, let's infer it manually
        uint64_t typeStoreSize = CurrentDL->getTypeStoreSize(GEPInstr->getResultElementType());
        // errs() << "\tSize of type of Ptr = " << typeStoreSize << "\n";
        // Note: the following indexing used to be GEPInstr->getOperand(1), but now it should be more accurate
        Value *Idx = Builder->CreateIntCast(GEPInstr->getOperand(GEPInstr->getNumIndices()), MySizeType, false);
        Value *Size = ConstantInt::get(MySizeType /*IntTy*/, typeStoreSize);
        Value *Offset = Builder->CreateMul(Idx, Size);
        // errs() << "\tUsing Offset from manual evaluation = " << *Offset << "\n";
        return Offset;
      }
      else
      {
        // Vector
        //TODO - Can infer manually mostly
        return UnknownSizeConstInt;
      }
    }

    /// getTrapBB - create a basic block that traps. All overflowing conditions
    /// branch to this block. There's only one trap block per function.
    BasicBlock *getTrapBB(Instruction *CurrInst)
    {
      if (TrapBB != nullptr /*&& SingleTrapBB*/)
      {
        // errs() << "\tReusing existing TrapBB\n";
        return TrapBB;
      }

      // errs() << "\tCreating TrapBB...";
      Function *Fn = CurrInst->getParent()->getParent();
      IRBuilder<>::InsertPointGuard Guard(*Builder);
      TrapBB = BasicBlock::Create(Fn->getContext(), "trap", Fn);
      Builder->SetInsertPoint(TrapBB);

      // print info useful to locate the error
      /*unsigned long ln = getLineNumberForInstruction(CurrInst);
        Value* linenum = ConstantInt::get(MySizeType, ln);
        Builder->CreateCall(MyPrintErrorLineFn, linenum);
        */

      llvm::Value *F = Intrinsic::getDeclaration(Fn->getParent(), Intrinsic::trap);
      CallInst *TrapCall = Builder->CreateCall(F);
      TrapCall->setDoesNotReturn();
      TrapCall->setDoesNotThrow();
      TrapCall->setDebugLoc(CurrInst->getDebugLoc());
      Builder->CreateUnreachable();
      // errs() << " Done.\n";

      return TrapBB;
    }

    bool instrumentGEP(GetElementPtrInst *GEPInstr)
    {
      if (isCurrentFunctionWhitelisted || isCurrentFunctionWhitelistedForInstrumentation)
      {
        // errs() << "Skipping instrumentation of GEP because of whitelisting\n";
        return false;
      }

      // errs() << "Instrumenting GEP: " << *GEPInstr << " (getType: " << *(GEPInstr->getType()) << " -> getResultElementType: " << *(GEPInstr->getResultElementType()) << ")\n";

      ++ChecksConsidered;

      // find out if we're using indices, otherwise this is not necessary
      if (!(GEPInstr->hasIndices()))
      { // || GEPInstr->hasAllZeroIndices()) {
        ++ChecksUnable;
        // errs() << "\tUnable, no indices\n";
        return false;
      }

      Value *Ptr = GEPInstr->getPointerOperand();

      // check if we know the size of the pointer
      // errs() << "\tLooking for Ptr = '" << *Ptr << "'\n";
      VariableInfo *varinfo = TheState.GetPointerVariableInfo(Ptr);
      if (varinfo == NULL)
      {
        ++ChecksUnable;
        // errs() << "\tUnable, unknown variable '" << *Ptr << "'\n";
        return false;
      }
      else if (varinfo->classification == VariableStates::Safe)
      {
        ++ChecksSkippedForSafe;
        // errs() << "\tSkipping, SAFE variable '" << *Ptr << "'\n";
        return false;
      }

      // errs() << "\tVariable found, size = " << *(varinfo->size) << "\n";

      // add instrumentation to check that index is within boundaries
      uint64_t typeStoreSize = CurrentDL->getTypeStoreSize(GEPInstr->getResultElementType());

      // generate the IF branch
      Type *IntTy = CurrentDL->getIntPtrType(Ptr->getType());
      Value *Offset = getOffsetForGEPInst(GEPInstr);
      Value *LHS;
      if (ConstantInt *C = dyn_cast_or_null<ConstantInt>(varinfo->size))
        LHS = ConstantInt::get(IntTy, C->getZExtValue() - typeStoreSize);
      else
        LHS = Builder->CreateSub(varinfo->size, ConstantInt::get(IntTy, typeStoreSize));
      Value *Cmp = Builder->CreateICmpSLT(LHS, Offset);

      // errs() << "\tCmp (" << /* *(varinfo->size) */ *LHS << " < " << *Offset << ") : " << *Cmp << "\n";

      // now emit a branch instruction to a trap block.
      // If Cmp is non-null, perform a jump only if its value evaluates to true.

      // check if the comparison is always constant
      ConstantInt *C = dyn_cast_or_null<ConstantInt>(Cmp);
      if (C)
      {
        if (!C->getZExtValue())
        {
          // always false, no check needed
          // errs() << "\tCheck is always false (" << C->getZExtValue() << ") -> unneeded\n";
          ++ChecksAlwaysFalse;
          if (!IS_NAIVE)
            return false;
        }
        else
        {
          // always true, memory bug!
          // errs() << "\t" << RED << "Check is always true (" << C->getZExtValue() << ") -> unconditional memory bug!!" << NORMAL << "\n";
          ++ChecksAlwaysTrue;
          Cmp = nullptr; // unconditional branch
        }
      }
      // errs() << "\tinstrumented\n";
      ++ChecksAdded;

      if (IS_DEBUGGING)
      {
        Builder->CreateCall(MyPrintCheckFn);
      }
      Instruction *I = &*Builder->GetInsertPoint();

      BasicBlock *OldBB = I->getParent();

      OldBB->getTerminator()->eraseFromParent();

      return true;
    }

    void recordPtrTypes(std::string ptrType, Value *ptr)
    {
      auto node = _PDG->getNode(*ptr);
      if (node == nullptr || !node->isAddrVarNode())
        return;
      auto node_val = node->getValue();
      if (Instruction *i = dyn_cast<Instruction>(node_val))
      {
        auto func_name = i->getFunction()->getName().str();
        if (func_name.find("_nesCheck") != std::string::npos)
          func_name.erase(func_name.find("_nesCheck"));
        // here, maybe we should aim for functions other than boundary funcs.
        if (BoundaryFuncNames.find(func_name) == BoundaryFuncNames.end())
          return;
      }

      std::set<pdg::TreeNode*>  tree_nodes;
      for (auto in_edge : node->getInEdgeSet())
      {
        if (in_edge->getEdgeType() == pdg::EdgeType::PARAMETER_IN && in_edge->getSrcNode()->getNodeType() == pdg::GraphNodeType::FORMAL_IN)
        {
          pdg::TreeNode* tn = static_cast<pdg::TreeNode*>(in_edge->getSrcNode());
          tree_nodes.insert(tn);
          break;
        }
      }

      for (auto tree_node : tree_nodes)
      {
        auto field_id = pdg::pdgutils::computeTreeNodeID(*tree_node);
        // check if the classified field is shared id
        if (!_DDA->getSDA()->isSharedFieldID(field_id) && !tree_node->isRootNode())
          continue;
        if (ProcessedNodes.find(tree_node) != ProcessedNodes.end())
          continue;
        ProcessedNodes.insert(tree_node);
        if (ptrType == "SAFE")
        {
          _ksplit_stats->increaseSafePtrNum();
          // SafePtrs.insert(ptr);
        }
        else if (ptrType == "SEQ")
        {
          if (Instruction *i = dyn_cast<Instruction>(ptr))
            errs() << "Find seq ptr: " << *i << " - " << i->getFunction()->getName() << " - " << pdg::dbgutils::getSourceLevelVariableName(*tree_node->getDIType()) << "\n";
          if (!pdg::dbgutils::isArrayType(*tree_node->getDIType()))
            _ksplit_stats->increaseUnhandledArrayNum();
          if (pdg::dbgutils::isStructPointerType(*tree_node->getDIType()))
            _ksplit_stats->increaseStructArrayNum();
        }
        else if (ptrType == "DYN")
        {
          if (!pdg::dbgutils::isVoidPointerType(*tree_node->getDIType()))
          {
          if (Instruction *i = dyn_cast<Instruction>(ptr))
            errs() << "Find wild ptr: " << *i << " - " << i->getFunction()->getName() << " - " << pdg::dbgutils::getSourceLevelVariableName(*tree_node->getDIType()) << "\n";
          _ksplit_stats->increaseNonVoidWildPtrNum();
          }
          else
          {
            _ksplit_stats->increaseVoidWildPtrNum();
          }
          // WildPtrs.insert(ptr);
        }
        else if (ptrType == "UNKNOWN")
        {
          if (Instruction *i = dyn_cast<Instruction>(ptr))
            errs() << "Find unknown ptr: " << *i << " - " << i->getFunction()->getName() << " - " << pdg::dbgutils::getSourceLevelVariableName(*tree_node->getDIType()) << "\n";
          _ksplit_stats->increaseUnknownPtrNum();
          errs() << "unknown: " << *ptr << "\n";
          // UnknownPtrs.insert(ptr);
        }
      }
    }

    void dumpRecordedTypes()
    {
      errs() << "SAFE Ptrs: " << SafePtrs.size() << "\n";
      for (auto ptr : SafePtrs)
      {
        if (Instruction *i = dyn_cast<Instruction>(ptr))
          errs() << *i << " - " << i->getFunction()->getName() << "\n";
      }
      errs() << " =============================================== \n";

      errs() << "Seq Ptrs: " << SeqPtrs.size() << "\n";
      for (auto ptr : SeqPtrs)
      {
        if (Instruction *i = dyn_cast<Instruction>(ptr))
          errs() << *i << " - " << i->getFunction()->getName() << "\n";
      }
      errs() << " =============================================== \n";

      errs() << "Wild Ptrs: " << WildPtrs.size() << "\n";
      for (auto ptr : WildPtrs)
      {
        if (Instruction *i = dyn_cast<Instruction>(ptr))
          errs() << *i << " - " << i->getFunction()->getName() << "\n";
      }
      errs() << " =============================================== \n";

      errs() << "Unknown Ptrs: " << UnknownPtrs.size() << "\n";
      for (auto ptr : UnknownPtrs)
      {
        if (Instruction *i = dyn_cast<Instruction>(ptr))
          errs() << "Unknwon: " << *i << " - " << i->getFunction()->getName() << "\n";
      }
      errs() << " =============================================== \n";
    }

    bool processInstruction(Instruction *I)
    {
      if (!I)
        return false;

      bool changed = false;

      std::string addr;
      llvm::raw_string_ostream ss(addr);
      ss << (const void *)I;
      // if (I != nullptr)
      //   errs() << BLUE << "[" << ss.str() << "] " << NORMAL;

      for (Use &U : (&*I)->operands())
      {
        if (GlobalVariable *GV = dyn_cast<GlobalVariable>(U))
        {
          //                errs() << "Global Variable - " << *GV << "\n";
          TheState.Variables[GV].dependentFunctions.insert(TheState.Variables[GV].dependentFunctions.begin(), (I->getFunction()->getName()));
        }
        //              For the edge cases where a gep instruction is another instruction's operand
        //              GEP Instruction isn't relevant to definition of a DYN pointer but it is relevant to SEQ
        else if (GEPOperator *gepo = dyn_cast<GEPOperator>(&U))
        {
          if (GlobalVariable *GV = dyn_cast<GlobalVariable>(gepo->getPointerOperand()))
          {
            // errs() << "Global Variable - " << *GV << "\n";
            TheState.Variables[GV].dependentFunctions.insert(TheState.Variables[GV].dependentFunctions.begin(), (I->getFunction()->getName()));
          }
          for (auto it = gepo->idx_begin(), et = gepo->idx_end(); it != et; ++it)
          {
            if (GlobalVariable *GV = dyn_cast<GlobalVariable>(*it))
            {
              // errs() << "Global Variable  - " << *GV << "\n";
              TheState.Variables[GV].dependentFunctions.insert(TheState.Variables[GV].dependentFunctions.begin(), (I->getFunction()->getName()));
            }
          }
        }
      }

      if (AllocaInst *II = dyn_cast_or_null<AllocaInst>(I))
      {
        bool isArray = II->isArrayAllocation() || II->getType()->getElementType()->isArrayTy();
        // errs() << "(+) " << *II << "\t" << DETAIL << " // {";
        // if (isArray)
        //   errs() << " array[" << *(II->getArraySize()) << "]";
        // errs() << " (" << *(II->getAllocatedType()) << ") "
        //        << "}"
        //        << "" << NORMAL << "\n";

        if (II->getAllocatedType()->isPointerTy())
        {
          TheState.RegisterVariable(II);
        }
        else
        {
          Value *arraysize = II->getArraySize();
          Value *totalsize = ConstantInt::get(arraysize->getType(), CurrentDL->getTypeAllocSize(II->getAllocatedType()));
          totalsize = Builder->CreateMul(totalsize, arraysize);
          totalsize = Builder->CreateIntCast(totalsize, MySizeType, false);
          TheState.SetSizeForPointerVariable(II, totalsize);
        }
      }

      else if (CallInst *II = dyn_cast_or_null<CallInst>(I))
      {
        if (II->getCalledFunction() != NULL && II->getCalledFunction()->getName() == "malloc" && II->getCalledFunction()->arg_size() == 1)
        {
          // errs() << "(M) " << *II << "\n";
          TheState.SetSizeForPointerVariable(II, II->getArgOperand(0));
        }
        else if (II->getCalledFunction() != NULL && II->getCalledFunction()->getName() == "realloc" && II->getCalledFunction()->arg_size() == 2)
        {
          // errs() << "(M) " << *II << "\n";
          TheState.SetSizeForPointerVariable(II, II->getArgOperand(1));
        }
        else if (II->getCalledFunction() != NULL && II->getCalledFunction()->getName() == "free" && II->getCalledFunction()->arg_size() == 1)
        {
          // errs() << "(F) " << *II << "\n";
          TheState.SetSizeForPointerVariable(II->getArgOperand(0), NULL);
          // propagate new size backwards
          Value *varr = II->getArgOperand(0);
          while (true)
          {
            if (LoadInst *II = dyn_cast<LoadInst>(varr))
            {
              varr = II->getPointerOperand();
            }
            else if (BitCastInst *II = dyn_cast<BitCastInst>(varr))
            {
              varr = II->getOperand(0);
            }
            else
            {
              break;
            }
            TheState.SetSizeForPointerVariable(varr, NULL);
          }
        }
        else
        {
          // errs() << "( ) " << *II << "\n";
          if (II->getType()->isPointerTy())
            TheState.SetSizeForPointerVariable(II, getSizeForValue(II));
        }

        // check if this instruction calls a function that has been rewritten and update it
        if (II->getCalledFunction() != NULL)
        {
          StringRef fname = II->getCalledFunction()->getName();
          if (CONTAINS(FunctionsToRemove, II->getCalledFunction()) && (fname.endswith("_nesCheck")))
          {
            // errs() << "Call needs rewriting!\n";
            rewriteCallSite(II);
          }
        }
      }

      else if (ReturnInst *RI = dyn_cast_or_null<ReturnInst>(I))
      {
        // errs() << "(R) " << *RI << "\n";
        if (CONTAINS(FunctionsAddedWithNewReturnType, RI->getParent()->getParent()))
        {
          // errs() << "Return instruction needs rewriting\n";
          // Don't support functions that had multiple return values
          assert(RI->getNumOperands() < 2);
          // return the size of the pointer being returned in the old function
          // errs() << "OLD RETURN VALUE = " << *(RI->getOperand(0)) << "\n";
          Value *varr = RI->getOperand(0);
          llvm::Value *CCC;
          VariableInfo *varinfo;
          while (!(varinfo = TheState.GetPointerVariableInfo(varr)))
          {
            if (LoadInst *II = dyn_cast<LoadInst>(varr))
            {
              varr = II->getPointerOperand();
            }
            else if (CastInst *II = dyn_cast<CastInst>(varr))
            {
              varr = II->getOperand(0);
            }
            else
            {
              break;
            }
          }
          if (varinfo != NULL)
          {
            CCC = varinfo->size;
            // Start out with an empty struct
            llvm::Value *Return = llvm::ConstantAggregateZero::get(RI->getParent()->getParent()->getReturnType());
            // Insert the original return value in field 0
            Return = llvm::InsertValueInst::Create(Return, RI->getOperand(0), 0, "ret", RI);
            // Insert the globals return value in field 1
            Return = llvm::InsertValueInst::Create(Return, CCC, 1, "ret", RI);
            // errs() << "Return: " << *Return->getType();

            // And update the return instruction
            RI->setOperand(0, Return);
          }
        }
      }

      else if (StoreInst *II = dyn_cast_or_null<StoreInst>(I))
      {
        Value *valoperand = II->getValueOperand();
        // propagate size metadata
        // if (!isa<Function>(valoperand))
        //   errs() << "(~) " << *II << "\t" << DETAIL << " // {" << *valoperand << " -> " << *(II->getPointerOperand()) << " }"
        //          << "" << NORMAL << "\n";
        // else
        //   errs() << "(~) " << *II << "\t" << DETAIL << " // {" << ((Function *)valoperand)->getName() << " -> " << *(II->getPointerOperand()) << " }"
        //          << "" << NORMAL << "\n";

        if (valoperand->getType()->isPointerTy())
        {
          VariableInfo *varinfo = TheState.GetPointerVariableInfo(valoperand);

          if (!varinfo && isa<Constant>(valoperand))
            varinfo = TheState.SetSizeForPointerVariable(valoperand, getSizeForValue(valoperand));

          bool differentBasicBlock = false;
          if (Instruction *instr = dyn_cast<Instruction>(II->getPointerOperand()))
          {
            if (II->getParent() != instr->getParent())
            {
              differentBasicBlock = true;
              BasicBlock *B = instr->getParent();
              // errs() << "\tValue " << *instr << " actually comes from a different BasicBlock\n" /* << *B << "\n"*/;

              AllocaInst *sizevaralloca;
              VariableInfo *varinfo2 = TheState.GetPointerVariableInfo(instr);
              if (varinfo2 == NULL || !varinfo2->hasExplicitSizeVariable)
              {
                // create a new explicit size variable for the pointer
                sizevaralloca = new AllocaInst(MySizeType, 0, instr->getName() + "_size_nesCheck", B->getTerminator());
                // store initial size value for explicit size variable
                //Attempted bug fix - is this statement of any use?
                if (varinfo2 != NULL)
                  new StoreInst(varinfo2->size, sizevaralloca, B->getTerminator());
                TheState.SetExplicitSizeVariableForPointerVariable(instr, sizevaralloca);
              }
              else if (varinfo2 != NULL)
              {
                sizevaralloca = (AllocaInst *)(varinfo2->explicitSizeVariable);
              }
              // store new size value for explicit size variable, if this BasicBlock gets executed
              if (varinfo != NULL)
                Builder->CreateStore(varinfo->size, sizevaralloca);
            }
          }

          if (!differentBasicBlock)
          {
            if (varinfo != NULL)
            {
              std::string ptrTypeName = TheState.ClassifyPointerVariable(II->getPointerOperand(), varinfo->classification);
              recordPtrTypes(ptrTypeName, II->getPointerOperand());
              TheState.SetSizeForPointerVariable(II->getPointerOperand(), varinfo->size);

              ///checks if this StoreInst needs to store metadata in the metadata table
              if (valoperand->getType()->isPointerTy() && !(isa<AllocaInst>(II->getPointerOperand())))
              {
                setMetadataTableEntry(II->getPointerOperand(), varinfo->size, I);
              }
            }
          }
        }
      }

      else if (LoadInst *II = dyn_cast_or_null<LoadInst>(I))
      {
        // propagate size metadata
        // errs() << "(~) " << *II << "\n";
        if (II->getType()->isPointerTy())
        {
          Value *ptroperand = II->getPointerOperand();
          VariableInfo *varinfo = TheState.GetPointerVariableInfo(ptroperand);
          //                errs()<<"The PTR Operand is: "<<*ptroperand<<" and its classification is : ";

          if (!varinfo && isa<Constant>(ptroperand))
            varinfo = TheState.SetSizeForPointerVariable(ptroperand, getSizeForValue(ptroperand));
          if (varinfo != NULL)
          {
            if (varinfo->hasExplicitSizeVariable && (!varinfo->instantiatedExplicitSizeVariable ||
                                                     (isa<Instruction>(varinfo->size) && ((Instruction *)varinfo->size)->getParent() != II->getParent())))
            {
              // this pointer is bound to an explicit size variable but either the LoadInst has not been created yet
              // or it was created for a different BasicBlock and is not reachable now, so instantiate it now
              LoadInst *loadsize = Builder->CreateLoad(varinfo->explicitSizeVariable);
              TheState.SetSizeForPointerVariable(ptroperand, loadsize);
              TheState.SetInstantiatedExplicitSizeVariable(ptroperand, true);
            }
            std::string ptrTypeName = TheState.ClassifyPointerVariable(II, varinfo->classification);
            recordPtrTypes(ptrTypeName, II);
            TheState.SetSizeForPointerVariable(II, varinfo->size);
          }
        }
      }

      else if (GetElementPtrInst *II = dyn_cast_or_null<GetElementPtrInst>(I))
      {
        Value *Ptr = II->getPointerOperand();

        // errs() << "(*) " << *II << "\t" << DETAIL << " // {" << *(Ptr) << " (" << *(II->getPointerOperandType()) << ") | " << *(II->getType()) << " -> " << *(II->getResultElementType()) << " }" << NORMAL << "\n";

        // errs() << "\tIndices = " << (II->getNumOperands() - 1) << ": ";
        // errs() << "\t";
        // for (unsigned int operd = 1; operd < II->getNumOperands(); operd++)
          // errs() << *(II->getOperand(operd)) << " ; ";
        // errs() << "\n";

        // we're accessing the pointer at an offset != 0, classify it as SEQ
        if (!(II->hasAllZeroIndices()))
        {
          Type* pointerOpType = II->getPointerOperand()->getType();
          if (pointerOpType->isPointerTy())
          pointerOpType = pointerOpType->getPointerElementType();
          {
            if (!pointerOpType->isStructTy())
            {
              std::string ptrTypeName = TheState.ClassifyPointerVariable(Ptr, VariableStates::Seq);
              recordPtrTypes(ptrTypeName, Ptr);
            }
          }
        }

        // register the new variable and set size for resulting value
        TheState.RegisterVariable(II);
        if (II->getResultElementType()->isPointerTy())
        {
          // this GEP needs metadata
          //Value* valoperand = II->getPointerOperand();
          //NesCheck::VariableInfo* varinfo = TheState.GetPointerVariableInfo(valoperand);
          //setMetadataTableEntry(II->getPointerOperand(), varinfo->size, I);
          lookupMetadataTableEntry(II, I);
        }
        else
        {
          // set size as originalPtr-offset
          VariableInfo *varinfo = TheState.GetPointerVariableInfo(Ptr);
          //errs() << "\tvarinfo at " << varinfo << "\n ";
          if (varinfo != NULL)
          {
            Value *otherSize = varinfo->size;
            if (!(II->hasAllZeroIndices()))
            {
              Value *Offset = getOffsetForGEPInst(II);
              if (varinfo->size->getType() != Offset->getType())
              {
                // errs() << RED << "!!! varinfo->size->getType() (" << *(varinfo->size->getType()) << ") != Offset->getType() (" << *(Offset->getType()) << ")\n" << NORMAL;
              }
              otherSize = Builder->CreateSub(varinfo->size, Offset);
            }
            TheState.SetSizeForPointerVariable(II, otherSize);
          }
        }

        // try to instrument this GEP if needed
        //changed |= instrumentGEP(II);
      }

      else if (CastInst *II = dyn_cast_or_null<CastInst>(I))
      {
        Type *srcT = II->getSrcTy();
        Type *dstT = II->getDestTy();
        // errs() << "(>) " << *II << "\t" << DETAIL << " // { " << *srcT << " " << countIndirections(srcT) << " into " << *dstT << " " << countIndirections(dstT) << " }" << "" << NORMAL << "\n";
        if (srcT->isPointerTy())
        {
          VariableInfo *varinfo = TheState.GetPointerVariableInfo(II->getOperand(0));
          Type *innerSrcT = unwrapPointer(srcT);
          Type *innerDstT = unwrapPointer(dstT);
          if (countIndirections(srcT) != countIndirections(dstT) ||
              innerSrcT->isIntegerTy() != innerDstT->isIntegerTy())
          {
            if (LoadInst *III = dyn_cast_or_null<LoadInst>(II->getOperand(0)))
            {
              std::string ptrTypeName = TheState.ClassifyPointerVariable(III->getPointerOperand(), VariableStates::Dyn);
              recordPtrTypes(ptrTypeName, III->getPointerOperand());
            }
            else if (isa<CallInst>(II->getOperand(0)))
            {
              if (isa<BitCastInst>(II) && isa<ConstantInt>(varinfo->size) && ((ConstantInt *)varinfo->size)->getZExtValue() == 1)
                TheState.SetSizeForPointerVariable(II->getOperand(0), getSizeForValue(II));

              std::string ptrTypeName = TheState.ClassifyPointerVariable(II->getOperand(0), VariableStates::Dyn);
              recordPtrTypes(ptrTypeName, II->getOperand(0));
              ptrTypeName = TheState.ClassifyPointerVariable(II, VariableStates::Dyn);
              recordPtrTypes(ptrTypeName, II);
            }
            // else
              // errs() << "=> Ignored classification of variable since we have no operand\n";
          }

          // propagate size metadata
          if (varinfo != 0x0)
          {
            TheState.SetSizeForPointerVariable(II, varinfo->size);
          }
          else
          {
            // errs() << "!!! DON'T KNOW variable or doesn't have size\n";
          }
        }
      }

      else
      {
        //errs() << "" << RED << "( )" << NORMAL << " " << *I;
        //errs() << "\n";
      }

      return changed;
    }

    bool needsRewritten(Type *t)
    {
      return t->isPointerTy() && !isa<FunctionType>(t);
    }

    bool rewriteCallSite(Instruction *Call)
    {
      ++FunctionCallSitesRewritten;
      // errs() << "Rewriting Call " << *Call << "\n";

      // Copy the existing arguments
      std::vector<Value *> Args;
      CallSite::arg_iterator AI = Call->op_begin(), AE = Call->op_end() - 1;
      std::vector<Value *> SpecificNewArgs;

      // get info about called function
      Function *calledF = isa<InvokeInst>(Call)
                              ? ((InvokeInst *)Call)->getCalledFunction()
                              : ((CallInst *)Call)->getCalledFunction();
      const FunctionType *FTy = calledF->getFunctionType();

      // First, copy regular arguments
      for (unsigned i = 0, e = FTy->getNumParams(); i != e; ++i, ++AI)
      {
        Value *varr = AI->get();
        // errs() << "Arg: " << *varr << "\n";

        if (needsRewritten(varr->getType()))
        {
          VariableInfo *varinfo;
          while (!(varinfo = TheState.GetPointerVariableInfo(varr)) && isa<LoadInst>(varr))
            varr = ((LoadInst *)varr)->getPointerOperand();
          // errs() << "Rewriting Call " << *Call << "\n";
          if (!varinfo && isa<Constant>(varr))
            varinfo = TheState.SetSizeForPointerVariable(varr, getSizeForValue(varr));
          if (varinfo != NULL)
            SpecificNewArgs.push_back(varinfo->size);
        }
        // errs() << "AI at " << AI << "\n";
        Args.push_back(*AI);
      }

      // Then, insert the new arguments
      for (Value *newspecificarg : SpecificNewArgs)
      {
        Args.push_back(newspecificarg);
      }
      // Lastly, copy any remaining varargs
      for (; AI != AE; ++AI)
        Args.push_back(*AI);

      llvm::Instruction *NewCall;
      llvm::Instruction *Before = Call;
      Function *NF = CurrentModule->getFunction((calledF->getName() + "_nesCheck").str());
      if (llvm::InvokeInst *II = llvm::dyn_cast<llvm::InvokeInst>(Call))
      {
        NewCall = llvm::InvokeInst::Create(NF, II->getNormalDest(), II->getUnwindDest(), Args, "", Before);
        llvm::cast<llvm::InvokeInst>(NewCall)->setCallingConv(II->getCallingConv());
      }
      else
      {
        NewCall = llvm::CallInst::Create(NF, Args, "", Before);
        llvm::cast<llvm::CallInst>(NewCall)->setCallingConv(((CallInst *)Call)->getCallingConv());
        if (llvm::cast<llvm::CallInst>(Call)->isTailCall())
          llvm::cast<llvm::CallInst>(NewCall)->setTailCall();
      }

      if (Call->getType() != Type::getVoidTy(Call->getParent()->getContext()))
      {
        if (Call->hasName())
          NewCall->takeName(Call);
        else
          NewCall->setName(NF->getName() + ".ret");
      }

      // The original function returned a pointer, so the new function returns the pointer and its size
      if (needsRewritten(Call->getType()))
      {
        // errs() << "Updating return values of the call\n";
        // Split the values
        llvm::Value *OrigRet = llvm::ExtractValueInst::Create(NewCall, 0, "origret", Before);
        llvm::Value *NewRet = llvm::ExtractValueInst::Create(NewCall, 1, "sizeret", Before);
        // Replace all the uses of the original result
        Call->replaceAllUsesWith(OrigRet);
        TheState.RegisterVariable(OrigRet);
        TheState.SetSizeForPointerVariable(OrigRet, NewRet);
      }
      else
      {
        Call->replaceAllUsesWith(NewCall);
      }

      // errs() << "Call " << *Call << " replaced with " << *NewCall << "\n";

      // Finally, remove the old call from the program, reducing the use-count of F
      Call->eraseFromParent();

      return true;
    }

    bool isWhitelisted(Function *F)
    {
      StringRef fname = F->getName();
      // Whitelist all functions that are only necessary for TOSSIM simulation.
      if (fname.startswith("sim_") || fname.startswith("heap") || fname.endswith("heap") ||
          fname.startswith("hashtable_") || fname.endswith("_hashtable"))
        return true;

      return false;
    }

    bool isWhitelistedForInstrumentation(Function *F)
    {
      StringRef fname = F->getName();
      std::string fnamestr = fname.str();
      // Whitelist all functions that are only necessary for TOSSIM simulation, or for nesCheck instrumentation.
      return (isWhitelisted(F) || CONTAINS(WhitelistedFunctions, fname.str()) ||
              (fname.endswith("_nesCheck") && CONTAINS(WhitelistedFunctions, fname.drop_back(9))));
    }

    Function *rewriteFunctionSignature(Function *F)
    {
      bool needsChanged = false;
      // TODO: no instrumentation of function is needed if the pointers parameters are SAFE in every CallSite

      if (isCurrentFunctionWhitelisted)
      {
        // simply register all the parameters as if they had been processed/rewritten
        for (Function::arg_iterator i = F->arg_begin(), e = F->arg_end(); i != e; ++i)
        {
          if (needsRewritten(i->getType()))
          {
            TheState.RegisterVariable(i);
            // set the size to something arbitrarily big (for now, but we should set it to the size of the parameter type)
            TheState.SetSizeForPointerVariable(i, UnknownSizeConstInt);
          }
        }

        // skip functions used with function pointer in structs for now, cause it's a mess
        // errs() << "\n\n*********\n REWRITING SIGNATURE FOR FUNCTION: " << F->getName() << '\n';
        // errs() << "SKIPPED function rewriting because of whitelisting\n";
        return F;
      }

      // check for pointer parameters and add a respective Size parameter for each
      SmallVector<Argument *, 8> newArgs;
      for (Function::arg_iterator i = F->arg_begin(), e = F->arg_end(); i != e; ++i)
      {
        if (needsRewritten(i->getType()))
        {
          Argument *newArg = new Argument(MySizeType, i->getName() + "_size");
          newArgs.push_back(newArg); // add argument for size of this pointer

          needsChanged = true;
        }
      }
      needsChanged |= needsRewritten(F->getReturnType());

      if (!needsChanged)
        return F;

      ++FunctionSignaturesRewritten;
      // errs() << "\n\n*********\n REWRITING SIGNATURE FOR FUNCTION: " << F->getName() << '\n';

      // starts changing the signature for this function by creating a new one and moving everything over there

      const llvm::FunctionType *FTy = F->getFunctionType();

      // Prepare the argument types
      std::vector<llvm::Type *> Params(FTy->param_begin(), FTy->param_end());
      for (Argument *newarg : newArgs)
        Params.push_back(newarg->getType());

      // New return type is simply the old one if it's not a pointer,
      // or a struct of the old type and the size type if the old was a pointer
      llvm::Type *OldRetTy = F->getReturnType();
      llvm::Type *NRetTy = OldRetTy;
      if (needsRewritten(OldRetTy))
      {
        NRetTy = llvm::StructType::get(OldRetTy, MySizeType);
        //NRetTy = dyn_cast<StructType>(OldRetTy);
      }

      // Create the new function type based on the recomputed parameters.
      llvm::FunctionType *NFTy = llvm::FunctionType::get(NRetTy, Params, FTy->isVarArg());

      // Create the new function body and insert it into the module...
      llvm::Function *NF = llvm::Function::Create(NFTy, F->getLinkage(), F->getName() + "_nesCheck");
      NF->copyAttributesFrom(F);
      F->getParent()->getFunctionList().insert(F->getIterator(), NF);

      // moves an iterator to the first extra parameter of this new function
      llvm::Function::arg_iterator NNAI = NF->arg_begin();
      for (llvm::Function::arg_iterator AI = F->arg_begin(), AE = F->arg_end(); AI != AE; ++AI, ++NNAI)
        ;
      llvm::Function::arg_iterator FirstNewArgIter = NNAI;

      // copy all the argument names from the old function, plus add the new ones
      for (llvm::Function::arg_iterator AI = F->arg_begin(), AE = F->arg_end(), NAI = NF->arg_begin(); AI != AE; ++AI, ++NAI)
      {
        NAI->takeName(AI);
        if (needsRewritten(AI->getType()))
        {
          TheState.RegisterVariable(NAI);
          TheState.SetSizeForPointerVariable(NAI, NNAI);
          TheState.SetExplicitSizeVariableForPointerVariable(NAI, NNAI);
          TheState.SetInstantiatedExplicitSizeVariable(NAI, true);
          NNAI++;
        }
      }
      llvm::Function::arg_iterator NAI = FirstNewArgIter;
      for (Argument *newarg : newArgs)
      {
        // errs() << "NAI: " << *NAI << " - " << "newarg name: " << newarg->getName() << "\n";
        NAI->takeName(newarg);
        NAI++;
      }

      // Splice the body of the old function right into the new function, leaving the old rotting hulk of the function empty.
      NF->getBasicBlockList().splice(NF->begin(), F->getBasicBlockList());

      // errs() << "New signature: " << *(NF->getFunctionType()) << "\n";

      // if we changed the return type, then we will have to pimp all return instructions
      if (needsRewritten(OldRetTy))
        FunctionsAddedWithNewReturnType.push_back(NF);

      // Replace all uses of the old arguments with the new arguments
      for (llvm::Function::arg_iterator I = F->arg_begin(), E = F->arg_end(), NI = NF->arg_begin(); I != E; ++I, ++NI)
        I->replaceAllUsesWith(NI);

      // Mark old function as deletable
      FunctionsToRemove.push_back(F);

      return NF;
    }

    void analyzeFunction(Function *F)
    {
      errs() << "\n\n*********\n ANALYZING FUNCTION: " << F->getName() << "\n";
      if (isCurrentFunctionWhitelisted)
      {
        errs() << "\t[whitelisted]\n";
      }
      if (isCurrentFunctionWhitelistedForInstrumentation)
      {
        errs() << "\t[whitelisted for instrumentation]\n";
      }

      TheState.RegisterFunction(F);

      TrapBB = nullptr;

      std::vector<Instruction *> instructionsToAnalyze;
      for (inst_iterator i = inst_begin(*F), e = inst_end(*F); i != e; ++i)
      {
        Instruction *I = &*i;
        instructionsToAnalyze.push_back(I);
      }
      for (Instruction *I : instructionsToAnalyze)
      {
        Builder->SetInsertPoint(I);
        processInstruction(I);
      }
    }

    void printStats()
    {
      errs() << "\n*********\n STATS SUMMARY: \n";
      errs() << TheState.GetVariablesStateAsString() << "\n";

      NesCheckCCuredSafePtrs += TheState.GetSafePointerCount();
      NesCheckCCuredSeqPtrs += TheState.GetSeqPointerCount();
      NesCheckCCuredDynPtrs += TheState.GetDynPointerCount();
      NesCheckVariablesWithMetadataTableEntries += TheState.GetHasMetadataTableEntryCount();

      errs() << "-->) Number of functions found\t\t" << NesCheckFunctionCounter << "\n";
      errs() << "-->) Checks considered\t\t" << ChecksConsidered << "\n";
      errs() << "-->) Checks added\t\t" << ChecksAdded << "\n";
      errs() << "-->) Checks always true (memory bugs)\t\t" << ChecksAlwaysTrue << "\n";
      errs() << "-->) Checks always false (unnecessary)\t\t" << ChecksAlwaysFalse << "\n";
      errs() << "-->) Checks skipped (SAFE pointer)\t\t" << ChecksSkippedForSafe << "\n";
      errs() << "-->) Bounds checks unable to add\t\t" << ChecksUnable << "\n";
      errs() << "-->) Metadata table lookups\t\t" << MetadataTableLookups << "\n";
      errs() << "-->) Metadata table updates\t\t" << MetadataTableUpdates << "\n";
      errs() << "-->) Function signatures rewritten\t\t" << FunctionSignaturesRewritten << "\n";
      errs() << "-->) Function call sites rewritten\t\t" << FunctionCallSitesRewritten << "\n\n";

      ////        Neo4j_Wrapper::Neo4j_Connector connector;
      ////        connector.connect();
      //        std::string instruction_string;
      //        llvm::raw_string_ostream rso(instruction_string);
      //        int i=1;
      //        for(std::map<const llvm::Value*, NesCheck::VariableInfo >::iterator it =TheState.Variables.begin(); it != TheState.Variables.end(); it++)
      //        {
      //            if(it->second.classification == NesCheck::VariableStates::Dyn)
      //            {
      //                rso << *(it->first);
      //                errs()<<i<<". Classified - " << it->first<<" : " << *(it->first) << "RSO: "<< instruction_string <<" as dyn\n\n";
      ////                connector.insert_attack_graph_node(Neo4j_Wrapper::AttackState,"Unsafe pointer CCured",rso.str());
      //                instruction_string.clear();
      //                ++i;
      //            }
      //        }

      errs() << "\n\n";
    }

    bool runOnModule(Module &M) override
    {
      bool changed = false;
      _ARA = &getAnalysis<pdg::AtomicRegionAnalysis>();
      _DDA = _ARA->getDAA();
      _PDG = _DDA->getPDG();
      _ksplit_stats = &pdg::KSplitStats::getInstance();
      auto start = std::chrono::high_resolution_clock::now();
      BoundaryFuncNames = _DDA->getSDA()->getBoundaryFuncNames();

      srand(time(NULL));

      errs() << "\n\n#############\n MODULE: " << M.getName() << '\n';

      CurrentModule = &M;
      CurrentDL = &(M.getDataLayout());
      MySizeType = Type::getInt64Ty(M.getContext());
      BuilderTy TheBuilder(M.getContext());
      //BuilderTy TheBuilder(M.getContext(), TargetFolder(*CurrentDL));
      Builder = &TheBuilder;
      ObjectSizeOffsetEvaluator TheObjSizeEval(*CurrentDL, nullptr, M.getContext());
      ObjSizeEval = &TheObjSizeEval;

      // register whitelisted functions (that belong just to the TOSSIM infrastructure)
      WhitelistedFunctions = {
          "active_message_deliver", "arrangeKey", "fillInOutput",
          "is_empty", "makeNoiseModel", "makePmfDistr", "RandomInitialise", "RandomUniform"};

      // get commonly used values
      MyPrintErrorLineFn = CurrentModule->getFunction("printErrorLine");
      MyPrintCheckFn = CurrentModule->getFunction("printCheck");
      UnknownSizeConstInt = (ConstantInt *)ConstantInt::get(MySizeType, 10000000);

      TheState.SetSizeType(MySizeType);

      // register the functions to manipulate the metadata table
      setMetadataFunction = CurrentModule->getFunction("setMetadataTableEntry");
      lookupMetadataFunction = CurrentModule->getFunction("lookupMetadataTableEntry");

      if (lookupMetadataFunction == NULL)
      { //Create function call without linking
        errs() << "****  lookupMetadataTableEntry not linked ****** " << '\n';

        lookupMetadataFunction = cast<Function>(CurrentModule->getOrInsertFunction("lookupMetadataTableEntry",
                                                                                   /*ret type*/ IntegerType::getInt64Ty(CurrentModule->getContext()),
                                                                                   /*args*/ IntegerType::getInt64Ty(CurrentModule->getContext()))
                                                    .getCallee());
      }

      if (setMetadataFunction == NULL)
      {
        errs() << "****  setMetadataTableEntry not linked ****** " << '\n';

        //Create function call without linking
        setMetadataFunction = cast<Function>(CurrentModule->getOrInsertFunction("setMetadataTableEntry",
                                                                                /*ret type*/ Type::getVoidTy(CurrentModule->getContext()),
                                                                                /*args*/ IntegerType::getInt64Ty(CurrentModule->getContext()),
                                                                                IntegerType::getInt64Ty(CurrentModule->getContext()),
                                                                                IntegerType::getInt64Ty(CurrentModule->getContext()))
                                                 .getCallee());
      }

      // register all global variables
      for (auto i = M.global_begin(), e = M.global_end(); i != e; ++i)
      {
        Value *gv = &*i;
        TheState.RegisterVariable(gv);
        TheState.Variables[gv].isGlobal = true;
        if (gv->getType()->isPointerTy())
        {
          TheState.SetSizeForPointerVariable(gv, getSizeForValue(gv));
        }
      }

      // process all functions
      std::vector<Function *> FunctionsToAnalyze;
      for (auto i = M.begin(), e = M.end(); i != e; ++i)
      {
        Function *F = &*i;
        // skip declarations and nesCheckLib functions
        if (F->isDeclaration())
          continue;
        const TargetLibraryInfo *TLI = &getAnalysis<TargetLibraryInfoWrapperPass>().getTLI(*F);
        ObjectSizeOffsetEvaluator TheObjSizeEval(*CurrentDL, TLI, M.getContext());
        ObjSizeEval = &TheObjSizeEval;

        StringRef fname = F->getName();
        if (fname == "printCheck" || fname == "printErrorLine" || fname == "printFaultInjectionExecuted" ||
            fname == "setMetadataTableEntry" || fname == "lookupMetadataTableEntry" || fname == "findMetadataTableEntry" || (fname.endswith("malloc_nesCheck")))
          continue;

        ++NesCheckFunctionCounter;

        isCurrentFunctionWhitelisted = isWhitelisted(F);

        // potentially rewrite signatures and relative CallSites for all functions that take or return pointers
        Function *NF = rewriteFunctionSignature(F);
        changed |= (F != NF);
        FunctionsToAnalyze.push_back(NF);
      }

      for (Function *F : FunctionsToAnalyze)
      {
        isCurrentFunctionWhitelisted = isWhitelisted(F);
        isCurrentFunctionWhitelistedForInstrumentation = isCurrentFunctionWhitelisted || isWhitelistedForInstrumentation(F);
        // analyze all functions and populate Instrumentation WorkList
        analyzeFunction(F);
      }
      
      if (pdg::EnableAnalysisStats)
        _ksplit_stats->printStats();
      auto stop = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
      // dumpRecordedTypes();
      printStats();
      errs() << "nescheck analysis takes: " << duration.count() << "\n";
      return changed;
    }

    void getAnalysisUsage(AnalysisUsage &AU) const override
    {
      AU.addRequired<TargetLibraryInfoWrapperPass>();
      AU.addRequired<pdg::AtomicRegionAnalysis>();
    }
  };
  char NesCheckPass::ID = 0;
  static RegisterPass<NesCheckPass> X("nescheck", "nesCheck - CCured analysis + dynamic instrumentation");
}