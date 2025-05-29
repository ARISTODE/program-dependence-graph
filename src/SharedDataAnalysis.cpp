#include "SharedDataAnalysis.hh"
#include "llvm/BinaryFormat/Dwarf.h"

using namespace llvm;

llvm::AnalysisKey pdg::SharedDataAnalysis::Key;

pdg::SharedDataAnalysis::Result pdg::SharedDataAnalysis::run(Module &M, ModuleAnalysisManager &MAM)
{
  _module = &M;
  // Get PDG analysis from previous result
  // Note: This will need to be updated when ProgramDependencyGraph is properly registered
  // _PDG = &MAM.getResult<ProgramDependencyGraph>(M).getPDG();
  _callGraph = &PDGCallGraph::getInstance();
  
  // read driver/kernel domian funcs
  setupStrOps();
  readSentinelFields();
  // insert driver global ops shared struct type
  readGlobalFuncOpStructNames();
  setupDriverFuncs(M);
  setupKernelFuncs(M);
  setupExportedFuncPtrFieldNames();
  // get boundary functions
  setupBoundaryFuncs(M);
  
  errs() << "Shared data analysis completed\n";
  return Result{true};
}

void pdg::SharedDataAnalysis::setupStrOps()
{
  _string_op_names.insert("strcpy");
  _string_op_names.insert("strncpy");
  _string_op_names.insert("strlen");
  _string_op_names.insert("strlcpy");
  _string_op_names.insert("strcmp");
  _string_op_names.insert("strchr");
  _string_op_names.insert("strncmp");
  _string_op_names.insert("strpbrk");
  _string_op_names.insert("kobject_set_name");
}

void pdg::SharedDataAnalysis::setupExportedFuncPtrFieldNames()
{
  std::ifstream driverExportedFuncPtrNames("exported_func_ptrs");
  for (std::string line; std::getline(driverExportedFuncPtrNames, line);)
  {
    exportedFuncPtrFieldNames.insert(line);
  }
}

void pdg::SharedDataAnalysis::setupDriverFuncs(Module &M)
{
  _driverDomainFuncs = readFuncsFromFile("driver_funcs", M, "boundaryFiles");
}

void pdg::SharedDataAnalysis::readDriverGlobalStrucTypes()
{
  std::ifstream driver_global_struct_types("boundaryFiles/driver_global_struct_types");
  for (std::string line; std::getline(driver_global_struct_types, line);)
  {
    _driver_global_struct_types.insert(line);
  }
}

void pdg::SharedDataAnalysis::setupKernelFuncs(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration() || F.empty())
      continue;
    // a special case is that driver function has module number concatenated, e.g., ixgbe_write_reg.5
    // neet to exclude such functions
    std::string funcName = F.getName().str();
    // ixgbe_write_reg.5 -> ixgbe_write_reg
    funcName = pdgutils::stripFuncNameVersionNumber(funcName);
    auto func = M.getFunction(StringRef(funcName));
    if (func == nullptr)
      continue;
    if (_driverDomainFuncs.find(func) == _driverDomainFuncs.end())
    {
      _kernelDomainFuncs.insert(func);
      _kernel_domain_func_names.insert(func->getName().str());
    }
  }
}

void pdg::SharedDataAnalysis::setupBoundaryFuncs(Module &M)
{
  auto imported_funcs = readFuncsFromFile("imported_funcs", M, "boundaryFiles");
  auto exported_funcs = readFuncsFromFile("exported_funcs", M, "boundaryFiles");

  _boundary_funcs.insert(imported_funcs.begin(), imported_funcs.end());
  _boundary_funcs.insert(exported_funcs.begin(), exported_funcs.end());
  // module init functions
  Function *init_func = getModuleInitFunc(M);
  if (init_func != nullptr)
    _boundary_funcs.insert(init_func);

  for (auto bf : _boundary_funcs)
  {
    _boundary_func_names.insert(bf->getName().str());
  }
}

std::set<Function *> pdg::SharedDataAnalysis::readFuncsFromFile(std::string fileName, Module &M, std::string dir)
{
  std::set<Function *> ret;
  sys::fs::file_status status;
  sys::fs::status("boundaryFiles", status);
  if (!dir.empty() && !sys::fs::exists(status) || !sys::fs::is_directory(status))
  {
    errs() << "boundary files don't exist, please run boundary analysis pass (-output-boundary-info) first\n";
    return ret;
  }

  auto fullPath = dir + "/" + fileName;
  std::ifstream ReadFile(fullPath);
  for (std::string line; std::getline(ReadFile, line);)
  {
    Function *f = M.getFunction(StringRef(line));
    if (!f)
      continue;
    if (f->isDeclaration() || f->empty())
      continue;
    ret.insert(f);
  }
  return ret;
}

void pdg::SharedDataAnalysis::computeSharedStructDITypes()
{
  // Implementation stub - requires full PDG integration
  errs() << "computeSharedStructDITypes: Implementation pending PDG integration\n";
}

void pdg::SharedDataAnalysis::computeGlobalStructTypeNames()
{
  for (auto &global_var : _module->globals())
  {
    SmallVector<DIGlobalVariableExpression *, 4> sv;
    if (!global_var.hasInitializer())
      continue;
    DIGlobalVariable *di_gv = nullptr;
    global_var.getDebugInfo(sv);
    for (auto di_expr : sv)
    {
      if (di_expr->getVariable()->getName().str() == global_var.getName().str())
        di_gv = di_expr->getVariable(); // get global variable from global expression
    }
    if (di_gv == nullptr)
      continue;
    auto gv_di_type = di_gv->getType();
    if (gv_di_type == nullptr)
      continue;
    auto gv_lowest_di_type = dbgutils::getLowestDIType(*gv_di_type);
    if (gv_lowest_di_type == nullptr || gv_lowest_di_type->getTag() != dwarf::DW_TAG_structure_type)
      continue;
    _global_struct_di_type_names.insert("struct " + dbgutils::getSourceLevelTypeName(*gv_di_type));
  }
}

void pdg::SharedDataAnalysis::buildTreesForSharedStructDIType(Module &M)
{
  // Implementation stub - requires full PDG integration
  errs() << "buildTreesForSharedStructDIType: Implementation pending PDG integration\n";
}

void pdg::SharedDataAnalysis::connectTypeTreeToAddrVars(Tree &type_tree)
{
  // Implementation stub - requires full PDG integration
  errs() << "connectTypeTreeToAddrVars: Implementation pending PDG integration\n";
}

void pdg::SharedDataAnalysis::computeVarsWithStructDITypeInFunc(DIType &dt, Function &F, std::set<Value *> &vars)
{
  // Implementation stub - requires full PDG integration
  errs() << "computeVarsWithStructDITypeInFunc: Implementation pending PDG integration\n";
}

std::set<Value *> pdg::SharedDataAnalysis::computeVarsWithStructDITypeInModule(DIType &dt, Module &M)
{
  std::set<Value *> vars;
  // Implementation stub
  return vars;
}

bool pdg::SharedDataAnalysis::isStructFieldNode(TreeNode &treeNode)
{
  // Implementation stub
  return false;
}

bool pdg::SharedDataAnalysis::isTreeNodeShared(TreeNode &treeNode)
{
  // Implementation stub
  return false;
}

bool pdg::SharedDataAnalysis::isFieldUsedInStringOps(TreeNode &treeNode)
{
  // Implementation stub
  return false;
}

bool pdg::SharedDataAnalysis::isSharedFieldID(std::string fieldId, std::string field_type_name)
{
  if (fieldId.empty())
    return false;
  return (_shared_field_id.find(fieldId) != _shared_field_id.end());
}

void pdg::SharedDataAnalysis::computeSharedFieldID()
{
  // Implementation stub - requires full PDG integration
  errs() << "computeSharedFieldID: Implementation pending PDG integration\n";
}

void pdg::SharedDataAnalysis::computeSharedGlobalVars()
{
  for (auto &global_var : _module->globals())
  {
    bool used_in_kernel = false;
    bool used_in_driver = false;
    for (auto user : global_var.users())
    {
      if (Instruction *i = dyn_cast<Instruction>(user))
      {
        auto func = i->getFunction();
        if (_kernelDomainFuncs.find(func) != _kernelDomainFuncs.end())
          used_in_kernel = true;
        else
          used_in_driver = true;
      }
      if (used_in_kernel && used_in_driver)
      {
        _shared_global_vars.insert(&global_var);
        break;
      }
    }
  }
}

void pdg::SharedDataAnalysis::dumpSharedFieldID()
{
  errs() << "dumping shared field id\n";
  for (auto id : _shared_field_id)
  {
    errs() << id << "\n";
  }
}

void pdg::SharedDataAnalysis::readSentinelFields()
{
  sys::fs::file_status status;
  sys::fs::status("boundaryFiles", status);
  if (!sys::fs::exists(status) || !sys::fs::is_directory(status))
  {
    errs() << "boundary files don't exist, please run boundary analysis pass (-output-boundary-info) first\n";
    return;
  }

  std::ifstream ReadFile("boundaryFiles/sentinel_fields");
  for (std::string line; std::getline(ReadFile, line);)
  {
    _sentinelFields.insert(line);
  }
}

void pdg::SharedDataAnalysis::readGlobalFuncOpStructNames()
{
  sys::fs::file_status status;
  sys::fs::status("boundaryFiles", status);
  if (!sys::fs::exists(status) || !sys::fs::is_directory(status))
  {
    errs() << "boundary files don't exist, please run boundary analysis pass (-output-boundary-info) first\n";
    return;
  }

  std::ifstream ReadFile("boundaryFiles/global_op_struct_names");
  for (std::string line; std::getline(ReadFile, line);)
  {
    _driver_func_op_struct_names.insert(line);
    _shared_struct_type_names.insert(line);
  }
}

Function *pdg::SharedDataAnalysis::getModuleInitFunc(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    std::string funcName = F.getName().str();
    if (funcName.find("_init_module") != std::string::npos)
      return &F;
  }
  return nullptr;
}

std::unordered_set<Function *> pdg::SharedDataAnalysis::computeBoundaryTransitiveClosure()
{
  // Implementation stub
  return std::unordered_set<Function *>();
}

std::unordered_set<Function *> pdg::SharedDataAnalysis::computeKernelInterfaceFuncTransitiveClosure()
{
  // Implementation stub
  return std::unordered_set<Function *>();
}

void pdg::SharedDataAnalysis::printPingPongCalls(Module &M)
{
  // Implementation stub
  errs() << "printPingPongCalls: Implementation stub\n";
}

void pdg::SharedDataAnalysis::dumpSharedTypes(std::string fileName)
{
  std::ofstream outputFile(fileName);
  for (auto shared_struct_type : _shared_struct_type_names)
  {
    if (!shared_struct_type.empty())
      outputFile << shared_struct_type << "\n";
  }
  outputFile.close();
}

void pdg::SharedDataAnalysis::collectSharedFieldsAccessStats()
{
  // Implementation stub
}

void pdg::SharedDataAnalysis::countReadWriteAccessTimes(TreeNode &treeNode)
{
  // Implementation stub
}

void pdg::SharedDataAnalysis::printDriverUpdateLocations(TreeNode &treeNode, llvm::raw_fd_ostream &OS)
{
  // Implementation stub
}

void pdg::SharedDataAnalysis::getDriverUpdateLocStr(TreeNode &treeNode, llvm::raw_string_ostream &ss)
{
  // Implementation stub
}

std::string pdg::SharedDataAnalysis::getFieldTypeStr(TreeNode &treeNode)
{
  // Implementation stub
  return "";
}

bool pdg::SharedDataAnalysis::usedInBranch(TreeNode &treeNode)
{
  // Implementation stub
  return false;
}

bool pdg::SharedDataAnalysis::isFuncPtr(TreeNode &treeNode)
{
  // Implementation stub
  return false;
}

bool pdg::SharedDataAnalysis::isDriverCallBackFuncPtrFieldNode(TreeNode &treeNode)
{
  // Implementation stub
  return false;
}

void pdg::SharedDataAnalysis::findKernelFuncsAccessType(std::string targetDtName, std::unordered_set<Function *> &funcs)
{
  // Implementation stub
}