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
      void generateServiceInterfaceForModule(llvm::Module &M);
      void generateServiceInterfaceForFunc(llvm::Function &F);
      void generateMsgStrForFunc(llvm::Function &F);
      void generateMsgStrFromArgTree(pdg::Tree *arg_tree, bool is_ret = false);
      void getAnalysisUsage(llvm::AnalysisUsage &AU) const override;
      llvm::StringRef getPassName() const override { return "Grpc Gen Analysis"; }

    private:
      std::ofstream _proto_buf_file;
      std::string _msg_str = "";
      pdg::DataAccessAnalysis *_DAA;
      pdg::SharedDataAnalysis *_SDA;
      pdg::ProgramGraph *_PDG;
  };
}

#endif