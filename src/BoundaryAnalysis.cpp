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
    auto gv_di_type = di_gv->getType();
    auto gv_lowest_di_type = dbgutils::getLowestDIType(*gv_di_type);
    if (gv_lowest_di_type->getTag() != dwarf::DW_TAG_structure_type)
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
        if (!struct_element->getName().str().empty())
        {
          if (!dbgutils::isFuncPointerType(*struct_field_di_type))
            continue;
          std::string func_name = struct_element->getName().str();
          _exported_func_ptrs.push_back(dbgutils::getSourceLevelVariableName(*struct_field_di_type));
          _exported_funcs.push_back(func_name);
        }
        // TODO: handle nested structs
      }
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