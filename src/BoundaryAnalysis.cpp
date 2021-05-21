#include "BoundaryAnalysis.hh"

char pdg::BoundaryAnalysis::ID = 0;

using namespace llvm;

cl::opt<std::string> BlackListFileName("libfile", cl::desc("Lib file"), cl::value_desc("lib filename"));

void pdg::BoundaryAnalysis::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.setPreservesAll();
}

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
    _black_list_func_names.insert(line);
  }
}

void pdg::BoundaryAnalysis::computeDriverImportedFuncs(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
    {
      std::string func_name = F.getName().str();
      func_name = pdgutils::stripFuncNameVersionNumber(func_name);
      if (isBlackListFunc(func_name))
        continue;
      _imported_funcs.push_back(func_name);
    }
  }
}

void pdg::BoundaryAnalysis::computeDriverFuncs(Module &M)
{
  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    std::string func_name = F.getName().str();
    func_name = pdgutils::stripFuncNameVersionNumber(func_name);
    if (isBlackListFunc(func_name))
      continue;
    _driver_domain_funcs.push_back(func_name);
  }
}

void pdg::BoundaryAnalysis::computeExportedFuncs(Module &M)
{
  // read shared struct type names if exist
  std::set<std::string> shared_struct_type_names;
  std::ifstream shared_struct_name_file("shared_struct_types");
  if (shared_struct_name_file.good())
  {
    // read shared data types
    for (std::string line; std::getline(shared_struct_name_file, line);)
    {
      shared_struct_type_names.insert(line);
    }
  }

  // used to store driver global
  std::ofstream driver_global_struct_types("driver_global_struct_types");
  for (auto &global_var : M.getGlobalList())
  {
    SmallVector<DIGlobalVariableExpression *, 4> sv;
    if (!global_var.hasInitializer())
      continue;
    DIGlobalVariable *di_gv = nullptr;
    global_var.getDebugInfo(sv);
    for (auto di_expr : sv)
    {
      if (di_expr->getVariable()->getName() == global_var.getName())
        di_gv = di_expr->getVariable(); // get global variable from global expression
    }
    if (!di_gv)
      continue;
    if (!global_var.isConstant() && global_var.hasInitializer())
      _driver_globalvar_names.push_back(global_var.getName().str());
    auto gv_di_type = di_gv->getType();
    auto gv_lowest_di_type = dbgutils::getLowestDIType(*gv_di_type);
    if (!gv_lowest_di_type || gv_lowest_di_type->getTag() != dwarf::DW_TAG_structure_type)
      continue;
    auto gv_di_type_name = dbgutils::getSourceLevelTypeName(*gv_lowest_di_type, true);
    auto gv_name = global_var.getName().str();
    gv_di_type_name = pdgutils::stripVersionTag(gv_di_type_name);
    if (!shared_struct_type_names.empty() && shared_struct_type_names.find(gv_di_type_name) == shared_struct_type_names.end())
      continue;
    driver_global_struct_types << gv_di_type_name << "\n";
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
        if (pdgutils::isUserOfSentinelTypeVal(*struct_element))
          _sentinel_fields.push_back(dbgutils::getSourceLevelVariableName(*struct_field_di_type));

        if (!field_type_name.empty())
        {
          std::string field_source_name = dbgutils::getSourceLevelVariableName(*struct_field_di_type);
          // concate the ptr name with the outer ops struct name
          field_source_name = gv_di_type_name + "_" + field_source_name;
          if (dbgutils::isFuncPointerType(*struct_field_di_type))
          {
            _exported_func_ptrs.push_back(field_source_name);
            _exported_funcs.push_back(field_type_name);
            _global_op_struct_names.insert(gv_di_type_name);
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
      std::string func_name = name.erase(0, 10);
      Function *f = M.getFunction(StringRef(func_name));
      if (f != nullptr)
        _exported_func_symbols.insert(func_name);
    }
  }
}

void pdg::BoundaryAnalysis::dumpToFiles()
{
  errs() << "dumping to files\n";
  dumpToFile("imported_funcs", _imported_funcs);
  dumpToFile("driver_funcs", _driver_domain_funcs);
  dumpToFile("exported_funcs", _exported_funcs);
  dumpToFile("exported_func_ptrs", _exported_func_ptrs);
  dumpToFile("sentinel_fields", _sentinel_fields);
  dumpToFile("driver_globalvar_names", _driver_globalvar_names);
  std::vector<std::string> exported_func_symbols(_exported_func_symbols.begin(), _exported_func_symbols.end());
  dumpToFile("driver_exported_func_symbols", exported_func_symbols);
  std::vector<std::string> global_op_struct_names(_global_op_struct_names.begin(), _global_op_struct_names.end());
  dumpToFile("global_op_struct_names", global_op_struct_names);
}

void pdg::BoundaryAnalysis::dumpToFile(std::string file_name, std::vector<std::string> &names)
{
  std::ofstream output_file(file_name);
  for (auto name: names)
  {
    output_file << name << "\n";
  }
  output_file.close();
}

static RegisterPass<pdg::BoundaryAnalysis>
    BoundaryAnalysis("output-boundary-info", "Compute Isolation Boundary", false, true);