#include "GenerateMonitor.hh"
/*
This file generates a monitor used to instrument and enforce policies
*/

using namespace llvm;

char pdg::GenerateMonitorPass::ID = 0;

extern cl::opt<std::string> TargetFuncName;

void pdg::GenerateMonitorPass::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

bool pdg::GenerateMonitorPass::runOnModule(Module &M)
{
  MonitorFile.open("Monitor.cpp");
  generateHeaders();
  for (auto &F : M)
  {
      if (F.isDeclaration())
          continue;
      auto funcName = pdgutils::getDemangledName(F.getName().str().data());
      if (funcName != TargetFuncName)
          continue;
      generateTypeCastFunc(F);
  }
  generateInstrumentFuncDefinitions();
  MonitorFile.close();
  return false;
}

void pdg::GenerateMonitorPass::generateHeaders()
{
  MonitorFile << "#include <iostream>\n"
              << "#include <vector>\n"
              << "#include <set>\n"
              << "#include <map>\n"
              << "#include <assert.h>\n"
              << "#include <fstream>\n"
              << "#include \"json.hpp\"\n";
  generateStructDefinitionHeaders();

  MonitorFile << "using json = nlohmann::json;\n";
  MonitorFile << "using namespace std;\n";
}

void pdg::GenerateMonitorPass::generateStructDefinitionHeaders()
{
  MonitorFile << "#include \"struct_def.h\"\n";
}

llvm::DIType *pdg::GenerateMonitorPass::getDebugTypeForParameter(Function &F, unsigned paramIndex)
{
  // Get the debug info for the function.
  DISubprogram *SP = F.getSubprogram();
  if (!SP)
      return nullptr;

  // Get the debug info for the parameter at the specified index.
  DITypeRefArray paramTypes = SP->getType()->getTypeArray();
  if (paramIndex + 1 >= paramTypes.size())
      return nullptr;

  DIType *paramType = paramTypes[paramIndex + 1];
  if (!paramType)
      return nullptr;

  // Check if the parameter is a pointer type.
  if (dbgutils::isPointerType(*paramType))
      paramType = dbgutils::getLowestDIType(*paramType);

  return paramType;
}

void pdg::GenerateMonitorPass::collectStructTypes(DIType *rootTy, std::unordered_set<DIType *> &structTypes)
{
  if (!rootTy || structTypes.count(rootTy))
    return;

  if (auto *structTy = dyn_cast<DICompositeType>(rootTy))
  {
    if (structTy->getTag() == dwarf::DW_TAG_structure_type ||
        structTy->getTag() == dwarf::DW_TAG_class_type)
    {
          structTypes.insert(structTy);
          for (auto *elemTy : structTy->getElements())
          {
              collectStructTypes(dyn_cast<DIType>(elemTy), structTypes);
          }
    }
  }
  else if (auto *ptrTy = dyn_cast<DIDerivedType>(rootTy))
  {
    collectStructTypes(ptrTy->getBaseType(), structTypes);
  }
}

void pdg::GenerateMonitorPass::collectFuncParamsStructTys(std::unordered_set<DIType *> &structTypes, Function &F)
{
  for (auto argIter = F.arg_begin(); argIter != F.arg_end(); ++argIter)
  {
    auto argIdx = argIter->getArgNo();
    auto argDITy = getDebugTypeForParameter(F, argIdx);
    if (!argDITy)
          continue;
    collectStructTypes(argDITy, structTypes);
  }
}

std::string pdg::GenerateMonitorPass::getStructTypeName(DIType* Ty) {
  if (!Ty)
    return "";

  if (auto* StructTy = dyn_cast<DICompositeType>(Ty)) {
    if (StructTy->getTag() == dwarf::DW_TAG_structure_type) {
      std::string TypeName = "struct " + StructTy->getName().str();
      return TypeName;
    }
  }

  return "";
}

void pdg::GenerateMonitorPass::generateCastFunction(std::unordered_set<DIType *> &structTypes)
{
  MonitorFile << "void* castToType(unsigned typeId, void* ptr) {\n";
  MonitorFile << "  switch (typeId) {\n";
  unsigned id = 0;
  for (auto ty : structTypes)
  {
    MonitorFile << "    case " << id++ << ": {\n";
    MonitorFile << "      return (void *)(*static_cast<" << getStructTypeName(ty) << "**>(ptr));\n";
    MonitorFile << "    }\n";
  }
  MonitorFile << "    default: {\n";
  MonitorFile << "      return nullptr;\n";
  MonitorFile << "    }\n";
  MonitorFile << "  }\n";
  MonitorFile << "}\n";
}

void pdg::GenerateMonitorPass::generateTypeCastFunc(Function &F)
{
  // compute all struct types reachable from the parameters
  std::unordered_set<DIType *> structTypes;
  collectFuncParamsStructTys(structTypes, F);
  // give a unique id for each type, and start generating a function
  generateCastFunction(structTypes);
}

void pdg::GenerateMonitorPass::generateInstrumentFuncDefinitions()
{
  MonitorFile << "std::map<void*, unsigned> fieldAccCapMap;\n";
  MonitorFile << R"(
    // receive a field addr, return the pointer stored on the address
// the fieldJSONObj stores the cap, and nested struct fields for the pointer field
void setupPolicyForAddr(void *addr, unsigned typeId, json fieldJSONObj)
{
    void *fieldPtrVal = castToType(typeId, addr);
    cout << "field addr " << addr << " deref addr " << fieldPtrVal << "\n";
    for (auto obj : fieldJSONObj["fields"])
    {
        if (!obj.contains("offset"))
            continue;
        auto offset = obj["offset"];
        auto accCap = obj["cap"];
        void *fieldAddr = static_cast<void *>(static_cast<char *>(fieldPtrVal) + offset);
        fieldAccCapMap[fieldAddr] = accCap;
        if (obj.contains("fields"))
            setupPolicyForAddr(fieldAddr, 0, obj);
    }
}

void setupArgAccessPolicy(void *baseAddr, unsigned argIdx)
{
    // load the field offset and it's access tag
    std::ifstream fieldAccFile("fieldAccFile.map");
    std::ifstream policyJSONFile("AccPolicy.json");
    json policyJSONObjList;
    policyJSONFile >> policyJSONObjList;
    // find the parameter based on the argIdx argument
    auto it = std::find_if(policyJSONObjList["args"].begin(), policyJSONObjList["args"].end(),
                           [argIdx](const auto &obj)
                           {
                               return obj["idx"] == argIdx;
                           });
    // Check if the object was found
    if (it != policyJSONObjList["args"].end())
    {
        // arg root object was found
        std::cout << "Found policy object with arg idx" << argIdx << std::endl;
        // retrive offset and access cap
        auto parentJSONObj = *it;
        for (auto obj : parentJSONObj["fields"])
        {
            auto offset = obj["offset"];
            auto accCap = obj["cap"];
            void *fieldAddr = static_cast<void *>(static_cast<char *>(baseAddr) + offset);
            fieldAccCapMap[fieldAddr] = accCap;
            // process pointer fields
            if (obj.contains("fields"))
                setupPolicyForAddr(fieldAddr, 0, obj);
        }
    }
}

void checkFieldAccessPolicy(void *fieldAddr, unsigned accTag)
{
    if (fieldAccCapMap.find(fieldAddr) == fieldAccCapMap.end())
        return;
    auto policyAccTag = fieldAccCapMap[fieldAddr];
    // allow both read and write, don't need to check
    if (policyAccTag == 3)
        return;
    if (policyAccTag == 0)
    {
        // the policy says don't allow both read and write
        if (accTag != 0)
            std::cout << "\033[1;31m"
                      << "[Violation]: "
                      << "\033[0m"
                      << "Accessing illegal addr." << std::endl;
    }
    else if (policyAccTag != accTag)
    {
        if (policyAccTag == 1)
            std::cout << "\033[1;31m"
                      << "[Violation]: "
                      << "\033[0m"
                      << "Writing to read-only addr " << fieldAddr << std::endl;
        else if (policyAccTag == 2)
            std::cout << "\033[1;31m"
                      << "[Violation]: "
                      << "\033[0m"
                      << "Reading to write-only addr" << fieldAddr << std::endl;
    }
}
)";
}

static RegisterPass<pdg::GenerateMonitorPass>
    PDG("monitor-gen", "Generate policy monitor", false, true);