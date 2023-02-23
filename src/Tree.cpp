#include "Tree.hh"

using namespace llvm;

pdg::TreeNode::TreeNode(const TreeNode &treeNode) : Node(treeNode.getNodeType())
{
  _func = treeNode.getFunc();
  _node_di_type = treeNode.getDIType();
  _node_type = treeNode.getNodeType();
}

pdg::TreeNode::TreeNode(DIType *di_type, int depth, TreeNode *parentNode, Tree *tree, GraphNodeType node_type) : Node(node_type)
{
  _node_di_type = di_type;
  _depth = depth;
  _parent_node = parentNode;
  _tree = tree;
  if (parentNode != nullptr)
    _func = parentNode->getFunc();
}

pdg::TreeNode::TreeNode(Function &f, DIType *di_type, int depth, TreeNode *parentNode, Tree *tree, GraphNodeType node_type) : Node(node_type)
{
  _node_di_type = di_type;
  _depth = depth;
  _parent_node = parentNode;
  _tree = tree;
  _func = &f;
}

int pdg::TreeNode::expandNode()
{
  // expand debugging information here
  if (_node_di_type == nullptr)
    return 0;
  DIType* dt = dbgutils::stripMemberTag(*_node_di_type);
  dt = dbgutils::stripAttributes(*dt);

  // iterate through all the child nodes, build a tree node for each of them.
  if (!dbgutils::isPointerType(*dt) && !dbgutils::isProjectableType(*dt))
    return 0;

  // for pointer type, build a child node, connect the chlid node with parent node
  if (dbgutils::isPointerType(*dt))
  {
    DIType* pointed_obj_dt = dbgutils::getLowestDIType(*dt);
    TreeNode *new_child_node = new TreeNode(*_func, pointed_obj_dt, _depth + 1, this, _tree, getNodeType());
    new_child_node->computeDerivedAddrVarsFromParent();
    _children.push_back(new_child_node);
    this->addNeighbor(*new_child_node, EdgeType::PARAMETER_FIELD);
    return 1;
  }
  // TODO: should change to aggregate type later
  // for aggregate types, connect all the fields node with the parent struct node
  if (dbgutils::isProjectableType(*dt))
  {
    auto di_node_arr = dyn_cast<DICompositeType>(dt)->getElements();
    for (unsigned i = 0; i < di_node_arr.size(); i++)
    {
      DIType *field_di_type = dyn_cast<DIType>(di_node_arr[i]);
      TreeNode *new_child_node = new TreeNode(*_func, field_di_type, _depth + 1, this, _tree, getNodeType());
      new_child_node->computeDerivedAddrVarsFromParent();
      _children.push_back(new_child_node);
      this->addNeighbor(*new_child_node, EdgeType::PARAMETER_FIELD);
    }
    return di_node_arr.size();
  }

  return 0;
}

void pdg::TreeNode::computeDerivedAddrVarsFromParent()
{
  if (!_parent_node)
    return;
  if (!_node_di_type)
    return;
  std::unordered_set<llvm::Value *> base_node_addr_vars;
  // handle struct pointer
  auto grand_parent_node = _parent_node->getParentNode();
  // TODO: now hanlde struct specifically, but should also verify on other aggregate pointer types
  if (grand_parent_node != nullptr && dbgutils::isStructType(*_parent_node->getDIType()) && dbgutils::isStructPointerType(*grand_parent_node->getDIType()))
  {
    base_node_addr_vars = grand_parent_node->getAddrVars();
  }
  else
    base_node_addr_vars = _parent_node->getAddrVars();

  bool is_struct_field = false;
  if (dbgutils::isStructType(*_parent_node->getDIType()))
    is_struct_field = true;

  for (auto base_node_addr_var : base_node_addr_vars)
  {
    if (base_node_addr_var == nullptr)
      continue;
    for (auto user : base_node_addr_var->users())
    {
      // handle load instruction, field should not inherit the load inst from the sturct pointer.
      if (LoadInst *li = dyn_cast<LoadInst>(user))
      {
        if (!is_struct_field)
          _addr_vars.insert(li);
      }
      // handle gep instruction
      if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(user))
      {
        if (pdgutils::isGEPOffsetMatchDIOffset(*_node_di_type, *gep))
          _addr_vars.insert(gep);
      }
    }
  }
}

void pdg::TreeNode::dump()
{
  errs() << _depth << " - " << static_cast<int>(_node_type) << "\n";
}

//  ====== Tree =======
pdg::Tree::Tree(const Tree &src_tree)
{
  TreeNode *src_tree_root_node = src_tree.getRootNode();
  TreeNode *new_root_node = new TreeNode(*src_tree_root_node);
  _root_node = new_root_node;
  _size = 0;
}

void pdg::Tree::print()
{
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(_root_node);
  while (!nodeQueue.empty())
  {
    int queue_size = nodeQueue.size();
    while (queue_size > 0)
    {
      TreeNode *currentNode = nodeQueue.front();
      nodeQueue.pop();
      queue_size--;
      if (currentNode == _root_node)
        errs() << dbgutils::getSourceLevelVariableName(*currentNode->getDILocalVar()) << ", ";
      else
      {
        if (currentNode->getDIType() != nullptr)
          errs() << dbgutils::getSourceLevelVariableName(*currentNode->getDIType()) << "(" << currentNode->getAddrVars().size() << ")"
                 << ", ";
      }
      for (auto child : currentNode->getChildNodes())
      {
        nodeQueue.push(child);
      }
    }
    errs() << "\n";
  }
}

void pdg::Tree::build(int max_tree_depth)
{
  int current_tree_depth = 0;
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(_root_node);
  while (!nodeQueue.empty()) // have more child to expand
  {
    current_tree_depth++;
    if (current_tree_depth > max_tree_depth)
      break;
    int queue_size = nodeQueue.size();
    while (queue_size > 0)
    {
      queue_size--;
      TreeNode *currentNode = nodeQueue.front();
      nodeQueue.pop();
      _size++;
      if (currentNode->expandNode() > 0)
      {
        for (auto child_node : currentNode->getChildNodes())
        {
          nodeQueue.push(child_node);
        }
      }
    }
  }
}

void pdg::Tree::addAccessForAllNodes(AccessTag acc_tag)
{
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(_root_node);
  while (!nodeQueue.empty()) // have more child to expand
  {
    auto currentNode = nodeQueue.front();
    nodeQueue.pop();
    currentNode->addAccessTag(acc_tag);
    for (auto child_node : currentNode->getChildNodes())
    {
      nodeQueue.push(child_node);
    }
  }
}

bool pdg::TreeNode::isStructMember()
{
  if (_node_di_type != nullptr)
    return (_node_di_type->getTag() == llvm::dwarf::DW_TAG_member);
  return false;
}

bool pdg::TreeNode::isStructField()
{
  if (_node_di_type != nullptr)
  {
    auto dt = dbgutils::stripAttributes(*_node_di_type);
    return (dt->getTag() == llvm::dwarf::DW_TAG_member);
  }
  return false;
}

std::string pdg::TreeNode::getSrcName()
{
  if (_di_local_var)
    return _di_local_var->getName().str();
  if (getDIType())
    return dbgutils::getSourceLevelVariableName(*getDIType());
  return "";
}

std::string pdg::TreeNode::getTypeName()
{
  if (getDIType()) 
    return dbgutils::getSourceLevelTypeName(*getDIType());
  return "";
}

std::string pdg::TreeNode::getSrcHierarchyName(bool hideStructTypeName)
{
  std::string retStr = "";
  auto curNode = this;
  while (curNode)
  {
    if (hideStructTypeName && curNode->getDIType() && dbgutils::isCompositeType(*curNode->getDIType()))
    {
      curNode = curNode->getParentNode();
      continue;
    }

    if (!curNode->getSrcName().empty())
      retStr = curNode->getSrcName() + retStr;
    curNode = curNode->getParentNode();
    // add -> to indicate the fields
    if (curNode)
      retStr = "->" + retStr;
  }
  return retStr;
}