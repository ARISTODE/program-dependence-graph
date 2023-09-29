#ifndef PDGENUMS_H_
#define PDGENUMS_H_

namespace pdg
{
  enum class RiskyDataType {
    PTR_READ,
    PTR_WRTIE,
    PTR_BUFFER,
    PTR_ARITH_BASE,
    ARR_BUFFER,
    ARR_IDX,
    NUM_ARITH,
    CONTROL_SENBRANCH,
    SEN_API,
    FUNC_PTR,
    OTHER
  };

  enum class EdgeType
  {
    CALL,
    IND_CALL,
    CONTROL, // control dependence edges
    CONTROL_FLOW, // control flow edges
    DATA_DEF_USE,
    DATA_RAW,
    DATA_RAW_REV,
    DATA_READ,
    DATA_MAY_ALIAS,
    DATA_MUST_ALIAS,
    DATA_ALIAS,
    DATA_RET,
    DATA_STORE_TO,
    DATA_EQUL_OBJ,
    PARAMETER_IN,
    PARAMETER_IN_REV,
    PARAMETER_OUT,
    PARAMETER_FIELD,
    GLOBAL_DEP,
    VAL_DEP
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
    GLOBAL_VAR,
    CALL,
    GLOBAL_TYPE,
    FUNC
  };

  enum class AccessTag
  {
    DATA_READ,
    DATA_WRITE
  };

  enum class DomainTag
  {
    KERNEL_DOMAIN,
    DRIVER_DOMAIN,
    NO_DOMAIN
  };
}

#endif