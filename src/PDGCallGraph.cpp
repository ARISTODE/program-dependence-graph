#include "PDGCallGraph.hh"

using namespace llvm;

void pdg::PDGCallGraph::build(Module &M)
{
  // setup functions that we don't need to consider during the analysis
  setupExcludeFuncs();
  setupExportedFuncs();
  // setup driver functions
  setupDriverFuncs(M);
  // setup interface functions
  setupBoundaryFuncs(M);
  unsigned total_num_func = 0;
  // build call graph nodes
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    total_num_func += 1;
    Node *n = new Node(F, GraphNodeType::FUNC);
    _val_node_map.insert(std::make_pair(&F, n));
    addNode(*n);
  }
  errs() << "total number of functions: " << total_num_func << "\n";
  // connect nodes through direct/indirect call edges
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    auto caller_node = getNode(F);
    for (auto inst_i = inst_begin(F); inst_i != inst_end(F); inst_i++)
    {
      if (CallInst *ci = dyn_cast<CallInst>(&*inst_i))
      {
        if (isa<DbgVariableIntrinsic>(ci))
          continue;
        if (ci->isInlineAsm())
          continue;
        auto called_func = pdgutils::getCalledFunc(*ci);
        // direct calls
        if (called_func != nullptr)
        {
          auto callee_node = getNode(*called_func);
          if (callee_node != nullptr)
            caller_node->addNeighbor(*callee_node, EdgeType::CALL);
        }
        else
        {
          auto ind_call_candidates = getIndirectCallCandidates(*ci, M);
          for (auto ind_call_can : ind_call_candidates)
          {
            Node *callee_node = getNode(*ind_call_can);
            if (callee_node != nullptr)
              caller_node->addNeighbor(*callee_node, EdgeType::IND_CALL);
          }
        }
      }
    }
  }
  // the followings are specific for computing the functions that require 
  // static analyses 
  // 1. taint all the pointer type arguments passed in the interface function
  for (auto func : _boundary_funcs)
  {
    _taint_funcs.insert(func);
    // taint all pointer arguments
    for (auto arg_iter = func->arg_begin(); arg_iter != func->arg_end(); arg_iter++)
    {
      _taint_vals.insert(&*arg_iter);
    }
    // taint global variables accessed in driver functions
    computeTaintGlobals();
  }
  // propagate taints and record all tained funcs, these functions are needed in static analysis
  computeTaintFuncs(M);
  errs() << "finish building call graph\n";
  errs() << "tainted funcs: " << _taint_funcs.size() << "\n";
  errs() << "global require analysis: " << _global_var_analysis.size() << "\n";
  _is_build = true;
}

bool pdg::PDGCallGraph::isFuncSignatureMatch(CallInst &ci, llvm::Function &f)
{
  if (f.isVarArg())
    return false;
  auto actual_arg_list_size = ci.getNumArgOperands();
  auto formal_arg_list_size = f.arg_size();
  if (actual_arg_list_size != formal_arg_list_size)
    return false;
  // compare return type
  auto actual_ret_type = ci.getType();
  auto formal_ret_type = f.getReturnType();
  if (!isTypeEqual(*actual_ret_type, *formal_ret_type))
    return false;

  for (unsigned i = 0; i < actual_arg_list_size; i++)
  {
    auto actual_arg = ci.getOperand(i);
    auto formal_arg = f.getArg(i);
    if (!isTypeEqual(*actual_arg->getType(), *formal_arg->getType()))
      return false;
  }
  return true;
}

bool pdg::PDGCallGraph::isTypeEqual(Type &t1, Type &t2)
{
  if (&t1 == &t2)
    return true;

  // need to compare name for sturct, due to llvm-link duplicate struct types
  if (!t1.isPointerTy() || !t2.isPointerTy())
    return false;

  auto t1_pointed_ty = t1.getPointerElementType();
  auto t2_pointed_ty = t2.getPointerElementType();

  if (!t1_pointed_ty->isStructTy() || !t2_pointed_ty->isStructTy())
    return false;

  auto t1_name = pdgutils::stripVersionTag(t1_pointed_ty->getStructName().str());
  auto t2_name = pdgutils::stripVersionTag(t2_pointed_ty->getStructName().str());

  return (t1_name == t2_name);
}

std::set<Function *> pdg::PDGCallGraph::getIndirectCallCandidates(CallInst &ci, Module &M)
{
  Type *call_func_ty = ci.getFunctionType();
  assert(call_func_ty != nullptr && "cannot find indirect call for null function type!\n");
  std::set<Function *> ind_call_cand;
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    if (isFuncSignatureMatch(ci, F))
    {
      // here we use some special hanlding.
      // if (isExportedFunc(F))
        ind_call_cand.insert(&F);
      // errs() << "ind call: " << ci << " | " << ci.getFunction()->getName() << "->" << F.getName() << "\n";
    }
  }
  return ind_call_cand;
}

bool pdg::PDGCallGraph::canReach(Node &src, Node &sink)
{
  std::queue<Node *> node_queue;
  std::unordered_set<Node *> seen_node;
  node_queue.push(&src);
  while (!node_queue.empty())
  {
    Node *n = node_queue.front();
    if (n == nullptr)
      continue;
    node_queue.pop();
    if (n == &sink)
      return true;
    if (seen_node.find(n) != seen_node.end())
      continue;
    seen_node.insert(n);

    for (auto out_neighbor : n->getOutNeighbors())
    {
      node_queue.push(out_neighbor);
    }
  }
  return false;
}

void pdg::PDGCallGraph::dump()
{
  for (auto pair : _val_node_map)
  {
    if (Function *f = dyn_cast<Function>(pair.first))
    {
      errs() << f->getName() << ": \n";
      for (auto out_node : pair.second->getOutNeighbors())
      {
        if (Function *callee = dyn_cast<Function>(out_node->getValue()))
          errs() << "\t\t" << callee->getName() << "\n";
      }
    }
  }
}

void pdg::PDGCallGraph::printPaths(Node &src, Node &sink)
{
  auto pathes = computePaths(src, sink);
  unsigned count = 1;
  for (auto path : pathes)
  {
    errs() << "************* Printing Pathes **************\n";
    errs() << "path len: " << path.size() << "\n";
    for (auto iter = path.begin(); iter != path.end(); iter++)
    {
      errs() << (*iter)->getName();
      if (std::next(iter, 1) != path.end())
        errs() << " -> ";
      else
        errs() << "\n\b";
    }
    errs() << "********************************************\n";
    count++;
  }
}

pdg::PDGCallGraph::PathVecs pdg::PDGCallGraph::computePaths(Node &src, Node &sink)
{
  PathVecs ret;
  std::unordered_set<Function *> visited_funcs;
  bool found_path = false;
  computePathsHelper(ret, src, sink, {}, visited_funcs, found_path); // just find one path
  return ret;
}

void pdg::PDGCallGraph::computePathsHelper(PathVecs &path_vecs, Node &src, Node &sink, std::vector<llvm::Function *> cur_path, std::unordered_set<llvm::Function *> visited_funcs, bool &found_path)
{
  if (found_path)
    return;
  assert(isa<Function>(src.getValue()) && "cannot process non function node (compute path, src)\n");
  assert(isa<Function>(sink.getValue()) && "cannot process non function node (compute path, sink)\n");
  Function *src_func = cast<Function>(src.getValue());
  Function *sink_func = cast<Function>(sink.getValue());
  if (visited_funcs.find(src_func) != visited_funcs.end())
    return;
  visited_funcs.insert(src_func);
  cur_path.push_back(src_func);
  if (src_func == sink_func)
  {
    path_vecs.push_back(cur_path);
    found_path = true;
    return;
  }

  for (auto out_neighbor : src.getOutNeighbors())
  {
    computePathsHelper(path_vecs, *out_neighbor, sink, cur_path, visited_funcs, found_path);
  }
}

// compute the functions that can be transitively reached from F through function calls
std::vector<pdg::Node *> pdg::PDGCallGraph::computeTransitiveClosure(pdg::Node &src)
{
  std::queue<Node *> node_queue;
  std::unordered_set<Node *> seen_node;
  std::vector<Node *> ret;
  node_queue.push(&src);
  while (!node_queue.empty())
  {
    Node *n = node_queue.front();
    node_queue.pop();
    if (seen_node.find(n) != seen_node.end())
      continue;
    seen_node.insert(n);
    ret.push_back(n);
    for (auto out_neighbor : n->getOutNeighbors())
    {
      auto val = out_neighbor->getValue();
      if (Function *f = dyn_cast<Function>(val))
      {
        // prune warning funcs in kernel
        if (isExcludeFunc(*f))
          continue;
        // prune all functions that don't have data flow reachable from shared fields

      }
      node_queue.push(out_neighbor);
    }
  }
  return ret;
}

void pdg::PDGCallGraph::setupExcludeFuncs()
{
  _exclude_func_names.insert("warn_slowpath_fmt");
  _exclude_func_names.insert("netdev_warn");
  _exclude_func_names.insert("netdev_err");
  _exclude_func_names.insert("netdev_info");
  _exclude_func_names.insert("dev_warn");
  _exclude_func_names.insert("dev_err");
  _exclude_func_names.insert("dev_info");
  _exclude_func_names.insert("kasprintf");
  _exclude_func_names.insert("kvasprintf");
  _exclude_func_names.insert("copy_user_overflow");
  _exclude_func_names.insert("rtnl_lock");
  _exclude_func_names.insert("rtnl_unlock");
}

void pdg::PDGCallGraph::setupExportedFuncs()
{
  std::ifstream ReadFile("exported_funcs");
  for (std::string line; std::getline(ReadFile, line);)
  {
    _exported_func_names.insert(line);
  }
}

void pdg::PDGCallGraph::setupDriverFuncs(Module &M)
{
  _driver_domain_funcs = pdgutils::readFuncsFromFile("driver_funcs", M);
}

bool pdg::PDGCallGraph::isExcludeFunc(Function &F)
{
  auto func_name = F.getName().str();
  func_name = pdgutils::stripFuncNameVersionNumber(func_name);
  return (_exclude_func_names.find(func_name) != _exclude_func_names.end());
}

bool pdg::PDGCallGraph::isExportedFunc(Function &F)
{
  auto func_name = F.getName().str();
  func_name = pdgutils::stripFuncNameVersionNumber(func_name);
  return (_exported_func_names.find(func_name) != _exported_func_names.end());
}

// speical handling for boundary functions
void pdg::PDGCallGraph::setupBoundaryFuncs(Module &M)
{
  auto imported_funcs = pdgutils::readFuncsFromFile("imported_funcs", M);
  auto exported_funcs = pdgutils::readFuncsFromFile("exported_funcs", M);

  if (EnableAnalysisStats)
  {
    auto &ksplit = KSplitStats::getInstance();
    ksplit.increaseKernelToDriverCallNum(exported_funcs.size());
    ksplit.increaseDriverToKernelCallNum(imported_funcs.size());
  }

  _boundary_funcs.insert(imported_funcs.begin(), imported_funcs.end());
  _boundary_funcs.insert(exported_funcs.begin(), exported_funcs.end());
  // module init functions
  Function *init_func = getModuleInitFunc(M);
  if (init_func != nullptr)
    _boundary_funcs.insert(init_func);
  // retrive all boundary func names

  for (auto f : _boundary_funcs)
  {
    auto func_name = f->getName().str();
    _boundary_func_names.insert(func_name);
  }
}

// void pdg::PDGCallGraph::initializeCommonCallFuncs(Function &boundary_func, std::set<Function *> &common_func)
// {
//   auto func_node = getNode(boundary_func);
//   assert(func_node != nullptr && "cannot get function node for computing transitive closure!");
//   auto trans_func_nodes = computeTransitiveClosure(*func_node);
//   for (Node *func_node : trans_func_nodes)
//   {
//     if (Function *trans_func = dyn_cast<Function>(func_node->getValue()))
//       common_func.insert(trans_func);
//   }
// }

void pdg::PDGCallGraph::collectDriverAccessedGlobalVars(Function &F)
{
  for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); ++inst_iter)
  {
    for (auto op : inst_iter->operand_values())
    {
      if (GlobalVariable *gv = dyn_cast<GlobalVariable>(op))
      {
        _taint_vals.insert(gv);
        // needed for generating projection for global variables
        _global_var_analysis.insert(gv);
      }
    }
  }
}

// void pdg::PDGCallGraph::computeBoundaryTransFuncs()
// {
//   // std::set<Function *> common_funcs;
//   // initializeCommonCallFuncs(**_boundary_funcs.begin(), common_funcs);

//   for (auto boundary_func : _boundary_funcs)
//   {
//     if (isExcludeFunc(*boundary_func))
//     {
//       errs() << "found exclude func " << boundary_func->getName() << "\n";
//       continue;
//     }
//     auto func_node = getNode(*boundary_func);
//     assert(func_node != nullptr && "cannot get function node for computing transitive closure!");
//     auto trans_func_nodes = computeTransitiveClosure(*func_node);
//     errs() << "transitive nodes for " << boundary_func->getName() << " - " << trans_func_nodes.size() << "\n";
//     for (auto n : trans_func_nodes)
//     {
//       if (Function *trans_func = dyn_cast<Function>(n->getValue()))
//       {
//         _boundary_trans_funcs.insert(trans_func);
//         // auto it = common_funcs.find(trans_func);
//         // if (it != common_funcs.end())
//         //   common_funcs.erase(it);
//         // collect global vars accessed in trans funcs
//         // collectAccessedGlobalVars(*trans_func);
//       }
//     }
//   }
// }

Function *pdg::PDGCallGraph::getModuleInitFunc(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    std::string func_name = F.getName().str();
    if (func_name.find("_init_module") != std::string::npos)
      return &F;
  }
  return nullptr;
}

unsigned pdg::PDGCallGraph::evaluateTransClosureSize(Function &F)
{
  std::set<Function*> seen_funcs;
  for (auto inst_iter = inst_begin(F); inst_iter != inst_end(F); ++inst_iter)
  {
    if (CallInst *ci = dyn_cast<CallInst>(&*inst_iter))
    {
      auto called_func = pdgutils::getCalledFunc(*ci);
      if (seen_funcs.find(called_func) != seen_funcs.end())
        continue;
      seen_funcs.insert(called_func);
    }
  }
  return seen_funcs.size();
}

void pdg::PDGCallGraph::computeTaintGlobals()
{
  for (auto driver_func : _driver_domain_funcs)
  {
    collectDriverAccessedGlobalVars(*driver_func);
  }
}

void pdg::PDGCallGraph::computeTaintFuncs(Module &M)
{
  for (auto taint_val : _taint_vals)
  {
    std::queue<Value*> val_q;
    std::set<Value*> seen_vals;
    val_q.push(taint_val);
    while (!val_q.empty())
    {
      Value *v = val_q.front();
      val_q.pop();
      // only consider pointer type value
      if (!v->getType()->isPointerTy())
        continue;
      for (auto user : v->users())
      {
        if (seen_vals.find(user) != seen_vals.end())
          continue;
        seen_vals.insert(user);
        if (isa<LoadInst>(user))
          val_q.push(user);
        else if (auto si = dyn_cast<StoreInst>(user))
          val_q.push(si->getPointerOperand());
        else if (isa<GetElementPtrInst>(user))
          val_q.push(user);
        else if (isa<BitCastInst>(user))
          val_q.push(user);
        // handle call instruction
        else if (CallInst *ci = dyn_cast<CallInst>(user))
        {
          // determine the arg idx
          unsigned arg_idx = 0;
          std::vector<Value *> arg_list;
          for (auto arg_iter = ci->arg_begin(); arg_iter != ci->arg_end(); arg_iter++)
          {
            arg_list.push_back(*arg_iter);
          }
          auto it = std::find(arg_list.begin(), arg_list.end(), v);
          if (it == arg_list.end())
            continue;
          arg_idx = std::distance(arg_list.begin(), it);
          // get the callsing function
          Function *calling_func = ci->getFunction();
          auto func_node = getNode(*calling_func);
          assert(func_node != nullptr && "cannot get function node for computing transitive closure!");
          // obtain all the possible callee (direct/indirect) to process
          auto callee = pdgutils::getCalledFunc(*ci);
          // prune warning funcs in kernel
          // case 1: direct call
          if (callee != nullptr)
          {
            if (callee->isDeclaration() || callee->isVarArg())
              continue;
            if (isExcludeFunc(*callee))
              continue;
            // push corresponding argument to the queue for later processing
            val_q.push(callee->getArg(arg_idx));
            // record the tainted function
            _taint_funcs.insert(callee);
          }
          else
          {
            auto ind_callees = getIndirectCallCandidates(*ci, M);
            for (auto ind_callee : ind_callees)
            {
              if (ind_callee->isDeclaration() || ind_callee->isVarArg())
                continue;
              if (isExcludeFunc(*ind_callee))
                continue;
              // push corresponding argument to the queue for later processing
              val_q.push(ind_callee->getArg(arg_idx));
              // record the tained function
              _taint_funcs.insert(ind_callee);
            }
          }
        }
      }
    }
  }
}