#include "CallWrapper.hh"

void pdg::CallWrapper::buildActualTreeForArgs(FunctionWrapper* fw)
{
  auto formal_arg_list = fw->getArgList();
  assert(_arg_list.size() == formal_arg_list.size() && "actual/formal arg size don't match!");
  auto actual_arg_iter = _arg_list.begin();
  auto formal_arg_iter = formal_arg_list.begin();
  while (actual_arg_iter != _arg_list.end())
  {
    // Tree* formal_tree = fw->getTreeByArg(formal_arg_iter);
    // Tree* actual_tree = new Tree(*formal_tree);
    // _arg_actual_tree_map.insert(std::make_pair(*actual_arg_iter, actual_tree));
    // actual_arg_iter++;
    // formal_arg_iter++;
  }
}
