#ifndef TREE_H_
#define TREE_H_
#include "LLVMEssentials.hh"
#include "DebugInfoUtils.hh"
#include "PDGNode.hh"
#include "PDGEnums.hh"
#include "PDGUtils.hh"
#include <set>

namespace pdg
{
  class Tree;
  class TreeNode : public Node
  {
    public:
      TreeNode(llvm::Value &val, GraphNodeType nodeTy) : Node(val, nodeTy) {};
      TreeNode(const TreeNode& treeNode); 
      TreeNode(llvm::DIType *di_type, int depth, TreeNode* parentNode, Tree* tree, GraphNodeType nodeTy);
      TreeNode(llvm::Function &f, llvm::DIType *di_type, int depth, TreeNode* parentNode, Tree* tree, GraphNodeType nodeTy);
      int expandNode(); // build child nodes and connect with them
      llvm::DILocalVariable *getDILocalVar() { return _di_local_var; }
      void insertChildNode(TreeNode *new_child_node) { _children.push_back(new_child_node); }
      void setParentTreeNode(TreeNode *parentNode) { _parentNode = parentNode; }
      void setDILocalVariable(llvm::DILocalVariable &di_local_var) { _di_local_var = &di_local_var; }
      void addAddrVar(llvm::Value &v) { _addrVars.insert(&v); }
      void setCanOptOut(bool can_opt_out) { _can_opt_out = can_opt_out; }
      bool getCanOptOut() { return _can_opt_out; }
      std::vector<TreeNode *> &getChildNodes() { return _children; }
      std::unordered_set<llvm::Value *> &getAddrVars() { return _addrVars; }
      void computeDerivedAddrVarsFromParent();
      TreeNode *getParentNode() { return _parentNode; }
      Tree *getTree() { return _tree; }
      int getDepth() { return _depth; }
      void addAccessTag(AccessTag accTag) { _acc_tag_set.insert(accTag); }
      std::set<AccessTag> &getAccessTags() { return _acc_tag_set; }
      bool isRootNode() {return _parentNode == nullptr;}
      bool isStructMember();
      bool isStructField();
      int numOfChild() { return _children.size(); }
      bool hasReadAccess() { return _acc_tag_set.find(AccessTag::DATA_READ) != _acc_tag_set.end(); }
      bool hasWriteAccess() { return _acc_tag_set.find(AccessTag::DATA_WRITE) != _acc_tag_set.end(); }
      bool hasAccess() { return (_acc_tag_set.size() != 0); }
      void setAccessInAtomicRegion() { _is_accessed_in_atomic_region = true; }
      bool isAccessedInAtomicRegion() { return _is_accessed_in_atomic_region; }
      void setAllocStr(std::string str) { _alloc_str = str; }
      std::string getAllocStr() { return _alloc_str; }
      void setDeallocStr(std::string str) { _dealloc_str = str; }
      std::string getDeallocStr() { return _dealloc_str; }
      bool isSeqPtr() { return is_seq_ptr; }
      void setSeqPtr() { is_seq_ptr = true; }
      void dump() override;
      std::string getSrcName();
      std::string getTypeName();
      std::string getSrcHierarchyName(bool hideStructTypeName = true); // obj->field->field
      // used for collecting ksplit stats
    public:
      bool isShared = false;
      bool is_ioremap = false;
      bool isUser = false;
      bool is_sentinel = false;
      bool isString = false;
      bool is_seq_ptr = false;
      std::set<std::string> annotations;

    private:
      Tree *_tree = nullptr;
      TreeNode *_parentNode = nullptr;
      int _depth = 0;
      llvm::DILocalVariable *_di_local_var = nullptr;
      std::vector<TreeNode *> _children;
      std::unordered_set<llvm::Value *> _addrVars;
      std::set<AccessTag> _acc_tag_set;
      bool _is_accessed_in_atomic_region = false;
      bool _can_opt_out = false;
      // FIXME: outdated
      std::string _alloc_str;
      std::string _dealloc_str;
  };

  class Tree
  {
  public:
    Tree() = default;
    Tree(llvm::Value &v) { _baseVal = &v; }
    Tree(const Tree &src_tree);
    void setRootNode(TreeNode &rootNode) { _rootNode = &rootNode; }
    void setTreeNodeType(GraphNodeType nodeTy) { _rootNode->setNodeType(nodeTy); }
    TreeNode *getRootNode() const { return _rootNode; }
    int size() { return _size; }
    void setSize(int size) { _size = size; }
    void increaseTreeSize() { _size++; }
    void print();
    void build(int maxTreeDepth = 6);
    llvm::Value *getBaseVal() { return _baseVal; }
    void setBaseVal(llvm::Value &v) { _baseVal = &v; }
    llvm::Function *getFunc() { return (_rootNode == nullptr ? nullptr : _rootNode->getFunc()); }
    void addAccessForAllNodes(AccessTag accTag);

  private:
    llvm::Value *_baseVal;
    TreeNode *_rootNode;
    int _size;
  };
} // namespace pdg

#endif