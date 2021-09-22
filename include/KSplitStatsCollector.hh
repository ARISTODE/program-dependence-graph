#ifndef KSPLIT_STATS_COLLECTOR_H_
#define KSPLIT_STATS_COLLECTOR_H_
#include "LLVMEssentials.hh"
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
    void increaseKernelToDriverCallNum(unsigned num) { _kernel_to_driver_func_call = (num == 0 ? _kernel_to_driver_func_call + 1 : _kernel_to_driver_func_call + num) ; }
    void increaseDriverToKernelCallNum(unsigned num) { _driver_to_kernel_func_call = (num == 0 ? _driver_to_kernel_func_call + 1 : _driver_to_kernel_func_call + num) ; }
    void increaseTotalFuncSize(unsigned num) { _total_func_size = (num == 0 ? _total_func_size + 1 : _total_func_size + num); }
    void increaseTotalPtrNum(unsigned num = 0) { _total_ptr_num = (num == 0 ? _total_ptr_num + 1 : _total_ptr_num + num); }
    void increaseSharedPtrNum() { _shared_ptr_num++; }
    void increaseSafePtrNum() { _safe_ptr_num++; }
    void increaseVoidPtrNum() { _void_ptr_num++; }
    void increasePtrArithNum() { _ptr_arith_num++; }
    void increasePtrGEPArithSDNum() { _ptr_gep_arith_sd++; }
    void increasePtrtoIntArithSDNum() { _ptr_ptrtoint_arith_sd++; }
    void increasePtrGEPArithDaaNum() { _ptr_gep_arith_daa++; }
    void increasePtrtoIntArithDaaNum() { _ptr_ptrtoint_arith_daa++; }
    void increaseUnhandledVoidPtrNum() { _unhandled_void_ptr_num++; }
    void increaseUnhandledVoidPtrSDNum() { _unhandled_void_ptr_sd_num++; }
    void increaseStringNum() { _string_num++; }
    void increaseArrayNum() { _array_num++; }
    void increaseUnhandledArrayNum() { _unhandled_array_num++; }
    void increaseStructArrayNum() { _struct_array_num++; }
    void increaseFuncPtrNum() { _func_ptr_num++; }
    void increaseNonVoidWildPtrNum() { _non_void_wild_ptr_num++; }
    void increaseVoidWildPtrNum() { _void_wild_ptr_num++; }
    void increaseUnknownPtrNum() { _unknown_ptr_num++; }
    void increaseFieldsDeepCopy(unsigned num = 0) { _fields_deep_copy = (num == 0 ? _fields_deep_copy + 1 : _fields_deep_copy + num); }
    void increaseFieldsFieldAccess() { _fields_field_analysis++; }
    void increaseFieldsSharedData() { _fields_shared_analysis++; }
    void increaseFieldsBoundaryOpt() { _fields_removed_boundary_opt++; }
    void increaseTotalUnionNum() { _total_union_num++; }
    void increaseSharedUnionNum() { _shared_union_num++; }
    void increaseTotalCS() { _total_CS++; }
    void increaseSharedCS() { _shared_CS++; }
    void increaseTotalAtomicOps() { _total_atomic_op++; }
    void increaseSharedAtomicOps() { _shared_atomic_op++; }
    void increaseTotalRCU() { _total_rcu++; }
    void increaseSharedRCU() { _shared_rcu++; }
    void increaseTotalSeqlock() { _total_seqlock++; }
    void increaseSharedSeqlock() { _shared_seqlock++; }
    void increaseTotalNestLock() { _total_nest_lock++; }
    void increaseSharedNestLock() { _shared_nest_lock++; }
    void increaseTotalBarrier() { _total_barrier++; }
    void increaseSharedBarrier() { _shared_barrier++; }
    void increaseTotalBitfield() { _total_bitfield++; }
    void increaseSharedBitfield() { _shared_bitfield++; }
    void increaseTotalContainerof() { _total_containerof++; }
    void increaseSharedContainerof() { _shared_containerof++; }
    void increaseTotalIORemap() { _total_ioremap++; }
    void increaseSharedIORemap() { _shared_ioremap++; }
    void collectStats(llvm::DIType &dt, std::set<std::string> &annotations);
    void printStats();
    void printStatsRaw();

  private:
    std::ofstream _stats_file;
    unsigned _driver_to_kernel_func_call = 0;
    unsigned _kernel_to_driver_func_call = 0;
    unsigned _total_func_size = 0;
    unsigned _shared_ptr_num = 0;
    unsigned _safe_ptr_num = 0;
    unsigned _void_ptr_num = 0;
    unsigned _unhandled_void_ptr_num = 0;
    unsigned _unhandled_void_ptr_sd_num = 0;
    unsigned _handled_void_ptr_num = 0;
    unsigned _string_num = 0;
    unsigned _array_num = 0;
    unsigned _unhandled_array_num = 0;
    unsigned _struct_array_num = 0;
    unsigned _non_void_wild_ptr_num = 0;
    unsigned _void_wild_ptr_num = 0;
    unsigned _unknown_ptr_num = 0;
    unsigned _func_ptr_num = 0;
    // fields analysis stats
    int _fields_deep_copy = 0;
    int _fields_field_analysis = 0;
    int _fields_shared_analysis = 0;
    int _fields_removed_boundary_opt = 0;
    // shared / private stats
    unsigned _total_ptr_num = 0;
    unsigned _total_union_num = 0;
    unsigned _shared_union_num = 0;
    unsigned _ptr_arith_num = 0;
    unsigned _ptr_gep_arith_daa = 0;
    unsigned _ptr_ptrtoint_arith_daa = 0;
    unsigned _ptr_gep_arith_sd = 0;
    unsigned _ptr_ptrtoint_arith_sd = 0;
    unsigned _total_CS = 0;
    unsigned _shared_CS = 0;
    unsigned _total_atomic_op = 0;
    unsigned _shared_atomic_op = 0;
    unsigned _total_rcu = 0;
    unsigned _shared_rcu = 0;
    unsigned _total_seqlock = 0;
    unsigned _shared_seqlock = 0;
    unsigned _total_nest_lock = 0;
    unsigned _shared_nest_lock = 0;
    unsigned _total_barrier = 0;
    unsigned _shared_barrier = 0;
    unsigned _total_bitfield = 0;
    unsigned _shared_bitfield = 0;
    unsigned _total_containerof = 0;
    unsigned _shared_containerof = 0;
    unsigned _total_ioremap = 0;
    unsigned _shared_ioremap = 0;
  };
}

#endif