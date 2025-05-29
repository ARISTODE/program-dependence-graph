#include "eBPFProgGeneration.hpp"
#include <fstream>

using namespace llvm;
char pdg::EbpfGeneration::ID = 0;

cl::opt<std::string> InterfaceFuncsPath("ifuncs",
                                cl::desc("Specify the path of the instrumented binary"),
                                cl::value_desc("target bin path to instrument"),
                                cl::init(""));

cl::opt<std::string> TargetBinPath("binpath",
                                cl::desc("Specify the path of the instrumented binary"),
                                cl::value_desc("target bin path to instrument"),
                                cl::init(""));

bool pdg::EbpfGeneration::runOnModule(Module &M)
{
  // step 1: obtain access information for all functions in the module
  DAA = &getAnalysis<DataAccessAnalysis>();
  PDG = DAA->getPDG();
  
  // step 2: using the access information to generate policy

  std::string eBPFKernelFileName = "prog.ebpf.c"; // this is the source code
  std::string eBPFUserspaceFileName = "prog.py"; // this is the userspace code that loads the ebpf program
  EbpfKernelFile.open(eBPFKernelFileName);
  EbpfUserspaceFile.open(eBPFUserspaceFileName);
  
  // generate user program imports (py)
  generateUserProgImports(eBPFKernelFileName);
  // generate kernel program imports(c)
  generateKernelProgImports();

  std::set<std::string> ifuncNames;
  pdgutils::readLinesFromFile(ifuncNames, InterfaceFuncsPath);
  std::set<Function*> interfaceFuncs;
  for (auto ifuncName : ifuncNames)
  {
    auto func = M.getFunction(StringRef(ifuncName));
    if (func)
      interfaceFuncs.insert(func);
  }

  // generate helper functions
  generateHelperFuncs();

  for (auto f : interfaceFuncs)
  {
    Function &F = *f;
    if (F.isDeclaration())
      continue;
    // generateEbpfMapOnFunc(F);
    generateEbpfUserProg(F);
    generateEbpfKernelProg(F);
  }

  generateTracePrint();

  EbpfKernelFile.close();
  EbpfUserspaceFile.close();

  return false;
}

// generate helper functions
void pdg::EbpfGeneration::generateHelperFuncs()
{
  EbpfKernelFile << "// Struct definitions for map values\n"
                 << "struct s64_value {\n"
                 << "    s64 state;\n"
                 << "    s64* addr;\n"
                 << "};\n"
                 << "\n"
                 << "struct u64_value {\n"
                 << "    u64 state;\n"
                 << "    u64* addr;\n"
                 << "};\n"
                 << "\n"
                 << "struct s32_value {\n"
                 << "    s32 state;\n"
                 << "    s32* addr;\n"
                 << "};\n"
                 << "\n"
                 << "struct u32_value {\n"
                 << "    u32 state;\n"
                 << "    u32* addr;\n"
                 << "};\n"
                 << "\n"
                 << "struct s16_value {\n"
                 << "    s16 state;\n"
                 << "    s16* addr;\n"
                 << "};\n"
                 << "\n"
                 << "struct u16_value {\n"
                 << "    u16 state;\n"
                 << "    u16* addr;\n"
                 << "};\n"
                 << "\n"
                 << "struct s8_value {\n"
                 << "    s8 state;\n"
                 << "    s8* addr;\n"
                 << "};\n"
                 << "\n"
                 << "struct u8_value {\n"
                 << "    u8 state;\n"
                 << "    u8* addr;\n"
                 << "};\n";

  // forward declarations
  EbpfKernelFile << "// Map declarations for all types\n"
                 << "BPF_HASH(s64_map, u32, struct s64_value);\n"
                 << "BPF_HASH(u64_map, u32, struct u64_value);\n"
                 << "BPF_HASH(s32_map, u32, struct s32_value);\n"
                 << "BPF_HASH(u32_map, u32, struct u32_value);\n"
                 << "BPF_HASH(s16_map, u32, struct s16_value);\n"
                 << "BPF_HASH(u16_map, u32, struct u16_value);\n"
                 << "BPF_HASH(s8_map, u32, struct s8_value);\n"
                 << "BPF_HASH(u8_map, u32, struct u8_value);\n";

  // code for storing value to global map
   EbpfKernelFile << "// Enum for representing types\n"
                   << "enum value_type {\n"
                   << "    TYPE_S64,\n"
                   << "    TYPE_U64,\n"
                   << "    TYPE_S32,\n"
                   << "    TYPE_U32,\n"
                   << "    TYPE_S16,\n"
                   << "    TYPE_U16,\n"
                   << "    TYPE_S8,\n"
                   << "    TYPE_U8\n"
                   << "};\n"
                   << "\n";

   EbpfKernelFile << "static void store_value(u32 tmpFieldId, void* state, void* addr, enum value_type type) {\n"
                  << "    switch (type) {\n"
                  << "        case TYPE_S64:\n"
                  << "            {\n"
                  << "                struct s64_value value = {\n"
                  << "                    .state = *(s64*)state,\n"
                  << "                    .addr = addr\n"
                  << "                };\n"
                  << "                s64_map.update(&tmpFieldId, &value);\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_U64:\n"
                  << "            {\n"
                  << "                struct u64_value value = {\n"
                  << "                    .state = *(u64*)state,\n"
                  << "                    .addr = addr\n"
                  << "                };\n"
                  << "                u64_map.update(&tmpFieldId, &value);\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_S32:\n"
                  << "            {\n"
                  << "                struct s32_value value = {\n"
                  << "                    .state = *(s32*)state,\n"
                  << "                    .addr = addr\n"
                  << "                };\n"
                  << "                s32_map.update(&tmpFieldId, &value);\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_U32:\n"
                  << "            {\n"
                  << "                struct u32_value value = {\n"
                  << "                    .state = *(u32*)state,\n"
                  << "                    .addr = addr\n"
                  << "                };\n"
                  << "                u32_map.update(&tmpFieldId, &value);\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_S16:\n"
                  << "            {\n"
                  << "                struct s16_value value = {\n"
                  << "                    .state = *(s16*)state,\n"
                  << "                    .addr = addr\n"
                  << "                };\n"
                  << "                s16_map.update(&tmpFieldId, &value);\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_U16:\n"
                  << "            {\n"
                  << "                struct u16_value value = {\n"
                  << "                    .state = *(u16*)state,\n"
                  << "                    .addr = addr\n"
                  << "                };\n"
                  << "                u16_map.update(&tmpFieldId, &value);\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_S8:\n"
                  << "            {\n"
                  << "                struct s8_value value = {\n"
                  << "                    .state = *(s8*)state,\n"
                  << "                    .addr = addr\n"
                  << "                };\n"
                  << "                s8_map.update(&tmpFieldId, &value);\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_U8:\n"
                  << "            {\n"
                  << "                struct u8_value value = {\n"
                  << "                    .state = *(u8*)state,\n"
                  << "                    .addr = addr\n"
                  << "                };\n"
                  << "                u8_map.update(&tmpFieldId, &value);\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        default:\n"
                  << "            break;\n"
                  << "    }\n"
                  << "}\n"
                  << "\n"
                  << "static void check_field(u32 unique_field_id, enum value_type type) {\n"
                  << "    switch (type) {\n"
                  << "        case TYPE_S64:\n"
                  << "            {\n"
                  << "                struct s64_value *value = s64_map.lookup(&unique_field_id);\n"
                  << "                if (value != NULL) {\n"
                  << "                    s64 current_state;\n"
                  << "                    bpf_probe_read(&current_state, sizeof(s64), value->addr);\n"
                  << "                    if (value->state != current_state) {\n"
                  << "                        bpf_trace_printk(\"illegal update\");\n"
                  << "                    }\n"
                  << "                }\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_U64:\n"
                  << "            {\n"
                  << "                struct u64_value *value = u64_map.lookup(&unique_field_id);\n"
                  << "                if (value != NULL) {\n"
                  << "                    u64 current_state;\n"
                  << "                    bpf_probe_read(&current_state, sizeof(u64), value->addr);\n"
                  << "                    if (value->state != current_state) {\n"
                  << "                        bpf_trace_printk(\"illegal update\");\n"
                  << "                    }\n"
                  << "                }\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_S32:\n"
                  << "            {\n"
                  << "                struct s32_value *value = s32_map.lookup(&unique_field_id);\n"
                  << "                if (value != NULL) {\n"
                  << "                    s32 current_state;\n"
                  << "                    bpf_probe_read(&current_state, sizeof(s32), value->addr);\n"
                  << "                    if (value->state != current_state) {\n"
                  << "                        bpf_trace_printk(\"illegal update\");\n"
                  << "                    }\n"
                  << "                }\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_U32:\n"
                  << "            {\n"
                  << "                struct u32_value *value = u32_map.lookup(&unique_field_id);\n"
                  << "                if (value != NULL) {\n"
                  << "                    u32 current_state;\n"
                  << "                    bpf_probe_read(&current_state, sizeof(u32), value->addr);\n"
                  << "                    if (value->state != current_state) {\n"
                  << "                        bpf_trace_printk(\"illegal update\");\n"
                  << "                    }\n"
                  << "                }\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_S16:\n"
                  << "            {\n"
                  << "                struct s16_value *value = s16_map.lookup(&unique_field_id);\n"
                  << "                if (value != NULL) {\n"
                  << "                    s16 current_state;\n"
                  << "                    bpf_probe_read(&current_state, sizeof(s16), value->addr);\n"
                  << "                    if (value->state != current_state) {\n"
                  << "                        bpf_trace_printk(\"illegal update\");\n"
                  << "                    }\n"
                  << "                }\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_U16:\n"
                  << "            {\n"
                  << "                struct u16_value *value = u16_map.lookup(&unique_field_id);\n"
                  << "                if (value != NULL) {\n"
                  << "                    u16 current_state;\n"
                  << "                    bpf_probe_read(&current_state, sizeof(u16), value->addr);\n"
                  << "                    if (value->state != current_state) {\n"
                  << "                        bpf_trace_printk(\"illegal update\");\n"
                  << "                    }\n"
                  << "                }\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_S8:\n"
                  << "            {\n"
                  << "                struct s8_value *value = s8_map.lookup(&unique_field_id);\n"
                  << "                if (value != NULL) {\n"
                  << "                    s8 current_state;\n"
                  << "                    bpf_probe_read(&current_state, sizeof(s8), value->addr);\n"
                  << "                    if (value->state != current_state) {\n"
                  << "                        bpf_trace_printk(\"illegal update\");\n"
                  << "                    }\n"
                  << "                }\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        case TYPE_U8:\n"
                  << "            {\n"
                  << "                struct u8_value *value = u8_map.lookup(&unique_field_id);\n"
                  << "                if (value != NULL) {\n"
                  << "                    u8 current_state;\n"
                  << "                    bpf_probe_read(&current_state, sizeof(u8), value->addr);\n"
                  << "                    if (value->state != current_state) {\n"
                  << "                        bpf_trace_printk(\"illegal update\");\n"
                  << "                    }\n"
                  << "                }\n"
                  << "            }\n"
                  << "            break;\n"
                  << "        default:\n"
                  << "            break;\n"
                  << "    }\n"
                  << "}\n";
}

void pdg::EbpfGeneration::generateEbpfKernelProg(Function &F)
{
  generateFuncStructDefinition(F);
  // generate struct type definitions accessed through the parameters of F
  // generateSturctTypeDefsForFunc(F);
  // generate ref/copy maps for F
  // generateFuncArgRefCopyMaps(F);
  // generate perf output
  // generatePerfOutput();
  // generate uprobe functions, which stores the references and copy to the parameters
  generateEbpfKernelEntryProgOnFunc(F);
  // generate uretprobe functions, which performs checks on the parameters
  generateEbpfKernelRetProbe(F);
}

void pdg::EbpfGeneration::generateKernelProgImports()
{
  // these are generic headers that need to be included by every
  // ebpf kernel program. Uses may need to add corresponding files that contains
  // parameter definitions manually.
  EbpfKernelFile << "#include <uapi/linux/bpf.h>"
                 << "\n";
  EbpfKernelFile << "#include <uapi/linux/ptrace.h>"
                 << "\n";
  // EbpfKernelFile << "<linux/netdevice.h>" << "\n";
  EbpfKernelFile << "#include <linux/version.h>" << "\n";
  // provide u1 - u32
  EbpfKernelFile << "#include <linux/types.h>" << "\n";
  // generate includes for headers that contain the struct definitions
}

std::string getEnumTypeString(const std::string& typeStr) {
    static const std::unordered_map<std::string, std::string> typeToEnumMap = {
        {"s64", "TYPE_S64"},
        {"u64", "TYPE_U64"},
        {"s32", "TYPE_S32"},
        {"u32", "TYPE_U32"},
        {"s16", "TYPE_S16"},
        {"u16", "TYPE_U16"},
        {"s8", "TYPE_S8"},
        {"u8", "TYPE_U8"}
    };

    auto it = typeToEnumMap.find(typeStr);
    if (it != typeToEnumMap.end()) {
        return it->second;
    }

    return "";
}

void pdg::EbpfGeneration::generateFuncStructDefinition(Function &F)
{
  auto funcWrapper = PDG->getFuncWrapper(F);
  auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
  std::string argStr = "";
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    auto argTree = iter->second;
    auto rootNode = argTree->getRootNode();
    auto rootDIType = rootNode->getDIType();

    if (!rootDIType || !dbgutils::isStructPointerType(*rootDIType))
      continue;

    auto structDIType = rootNode->getChildNodes()[0]->getDIType();
    if (!structDIType)
    {
      errs() << "[Warning]: cannot find struct ditype " << F.getName() << "\n";
      continue;
    }
    auto structDefName = dbgutils::getSourceLevelTypeName(*structDIType);
    if (structDefNames.find(structDefName) != structDefNames.end())
      continue;
    structDefNames.insert(structDefName);
    if (dbgutils::isStructPointerType(*rootDIType))
    {
      generateStructDefString(*rootNode->getChildNodes()[0]);
    }
  }
}

// for each struct type, we generate the definition for this type.
void pdg::EbpfGeneration::generateStructDefString(TreeNode &structNode)
{
  // The generation of the type should be limited to the first level struct definition,
  // however, if the struct contains pointer to other struct, we replace the pointer to void*
  // this avoid bringing in more types
  Function *func = structNode.getFunc();
  std::string structDefStr = "";
  auto structDIType = structNode.getDIType();
  auto structName = dbgutils::getSourceLevelTypeName(*structDIType);
  structDefStr = structName + "{\n";
  for (auto childNode : structNode.getChildNodes())
  {
    auto fieldDIType = childNode->getDIType();
    auto actualFieldDIType = dbgutils::stripMemberTagAndAttributes(*fieldDIType);
    auto fieldNameStr = dbgutils::getSourceLevelVariableName(*fieldDIType);
    // process function ptr field
    if (dbgutils::isFuncPointerType(*actualFieldDIType))
    {
      structDefStr = structDefStr + "\t" + dbgutils::getFuncSigName(*actualFieldDIType, *func, fieldNameStr) + ";\n";
    }
    else
    {
      // if the element type is aggregate type, we replace it with array of
      if (dbgutils::isStructType(*actualFieldDIType))
      {
        auto fieldByteSize = actualFieldDIType->getSizeInBits() / 8;
        std::string fieldStr = "char " + fieldNameStr + "[" + std::to_string(fieldByteSize) + "]";
        structDefStr = structDefStr + "\t" + fieldStr + ";\n";
      }
      else
      {
        std::string fieldTypeStr = "";
        // all pointers are replaced with void pointer primitive/struct ptrs -> void*
        if (actualFieldDIType && dbgutils::isStructPointerType(*actualFieldDIType))
        {
          fieldTypeStr = "u64*";
        }
        else
        {
          fieldTypeStr = switchType(dbgutils::getSourceLevelTypeName(*fieldDIType, false, fieldNameStr));
        }
        auto fieldStr = fieldTypeStr + " " + fieldNameStr;
        structDefStr = structDefStr + "\t" + fieldStr + ";\n";
      }
    }
  }
  structDefStr += "};";

  EbpfKernelFile << structDefStr << "\n";
}

void pdg::EbpfGeneration::generateFuncArgRefCopyMaps(Function &F)
{
  auto funcWrapper = PDG->getFuncWrapper(F);
  auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
  std::string argStr = "";
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    auto argTree = iter->second;
    auto rootNode = argTree->getRootNode();
    auto argName = rootNode->getSrcName();
    auto argTypeName = rootNode->getTypeName();
    generateArgRefCopyMaps(argName, argTypeName);
  }
}

void pdg::EbpfGeneration::generateArgRefCopyMaps(std::string argName, std::string argTypeName)
{
  auto argRefMapName = argName + "_ref_map";
  auto argCopyMapName = argName + "_copy_map";

  // strip the * at the end
  auto argObjTypeName = argTypeName;
  while (!argObjTypeName.empty() && argObjTypeName.back() == '*')
  {
    argObjTypeName.pop_back();
  }

  if (mapNames.find(argRefMapName) == mapNames.end())
  {
    // ref map
    EbpfKernelFile << "BPF_HASH("
                   << argRefMapName
                   << ", u64, "
                   << argTypeName
                   << ");"
                   << "\n";
    mapNames.insert(argRefMapName);
  }

  if (mapNames.find(argCopyMapName) == mapNames.end())
  {
    // copy map
    EbpfKernelFile << "BPF_HASH("
                   << argCopyMapName
                   << ", u64, "
                   << argObjTypeName
                   << ");"
                   << "\n\n";
    mapNames.insert(argCopyMapName);
  }
}

void pdg::EbpfGeneration::generatePerfOutput()
{
  EbpfKernelFile << "BPF_PERF_OUTPUT("
                 << "output);"
                 << "\n\n";
}

/*
Example map:
struct field_value {
    u64 state;
    u64 address;
};

BPF_HASH(field_map, u32, struct field_value, MAX_ENTRIES);
*/

std::string pdg::EbpfGeneration::createEbpfMapForType(DIType &dt)
{
  auto fieldType = dbgutils::stripMemberTag(dt);
  if (!fieldType)
    return "";

  if (isUnspportedTypes(*fieldType))
    return "";

  auto fieldTypeStr = dbgutils::getSourceLevelTypeName(*fieldType);

  // use u64 to store pointer value
  if (dbgutils::isPointerType(*fieldType))
    fieldTypeStr = "u64";
  else
    fieldTypeStr = switchType(fieldTypeStr);

  if (mapTypes.count(fieldTypeStr) > 0)
    return "";

  std::string mapName = "";
  // handle pointer type value
  if (!hasPtrMap && dbgutils::isPointerType(*fieldType))
  {
    mapName = "u64";
    hasPtrMap = true;
  }
  else
  {
    auto elementType = dbgutils::getLowestDIType(*fieldType);
    if (!elementType || dbgutils::isPrimitiveType(*elementType))
      return "";

    mapName = switchType(elementType->getName().str());
  }

  mapTypes.insert(fieldTypeStr);
  return getMapDefinition(mapName);
}

// used to generate map for the argument.
// for each encountered arg, field, determine if the type is supported or not
// if is supported type, then create a map for that type
void pdg::EbpfGeneration::generateEbpfMapOnArg(Tree &argTree)
{
  auto argRootNode = argTree.getRootNode();
  auto argDIType = argRootNode->getDIType();

  // Only generate instrumentation on pointer type parameter
  if (!argDIType || !dbgutils::isPointerType(*argDIType))
    return;

  if (dbgutils::isStructPointerType(*argDIType))
  {
    generateEbpfMapForStructPointer(argRootNode);
  }
  else
  {
    generateEbpfMapForNonStructPointer(argDIType);
  }
}

void pdg::EbpfGeneration::generateEbpfMapForStructPointer(TreeNode *argRootNode)
{
  auto structObjNode = argRootNode->getStructObjNode();
  if (!structObjNode)
    return;

  for (auto fieldNode : structObjNode->getChildNodes())
  {
    auto fieldDt = fieldNode->getDIType();
    if (!fieldDt)
      continue;

    auto fieldMapStr = createEbpfMapForType(*fieldDt);
    if (!fieldMapStr.empty())
      EbpfKernelFile << fieldMapStr << "\n\n";
  }
}

void pdg::EbpfGeneration::generateEbpfMapForNonStructPointer(DIType *argDIType)
{
  auto lowestDIType = dbgutils::getLowestDIType(*argDIType);
  if (!lowestDIType)
    return;

  auto mapStr = createEbpfMapForType(*lowestDIType);
  if (!mapStr.empty())
    EbpfKernelFile << mapStr << "\n\n";
}

void pdg::EbpfGeneration::generateEbpfMapOnFunc(Function &F)
{
  auto funcWrapper = PDG->getFuncWrapper(F);
  assert(funcWrapper != nullptr && "");
  // generate entry trace func signature
  auto funcName = F.getName().str();
  auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    generateEbpfMapOnArg(*iter->second);
  }
}

void pdg::EbpfGeneration::updateMap(std::string fieldHierarchyName, std::string typeMapStr)
{
  std::string mapName = typeMapStr + "_map";
  std::string valueName = typeMapStr + "_value";
  // code for defining struct
  EbpfKernelFile << "\tstruct " << typeMapStr << "_value " << "value" << " = {\n"
                 << "\t\t.state = " << fieldHierarchyName << ", \n"
                 << "\t\t.addr = &" << fieldHierarchyName << "\n"
                 << "\t};\n";

  // code for update the map
  EbpfKernelFile << "\t" << mapName << ".update(&tmpFieldId, &" << valueName << ");\n";
}

// void pdg::EbpfGeneration::updateCopyMap(std::string fieldTypeStr, std::string fieldName, std::string fieldHierarchyName,
//                    std::string typeCopyMap) {
//     std::string tmpStackVarName = "tmp_" + fieldName;
//     EbpfKernelFile << "\t" << fieldTypeStr << " " << tmpStackVarName << ";\n";
//     EbpfKernelFile << "\t"
//                    << "bpf_probe_read(&" << tmpStackVarName << ", "
//                    << "sizeof(" << fieldTypeStr << "), &"
//                    << fieldHierarchyName
//                    << ");\n";
//     EbpfKernelFile << "\t" << typeCopyMap << ".update(&tmpFieldId" << ", &" << tmpStackVarName  << ");\n";
// }

// void pdg::EbpfGeneration::updateRefMap(std::string fieldTypeStr, std::string fieldName, std::string fieldHierarchyName,
//                   std::string typeRefMap) {
//     std::string tmpStackVarPtrName = "tmp_ptr_" + fieldName;
//     EbpfKernelFile << "\t" << fieldTypeStr << "* " << tmpStackVarPtrName << ";\n";
//     EbpfKernelFile << "\t" << tmpStackVarPtrName << " = &"  << fieldHierarchyName << ";\n";
//     EbpfKernelFile << "\t" << typeRefMap << ".update(&tmpFieldId"
//                    << ", &" << tmpStackVarPtrName << ");\n";
// }

std::string pdg::EbpfGeneration::retriveFieldFromRefMap(std::string fieldTypeStr, std::string fieldName, std::string typeRefMap)
{
  // retrive the pointer
  std::string tmpStackVarPtrName = "tmp_ptr_" + fieldName;
  EbpfKernelFile << "\t" << fieldTypeStr << "** "
                 << tmpStackVarPtrName << " = "
                 << typeRefMap
                 << ".lookup(&tmpFieldId);\n";
  return tmpStackVarPtrName;
}

std::string pdg::EbpfGeneration::retriveFieldFromCopyMap(std::string fieldTypeStr, std::string fieldName, std::string typeCopyMap)
{
  std::string tmpStackVarName = "tmp_" + fieldName;
  EbpfKernelFile << "\t" << fieldTypeStr << "* "
                 << tmpStackVarName << " = "
                 << typeCopyMap
                 << ".lookup(&tmpFieldId);\n";
  return tmpStackVarName;
}

void pdg::EbpfGeneration::generateEbpfKernelEntryProgOnArg(Tree &argTree, unsigned argIdx)
{
  // only generate instrumentation on pointer type parameter
  auto argRootNode = argTree.getRootNode();
  auto argDIType = argRootNode->getDIType();
  if (!argDIType || !dbgutils::isPointerType(*argDIType))
    return;

  Function *F = argTree.getFunc();
  if (dbgutils::isStructPointerType(*argDIType))
  {
    auto structObjNode = argRootNode->getStructObjNode();
    if (!structObjNode)
      return;

    for (auto fieldNode : structObjNode->getChildNodes())
    {
      auto fieldDt = fieldNode->getDIType();
      auto rawFieldDt = dbgutils::stripMemberTagAndAttributes(*fieldDt);

      // skip the check for unsupported data type
      if (isUnspportedTypes(*rawFieldDt))
        continue;

      auto fieldTypeStr = dbgutils::getSourceLevelTypeName(*fieldDt);
      auto mapTypeStr = dbgutils::isPointerType(*fieldDt) ? "u64" : switchType(fieldTypeStr);
      fieldTypeStr = dbgutils::isPointerType(*fieldDt) ? "u64*" : switchType(mapTypeStr);

      auto fieldName = fieldNode->getSrcName();
      std::string fieldHierarchyName = fieldNode->getSrcHierarchyName();
      unsigned funcID = pdgutils::getFuncUniqueId(*F);
      unsigned fieldOffset = fieldDt->getOffsetInBits() / 8;
      unsigned uniqueFieldId = pdgutils::computeFieldUniqueId(funcID, argIdx, fieldOffset);
      EbpfKernelFile << "\ttmpFieldId = " << uniqueFieldId << ";\n";

      // record the field state and a reference to the field, if the field is non-writable
      // TODO: as an optimization, we should check if this field is read by the trusted compartment. If not, then there is no need to protect it
      if (!fieldNode->hasWriteAccess())
      {
        std::string fieldAddrStr = "&" + fieldHierarchyName;
        EbpfKernelFile << "\tstore_value(tmpFieldId, " << fieldAddrStr << ", " << fieldAddrStr << ", " << getEnumTypeString(mapTypeStr) << ");\n";
        // updateMap(fieldHierarchyName, mapTypeStr);
      }

      // if a field is non-readable by the callee domain, we should just ensure this field contain random info, instead of leaking things.
      // TODO: need to also record the updated value, this requires extra overhead
      // if (!fieldNode->hasReadAccess())
      // {
      //   if (dbgutils::isPointerType(*fieldDt) || dbgutils::isPrimitiveType(*fieldDt))
      //   {
      //     // for pointers and other numeric ty pes, generate a random number and store that to the field
      //     EbpfKernelFile << "\trand_val = bpf_get_prandom_u32();\n";
      //     EbpfKernelFile << "\tif (bpf_probe_write_user(&" << fieldHierarchyName << ", &rand_val, sizeof(rand_val))"
      //                    << " != 0 ) {\n ";
      //     EbpfKernelFile << "\t\tbpf_trace_printk(\"bpf_probe_write_user fail, " << fieldHierarchyName << "\\n\");\n";
      //     EbpfKernelFile << "\t\treturn 0;\n";
      //     EbpfKernelFile << "\t}\n";
      //   }
      // }
    }
  }
  else
  {
  }
}

void pdg::EbpfGeneration::generateEbpfKernelEntryProgOnFunc(Function &F)
{
  auto funcWrapper = PDG->getFuncWrapper(F);
  assert(funcWrapper != nullptr && "");

  // Generate entry trace func signature
  auto funcName = F.getName().str();
  std::string entryTraceFuncSignature = "int uprobe_" + funcName + "(struct pt_regs *ctx";
  auto argNameStr = extractFuncArgStr(F);
  if (!argNameStr.empty())
    entryTraceFuncSignature += ", " + argNameStr;
  entryTraceFuncSignature += ") {\n";
  EbpfKernelFile << entryTraceFuncSignature;

  // Declare stack variables
  EbpfKernelFile << "\tunsigned tmpFieldId;\n";
  EbpfKernelFile << "\tu32 randVal;\n";

  // Generate eBPF kernel entry program for each argument
  auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    unsigned argIdx = iter->first->getArgNo();
    generateEbpfKernelEntryProgOnArg(*iter->second, argIdx);
  }

  // Return 0 and close the function
  EbpfKernelFile << "\treturn 0;\n";
  EbpfKernelFile << "}\n\n";
}

void pdg::EbpfGeneration::generateAttacks(std::string argTypeName, std::string argName, Tree &argTree)
{
  // generate attack to replace various byte in the target object, this might casuing the orignal program to crash
  std::string byteArgName = "byte_" + argName;
  EbpfKernelFile << "    // Generate attacks\n";
  EbpfKernelFile << "    unsigned objectSize = sizeof(" << argTypeName << ");;\n";
  EbpfKernelFile << "    // Cast to byte array representation\n";
  EbpfKernelFile << "    char* " << byteArgName << " = (char*)" << argName << ";\n";
  EbpfKernelFile << "    for (int i = 0; i < objectSize; i++)\n"
                 << "    {\n"
                 << "        u32 random_value = bpf_get_prandom_u32();\n"
                 << "        int increment_decrement = random_value % 2;\n"
                 << "        char current_byte;\n"
                 << "        bpf_probe_read_user(&current_byte, sizeof(current_byte), (void *)(" << byteArgName << " + i));\n"
                 << "        if (increment_decrement == 1) { current_byte++; }\n"
                 << "        else { current_byte--; }\n"
                 << "        bpf_probe_write_user((void *)(" << byteArgName << "+ i), &current_byte, sizeof(current_byte));\n"
                 << "    }\n";

  // generate attack to replace a non-writable pointer field with null pointer
  std::queue<TreeNode *> nodeQ;
  nodeQ.push(argTree.getRootNode());

  while (!nodeQ.empty())
  {
    TreeNode *curNode = nodeQ.front();
    nodeQ.pop();
    // enqueue all child nodes
    for (auto childNode : curNode->getChildNodes())
    {
      if (curNode->getDepth() < 3)
        nodeQ.push(childNode);
    }

    if (curNode->getDepth() <= 3 && !curNode->hasWriteAccess() && curNode->isStructMember())
    {
      auto fieldName = argName + curNode->getSrcHierarchyName(true, true);
      // replace the pointer with NULL pointer
      // EbpfKernelFile << "\tbpf_probe_write_user(&" << fieldName << ", &(void *){NULL}, sizeof(void*));\n";
    }
  }
}

void pdg::EbpfGeneration::generateEbpfAccessChecksOnArg(Tree &argTree, unsigned argIdx)
{
  // generate checks on arguments
  auto argRootNode = argTree.getRootNode();
  auto argDIType = argRootNode->getDIType();
  if (!argDIType || !dbgutils::isPointerType(*argDIType))
    return;

  Function *F = argTree.getFunc();
  if (dbgutils::isStructPointerType(*argDIType))
  {
    // for struct pointer, we iterate through each field and then check if the the field's type
    // has corresponding map. Pointers are recorded in a map with void* value, and other fields are recorded
    // to maps that have corresponding value types
    // the key is funcid + arg no + offset
    auto structObjNode = argRootNode->getStructObjNode();
    if (!structObjNode)
      return;

    for (auto fieldNode : structObjNode->getChildNodes())
    {
      auto fieldDt = fieldNode->getDIType();
      auto rawFieldDt = dbgutils::stripMemberTagAndAttributes(*fieldDt);

      if (dbgutils::isArrayType(*rawFieldDt) || dbgutils::isPointerType(*rawFieldDt) || dbgutils::isCompositeType(*rawFieldDt))
        continue;

      auto fieldTypeStr = dbgutils::getSourceLevelTypeName(*fieldDt);
      auto mapTypeStr = dbgutils::isPointerType(*fieldDt) ? "u64" : switchType(fieldTypeStr);
      fieldTypeStr = dbgutils::isPointerType(*fieldDt) ? "u64" : mapTypeStr;

      auto fieldName = fieldNode->getSrcName();
      unsigned funcID = pdgutils::getFuncUniqueId(*F);
      // offset in bytes
      unsigned fieldOffset = fieldDt->getOffsetInBits() / 8;
      // create a unique id for the field
      unsigned uniqueFieldId = pdgutils::computeFieldUniqueId(funcID, argIdx, fieldOffset);
      // EbpfKernelFile << "\ttmpFieldId = " << uniqueFieldId << ";\n";
      EbpfKernelFile << "\tcheck_field(" << uniqueFieldId << ", " << getEnumTypeString(mapTypeStr) << ");\n";
      // look up the value struct
      // std::string valueStr = mapTypeStr + "_value";
      // EbpfKernelFile << "\tstruct " << fieldTypeStr << "* "
      //                << valueStr << " = "
      //                << mapTypeStr << "_map"
      //                << ".lookup(&tmpFieldId);\n";

      // EbpfKernelFile << "\tbpf_probe_read(&current_state , sizeof(" << fieldTypeStr << ", " << mapTypeStr << "_value->addr);\n";
      // // generate code for comparing the current state and old state
      // std::string warningStr = "Illegal update " + fieldName;
      // EbpfKernelFile << "\tif (" << mapTypeStr << "_value->state != " << "current_state) {\n"
      //                << "\t\tbpf_trace_printk(\"illegal update" << warningStr << "\");\n"
      //                << "\t}\n";

      // look up the ref value from ref map
      // std::string ptrVarName = retriveFieldFromRefMap(fieldTypeStr, fieldName, mapTypeStr + "_ref_map");
      // // look up the copy value from copy map
      // std::string copyVarName = retriveFieldFromCopyMap(fieldTypeStr, fieldName, mapTypeStr + "_copy_map");

      // // check if the retrived pointer is null, a requirement by eBPF program
      // EbpfKernelFile << "\tif (!" << ptrVarName << " || " << "!*" << ptrVarName  << " || " << "!" << copyVarName << ")\n" ;
      // EbpfKernelFile << "\t\treturn 0;\n";

      // EbpfKernelFile << "\tif (**" << ptrVarName << " != *" << copyVarName << "){\n" ;
      // EbpfKernelFile << "\t\tbpf_trace_printk(\"illegal update read-only field " << fieldName << "\");\n";
      // EbpfKernelFile << "\t}\n";
    }
  }
}

// generate checks at the exit of a function
void pdg::EbpfGeneration::generateEbpfKernelRetProbe(Function &F)
{
  auto funcName = F.getName().str();
  EbpfKernelFile << "int "
                 << "uretprobe_" << funcName << "( struct pt_regs *ctx ) {\n";
  // EbpfKernelFile << "\tuint64_t pid_tgid = bpf_get_current_pid_tgid();\n";
  auto tmpFieldId = "tmpFieldId";
  EbpfKernelFile << "\tunsigned " << tmpFieldId << ";\n";
  // extract reference and copy
  auto funcWrapper = PDG->getFuncWrapper(F);
  assert(funcWrapper != nullptr && "");
  auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    auto arg = iter->first;
    if (!arg->getType()->isPointerTy())
      continue;
    auto argTree = iter->second;
    auto rootNode = argTree->getRootNode();
    auto argName = rootNode->getSrcName();
    auto argTypeName = rootNode->getTypeName();
    generateEbpfAccessChecksOnArg(*argTree, arg->getArgNo());
  }

  EbpfKernelFile << "\treturn 0;\n";
  EbpfKernelFile << "}\n\n";
}

void pdg::EbpfGeneration::generateEbpfFieldAccRules(Tree &argTree, std::string argRefName, std::string argCopyName)
{
  auto func = argTree.getFunc();
  auto funcName = func->getName().str();
  std::queue<TreeNode *> nodeQ;
  nodeQ.push(argTree.getRootNode());

  while (!nodeQ.empty())
  {
    TreeNode *curNode = nodeQ.front();
    nodeQ.pop();
    // enqueue all child nodes
    if (curNode->getDepth() <= 3)
    {
      for (auto childNode : curNode->getChildNodes())
      {
        nodeQ.push(childNode);
      }
    }
    if (!curNode->isStructMember())
      continue;
    // for each node check if the node is ptr type
    auto dt = curNode->getDIType();
    if (!dt)
      continue;
    // check a read-only pointer is not updated
    if (!curNode->hasWriteAccess())
    {
      auto fieldHierarchyName = curNode->getSrcHierarchyName(true, true);
      auto copyHierarchyName = argCopyName + fieldHierarchyName;
      auto fieldTypeName = dbgutils::getSourceLevelTypeName(*dt);
      EbpfKernelFile << "\tif ((*"
                     << argRefName << ")" << fieldHierarchyName << " != "
                     << copyHierarchyName
                     << ") {\n";
      EbpfKernelFile << "\t\tbpf_trace_printk(\"illegal update read-only field " << copyHierarchyName << "\");\n";
      // restoring the states
      EbpfKernelFile << "\t\tbpf_probe_write_user(&(*" << argRefName << ")" << fieldHierarchyName << ", &" << copyHierarchyName << ", sizeof(" << fieldTypeName << "));"
                     << "\n";
      EbpfKernelFile << "\t}\n\n";
    }
  }
}

// ----- generate userspace program
void pdg::EbpfGeneration::generateEbpfUserProg(Function &F)
{
  generateProbeAttaches(F);
}

void pdg::EbpfGeneration::generateUserProgImports(std::string kernelProgFileName)
{
  EbpfUserspaceFile << "from bcc import BPF\n";
  EbpfUserspaceFile << "from ctypes import cast, POINTER, c_char\n\n";
  // create bpf object

  EbpfUserspaceFile << "include_path = \"-I/usr/include/\"\n";
  EbpfUserspaceFile << "def_path = \"-I/usr/include/clang/10/include/\"\n";
  EbpfUserspaceFile << "b = BPF(src_file=\"" << kernelProgFileName << "\""
                    << ", cflags=[\"-O2\", include_path, def_path], debug=0"
                    << ")\n\n";
}

void pdg::EbpfGeneration::generateProbeAttaches(Function &F)
{
  auto entryEbpfProgName = "uprobe_" + F.getName().str();
  auto exitEbpfProgName = "uretprobe_" + F.getName().str();
  EbpfUserspaceFile << "b.attach_uprobe(name=\"" << TargetBinPath << "\", sym=\"" << F.getName().str() << "\", fn_name=\"" << entryEbpfProgName << "\")\n";
  EbpfUserspaceFile << "b.attach_uretprobe(name=\"" << TargetBinPath << "\", sym=\"" << F.getName().str() << "\", fn_name=\"" << exitEbpfProgName << "\")\n";
}

void pdg::EbpfGeneration::generateTracePrint()
{
  EbpfUserspaceFile << "while True:\n";
  EbpfUserspaceFile << "  try:\n";
  EbpfUserspaceFile << "    b.trace_print()\n";
  EbpfUserspaceFile << "  except KeyboardInterrupt:\n";
  EbpfUserspaceFile << "    break\n";
}

void pdg::EbpfGeneration::getAnalysisUsage(AnalysisUsage &AU) const
{
  AU.addRequired<DataAccessAnalysis>();
  AU.setPreservesAll();
}

std::string pdg::EbpfGeneration::extractFuncArgStr(Function &F)
{
  auto funcWrapper = PDG->getFuncWrapper(F);
  auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
  std::string argStr = "";
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    auto argTree = iter->second;
    auto rootNode = argTree->getRootNode();
    auto argName = rootNode->getSrcName();
    auto argTypeName = rootNode->getTypeName();
    auto tmpStr = argTypeName + " " + argName;
    if (std::distance(iter, argTreeMap.end()) != 1)
      tmpStr += ", ";
    argStr += tmpStr;
  }
  return argStr;
}

bool pdg::EbpfGeneration::isUnspportedTypes(DIType &dt)
{
  auto rawFieldDt = dbgutils::stripMemberTagAndAttributes(dt);
  if (dbgutils::isArrayType(*rawFieldDt) ||
      dbgutils::isCompositeType(*rawFieldDt) ||
      dbgutils::isUnionType(*rawFieldDt))
    return true;
  return false;
}

std::string pdg::EbpfGeneration::getMapDefinition(const std::string &mapName)
{
  std::stringstream struct_def_ss;
  struct_def_ss << "struct " << mapName << "_value {\n"
                << "\t" << mapName << " state;\n"
                << "\t" << mapName << "* addr;\n"
                << "};\n";

  std::stringstream map_def_ss;
  map_def_ss << "BPF_HASH("
             << mapName << "_map, "
             << "u32, "
             << "struct " << mapName << "_value"
             << ");\n";

  return struct_def_ss.str() + map_def_ss.str();
}

std::string pdg::EbpfGeneration::switchType(const std::string &typeStr)
{
  static const std::unordered_map<std::string, std::string> typeMapping = {
      {"long int", "s64"},
      {"signed long int", "s64"},
      {"unsigned long int", "u64"},
      {"long unsigned int", "u64"},
      {"short int", "s16"},
      {"signed short int", "s16"},
      {"unsigned short int", "u16"},
      {"unsigned short", "u16"},
      {"signed int", "s32"},
      {"int", "s32"},
      {"unsigned int", "u32"},
      {"signed char", "s8"},
      {"char", "s8"},
      {"unsigned char", "u8"},
      {"double", "s64"},
      {"long double", "s64"},
      {"float", "s32"}};

  auto it = typeMapping.find(typeStr);
  if (it != typeMapping.end())
  {
    return it->second;
  }
  else
  {
    return typeStr;
  }
}

// generate checks at the entry of a function
// void pdg::EbpfGeneration::generateEbpfKernelEntryProgOnFunc(Function &F)
// {
//   // for entry program, we check the following rules:
//   auto funcWrapper = PDG->getFuncWrapper(F);
//   assert(funcWrapper != nullptr && "");
//   // generate entry trace func signature
//   auto funcName = F.getName().str();
//   EbpfKernelFile << "int "
//                  << "uprobe_" << funcName << "( struct pt_regs *ctx";
//   auto argNameStr = extractFuncArgStr(F);
//   if (!argNameStr.empty())
//     EbpfKernelFile << ", ";
//   EbpfKernelFile << argNameStr << ") {\n";
//   EbpfKernelFile << "\tuint64_t pid_tgid = bpf_get_current_pid_tgid();\n";

//   auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
//   for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
//   {
//     auto arg = iter->first;
//     if (!arg->getType()->isPointerTy())
//       continue;
//     auto argTree = iter->second;
//     auto rootNode = argTree->getRootNode();
//     auto argName = rootNode->getSrcName();
//     auto argTypeName = rootNode->getTypeName();
//     auto objNode = rootNode->getChildNodes()[0];
//     auto structDIType = objNode->getDIType();

//     // strip the * at the end
//     auto argObjTypeName = argTypeName;
//     while (!argObjTypeName.empty() && argObjTypeName.back() == '*')
//     {
//       argObjTypeName.pop_back();
//     }
//     std::string argRefMapName = argName + "_ref_map";
//     std::string argCopyMapName = argName + "_copy_map";
//     std::string argCopyName = argName + "_copy";

//     // generate a local copy for the argument, this is required by ebpf
//     bool isStructType = dbgutils::isStructPointerType(*rootNode->getDIType());
//     EbpfKernelFile << "\t" << argObjTypeName
//                    << " " << argCopyName;
//     if (isStructType)
//       EbpfKernelFile << " = {};\n";
//     else
//       EbpfKernelFile << ";\n";

//     EbpfKernelFile << "\tbpf_probe_read(&" << argCopyName
//                    << ", "
//                    << "sizeof("
//                    << argObjTypeName
//                    << "), " << argName
//                    << ");\n";

//     // store ref and copy for arg
//     EbpfKernelFile << "\t" << argRefMapName << ".update(&pid_tgid"
//                    << ", "
//                    << "&" << argName << ");\n";

//     EbpfKernelFile << "\t" << argCopyMapName << ".update(&pid_tgid"
//                    << ", "
//                    << "&" << argCopyName << ");\n";
//     // inject attacks towards the original program
//     // generateAttacks(argObjTypeName, argName, *argTree);
//   }

//   EbpfKernelFile << "\treturn 0;\n";
//   EbpfKernelFile << "}\n\n";
// }

static RegisterPass<pdg::EbpfGeneration>
    EBPFGEN("ebpf-gen", "eBPF Instrumentation Program Generation", false, true);