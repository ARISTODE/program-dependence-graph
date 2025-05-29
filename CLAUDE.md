# Program Dependence Graph (PDG) Project Structure

## Overview
This is a Program Dependence Graph implementation for LLVM 19 that constructs both data and control dependency graphs for LLVM IR programs.

## Directory Structure
```
program-dependence-graph/
├── CMakeLists.txt          # Build configuration for LLVM 19
├── include/                # Header files
│   ├── CallWrapper.hh      # Wrapper for call instructions
│   ├── ControlDependencyGraph.hh  # Control dependency analysis
│   ├── DataDependencyGraph.hh     # Data dependency analysis
│   ├── DebugInfoUtils.hh   # Debug info utilities
│   ├── FunctionWrapper.hh  # Function analysis wrapper
│   ├── Graph.hh           # Generic graph implementation
│   ├── GraphTraits.hh     # Graph traits for LLVM
│   ├── GraphWriter.hh     # DOT graph output
│   ├── LLVMEssentials.hh  # Common LLVM includes
│   ├── PDGCallGraph.hh    # Call graph construction
│   ├── PDGCommandLineOptions.hh
│   ├── PDGEdge.hh         # Edge representation
│   ├── PDGEnums.hh        # Enumerations for node/edge types
│   ├── PDGNode.hh         # Node representation
│   ├── PDGUtils.hh        # Utility functions
│   ├── ProgramDependencyGraph.hh  # Main PDG class
│   └── Tree.hh            # Tree data structure
├── src/                   # Implementation files
│   ├── CallWrapper.cpp
│   ├── ControlDependencyGraph.cpp
│   ├── DataDependencyGraph.cpp
│   ├── DebugInfoUtils.cpp
│   ├── FunctionWrapper.cpp
│   ├── Graph.cpp
│   ├── GraphWriter.cpp
│   ├── PDGCallGraph.cpp
│   ├── PDGNode.cpp
│   ├── PDGPlugin.cpp      # New pass manager plugin
│   ├── PDGUtils.cpp
│   ├── ProgramDependencyGraph.cpp
│   └── Tree.cpp
├── example/               # Example code and outputs
├── Edge_Specification/    # PDG edge classification docs
├── SVF/                   # SVF framework integration
├── build/                 # Build directory
└── progress.md           # Migration progress tracking
```

## Key Components

### Analysis Passes (New Pass Manager)
1. **ProgramDependencyGraph**: Main module analysis that orchestrates PDG construction
2. **DataDependencyGraph**: Constructs data dependencies (def-use, RAW, alias)
3. **ControlDependencyGraph**: Constructs control dependencies using post-dominator analysis

### Core Classes
- **Node/Edge**: Graph representation with typed nodes and edges
- **FunctionWrapper**: Manages function-level analysis data
- **CallWrapper**: Handles interprocedural analysis at call sites
- **Tree**: Represents formal/actual parameter trees for interprocedural analysis

### Edge Types
- Control dependencies: CONTROLDEP_ENTRY, CONTROLDEP_BR, CONTROLDEP_CALLINV, CONTROLDEP_CALLRET
- Data dependencies: DATA_DEF_USE, DATA_RAW, DATA_ALIAS, DATA_RET
- Parameter dependencies: PARAMETER_IN, PARAMETER_OUT, PARAMETER_FIELD

## Build Commands
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j8
```

## Usage
```bash
# Load PDG analysis
opt -load-pass-plugin=./libpdg.so -passes="pdg" input.ll -o output.ll

# Generate DOT graph
opt -load-pass-plugin=./libpdg.so -passes="dot-pdg" input.ll
```

## LLVM 19 Compatibility
- Uses new pass manager infrastructure
- C++17 standard
- Opaque pointer support
- Updated debug intrinsics API
- Scoped AliasResult enums