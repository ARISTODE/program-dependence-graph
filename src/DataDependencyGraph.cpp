#include "DataDependencyGraph.hh"

char pdg::DataDependencyGraph::ID = 0;

using namespace llvm;

bool pdg::DataDependencyGraph::runOnModule(Module &M)
{
  // setup SVF 
  ProgramGraph &g = ProgramGraph::getInstance();
  PTAWrapper &ptaw = PTAWrapper::getInstance();
  if (!g.isBuild())
  {
    g.build(M);
    g.bindDITypeToNodes(M);
  }

  if (!ptaw.hasPTASetup())
    ptaw.setupPTA(M);

  // std::chrono::milliseconds defuse = std::chrono::milliseconds::zero();
  // std::chrono::milliseconds raw = std::chrono::milliseconds::zero();
  // std::chrono::milliseconds alias = std::chrono::milliseconds::zero();

  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    _mem_dep_res = &getAnalysis<MemoryDependenceWrapperPass>(F).getMemDep();
    for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); inst_iter++)
    {
      // auto t1 = std::chrono::high_resolution_clock::now();
      addDefUseEdges(*inst_iter);
      // auto t2 = std::chrono::high_resolution_clock::now();
      // defuse += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
      addRAWEdges(*inst_iter);
      addRAWEdgesUnderapproximate(*inst_iter);
      // auto t3 = std::chrono::high_resolution_clock::now();
      // raw += std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2);
      addAliasEdges(*inst_iter);
      // auto t4 = std::chrono::high_resolution_clock::now();
      // alias += std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3);
    }
  }
  // errs() << "defuse: " << std::chrono::duration_cast<std::chrono::milliseconds>(defuse).count() << "\n";
  // errs() << "raw: " << std::chrono::duration_cast<std::chrono::milliseconds>(raw).count() << "\n";
  // errs() << "alias: " << std::chrono::duration_cast<std::chrono::milliseconds>(alias).count() << "\n";
  return false;
}

void pdg::DataDependencyGraph::addAliasEdges(Instruction &inst)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  PTAWrapper &ptaw = PTAWrapper::getInstance();
  Function* func = inst.getFunction();
  for (auto inst_iter = inst_begin(func); inst_iter != inst_end(func); inst_iter++)
  {
    if (&inst == &*inst_iter)
      continue;
    if (!inst.getType()->isPointerTy())
      continue;
    auto anders_aa_result = ptaw.queryAlias(inst, *inst_iter);
    auto alias_result = queryAliasUnderApproximate(inst, *inst_iter);
    if (anders_aa_result != NoAlias || alias_result != NoAlias)
    {
      Node* src = g.getNode(inst);
      Node* dst = g.getNode(*inst_iter);
      if (src == nullptr || dst == nullptr)
        continue;
      // use type info to eliminate dubious gep
      if (!isa<BitCastInst>(*inst_iter) && !isa<BitCastInst>(&inst))
      {
        if (inst.getType() != inst_iter->getType())
          continue;
      }
      src->addNeighbor(*dst, EdgeType::DATA_ALIAS);
      dst->addNeighbor(*src, EdgeType::DATA_ALIAS);
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
    src->addNeighbor(*dst, EdgeType::DATA_DEF_USE);
  }
}

void pdg::DataDependencyGraph::addRAWEdges(Instruction &inst)
{
  if (!isa<LoadInst>(&inst))
    return;

  ProgramGraph &g = ProgramGraph::getInstance();
  auto dep_res = _mem_dep_res->getDependency(&inst);
  auto dep_inst = dep_res.getInst();

  if (!dep_inst)
    return;
  if (!isa<StoreInst>(dep_inst))
    return;

  Node *src = g.getNode(inst);
  Node *dst = g.getNode(*dep_inst);
  if (src == nullptr || dst == nullptr)
    return;
  dst->addNeighbor(*src, EdgeType::DATA_RAW);
  src->addNeighbor(*dst, EdgeType::DATA_RAW_REV);
}

void pdg::DataDependencyGraph::addRAWEdgesUnderapproximate(Instruction &inst) {
  ProgramGraph &g = ProgramGraph::getInstance();
  if (LoadInst *li = dyn_cast<LoadInst>(&inst)) {
    Function* curFunc = inst.getFunction();
    // obtain load address
    auto loadAddr = li->getPointerOperand();
    auto addrNode = g.getNode(*loadAddr);
    if (addrNode == nullptr) {
        // errs() << "empty addr node load inst " << *loadAddr << " in func " << curFunc->getName().str() << "\n";
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
    return NoAlias;
  // check bit cast
  if (BitCastInst *bci = dyn_cast<BitCastInst>(&v1))
  {
    if (bci->getOperand(0) == &v2)
      return MustAlias;
  }
  // handle load instruction  
  if (LoadInst* li = dyn_cast<LoadInst>(&v1))
  {
    auto load_addr = li->getPointerOperand();
    for (auto user : load_addr->users())
    {
      if (isa<LoadInst>(user))
      {
        if (user == &v2)
          return MustAlias;
      }
      if (StoreInst *si = dyn_cast<StoreInst>(user))
      {
        if (si->getPointerOperand() == load_addr)
        {
          if (si->getValueOperand() == &v2)
            return MustAlias;
        }
      }
    }
  }

  // handle gep
  if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(&v1))
  {
    if (gep->getPointerOperand() == &v2 && gep->hasAllZeroIndices())
      return MustAlias;
  }

  // for others instructions, check if v2 can be loaded form the same address
  if (Instruction *i = dyn_cast<Instruction>(&v1))
  {
    for (auto user : i->users())
    {
      if (StoreInst *si = dyn_cast<StoreInst>(user))
      {
        auto storeAddr = si->getPointerOperand();
        for (auto storeAddrUser : storeAddr->users())
        {
          if (storeAddrUser == &v2)
            return MustAlias;
        }
      }
    }
  }

  return NoAlias;
}

void pdg::DataDependencyGraph::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<MemoryDependenceWrapperPass>();
  AU.setPreservesAll();
}

static RegisterPass<pdg::DataDependencyGraph>
    DDG("ddg", "Data Dependency Graph Construction", false, true);