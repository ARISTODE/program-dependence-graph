#ifndef PDGENUMS_H_
#define PDGENUMS_H_

namespace pdg
{
  enum class EdgeType
  {
    IND_CALL,
    CONTROLDEP_CALLINV,
    CONTROLDEP_CALLRET,
    CONTROLDEP_ENTRY,
    CONTROLDEP_BR,
    CONTROLDEP_IND_BR,
    DATA_DEF_USE,
    DATA_RAW,
    DATA_READ,
    DATA_ALIAS,
    DATA_RET,
    PARAMETER_IN,
    PARAMETER_OUT,
    PARAMETER_FIELD,
    GLOBAL_DEP,
    VAL_DEP,
    ANNO_FUNC,
    ANNO_VAR,
    TYPE_OTHEREDGE
  };

  enum class GraphNodeType
  {
    INST,
    FORMAL_IN,
    FORMAL_OUT,
    ACTUAL_IN,
    ACTUAL_OUT,
    RETURN,
    FUNC_ENTRY,
    CALL,
    GLOBAL_TYPE,
    FUNC,
    INST_ANNO_LOCAL,
    INST_ANNO_GLOBAL,
    GLOBALVAR_GLOBL,
    GLOBALVAR_LOCAL,
    TYPE_OTHERNODE
  };

  enum class AccessTag
  {
    DATA_READ,
    DATA_WRITE
  };
}

#endif