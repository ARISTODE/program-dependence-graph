#ifndef RISKY_FIELD_ANALYSIS_H_
#define RISKY_FIELD_ANALYSIS_H_
#include "DataAccessAnalysis.hh"
#include "ControlDependencyGraph.hh"
#include "TaintUtils.hh"
#include "json.hpp"

namespace pdg
{
    class RiskyFieldAnalysis : public llvm::ModulePass
    {
        public:
            static char ID;
            RiskyFieldAnalysis() : llvm::ModulePass(ID){};
            void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
            llvm::StringRef getPassName() const override { return "Risky Field Analysis"; }
            bool runOnModule(llvm::Module &M) override;

            // Core analysis functions
            void propagateTaints(std::set<llvm::Function *> &kernelInterfaceAPIs);
            void propagateTaintsFromSharedStructs();
            void propagateTaintsFromKernelInterfaces(std::set<llvm::Function *> &kernelInterfaceAPIs);
            void classifyRiskyBoundaryParams(std::set<llvm::Function *> &kernelInterfaceAPIs);
            void classifyRetErrorCode(std::set<llvm::Function *> &kernelInterfaceAPIs);

            // Classification helpers
            void classifyRiskyField(TreeNode &tn, std::set<RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs);
            bool classifyRiskyPtrField(TreeNode &tn, std::set<RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs);
            bool classifyRiskyNonPtrField(TreeNode &tn, std::set<RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs);
            
            // Analysis helpers
            bool isDriverControlledField(TreeNode &tn, bool &hasDrvRead);
            bool isUsedInSensitiveContext(Node &node, std::string &senOpName);
            bool isDstInstPrecedeOfSrcInst(Node& srcNode, Node &dstNode);
            bool hasUpdateInDrv(TreeNode &n);
            bool canParamReachRetVal(FunctionWrapper &fw);
            llvm::Function *canReachSensitiveOperations(Node &srcFuncNode);
            std::unordered_set<Node *> findNodesTaintedByEdges(Node &src, const std::set<EdgeType> &edgeTypes, bool isBackward = false);

            // Processing helpers
            void handleDirectRiskyAPI(llvm::Function &func, FunctionWrapper &funcWrapper);
            void processArgumentTree(Tree &argTree, llvm::StringRef funcName);
            void recordUnclassifiedField(TreeNode &tn);
            void addClassification(RiskyDataType type, std::set<RiskyDataType> &classifications,
                                 nlohmann::ordered_json &jsonObj, const std::string &accessPath,
                                 const std::string &details, Node &srcNode, Node &dstNode,
                                 const std::set<EdgeType> &edges);

            // Error code analysis
            bool analyzeReturnValueUsage(TreeNode &retRootNode, llvm::Function &func,
                                       const std::set<EdgeType> &taintEdges,
                                       nlohmann::ordered_json &retTaintJsonObjs,
                                       unsigned &numOfDrvIFuncRetEC,
                                       unsigned &numOfMissingEC);
            void recordMissingErrorCheck(llvm::Function &func, TreeNode &retRootNode,
                                       nlohmann::ordered_json &retTaintJsonObjs);

            // Statistics and trace generation
            void updateRiskyFieldCounters(std::set<RiskyDataType> &riskyDataTypes);
            void updateRiskyParamCounters(std::set<RiskyDataType> &riskyDataTypes);
            void updateClassificationStats(TreeNode &node, const std::set<RiskyDataType> &classifications,
                                        const std::string &structTypeName);
            void updateStructStats(const std::string &structTypeName, unsigned numFields,
                                 unsigned numKRDUFields);
            void populateInterfaceParamTraceInfo(Node &paramTreeNode, nlohmann::ordered_json &traceJsonObj,
                                               llvm::Instruction &sinkInst);
            void populateDrvUpdateLocations(TreeNode &treeNode, nlohmann::ordered_json &traceJsonObj,
                                          llvm::Instruction &sinkInst);
            void populatePathChecksInfo(std::vector<std::pair<Node *, Edge *>> &taintPath,
                                      nlohmann::ordered_json &traceJsonObj);
            void populateDirectPathChecksInfo(std::vector<std::pair<Node *, Edge *>> &taintPath,
                                            Node &srcNode, Node &dstNode,
                                            nlohmann::ordered_json &traceObj);
            nlohmann::ordered_json generateTraceJsonObj(Node &srcNode, Node &dstNode,
                                                       std::string accessPathStr, std::string taintType,
                                                       unsigned caseId, const std::set<EdgeType> &taintEdges,
                                                       TreeNode *typeTreeNode = nullptr);

            // Output functions
            void printFieldClassificationTaint();
            void printBoundaryStructFieldsClassificationStats();
            void printRiskyFieldInfo(llvm::raw_ostream &os, const std::string &category,
                                   TreeNode &treeNode, llvm::Function &func,
                                   llvm::Instruction &inst);

            // Accessors
            SharedDataAnalysis *getSDA() { return _SDA; }

        private:
            llvm::Module *_module;
            ProgramGraph *_PDG;
            DataAccessAnalysis *_DAA;
            SharedDataAnalysis *_SDA;
            PDGCallGraph *_callGraph;

            // Taint tracking
            std::set<std::tuple<Node *, Node *, std::string, std::string>> _taintTuples;
            std::set<std::tuple<Node *, Node *, std::string, std::string>> _structTaintTuples;
            unsigned _caseID = 0;

            // Statistics
            unsigned _numKernelReadDriverUpdatedFields = 0;
            unsigned _numSharedFields = 0;
            unsigned _numBoundaryArg = 0;
            unsigned _numBoundaryFields = 0;
            unsigned _numClassifiedBoundaryArg = 0;
            unsigned _numClassifiedBoundaryFields = 0;
            unsigned _numNonStructBoundaryArg = 0;
            unsigned numPtrField = 0;
            unsigned numFuncPtrField = 0;
            unsigned numDataPtrField = 0;
            unsigned numKernelAPIParam = 0;
            unsigned _numControlTaintTrace = 0;
            unsigned _numDirectControlTaintTrace = 0;
            unsigned _numTotalTaintTrace = 0;

            // Output tracking
            std::unordered_map<RiskyDataType, int> totalRiskyFieldCounters;
            std::unordered_map<RiskyDataType, int> totalRiskyParamCounters;
            nlohmann::ordered_json taintTracesJson = nlohmann::ordered_json::array();
            nlohmann::ordered_json unclassifiedFieldsJson = nlohmann::ordered_json::array();
            std::unordered_set<std::string> _KRDUFieldIds;
            std::unordered_map<std::string, nlohmann::ordered_json> _sharedStructTypeRiskyCounts;
            std::unordered_map<std::string, std::set<std::string>> _sharedStructClassifiedFields;
            std::unordered_map<std::string, std::map<RiskyDataType, std::set<std::string>>> _fieldRiskyTypeMap;
    };
}

#endif