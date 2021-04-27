#include "GrpcGeneration.hh"

using namespace llvm;

char grpc_gen::GrpcGenAnalysis::ID = 0;

bool grpc_gen::GrpcGenAnalysis::runOnModule(Module &M)
{
  _DAA = &getAnalysis<pdg::DataAccessAnalysis>();
  _SDA = _DAA->getSDA();
  _PDG = _SDA->getPDG();
  // append default headers
  _proto_buf_file.open("prog.proto");
  _proto_buf_file << "syntax = \"proto3\";\n";
  _proto_buf_file << "option java_multiple_files = true;\n";
  _proto_buf_file << "option java_package = \"io.grpc.examples.prog\";\n";
  _proto_buf_file << "option java_outer_classname = \"ProgProto\";\n";
  _proto_buf_file << "option objc_class_prefix = \"PRG\";\n";
  _proto_buf_file << "package prog;\n";
  // generation
  generateServiceInterfaceForModule(M);
  _proto_buf_file.close();

  // generate server side code
  _server_file.open("prog_server.cc");
  generateServerHeaders();
  _server_file.close();
  return false;
}

void grpc_gen::GrpcGenAnalysis::generateServiceInterfaceForModule(Module &M)
{
  _proto_buf_file << "service Prog {\n";
  for (auto F : _SDA->getServerFuncs())
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
  std::string response_str = F.getName().str() + "Reply";

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
  response_s << "message " << func_name << "Reply { \n\t" << ret_val_type_name << "\n}";

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

void grpc_gen::GrpcGenAnalysis::generateServerHeaders() {
  generateExternCHeader();
  generateRpcHeaders();
  generateServiceImplClass();
  generateRunServer();
}

void grpc_gen::GrpcGenAnalysis::generateExternCHeader() {
  _server_file << "extern \"C\" {\n";
  _server_file << "#include \"prog.h\"\n";
  _server_file << "}\n";
}

void grpc_gen::GrpcGenAnalysis::generateRpcHeaders() {
  _server_file << "#include <iostream>\n";
  _server_file << "#include <memory>\n";
  _server_file << "#include <string>\n";

  _server_file << "#include <grpcpp/grpcpp.h>\n";
  _server_file << "#include <grpcpp/health_check_service_interface.h>\n";
  _server_file << "#include <grpcpp/ext/proto_server_reflection_plugin.h>\n";

  _server_file << "#include \"prog.grpc.pb.h\"\n";
  for (auto server_func : _SDA->getServerFuncs())
  {
    std::string func_name = server_func->getName().str();
    std::string request_str = func_name + "Request";
    std::string reply_str = func_name + "Reply";
    _server_file << "using prog::" << request_str << ";\n";
    _server_file << "using prog::" << reply_str << ";\n";
  }
  _server_file << "using prog::Prog;\n\n";
}

void grpc_gen::GrpcGenAnalysis::generateServiceImplClass() {
  _server_file << "class ProgServiceImpl final : public Prog::Service {\n";
  generateServicesImpl();
  _server_file << "};\n";
}

void grpc_gen::GrpcGenAnalysis::generateServicesImpl()
{
  auto func_wrapper_map = _PDG->getFuncWrapperMap();

  for (auto server_func : _SDA->getServerFuncs())
  {
    auto func_iter = func_wrapper_map.find(server_func);
    assert(func_iter != func_wrapper_map.end() && "no function wrapper found (IDL-GEN)!");
    auto fw = func_iter->second;
    auto arg_tree_map = fw->getArgFormalInTreeMap();

    std::string func_name = server_func->getName().str();
    std::string func_request = func_name + "Request";
    std::string func_reply = func_name + "Reply";
    _server_file << "\tStatus " << func_name << "(ServerContext* context, const "
                 << func_request << "* request, "
                 << func_reply << "* reply) {\n";

    std::string request_arg_str = "";
    for (auto iter = arg_tree_map.begin(); iter != arg_tree_map.end(); iter++)
    {
      pdg::Tree *arg_tree = iter->second;
      pdg::TreeNode *root_node = arg_tree->getRootNode();
      auto arg_di_type = root_node->getDIType();
      auto arg_type_name = pdg::dbgutils::getSourceLevelTypeName(*arg_di_type);
      auto arg_name = pdg::dbgutils::getArgumentName(*(iter->first));
      request_arg_str = request_arg_str + "request->" + arg_name;
      request_arg_str += "()";
      if (arg_type_name.find("char*") != std::string::npos)
        request_arg_str += ".c_str()";
      if (std::next(iter) != arg_tree_map.end())
        request_arg_str += ", ";
    }

    _server_file << "\t\t" << func_name << "(" << request_arg_str << ");\n";
    _server_file << "\t\treturn Status::OK;\n";
    _server_file << "\t}\n";
  }
}

void grpc_gen::GrpcGenAnalysis::generateRunServer()
{
  _server_file << "void RunServer() {\n"
               << "\tstd::string server_address(\"0.0.0.0:50051\");\n"
               << "\tProgServiceImpl service;\n"
               << "\tgrpc::EnableDefaultHealthCheckService(true);\n"
               << "\tgrpc::reflection::InitProtoReflectionServerBuilderPlugin();\n"
               << "\tServerBuilder builder;\n"
               << "\tbuilder.AddListeningPort(server_address, grpc::InsecureServerCredentials());\n"
               << "\tbuilder.RegisterService(&service);\n"
               << "\tstd::unique_ptr<Server> server(builder.BuildAndStart());\n"
               << "\tstd::cout << \"Server listening on \" << server_address << std::endl;\n"
               << "\tserver->Wait();\n"
               << "}\n"
               << "int main(int argc, char** argv) {\n"
               << "\tRunServer();\n"
               << "\treturn 0;\n"
               << "}\n";
}

void grpc_gen::GrpcGenAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<pdg::DataAccessAnalysis>();
  AU.setPreservesAll();
}

static RegisterPass<grpc_gen::GrpcGenAnalysis>
    GRPCGEN("grpc-gen", "Grpc Generation Analysis Pass", false, true);