#include "DataAccessAnalysis.hh"

using namespace llvm;

char pdg::DataAccessAnalysis::ID = 0;

bool pdg::DataAccessAnalysis::runOnModule(Module &M)
{
  auto start = std::chrono::high_resolution_clock::now();
  _module = &M;
  PDG = getAnalysis<ProgramDependencyGraph>().getPDG();
  idl_file.open("kernel.idl");
  // intra-procedural analysis
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    computeIntraProcDataAccess(F);
  }
  // inter-procedural analysis 
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    // auto call_chain = uti
  }

  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    generateIDLForFunc(F);
  }

  errs() << "Finish analyzing data access info.";
  idl_file.close();
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  errs() << "data analysis pass takes: " << duration.count() << "\n";
  return false;
}

void pdg::DataAccessAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<ProgramDependencyGraph>();
  AU.setPreservesAll();
}

std::set<pdg::AccessTag> pdg::DataAccessAnalysis::computeDataAccessTagsForVal(Value &val)
{
  std::set<AccessTag> acc_tags;
  if (pdgutils::hasReadAccess(val))
    acc_tags.insert(AccessTag::DATA_READ);
  if (pdgutils::hasWriteAccess(val))
    acc_tags.insert(AccessTag::DATA_WRITE);
  return acc_tags;
}

void pdg::DataAccessAnalysis::computeDataAccessForTreeNode(TreeNode& tree_node)
{
  auto addr_vars = tree_node.getAddrVars();
  for (auto addr_var : addr_vars)
  {
    auto acc_tags = computeDataAccessTagsForVal(*addr_var);
    for (auto acc_tag : acc_tags)
    {
      tree_node.addAccessTag(acc_tag);
    }
  }
}

void pdg::DataAccessAnalysis::computeDataAccessForTree(Tree* tree)
{
  TreeNode* root_node = tree->getRootNode();
  assert(root_node != nullptr && "cannot compute access info for empty tree!");
  std::queue<TreeNode*> node_queue;
  node_queue.push(root_node);
  while (!node_queue.empty())
  {
    TreeNode* current_node = node_queue.front();
    node_queue.pop();
    computeDataAccessForTreeNode(*current_node);
    for (auto child_node : current_node->getChildNodes())
    {
      node_queue.push(child_node);
    }
  }
}

void pdg::DataAccessAnalysis::computeIntraProcDataAccess(Function &F)
{
  auto func_wrapper_map = PDG->getFuncWrapperMap();
  if (func_wrapper_map.find(&F) == func_wrapper_map.end())
    return;
  FunctionWrapper* fw =  func_wrapper_map[&F];
  auto arg_tree_map = fw->getArgFormalInTreeMap();
  for (auto iter = arg_tree_map.begin(); iter != arg_tree_map.end(); iter++)
  {
    Tree* arg_tree = iter->second;
    computeDataAccessForTree(arg_tree);
  }
}

/*
Four cases:
1. pointer to simple type
2. simple type
3. pointer to aggregate type
4. aggregate type
*/
void pdg::DataAccessAnalysis::generateIDLFromTreeNode(TreeNode &tree_node, raw_string_ostream &projection_str, std::queue<TreeNode *> &node_queue, std::string indent_level)
{
  DIType* node_di_type = tree_node.getDIType();
  assert(node_di_type != nullptr && "cannot generate IDL for node with null DIType\n");
  DIType* node_lowest_di_type = dbgutils::getLowestDIType(*node_di_type);
  if (!node_lowest_di_type || !dbgutils::isProjectableType(*node_lowest_di_type))
    return;
  // generate idl for each field
  for (auto child_node : tree_node.getChildNodes())
  {
    if (child_node->getAccessTags().size() == 0)
      continue;

    DIType* field_di_type = child_node->getDIType();
    auto field_var_name = dbgutils::getSourceLevelVariableName(*field_di_type);
    auto field_type_name = dbgutils::getSourceLevelTypeName(*field_di_type);
    if (dbgutils::isStructPointerType(*field_di_type))
    {
      projection_str << indent_level
                     << "projection "
                     << field_type_name
                     << " "
                     << field_var_name;
      node_queue.push(child_node);
    }
    else if (dbgutils::isProjectableType (*field_di_type))
    {
      std::string sub_fields_str;
      raw_string_ostream nested_struct_proj_str(sub_fields_str);
      generateIDLFromTreeNode(*child_node, nested_struct_proj_str, node_queue, indent_level + "\t");
      projection_str << indent_level
                     << "projection "
                     << " {\n"
                     << nested_struct_proj_str.str()
                     << indent_level
                     << "} " << field_var_name
                     << ";\n";
    }
    else
    {
      projection_str << indent_level << field_type_name << " " << field_var_name << ";\n";
    }
  }
}

void pdg::DataAccessAnalysis::generateIDLFromArgTree(Tree *arg_tree)
{
  if (!arg_tree)
    return;
  TreeNode* root_node = arg_tree->getRootNode();
  DIType* root_node_di_type = root_node->getDIType();
  DIType* root_node_lowest_di_type = dbgutils::getLowestDIType(*root_node_di_type);
  if (!root_node_lowest_di_type || !dbgutils::isProjectableType(*root_node_lowest_di_type))
    return;
  std::queue<TreeNode*> node_queue;
  // generate root projection
  node_queue.push(root_node);
  while (!node_queue.empty())
  {
    TreeNode* current_node = node_queue.front();
    node_queue.pop();
    DIType* node_di_type = current_node->getDIType();
    DIType* node_lowest_di_type = dbgutils::getLowestDIType(*node_di_type);
    // check if node needs projection
    if (!node_lowest_di_type || !dbgutils::isProjectableType(*node_lowest_di_type))
      continue;
    // get the type / variable name for the pointer field
    auto proj_type_name = dbgutils::getSourceLevelTypeName(*node_di_type);
    auto proj_var_name = dbgutils::getSourceLevelVariableName(*node_di_type);
    if (current_node->isRootNode())
      proj_var_name = dbgutils::getSourceLevelVariableName(*current_node->getDILocalVar());
    std::string str;
    raw_string_ostream projection_str(str);
    // for pointer to aggregate type, retrive the child node(pointed object), and generate projection
    if (dbgutils::isPointerType(*node_di_type) && !current_node->getChildNodes().empty())
      current_node = current_node->getChildNodes()[0];
    generateIDLFromTreeNode(*current_node, projection_str, node_queue, "\t\t");

    idl_file << "\tprojection < " << proj_type_name << "> "
             << proj_var_name
             << " {\n"
             << projection_str.str()
             << "\t};\n";
  }
}

void pdg::DataAccessAnalysis::generateRpcForFunc(Function &F)
{
  FunctionWrapper *fw = PDG->getFuncWrapperMap()[&F];
  std::string rpc_str = "";
  // generate function rpc stub
  rpc_str = "rpc " + F.getName().str() + "( ";
  auto arg_list = fw->getArgList();
  for (int i = 0; i < arg_list.size(); i++)
  {
    auto arg = arg_list[i];
    auto formal_in_tree = fw->getArgFormalInTree(*arg);
    if (!formal_in_tree)
      continue;
    TreeNode* root_node = formal_in_tree->getRootNode();
    auto arg_name = dbgutils::getSourceLevelVariableName(*root_node->getDILocalVar());
    auto arg_type_name = dbgutils::getSourceLevelTypeName(*root_node->getDIType());
    if (dbgutils::isStructPointerType(*root_node->getDIType()))
      arg_type_name = "projection *";

    rpc_str = rpc_str + arg_type_name + " " + arg_name;
    if (i != arg_list.size() - 1)
      rpc_str += ", ";
  }
  rpc_str += " ) ";
  idl_file << rpc_str;
}

void pdg::DataAccessAnalysis::generateIDLForFunc(Function &F)
{
  auto func_wrapper_map = PDG->getFuncWrapperMap();
  auto func_iter = func_wrapper_map.find(&F);
  assert(func_iter != func_wrapper_map.end() && "no function wrapper found (IDL-GEN)!");
  auto fw = func_iter->second;
  generateRpcForFunc(F);
  idl_file << "{\n";
  auto arg_tree_map = fw->getArgFormalInTreeMap();
  for (auto iter = arg_tree_map.begin(); iter != arg_tree_map.end(); iter++)
  {
    auto arg_tree = iter->second;
    generateIDLFromArgTree(arg_tree);
  }
  idl_file << "}\n";
}

static RegisterPass<pdg::DataAccessAnalysis>
    DAA("daa", "Data Access Analysis Pass", false, true);