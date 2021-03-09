#include "DataAccessAnalysis.hh"

using namespace llvm;

char pdg::DataAccessAnalysis::ID = 0;

void pdg::DataAccessAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<SharedDataAnalysis>();
  AU.setPreservesAll();
}

bool pdg::DataAccessAnalysis::runOnModule(Module &M)
{
  auto start = std::chrono::high_resolution_clock::now();
  _module = &M;
  _SDA = &getAnalysis<SharedDataAnalysis>();
  _PDG = _SDA->getPDG();
  computeExportedFuncsPtrNameMap();
  idl_file.open("kernel.idl");
  // intra-procedural analysis
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    computeIntraProcDataAccess(F);
    // computeInterProcDataAccess(F);
  }

  idl_file << "module kernel() {\n";
  for (auto F : _SDA->getBoundaryFuncs())
  {
    if (F->isDeclaration())
      continue;
    generateIDLForFunc(*F);
  }

  idl_file << _ops_struct_proj_str << "\n";
  idl_file << "\n}";
  errs() << "Finish analyzing data access info.";
  idl_file.close();
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  errs() << "data analysis pass takes: " << duration.count() << "\n";
  return false;
}

void pdg::DataAccessAnalysis::computeExportedFuncsPtrNameMap()
{
  std::ifstream driverExportFuncs("exported_funcs");
  std::ifstream driverExportFuncPtrs("exported_func_ptrs");
  for (std::string line1, line2; std::getline(driverExportFuncPtrs, line1), std::getline(driverExportFuncs, line2);)
  {
    // in some cases, a function pointer exported from driver may point to a kernel function
    // in this case, we don't treat this exported pointer as a interface function.
    Function *pointed_func = _module->getFunction(line2);
    if (pointed_func == nullptr || pointed_func->isDeclaration())
      continue;
    auto kernel_func = _SDA->getKernelFuncs();
    if (kernel_func.find(pointed_func) != kernel_func.end())
      continue;
    _exported_funcs_ptr_name_map[line1] = line2; // key: registered driver side function, value: the registered function pointer name
  }
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
  // special hanlding for function pointers
  if (tree_node.getDIType() != nullptr && dbgutils::isFuncPointerType(*tree_node.getDIType()))
  {
    tree_node.addAccessTag(AccessTag::DATA_READ);
  }
  // intra proc access tags
  auto addr_vars = tree_node.getAddrVars();
  for (auto addr_var : addr_vars)
  {
    auto acc_tags = computeDataAccessTagsForVal(*addr_var);
    for (auto acc_tag : acc_tags)
    {
      tree_node.addAccessTag(acc_tag);
    }
  }

  // inter proc access tags
  auto parameter_in_nodes = _PDG->findNodesReachedByEdge(tree_node, EdgeType::PARAMETER_IN);
  for (auto n : parameter_in_nodes)
  {
    if (n->getValue() != nullptr)
    {
      auto acc_tags = computeDataAccessTagsForVal(*n->getValue());
      for (auto acc_tag : acc_tags)
      {
        tree_node.addAccessTag(acc_tag);
      }
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
  auto func_wrapper_map = _PDG->getFuncWrapperMap();
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

void pdg::DataAccessAnalysis::computeInterProcDataAccess(Function &F)
{
  auto func_wrapper_map = _PDG->getFuncWrapperMap();
  if (func_wrapper_map.find(&F) == func_wrapper_map.end())
    return;
  FunctionWrapper* fw =  func_wrapper_map[&F];
  auto arg_tree_map = fw->getArgFormalInTreeMap();
  for (auto iter = arg_tree_map.begin(); iter != arg_tree_map.end(); iter++)
  {
    Tree* arg_tree = iter->second;
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
    DIType *field_di_type = child_node->getDIType();
    auto field_var_name = dbgutils::getSourceLevelVariableName(*field_di_type);
    // check for access tags, if none, no need to put this field in projection
    if (child_node->getAccessTags().size() == 0 && !dbgutils::isFuncPointerType(*field_di_type))
      continue;
    // check for shared fields
    std::string field_id = pdgutils::computeTreeNodeID(*child_node);
    if (!_SDA->isSharedFieldID(field_id) && !dbgutils::isFuncPointerType(*field_di_type))
      continue;

    auto field_type_name = dbgutils::getSourceLevelTypeName(*field_di_type);
    field_di_type = dbgutils::stripMemberTag(*field_di_type);
    // compute access attributes
    std::string access_attributes = "";
    auto child_access_tags = child_node->getAccessTags();
    if (child_access_tags.find(AccessTag::DATA_WRITE) != child_access_tags.end())
      access_attributes = "[out]";
    if (dbgutils::isStructPointerType(*field_di_type))
    {
      std::string field_name_prefix = "";
      if (field_var_name.find("_ops") != std::string::npos)
      {
        field_name_prefix = "_global_";
      }
      projection_str << indent_level
                     << "projection "
                     << field_name_prefix
                     << field_type_name 
                     << " *"
                     << field_var_name
                     << ";\n";
      node_queue.push(child_node);
    }
    else if (dbgutils::isProjectableType(*field_di_type))
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
    else if (dbgutils::isFuncPointerType(*field_di_type))
    {
      if (_exported_funcs_ptr_name_map.find(field_var_name) == _exported_funcs_ptr_name_map.end())
        continue;
      std::string exported_func_name = _exported_funcs_ptr_name_map[field_var_name];
      Function *called_func = _module->getFunction(exported_func_name);
      if (called_func == nullptr)
        continue;
      projection_str << indent_level << "rpc " << dbgutils::getFuncSigName(*dbgutils::getLowestDIType(*field_di_type), *called_func, field_var_name) << ";\n";
    }
    else
    {
      projection_str << indent_level << field_type_name << " " << access_attributes << " " << field_var_name << ";\n";
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
    auto proj_type_name = dbgutils::getSourceLevelTypeName(*node_di_type, true);
    while (proj_type_name.back() == '*')
    {
      proj_type_name.pop_back();
    }
    auto proj_var_name = dbgutils::getSourceLevelVariableName(*node_di_type);
    if (current_node->isRootNode())
      proj_var_name = dbgutils::getSourceLevelVariableName(*current_node->getDILocalVar());
    std::string str;
    raw_string_ostream projection_str(str);
    // for pointer to aggregate type, retrive the child node(pointed object), and generate projection
    if (dbgutils::isPointerType(*dbgutils::stripMemberTag(*node_di_type)) && !current_node->getChildNodes().empty())
      current_node = current_node->getChildNodes()[0];
    // errs() << "generate idl for node: " << proj_type_name << "\n";
    generateIDLFromTreeNode(*current_node, projection_str, node_queue, "\t\t");
    // handle funcptr ops struct specifically
    if (proj_type_name.find("_ops") != std::string::npos)
    {
      // if this is a op struct, generaete a projection for it
      if (_seen_func_ops.find(proj_type_name) != _seen_func_ops.end())
        continue;
      _seen_func_ops.insert(proj_type_name);
      std::string proj_str = "projection < struct " + proj_type_name + " > " + "_global_" + proj_type_name + " {\n " + projection_str.str() + "};\n";
      _ops_struct_proj_str += proj_str;
    }
    else
    {
      idl_file << "\tprojection < struct "
               << proj_type_name
               << " > "
               << proj_var_name
               << " {\n"
               << projection_str.str()
               << "\t};\n";
    }
  }
}

void pdg::DataAccessAnalysis::generateRpcForFunc(Function &F)
{
  FunctionWrapper *fw = _PDG->getFuncWrapperMap()[&F];
  std::string rpc_str = "";
  // generate function rpc stub
  // first generate for return value
  DIType* func_ret_di_type = fw->getReturnValDIType();
  std::string ret_type_str = "";
  if (func_ret_di_type != nullptr)
  {
    ret_type_str = dbgutils::getSourceLevelTypeName(*func_ret_di_type, true);
    if (dbgutils::isStructPointerType(*func_ret_di_type))
      ret_type_str = "projection ret_" + ret_type_str;
  }
  else
  {
    ret_type_str = "void";
  }

  rpc_str = "rpc " + ret_type_str + " " + F.getName().str() + "( ";
  auto arg_list = fw->getArgList();
  for (unsigned i = 0; i < arg_list.size(); i++)
  {
    auto arg = arg_list[i];
    auto formal_in_tree = fw->getArgFormalInTree(*arg);
    if (!formal_in_tree)
      continue;
    TreeNode* root_node = formal_in_tree->getRootNode();
    DIType* arg_di_type = root_node->getDIType();
    auto arg_name = dbgutils::getSourceLevelVariableName(*root_node->getDILocalVar());
    auto arg_type_name = dbgutils::getSourceLevelTypeName(*arg_di_type, true);
    if (dbgutils::isStructPointerType(*arg_di_type))
    {
      arg_type_name = "projection *";
      if (arg_type_name.find("_ops") != std::string::npos)
        arg_name = "_global_" + arg_type_name;
    }
    else if (dbgutils::isFuncPointerType(*arg_di_type))
    {
      if (_exported_funcs_ptr_name_map.find(arg_name) != _exported_funcs_ptr_name_map.end())
      {
        Function* called_func = _module->getFunction(_exported_funcs_ptr_name_map[arg_name]);
        if (called_func != nullptr)
        {
          arg_type_name = dbgutils::getFuncSigName(*arg_di_type, *called_func, arg_name);
          // also, no need to concate the arg_name
          arg_name = "";
        }
      }
    }

    auto annotations = inferTreeNodeAnnotations(*root_node);
    std::string anno_str = "";
    for (auto anno : annotations) 
      anno_str += anno;
    rpc_str = rpc_str + arg_type_name + " " + anno_str + " " + arg_name;
    if (i != arg_list.size() - 1)
      rpc_str += ", ";
  }
  rpc_str += " ) ";
  idl_file << rpc_str;
}

void pdg::DataAccessAnalysis::generateIDLForFunc(Function &F)
{
  auto func_wrapper_map = _PDG->getFuncWrapperMap();
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

std::set<std::string> pdg::DataAccessAnalysis::inferTreeNodeAnnotations(TreeNode &tree_node)
{
  std::set<std::string> annotations;
  if (tree_node.isRootNode())
  {
    if (_SDA->isFieldUsedInStringOps(tree_node))
      annotations.insert("[string]");
  }
  // for field, also check for global use info for this field
  else
  {
    auto field_id = pdgutils::computeTreeNodeID(tree_node);
    if (_SDA->isStringFieldID(field_id))
      annotations.insert("[string]");
  }
  return annotations;
}

static RegisterPass<pdg::DataAccessAnalysis>
    DAA("daa", "Data Access Analysis Pass", false, true);