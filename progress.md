# LLVM 19 Migration Progress

## Date: 2025-05-28

### Overview
Successfully migrated the Program Dependence Graph (PDG) codebase from legacy LLVM pass infrastructure to LLVM 19 with the new pass manager.

### Major Changes Implemented

#### 1. Build System Updates
- **CMakeLists.txt**:
  - Updated C++ standard from C++14 to C++17
  - Configured to use LLVM 19 from `/opt/homebrew/opt/llvm@19`
  - Updated minimum CMake version to 3.13.4

#### 2. New Pass Manager Migration
- **Converted Legacy Passes**:
  - `ProgramDependencyGraph`: `ModulePass` → New analysis pass with proper `Result` struct
  - `DataDependencyGraph`: `ModulePass` → New analysis pass
  - `ControlDependencyGraph`: `FunctionPass` → New function analysis pass
  
- **Pass Registration**:
  - Created `PDGPlugin.cpp` for new pass manager plugin infrastructure
  - Removed legacy `RegisterPass<>` declarations
  - Added proper analysis registration callbacks

#### 3. LLVM API Updates
- **Debug Intrinsics**:
  - `DbgDeclareInst` → `DbgVariableIntrinsic`
  - `getVariableLocation()` → `getVariableLocationOp(0)`
  
- **Module APIs**:
  - `Module::getGlobalList()` → `Module::globals()`
  
- **CallInst APIs**:
  - `CallInst::getNumArgOperands()` → `CallInst::arg_size()`
  
- **Opaque Pointer Updates**:
  - Removed `Type::getPointerElementType()` usage
  - Updated `GetElementPtrInst` to use `getSourceElementType()`
  - Simplified type comparisons for pointer types
  
- **Alias Analysis**:
  - Updated to scoped enums: `NoAlias` → `AliasResult::NoAlias`
  - Same for `MustAlias` → `AliasResult::MustAlias`

#### 4. Include Updates
- Added missing standard library includes:
  - `<map>`, `<vector>`, `<stack>`, `<queue>`
- Added LLVM-specific includes:
  - `llvm/BinaryFormat/Dwarf.h` for dwarf namespace
  - `llvm/IR/DebugProgramInstruction.h` for debug intrinsics
  - `llvm/Analysis/MemoryDependenceAnalysis.h`
  - `llvm/Analysis/PostDominators.h`

#### 5. Analysis Result Structures
- Added proper `Result` structs with `invalidate` methods for:
  - `ProgramDependencyGraph::Result`
  - `DataDependencyGraph::Result`
  - `ControlDependencyGraph::Result`

### Files Modified
1. **CMakeLists.txt**
2. **include/**:
   - `LLVMEssentials.hh`
   - `ProgramDependencyGraph.hh`
   - `DataDependencyGraph.hh`
   - `ControlDependencyGraph.hh`
   - `FunctionWrapper.hh`
   - `CallWrapper.hh`
   - `PDGNode.hh`
   - `GraphWriter.hh`
3. **src/**:
   - `ProgramDependencyGraph.cpp`
   - `DataDependencyGraph.cpp`
   - `ControlDependencyGraph.cpp`
   - `FunctionWrapper.cpp`
   - `Graph.cpp`
   - `GraphWriter.cpp`
   - `PDGCallGraph.cpp`
   - `PDGUtils.cpp`
   - `DebugInfoUtils.cpp`
   - `PDGPlugin.cpp` (new file)

### Build Status
✅ **BUILD SUCCESSFUL** - The project now builds cleanly with LLVM 19.

### Next Steps
- Test the PDG functionality with sample LLVM IR files
- Update any command-line tools to use the new pass manager (`opt -passes=...`)
- Consider adding more comprehensive error handling for the new APIs
- Update documentation to reflect the new pass manager usage

### Usage with New Pass Manager
To use the PDG passes with opt:
```bash
opt -load-pass-plugin=./libpdg.so -passes="pdg" input.ll -o output.ll
```

For dot graph generation:
```bash
opt -load-pass-plugin=./libpdg.so -passes="dot-pdg" input.ll
```