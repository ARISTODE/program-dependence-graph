#include "BoundaryAnalysis.hh"

char pdg::BoundaryAnalysis::ID = 0;

using namespace llvm;

cl::opt<std::string> BlackListFileName("libfile", cl::desc("Lib file"), cl::value_desc("lib filename"));

void pdg::BoundaryAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.setPreservesAll();
}

std::set<std::string> remove_ops = {
    "ixgbe_eeprom_operations",
    "ixgbe_mac_operations",
    "ixgbe_mbx_operations",
    "ixgbe_phy_opeations"};

bool pdg::BoundaryAnalysis::runOnModule(Module &M)
{
  setupBlackListFuncNames();
  computeDriverImportedFuncs(M);
  computeDriverFuncs(M);
  computeExportedFuncs(M);
  computeExportedFuncSymbols(M);
  dumpToFiles();
  return false;
}

void pdg::BoundaryAnalysis::setupBlackListFuncNames()
{
  // some default filters
  _blackListFuncNames.insert("llvm");
  // read default library func list from liblcd_func.txt
  if (BlackListFileName.empty())
    BlackListFileName = "liblcd_funcs.txt";
  std::ifstream black_list_func_file(BlackListFileName);
  if (!black_list_func_file)
  {
    errs() << "fail to locate black list function file!\n";
    return;
  }

  for (std::string line; std::getline(black_list_func_file, line);)
  {
    _blackListFuncNames.insert(line);
  }
}

void pdg::BoundaryAnalysis::computeDriverImportedFuncs(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    if (pdgutils::isFuncDefinedInHeaderFile(F))
      continue;
    for (auto iIter = inst_begin(F); iIter != inst_end(F); ++iIter)
    {
      if (auto CI = dyn_cast<CallInst>(&*iIter))
      {
        auto calledFunc = pdgutils::getCalledFunc(*CI);
        if (!calledFunc)
          continue;
        if (calledFunc->isDeclaration())
        {
          std::string funcName = calledFunc->getName().str();
          funcName = pdgutils::stripFuncNameVersionNumber(funcName);
          // if (isBlackListFunc(funcName))
          //   continue;

          if (std::find(_importedFuncs.begin(), _importedFuncs.end(), funcName) == _importedFuncs.end())
          {
            _importedFuncs.push_back(funcName);
          }
        }
      }
    }
  }
}

void pdg::BoundaryAnalysis::computeDriverFuncs(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    std::string funcName = F.getName().str();
    funcName = pdgutils::stripFuncNameVersionNumber(funcName);
    // if (isBlackListFunc(funcName))
    //   continue;
    _driverDomainFuncs.push_back(funcName);
  }
  // consider all library functions as driver funcs
  // _driverDomainFuncs.insert(std::end(_driverDomainFuncs), std::begin(_blackListFuncNames), std::end(_blackListFuncNames));
}

void pdg::BoundaryAnalysis::computeExportedFuncs(Module &M)
{
  // read shared struct type names if exist
  std::set<std::string> shared_struct_type_names;
  std::ifstream shared_struct_name_file("boundaryFiles/shared_struct_types");
  if (shared_struct_name_file.good())
  {
    // read shared data types
    for (std::string line; std::getline(shared_struct_name_file, line);)
    {
      shared_struct_type_names.insert(line);
    }
  }

  // used to store driver global
  std::ofstream driver_global_struct_types("boundaryFiles/driver_global_struct_types");
  for (auto &global_var : M.getGlobalList())
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
    if (!di_gv)
      continue;
    if (!global_var.isConstant() && global_var.hasInitializer())
      _driverGlobalVarNames.push_back(global_var.getName().str());
    auto gv_di_type = di_gv->getType();
    auto gv_lowest_di_type = dbgutils::getLowestDIType(*gv_di_type);
    if (!gv_lowest_di_type || gv_lowest_di_type->getTag() != dwarf::DW_TAG_structure_type)
      continue;
    auto gv_di_type_name = dbgutils::getSourceLevelTypeName(*gv_lowest_di_type, true);
    auto gv_name = global_var.getName().str();
    gv_di_type_name = pdgutils::stripVersionTag(gv_di_type_name);
    // if (!shared_struct_type_names.empty() && shared_struct_type_names.find(gv_di_type_name) == shared_struct_type_names.end())
    //   continue;
    driver_global_struct_types << gv_di_type_name << "\n";
    if (remove_ops.find(gv_di_type_name) != remove_ops.end())
      continue;

    const auto &typeArrRef = dyn_cast<DICompositeType>(gv_lowest_di_type)->getElements();
    Type *global_type = global_var.getType();
    if (auto t = dyn_cast<PointerType>(global_type))
      global_type = t->getPointerElementType();
    if (!global_type->isStructTy())
      continue;
    if (global_type->getStructNumElements() != typeArrRef.size())
      continue;
    for (unsigned i = 0; i < global_type->getStructNumElements(); ++i)
    {
      auto struct_element = global_var.getInitializer()->getAggregateElement(i);
      if (struct_element == nullptr)
        continue;
      if (DIType *struct_field_di_type = dyn_cast<DIType>(typeArrRef[i]))
      {
        // if the field is a function pointer, directly print it to map
        std::string field_type_name = struct_element->getName().str();
        // if a field is a user of sentinel array (hold the content of sentinel array), then we need to record it
        // and synchronize this field with special syntax in IDL generation
        // if (pdgutils::isUserOfSentinelTypeVal(*struct_element))
        //   _sentinelFields.push_back(dbgutils::getSourceLevelVariableName(*struct_field_di_type));

        // extract all the function pointer name exported by the driver
        if (!field_type_name.empty())
        {
          std::string field_source_name = dbgutils::getSourceLevelVariableName(*struct_field_di_type);
          // concate the ptr name with the outer ops struct name
          field_source_name = gv_di_type_name + "_" + field_source_name;
          if (dbgutils::isFuncPointerType(*struct_field_di_type))
          {
            _exportedFuncPtrs.push_back(field_source_name);
            _exportedFuncs.push_back(field_type_name);
            _globalOpStructNames.insert(gv_di_type_name);
          }
        }
        // TODO: handle nested structs
      }
    }
  }
}

void pdg::BoundaryAnalysis::computeExportedFuncSymbols(Module &M)
{
  for (auto &gv : M.getGlobalList())
  {
    auto name = gv.getName().str();
    // look for global name starts with __ksymtab or __kstrtab
    if (name.find("__ksymtab_") == 0 || name.find("__kstrtab_") == 0)
    {
      std::string funcName = name.erase(0, 10);
      Function *f = M.getFunction(StringRef(funcName));
      if (f != nullptr)
        _exportedFuncSymbols.insert(funcName);
    }
  }
}

void pdg::BoundaryAnalysis::dumpToFiles()
{
  sys::fs::file_status status;
  sys::fs::status("boundaryFiles", status);
  if (!sys::fs::exists(status) || !sys::fs::is_directory(status))
  {
    // Directory does not exist, create it
    sys::fs::create_directory("boundaryFiles", sys::fs::perms::all_perms);
  }

  // Dump data to files
  dumpToFile("boundaryFiles/imported_funcs", _importedFuncs);
  dumpToFile("boundaryFiles/driver_funcs", _driverDomainFuncs);
  dumpToFile("boundaryFiles/exported_funcs", _exportedFuncs);
  dumpToFile("boundaryFiles/exported_func_ptrs", _exportedFuncPtrs);
  dumpToFile("boundaryFiles/sentinel_fields", _sentinelFields);
  dumpToFile("boundaryFiles/driver_globalvar_names", _driverGlobalVarNames);

  std::vector<std::string> exported_func_symbols(_exportedFuncSymbols.begin(), _exportedFuncSymbols.end());
  dumpToFile("boundaryFiles/driver_exported_func_symbols", exported_func_symbols);

  std::vector<std::string> global_op_struct_names(_globalOpStructNames.begin(), _globalOpStructNames.end());
  dumpToFile("boundaryFiles/global_op_struct_names", global_op_struct_names);
}

void pdg::BoundaryAnalysis::dumpToFile(std::string fileName, std::vector<std::string> &names)
{
  std::ofstream outputFile(fileName);
  for (auto name : names)
  {
    outputFile << name << "\n";
  }
  outputFile.close();
}

static RegisterPass<pdg::BoundaryAnalysis>
    BoundaryAnalysis("output-boundary-info", "Compute Isolation Boundary", false, true);