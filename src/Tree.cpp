#include "Tree.hh"

using namespace llvm;

pdg::TreeNode::TreeNode(const TreeNode &treeNode) : Node(treeNode.getNodeType())
{
  _func = treeNode.getFunc();
  _nodeDt = treeNode.getDIType();
  _node_type = treeNode.getNodeType();
}

pdg::TreeNode::TreeNode(DIType *di_type, int depth, TreeNode *parentNode, Tree *tree, GraphNodeType nodeTy) : Node(nodeTy)
{
  _nodeDt = di_type;
  _depth = depth;
  _parentNode = parentNode;
  _tree = tree;
  if (parentNode != nullptr)
    _func = parentNode->getFunc();
}

pdg::TreeNode::TreeNode(Function &f, DIType *di_type, int depth, TreeNode *parentNode, Tree *tree, GraphNodeType nodeTy) : Node(nodeTy)
{
  _nodeDt = di_type;
  _depth = depth;
  _parentNode = parentNode;
  _tree = tree;
  _func = &f;
}

int pdg::TreeNode::expandNode()
{
  // expand debugging information here
  if (_nodeDt == nullptr)
    return 0;

  // if the current node has tag MEMBER, then this is a struct field.
  // construct a node representing the address of this field
  if (isStructMember())
  {
    // skip attributes tags, e.g., const
    DIType *fieldDt = dbgutils::stripMemberTag(*_nodeDt);
    fieldDt = dbgutils::stripAttributes(*fieldDt);
    TreeNode *newChildNode = new TreeNode(*_func, fieldDt, _depth + 1, this, _tree, getNodeType());
    newChildNode->computeDerivedAddrVarsFromParent();
    _children.push_back(newChildNode);
    this->addNeighbor(*newChildNode, EdgeType::PARAMETER_FIELD);
    return 1;
  }

  // if the current node is not of pointer type of any projectable type, it must be either primitive type
  // or array. There is no need to go further because there is no base type.
  // if (!dbgutils::isPointerType(*dt) && !dbgutils::isProjectableType(*dt))
  //   return 0;

  // for pointer type, build a child node, connect the chlid node with parent node
  if (dbgutils::isPointerType(*_nodeDt))
  {
    DIType *pointedObjTy = dbgutils::getLowestDIType(*_nodeDt);
    TreeNode *newChildNode = new TreeNode(*_func, pointedObjTy, _depth + 1, this, _tree, getNodeType());
    newChildNode->computeDerivedAddrVarsFromParent();
    _children.push_back(newChildNode);
    this->addNeighbor(*newChildNode, EdgeType::PARAMETER_FIELD);
    return 1;
  }
  // TODO: should change to aggregate type later
  // for aggregate types, connect all the fields node with the parent struct node
  if (dbgutils::isProjectableType(*_nodeDt))
  {
    auto DINodeArr = dyn_cast<DICompositeType>(_nodeDt)->getElements();
    for (unsigned i = 0; i < DINodeArr.size(); i++)
    {
      DIType *fieldDt = dyn_cast<DIType>(DINodeArr[i]);
      TreeNode *newChildNode = new TreeNode(*_func, fieldDt, _depth + 1, this, _tree, getNodeType());
      newChildNode->computeDerivedAddrVarsFromParent();
      _children.push_back(newChildNode);
      this->addNeighbor(*newChildNode, EdgeType::PARAMETER_FIELD);
    }
    return DINodeArr.size();
  }
  return 0;
}

void pdg::TreeNode::computeDerivedAddrVarsFromParent()
{
  if (!_parentNode)
    return;
  if (!_nodeDt)
    return;
  std::unordered_set<llvm::Value *> baseNodeAddrVars;
  // handle struct pointer
  // if root node is pointer, the fields addresses are computed directly from the root node' addr vars
  auto grandParentNode = _parentNode->getParentNode();
  // hanlde struct specifically, because field's address could be computed from the base pointer, which is
  if (grandParentNode != nullptr && dbgutils::isStructType(*_parentNode->getDIType()) && dbgutils::isStructPointerType(*grandParentNode->getDIType()))
    baseNodeAddrVars = grandParentNode->getAddrVars();
  else
    baseNodeAddrVars = _parentNode->getAddrVars();

  for (auto baseNodeAddrVar : baseNodeAddrVars)
  {
    if (baseNodeAddrVar == nullptr)
      continue;
    for (auto user : baseNodeAddrVar->users())
    {
      // handle load instruction, field should not inherit the load inst from the sturct pointer.
      if (LoadInst *li = dyn_cast<LoadInst>(user))
      {
        if (baseNodeAddrVars.find(li) == baseNodeAddrVars.end())
          _addrVars.insert(li);
      }
      // handle gep instruction
      if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(user))
      {
        if (pdgutils::isGEPOffsetMatchDIOffset(*_nodeDt, *gep))
          _addrVars.insert(gep);
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
  _rootNode = new_root_node;
  _size = 0;
}

void pdg::Tree::print()
{
  if (getFunc())
    errs() << "func: " << getFunc()->getName() << "\n";
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(_rootNode);
  while (!nodeQueue.empty())
  {
    int queue_size = nodeQueue.size();
    while (queue_size > 0)
    {
      TreeNode *currentNode = nodeQueue.front();
      nodeQueue.pop();
      queue_size--;
      if (currentNode->getDIType() != nullptr)
        errs() << currentNode->getTypeName() << " - " << currentNode->getSrcHierarchyName(false) << "(" << currentNode->getAddrVars().size() << ")"
               << ", ";
      for (auto addrVar : currentNode->getAddrVars())
        errs() << "\t" << *addrVar << "\n";
      for (auto child : currentNode->getChildNodes())
      {
        nodeQueue.push(child);
      }
    }
    errs() << "\n";
  }
}

void pdg::Tree::build(int maxTreeDepth)
{
  int current_tree_depth = 0;
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(_rootNode);
  while (!nodeQueue.empty()) // have more child to expand
  {
    current_tree_depth++;
    if (current_tree_depth > maxTreeDepth)
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
        for (auto childNode : currentNode->getChildNodes())
        {
          nodeQueue.push(childNode);
        }
      }
    }
  }
}

void pdg::Tree::addAccessForAllNodes(AccessTag accTag)
{
  std::queue<TreeNode *> nodeQueue;
  nodeQueue.push(_rootNode);
  while (!nodeQueue.empty()) // have more child to expand
  {
    auto currentNode = nodeQueue.front();
    nodeQueue.pop();
    currentNode->addAccessTag(accTag);
    for (auto childNode : currentNode->getChildNodes())
    {
      nodeQueue.push(childNode);
    }
  }
}

bool pdg::TreeNode::isStructMember()
{
  if (_nodeDt != nullptr)
    return (_nodeDt->getTag() == llvm::dwarf::DW_TAG_member);
  return false;
}

bool pdg::TreeNode::isStructField()
{
  if (_nodeDt != nullptr)
  {
    auto dt = dbgutils::stripAttributes(*_nodeDt);
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