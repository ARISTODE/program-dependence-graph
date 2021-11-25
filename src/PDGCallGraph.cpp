#include "PDGCallGraph.hh"

using namespace llvm;

void pdg::PDGCallGraph::build(Module &M)
{
  setupExcludeFuncs();
  setupExportedFuncs();

  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    Node *n = new Node(F, GraphNodeType::FUNC);
    _val_node_map.insert(std::make_pair(&F, n));
    addNode(*n);
  }

  // connect nodes
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    auto caller_node = getNode(F);
    for (auto inst_i = inst_begin(F); inst_i != inst_end(F); inst_i++)
    {
      if (CallInst *ci = dyn_cast<CallInst>(&*inst_i))
      {
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

  // check the calls from interface functions
  setupBoundaryFuncs(M);
  auto boundary_trans_funcs = computeBoundaryTransitiveClosure();
  errs() << "finish building call graph\n";
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
      if (isExportedFunc(F))
        ind_call_cand.insert(&F);
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
      // prune warning funcs in kernel
      auto val = out_neighbor->getValue();
      if (Function *f = dyn_cast<Function>(val))
      {
        if (isExcludeFunc(*f))
          continue;
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
}

void pdg::PDGCallGraph::setupExportedFuncs()
{
  std::ifstream ReadFile("exported_funcs");
  for (std::string line; std::getline(ReadFile, line);)
  {
    _exported_func_names.insert(line);
  }
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

void pdg::PDGCallGraph::initializeCommonCallFuncs(Function &boundary_func, std::set<Function *> &common_func)
{
  auto func_node = getNode(boundary_func);
  assert(func_node != nullptr && "cannot get function node for computing transitive closure!");
  auto trans_func_nodes = computeTransitiveClosure(*func_node);
  for (Node *func_node : trans_func_nodes)
  {
    if (Function *trans_func = dyn_cast<Function>(func_node->getValue()))
      common_func.insert(trans_func);
  }
}

std::set<Function *> pdg::PDGCallGraph::computeBoundaryTransitiveClosure()
{
  std::set<Function *> boundary_trans_funcs;
  std::set<Function *> common_funcs;

  initializeCommonCallFuncs(**_boundary_funcs.begin(), common_funcs);

  for (auto boundary_func : _boundary_funcs)
  {
    if (isExcludeFunc(*boundary_func))
    {
      errs() << "found exclude func " << boundary_func->getName() << "\n";
      continue;
    }
    auto func_node = getNode(*boundary_func);
    assert(func_node != nullptr && "cannot get function node for computing transitive closure!");
    auto trans_func_nodes = computeTransitiveClosure(*func_node);
    errs() << "transitive nodes for " << boundary_func->getName() << " - " << trans_func_nodes.size() << "\n";
    for (auto n : trans_func_nodes)
    {
      if (Function *trans_func = dyn_cast<Function>(n->getValue()))
      {
        boundary_trans_funcs.insert(trans_func);
        auto it = common_funcs.find(trans_func);
        if (it != common_funcs.end())
          common_funcs.erase(it);
      }
    }
  }
  for (auto common_func : common_funcs)
  {
    errs() << "common func: " << common_func->getName() << "\n";
  }
  return boundary_trans_funcs;
}

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
