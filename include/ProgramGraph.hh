#ifndef _PROGRAMGRAPH_H_
#define _PROGRAMGRAPH_H_
#include "PDGCallGraph.hh"

namespace pdg
{
    class ProgramGraph : public GenericGraph
    {
    public:
        typedef std::unordered_map<llvm::Function *, FunctionWrapper *> FuncWrapperMap;
        typedef std::unordered_map<llvm::CallInst *, CallWrapper *> CallWrapperMap;
        typedef std::unordered_map<Node *, llvm::DIType *> NodeDIMap;
        typedef std::unordered_map<llvm::GlobalVariable *, Tree *> GlobalVarTreeMap;

        ProgramGraph() = default;
        ProgramGraph(const ProgramGraph &) = delete;
        ProgramGraph(ProgramGraph &&) = delete;
        ProgramGraph &operator=(const ProgramGraph &) = delete;
        ProgramGraph &operator=(ProgramGraph &&) = delete;
        static ProgramGraph &getInstance()
        {
            static ProgramGraph g{};
            return g;
        }

        FuncWrapperMap &getFuncWrapperMap() { return _func_wrapper_map; }
        CallWrapperMap &getCallWrapperMap() { return _call_wrapper_map; }
        NodeDIMap &getNodeDIMap() { return _node_di_type_map; }
        GlobalVarTreeMap &getGlobalVarTreeMap() { return _global_var_tree_map; }
        void build(llvm::Module &M) override;
        bool hasFuncWrapper(llvm::Function &F) { return _func_wrapper_map.find(&F) != _func_wrapper_map.end(); }
        bool hasCallWrapper(llvm::CallInst &ci) { return _call_wrapper_map.find(&ci) != _call_wrapper_map.end(); }
        FunctionWrapper *getFuncWrapper(llvm::Function &F) { return _func_wrapper_map[&F]; }
        CallWrapper *getCallWrapper(llvm::CallInst &ci) { return _call_wrapper_map[&ci]; }
        void bindDITypeToNodes();
        llvm::DIType *computeNodeDIType(Node &n);
        void addTreeNodesToGraph(Tree &tree);
        void addFormalTreeNodesToGraph(FunctionWrapper &func_w);
        std::set<llvm::Value *> &getAllocators() { return _allocators; }
        std::set<llvm::Value *> &getDeallocators() { return _deallocators; }

    private:
        FuncWrapperMap _func_wrapper_map;
        CallWrapperMap _call_wrapper_map;
        GlobalVarTreeMap _global_var_tree_map;
        NodeDIMap _node_di_type_map;
        std::set<llvm::Value *> _allocators;
        std::set<llvm::Value *> _deallocators;
    };
}

#endif