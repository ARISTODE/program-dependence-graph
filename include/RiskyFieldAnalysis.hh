#ifndef RISKY_FIELD_ANALYSIS_H_
#define RISKY_FIELD_ANALYSIS_H_
#include "SharedDataAnalysis.hh"
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
            bool isDriverControlledField(TreeNode &tn);
            llvm::Function *canReachSensitiveOperations(Node &srcFuncNode);
            void classifyRiskyFieldDirectUse(TreeNode &tn);
            void classifyRiskyFieldTaint(TreeNode &tn);
            void classifyRiskyField(TreeNode &tn, std::set<RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs, unsigned &caseID);
            bool classifyRiskyPtrField(TreeNode &tn, std::set<RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs, unsigned &caseID);
            bool classifyRiskyNonPtrField(TreeNode &tn, std::set<RiskyDataType> &riskyClassifications, nlohmann::ordered_json &taintJsonObjs, unsigned &caseID);
            // pointer field checks
            bool checkPtrValUsedInPtrArithOp(Node &n);
            // scalar field checks
            bool checkValUsedAsArrayIndex(Node &n);
            bool checkIsArrayAccess(llvm::Instruction &inst);
            // generic field checks
            static bool checkValUsedInPtrArithOp(Node &n);
            bool checkValUsedInSenBranchCond(Node &n, llvm::raw_fd_ostream &OS, std::string &senTypeStr);
            bool checkValInSecurityChecks(Node &n);
            static bool checkValUsedInSensitiveOperations(Node &n, std::string &senOpName);
            bool checkValUsedInInlineAsm(Node &n);
            bool isSensitiveOperation(llvm::Function &F);
            bool hasUpdateInDrv(TreeNode &n);
            // print helpers
            void printRiskyFieldInfo(llvm::raw_ostream &os, const std::string &category, TreeNode &treeNode, llvm::Function &func, llvm::Instruction &inst);
            void printTaintTrace(llvm::Instruction &source, llvm::Instruction &sink, std::string fieldHierarchyName, std::string flowType, llvm::raw_fd_ostream &OS);
            void printJsonToFile(nlohmann::ordered_json& json, std::string logFileName);
            void getTraceStr(llvm::Instruction &source, llvm::Instruction &sink, std::string fieldHierarchyName, std::string flowType, llvm::raw_string_ostream &OS);
            void printFieldDirectUseClassification(llvm::raw_fd_ostream &OS);
            void printFieldClassificationTaint(llvm::raw_fd_ostream &OS);
            void printTaintFieldInfo();
            nlohmann::ordered_json generateTraceJsonObj(Node &srcNode, Node &dstNode, std::string accessPathStr, std::string taintType, unsigned caseId, std::set<EdgeType> &taintEdges, TreeNode *typeTreeNode = nullptr);
            void updateRiskyFieldCounters(std::set<RiskyDataType> &riskyDataTypes);
            void updateRiskyParamCounters(std::set<RiskyDataType> &riskyDataTypes);
            SharedDataAnalysis *getSDA() { return _SDA; }

        private:
            llvm::Module *_module;
            ProgramGraph *_PDG;
            SharedDataAnalysis *_SDA;
            PDGCallGraph *_callGraph;
            // store taint source/sink pair
            std::set<std::tuple<Node *, Node *, std::string, std::string>> _taintTuples;
            std::set<std::tuple<Node *, Node *, std::string, std::string>> _structTaintTuples; // used to store taint for struct field
            // stats counting
            unsigned _numKernelReadDriverUpdatedFields = 0;
            unsigned _numSharedFields = 0;
            unsigned _numBoundaryArg = 0;
            unsigned _numNonStructBoundaryArg = 0;
            unsigned numPtrField = 0;
            unsigned numFuncPtrField = 0;
            unsigned numDataPtrField = 0;
            unsigned numKernelAPIParam = 0;
            unsigned numControlTaintTrace = 0;
            // output file
            llvm::raw_fd_ostream *riskyFieldOS;
            llvm::raw_fd_ostream *riskyFieldTaintOS;
            std::unordered_map<RiskyDataType, int> totalRiskyFieldCounters;
            std::unordered_map<RiskyDataType, int> totalRiskyParamCounters;
            nlohmann::ordered_json taintTracesJson = nlohmann::ordered_json::array();
            nlohmann::ordered_json taintTracesJsonNoConds = nlohmann::ordered_json::array();
            nlohmann::ordered_json unclassifiedFieldsJson = nlohmann::ordered_json::array();
    };
}

#endif