#include "KSplitStatsCollector.hh"

void pdg::KSplitStats::printStats()
{
  _stats_file.open("ksplit_stats");

  _stats_file << "=============== Interface Calls ================\n";
  _stats_file << "kernel to driver call: " << _kernel_to_driver_func_call << "\n";
  _stats_file << "driver to kernel call: " << _driver_to_kernel_func_call << "\n";
  _stats_file << "total funcs size: " << _total_func_size << "\n";

  _stats_file << "=============== Fields Access Analysis ================\n";
  _stats_file << "num fields deep copying: " << _fields_deep_copy << "\n";
  _stats_file << "num fields field access analysis: " << _fields_field_analysis << "\n";
  _stats_file << "num fields shared_analysis: " << _fields_shared_analysis << "\n";
  _stats_file << "num fields removed by boundary opt: " << _fields_removed_boundary_opt << "\n";
  _stats_file << "num fields have ptr arith: " << _ptr_arith_num << "\n";
  _stats_file << "num fields have ptr gep arith in sd: " << _ptr_gep_arith_sd << "\n";
  _stats_file << "num fields have ptr ptrtoint arith in sd: " << _ptr_ptrtoint_arith_sd << "\n";
  _stats_file << "num fields have ptr gep arith in daa: " << _ptr_gep_arith_daa << "\n";
  _stats_file << "num fields have ptr ptrtoint arith in daa: " << _ptr_ptrtoint_arith_daa << "\n";

  _stats_file << "=============== Pointer Classification ================\n";
  unsigned total_shared_ptr = _safe_ptr_num + _void_ptr_num + _unhandled_void_ptr_num + _string_num + _array_num + _unhandled_array_num + _non_void_wild_ptr_num + _unknown_ptr_num;
  _stats_file << "shared ptr fields: " << total_shared_ptr << "\n";
  _stats_file << "safe ptr num: " << _safe_ptr_num << "\n";
  _stats_file << "void ptr num: " << _void_ptr_num << "\n";
  _stats_file << "unhandled void ptr num: " << _unhandled_void_ptr_num << "\n";
  _stats_file << "unhandled void ptr num SD: " << _unhandled_void_ptr_sd_num << "\n";
  _stats_file << "void wild ptr num: " << _void_wild_ptr_num << "\n";
  _stats_file << "string num: " << _string_num << "\n";
  _stats_file << "array num: " << _array_num << "\n";
  _stats_file << "unhandled array num: " << _unhandled_array_num << "\n";
  _stats_file << "struct array num: " << _struct_array_num << "\n";
  _stats_file << "func ptr num: " << _func_ptr_num << "\n";
  _stats_file << "non void wild ptr num: " << _non_void_wild_ptr_num << "\n";
  _stats_file << "unknown num: " << _unknown_ptr_num << "\n";

  _stats_file << "=============== Private/Shared Data Classification ================\n";
  _stats_file << "pointers: " << _total_ptr_num << " / " << (_total_ptr_num - total_shared_ptr) << " / " << total_shared_ptr << "\n";
  _stats_file << "unions: " << _total_union_num << " / " << (_total_union_num - _shared_union_num) << " / " << _shared_union_num << "\n";
  _stats_file << "CS: " << _total_CS << " / " << (_total_CS - _shared_CS) << " / " << _shared_CS << "\n";
  _stats_file << "Atomic Ops: " << _total_atomic_op << " / " << (_total_atomic_op - _shared_atomic_op) << " / " << _shared_atomic_op << "\n";
  _stats_file << "RCU: " << _total_rcu << " / " << (_total_rcu - _shared_rcu) << " / " << _shared_rcu << "\n";
  _stats_file << "Seqlock: " << _total_seqlock << " / " << (_total_seqlock - _shared_seqlock) << " / " << _shared_seqlock << "\n";
  _stats_file << "Nest Lock: " << _total_nest_lock << " / " << (_total_nest_lock - _shared_nest_lock) << " / " << _shared_nest_lock << "\n";
  _stats_file << "Barrier: " << _total_barrier << " / " << _total_barrier << " / " << _shared_barrier << "\n";
  _stats_file << "Bitfield: " << _total_bitfield << " / " << (_total_bitfield - _shared_bitfield) << " / " << _shared_bitfield << "\n";
  _stats_file << "containerof: " << _total_containerof << " / " << (_total_containerof - _shared_containerof) << " / " << _shared_containerof << "\n";
  _stats_file << "IO remap: " << _total_ioremap << " / " << (_total_ioremap - _shared_ioremap) << " / " << _shared_containerof << "\n";
  _stats_file.close();
}

void pdg::KSplitStats::printStatsRaw()
{
  _stats_file.open("ksplit_stats");
  unsigned total_shared_ptr = _safe_ptr_num + _void_ptr_num + _unhandled_void_ptr_num + _string_num + _array_num + _unhandled_array_num + _non_void_wild_ptr_num + _unknown_ptr_num;
  _stats_file << _kernel_to_driver_func_call << "/0" << "\n";
  _stats_file << _driver_to_kernel_func_call << "/0" << "\n";
  _stats_file << _total_func_size << "/0" << "\n";
  _stats_file << (_total_ptr_num - total_shared_ptr) << "/" << total_shared_ptr << "\n";
  _stats_file << (_total_union_num - _shared_union_num) << "/" << _shared_union_num << "\n";
  _stats_file << (_total_CS - _shared_CS) << "/" << _shared_CS << "\n";
  _stats_file << (_total_atomic_op - _shared_atomic_op) << "/" << _shared_atomic_op << "\n";
  _stats_file << (_total_rcu - _shared_rcu) << "/" << _shared_rcu << "\n";
  _stats_file << (_total_seqlock - _shared_seqlock) << "/" << _shared_seqlock << "\n";
  _stats_file << (_total_nest_lock - _shared_nest_lock) << "/" << _shared_nest_lock << "\n";
  _stats_file << _total_barrier << "/" << _shared_barrier << "\n";
  _stats_file << (_total_bitfield - _shared_bitfield) << "/" << _shared_bitfield << "\n";
  _stats_file << (_total_containerof - _shared_containerof) << "/" << _shared_containerof << "\n";
  _stats_file << _safe_ptr_num << "/0" << "\n";
  _stats_file << _array_num << "/" << _unhandled_array_num << "\n";
  _stats_file << _string_num << "/0" << "\n";
  _stats_file << _void_ptr_num << "/" << _unhandled_void_ptr_num << "\n";
  _stats_file << (_non_void_wild_ptr_num + _unknown_ptr_num) << "/0" << "\n";

  // _stats_file << "=============== Fields Access Analysis ================\n";
  // _stats_file << "num fields deep copying: " << _fields_deep_copy << "\n";
  // _stats_file << "num fields field access analysis: " << _fields_field_analysis << "\n";
  // _stats_file << "num fields _shared_analysis: " << _fields_shared_analysis << "\n";
  // _stats_file << "num fields removed by boundary opt: " << _fields_removed_boundary_opt << "\n";

  // unsigned total_shared_ptr = _safe_ptr_num + _void_ptr_num + _unhandled_void_ptr_num + _string_num + _array_num + _unhandled_array_num + _non_void_wild_ptr_num + _unknown_ptr_num;
  // _stats_file << total_shared_ptr << "/0" << "\n";

  _stats_file.close();
}