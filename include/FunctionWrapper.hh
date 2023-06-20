#ifndef FUNCTIONWRAPPER_H_
#define FUNCTIONWRAPPER_H_
#include "LLVMEssentials.hh"
#include "Tree.hh"
#include "PDGUtils.hh"

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
        _argList.push_back(&*arg_iter);
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
    Tree *getRetFormalInTree() { return _retValFormalInTree; }
    Tree *getRetFormalOutTree() { return _retValFormalOutTree; }
    std::map<llvm::Argument *, Tree *> &getArgFormalInTreeMap() { return _argFormalInTreeMap; }
    std::map<llvm::Argument *, Tree *> &getArgFormalOutTreeMap() { return _argFormalOutTreeMap; }
    std::vector<llvm::AllocaInst *> &getAllocInsts() { return _allocaInsts; }
    std::vector<llvm::DbgDeclareInst *> &getDbgDeclareInsts() { return _dbgDeclareInsts; }
    std::vector<llvm::LoadInst *> &getLoadInsts() { return _loadInsts; }
    std::vector<llvm::StoreInst *> &getStoreInsts() { return _storeInsts; }
    std::vector<llvm::CallInst *> &getCallInsts() { return _callInsts; }
    std::vector<llvm::ReturnInst *> &getReturnInsts() { return _returnInsts; }
    std::vector<llvm::Argument *> &getArgList() { return _argList; }
    bool hasNullRetVal() { return (_retValFormalInTree == nullptr); }
    std::set<llvm::Value *> computeAddrVarDerivedFromArg(llvm::Argument &arg);
    int getArgIdxByFormalInTree(Tree* tree);

  private:
    Node *_entryNode;
    llvm::Function *_func;
    std::vector<llvm::AllocaInst *> _allocaInsts;
    std::vector<llvm::DbgDeclareInst *> _dbgDeclareInsts;
    std::vector<llvm::LoadInst *> _loadInsts;
    std::vector<llvm::StoreInst *> _storeInsts;
    std::vector<llvm::CallInst *> _callInsts;
    std::vector<llvm::ReturnInst *> _returnInsts;
    std::vector<llvm::Argument *> _argList;
    std::map<llvm::Argument *, Tree *> _argFormalInTreeMap;
    std::map<llvm::Argument *, Tree *> _argFormalOutTreeMap;
    Tree *_retValFormalInTree;
    Tree *_retValFormalOutTree;

  };
} // namespace pdg

#endif