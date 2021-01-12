#ifndef CALLWRAPPER_H_
#define CALLWRAPPER_H_
#include "LLVMEssentials.hh"
#include "Tree.hh"
#include "PDGUtils.hh"
#include "FunctionWrapper.hh"

namespace pdg
{
  class CallWrapper
  {
    private:
      llvm::Function* _called_func;
      std::vector<llvm::Value *> _arg_list;
      std::map<llvm::Argument *, Tree *> _arg_actual_tree_map;
    public:
      CallWrapper(llvm::CallInst& ci)
      {
        assert(ci.getCalledFunction() != nullptr);
        _called_func = ci.getCalledFunction();
        // for (auto arg_iter = ci.arg_begin(); arg_iter != ci.arg_end(); ++arg_iter) 
        // {
        //   _arg_list.push_back(&*arg_iter);
        // }
      }
      void buildActualTreeForArgs(FunctionWrapper* fw);
  };
}

#endif