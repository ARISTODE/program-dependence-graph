#include "KSplitStatsCollector.hh"
using namespace llvm;

void pdg::KSplitStats::printDataStats()
{
  _stats_file.open("ksplit_stats");
  // table 1.a
  _stats_file << "=============== Interface Calls ================\n";
  _stats_file << "driver to kernel call: " << _driver_to_kernel_func_call << "\n";
  _stats_file << "kernel to driver call: " << _kernel_to_driver_func_call << "\n";
  _stats_file << "total funcs size: " << _total_func_size << "\n";
  // table 1.b
  _stats_file << "=============== Fields Marshaled Through ================\n";
  _stats_file << "num fields deep copying: " << _fields_deep_copy << "\n";
  _stats_file << "num fields field access analysis: " << _fields_field_analysis << "\n";
  _stats_file << "num fields shared_analysis: " << _fields_shared_analysis << "\n";
  _stats_file << "num fields removed by boundary opt: " << (_fields_shared_analysis - _fields_removed_boundary_opt) << "\n";
  // table 1.c
  _stats_file << "=============== Data Classification ================\n";
  _stats_file << "private / shared pointers: ";
    // table 1.d
    _stats_file << "\t =============== Pointers Classification ================\n";
    // unsigned total_shared_ptr = _safe_ptr_num + _shared_void_ptr_num + _unhandled_void_ptr_num + _string_num + _array_num + _unhandled_array_num + _non_void_wild_ptr_num + _func_ptr_num;
    _stats_file << "\t total ptr num: " << _total_ptr_num << "\n";
    _stats_file << "\t safe ptr num: " << _safe_ptr_num << "\n";
      _stats_file << "\t\t ioremap region num: " << _shared_ioremap_num << "\n";
      _stats_file << "\t\t user region num: " << _shared_user_num << "\n";
      _stats_file << "\t\t func ptr num: " << _func_ptr_num << "\n";
    _stats_file << "\t dyn size array num: " << _dyn_sized_arr_num << "\n"; // the ones we cannot infer size
      _stats_file << "\t\t dyn_sentinel num: " << _dyn_sized_sentinel_num << "\n";
        _stats_file << "\t\t\t dyn_string num: " << _dyn_sized_string_num << "\n";
    _stats_file << "\t single cast shared void ptr num: " << _single_cast_shared_void_ptr_num << "\n";
    _stats_file << "\t multi-cast shared void ptr num (unhandled): " << _multi_cast_shared_void_ptr_num << "\n";
    _stats_file << "\t non void wild ptr num: " << _non_void_wild_ptr_num << "\n";
    // _stats_file << "\t void wild ptr num: " << _void_wild_ptr_num << "\n";

  _stats_file << "======================================================\n";
  // _stats_file << "private / shared primitive types: " << (_total_primitive_num - _shared_primitive_num) << " / " << _shared_primitive_num << "\n";
  _stats_file << "primitive types: " << _primitive_fields << "\n";
  // _stats_file << "\t private / shared bit field: " << (_total_bitfield_num - _shared_bitfield_num) << " / " << _shared_bitfield_num << "\n";
  _stats_file << "\t shared bit field: " << _shared_bitfield << "\n";

  _stats_file << "======================================================\n";
  // _stats_file << "private / shared complex types: " << (_totoal_complex_ty_num - _shared_complex_ty_num) << " / " << _shared_complex_types << "\n";
  // _stats_file << "\t private / shared struct: " << (_total_struct_num - _shared_struct_num) << " / " << _shared_struct_types << "\n";
  // _stats_file << "\t private / shared union: " << (_total_union_num - _shared_union_num) << " / " << _shared_union_types << "\n";
  _stats_file << "\t shared struct: " << _shared_struct_num << "\n";
  _stats_file << "\t\t recursive struct: " << _recursive_struct_num << "\n";
  _stats_file << "\t shared union: " << _shared_union_num << "\n";
  // _stats_file << "\t private / shared sized arrays: " << (_total_sized_arr_num - _shared_sized_arr_num) << " / " << _shared_sized_arr_num << "\n";
  _stats_file << "\t sized array num: " << _sized_arr_num << "\n";
    _stats_file << "\t\t sized_sentinel num: " << _sized_sentinel_num << "\n";
      _stats_file << "\t\t\t sized_string num: " << _sized_string_num << "\n";
  
  _stats_file << "======================================================\n";
  _stats_file << "\t Private/Shared CS: " << (_total_CS - _shared_CS) << " / " << _shared_CS << "\n";
  _stats_file << "\t RCU: " << _shared_rcu << "\n";
  _stats_file << "\t seqlock: " << _shared_seqlock << "\n";
  _stats_file << "\t Private/Shared Atomic Operation: " << (_total_atomic_op - _shared_atomic_op) << " / " << _shared_atomic_op << "\n";

  _stats_file << "\t Unknown: " << _shared_other << "\n";
  _stats_file.close();
}

// void pdg::KSplitStats::printStats()
// {
//   _stats_file.open("ksplit_stats");

//   _stats_file << "=============== Interface Calls ================\n";
//   _stats_file << "kernel to driver call: " << _kernel_to_driver_func_call << "\n";
//   _stats_file << "driver to kernel call: " << _driver_to_kernel_func_call << "\n";
//   _stats_file << "total funcs size: " << _total_func_size << "\n";

//   _stats_file << "=============== Fields Access Analysis ================\n";
//   _stats_file << "num fields deep copying: " << _fields_deep_copy << "\n";
//   _stats_file << "num fields field access analysis: " << _fields_field_analysis << "\n";
//   _stats_file << "num fields shared_analysis: " << _fields_shared_analysis << "\n";
//   _stats_file << "num fields removed by boundary opt: " << (_fields_shared_analysis - _fields_removed_boundary_opt) << "\n";
//   _stats_file << "num fields have ptr arith: " << _ptr_arith_num << "\n";
//   _stats_file << "num fields have ptr gep arith in sd: " << _ptr_gep_arith_sd << "\n";
//   _stats_file << "num fields have ptr ptrtoint arith in sd: " << _ptr_ptrtoint_arith_sd << "\n";
//   _stats_file << "num fields have ptr gep arith in daa: " << _ptr_gep_arith_daa << "\n";
//   _stats_file << "num fields have ptr ptrtoint arith in daa: " << _ptr_ptrtoint_arith_daa << "\n";

//   _stats_file << "=============== Pointer Classification ================\n";
//   unsigned total_shared_ptr = _safe_ptr_num + _shared_void_ptr_num + _unhandled_void_ptr_num + _string_num + _array_num + _unhandled_array_num + _non_void_wild_ptr_num + _unknown_ptr_num;
//   _stats_file << "shared ptr fields: " << total_shared_ptr << "\n";
//   _stats_file << "safe ptr num: " << _safe_ptr_num << "\n";
//   _stats_file << "shared void ptr num: " << _shared_void_ptr_num << "\n";
//   _stats_file << "unhandled void ptr num: " << _unhandled_void_ptr_num << "\n";
//   _stats_file << "unhandled void ptr num SD: " << _unhandled_void_ptr_sd_num << "\n";
//   _stats_file << "void wild ptr num: " << _void_wild_ptr_num << "\n";
//   _stats_file << "string num: " << _string_num << "\n";
//   _stats_file << "inferred string num: " << _inferred_string_num << "\n";
//   _stats_file << "array num: " << _array_num << "\n";
//   _stats_file << "unhandled array num: " << _unhandled_array_num << "\n";
//   _stats_file << "struct array num: " << _struct_array_num << "\n";
//   _stats_file << "func ptr num: " << _func_ptr_num << "\n";
//   _stats_file << "non void wild ptr num: " << _non_void_wild_ptr_num << "\n";
//   _stats_file << "unknown num: " << _unknown_ptr_num << "\n";

//   _stats_file << "=============== Private/Shared Data Classification ================\n";
//   _stats_file << "pointers: " << _total_ptr_num << " / " << (_total_ptr_num - total_shared_ptr) << " / " << total_shared_ptr << " / " << _shared_ptr_num << "\n";
//   _stats_file << "union ptr: " << _total_union_ptr_num << " / " << (_total_union_ptr_num - _shared_union_ptr_num) << " / " << _shared_union_ptr_num << "\n";
//   _stats_file << "union: " << _total_union_num << " / " << (_total_union_num - _shared_union_num) << " / " << _shared_union_num << " / " << (_shared_tagged_union_num) << "\n";
//   _stats_file << "CS: " << _total_CS << " / " << (_total_CS - _shared_CS) << " / " << _shared_CS << "\n";
//   _stats_file << "Atomic Ops: " << _total_atomic_op << " / " << (_total_atomic_op - _shared_atomic_op) << " / " << _shared_atomic_op << "\n";
//   _stats_file << "RCU: " << _total_rcu << " / " << (_total_rcu - _shared_rcu) << " / " << _shared_rcu << "\n";
//   _stats_file << "Seqlock: " << _total_seqlock << " / " << (_total_seqlock - _shared_seqlock) << " / " << _shared_seqlock << "\n";
//   _stats_file << "Nest Lock: " << _total_nest_lock << " / " << (_total_nest_lock - _shared_nest_lock) << " / " << _shared_nest_lock << "\n";
//   _stats_file << "Barrier: " << _total_barrier << " / " << _total_barrier << " / " << _shared_barrier << "\n";
//   _stats_file << "Bitfield: " << _total_bitfield << " / " << (_total_bitfield - _shared_bitfield) << " / " << _shared_bitfield << "\n";
//   _stats_file << "containerof: " << _total_containerof << " / " << (_total_containerof - _shared_containerof) << " / " << _shared_containerof << "\n";
//   _stats_file << "IO remap: " << _total_ioremap << " / " << (_total_ioremap - _shared_ioremap) << " / " << _shared_containerof << "\n";
//   _stats_file << "Sentinel array: " << _shared_sentinel_array << "\n";
//   _stats_file.close();
// }

// void pdg::KSplitStats::printStatsRaw()
// {
//   _stats_file.open("ksplit_stats");
//   unsigned total_shared_ptr = _safe_ptr_num + _void_ptr_num + _unhandled_void_ptr_num + _string_num + _array_num + _unhandled_array_num + _non_void_wild_ptr_num + _unknown_ptr_num;
//   // unsigned total_shared_ptr = _safe_ptr_num + _void_ptr_num + _unhandled_void_ptr_num + _string_num + _array_num + _unhandled_array_num + _non_void_wild_ptr_num + _unknown_ptr_num;
//   _stats_file << _kernel_to_driver_func_call << "/0" << "\n";
//   _stats_file << _driver_to_kernel_func_call << "/0" << "\n";
//   _stats_file << _total_func_size << "/0" << "\n";
//   _stats_file << (_total_ptr_num - total_shared_ptr) << "/" << total_shared_ptr << "\n";
//   _stats_file << (_total_union_num - _shared_union_num) << "/" << _shared_union_num << "\n";
//   _stats_file << (_total_CS - _shared_CS) << "/" << _shared_CS << "\n";
//   _stats_file << (_total_atomic_op - _shared_atomic_op) << "/" << _shared_atomic_op << "\n";
//   _stats_file << (_total_rcu - _shared_rcu) << "/" << _shared_rcu << "\n";
//   _stats_file << (_total_seqlock - _shared_seqlock) << "/" << _shared_seqlock << "\n";
//   _stats_file << (_total_nest_lock - _shared_nest_lock) << "/" << _shared_nest_lock << "\n";
//   _stats_file << _total_barrier << "/" << _shared_barrier << "\n";
//   _stats_file << (_total_bitfield - _shared_bitfield) << "/" << _shared_bitfield << "\n";
//   _stats_file << (_total_containerof - _shared_containerof) << "/" << _shared_containerof << "\n";
//   _stats_file << _safe_ptr_num << "/0" << "\n";
//   _stats_file << _array_num << "/" << _unhandled_array_num << "\n";
//   _stats_file << _string_num << "/0" << "\n";
//   _stats_file << _void_ptr_num << "/" << _unhandled_void_ptr_num << "\n";
//   _stats_file << (_non_void_wild_ptr_num + _unknown_ptr_num) << "/0" << "\n";

//   // _stats_file << "=============== Fields Access Analysis ================\n";
//   // _stats_file << "num fields deep copying: " << _fields_deep_copy << "\n";
//   // _stats_file << "num fields field access analysis: " << _fields_field_analysis << "\n";
//   // _stats_file << "num fields _shared_analysis: " << _fields_shared_analysis << "\n";
//   // _stats_file << "num fields removed by boundary opt: " << _fields_removed_boundary_opt << "\n";

//   // unsigned total_shared_ptr = _safe_ptr_num + _void_ptr_num + _unhandled_void_ptr_num + _string_num + _array_num + _unhandled_array_num + _non_void_wild_ptr_num + _unknown_ptr_num;
//   // _stats_file << total_shared_ptr << "/0" << "\n";

//   _stats_file.close();
// }

// ksplit stats collect
// void pdg::KSplitStats::collectTotalPointerStats(DIType &dt)
// {
//   // totoal pointer type is computed using di type transitively
//   // only count total and shared. Private then can be computed by substracting shared from total
//   if (dbgutils::isPointerType(dt))
//   {
//     increaseTotalPtrNum(); // total accessed pointer fields
//     if (dbgutils::isVoidPointerType(dt))
//       increaseTotalVoidPtrNum();
//     else if (dbgutils::isUnionPointerType(dt))
//       increaseTotalUnionPtrNum();
//     else if (dbgutils::isFuncPointerType(dt))
//       increaseFuncPtrNum();
//   }
// }

void pdg::KSplitStats::collectDataStats(TreeNode& tree_node, std::string nescheck_ptr_type)
{
  // this function classify the tree node and accumulate stats
  DIType* dt = tree_node.getDIType();
  if (!dt)
    return;
  // first strip member tag
  dt = dbgutils::stripMemberTag(*dt);
  dt = dbgutils::stripAttributes(*dt);
  if (tree_node.getAccessTags().size() > 0)
    _fields_field_analysis ++;
  if (!tree_node.is_shared)
    return;
  _fields_shared_analysis++;

  // pointers, basic types, struct, union, array
  if (dbgutils::isPointerType(*dt))
  {
    _total_ptr_num += 1;
    collectSharedPointerStats(tree_node, nescheck_ptr_type);
  }
  else if (isa<DIBasicType>(dt))
  {
    _primitive_fields += 1;
    if (dt->isBitField())
      _shared_bitfield += 1;
  }
  else if (dbgutils::isStructType(*dt))
  {
    _shared_struct_num += 1;
    if (dbgutils::isRecursiveTy(*dt))
      _recursive_struct_num += 1;
  }
  else if (dbgutils::isArrayType(*dt))
    _sized_arr_num += 1;
  else if (dbgutils::isUnionType(*dt))
    _shared_union_num += 1;
  else
  {
    _shared_other += 1; // This should be 0, otherwise, we need to look at this node
    errs() << "unclassified field type: " << tree_node.getTree()->getFunc()->getName() << " - " << dbgutils::getSourceLevelTypeName(*dt) << "\n";
  }
}

void pdg::KSplitStats::collectSharedPointerStats(TreeNode& node, std::string nescheck_ptr_type)
{
  auto annotations = node.annotations;
  DIType *dt = node.getDIType();
  if (nescheck_ptr_type == "SAFE")
  {
    // chekc if this is speical memory
    // ioremap
    bool has_ioremap_anno = (annotations.find("[ioremap(caller)]") != annotations.end());
    if (has_ioremap_anno)
      _shared_ioremap_num += 1;
    // user
    bool has_user_anno = (annotations.find("[user]") != annotations.end());
    if (has_user_anno)
      _shared_user_num += 1;
    // func pointer
    if (dbgutils::isFuncPointerType(*dt))
      _func_ptr_num += 1;
    if (dbgutils::isVoidPointerType(*dt))
      _no_cast_void_pointer += 1;
    _safe_ptr_num += 1;
  }
  else if (nescheck_ptr_type == "SEQ")
  {
    // must be an array because structs are eliminated
    _dyn_sized_arr_num += 1;
    if (node.is_sentinel)
      _dyn_sized_sentinel_num += 1;
    else if (node.is_string)
    {
      _dyn_sized_sentinel_num++;
      _dyn_sized_string_num++;
    }
  }
  else if (nescheck_ptr_type == "DYN")
  {
    _dyn_ptr_num += 1;
    if (dbgutils::isVoidPointerType(*dt))
    {
      if (pdgutils::isVoidPointerHasMultipleCasts(node))
        _multi_cast_shared_void_ptr_num += 1;
      else
        _single_cast_shared_void_ptr_num += 1;
    }
    else
    {
      _non_void_wild_ptr_num += 1;
    }
  }
  else if (nescheck_ptr_type == "UNKNOWN")
    _unknown_ptr_num += 1;
}

// void pdg::KSplitStats::collectSharedPointerStats(DIType &dt, std::string var_name, std::string func_name)
// {
//   // only count total and shared. Private then can be computed by substracting shared from total
//   if (dbgutils::isPointerType(dt))
//   {
//     if (!dbgutils::isFuncPointerType(dt))
//       increaseSharedPtrNum();
//     if (dbgutils::isVoidPointerType(dt))
//       increaseSharedVoidPtrNum();
//     else if (dbgutils::isUnionPointerType(dt))
//       increaseSharedUnionPtrNum();
//     // else if (dbgutils::isFuncPointerType(dt))
//     //   increaseFuncPtrNum();
//   }
// }

// void pdg::KSplitStats::collectInferredStringStats(std::set<std::string> &annotations)
// {
//   if (annotations.find("[string]") != annotations.end())
//   {
//     increaseStringNum();
//     increaseInferredStringNum();
//   }
// }