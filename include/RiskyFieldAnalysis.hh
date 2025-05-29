#ifndef RISKY_FIELD_ANALYSIS_H_
#define RISKY_FIELD_ANALYSIS_H_
#include "SharedDataAnalysis.hh"
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
            void propagateTaints(std::set<llvm::Function *> &kernelInterfaceAPIs);
            void classifyRiskySharedFields();
            void classifyRiskyBoundaryParams(std::set<llvm::Function *> &kernelInterfaceAPIs);
            void classifyDrvCallBackRetval();

            bool isDriverControlledField(TreeNode &tn, bool &hasDrvRead);
            llvm::Function *canReachSensitiveOperations(Node &srcFuncNode);
            void classifyRiskyFieldDirectUse(TreeNode &tn);
            void classifyRiskyFieldTaint(TreeNode &tn);
            void classifyRiskyField(TreeNode &tn, std::set<RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs);
            bool classifyRiskyPtrField(TreeNode &tn, std::set<RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs);
            bool classifyRiskyNonPtrField(TreeNode &tn, std::set<RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs);
            // helper funcs
            bool hasUpdateInDrv(TreeNode &n);
            std::unordered_set<Node *> findNodesTaintedByEdges(Node &src, std::set<EdgeType> &edgeTypes, bool isBackward = false);
            bool canParamReachRetVal(FunctionWrapper &fw);
            // print helpers
            void printRiskyFieldInfo(llvm::raw_ostream &os, const std::string &category, TreeNode &treeNode, llvm::Function &func, llvm::Instruction &inst);
            void printTaintTrace(llvm::Instruction &source, llvm::Instruction &sink, std::string fieldHierarchyName, std::string flowType, llvm::raw_fd_ostream &OS);
            void printJsonToFile(nlohmann::ordered_json& json, std::string logFileName);
            void getTraceStr(llvm::Instruction &source, llvm::Instruction &sink, std::string fieldHierarchyName, std::string flowType, llvm::raw_string_ostream &OS);
            void printFieldDirectUseClassification(llvm::raw_fd_ostream &OS);
            void printFieldClassificationTaint();
            void printTaintFieldInfo();
            // functions for generating the trace object
            bool isDstInstPrecedeOfSrcInst(Node& srcNode, Node &dstNode);
            void populateInterfaceParamTraceInfo(Node &paramTreeNode, nlohmann::ordered_json &traceJsonObj, llvm::Instruction &sinkInst);
            void populateDrvUpdateLocations(TreeNode &treeNode, nlohmann::ordered_json &traceJsonObj, llvm::Instruction &sinkInst);
            void populatePathChecksInfo(std::vector<std::pair<Node *, Edge *>> &taintPath, nlohmann::ordered_json &traceJsonObj);
            void populateDirectPathChecksInfo(std::vector<std::pair<Node *, Edge *>> &taintPath, Node &srcNode, Node &dstNode, nlohmann::ordered_json &traceObj);
            nlohmann::ordered_json generateTraceJsonObj(Node &srcNode, Node &dstNode, std::string accessPathStr, std::string taintType, unsigned caseId, std::set<EdgeType> &taintEdges, TreeNode *typeTreeNode = nullptr);
            void updateRiskyFieldCounters(std::set<RiskyDataType> &riskyDataTypes);
            void updateRiskyParamCounters(std::set<RiskyDataType> &riskyDataTypes);
            void printBoundaryStructFieldsClassificationStats();
            SharedDataAnalysis *getSDA() { return _SDA; }

        private:
            llvm::Module *_module;
            ProgramGraph *_PDG;
            SharedDataAnalysis *_SDA;
            PDGCallGraph *_callGraph;
            // store taint source/sink pair
            std::set<std::tuple<Node *, Node *, std::string, std::string>> _taintTuples;
            std::set<std::tuple<Node *, Node *, std::string, std::string>> _structTaintTuples; // used to store taint for struct field
            unsigned _caseID = 0;
            // stats counting
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
            // output file
            std::unordered_map<RiskyDataType, int> totalRiskyFieldCounters;
            std::unordered_map<RiskyDataType, int> totalRiskyParamCounters;
            nlohmann::ordered_json taintTracesJson = nlohmann::ordered_json::array();
            nlohmann::ordered_json unclassifiedFieldsJson = nlohmann::ordered_json::array();
            std::unordered_set<std::string> _KRDUFieldIds;
            std::unordered_map<std::string, nlohmann::ordered_json> _sharedStructTypeRiskyCounts;
            std::unordered_map<std::string, std::set<std::string>> _sharedStructClassifiedFields;
            std::unordered_map<std::string, std::map<RiskyDataType, std::set<std::string>>> _fieldRiskyTypeMap;
            // mapping struct, to risky classification, and the fields in those risky classification
    };
}

#endif