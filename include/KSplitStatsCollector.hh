#ifndef KSPLIT_STATS_COLLECTOR_H_
#define KSPLIT_STATS_COLLECTOR_H_
#include "LLVMEssentials.hh"
#include "DebugInfoUtils.hh"
#include "Tree.hh"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <tuple>
#include <iomanip>

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
    void collectTotalPointerStats(llvm::DIType &dt);
    // void collectSharedPointerStats(llvm::DIType &dt, std::string var_name, std::string funcName);
    void collectDataStats(TreeNode &treeNode, std::string nescheck_ptr_type, llvm::Function &func, int paramIdx = -1, bool is_driver_func = false);
    void collectSharedPointerStats(TreeNode &treeNode, std::string nescheck_ptr_type);
    void collectInferredStringStats(std::set<std::string> &annotations);
    void printStats();
    void printDataStats();
    void printTable1Raw();
    void printTable2Raw();
    void printDrvAPIStats();
    void printRiskyPatterns();
    void printSoKClassifiedFields();

  public:
    std::ofstream _stats_file;
    std::unordered_map<llvm::Function*, std::tuple<unsigned, unsigned, unsigned>> _drv_api_acc_map;
    // record function ptr (read, write, read/write)
    std::unordered_map<llvm::Function*, std::tuple<unsigned, unsigned, unsigned>> _drv_api_ptr_acc_map;
    // 1.a complexity
    unsigned _driver_to_kernel_func_call = 0;
    unsigned _kernel_to_driver_func_call = 0;
    unsigned _total_func_size = 0;
    // 1.b fields analysis stats
    int _fieldsDeepCopyNum = 0;
    int _fields_field_analysis = 0;
    int _fields_shared_analysis = 0;
    int _fields_removed_boundary_opt = 0;
    // 1.c data classification
    // primitive types
    unsigned _primitive_fields = 0;
    // unsigned _total_bitfield = 0;
    unsigned _shared_bitfield = 0;
    // pointers
    unsigned _totalPtrNum = 0;
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

    // allocator stats
    unsigned _driverSharedAllocators = 0;
    unsigned _kernelSharedAllocators = 0;

    // kernel driver specific access data
    // per instance
    unsigned accessedSharedFields = 0;
    unsigned _driver_read_fields = 0;
    unsigned _driver_write_fields = 0;
    unsigned _driver_access_fields = 0;
    unsigned _driver_read_ptr_fields = 0;
    unsigned _driver_write_ptr_fields = 0;
    unsigned _driver_write_func_ptr_fields = 0;
    unsigned _driver_access_ptr_fields = 0;
    unsigned _driver_write_through_ptr_fields = 0;
    unsigned kernelReadableFields = 0;
    unsigned kernelReadablePtrFields = 0;
    unsigned kernelRAWDriverSharedFields = 0;
    unsigned kernelRAWDriverSharedPtrFields = 0;
    unsigned kernelReadDriverUpdateSharedFields = 0;
    unsigned kernelReadDriverUpdateSharedPtrFields = 0;
    // per shared struct type 
    unsigned numSharedStructType = 0;
    unsigned kernelReadableFieldsPerTy = 0;
    unsigned kernelReadablePtrFieldsPerTy = 0;
    unsigned driverWritableFieldsPerTy = 0;
    unsigned driverWritablePtrFieldsPerTy = 0;
    unsigned kernelReadDriverUpdateSharedFieldsPerTy = 0;
    unsigned kernelReadDriverUpdateSharedPtrFieldsPerTy = 0;
    unsigned kernelReadDriverUpdateSharedFuncPtrFieldsPerTy = 0;
    unsigned numRWPtr = 0;
    unsigned numRWFuncPtr = 0;
    unsigned numRWNonPtr = 0;
    unsigned numRWPtrCondVar = 0;
    unsigned numRWNonPtrCondVar = 0;
    unsigned numRWPtrInPtrArith = 0;
    unsigned numRWNonPtrInPtrArith = 0;
    unsigned riskyFieldUsedInSensitiveAPI = 0;
    unsigned riskyFieldUsedInSensitiveAPITaint = 0;
    unsigned riskyPtrArithField = 0;
    unsigned riskyPtrArithFieldTaint = 0;
    unsigned riskyIndexField = 0;
    unsigned riskyIndexFieldTaint = 0;
    unsigned riskyBoundRAWField = 0;
    unsigned riskyCondField = 0;
    unsigned riskyCondFieldTaint = 0;
    unsigned riskyCondRAWField = 0;
    unsigned riskyCondFuncField = 0;
    unsigned riskyLockField = 0;


    unsigned kernelAllocAPI = 0;
    unsigned kernelRAWAllocAPI = 0;
    unsigned kernelDeallocAPI = 0;
    unsigned kernelRAWDeallocAPI = 0;

    // classify shared fields
    unsigned funcPtrNum = 0;
    unsigned DCFuncPtrNum = 0;
    unsigned DLFuncPtrNum = 0;
    unsigned dataPtrNum = 0;
    unsigned DCDataPtrNum = 0;
    unsigned DLDataPtrNum = 0;

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