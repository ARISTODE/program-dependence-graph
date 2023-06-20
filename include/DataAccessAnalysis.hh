#ifndef DATAACCESSANALYSIS_H_
#define DATAACCESSANALYSIS_H_
#include "SharedDataAnalysis.hh"
#include "llvm/Analysis/CaptureTracking.h"
#include "json.hpp"
#include <fstream>
#include <sstream>

namespace pdg
{
  class DataAccessAnalysis : public llvm::ModulePass
  {
  public:
    static char ID;
    DataAccessAnalysis() : llvm::ModulePass(ID){};
    bool runOnModule(llvm::Module &M) override;
    void generateSyncStubsForBoundaryFunctions(llvm::Module &M);
    void generateSyncStubsForGlobalVars();
    void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
    llvm::StringRef getPassName() const override { return "Data Access Analysis"; }
    void computeDataAccessTagsForVal(llvm::Value &val, std::set<AccessTag> &accTags);
    void computeDataAccessTagsForArrayVal(llvm::Value &val, std::set<AccessTag> &accTags);
    std::set<pdg::Node *> findCrossDomainParamNode(Node &n, bool isBackward = false);
    void readDriverDefinedGlobalVarNames(std::string fileName);
    void readDriverExportedFuncSymbols(std::string fileName);
    bool isSharedAllocator(llvm::Value &allocator);
    std::unordered_set<pdg::Node *> computeSharedAllocators();
    void propagateAllocSizeAnno(llvm::Value &allocator);
    void inferDeallocAnno(llvm::Value &deallocator);
    void computeAllocSizeAnnos(llvm::Module &M);
    void computeDeallocAnnos(llvm::Module &M);
    void computeCollocatedAllocsite(llvm::Module &M);
    void checkCollocatedAllocsite(llvm::Value &allocSite);
    void computeExportedFuncsPtrNameMap();
    void computeDataAccessForTree(Tree *tree, bool isRet = false);
    void computeDataAccessForGlobalTree(Tree *tree);
    void computeDataAccessForTreeNode(TreeNode &treeNode, bool isGlobalTreeNode = false, bool isRet = false);
    void computeDataAccessForFuncArgs(llvm::Function &F);
    void checkCrossDomainRAWforFormalTreeNode(TreeNode &treeNode);
    void computeKernelReadDriverUpdateFields(llvm::Module &M);
    void computeFieldReadWriteForTree(Tree *argTree, bool isKernelFunc = true);
    void computeKernelReadSharedFields(llvm::Function &F);
    void computeDriverUpdateSharedFields(llvm::Function &F);
    void generateIDLForFunc(llvm::Function &F, bool processExportedFunc = false);
    void generateRpcForFunc(llvm::Function &F, bool processExportedFunc = false);
    void generateIDLFromGlobalVarTree(llvm::GlobalVariable &gv, Tree *tree);
    void generateIDLFromArgTree(Tree *argTree, std::ofstream &outputFile, bool isRet = false, bool isGlobal = false);
    void generateIDLFromTreeNode(TreeNode &treeNode, llvm::raw_string_ostream &fieldsProjectionStr, llvm::raw_string_ostream &nestedStructProjStr, std::queue<TreeNode *> &nodeQueue, std::string indentLevel, std::string parentStructTypeName, bool isRet = false);
    void generateJSONObjectForFunc(llvm::Function &F, nlohmann::json &moduleJSONObj);
    nlohmann::json generateJSONObjectFromArgTree(Tree *argTree, unsigned argIdx);
    unsigned computeAccCapForNode(TreeNode &treeNode);
    nlohmann::json createJSONObjectForNode(TreeNode &treeNode);
    void constructGlobalOpStructStr();
    void computeContainerOfLocs(llvm::Function &F);
    std::set<std::string> inferTreeNodeAnnotations(TreeNode &treeNode, bool isRet = false);
    // void inferAllocStackForKernelToDriverCalls();
    std::string inferAllocStackAnnotation(TreeNode &treeNode);
    void inferUserAnnotation(TreeNode &treeNode, std::set<std::string> &annotations);
    void inferMayWithin(TreeNode &treeNode, std::set<std::string> &annoStr);
    bool globalVarHasAccessInDriver(llvm::GlobalVariable &gv);
    bool isDriverDefinedGlobal(llvm::GlobalVariable &gv);
    bool containerHasSharedFieldsAccessed(llvm::BitCastInst &bci, std::string structTyName);
    bool isExportedFunc(llvm::Function &F);
    bool passedToLibrary(Node &paramNode); // TODO: finish implementing the function summary
    std::string computeAllocCallerAnnotation(TreeNode &treeNode);
    std::string computeAllocCalleeAnnotation(TreeNode &treeNode);
    std::string getExportedFuncPtrName(std::string funcName);
    std::set<Node *> findAllocator(TreeNode &treeNode, bool isForward = false);
    FunctionWrapper *getNescheckFuncWrapper(llvm::Function &F); // F's signature is rewrittern by nescheck
    std::set<llvm::Function *> getPointedFuncAtArgIdx(llvm::Function &F, unsigned argIdx);
    std::map<unsigned, unsigned> getFieldOffsetAccessMap(TreeNode &paramRootNode);
    void dumpFieldOffsetAccessMapToFile(TreeNode &paramRootNode, std::string fileName);
    // functions related to identifying risky allocator
    void initAllocatorFuncNodes();
    bool allocateKernelObj(llvm::Function &F);
    void findKernelAllocatorAPI(std::unordered_set<llvm::Function *> &allocatorFuncs);
    // functions related to identifying risky deallocator
    void initDeallocatorFuncNodes();
    bool deallocateKernelObj(llvm::Function &F);
    void findKernelDeallocatorAPI(std::unordered_set<llvm::Function *> &allocatorFuncs);
    // helper funcs on identify alloc/dealloc APIs
    void printDriverTaintKernelAllocDeallocFuncs();
    void printDriverCallSite(llvm::Function &boundaryFunc, llvm::Function &sinkFunc, bool isAlloc);
    bool hasParamDataflow(llvm::Function &boundaryFunc, llvm::Function &allocatorFunc);
    // logging related functions
    void printContainerOfStats();
    void logSkbFieldStats(TreeNode &skb_root_node);
    void logSkbNode(TreeNode &treeNode);
    void countControlData(TreeNode &treeNode);
    bool isUsedInBranchStat(Node &valNode);
    DomainTag computeFuncDomainTag(llvm::Function &F);
    KSplitStats *getKSplitStats() { return _ksplitStats; }
    SharedDataAnalysis *getSDA() { return _SDA; }
    ProgramGraph *getPDG() { return _PDG; }
    // shared fields analysis
    std::set<std::string> _kernelReadSharedFields;
    std::set<std::string> _driverUpdateSharedFields;

  private:
    llvm::Module *_module;
    SharedDataAnalysis *_SDA;
    ProgramGraph *_PDG;
    PDGCallGraph *_callGraph;
    std::ofstream _idlFile;
    std::ofstream _globalVarAccessInfo;
    std::ofstream _sync_stub_file;
    std::unordered_set<std::string> _seenFuncOps;
    std::string _opsStructProjStr;
    std::map<std::string, std::string> _exportedFuncsPtrNameMap;
    std::unordered_set<std::string> _existFuncDefs;
    std::map<std::string, std::set<std::string>> _globalOpsFieldsMap;
    std::unordered_set<llvm::Instruction *> _containerofInsts;
    KSplitStats *_ksplitStats;
    std::string _currentProcessingFunc = "";
    std::unordered_set<std::string> _driverDefGlobalVarNames;
    std::unordered_set<std::string> _driverExportedFuncSymbols;
    std::unordered_set<Node *> _funcsReachableFromBoundary;
    std::unordered_set<llvm::Function *> _kernelFuncsRegisteredWithFuncPtr;
    std::unordered_set<llvm::Function *> _transitiveBoundaryFuncs;
    bool _generateingIDLforGlobal = false;
    std::set<std::string> _visitedSharedFieldIDInRAWAna;
    unsigned int _kernelRAWDriverFields = 0;
    std::unordered_set<Node *> allocatorFuncNodes;
    std::unordered_set<Node *> deallocatorFuncNodes;
  };
}

#endif