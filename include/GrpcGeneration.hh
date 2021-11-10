#ifndef _GRPCGENERATION_H_
#define _GRPCGENERATION_H_
#include "LLVMEssentials.hh"
#include "DataAccessAnalysis.hh"

namespace grpc_gen
{
  class GrpcGenAnalysis : public llvm::ModulePass
  {
    public: 
      static char ID;
      GrpcGenAnalysis() : llvm::ModulePass(ID) {};
      bool runOnModule(llvm::Module &M) override;
      llvm::StringRef getPassName() const override { return "Grpc Gen Analysis"; }
      void generateServiceInterfaceForModule(llvm::Module &M);
      void generateServiceInterfaceForFunc(llvm::Function &F);
      void generateMsgStrForFunc(llvm::Function &F);
      void generateMsgStrFromArgTree(pdg::Tree *arg_tree, bool is_ret = false);
      void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
      // generate server code
      void generateServerStubCode();
      void generateExternCHeader();
      void generateServerRpcHeaders();
      void generateServiceImplClass();
      void generateServicesImpl();
      void generateRunServer();

      // generate slicent code
      void generateClientStubCode();
      void generateClientRpcHeaders();
      void generateClientImplClass();
      void generateClientImpl();
      void generateStubHeaderInC();
      void generateStubCodeInC();

      // helper funcs
      std::string computeFuncSignature(llvm::Function &F, std::string default_func_name = "");
      std::string computeFuncArgStr(llvm::Function &F);

    private:
      std::ofstream _proto_buf_file;
      std::ofstream _server_file;
      std::ofstream _client_file;
      std::ofstream _client_stub_header;
      std::string _msg_str = "";
      pdg::DataAccessAnalysis *_DAA;
      pdg::SharedDataAnalysis *_SDA;
      pdg::ProgramGraph *_PDG;
  };
}

#endif