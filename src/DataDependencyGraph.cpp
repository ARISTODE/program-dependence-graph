#include "DataDependencyGraph.hh"
#include "PDGUtils.hh"
#include "llvm/Analysis/MemoryDependenceAnalysis.h"

using namespace llvm;

llvm::AnalysisKey pdg::DataDependencyGraph::Key;

pdg::DataDependencyGraph::Result pdg::DataDependencyGraph::run(Module &M, ModuleAnalysisManager &MAM) {
  _module = &M;

  PDGCallGraph &call_g = PDGCallGraph::getInstance();
  if (!call_g.isBuild()) {
    call_g.build(M);
    call_g.setupBuildFuncNodes(M);
  }

  // setup SVF
  PTAWrapper &ptaw = PTAWrapper::getInstance();
  if (!ptaw.hasPTASetup())
    ptaw.setupPTA(M);

  ProgramGraph &g = ProgramGraph::getInstance();

  if (!g.isBuild()) {
    // setup the interface functions for PDG build
    g.build(M);
    // TODO: add comment
    g.bindDITypeToNodes(M);
  }

  for (auto &F : M) {
    if (F.isDeclaration() || F.empty())
      continue;

    if (!g.hasFuncWrapper(F))
      continue;

    auto &FAM = MAM.getResult<FunctionAnalysisManagerModuleProxy>(M).getManager();
    _mem_dep_res = &FAM.getResult<MemoryDependenceAnalysis>(F);
    
    // setup alias query interface for each function
    for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); inst_iter++) {
      addDefUseEdges(*inst_iter);
      addAliasEdges(*inst_iter);
      addRAWEdges(*inst_iter);
      // some RAW could be missing due to the unsound alias analysis, need to swap the alias analysis used by the memory dependency analysis to obtain more precise results.
      addRAWEdgesUnderapproximate(*inst_iter);
      if (StoreInst *si = dyn_cast<StoreInst>(&*inst_iter))
        addStoreToEdge(*si);
      if (LoadInst *li = dyn_cast<LoadInst>(&*inst_iter))
        addEqualObjEdge(*li);
    }
  }
  return Result{true};
}

void pdg::DataDependencyGraph::addAliasEdges(Instruction &inst) {
  ProgramGraph &g = ProgramGraph::getInstance();
  PTAWrapper &ptaw = PTAWrapper::getInstance();
  Function *func = inst.getFunction();

  auto inst_iter = inst_begin(func);

  for (; inst_iter != inst_end(func); inst_iter++) {
    if (&inst == &*inst_iter)
      continue;
    
    if (!inst.getType()->isPointerTy())
      continue;
    auto andersAAresult = ptaw.queryAlias(inst, *inst_iter);
    auto mustAliasRes = queryMustAlias(inst, *inst_iter);
    if (andersAAresult != AliasResult::NoAlias || mustAliasRes != AliasResult::NoAlias) {
      if (mustAliasRes != AliasResult::NoAlias) {
        Node *src = g.getNode(inst);
        Node *dst = g.getNode(*inst_iter);
        if (src == nullptr || dst == nullptr)
          continue;
        // use type info to eliminate dubious gep
        // TODO: prune the type by creating equivalent classes
        if (inst.getType() != inst_iter->getType()) {
          continue;
          //if (!isa<BitCastInst>(*inst_iter) && !isa<BitCastInst>(&inst))
        }
        // if alias is a gep, ensure the offset is the same
        if (auto srcGep = dyn_cast<GetElementPtrInst>(&inst)) {
          if (auto dstGep = dyn_cast<GetElementPtrInst>(&*inst_iter)) {
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
}

void pdg::DataDependencyGraph::addDefUseEdges(Instruction &inst) {
  ProgramGraph &g = ProgramGraph::getInstance();
  for (auto user : inst.users()) {
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
    
    // add a special variant for data def_use relation
    if (isa<LoadInst>(user))
      src->addNeighbor(*dst, EdgeType::DATA_DEF_USE_LOAD);
    else if (isa<GetElementPtrInst>(user))
      src->addNeighbor(*dst, EdgeType::DATA_DEF_USE_GEP);
    else if (isa<CastInst>(user))
      src->addNeighbor(*dst, EdgeType::DATA_DEF_USE_CAST);
    else if (isa<BinaryOperator>(user))
      src->addNeighbor(*dst, EdgeType::DATA_DEF_USE_ARITH);
  }
}

void pdg::DataDependencyGraph::addRAWEdges(Instruction &inst) {
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
    auto aliasNodes = addrNode->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
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

// this function query the must alias relation for intra-function analysis
AliasResult pdg::DataDependencyGraph::queryMustAlias(Value &v1, Value &v2) {
  if (!v1.getType()->isPointerTy() || !v2.getType()->isPointerTy())
    return AliasResult::NoAlias;
  // check bit cast
  if (BitCastInst *bci = dyn_cast<BitCastInst>(&v1)) {
    if (bci->getOperand(0) == &v2)
      return AliasResult::MustAlias;
  }

  // check load-store pattern
  for (auto user : v1.users()) {
    if (LoadInst *li = dyn_cast<LoadInst>(user)) {
      for (auto loadValUser : li->users()) {
        if (StoreInst *si = dyn_cast<StoreInst>(loadValUser)) {
          if (si->getPointerOperand() == &v2)
            return AliasResult::MustAlias;
        }
      }
    }
  }

  // handle load instruction
  if (LoadInst *li = dyn_cast<LoadInst>(&v1)) {
    auto load_addr = li->getPointerOperand();
    for (auto user : load_addr->users()) {
      // check if two loads can load form the same address
      if (isa<LoadInst>(user)) {
        if (user == &v2)
          return AliasResult::MustAlias;
      }
    }
  }

  // handle gep
  ProgramGraph &g = ProgramGraph::getInstance();
  if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(&v1)) {
    if (gep->getPointerOperand() == &v2 && gep->hasAllZeroIndices())
      return AliasResult::MustAlias;
    if (GetElementPtrInst *gepp = dyn_cast<GetElementPtrInst>(&v2)) {
      auto gepAddr = gep->getPointerOperand();
      auto geppAddr = gepp->getPointerOperand();
      if (g.getNode(*gepAddr)) {
        auto aliasNodes = g.getNode(*gepAddr)->getOutNeighborsWithDepType(EdgeType::DATA_ALIAS);
        if (aliasNodes.find(g.getNode(*geppAddr)) != aliasNodes.end())
          return AliasResult::MustAlias;
      }
    }
  }

  // for others instructions, check if v2 can be loaded form the same address
  if (Instruction *i = dyn_cast<Instruction>(&v1)) {
    for (auto user : i->users()) {
      if (StoreInst *si = dyn_cast<StoreInst>(user)) {
        auto storeAddr = si->getPointerOperand();
        for (auto storeAddrUser : storeAddr->users()) {
          if (storeAddrUser == &v2)
            return AliasResult::MustAlias;
        }
      }
    }
  }

  return AliasResult::NoAlias;
}

void pdg::DataDependencyGraph::addStoreToEdge(StoreInst &si) {
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
void pdg::DataDependencyGraph::addEqualObjEdge(LoadInst &li) {
  ProgramGraph &g = ProgramGraph::getInstance();
  // search for object load from the same address
  auto loadAddr = li.getPointerOperand();
  auto loadAddrNode = g.getNode(*loadAddr);
  auto aliasNodes = g.findNodesReachedByEdge(*loadAddrNode, EdgeType::DATA_ALIAS);
  for (auto aliasNode : aliasNodes) {
    if (aliasNode == loadAddrNode)
      continue;

    auto aliasNodeVal = aliasNode->getValue();
    for (auto aliasUser : aliasNodeVal->users()) {
      if (isa<LoadInst>(aliasUser)) {
        auto srcObjNode = g.getNode(li);
        auto dstObjNode = g.getNode(*aliasUser);
        if (!srcObjNode || !dstObjNode)
          continue;
        srcObjNode->addNeighbor(*dstObjNode, EdgeType::DATA_EQUL_OBJ);
      }
    }
  }
}