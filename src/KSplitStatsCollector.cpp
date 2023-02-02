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
  _stats_file << "Singleton: " << (_safe_ptr_num + _unknown_ptr_num) << "/0"
              << "\n";
  _stats_file << "Array: " << ((_dyn_sized_arr_num - _dyn_sized_string_num) + _sized_arr_num) << "/" << _sized_arr_num << "\n";
  _stats_file << "String: " << _dyn_sized_string_num << "/0"
              << "\n";
  _stats_file << "Void: " << (_void_ptr_num - _multi_cast_shared_void_ptr_num) << "/" << _multi_cast_shared_void_ptr_num << "\n";
  _stats_file << "non-void wild ptr: "
              << "0/" << _non_void_wild_ptr_num << "\n";
  _stats_file << "======================================================\n";

  _stats_file << " ====== driver data accesses ======\n";
  _stats_file << "Driver read only fields: " << _driver_read_fields << " - " << ((float)_driver_read_fields / _fields_shared_analysis * 100) << "%"
              << "\n";
  _stats_file << "Driver read only ptr fields: " << _driver_read_ptr_fields << " - " << ((float)_driver_read_ptr_fields / _shared_ptr_num * 100) << "%"
              << "\n";
  _stats_file << "Driver write only fields: " << _driver_write_fields << " - " << ((float)_driver_write_fields / _fields_shared_analysis * 100) << "%"
              << "\n";
  _stats_file << "Driver write only ptr fields: " << _driver_write_ptr_fields << " - " << ((float)_driver_write_ptr_fields / _shared_ptr_num * 100) << "%"
              << "\n";
  _stats_file << "Driver write only func ptr fields: " << _driver_write_func_ptr_fields << " - " << ((float)_driver_write_func_ptr_fields / _driver_write_ptr_fields * 100) << "%"
              << "\n";
  _stats_file << "Driver write through ptr fields: " << _driver_write_through_ptr_fields << "\n";
  _stats_file << "Driver access fields: " << _driver_access_fields << " - " << ((float)_driver_access_fields / _fields_shared_analysis * 100) << "%"
              << "\n";
  _stats_file << "Driver access ptr fields: " << _driver_access_ptr_fields << " - " << ((float)_driver_access_ptr_fields / _shared_ptr_num * 100) << "%"
              << "\n";
  _stats_file << "Driver readable fields: " << (_driver_access_fields + _driver_read_fields) << "\n";
  _stats_file << "Driver readable ptr fields: " << (_driver_access_ptr_fields + _driver_read_ptr_fields) << "\n";

  _stats_file << "No. Kernel readable fields: " << kernelReadableFields << "\n";
  _stats_file << "No. Kernel readable ptr fields: " << kernelReadablePtrFields << "\n";
  _stats_file << "No. Kernel readable non-ptr fields: " << (kernelReadableFields - kernelReadablePtrFields) << "\n";
  _stats_file << "No. Driver writable fields: " << (_driver_access_fields + _driver_write_fields) << "\n";
  _stats_file << "No. Driver writable ptr fields: " << (_driver_access_ptr_fields + _driver_write_ptr_fields) << "\n";
  _stats_file << "No. Driver writable non-ptr fields: " << (_driver_access_fields + _driver_write_fields - _driver_access_ptr_fields - _driver_write_ptr_fields) << "\n";
  _stats_file << "No. Shared fields kernel may read after driver write: " << kernelRAWDriverSharedFields << "\n";
  _stats_file << "No. Shared ptr fields kernel may read after driver write: " << kernelRAWDriverSharedPtrFields << "\n";
  _stats_file << "No. Shared non-Ptr fields kernel may read after driver write: " << (kernelRAWDriverSharedFields - kernelRAWDriverSharedPtrFields) << "\n";
  _stats_file << "No. Shared fields kernel read driver update: " << kernelReadDriverUpdateSharedFields << "\n";
  _stats_file << "No. Shared ptr fields kernel read driver update: " << kernelReadDriverUpdateSharedPtrFields << "\n";
  _stats_file << "No. Shared non-ptr fields kernel read driver update: " << (kernelReadDriverUpdateSharedFields - kernelReadDriverUpdateSharedPtrFields) << "\n";

  // per shared type stats
  _stats_file << " ----------------  Per Type Stat ----------------- "
              << "\n";
  _stats_file << "No. Shared struct types: " << numSharedStructType << "\n";
  // _stats_file << "No. Kernel readable fields (per type): " << kernelReadableFieldsPerTy << "\n";
  // _stats_file << "No. Kernel readable ptr fields (per type): " << kernelReadablePtrFieldsPerTy << "\n";
  // _stats_file << "No. Kernel readable non-ptr fields (per type): " << (kernelReadableFieldsPerTy - kernelReadablePtrFieldsPerTy) << "\n";
  // _stats_file << "No. Driver writable fields (per type): " << driverWritableFieldsPerTy << "\n";
  // _stats_file << "No. Driver writable ptr fields (per type): " << driverWritablePtrFieldsPerTy << "\n";
  // _stats_file << "No. Driver writable non-ptr fields (per type): " << (driverWritableFieldsPerTy - driverWritablePtrFieldsPerTy) << "\n";
  // _stats_file << "No. Shared fields kernel read driver update: " << kernelReadDriverUpdateSharedFieldsPerTy << "\n";
  // _stats_file << "No. Shared ptr fields kernel read driver update: " << kernelReadDriverUpdateSharedPtrFieldsPerTy << "\n";
  // _stats_file << "No. Shared func ptr fields kernel read driver update: " << kernelReadDriverUpdateSharedFuncPtrFieldsPerTy << "\n";
  // _stats_file << "No. Shared non-ptr fields kernel read driver update: " << (kernelReadDriverUpdateSharedFieldsPerTy - kernelReadDriverUpdateSharedPtrFieldsPerTy) << "\n";
  _stats_file << "No. RW ptr: " << numRWPtr << "\n";
  _stats_file << "No. RW func ptr: " << numRWFuncPtr << "\n";
  _stats_file << "No. RW ptr used in branch: " << numRWPtrCondVar << "\n";
  _stats_file << "No. RW ptr used in ptr arith: " << numRWPtrInPtrArith << "\n";
  _stats_file << "No. RW non ptr: " << numRWNonPtr << "\n";
  _stats_file << "No. RW non ptr used in branch: " << numRWNonPtrCondVar << "\n";
  _stats_file << "No. RW non ptr used in ptr arith: " << numRWNonPtrInPtrArith << "\n";
  _stats_file.close();
}

void pdg::KSplitStats::printTable1Raw()
{
  _stats_file.open("table1");
  // 1.a
  _stats_file << _driver_to_kernel_func_call << "\n";
  _stats_file << _kernel_to_driver_func_call << "\n";
  _stats_file << _total_func_size << "/0"
              << "\n";
  // 1.b
  _stats_file << _fields_deep_copy << "\n";
  _stats_file << _fields_field_analysis << "\n";
  _stats_file << _fields_shared_analysis << "\n";
  _stats_file << (_fields_shared_analysis - _fields_removed_boundary_opt) << "\n";
  // 1.c
  _stats_file << _total_ptr_num << "/" << (_shared_ptr_num + _sized_arr_num) << "\n";
  _stats_file << (_total_union_num - _shared_union_num) << "/" << _shared_union_num << "\n";
  _stats_file << (_total_CS - _shared_CS) << "/" << _shared_CS << "\n";
  _stats_file << _total_rcu << "/" << _shared_rcu << "\n";
  _stats_file << _total_seqlock << "/" << _shared_seqlock << "\n";
  _stats_file << (_total_atomic_op - _shared_atomic_op) << "/" << _shared_atomic_op << "\n";
  _stats_file << _total_containerof << "/" << _shared_containerof << "\n";
  // 1.d
  _stats_file << (_safe_ptr_num + _unknown_ptr_num) << "/0"
              << "\n";
  _stats_file << _sized_arr_num << "/" << _dyn_sized_arr_num << "\n";
  _stats_file << _dyn_sized_string_num << "/0"
              << "\n";
  _stats_file << (_void_ptr_num - _multi_cast_shared_void_ptr_num) << "/" << _multi_cast_shared_void_ptr_num << "\n";
  _stats_file << "0/" << _non_void_wild_ptr_num << "\n";
  _stats_file.close();
}

void pdg::KSplitStats::printTable2Raw()
{
  _stats_file.open("table2");
  _stats_file << _driver_to_kernel_func_call << "\n";
  _stats_file << _kernel_to_driver_func_call << "\n";
  _stats_file << _total_func_size << "/0"
              << "\n";

  // XXX: Not needed for table2
  //_stats_file << _fields_deep_copy  << "/" << _fields_shared_analysis << "\n";
  // shared data analysis impact
  _stats_file << _total_ptr_num << "/" << (_shared_ptr_num + _sized_arr_num) << "\n";
  _stats_file << (_total_union_num - _shared_union_num) << "/" << _shared_union_num << "\n";
  _stats_file << (_total_CS - _shared_CS) << "/" << _shared_CS << "\n";
  _stats_file << (_total_rcu - _shared_rcu) << "/" << _shared_rcu << "\n";
  _stats_file << (_total_seqlock - _shared_seqlock) << "/" << _shared_seqlock << "\n";
  _stats_file << (_total_atomic_op - _shared_atomic_op) << "/" << _shared_atomic_op << "\n";
  _stats_file << (_total_containerof - _shared_containerof) << "/" << _shared_containerof << "\n";
  // pointer stats
  _stats_file << (_safe_ptr_num + _unknown_ptr_num) << "/0\n";
  // _stats_file << ((_dyn_sized_arr_num - _dyn_sized_string_num) + _sized_arr_num) << "/" << _sized_arr_num << "\n";
  _stats_file << _sized_arr_num << "/" << _dyn_sized_arr_num << "\n";
  _stats_file << _dyn_sized_string_num << "/0\n";
  _stats_file << (_void_ptr_num - _multi_cast_shared_void_ptr_num) << "/" << _multi_cast_shared_void_ptr_num << "\n";
  _stats_file << "0/" << _non_void_wild_ptr_num << "\n";
  _stats_file.close();
}

void pdg::KSplitStats::collectDataStats(TreeNode &tree_node, std::string nescheck_ptr_type, Function &func, int paramIdx, bool is_driver_func)
{
  // this function classify the tree node and accumulate stats
  DIType *dt = tree_node.getDIType();
  if (!dt)
    return;
  if (!tree_node.isStructField())
    return;
  std::string fieldName = tree_node.getSrcHierarchyName();
  std::string funcName = func.getName().str();

  // need to extract bit field info here because this info will be lost if we strip the tag
  bool isBitField = dt->isBitField();
  bool isFuncPtrField = dbgutils::isFuncPointerType(*dt);

  auto access_tags = tree_node.getAccessTags();
  if (access_tags.size() == 0)
    return;

  dt = dbgutils::stripMemberTag(*dt);
  dt = dbgutils::stripAttributes(*dt);
  // if (dt && tree_node.getAccessTags().size() == 0 && !tree_node.isRootNode())
  _fields_field_analysis++;
  if (dbgutils::isUnionType(*dt))
    _total_union_num++;
  if (!tree_node.is_shared)
    return;

  bool isPtrType = dbgutils::isPointerType(*dt);
  // collect stats of per driver API data access stats
  if (is_driver_func)
  {
    assert(_drv_api_acc_map.find(&func) != _drv_api_acc_map.end() && "API Collect: cannot find driver name\n");
    assert(_drv_api_ptr_acc_map.find(&func) != _drv_api_ptr_acc_map.end() && "API Ptr Collect: cannot find driver name\n");
    auto &fieldAccTuple = _drv_api_acc_map[&func];
    auto &ptrFieldAccTuple = _drv_api_ptr_acc_map[&func];

    // collect read/write stats for the pointed value
    if (isPtrType)
    {
      // obtain the pointed value node
      if (tree_node.numOfChild() == 1)
      {
        auto pointedObjNode = tree_node.getChildNodes()[0];
        auto objNodeAccTags = pointedObjNode->getAccessTags();
        if (objNodeAccTags.size() > 0)
        {
          if (objNodeAccTags.find(AccessTag::DATA_WRITE) != objNodeAccTags.end())
          {
            _driver_write_through_ptr_fields++;
            errs() << "write through pointer: " << fieldName << " in func " << funcName << "\n";
          }
        }
      }
    }

    // collects pointer updates when kernel pass a parameter to driver, and driver updates the
    // parameter
    if (access_tags.size() == 2)
    {
      _driver_access_fields++;
      std::get<2>(fieldAccTuple) += 1;
      if (isPtrType)
      {
        _driver_access_ptr_fields++;
        std::get<2>(ptrFieldAccTuple) += 1;
        // chekcing pointer update cases
        if (isFuncPtrField)
        {
          _driver_write_func_ptr_fields += 1;
          errs() << "driver update ptr field (func): " << fieldName << " - "
                 << funcName << " - " << tree_node.getDepth() << " - " << paramIdx << "\n";
        }
        else
        {
          errs() << "driver update ptr field (non-func): " << fieldName << " - "
                 << funcName << " - " << tree_node.getDepth() << " - " << paramIdx << "\n";
          errs() << "addr var size: " << tree_node.getAddrVars().size() << "\n";
          for (auto addrVar : tree_node.getAddrVars())
          {
            if (auto inst = dyn_cast<Instruction>(addrVar))
              errs() << "\t" << *inst << " in " << inst->getFunction()->getName() << "\n";
          }
        }
      }
      else
        errs() << "driver access field: " << fieldName << " - " << funcName << "\n";
    }
    // collect read only, write only fields
    else if (access_tags.size() == 1)
    {
      if (access_tags.find(AccessTag::DATA_READ) != access_tags.end())
      {
        _driver_read_fields++;
        std::get<0>(fieldAccTuple) += 1;
        if (isPtrType)
        {
          _driver_read_ptr_fields++;
          std::get<0>(ptrFieldAccTuple) += 1;
          errs() << "driver read only ptr data: " << fieldName << " - " << funcName << "\n";
        }
        else
          errs() << "driver read only data: " << fieldName << " - " << funcName << "\n";
      }
      else if (access_tags.find(AccessTag::DATA_WRITE) != access_tags.end())
      {
        _driver_write_fields++;
        std::get<1>(fieldAccTuple) += 1;
        // TODO: debugging purpose
        errs() << "driver update only field: " << fieldName << " - " << funcName << "\n";
        if (!tree_node.isRootNode())
        {
          if (isPtrType)
          {
            _driver_write_ptr_fields++;
            std::get<1>(ptrFieldAccTuple) += 1;
            if (isFuncPtrField)
            {
              _driver_write_func_ptr_fields += 1;
              errs() << "driver update only ptr field (func): " << fieldName << " - "
                     << funcName << " - " << tree_node.getDepth() << " - " << paramIdx << "\n";
            }
            else
            {
              errs() << "driver update only ptr field (non-func): " << fieldName << " - "
                     << funcName << " - " << tree_node.getDepth() << " - " << paramIdx << "\n";
              errs() << "addr var size: " << tree_node.getAddrVars().size() << "\n";
              for (auto addrVar : tree_node.getAddrVars())
              {
                if (auto inst = dyn_cast<Instruction>(addrVar))
                  errs() << "\t" << *inst << " in " << inst->getFunction()->getName() << "\n";
              }
            }
          }
        }
      }
    }
  }
  else
  {
    // collect kernel stats
    if (access_tags.find(AccessTag::DATA_READ) != access_tags.end())
    {
      kernelReadableFields++;
      if (isPtrType)
        kernelReadablePtrFields++;
    }
  }

  _fields_shared_analysis++;
  // pointers, basic types, struct, union, array
  if (isBitField)
  {
    _shared_bitfield++;
  }
  else if (isPtrType)
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
    if (!fieldName.empty())
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
        Function *func = node.getTree()->getFunc();
        if (func != nullptr)
          errs() << "find multiple cast void ptr: " << func->getName() << "\n";
        _multi_cast_shared_void_ptr_num++;
      }
      else
        _single_cast_shared_void_ptr_num++;
    }
    else
    {
      errs() << "non-void wild ptr found in " << node.getFunc()->getName() << "\n";
      _non_void_wild_ptr_num++;
    }
  }
  else if (nescheck_ptr_type == "UNKNOWN")
    _unknown_ptr_num++;
}

void pdg::KSplitStats::printDrvAPIStats()
{
  std::ofstream drvAPIFile;
  // store API access field for each function
  drvAPIFile.open("API_DATA_ACC.csv");
  // field access for each function
  for (auto iter = _drv_api_acc_map.begin(); iter != _drv_api_acc_map.end(); ++iter)
  {
    auto stat_tuple = iter->second;
    drvAPIFile << iter->first->getName().str() << ","
               << std::get<0>(stat_tuple) << ", "
               << std::get<1>(stat_tuple) << ","
               << std::get<2>(stat_tuple) << "\n";
  }
  // ptr field access stat for each function
  for (auto iter = _drv_api_ptr_acc_map.begin(); iter != _drv_api_acc_map.end(); ++iter)
  {
    auto stat_tuple = iter->second;
    drvAPIFile << iter->first->getName().str() << ","
               << std::get<0>(stat_tuple) << ", "
               << std::get<1>(stat_tuple) << ","
               << std::get<2>(stat_tuple) << "\n";
  }

  drvAPIFile.close();
}