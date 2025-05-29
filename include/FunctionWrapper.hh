#ifndef FUNCTIONWRAPPER_H_
#define FUNCTIONWRAPPER_H_
#include "LLVMEssentials.hh"
#include "Tree.hh"
#include "PDGUtils.hh"
#include <map>
#include <vector>

namespace pdg
{
  class FunctionWrapper
  {
  public:
    FunctionWrapper(llvm::Function *func)
    {
      _func = func;
      for (auto arg_iter = _func->arg_begin(); arg_iter != _func->arg_end(); arg_iter++)
      {
        _arg_list.push_back(&*arg_iter);
      }
      _entryNode = new Node(GraphNodeType::FUNC_ENTRY);
      _entryNode->setFunc(*func);
    }
    llvm::Function *getFunc() const { return _func; }
    Node *getEntryNode() { return _entryNode; }
    void addInst(llvm::Instruction &i);
    void buildFormalTreeForArgs();
    void buildFormalTreesForRetVal();
    llvm::DIType *getArgDIType(llvm::Argument &arg);
    llvm::DIType *getReturnValDIType();
    llvm::DILocalVariable *getArgDILocalVar(llvm::Argument &arg);
    llvm::AllocaInst *getArgAllocaInst(llvm::Argument &arg);
    Tree *getArgFormalInTree(llvm::Argument &arg);
    Tree *getArgFormalOutTree(llvm::Argument &arg);
    Tree *getRetFormalInTree() { return _ret_val_formal_in_tree; }
    Tree *getRetFormalOutTree() { return _ret_val_formal_out_tree; }
    std::map<llvm::Argument *, Tree *> &getArgFormalInTreeMap() { return _arg_formal_in_tree_map; }
    std::map<llvm::Argument *, Tree *> &getArgFormalOutTreeMap() { return _arg_formal_out_tree_map; }
    std::vector<llvm::AllocaInst *> &getAllocInsts() { return _alloca_insts; }
    std::vector<llvm::DbgVariableIntrinsic *> &getDbgDeclareInsts() { return _dbg_declare_insts; }
    std::vector<llvm::LoadInst *> &getLoadInsts() { return _load_insts; }
    std::vector<llvm::StoreInst *> &getStoreInsts() { return _store_insts; }
    std::vector<llvm::CallInst *> &getCallInsts() { return _call_insts; }
    std::vector<llvm::ReturnInst *> &getReturnInsts() { return _return_insts; }
    std::vector<llvm::Argument *> &getArgList() { return _arg_list; }
    bool hasNullRetVal() { return (_ret_val_formal_in_tree == nullptr); }
    std::set<llvm::Value *> computeAddrVarDerivedFromArg(llvm::Argument &arg);
    int getArgIdxByFormalInTree(Tree* tree);
    void setControlDepBuilt() { hasControlDep = true; }
    bool hasControlDepBuilt() { return hasControlDep; }

  private:
    Node *_entryNode;
    llvm::Function *_func;
    std::vector<llvm::AllocaInst *> _alloca_insts;
    std::vector<llvm::DbgVariableIntrinsic *> _dbg_declare_insts;
    std::vector<llvm::LoadInst *> _load_insts;
    std::vector<llvm::StoreInst *> _store_insts;
    std::vector<llvm::CallInst *> _call_insts;
    std::vector<llvm::ReturnInst *> _return_insts;
    std::vector<llvm::Argument *> _arg_list;
    std::map<llvm::Argument *, Tree *> _arg_formal_in_tree_map;
    std::map<llvm::Argument *, Tree *> _arg_formal_out_tree_map;
    Tree *_ret_val_formal_in_tree;
    Tree *_ret_val_formal_out_tree;
    std::vector<llvm::UnreachableInst*> _unreachableInsts;
    bool hasControlDep = false;

  };
} // namespace pdg

#endif