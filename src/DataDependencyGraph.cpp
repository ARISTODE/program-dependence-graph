#include "DataDependencyGraph.hh"
#include "PDGUtils.hh"
#include "llvm/Analysis/MemoryDependenceAnalysis.h"

llvm::AnalysisKey pdg::DataDependencyGraph::Key;

using namespace llvm;

pdg::DataDependencyGraph::Result pdg::DataDependencyGraph::run(Module &M, ModuleAnalysisManager &MAM)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  if (!g.isBuild())
  {
    g.build(M);
    // TODO: add comment
    g.bindDITypeToNodes(M);
  }
  
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    
    auto &FAM = MAM.getResult<FunctionAnalysisManagerModuleProxy>(M).getManager();
    _mem_dep_res = &FAM.getResult<MemoryDependenceAnalysis>(F);
    // setup alias query interface for each function
    for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); inst_iter++)
    {
      addDefUseEdges(*inst_iter);
      addAliasEdges(*inst_iter);
      addRAWEdges(*inst_iter);
      // some RAW could be missing due to the unsound alias analysis, need to swap the alias analysis used by the memory dependency analysis to obtain more precise results.
      addRAWEdgesUnderapproximate(*inst_iter);
    }
  }
  return Result{true};
}


void pdg::DataDependencyGraph::addAliasEdges(Instruction &inst)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  Function* func = inst.getFunction();
  for (auto inst_iter = inst_begin(func); inst_iter != inst_end(func); inst_iter++)
  {
    if (&inst == &*inst_iter)
      continue;
    
    auto alias_result = queryAliasUnderApproximate(inst, *inst_iter);
    if (alias_result != AliasResult::NoAlias)
    {
      Node* src = g.getNode(inst);
      Node* dst = g.getNode(*inst_iter);
      if (src == nullptr || dst == nullptr)
        continue;
      src->addNeighbor(*dst, EdgeType::DATA_ALIAS);
    }
  }
}

void pdg::DataDependencyGraph::addDefUseEdges(Instruction &inst)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  for (auto user : inst.users())
  {
    Node *src = g.getNode(inst);
    Node *dst = g.getNode(*user);
    if (src == nullptr || dst == nullptr)
      continue;
    EdgeType edge_type = EdgeType::DATA_DEF_USE;
    if (dst->getNodeType() == GraphNodeType::ANNO_VAR)
      edge_type = EdgeType::ANNO_VAR;
    if (dst->getNodeType() == GraphNodeType::ANNO_GLOBAL)
      edge_type = EdgeType::ANNO_GLOBAL;
    src->addNeighbor(*dst, edge_type);
  }
}

void pdg::DataDependencyGraph::addRAWEdges(Instruction &inst)
{
  if (!isa<LoadInst>(&inst))
    return;

  ProgramGraph &g = ProgramGraph::getInstance();
  auto dep_res = _mem_dep_res->getDependency(&inst);
  auto dep_inst = dep_res.getInst();
  
  if (!dep_inst || !isa<StoreInst>(dep_inst))
    return;

  Node *src = g.getNode(inst);
  Node *dst = g.getNode(*dep_inst);
  if (src == nullptr || dst == nullptr)
    return;
  dst->addNeighbor(*src, EdgeType::DATA_RAW);
}

void pdg::DataDependencyGraph::addRAWEdgesUnderapproximate(Instruction &inst) {
  ProgramGraph &g = ProgramGraph::getInstance();
  if (LoadInst *li = dyn_cast<LoadInst>(&inst)) {
    Function* curFunc = inst.getFunction();
    // obtain load address
    auto loadAddr = li->getPointerOperand();
    auto addrNode = g.getNode(*loadAddr);
    if (addrNode == nullptr) {
        errs() << "empty addr node load inst " << *loadAddr << " in func " << curFunc->getName().str() << "\n";
        return;
    }
    auto aliasNodes =
        addrNode->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
    aliasNodes.insert(addrNode);
    // check the user of the load addr, search for store inst
    // check for alias nodes
    for (auto aliasNode : aliasNodes) {
      auto nodeVal = aliasNode->getValue();
      if (!nodeVal)
        continue;
      for (auto user : nodeVal->users()) {
        if (StoreInst* si = dyn_cast<StoreInst>(user)) {
          if (si->getPointerOperand() == nodeVal) {
            // check for order, the store must happen before the load
            if (!pdgutils::isPrecedeInst(*si, *li, *curFunc))
              continue;
            // add raw dep from store to load
            auto storeNode = g.getNode(*si);
            auto loadNode = g.getNode(*li);
            assert((storeNode && loadNode) && "error processing empty node (RAW edge processing)\n");
            storeNode->addNeighbor(*loadNode, EdgeType::DATA_RAW);
          }
        }
      }
    }
  }
}

AliasResult pdg::DataDependencyGraph::queryAliasUnderApproximate(Value &v1, Value &v2)
{
  if (!v1.getType()->isPointerTy() || !v2.getType()->isPointerTy())
    return AliasResult::NoAlias;
  // check bit cast
  if (BitCastInst *bci = dyn_cast<BitCastInst>(&v1))
  {
    if (bci->getOperand(0) == &v2)
      return AliasResult::MustAlias;
  }
  // handle load instruction
  if (LoadInst *li = dyn_cast<LoadInst>(&v1))
  {
    auto load_addr = li->getPointerOperand();
    for (auto user : load_addr->users())
    {
      if (StoreInst *si = dyn_cast<StoreInst>(user))
      {
        if (si->getPointerOperand() == load_addr)
        {
          if (si->getValueOperand() == &v2)
            return AliasResult::MustAlias;
        }
      }
    }
  }
  return AliasResult::NoAlias;
}

