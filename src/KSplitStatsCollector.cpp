#include "KSplitStatsCollector.hh"
using namespace llvm;

bool EnableAnalysisStats = false;

void pdg::KSplitStats::printDataStats()
{
  _stats_file.open("logs/KSplitStats");
  _stats_file << "Driver interface read fields: " << _drv_read_fields << "\n";
  _stats_file << "Num fields deep copying: " << _fieldsDeepCopyNum << "\n";
  _stats_file << "Filtered Fields: " << (_fieldsDeepCopyNum - _drv_read_fields) << "\n";
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
  _stats_file << _fieldsDeepCopyNum << "\n";
  _stats_file << _fields_field_analysis << "\n";
  _stats_file << _fields_shared_analysis << "\n";
  _stats_file << (_fields_shared_analysis - _fields_removed_boundary_opt) << "\n";
  // 1.c
  _stats_file << _totalPtrNum << "/" << (_shared_ptr_num + _sized_arr_num) << "\n";
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
  _stats_file.close();
}

void pdg::KSplitStats::printTable2Raw()
{
  _stats_file.open("table2");
  _stats_file << _driver_to_kernel_func_call << "\n";
  _stats_file << _kernel_to_driver_func_call << "\n";
  _stats_file << _total_func_size << "/0" << "\n";

  // shared data analysis impact
  _stats_file << _totalPtrNum << "/" << (_shared_ptr_num + _sized_arr_num) << "\n";
  _stats_file << (_total_union_num - _shared_union_num) << "/" << _shared_union_num << "\n";
  _stats_file << (_total_CS - _shared_CS) << "/" << _shared_CS << "\n";
  _stats_file << (_total_rcu - _shared_rcu) << "/" << _shared_rcu << "\n";
  _stats_file << (_total_seqlock - _shared_seqlock) << "/" << _shared_seqlock << "\n";
  _stats_file << (_total_atomic_op - _shared_atomic_op) << "/" << _shared_atomic_op << "\n";
  _stats_file << (_total_containerof - _shared_containerof) << "/" << _shared_containerof << "\n";
  // pointer stats
  _stats_file << (_safe_ptr_num + _unknown_ptr_num) << "/0\n";
  _stats_file << _sized_arr_num << "/" << _dyn_sized_arr_num << "\n";
  _stats_file << _dyn_sized_string_num << "/0\n";
  _stats_file << (_void_ptr_num - _multi_cast_shared_void_ptr_num) << "/" << _multi_cast_shared_void_ptr_num << "\n";
  _stats_file << "0/" << _non_void_wild_ptr_num << "\n";
  _stats_file.close();
}

void pdg::KSplitStats::printSoKClassifiedFields()
{
  errs() << "Shared Fields Classification:\n";
  errs() << "----------------------------\n";
  errs() << "Function Pointer Number: " << funcPtrNum << "\n";
  errs() << "Data Corruption Function Pointer Number: " << DCFuncPtrNum << "\n";
  errs() << "Data Leakage Function Pointer Number: " << DLFuncPtrNum << "\n";
  errs() << "Data Pointer Number: " << dataPtrNum << "\n";
  errs() << "Data Corruption Data Pointer Number: " << DCDataPtrNum << "\n";
  errs() << "Data Leakage Data Pointer Number: " << DLDataPtrNum << "\n";
  errs() << "----------------------------\n";
}

void pdg::KSplitStats::collectDataStats(TreeNode &treeNode, std::string nescheck_ptr_type, Function &func, int paramIdx, bool is_driver_func)
{
  // Implementation stub - simplified for basic compilation
  _fields_field_analysis++;
}

void pdg::KSplitStats::collectSharedPointerStats(TreeNode &node, std::string nescheck_ptr_type)
{
  // Implementation stub - simplified for basic compilation
}

void pdg::KSplitStats::collectTotalPointerStats(llvm::DIType &dt)
{
  // Implementation stub
}

void pdg::KSplitStats::collectInferredStringStats(std::set<std::string> &annotations)
{
  // Implementation stub
}

void pdg::KSplitStats::printStats()
{
  printDataStats();
}

void pdg::KSplitStats::printDrvAPIStats()
{
  std::ofstream drvAPIFile;
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

  drvAPIFile.close();
}

void pdg::KSplitStats::printRiskyPatterns()
{
  errs() << "-------------------------------------------------\n";
  errs() << "| Pattern Name         | Number of Occurrences |\n";
  errs() << "-------------------------------------------------\n";

  std::vector<std::pair<std::string, int>> patterns = {
      {"Risky ptr arith field num", riskyPtrArithField},
      {"Risky index field num", riskyIndexField},
      {"Risky RAW bound field num", riskyBoundRAWField},
      {"Risky cond field num", riskyCondField},
      {"Risky RAW cond field num", riskyCondRAWField},
      {"Risky cond func Ptr", riskyCondFuncField},
      {"Risky sensitive API field num", riskyFieldUsedInSensitiveAPI},
      {"Risky lock field num", riskyLockField},
      {"Risky kernel alloc API", kernelAllocAPI},
      {"Risky kernel RAW alloc API", kernelRAWAllocAPI},
      {"Risky kernel dealloc API", kernelDeallocAPI},
      {"Risky kernel RAW dealloc API", kernelRAWDeallocAPI},
      {"Risky ptr arith taint field num ", riskyPtrArithFieldTaint},
      {"Risky index taint field num", riskyIndexFieldTaint},
      {"Risky cond taint field num", riskyCondFieldTaint},
      {"Risky sensitive API taint field num", riskyFieldUsedInSensitiveAPITaint}
      };

  for (const auto &pattern : patterns) {
    std::ostringstream oss;
    oss << "| " << std::left << std::setw(22) << pattern.first
        << std::right << std::setw(10) << "  " << std::right << std::setw(10) << pattern.second << " |\n";
    errs() << oss.str();
  }

  errs() << "-------------------------------------------------\n";
}