#include "Tree.hh"
#include "Graph.hh"

using namespace llvm;

pdg::TreeNode::TreeNode(const TreeNode &treeNode) : Node(treeNode.getNodeType())
{
  _func = treeNode.getFunc();
  _nodeDt = treeNode.getDIType();
  _nodeType = treeNode.getNodeType();
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

/*
This function calculates the IR variables representing the abstract address for a tree node.
There are generally two cases:
1. When the parent node is a pointer, the child's address variables should consist of the load instructions
  (and their aliases) that load from the parent pointer. These instructions represent the address of the pointed object.
2. When the parent node is an object, such as a struct, the child node should represent each field address.
   In this case, we need to identify the GetElementPtr (GEP) instructions that compute the field address and
   consider these instructions as the abstract address representation of the tree node.
*/

void pdg::TreeNode::computeDerivedAddrVarsFromParent()
{
  if (!_parentNode || !_nodeDt)
    return;

  auto &programGraph = ProgramGraph::getInstance();
  auto parentAddrVars = _parentNode->getAddrVars();

  auto handleLoadInst = [&](Value *user)
  {
    if (!isa<LoadInst>(user))
      return;
      
    if (parentAddrVars.find(user) == parentAddrVars.end())
    {
      // _addrVars.insert(user);
      auto instNode = programGraph.getNode(*user);

      if (!instNode)
        return;

      auto aliasNodes = programGraph.findNodesReachedByEdge(*instNode, EdgeType::DATA_ALIAS);
      for (auto aliasNode : aliasNodes)
      {
        auto aliasVar = aliasNode->getValue();
        // if (aliasVar && isa<LoadInst>(aliasVar) && parentAddrVars.find(aliasVar) == parentAddrVars.end())
        if (aliasVar && isa<LoadInst>(aliasVar) && aliasVar->getType() == user->getType())
          _addrVars.insert(aliasVar);
      }
    }
  };

  auto handleGEPInst = [&](Value *user)
  {
    if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(user))
    {
      if (pdgutils::isGEPOffsetMatchDIOffset(*_nodeDt, *gep))
      {
        _addrVars.insert(gep);

        auto instNode = programGraph.getNode(*gep);
        auto aliasNodes = programGraph.findNodesReachedByEdge(*instNode, EdgeType::DATA_ALIAS);

        for (auto aliasNode : aliasNodes)
        {
          auto aliasVar = aliasNode->getValue();
          // if (aliasVar && parentAddrVars.find(aliasVar) == parentAddrVars.end())
          if (GetElementPtrInst *aliasGep = dyn_cast<GetElementPtrInst>(aliasVar))
          {
            if (pdgutils::isGEPOffsetMatchDIOffset(*_nodeDt, *aliasGep))
            {
              _addrVars.insert(aliasVar);
            }
          }
        }
      }
    }
  };

  // a field's address can be computed using gep, using the pointer to the object as the base address
  // but the parent node is the object, so need to consider the top pointer's addr vars when identifying gep
  std::unordered_set<Value *> baseAddrVars = _parentNode->getAddrVars();
  if (this->isStructMember())
  {
    auto topPointerNode = _parentNode->getParentNode();
    if (topPointerNode)
    {
      // use the top pointer as the base variable to compute geps
      auto topPointerAddrVars = topPointerNode->getAddrVars();
      baseAddrVars = topPointerAddrVars;
    }
  }

  for (auto addrVar : baseAddrVars)
  {
    for (auto user : addrVar->users())
    {
      if (isa<LoadInst>(user))
      {
        handleLoadInst(user);
      }
      else
      {
        handleGEPInst(user);
      }
    }
  }
}

void pdg::TreeNode::dump()
{
  errs() << _depth << " - " << static_cast<int>(_nodeType) << "\n";
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
  while (!nodeQueue.empty() && current_tree_depth < maxTreeDepth)
  {
    current_tree_depth++;
    int queue_size = nodeQueue.size();

    for (int i = 0; i < queue_size; i++)
    {
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

bool pdg::TreeNode::isSharedLockField()
{
  auto fieldTypeName = getTypeName();

  // must be mutex or spin lock type
  bool isSpinLockType = fieldTypeName.find("spinlock") != std::string::npos;
  bool isMutexType = fieldTypeName.find("mutex") != std::string::npos;
  if (!isSpinLockType && !isMutexType)
  {
    return false;
  }
  return true;

  // auto &progGraph = ProgramGraph::getInstance();
  // for (auto addrVar : _addrVars)
  // {
  //   auto addrVarNode = progGraph.getNode(*addrVar);
  //   auto aliasNodes = progGraph.findNodesReachedByEdge(*addrVarNode, EdgeType::DATA_ALIAS);
  //   aliasNodes.insert(addrVarNode);
  //   for (auto aliasNode : aliasNodes)
  //   {
  //     auto aliasVal = aliasNode->getValue();
  //     if (!aliasVal)
  //       continue;
  //     // check two-levels of def-use chain, determine if the lock is used in lock/unlock calls
  //     for (auto user : aliasVal->users())
  //     {
  //       for (auto secLevelUser : user->users())
  //       {
  //         for (auto u : secLevelUser->users())
  //         {
  //           if (CallInst *callInst = dyn_cast<CallInst>(u))
  //           {
  //             Function *calledFunc = callInst->getCalledFunction();
  //             if (calledFunc)
  //             {
  //               StringRef funcName = calledFunc->getName();
  //               if (funcName == "_raw_spin_lock" || funcName == "_raw_spin_unlock" ||
  //                   funcName == "mutex_lock" || funcName == "mutex_unlock")
  //                 return true;
  //             }
  //           }
  //         }
  //       }
  //     }
  //   }
  // }
  // return false;
}

std::string pdg::TreeNode::getSrcName()
{
  if (_di_local_var)
    return _di_local_var->getName().str();
  if (getDIType())
    return dbgutils::getSourceLevelVariableName(*getDIType());
  return "";
}

std::string pdg::TreeNode::getTypeName(bool isRaw)
{
  if (getDIType())
    return dbgutils::getSourceLevelTypeName(*getDIType(), isRaw);
  return "";
}

std::string pdg::TreeNode::getSrcHierarchyName(bool hideStructTypeName, bool ignoreRootParamName)
{
  if (!srcHierarchyName.empty())
    return srcHierarchyName;

  std::string retStr = "";
  TreeNode *curNode = this;
  while (curNode)
  {
    if (hideStructTypeName && curNode->getDIType() && dbgutils::isCompositeType(*curNode->getDIType()))
    {
      curNode = curNode->getParentNode();
      continue;
    }
    
    // anonymous struct/union may have empty src name
    if (!curNode->getSrcName().empty() && curNode->isStructMember())
      retStr = "->" + curNode->getSrcName() + retStr;

    if (curNode->isRootNode())
    {
        if (!ignoreRootParamName)
          retStr = curNode->getSrcName() + retStr;
    }
    curNode = curNode->getParentNode();
  }

  srcHierarchyName = retStr;
  return srcHierarchyName;
}

pdg::TreeNode *pdg::TreeNode::getStructObjNode()
{
  if (_nodeDt && dbgutils::isStructPointerType(*_nodeDt))
  {
    return getChildNodes()[0];
  }
  return nullptr;
}