#include "Graph.hh"

using namespace llvm;

void pdg::ProgramGraph::build(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    FunctionWrapper *func_w = new FunctionWrapper(&F);
    for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); ++inst_iter)
    {
      Node *n = new Node(*inst_iter, GraphNodeType::INST);
      _inst_node_map.insert(std::pair<Value *, Node *>(&*inst_iter, n));
      func_w->addInst(*inst_iter);
    }
    func_w->buildFormalTreeForArgs();
    _func_wrapper_map.insert(std::make_pair(&F, func_w));
  }

  // handle interprocedural connection
  // for (auto &F : M)
  // {
  //   if (F.isDeclaration() || F.empty())
  //     continue;
  //   FunctionWrapper *func_w = new FunctionWrapper(&F);
  //   auto call_insts_in_func = func_w->getCallInsts();
  //   for (auto ci : call_insts_in_func)
  //   {
  //     auto called_val = ci->getCalledValue();
  //     if (called_val == nullptr)
  //       continue;
  //     if (Function *f = dyn_cast<Function>(called_val->stripPointerCasts()))
  //     {
  //       CallWrapper *cw = new CallWrapper(ci);
  //       cw->buildActualTreeForArgs(func_w);
  //       connectCallerAndCallee(cw, func_w);
  //     }
  //     _call_wrapper_map.insert(ci, cw);
  //   }
  // }
}


// pdg::Node::computeNodeDIType(Value &v)
// {
//   if (Instruction *i = dyn_cast<Instruction>(v))
//   {
//     if (AllocaInst *ai = dyn_cast<AllocaInst>(i))
//     {
//       DIType *allocDIType = dbgutils::getInstDIType(ai, dbgInstList);
//       return allocDIType;
//     }

//     if (LoadInst *li = dyn_cast<LoadInst>(inst))
//     {
//       if (Instruction *sourceInst = dyn_cast<Instruction>(li->getPointerOperand()))
//       {
//         if (G_InstDITypeMap.find(sourceInst) == G_InstDITypeMap.end())
//           return nullptr;
//         DIType *sourceInstDIType = G_InstDITypeMap[sourceInst];
//         // DIType* retDIType = DIUtils::stripAttributes(sourceInstDIType);
//         DIType *retDIType = DIUtils::getLowestDIType(sourceInstDIType);
//         return retDIType;
//       }
//       if (GlobalVariable *gv = dyn_cast<GlobalVariable>(li->getPointerOperand()))
//       {
//         DIType *sourceGlobalVarDIType = DIUtils::getGlobalVarDIType(*gv);
//         if (!sourceGlobalVarDIType)
//           return nullptr;
//         return DIUtils::getLowestDIType(sourceGlobalVarDIType);
//       }
//     }

//     if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(inst))
//     {
//       if (Instruction *sourceInst = dyn_cast<Instruction>(gep->getPointerOperand()))
//       {
//         if (G_InstDITypeMap.find(sourceInst) == G_InstDITypeMap.end())
//           return nullptr;
//         DIType *sourceInstDIType = G_InstDITypeMap[sourceInst];
//         sourceInstDIType = DIUtils::stripMemberTag(sourceInstDIType);
//         sourceInstDIType = DIUtils::stripAttributes(sourceInstDIType);
//         if (DIUtils::isStructTy(sourceInstDIType) || DIUtils::isStructPointerTy(sourceInstDIType))
//         {
//           sourceInstDIType = DIUtils::getLowestDIType(sourceInstDIType);
//           auto DINodeArr = dyn_cast<DICompositeType>(sourceInstDIType)->getElements();
//           StructType *structTy = getStructTypeFromGEP(gep);
//           if (structTy == nullptr)
//             return nullptr;
//           for (unsigned i = 0; i < DINodeArr.size(); ++i)
//           {
//             DIType *fieldDIType = dyn_cast<DIType>(DINodeArr[i]);
//             if (isGEPOffsetMatchWithDI(structTy, fieldDIType, gep))
//               return fieldDIType;
//           }
//         }
//       }
//     }

//     if (CastInst *castInst = dyn_cast<CastInst>(inst))
//     {
//       if (Instruction *sourceInst = dyn_cast<Instruction>(castInst->getOperand(0)))
//       {
//         if (G_InstDITypeMap.find(sourceInst) == G_InstDITypeMap.end())
//           return nullptr;
//         return G_InstDITypeMap[sourceInst];
//       }
//     }
//   }

//   return nullptr;
// }

bool pdg::ProgramGraph::hasNode(Value &v)
{
  return (_inst_node_map.find(&v) != _inst_node_map.end());
}

pdg::Node *pdg::ProgramGraph::getNode(Value& v)
{
  if (!hasNode(v))
    return nullptr;
  return _inst_node_map[&v];
}

void pdg::ProgramGraph::connectNodesByVal(Value& src, Value& dst, EdgeType edge_type)
{
  if (!hasNode(src) || !hasNode(dst))
    return;
  Node *src_node = getNode(src);
  Node *dst_node = getNode(dst);
  Edge e(src_node, dst_node, edge_type);
  src_node->addOutEdge(e);
  dst_node->addInEdge(e);
  addEdge(e);
}