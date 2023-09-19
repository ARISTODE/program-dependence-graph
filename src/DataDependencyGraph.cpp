#include "DataDependencyGraph.hh"

char pdg::DataDependencyGraph::ID = 0;

using namespace llvm;

bool pdg::DataDependencyGraph::runOnModule(Module &M)
{
  _module = &M;

  PDGCallGraph &call_g = PDGCallGraph::getInstance();
  if (!call_g.isBuild())
  {
    call_g.build(M);
    call_g.setupBuildFuncNodes(M);
  }
  // setup SVF
  PTAWrapper &ptaw = PTAWrapper::getInstance();
  if (!ptaw.hasPTASetup())
    ptaw.setupPTA(M);

  ProgramGraph &g = ProgramGraph::getInstance();
  if (!g.isBuild())
  {
    g.build(M);
    g.bindDITypeToNodes(M);
  }

  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    // if (!call_g.isBuildFuncNode(F))
    //   continue;
    _mem_dep_res = &getAnalysis<MemoryDependenceWrapperPass>(F).getMemDep();
    for (auto instIter = inst_begin(F); instIter != inst_end(F); instIter++)
    {
      addDefUseEdges(*instIter);
      addAliasEdges(*instIter);
      addRAWEdges(*instIter);
      addRAWEdgesUnderapproximate(*instIter);
      if (StoreInst *si = dyn_cast<StoreInst>(&*instIter))
        addStoreToEdge(*si);
      if (LoadInst *li = dyn_cast<LoadInst>(&*instIter))
        addEqualObjEdge(*li);
    }
  }
  return false;
}

void pdg::DataDependencyGraph::addAliasEdges(Instruction &inst)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  PTAWrapper &ptaw = PTAWrapper::getInstance();
  Function *func = inst.getFunction();

  auto instIter = inst_begin(func);

  for (; instIter != inst_end(func); instIter++)
  {
    if (&inst == &*instIter)
      continue;
    if (!inst.getType()->isPointerTy())
      continue;
    auto andersAAresult = ptaw.queryAlias(inst, *instIter);
    auto mustAliasRes = queryMustAlias(inst, *instIter);
    if (andersAAresult != NoAlias || mustAliasRes != NoAlias)
    {
      Node *src = g.getNode(inst);
      Node *dst = g.getNode(*instIter);
      if (src == nullptr || dst == nullptr)
        continue;
      // use type info to eliminate dubious gep
      // TODO: prune the type by creating equivalent classes
      if (inst.getType() != instIter->getType())
      {
        continue;
        //if (!isa<BitCastInst>(*instIter) && !isa<BitCastInst>(&inst))
      }
      // if alias is a gep, ensure the offset is the same
      if (auto srcGep = dyn_cast<GetElementPtrInst>(&inst))
      {
        if (auto dstGep = dyn_cast<GetElementPtrInst>(&*instIter))
        {
          StructType *srcStructTy = pdgutils::getStructTypeFromGEP(*srcGep);
          StructType *dstStructTy = pdgutils::getStructTypeFromGEP(*dstGep);
          if (!srcStructTy || !dstStructTy)
            continue;
          uint64_t srcGepBitOffset = pdgutils::getGEPOffsetInBits(*_module, *srcStructTy, *srcGep);
          uint64_t dstGepBitOffset = pdgutils::getGEPOffsetInBits(*_module, *srcStructTy, *dstGep);
          if (srcGepBitOffset != dstGepBitOffset)
            continue;
        }
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

void pdg::DataDependencyGraph::addRAWEdgesUnderapproximate(Instruction &inst)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  if (LoadInst *li = dyn_cast<LoadInst>(&inst))
  {
    Function *curFunc = inst.getFunction();
    // obtain load address
    auto loadAddr = li->getPointerOperand();
    auto addrNode = g.getNode(*loadAddr);
    if (addrNode == nullptr)
    {
      // errs() << "empty addr node load inst " << *loadAddr << " in func " << curFunc->getName().str() << "\n";
      return;
    }
    auto aliasNodes = addrNode->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
    aliasNodes.insert(addrNode);
    // check the user of the load addr, search for store inst
    // check for alias nodes
    for (auto aliasNode : aliasNodes)
    {
      auto nodeVal = aliasNode->getValue();
      if (!nodeVal)
        continue;
      for (auto user : nodeVal->users())
      {
        if (StoreInst *si = dyn_cast<StoreInst>(user))
        {
          if (si->getPointerOperand() == nodeVal)
          {
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

// this function query the must alias relation for intra-function analysis
AliasResult pdg::DataDependencyGraph::queryMustAlias(Value &v1, Value &v2)
{
  if (!v1.getType()->isPointerTy() || !v2.getType()->isPointerTy())
    return NoAlias;
  // check bit cast
  if (BitCastInst *bci = dyn_cast<BitCastInst>(&v1))
  {
    if (bci->getOperand(0) == &v2)
      return MustAlias;
  }

  // check load-store pattern
  for (auto user : v1.users())
  {
    if (LoadInst *li = dyn_cast<LoadInst>(user))
    {
      for (auto loadValUser : li->users())
      {
        if (StoreInst *si = dyn_cast<StoreInst>(loadValUser))
        {
          if (si->getPointerOperand() == &v2)
            return MustAlias;
        }
      }
    }
  }

  // handle load instruction
  if (LoadInst *li = dyn_cast<LoadInst>(&v1))
  {
    auto load_addr = li->getPointerOperand();
    for (auto user : load_addr->users())
    {
      // check if two loads can load form the same address
      if (isa<LoadInst>(user))
      {
        if (user == &v2)
          return MustAlias;
      }
      // // check 
      // if (StoreInst *si = dyn_cast<StoreInst>(user))
      // {
      //   if (si->getPointerOperand() == load_addr)
      //   {
      //     if (si->getValueOperand() == &v2)
      //       return MustAlias;
      //   }
      // }
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

void pdg::DataDependencyGraph::addStoreToEdge(StoreInst &si)
{
  ProgramGraph &g = ProgramGraph::getInstance();

  auto ptrOp = si.getPointerOperand();
  auto valOp = si.getValueOperand();
  auto ptrOpNode = g.getNode(*ptrOp);
  auto valOpNode = g.getNode(*valOp);
  if (!ptrOpNode || !valOpNode)
    return;
  valOpNode->addNeighbor(*ptrOpNode, EdgeType::DATA_STORE_TO);
}

// load instructon is used to load objects from pointer
void pdg::DataDependencyGraph::addEqualObjEdge(LoadInst &li)
{
  ProgramGraph &g = ProgramGraph::getInstance();
  // search for object load from the same address
  auto loadAddr = li.getPointerOperand();
  for (auto user : li.users())
  {
    if (auto si = dyn_cast<StoreInst>(user))
    {
      // check if the object is being stored to another SSA register
      if (si->getValueOperand() == &li)
      {
        auto storeAddr = si->getPointerOperand();
        // for the stored SSA register, check the load from the address, the loaded object is the equavalent
        // object of li
        for (auto storeAddrUser : storeAddr->users())
        {
          if (isa<LoadInst>(storeAddrUser))
          {
            auto srcObjNode = g.getNode(li);
            auto dstObjNode = g.getNode(*storeAddrUser);
            if (!srcObjNode || !dstObjNode)
              continue;
            srcObjNode->addNeighbor(*dstObjNode, EdgeType::DATA_EQUL_OBJ);
          }
        }
      }
    }
  }
}

void pdg::DataDependencyGraph::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<MemoryDependenceWrapperPass>();
  AU.setPreservesAll();
}

static RegisterPass<pdg::DataDependencyGraph>
    DDG("ddg", "Data Dependency Graph Construction", false, true);