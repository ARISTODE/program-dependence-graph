#include "CallWrapper.hh"

using namespace llvm;

void pdg::CallWrapper::buildActualTreeForArgs(FunctionWrapper &callee_fw)
{
  Function* called_func = callee_fw.getFunc();
  // we don't handle varidic function at the moment
  if (called_func->isVarArg())
    return;
  // construct actual tree based on the type signature of callee
  Function *callingFunc = _call_inst->getFunction();
  auto formal_arg_list = callee_fw.getArgList();
  assert(_argList.size() == formal_arg_list.size() && "actual/formal arg size don't match!");
  // iterate through actual param list and construct actual tree by copying formal tree
  auto actual_arg_iter = _argList.begin();
  auto formal_arg_iter = formal_arg_list.begin();
  
  while (actual_arg_iter != _argList.end())
  {
    Tree* arg_formal_in_tree = callee_fw.getArgFormalInTree(**formal_arg_iter);
    if (!arg_formal_in_tree) {
      // in some case, not each parameter has tree, for example, a function with structure parameter
      actual_arg_iter++;
      formal_arg_iter++;
      continue;
    }
    // build actual in tree, copying the formal_in tree structure at the moment
    Tree* arg_actual_in_tree = new Tree(*arg_formal_in_tree);
    arg_actual_in_tree->setBaseVal(**actual_arg_iter);
    arg_actual_in_tree->setTreeNodeType(GraphNodeType::ACTUAL_IN);
    TreeNode* actual_in_root_node = arg_actual_in_tree->getRootNode();
    actual_in_root_node->addAddrVar(**actual_arg_iter);
    actual_in_root_node->setFunc(*callingFunc);
    arg_actual_in_tree->build();
    _arg_actual_in_tree_map.insert(std::make_pair(*actual_arg_iter, arg_actual_in_tree));
    // build actual out tree
    Tree* arg_actual_out_tree = new Tree(*arg_formal_in_tree);
    arg_actual_out_tree->setBaseVal(**actual_arg_iter);
    arg_actual_out_tree->setTreeNodeType(GraphNodeType::ACTUAL_OUT);
    TreeNode* actual_out_root_node = arg_actual_out_tree->getRootNode();
    actual_out_root_node->addAddrVar(**actual_arg_iter);
    actual_out_root_node->setFunc(*callingFunc);
    arg_actual_out_tree->build();
    _arg_actual_out_tree_map.insert(std::make_pair(*actual_arg_iter, arg_actual_out_tree));
    actual_arg_iter++;
    formal_arg_iter++;
  }
}

void pdg::CallWrapper::buildActualTreesForRetVal(FunctionWrapper &callee_fw)
{
  Tree *ret_formal_in_tree = callee_fw.getRetFormalInTree();
  if (!ret_formal_in_tree)
    return;
  // build actual in tree, copying the formal_in tree structure at the moment
  Tree *ret_actual_in_tree = new Tree(*ret_formal_in_tree);
  ret_actual_in_tree->setTreeNodeType(GraphNodeType::ACTUAL_IN);
  TreeNode *ret_actual_in_root_node = ret_actual_in_tree->getRootNode();
  ret_actual_in_root_node->addAddrVar(*_call_inst);
  ret_actual_in_tree->build();
  _ret_val_actual_in_tree = ret_actual_in_tree;

  // build actual out tree
  Tree *ret_actual_out_tree = new Tree(*ret_formal_in_tree);
  ret_actual_out_tree->setTreeNodeType(GraphNodeType::ACTUAL_OUT);
  TreeNode *ret_actual_out_root_node = ret_actual_out_tree->getRootNode();
  ret_actual_out_root_node->addAddrVar(*_call_inst);
  ret_actual_out_tree->build();
  _ret_val_actual_out_tree = ret_actual_out_tree;
}

pdg::Tree *pdg::CallWrapper::getArgActualInTree(Value &actual_arg)
{
  auto iter = _arg_actual_in_tree_map.find(&actual_arg);
  if (iter == _arg_actual_in_tree_map.end())
    return nullptr;
  return _arg_actual_in_tree_map[&actual_arg];
}

pdg::Tree *pdg::CallWrapper::getArgActualOutTree(Value &actual_arg)
{
  auto iter = _arg_actual_out_tree_map.find(&actual_arg);
  if (iter == _arg_actual_out_tree_map.end())
    return nullptr;
  return _arg_actual_out_tree_map[&actual_arg];
}

int pdg::CallWrapper::getArgIdxByVal(Value& val)
{
  auto it = std::find(_argList.begin(), _argList.end(), &val);
  if (it == _argList.end())
    return -1;
  return std::distance(_argList.begin(), it);
}
