#ifndef KSPLIT_STATS_COLLECTOR_H_
#define KSPLIT_STATS_COLLECTOR_H_
#include "LLVMEssentials.hh"
#include "DebugInfoUtils.hh"
#include "Tree.hh"
#include <set>
#include <fstream>
#include <sstream>

namespace pdg
{
  class KSplitStats
  {
  public:
    KSplitStats() = default;
    KSplitStats(const KSplitStats &) = delete;
    KSplitStats(KSplitStats &&) = delete;
    KSplitStats &operator=(const KSplitStats &) = delete;
    KSplitStats &operator=(KSplitStats &&) = delete;
    static KSplitStats &getInstance()
    {
      static KSplitStats ks{};
      return ks;
    }
    // void increaseKernelToDriverCallNum(unsigned num) { _kernel_to_driver_func_call = (num == 0 ? _kernel_to_driver_func_call + 1 : _kernel_to_driver_func_call + num) ; }
    // void increaseDriverToKernelCallNum(unsigned num) { _driver_to_kernel_func_call = (num == 0 ? _driver_to_kernel_func_call + 1 : _driver_to_kernel_func_call + num) ; }
    // void increaseTotalFuncSize(unsigned num) { _total_func_size = (num == 0 ? _total_func_size + 1 : _total_func_size + num); }
    // void increaseTotalPtrNum(unsigned num = 0) { _total_ptr_num = (num == 0 ? _total_ptr_num + 1 : _total_ptr_num + num); }
    // void increaseSharedPtrNum() { _shared_ptr_num++; }
    // void increaseSafePtrNum() { _safe_ptr_num++; }
    // void increaseTotalVoidPtrNum() { _void_ptr_num++; }
    // void increaseSharedVoidPtrNum() { _shared_void_ptr_num++; }
    // void increasePtrArithNum() { _ptr_arith_num++; }
    // void increasePtrGEPArithSDNum() { _ptr_gep_arith_sd++; }
    // void increasePtrtoIntArithSDNum() { _ptr_ptrtoint_arith_sd++; }
    // void increasePtrGEPArithDaaNum() { _ptr_gep_arith_daa++; }
    // void increasePtrtoIntArithDaaNum() { _ptr_ptrtoint_arith_daa++; }
    // void increaseUnhandledVoidPtrNum() { _unhandled_void_ptr_num++; }
    // void increaseUnhandledVoidPtrSDNum() { _unhandled_void_ptr_sd_num++; }
    // void increaseStringNum() { _string_num++; }
    // void increaseInferredStringNum() { _inferred_string_num++; }
    // void increaseArrayNum() { _array_num++; }
    // void increaseUnhandledArrayNum() { _unhandled_array_num++; }
    // void increaseStructArrayNum() { _struct_array_num++; }
    // void increaseFuncPtrNum() { _func_ptr_num++; }
    // void increaseNonVoidWildPtrNum() { _non_void_wild_ptr_num++; }
    // void increaseVoidWildPtrNum() { _void_wild_ptr_num++; }
    // void increaseUnknownPtrNum() { _unknown_ptr_num++; }
    // void increaseFieldsDeepCopy(unsigned num = 0) { _fields_deep_copy = (num == 0 ? _fields_deep_copy + 1 : _fields_deep_copy + num); }
    // void increaseFieldsFieldAccess() { _fields_field_analysis++; }
    // void increaseFieldsSharedData() { _fields_shared_analysis++; }
    // void increaseFieldsBoundaryOpt() { _fields_removed_boundary_opt++; }
    // void increaseTotalUnionNum() { _total_union_num++; }
    // void increaseTotalUnionPtrNum() { _total_union_ptr_num++; }
    // void increaseSharedUnionNum() { _shared_union_num++; }
    // void increaseSharedTaggedUnionNum() { _shared_tagged_union_num++; }
    // void increaseSharedUnionPtrNum() { _shared_union_ptr_num++; }
    // void increaseTotalCS() { _total_CS++; }
    // void increaseSharedCS() { _shared_CS++; }
    // void increaseTotalAtomicOps() { _total_atomic_op++; }
    // void increaseSharedAtomicOps() { _shared_atomic_op++; }
    // void increaseTotalRCU() { _total_rcu++; }
    // void increaseSharedRCU() { _shared_rcu++; }
    // void increaseTotalSeqlock() { _total_seqlock++; }
    // void increaseSharedSeqlock() { _shared_seqlock++; }
    // void increaseTotalNestLock() { _total_nest_lock++; }
    // void increaseSharedNestLock() { _shared_nest_lock++; }
    // void increaseTotalBarrier() { _total_barrier++; }
    // void increaseSharedBarrier() { _shared_barrier++; }
    // void increaseTotalBitfield() { _total_bitfield++; }
    // void increaseSharedBitfield() { _shared_bitfield++; }
    // void increaseTotalContainerof() { _total_containerof++; }
    // void increaseSharedContainerof() { _shared_containerof++; }
    // void increaseSharedIORemap() { _shared_ioremap_num++; }
    // void increaseSharedUser() { _shared_user_num++; }
    // void increaseSharedSentinelArray() { _shared_sentinel_array++; }
    // void increaseControlDataFieldNum() { _control_data_field_num++; }
    // void increaseReadDataFieldNum() { _read_data_field++; }
    // void increaseWrittenDataFieldNum() { _written_data_field++; }
    // void increaseParamNum() { _param_num++; }
    void collectTotalPointerStats(llvm::DIType &dt);
    // void collectSharedPointerStats(llvm::DIType &dt, std::string var_name, std::string func_name);
    void collectDataStats(TreeNode &tree_node, std::string nescheck_ptr_type);
    void collectSharedPointerStats(TreeNode &tree_node, std::string nescheck_ptr_type);
    void collectInferredStringStats(std::set<std::string> &annotations);
    void printStats();
    void printDataStats();
    void printStatsRaw();

  public:
    std::ofstream _stats_file;
    // 1.a complexity
    unsigned _driver_to_kernel_func_call = 0;
    unsigned _kernel_to_driver_func_call = 0;
    unsigned _total_func_size = 0;
    // 1.b fields analysis stats
    int _fields_deep_copy = 0;
    int _fields_field_analysis = 0;
    int _fields_shared_analysis = 0;
    int _fields_removed_boundary_opt = 0;
    // 1.c data classification
    // primitive types
    unsigned _primitive_fields = 0;
    // unsigned _total_bitfield = 0;
    unsigned _shared_bitfield = 0;
    // pointers
    unsigned _total_ptr_num = 0;
    unsigned _shared_ptr_num = 0;
    // safe pointers (singleton)
    unsigned _safe_ptr_num = 0;
    unsigned _void_ptr_num = 0;
    unsigned _no_cast_void_pointer = 0;
    unsigned _func_ptr_num = 0;
    unsigned _shared_ioremap_num = 0;
    unsigned _shared_user_num = 0;
    // seq pointers
    // array sized/dyn
    unsigned _dyn_sized_arr_num = 0;
    unsigned _dyn_sized_sentinel_num = 0;
    unsigned _dyn_sized_string_num = 0;
    // dyn pointers
    unsigned _dyn_ptr_num;
    unsigned _cast_void_ptr_num = 0;
    unsigned _single_cast_shared_void_ptr_num = 0;
    unsigned _multi_cast_shared_void_ptr_num = 0;
    unsigned _non_void_wild_ptr_num = 0;
    // unknown pointers    
    unsigned _unknwon_ptr_num = 0;

    // complex types
    unsigned _shared_struct_num = 0;
    unsigned _recursive_struct_num = 0;
    unsigned _total_union_num = 0;
    unsigned _shared_union_num = 0;
    unsigned _shared_tagged_union_num = 0;
    unsigned _shared_anonymous_union_num = 0;
    unsigned _sized_arr_num = 0;
    unsigned _sized_sentinel_num = 0;
    unsigned _sized_string_num = 0;
    unsigned _sized_array_collocated_num = 0;

    // shared / private stats

    // atomic region
    unsigned _total_CS = 0;
    unsigned _shared_CS = 0;
    unsigned _total_atomic_op = 0;
    unsigned _shared_atomic_op = 0;
    // unsigned _total_union_ptr_num = 0;
    unsigned _shared_union_ptr_num = 0;
    unsigned _ptr_arith_num = 0;
    unsigned _ptr_gep_arith_daa = 0;
    unsigned _ptr_ptrtoint_arith_daa = 0;
    unsigned _ptr_gep_arith_sd = 0;
    unsigned _ptr_ptrtoint_arith_sd = 0;
    unsigned _total_rcu = 0;
    unsigned _shared_rcu = 0;
    unsigned _total_seqlock = 0;
    unsigned _shared_seqlock = 0;
    unsigned _total_nest_lock = 0;
    unsigned _shared_nest_lock = 0;
    unsigned _total_barrier = 0;
    unsigned _shared_barrier = 0;
    unsigned _total_containerof = 0;
    unsigned _shared_containerof = 0;
    unsigned _shared_sentinel_array = 0;
    unsigned _shared_other = 0;

    // classify shared data passed from driver to kernel
    unsigned _union_read = 0;
    unsigned _union_write = 0;
    unsigned _union_rw = 0;
    unsigned _primitive_read = 0;
    unsigned _primitive_write = 0;
    unsigned _primitive_rw = 0;
    unsigned _struct_read = 0;
    unsigned _struct_write = 0;
    unsigned _struct_rw = 0;
    unsigned _other_read = 0;
    unsigned _other_write = 0;
    unsigned _other_rw = 0;

    // pointer shared data passed from driver to kernel
    unsigned _singleton_read = 0;
    unsigned _singleton_write = 0;
    unsigned _singleton_rw = 0;
    unsigned _seq_read = 0;
    unsigned _seq_write = 0;
    unsigned _seq_rw = 0;
    unsigned _wild_read = 0;
    unsigned _wild_write = 0;
    unsigned _wild_rw = 0;
    unsigned _unknown_read = 0;
    unsigned _unknown_write = 0;
    unsigned _unknown_rw = 0;

    // outdated
    unsigned _unhandled_array_num = 0; // for some dyn size arr, we could try infer it's size
    unsigned _unhandled_void_ptr_num = 0;
    unsigned _unhandled_void_ptr_sd_num = 0;
    unsigned _handled_void_ptr_num = 0;
    unsigned _string_num = 0;
    unsigned _void_wild_ptr_num = 0;
    unsigned _inferred_string_num = 0;
    unsigned _char_array_num = 0;
    unsigned _struct_array_num = 0;
    unsigned _unknown_ptr_num = 0;
  };
}

#endif