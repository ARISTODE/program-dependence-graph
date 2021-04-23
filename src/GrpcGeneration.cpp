#include "GrpcGeneration.hh"

using namespace llvm;

char grpc_gen::GrpcGenAnalysis::ID = 0;

bool grpc_gen::GrpcGenAnalysis::runOnModule(Module &M)
{
  _DAA = &getAnalysis<pdg::DataAccessAnalysis>();
  _SDA = _DAA->getSDA();
  _PDG = _SDA->getPDG();
  _proto_buf_file.open("test.proto");
  _proto_buf_file << "syntax = \"proto3\"";
  // generation
  generateServiceInterfaceForModule(M);
  _proto_buf_file.close();
  return false;
}

void grpc_gen::GrpcGenAnalysis::generateServiceInterfaceForModule(Module &M)
{
  _proto_buf_file << "service Service {\n";
  for (auto F : _SDA->getBoundaryFuncs())
  {
    if (F->isDeclaration())
      continue;
    generateServiceInterfaceForFunc(*F);
  }
  _proto_buf_file << "}\n";
  _proto_buf_file << _msg_str;
}

void grpc_gen::GrpcGenAnalysis::generateServiceInterfaceForFunc(Function &F)
{
  std::string request_str = F.getName().str() + "Request";
  std::string response_str = F.getName().str() + "Response";

  _proto_buf_file << "\trpc " << F.getName().str() << "(" << request_str << ")" << "returns " << "(" << response_str << ")" << "{}\n";

  generateMsgStrForFunc(F);
}

void grpc_gen::GrpcGenAnalysis::generateMsgStrForFunc(Function &F)
{
  std::string func_name = F.getName().str();
  auto func_wrapper_map = _PDG->getFuncWrapperMap();
  auto func_iter = func_wrapper_map.find(&F);
  assert(func_iter != func_wrapper_map.end() && "no function wrapper found (IDL-GEN)!");
  auto fw = func_iter->second;
  // generate response msg (return value)
  std::string response_str;
  raw_string_ostream response_s(response_str);

  auto ret_arg_tree = fw->getRetFormalInTree();
  auto ret_root_node = ret_arg_tree->getRootNode();
  auto ret_val_di_type = ret_root_node->getDIType();
  std::string ret_val_type_name = "";
  if (ret_val_di_type != nullptr)
    ret_val_type_name = pdg::dbgutils::getSourceLevelTypeName(*ret_val_di_type) + " = 1";
  response_s << "message " << func_name << "Response { \n\t" << ret_val_type_name << "\n}";

  // if (dbgutils::getFuncRetDIType(F) != nullptr)
  //   generateMsgStrFromArgTree(ret_arg_tre, true);

  // generate request msg (parameters)
  std::string request_str;
  raw_string_ostream request_s(request_str);
  auto arg_tree_map = fw->getArgFormalInTreeMap();
  unsigned arg_count = 1;
  request_s << "message " << func_name << "Request {\n ";
  for (auto iter = arg_tree_map.begin(); iter != arg_tree_map.end(); iter++)
  {
    pdg::Tree *arg_tree = iter->second;
    pdg::TreeNode* root_node = arg_tree->getRootNode();
    auto arg_di_type = root_node->getDIType();
    // if (dbgutils::isStructPointerType(*arg_di_type))
    //   generateMsgStrFromArgTree(arg_tree);

    auto arg_name = pdg::dbgutils::getArgumentName(*(iter->first));
    auto arg_type_name = pdg::dbgutils::getSourceLevelTypeName(*arg_di_type);
    request_s << "\t" << arg_type_name << " " << arg_name << " = " << arg_count << ";\n";
    ++arg_count;
  }
  request_s << "}\n";

  _msg_str = _msg_str + response_s.str() + "\n";
  _msg_str = _msg_str + request_s.str() + "\n";
}

// void pdg::GrpcGenAnalysis::generateMsgStrFromArgTree(pdg::Tree* arg_tree, bool is_ret)
// {


// }

void grpc_gen::GrpcGenAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<pdg::DataAccessAnalysis>();
  AU.setPreservesAll();
}

static RegisterPass<grpc_gen::GrpcGenAnalysis>
    GRPCGEN("grpc-gen", "Grpc Generation Analysis Pass", false, true);