#ifndef GRAPHWRITER_H_
#define GRAPHWRITER_H_
#include "llvm/ADT/GraphTraits.h"
#include "llvm/Analysis/DOTGraphTraitsPass.h"
#include "GraphTraits.hh"

namespace llvm
{
  template <>
  struct DOTGraphTraits<pdg::Node *> : public DefaultDOTGraphTraits
  {
    DOTGraphTraits(bool isSimple = false) : DefaultDOTGraphTraits(isSimple) {}
  };

  template <>
  struct DOTGraphTraits<pdg::ProgramDependencyGraph *> : public DefaultDOTGraphTraits
  {
    DOTGraphTraits(bool isSimple = false) : DefaultDOTGraphTraits(isSimple) {}

    // Return graph name;
    static std::string getGraphName(pdg::ProgramDependencyGraph *)
    {
      return "Program Dependency  Graph";
    }

    std::string getNodeLabel(pdg::Node *node, pdg::ProgramDependencyGraph *)
    {
      pdg::GraphNodeType node_type = node->getNodeType();
      Function* func = node->getFunc();
      Value* node_val = node->getValue();
      std::string str;
      raw_string_ostream OS(str);

      switch (node_type)
      {
      case pdg::GraphNodeType::FUNC_ENTRY:
        return "<<ENTRY>> " + func->getName().str();
      case pdg::GraphNodeType::FORMAL_IN:
        return "FORMAL_IN";
      case pdg::GraphNodeType::FORMAL_OUT:
        return "FORMAL_OUT";
      case pdg::GraphNodeType::ACTUAL_IN:
        return "ACTUAL_IN";
      case pdg::GraphNodeType::ACTUAL_OUT:
        return "ACTUAL_OUT";
      case pdg::GraphNodeType::INST:
      {
        if (Instruction *i = dyn_cast<Instruction>(node_val))
        {
          OS << *i;
          return OS.str(); // print the instruction literal
        }
        break;
      }
      default:
        break;
      }
      return "";
    }

    std::string getEdgeAttributes(pdg::Node *Node, pdg::Node::iterator edge_itertor, pdg::ProgramDependencyGraph *PDG)
    {
      return "";
    }
  };
} // namespace llvm

namespace pdg
{
  struct ProgramDependencyPrinter : public llvm::DOTGraphTraitsPrinter<ProgramDependencyGraph, false>
  {
    static char ID;
    ProgramDependencyPrinter() : llvm::DOTGraphTraitsPrinter<ProgramDependencyGraph, false>("pdgragh", ID) {}
  };

} // namespace pdg

#endif