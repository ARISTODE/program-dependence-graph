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
      TreeNode(llvm::Value &val, GraphNodeType node_type) : Node(val, node_type) {};
      TreeNode(const TreeNode& tree_node); 
      TreeNode(llvm::DIType *di_type, int depth, TreeNode* parent_node, Tree* tree, GraphNodeType node_type);
      TreeNode(llvm::Function &f, llvm::DIType *di_type, int depth, TreeNode* parent_node, Tree* tree, GraphNodeType node_type);
      int expandNode(); // build child nodes and connect with them
      llvm::DILocalVariable *getDILocalVar() { return _di_local_var; }
      void insertChildNode(TreeNode *new_child_node) { _children.push_back(new_child_node); }
      void setParentTreeNode(TreeNode *parent_node) { _parent_node = parent_node; }
      void setDILocalVariable(llvm::DILocalVariable &di_local_var) { _di_local_var = &di_local_var; }
      void addAddrVar(llvm::Value &v) { _addr_vars.insert(&v); }
      void setCanOptOut(bool can_opt_out) { _can_opt_out = can_opt_out; }
      bool getCanOptOut() { return _can_opt_out; }
      std::vector<TreeNode *> &getChildNodes() { return _children; }
      std::unordered_set<llvm::Value *> &getAddrVars() { return _addr_vars; }
      void computeDerivedAddrVarsFromParent();
      TreeNode *getParentNode() { return _parent_node; }
      Tree *getTree() { return _tree; }
      int getDepth() { return _depth; }
      void addAccessTag(AccessTag acc_tag) { _acc_tag_set.insert(acc_tag); }
      std::set<AccessTag> &getAccessTags() { return _acc_tag_set; }
      bool isRootNode() {return _parent_node == nullptr;}
      int numOfChild() { return _children.size(); }
      bool hasReadAccess() { return _acc_tag_set.find(AccessTag::DATA_READ) != _acc_tag_set.end(); }
      bool hasWriteAccess() { return _acc_tag_set.find(AccessTag::DATA_WRITE) != _acc_tag_set.end(); }
      void setAccessInAtomicRegion() { _is_accessed_in_atomic_region = true; }
      bool isAccessedInAtomicRegion() { return _is_accessed_in_atomic_region; }
      void setAllocStr(std::string str) { _alloc_str = str; }
      std::string getAllocStr() { return _alloc_str; }
      void setDeallocStr(std::string str) { _dealloc_str = str; }
      std::string getDeallocStr() { return _dealloc_str; }
      void dump() override;

    private:
      Tree *_tree = nullptr;
      TreeNode *_parent_node = nullptr;
      int _depth = 0;
      llvm::DILocalVariable *_di_local_var = nullptr;
      std::vector<TreeNode *> _children;
      std::unordered_set<llvm::Value *> _addr_vars;
      std::set<AccessTag> _acc_tag_set;
      bool _is_accessed_in_atomic_region = false;
      bool _can_opt_out = false;
      std::string _alloc_str;
      std::string _dealloc_str;
  };

  class Tree
  {
  public:
    Tree() = default;
    Tree(llvm::Value &v) { _base_val = &v; }
    Tree(const Tree &src_tree);
    void setRootNode(TreeNode &root_node) { _root_node = &root_node; }
    void setTreeNodeType(GraphNodeType node_type) { _root_node->setNodeType(node_type); }
    TreeNode *getRootNode() const { return _root_node; }
    int size() { return _size; }
    void setSize(int size) { _size = size; }
    void increaseTreeSize() { _size++; }
    void print();
    void build(int max_tree_depth = 6);
    llvm::Value *getBaseVal() { return _base_val; }
    void setBaseVal(llvm::Value &v) { _base_val = &v; }
    llvm::Function *getFunc() { return (_root_node == nullptr ? nullptr : _root_node->getFunc()); }

  private:
    llvm::Value *_base_val;
    TreeNode *_root_node;
    int _size;
  };
} // namespace pdg

#endif