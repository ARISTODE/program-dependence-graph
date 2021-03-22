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

    std::string getNodeLabel(pdg::Node *node, pdg::ProgramDependencyGraph *G)
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
      {
        pdg::pdgutils::printTreeNodesLabel(node, OS, "FORMAL_IN");
        return OS.str();
      }
      case pdg::GraphNodeType::FORMAL_OUT:
      {
        pdg::pdgutils::printTreeNodesLabel(node, OS, "FORMAL_OUT");
        return OS.str();
      }
      case pdg::GraphNodeType::ACTUAL_IN:
      {
        pdg::pdgutils::printTreeNodesLabel(node, OS, "ACTUAL_IN");
        return OS.str();
      }
      case pdg::GraphNodeType::ACTUAL_OUT:
      {
        pdg::pdgutils::printTreeNodesLabel(node, OS, "ACTUAL_OUT");
        return OS.str();
      }
      case pdg::GraphNodeType::INST:
      {
        if (Instruction *i = dyn_cast<Instruction>(node_val))
        {
          OS << *i;
          return OS.str(); // print the instruction literal
        }
        break;
      }
      case pdg::GraphNodeType::INST_ANNO_LOCAL:
      {
          OS << "Local Anno: " << *node_val;
          return OS.str();
      }
      case pdg::GraphNodeType::INST_ANNO_GLOBAL:
      {
          OS << "Global Anno: " << *node_val;
          return OS.str();
      }
      case pdg::GraphNodeType::GLOBALVAR_GLOBL:
      {
          OS << "global var: " << *node_val;
          return OS.str();
      }
      case pdg::GraphNodeType::GLOBALVAR_LOCAL:
      {
          OS << "static var: " << *node_val;
          return OS.str();
      }
      default:
        break;
      }
      return "";
    }

    std::string getEdgeAttributes(pdg::Node *Node, pdg::Node::iterator edge_iter, pdg::ProgramDependencyGraph *PDG)
    {
      pdg::EdgeType edge_type = edge_iter.getEdgeType();
      switch (edge_type)
      {
      case pdg::EdgeType::CONTROLDEP_ENTRY:
        return "label = \"{CONTROLDEP_ENTRY}\"";
      case pdg::EdgeType::CONTROLDEP_BR:
        return "label = \"{CONTROLDEP_BR}\"";
      case pdg::EdgeType::CONTROLDEP_CALLINV:
        return "label = \"{CONTROLDEP_CALLINV}\"";
      case pdg::EdgeType::CONTROLDEP_CALLRET:
        return "label = \"{CONTROLDEP_CALLRET}\"";
      case pdg::EdgeType::CONTROLDEP_IND_BR:
        return "label = \"{CONTROLDEP_IND_BR}\"";
      case pdg::EdgeType::DATA_DEF_USE:
        return "style=dotted,label = \"{D_DEF_USE}\" ";
      case pdg::EdgeType::DATA_ALIAS:
        return "style=dotted,label = \"{D_ALIAS}\" ";
      case pdg::EdgeType::PARAMETER_IN:
        return "style=dashed, color=\"blue\", label=\"{P_IN}\"";
      case pdg::EdgeType::PARAMETER_OUT:
        return "style=dashed, color=\"blue\", label=\"{P_OUT}\"";
      case pdg::EdgeType::PARAMETER_FIELD:
        return "style=dashed, color=\"blue\", label=\"{P_F}\"";
      case pdg::EdgeType::DATA_RAW:
        return "style=dotted,label = \"{D_RAW}\" ";
      case pdg::EdgeType::DATA_RET:
        return "style=dashed, color=\"red\", label =\"{D_RET}\"";
      case pdg::EdgeType::ANNO_VAR:
        return "style=dashed, color=\"green\", label =\"{anno}\"";
      default:
        break;
      }
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