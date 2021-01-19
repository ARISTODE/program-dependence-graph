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
        pdg::TreeNode* n = dynamic_cast<pdg::TreeNode*>(node);
        int tree_node_depth = n->getDepth();
        DIType *node_di_type = n->getDIType();
        std::string field_type_name = pdg::dbgutils::getSourceLevelTypeName(*node_di_type);
        OS << "FORMAL_IN: " << tree_node_depth << " " << field_type_name;
        return OS.str();
      }
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

    std::string getEdgeAttributes(pdg::Node *Node, pdg::Node::iterator edge_iter, pdg::ProgramDependencyGraph *PDG)
    {
      pdg::EdgeType edge_type = edge_iter.getEdgeType();
      switch (edge_type)
      {
      case pdg::EdgeType::CONTROL:
        return "label=\"{c}\"";
      case pdg::EdgeType::DATA_DEF_USE:
        return "style=dotted,label = \"{DEF_USE}\" ";
      case pdg::EdgeType::PARAMETER_IN:
        return "style=dashed, color=\"blue\"";
      case pdg::EdgeType::PARAMETER_OUT:
        return "style=dashed, color=\"blue\"";
      case pdg::EdgeType::CALL:
        return "style=dashed, color=\"red\", label =\"{CALL}\"";
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