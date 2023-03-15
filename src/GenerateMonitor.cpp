#include "GenerateMonitor.hh"
/*
This file generates a monitor used to instrument and enforce policies
*/

using namespace llvm;

char pdg::GenerateMonitorPass::ID = 0;

void pdg::GenerateMonitorPass::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

bool pdg::GenerateMonitorPass::runOnModule(Module &M)
{
  MonitorFile.open("Monitor.cpp");
  generateHeaders();
  // get the boundary API names
  std::set<std::string> boundaryAPINames;
  pdgutils::readLinesFromFile(boundaryAPINames, "boundaryAPI");
  generateTypeCastFuncTop();
  for (auto &F : M)
  {
      if (F.isDeclaration())
          continue;
      auto mangledFuncName = F.getName().str();
      auto demangledFuncName = pdgutils::getDemangledName(mangledFuncName.data());
      if (demangledFuncName.empty())
          demangledFuncName = mangledFuncName;
      if (boundaryAPINames.find(demangledFuncName) == boundaryAPINames.end())
          continue;
      generateTypeCastFuncBody(F);
  }
  generateTypeCastFuncBottom();
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
              << "#include <string>\n"
              << "#include <functional>\n"
              << "#include \"json.hpp\"\n";

  MonitorFile << "using json = nlohmann::json;\n";
  MonitorFile << "using namespace std;\n";
  MonitorFile << "std::set<std::string> checkID;\n";
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

void pdg::GenerateMonitorPass::collectStructTypes(DIType *rootTy, std::unordered_map<DIType *, std::string> &structTypes, std::string offsetStr, std::string &funcName)
{
  if (!rootTy || structTypes.count(rootTy))
    return;

  if (auto *structTy = dyn_cast<DICompositeType>(rootTy))
  {
    if (structTy->getTag() == dwarf::DW_TAG_structure_type ||
        structTy->getTag() == dwarf::DW_TAG_class_type)
    {
          structTypes.insert(std::make_pair(structTy, (funcName + "." + offsetStr)));
          for (auto *elemTy : structTy->getElements())
          {
              collectStructTypes(dyn_cast<DIType>(elemTy), structTypes, offsetStr, funcName);
          }
    }
  }
  else if (rootTy->getTag() == llvm::dwarf::DW_TAG_member)
  {
    auto *ptrTy = cast<DIDerivedType>(rootTy);
    auto fieldOffset = rootTy->getOffsetInBits() / 8;
    std::string newOffsetStr = offsetStr + "." + std::to_string(fieldOffset);
    collectStructTypes(ptrTy->getBaseType(), structTypes, newOffsetStr, funcName);
  }
  else if (auto *ptrTy = dyn_cast<DIDerivedType>(rootTy))
  {
    collectStructTypes(ptrTy->getBaseType(), structTypes, offsetStr, funcName);
  }
}

void pdg::GenerateMonitorPass::collectFuncParamsStructTys(std::unordered_map<DIType *, std::string> &structTypes, Function &F)
{
  for (auto argIter = F.arg_begin(); argIter != F.arg_end(); ++argIter)
  {
    auto argIdx = argIter->getArgNo();
    auto argDITy = getDebugTypeForParameter(F, argIdx);
    if (!argDITy)
          continue;
    auto funcName = F.getName().str();
    collectStructTypes(argDITy, structTypes, std::to_string(argIdx), funcName);
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

void pdg::GenerateMonitorPass::generateTypeCastFuncTop()
{
  MonitorFile << "void* castToType(std::string typeId, void* ptr) {\n";
  MonitorFile << "  std::hash<std::string> hashFunc;\n";
  MonitorFile << "  size_t strHash = hashFunc(typeId);\n";
  MonitorFile << "  switch (strHash) {\n";
}

void pdg::GenerateMonitorPass::generateTypeCasts(std::unordered_map<DIType *, std::string> &structTypes)
{
  std::hash<std::string> hashFunc;
  for (auto iter = structTypes.begin(); iter != structTypes.end(); iter++)
  {
    DIType* structTy = iter->first;
    std::string id = iter->second;
    MonitorFile << "    case " << hashFunc(id) << ": {\n";
    MonitorFile << "      return (void *)(*static_cast<" << getStructTypeName(structTy) << "**>(ptr));\n";
    MonitorFile << "    }\n";
  }
}

void pdg::GenerateMonitorPass::generateTypeCastFuncBottom()
{
  MonitorFile << "    default: {\n";
  MonitorFile << "      return nullptr;\n";
  MonitorFile << "    }\n";
  MonitorFile << "  }\n";
  MonitorFile << "}\n";
}

void pdg::GenerateMonitorPass::generateTypeCastFuncBody(Function &F)
{
  // compute all struct types reachable from the parameters
  std::unordered_map<DIType *, std::string> structTypes;
  collectFuncParamsStructTys(structTypes, F);
  // give a unique id for each type, and start generating a function
  generateTypeCasts(structTypes);
}

void pdg::GenerateMonitorPass::generateInstrumentFuncDefinitions()
{
  MonitorFile << "std::map<std::string, std::pair<unsigned, std::string>> fieldAccCapMap;\n";
  MonitorFile << R"(
    // receive a field addr, return the pointer stored on the address
// the fieldJSONObj stores the cap, and nested struct fields for the pointer field
void setupPolicyForAddr(void *addr, std::string offsetStr, json fieldJSONObj, std::string funcName)
{
    void *fieldPtrVal = castToType(offsetStr, addr);
    if (!fieldPtrVal)
      return;
    for (auto obj : fieldJSONObj["fields"])
    {
        if (!obj.contains("offset"))
            continue;
        std::string dbgStr = "";
        if (obj.contains("dbg"))
          dbgStr = obj["dbg"];
        auto offset = obj["offset"];
        auto accCap = obj["cap"];
        void *fieldAddr = static_cast<void *>(static_cast<char *>(fieldPtrVal) + offset);
        std::stringstream ss;
        ss << fieldAddr;
        std::string addrId = funcName + ss.str();
        fieldAccCapMap[addrId] = std::make_pair(accCap, dbgStr);
        if (obj.contains("fields")) {
            std::string newOffsetStr = offsetStr + "." + std::to_string((long long)offset);
            setupPolicyForAddr(fieldAddr, newOffsetStr, obj, funcName);
        }
    }
}

void setupArgAccessPolicy(void *baseAddr, unsigned argIdx, char* fName)
{
    std::string funcName(fName);
    std::string argID = funcName + std::to_string(argIdx);
    if (checkID.find(argID) != checkID.end())
      return;
    checkID.insert(argID);
    // load the field offset and it's access tag
    std::ifstream policyJSONFile("AccPolicy.json");
    json moduleJSONObj;
    policyJSONFile >> moduleJSONObj;
    // find the parameter based on the argIdx argument
    auto modulePolicyObjList = moduleJSONObj["policy"];
    auto funcJSONObjIter = std::find_if(modulePolicyObjList.begin(), modulePolicyObjList.end(), 
                            [funcName](const auto &obj) {
                                return obj["fname"] == funcName;
                            });
    if (funcJSONObjIter == modulePolicyObjList.end())
      return;
    cout << "setting up policy for func: " << funcName << "\n";
    json funcJSONObj = *funcJSONObjIter;
    auto it = std::find_if(funcJSONObj["args"].begin(), funcJSONObj["args"].end(),
                           [argIdx](const auto &obj)
                           {
                               return obj["idx"] == argIdx;
                           });
    // Check if the object was found
    if (it != funcJSONObj["args"].end())
    {
        // arg root object was found
        // retrive offset and access cap
        auto parentJSONObj = *it;
        for (auto obj : parentJSONObj["fields"])
        {
            auto offset = obj["offset"];
            auto accCap = obj["cap"];
            void *fieldAddr = static_cast<void *>(static_cast<char *>(baseAddr) + offset);
            std::string dbgStr = "";
            if (obj.contains("dbg"))
              dbgStr = obj["dbg"];
            std::stringstream ss;
            ss << fieldAddr;
            std::string addrId = funcName + ss.str();
            fieldAccCapMap[addrId] = std::make_pair(accCap, obj["dbg"]);
            // process pointer fields
             if (obj.contains("fields")) {
                auto offsetStr = funcName + "." + std::to_string((long long)argIdx) + "." + std::to_string((long long)offset);
                setupPolicyForAddr(fieldAddr, offsetStr, obj, funcName);
            }
        }
    }
}

void checkFieldAccessPolicy(void *fieldAddr, unsigned accTag, char* fName)
{
    std::stringstream ss;
    ss << fieldAddr;
    std::string funcName(fName);
    std::string addrId = funcName + ss.str();
    if (fieldAccCapMap.find(addrId) == fieldAccCapMap.end())
        return;
    auto accPair = fieldAccCapMap[addrId];
    auto policyAccTag = accPair.first;
    auto dbgStr = accPair.second;
    // allow both read and write, don't need to check
    if (policyAccTag == 3)
        return;
    if (policyAccTag == 0)
    {
        auto accTyStr = "READ";
        if (accTag == 2)
          accTyStr = "WRITE";
        // the policy says don't allow both read and write
        if (accTag != 0)
            std::cout << "\033[1;31m"
                      << "[Violation]: "
                      << "\033[0m"
                      << accTyStr
                      << " accessing illegal addr " 
                      << fieldAddr
                      << " ["
                      << dbgStr
                      << "]"
                      << std::endl;
    }
    else if (policyAccTag != accTag)
    {
        if (policyAccTag == 1)
            std::cout << "\033[1;31m"
                      << "[Violation]: "
                      << "\033[0m"
                      << "Writing to read-only addr " 
                      <<  fieldAddr
                      << " ["
                      << dbgStr 
                      << "]"
                      << std::endl;
        else if (policyAccTag == 2)
            std::cout << "\033[1;31m"
                      << "[Violation]: "
                      << "\033[0m"
                      << "Reading to write-only addr " 
                      <<  fieldAddr
                      << " ["
                      << dbgStr 
                      << "]"
                      << std::endl;
    }
}
)";
}

static RegisterPass<pdg::GenerateMonitorPass>
    PDG("monitor-gen", "Generate policy monitor", false, true);