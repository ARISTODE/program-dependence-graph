#include "GrpcGeneration.hh"

using namespace llvm;

char pdg::GrpcGenAnalysis::ID = 0;


bool pdg::GrpcGenAnalysis::runOnModule(Module &M)
{
  _proto_buf_file.open("test.proto");
  _proto_buf_file << "syntax = \"proto3\"";
  // generation
  generate
  for (auto &F : _SDA->getBoundaryFuncs())
  {
    if (F->isDeclaration())
      continue;
    generateGrpcForFunc(*F);
  }

  return false;
}

void pdg::GrpcGenAnalysis::generateServiceInterfaceForModule(Module &M)
{
  _proto_buf_file << "service Service {\n";
  for (auto F : _SDA->getBoundaryFuncs())
  {
    if (F.isDeclaration())
      continue;
    generateServiceInterfaceForFunc(*F);
  }
  _proto_buf_file << "}\n";
}

void pdg::GrpcGenAnalysis::generateServiceInterfaceForFunc(Function &F)
{
  std::string request_str = F.getName().str() + "Request";
  std::string response_str = F.getName().str() + "Response";

  _proto_buf_file << "rpc " << F.getName().str() << "(" << request_str << ")" << "returns " << "(" response_str << ")" << "{}\n";

  generateMsgStrForFunc(F);
}

void pdg::GrpcGenAnalysis::generateMsgStrForFunc(Function &F)
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
  std::string ret_val_type_name = dbgutils::getSourceLevelTypeName(*ret_val_di_type);
  response_str << "message " << func_name << "Response { \n" << ret_val_type_name << " = 1;"  << "\n}"

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
    Tree *arg_tree = iter->second;
    TreeNode* root_node = arg_tree->getRootNode();
    auto arg_di_type = root_node->getDIType();
    // if (dbgutils::isStructPointerType(*arg_di_type))
    //   generateMsgStrFromArgTree(arg_tree);

    auto arg_name = dbgutils::getArgumentName(*(iter->first));
    auto arg_type_name = dbgutils::getSourceLevelTypeName(arg_di_type);
    request_s << arg_type_name << " " << arg_name << " = " << arg_count << ";\n";
    ++arg_count;
  }
  request_s << "}\n";
}

// void pdg::GrpcGenAnalysis::generateMsgStrFromArgTree(pdg::Tree* arg_tree, bool is_ret)
// {


// }

void pdg::DataAccessAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.setPreservesAll();
}

static RegisterPass<pdg::DataAccessAnalysis>
    GRPCGEN("grpc-gen", "Grpc Generation Analysis Pass", false, true);