#include "eBPFProgGeneration.hpp"
using namespace llvm;
char pdg::EbpfGeneration::ID = 0;


bool pdg::EbpfGeneration::runOnModule(Module &M)
{
    // step 1: obtain access information for all functions in the module
    DAA = &getAnalysis<DataAccessAnalysis>();
    PDG = DAA->getPDG();
    // step 2: using the access information to generate policy
    for (auto &F : M)
    {
      if (F.isDeclaration())
        continue;
      // if (F.getName().str() != TargetFuncName)
      //   continue;
      std::string funcName = F.getName().str();
      std::string eBPFKernelFileName = funcName + "_check.c";
      std::string eBPFUserspaceFileName = funcName + "_check.py";
      EbpfKernelFile.open(eBPFKernelFileName);
      EbpfUserspaceFile.open(eBPFUserspaceFileName);
      generateEbpfUserProg(F, eBPFKernelFileName);
      generateEbpfKernelProg(F);
    }

    return false;
}

void pdg::EbpfGeneration::generateEbpfKernelProg(Function &F)
{
    generateHeaders();
    generateEbpfKernelEntryProg(F);
    generateEbpfKernelExitProg(F);
    EbpfKernelFile.close();
    EbpfUserspaceFile.close();
}

void pdg::EbpfGeneration::generateHeaders()
{
  // these are generic headers that need to be included by every 
  // ebpf kernel program. Uses may need to add corresponding files that contains 
  // parameter definitions manually.
  EbpfKernelFile << "<uapi/linux/ptrace.h>" << "\n";
  EbpfKernelFile << "<linux/netdevice.h>" << "\n";
  EbpfKernelFile << "<linux/sched.h>" << "\n";
}

// generate checks at the entry of a function
void pdg::EbpfGeneration::generateEbpfKernelEntryProg(Function &F)
{
  // for entry program, we check the following rules:
  auto funcWrapper = PDG->getFuncWrapper(F);
  assert(funcWrapper != nullptr && "");
  // 1. for pointer type parameter/field, if the field is dereferenced, place a non-null check for it
  auto argTreeMap = funcWrapper->getArgFormalInTreeMap();
  // generate entry trace func signature
  auto funcName = F.getName().str();
  EbpfKernelFile << "int " << funcName << "_trace_entry( struct pt_regs *ctx";

  auto argNameStr = extractFuncArgStr(F);
  if (!argNameStr.empty())
      EbpfKernelFile << ", ";

  EbpfKernelFile << argNameStr << ") {\n";
  for (auto iter = argTreeMap.begin(); iter != argTreeMap.end(); iter++)
  {
      auto argTree = iter->second;
      // generate rules for each fields
      generateEbpfKernelEntryRulesForFields(*argTree);
  }
  EbpfKernelFile << "}\n\n";

  // 2. record references and values to fields that require val_check rules 
      

  
}

void pdg::EbpfGeneration::generateEbpfKernelEntryRulesForFields(Tree &argTree)
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
    for (auto childNode : curNode->getChildNodes())
    {
      nodeQ.push(childNode);
    }
    // for each node check if the node is ptr type
    auto dt = curNode->getDIType();
    if (!dt)
      continue;
    if (!dbgutils::isPointerType(*dt))
      continue;
    // if a pointer is read, meaning there are a load inst on it, which indicates that 
    // the pointer is being dereferenced
    if (curNode->hasReadAccess())
    {
      auto fieldHierarchyName = curNode->getSrcHierarchyName();
      EbpfKernelFile << "\tif (" << fieldHierarchyName << " != "
                     << "NULL"
                     << ") {\n";
      EbpfKernelFile << "\t\tbpf_trace_printk(\" find nullptr dereference in " << funcName << " \")\n";
      EbpfKernelFile << "\t}\n";
    }
  }
}

// generate checks at the exit of a function
void pdg::EbpfGeneration::generateEbpfKernelExitProg(Function &F)
{
  auto funcName = F.getName().str();
  EbpfKernelFile << "int " << funcName << "_trace_exit( struct pt_regs *ctx ) {\n";
  // 1. generate val_check for fields with bounds, security sensitive variables etc

  EbpfKernelFile << "\treturn 0;\n";
  EbpfKernelFile << "}";
}


// ----- generate userspace program
void pdg::EbpfGeneration::generateEbpfUserProg(Function &F, std::string kernelProgFileName)
{
  generateUserProgImports();
  generateProbeAttaches(F, kernelProgFileName);
}

void pdg::EbpfGeneration::generateUserProgImports()
{
  EbpfUserspaceFile << "from bcc import BPF\n";
  EbpfUserspaceFile << "from ctypes import cast, POINTER, c_char\n";
}

void pdg::EbpfGeneration::generateProbeAttaches(Function &F, std::string kernelProgFileName)
{
  auto entryEbpfProgName = F.getName().str() + "_trace_entry";
  auto exitEbpfProgName = F.getName().str() + "_trace_exit";
  EbpfUserspaceFile << "b = BPF(src_file=\"" << kernelProgFileName << "\")\n";
  EbpfUserspaceFile << "b.attach_kprobe(event=\"" << F.getName().str() << "\", fn_name=\"" << entryEbpfProgName << "\")\n";
  EbpfUserspaceFile << "b.attach_kretprobe(event=\"" << F.getName().str() << "\", fn_name=\"" << exitEbpfProgName << "\")\n";
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

static RegisterPass<pdg::EbpfGeneration>
    EBPFGEN("ebpf-gen", "eBPF Instrumentation Program Generation", false, true);