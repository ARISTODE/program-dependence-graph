#include "eBPFProgGeneration.hpp"
using namespace llvm;
char pdg::EbpfGeneration::ID = 0;

cl::opt<std::string> TargetFuncName("target-func",
                                cl::desc("Specify the target function to analyze"),
                                cl::value_desc("function_name"),
                                cl::init(""));

bool pdg::EbpfGeneration::runOnModule(Module &M)
{
  // step 1: obtain access information for all functions in the module
  DAA = &getAnalysis<DataAccessAnalysis>();
  PDG = DAA->getPDG();
  // step 2: using the access information to generate policy
  std::set<std::string> boundaryAPINames;
  pdgutils::readLinesFromFile(boundaryAPINames, "boundaryAPI");

  std::string eBPFKernelFileName = "user_prog_check.c";
  std::string eBPFUserspaceFileName = "user_prog_check.py";
  EbpfKernelFile.open(eBPFKernelFileName);
  EbpfUserspaceFile.open(eBPFUserspaceFileName);
  
  // generate user program imports (py)
  generateUserProgImports(eBPFKernelFileName);
  // generate kernel program imports(c)
  generateKernelProgImports();

  for (auto &F : M)
  {
    if (F.isDeclaration())
      continue;
    // if (F.getName().str() != TargetFuncName)
    //   continue;
    std::string funcName = F.getName().str();
    if (boundaryAPINames.find(funcName) == boundaryAPINames.end())
      continue;
    generateEbpfMapOnFunc(F);
    generateEbpfUserProg(F);
    generateEbpfKernelProg(F);
  }

  generateTracePrint();

  EbpfKernelFile.close();
  EbpfUserspaceFile.close();

  return false;
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
  generateEbpfKernelExitProg(F);
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
  EbpfKernelFile << "#include <linux/version.h>"
                 << "\n";
  // generate includes for headers that contain the struct definitions
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
      continue;
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
  std::string structDefStr = "";
  auto structDIType = structNode.getDIType();
  auto structName = dbgutils::getSourceLevelTypeName(*structDIType);
  structDefStr = structName + "{\n";
  for (auto childNode : structNode.getChildNodes())
  {
    auto fieldDIType = childNode->getDIType();
    auto baseDIType = dbgutils::stripMemberTag(*fieldDIType);
    std::string fieldTypeStr = "";
    if (baseDIType && dbgutils::isStructPointerType(*baseDIType))
      fieldTypeStr = "void*";
    else
      fieldTypeStr = dbgutils::getSourceLevelTypeName(*fieldDIType);
    auto fieldNameStr = dbgutils::getSourceLevelVariableName(*fieldDIType);
    auto fieldStr = fieldTypeStr + " " + fieldNameStr;
    structDefStr = structDefStr + "\t" + fieldStr + ";\n";
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

std::string pdg::EbpfGeneration::createEbpfMapForType(DIType &dt)
{
  auto fieldType = dbgutils::stripMemberTag(dt);
  // we only handle map for 
  if (!fieldType)
    return "";
  auto fieldTypeStr = dbgutils::getSourceLevelTypeName(*fieldType);
  if (dbgutils::isPointerType(*fieldType))
    fieldTypeStr = "void*";
  else
    fieldTypeStr = switchType(fieldTypeStr);

  if (mapTypes.count(fieldTypeStr) > 0) {
    return "";
  }
  else
  {
    mapTypes.insert(fieldTypeStr);
    std::string typeStr = "";
    std::string mapName = "";

    // if the field is a pointer, we store this pointer to a void* map
    if (!hasPtrMap && dbgutils::isPointerType(*fieldType))
    {
      mapName = "void_ptr";
      typeStr = "void*";
      hasPtrMap = true;
    }
    else
    {
      auto elementType = dbgutils::getLowestDIType(*fieldType);
      if (elementType && !dbgutils::isPrimitiveType(*elementType))
        return "";
      mapName = elementType->getName().str();
      mapName = switchType(mapName);
      typeStr = dbgutils::getSourceLevelTypeName(*elementType);
    }
    // Create the eBPF map copy/ref definition string
    std::string mapDefinition = "BPF_HASH(";
    mapDefinition += mapName;
    mapDefinition += "_copy_map, u32, ";
    mapDefinition += typeStr;
    mapDefinition += ");\n";

    mapDefinition += "BPF_HASH(";
    mapDefinition += mapName;
    mapDefinition += "_ref_map, u32, ";
    mapDefinition += typeStr;
    mapDefinition += "*);";

    return mapDefinition;
  }
  return "";
}

void pdg::EbpfGeneration::generateEbpfMapOnArg(Tree &argTree)
{
  auto argRootNode = argTree.getRootNode();
  auto argDIType = argRootNode->getDIType();
  // only generate instrumentation on pointer type parameter
  if(!argDIType || !dbgutils::isPointerType(*argDIType))
    return;

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
      if (!fieldDt)
        continue;
      auto fieldMapStr = createEbpfMapForType(*fieldDt);
      if (!fieldMapStr.empty())
        EbpfKernelFile << fieldMapStr << "\n\n";
    }
  }
  else
  {
    // for non struct pointer type, we just get the lowest type, and then generate type map for it
    auto lowestDIType = dbgutils::getLowestDIType(*argDIType);
    if (!lowestDIType)
      return;
    auto mapStr = createEbpfMapForType(*lowestDIType);
    if (!mapStr.empty())
      EbpfKernelFile << mapStr << "\n\n";
  }
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

void pdg::EbpfGeneration::updateCopyMap(std::string fieldTypeStr, std::string fieldName, std::string fieldHierarchyName,
                   std::string typeCopyMap) {
    std::string tmpStackVarName = "tmp_" + fieldName;
    EbpfKernelFile << "\t" << fieldTypeStr << " " << tmpStackVarName << ";\n";
    EbpfKernelFile << "\t"
                   << "bpf_probe_read(&" << tmpStackVarName << ", "
                   << "sizeof(" << fieldTypeStr << "), &" 
                   << fieldHierarchyName
                   << ");\n";
    EbpfKernelFile << "\t" << typeCopyMap << ".update(&tmpFieldId" << ", &" << tmpStackVarName  << ");\n";
}

void pdg::EbpfGeneration::updateRefMap(std::string fieldTypeStr, std::string fieldName, std::string fieldHierarchyName,
                  std::string typeRefMap) {
    std::string tmpStackVarPtrName = "tmp_ptr_" + fieldName;
    EbpfKernelFile << "\t" << fieldTypeStr << "* " << tmpStackVarPtrName << ";\n";
    EbpfKernelFile << "\t" << tmpStackVarPtrName << " = &"  << fieldHierarchyName << ";\n";
    EbpfKernelFile << "\t" << typeRefMap << ".update(&tmpFieldId"
                   << ", &" << tmpStackVarPtrName << ");\n";
}

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

      if (dbgutils::isArrayType(*rawFieldDt) || dbgutils::isCompositeType(*rawFieldDt))
        continue;

      auto fieldTypeStr = dbgutils::getSourceLevelTypeName(*fieldDt);
      auto mapTypeStr = dbgutils::isPointerType(*fieldDt) ? "void_ptr" : switchType(fieldTypeStr);
      fieldTypeStr = dbgutils::isPointerType(*fieldDt) ? "void*" : mapTypeStr;

      auto fieldName = fieldNode->getSrcName();
      std::string fieldHierarchyName = fieldNode->getSrcHierarchyName();
      unsigned funcID = pdgutils::getFuncUniqueId(*F);
      unsigned fieldOffset = fieldDt->getOffsetInBits() / 8;
      unsigned uniqueFieldId = pdgutils::computeFieldUniqueId(funcID, argIdx, fieldOffset);

      EbpfKernelFile << "\ttmpFieldId = " << uniqueFieldId << ";\n";
      updateRefMap(fieldTypeStr, fieldName, fieldHierarchyName, mapTypeStr + "_ref_map");
      updateCopyMap(fieldTypeStr, fieldName, fieldHierarchyName, mapTypeStr + "_copy_map");
    }
  }
  else
  {
    // TODO: handle non-struct pointer types

  }
}

void pdg::EbpfGeneration::generateEbpfKernelEntryProgOnFunc(Function &F)
{
  auto funcWrapper = PDG->getFuncWrapper(F);
  assert(funcWrapper != nullptr && "");
  // generate entry trace func signature
  auto funcName = F.getName().str();
  EbpfKernelFile << "int "
                 << "uprobe_" << funcName << "( struct pt_regs *ctx";
  auto argNameStr = extractFuncArgStr(F);
  if (!argNameStr.empty())
    EbpfKernelFile << ", ";
  EbpfKernelFile << argNameStr << ") {\n";
  EbpfKernelFile << "\tuint64_t pid_tgid = bpf_get_current_pid_tgid();\n";
  
  // stack variable for holding the unique function id
  auto tmpFieldId = "tmpFieldId";
  EbpfKernelFile << "\tunsigned " << tmpFieldId << ";\n";

  auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
    unsigned argIdx = iter->first->getArgNo();
    generateEbpfKernelEntryProgOnArg(*iter->second, argIdx);
  }
  EbpfKernelFile << "\treturn 0;\n";
  EbpfKernelFile << "\t}\n\n";
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
  if(!argDIType || !dbgutils::isPointerType(*argDIType))
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
      auto mapTypeStr = dbgutils::isPointerType(*fieldDt) ? "void_ptr" : switchType(fieldTypeStr);
      fieldTypeStr = dbgutils::isPointerType(*fieldDt) ? "void*" : mapTypeStr;

      auto fieldName = fieldNode->getSrcName();
      unsigned funcID = pdgutils::getFuncUniqueId(*F);
      // offset in bytes
      unsigned fieldOffset = fieldDt->getOffsetInBits() / 8;
      // create a unique id for the field
      unsigned uniqueFieldId = pdgutils::computeFieldUniqueId(funcID, argIdx, fieldOffset);
      EbpfKernelFile << "\ttmpFieldId = " << uniqueFieldId << ";\n";
      // look up the ref value from ref map
      std::string ptrVarName = retriveFieldFromRefMap(fieldTypeStr, fieldName, mapTypeStr + "_ref_map");
      // look up the copy value from copy map
      std::string copyVarName = retriveFieldFromCopyMap(fieldTypeStr, fieldName, mapTypeStr + "_copy_map");
      
      // check if the retrived pointer is null
      EbpfKernelFile << "\tif (!" << ptrVarName << " || " << "!*" << ptrVarName  << " || " << "!" << copyVarName << ")\n" ;
      EbpfKernelFile << "\t\treturn 0;\n";

      EbpfKernelFile << "\tif (**" << ptrVarName << " != *" << copyVarName << "){\n" ;
      EbpfKernelFile << "\t\tbpf_trace_printk(\"illegal update read-only field " << fieldName << "\");\n";
      EbpfKernelFile << "\t}\n";
    }
  }
}

// generate checks at the exit of a function
void pdg::EbpfGeneration::generateEbpfKernelExitProg(Function &F)
{
  auto funcName = F.getName().str();
  EbpfKernelFile << "int "
                 << "uretprobe_" << funcName << "( struct pt_regs *ctx ) {\n";
  EbpfKernelFile << "\tuint64_t pid_tgid = bpf_get_current_pid_tgid();\n";
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

  //   // TODO: skip for now, need to create field maps
  //   auto objNode = rootNode->getChildNodes()[0];
  //   auto structDIType = objNode->getDIType();
  //   auto objSize = dbgutils::computeStructTypeStorageSize(*structDIType);
  //   if ((objSize / 8) >= 512)
  //     continue;  

  //   // strip the * at the end
  //   auto argObjTypeName = argTypeName;
  //   while (!argObjTypeName.empty() && argObjTypeName.back() == '*')
  //   {
  //     argObjTypeName.pop_back();
  //   }
  //   std::string argRefMapName = argName + "_ref_map";
  //   std::string argCopyMapName = argName + "_copy_map";
  //   auto argRefName = argName + "_ref";
  //   auto argCopyName = argName + "_copy";

  //   // store ref and copy for arg
  //   EbpfKernelFile << "\t"
  //                  << argObjTypeName << " **" << argRefName << " = "
  //                  << argRefMapName << ".lookup(&pid_tgid);\n";

  //   EbpfKernelFile << "\t"
  //                  << argObjTypeName << " *" << argCopyName << " = "
  //                  << argCopyMapName << ".lookup(&pid_tgid);\n";

  //   // place null check
  //   EbpfKernelFile << "\tif ("
  //                  << "!" << argRefName << " || !" << argCopyName << ") {\n";
  //   EbpfKernelFile << "\t\treturn 0;\n "
  //                  << "\t}\n\n";
  //   // creat a local copy, and copy the latest state from ref
  //   bool isStructType = dbgutils::isStructPointerType(*rootNode->getDIType());

  //   // generate access checks for the arg and fields
  //   generateEbpfFieldAccRules(*argTree, argRefName, argCopyName);

  //   // cleanup
  //   EbpfKernelFile << "\t" << argRefMapName << ".delete(&pid_tgid);\n";
  //   EbpfKernelFile << "\t" << argCopyMapName << ".delete(&pid_tgid);\n";
  // }

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
                     << argRefName << ")"<< fieldHierarchyName << " != "
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
  EbpfUserspaceFile << "b.attach_uprobe(name=\"  \", sym=\"" << F.getName().str() << "\", fn_name=\"" << entryEbpfProgName << "\")\n";
  EbpfUserspaceFile << "b.attach_uretprobe(name=\" \", sym=\"" << F.getName().str() << "\", fn_name=\"" << exitEbpfProgName << "\")\n";
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

std::string pdg::EbpfGeneration::switchType(std::string typeStr)
{
  if (typeStr == "long int" || typeStr == "signed long int")
    return "long";
  else if (typeStr == "unsigned long int" || typeStr == "long unsigned int")
    return "ulong";
  else if (typeStr == "short int" || typeStr == "signed short int")
    return "short";
  else if (typeStr == "unsigned short int" || typeStr == "unsigned short")
    return "ushort";
  else if (typeStr == "signed int" || typeStr == "int")
    return "int";
  else if (typeStr == "unsigned int")
    return "uint";
  else if (typeStr == "signed char" || typeStr == "char")
    return "char";
  else if (typeStr == "unsigned char")
    return "uchar";
  else if (typeStr == "double")
    return "double";
  else if (typeStr == "long double")
    return "ldouble";
  else if (typeStr == "float")
    return "float";
  else
    return typeStr;
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