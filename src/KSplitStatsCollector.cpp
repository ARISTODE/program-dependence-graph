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
  
  _stats_file << "======================================================\n";
  _stats_file << "\t Union: " << (_total_union_num - _shared_union_num) << " / " << _shared_union_num << "\n";
  _stats_file << "\t Private/Shared CS: " << (_total_CS - _shared_CS) << " / " << _shared_CS << "\n";
  _stats_file << "\t RCU: " << _total_rcu << "/" << _shared_rcu << "\n";
  _stats_file << "\t seqlock: " << _total_seqlock << "/" << _shared_seqlock << "\n";
  _stats_file << "\t Private/Shared Atomic Operation: " << (_total_atomic_op - _shared_atomic_op) << " / " << _shared_atomic_op << "\n";
  _stats_file << "\t Container_of: " << _total_containerof << " / " << _shared_containerof << "\n";

  // table 1.c
  _stats_file << "=============== Data Classification ================\n";
    // table 1.d
    _stats_file << "\t =============== Pointers Classification ================\n";
    // unsigned total_shared_ptr = _safe_ptr_num + _shared_void_ptr_num + _unhandled_void_ptr_num + _string_num + _array_num + _unhandled_array_num + _non_void_wild_ptr_num + _func_ptr_num;
    _stats_file << "\t ptr num: " << _total_ptr_num << "/" << _shared_ptr_num << "\n";
    _stats_file << "\t safe ptr num: " << _safe_ptr_num << "\n";
      _stats_file << "\t\t ioremap region num: " << _shared_ioremap_num << "\n";
      _stats_file << "\t\t user region num: " << _shared_user_num << "\n";
      _stats_file << "\t\t func ptr num: " << _func_ptr_num << "\n";
    _stats_file << "\t dyn size array num: " << _dyn_sized_arr_num << "\n"; // the ones we cannot infer size
      _stats_file << "\t\t dyn_sentinel num: " << _dyn_sized_sentinel_num << "\n";
        _stats_file << "\t\t\t dyn_string num: " << _dyn_sized_string_num << "\n";
      
    _stats_file << "\t dyn ptr: " << _dyn_ptr_num << "\n";
    _stats_file << "\t\t single cast shared void ptr num: " << _single_cast_shared_void_ptr_num << "\n";
    _stats_file << "\t\t multi-cast shared void ptr num (unhandled): " << _multi_cast_shared_void_ptr_num << "\n";
    _stats_file << "\t\t non void wild ptr num: " << _non_void_wild_ptr_num << "\n";
    _stats_file << "\t unknown ptr num: " << _unknown_ptr_num << "\n";
    // _stats_file << "\t void wild ptr num: " << _void_wild_ptr_num << "\n";

  _stats_file << "======================================================\n";
  // _stats_file << "private / shared primitive types: " << (_total_primitive_num - _shared_primitive_num) << " / " << _shared_primitive_num << "\n";
  _stats_file << "\t primitive types: " << _primitive_fields + _shared_other << "\n";
  // _stats_file << "\t private / shared bit field: " << (_total_bitfield_num - _shared_bitfield_num) << " / " << _shared_bitfield_num << "\n";
  _stats_file << "\t shared bit field: " << _shared_bitfield << "\n";

  _stats_file << "======================================================\n";
  // _stats_file << "private / shared complex types: " << (_totoal_complex_ty_num - _shared_complex_ty_num) << " / " << _shared_complex_types << "\n";
  // _stats_file << "\t private / shared struct: " << (_total_struct_num - _shared_struct_num) << " / " << _shared_struct_types << "\n";
  // _stats_file << "\t private / shared union: " << (_total_union_num - _shared_union_num) << " / " << _shared_union_types << "\n";
  _stats_file << "\t shared struct: " << _shared_struct_num << "\n";
  _stats_file << "\t\t recursive struct: " << _recursive_struct_num << "\n";
  _stats_file << "\t shared union: " << _shared_union_num << "\n";
  _stats_file << "\t\t shared tagged union: " << _shared_tagged_union_num << "\n";
  _stats_file << "\t\t shared anonymou union: " << _shared_anonymous_union_num << "\n";
  // _stats_file << "\t private / shared sized arrays: " << (_total_sized_arr_num - _shared_sized_arr_num) << " / " << _shared_sized_arr_num << "\n";
  _stats_file << "\t sized array num: " << _sized_arr_num << "\n";
    _stats_file << "\t\t sized_sentinel num: " << _sized_sentinel_num << "\n";
      _stats_file << "\t\t\t sized_string num: " << _sized_string_num << "\n";

  // _stats_file << "\t Unknown: " << _shared_other << "\n";
  _stats_file << "======================================================\n";
  _stats_file << "================== Automatic/Manual ======================\n";
  _stats_file << "Singleton: " << (_safe_ptr_num + _unknown_ptr_num) << "/0" << "\n";
  _stats_file << "Array: " << ((_dyn_sized_arr_num - _dyn_sized_string_num) + _sized_arr_num) << "/" << _sized_arr_num << "\n";
  _stats_file << "String: " << _dyn_sized_string_num << "/0" << "\n";
  _stats_file << "Void: " << (_void_ptr_num - _multi_cast_shared_void_ptr_num) << "/" << _multi_cast_shared_void_ptr_num << "\n";
  _stats_file << "non-void wild ptr: " << "0/" << _non_void_wild_ptr_num << "\n";
  _stats_file << "======================================================\n";

  // _stats_file << "read only data: \n";
  // _stats_file << "\t ptr type: \n";
  // _stats_file << "\t\t singleton: " << _singleton_read << "\n";
  // _stats_file << "\t\t seq: " << _seq_read << "\n";
  // _stats_file << "\t\t wild: " << _wild_read << "\n";
  // _stats_file << "\t\t unknow: " << _unknown_read << "\n";
  // _stats_file << "\t non-ptr type: \n";
  // _stats_file << "\t\t primitive: " << _primitive_read << "\n";
  // _stats_file << "\t\t struct: " << _struct_read << "\n";
  // _stats_file << "\t\t union: " << _union_read << "\n";
  // _stats_file << "\t\t other: " << _other_read << "\n";
  // _stats_file << "write only data: \n";
  // _stats_file << "\t ptr type: \n";
  // _stats_file << "\t\t singleton: " << _singleton_write << "\n";
  // _stats_file << "\t\t seq: " << _seq_write << "\n";
  // _stats_file << "\t\t wild: " << _wild_write << "\n";
  // _stats_file << "\t\t unknow: " << _unknown_write << "\n";
  // _stats_file << "\t non-ptr type: \n";
  // _stats_file << "\t\t primitive: " << _primitive_write << "\n";
  // _stats_file << "\t\t struct: " << _struct_write << "\n";
  // _stats_file << "\t\t union: " << _union_write << "\n";
  // _stats_file << "\t\t other: " << _other_write << "\n";
  // _stats_file << "read/write data: \n";
  // _stats_file << "\t ptr type: \n";
  // _stats_file << "\t\t singleton: " << _singleton_rw << "\n";
  // _stats_file << "\t\t seq: " << _seq_rw << "\n";
  // _stats_file << "\t\t wild: " << _wild_rw << "\n";
  // _stats_file << "\t\t unknow: " << _unknown_rw << "\n";
  // _stats_file << "\t non-ptr type: \n";
  // _stats_file << "\t\t primitive: " << _primitive_rw << "\n";
  // _stats_file << "\t\t struct: " << _struct_rw << "\n";
  // _stats_file << "\t\t union: " << _union_rw << "\n";
  // _stats_file << "\t\t other: " << _other_rw << "\n";

  _stats_file.close();
}

void pdg::KSplitStats::printTable1Raw()
{
  _stats_file.open("table1");
  // 1.a
  _stats_file << _driver_to_kernel_func_call << "\n";
  _stats_file << _kernel_to_driver_func_call << "\n";
  _stats_file << _total_func_size << "/0" << "\n";
  // 1.b
  _stats_file << _fields_deep_copy << "\n";
  _stats_file << _fields_field_analysis << "\n";
  _stats_file << _fields_shared_analysis << "\n";
  _stats_file << (_fields_shared_analysis - _fields_removed_boundary_opt) << "\n";
  // 1.c
  _stats_file <<  _total_ptr_num << "/" << (_shared_ptr_num + _sized_arr_num) << "\n";
  _stats_file << (_total_union_num - _shared_union_num) << "/" << _shared_union_num << "\n";
  _stats_file << (_total_CS - _shared_CS) << "/" << _shared_CS << "\n";
  _stats_file << _total_rcu << "/" << _shared_rcu << "\n";
  _stats_file << _total_seqlock << "/" << _shared_seqlock << "\n";
  _stats_file << (_total_atomic_op - _shared_atomic_op) << "/" << _shared_atomic_op << "\n";
  _stats_file << _total_containerof << "/" << _shared_containerof << "\n";
  // 1.d
  _stats_file << (_safe_ptr_num + _unknown_ptr_num) << "/0" << "\n";
  _stats_file << _sized_arr_num << "/" << _dyn_sized_arr_num << "\n";
  _stats_file << _dyn_sized_string_num << "/0" << "\n";
  _stats_file << (_void_ptr_num - _multi_cast_shared_void_ptr_num) << "/" << _multi_cast_shared_void_ptr_num << "\n";
  _stats_file << "0/" << _non_void_wild_ptr_num << "\n";
  _stats_file.close() ;
}

void pdg::KSplitStats::printTable2Raw()
{
  _stats_file.open("table2");
  _stats_file << _driver_to_kernel_func_call << "/" << _kernel_to_driver_func_call << "\n";
  _stats_file << _total_func_size << "/0" << "\n";
  _stats_file << _fields_deep_copy  << "/" << _fields_shared_analysis << "\n";
  // shared data analysis impact
  _stats_file << _total_ptr_num << "/" << (_shared_ptr_num + _sized_arr_num) << "\n";
  _stats_file << (_total_union_num - _shared_union_num) << "/" << _shared_union_num  << "\n";
  _stats_file << (_total_CS - _shared_CS) << "/" << _shared_CS  << "\n";
  _stats_file << (_total_rcu - _shared_rcu) << "/" << _shared_rcu  << "\n";
  _stats_file << (_total_seqlock - _shared_seqlock) << "/" << _shared_seqlock  << "\n";
  _stats_file << (_total_atomic_op - _shared_atomic_op) << "/" << _shared_atomic_op  << "\n";
  _stats_file << (_total_containerof - _shared_containerof) << "/" << _shared_containerof << "\n";
  // pointer stats
  _stats_file << (_safe_ptr_num + _unknown_ptr_num) << "/0\n";
  // _stats_file << ((_dyn_sized_arr_num - _dyn_sized_string_num) + _sized_arr_num) << "/" << _sized_arr_num << "\n";
  _stats_file <<  _sized_arr_num << "/" << _dyn_sized_arr_num << "\n";
  _stats_file << _dyn_sized_string_num << "/0\n";
  _stats_file << (_void_ptr_num - _multi_cast_shared_void_ptr_num) << "/" << _multi_cast_shared_void_ptr_num << "\n";
  _stats_file <<  "0/" << _non_void_wild_ptr_num << "\n";
  _stats_file.close() ;
}

void pdg::KSplitStats::collectDataStats(TreeNode& tree_node, std::string nescheck_ptr_type)
{
  // this function classify the tree node and accumulate stats
  DIType* dt = tree_node.getDIType();
  if (!dt)
    return;
  // first strip member tag
  std::string field_name = dbgutils::getSourceLevelVariableName(*dt);
  bool is_bitfield = false;
  // need to extract bit field info here because this info will be lost if we strip the tag
  if (dt->isBitField())
    is_bitfield = true;

  if (tree_node.getAccessTags().size() == 0 && !tree_node.isRootNode())
    return;
  dt = dbgutils::stripMemberTag(*dt);
  dt = dbgutils::stripAttributes(*dt);
  // if (dt && tree_node.getAccessTags().size() == 0 && !tree_node.isRootNode())
  _fields_field_analysis++;
  if (dbgutils::isUnionType(*dt))
    _total_union_num++;
  if (!tree_node.is_shared)
    return;
  _fields_shared_analysis++;
  // pointers, basic types, struct, union, array
  if (is_bitfield)
  {
    _shared_bitfield++;
  }
  else if (dbgutils::isPointerType(*dt))
  {
    _shared_ptr_num++;
    collectSharedPointerStats(tree_node, nescheck_ptr_type);
  }
  else if (isa<DIBasicType>(dt))
  {
    _primitive_fields++;
  }
  else if (dbgutils::isStructType(*dt))
  {
    _shared_struct_num++;
    if (dbgutils::isRecursiveType(*dt))
      _recursive_struct_num++;
  }
  else if (dbgutils::isArrayType(*dt))
  {
    _sized_arr_num++;
  }
  else if (dbgutils::isUnionType(*dt))
  {
    _shared_union_num++;
    if (!field_name.empty())
      _shared_tagged_union_num++;
    else
      _shared_anonymous_union_num++;
  }
  else
  {
    _shared_other++; // This should be 0, otherwise, we need to look at this node
    errs() << "unclassified field type: " << tree_node.getTree()->getFunc()->getName() << " - " << dbgutils::getSourceLevelTypeName(*dt) << "\n";
  }
}

void pdg::KSplitStats::collectSharedPointerStats(TreeNode &node, std::string nescheck_ptr_type)
{
  DIType *dt = node.getDIType();

  if (nescheck_ptr_type == "SAFE")
  {
    _safe_ptr_num++;
    // chekc if this is speical memory
    // ioremap
    if (node.is_ioremap)
      _shared_ioremap_num++;
    // user
    if (node.is_user)
      _shared_user_num++;
    // func pointer
    if (dbgutils::isFuncPointerType(*dt))
      _func_ptr_num++;
    // nescheck may fail to classify a string is seq because of library calls
    if (node.is_sentinel)
    {
      _dyn_sized_arr_num++;
      _dyn_sized_sentinel_num++;
      _safe_ptr_num--;
    }
    else if (node.is_string)
    {
      _dyn_sized_arr_num++;
      _dyn_sized_sentinel_num++;
      _dyn_sized_string_num++;
      _safe_ptr_num--;
    }
    // if the void pointer is not casted, it will be classified as a singleton
    if (dbgutils::isVoidPointerType(*dt))
    {
      _void_ptr_num++;
      _safe_ptr_num--;
    }
  }
  else if (nescheck_ptr_type == "SEQ")
  {
    // must be an array because structs are eliminated
    _dyn_sized_arr_num++;
    if (node.is_sentinel)
      _dyn_sized_sentinel_num++;
    else if (node.is_string)
    {
      _dyn_sized_sentinel_num++;
      _dyn_sized_string_num++;
    }
  }
  else if (nescheck_ptr_type == "DYN")
  {
    _dyn_ptr_num++;
    if (dbgutils::isVoidPointerType(*dt))
    {
      _void_ptr_num++;
      _dyn_ptr_num--;
      if (pdgutils::isVoidPointerHasMultipleCasts(node))
      {
        Function* func = node.getTree()->getFunc();
        if (func != nullptr)
          errs() << "find multiple cast void ptr: " << func->getName() << "\n";
        _multi_cast_shared_void_ptr_num++;
      }
      else
        _single_cast_shared_void_ptr_num++;
    }
    else
    {
      _non_void_wild_ptr_num++;
    }
  }
  else if (nescheck_ptr_type == "UNKNOWN")
    _unknown_ptr_num++;
  
}