# KSplit

## Introduction
This repository contains the key static analyses implementations for the KSplit project. KSplit is a driver isolation framework that helps developers to 
isolate driver with automatic supports. The main static analyses in KSplit are described below. Note that the analyses need to run aspect to the listed order.

1. Boundary analysis -> computes the boundary between kernel and the isolated driver using common driver-kernel communication idiom.
2. Shared fields analysis -> computes the shared struct fields that are accessed on both driver and kernel sides. This set of fields are used in later analyses to eliminate the private fields required synchronization and improve communication performance.
3. Field access analysis -> computes the struct fields that are accessed through references passed across islation boundary. 
4. Concurrency data synchronization analysis -> computes all the atomic regions, e.g, critical sections and atomic operations, and the shared data accessed in these regions. 
5. Nescheck analysis -> classify the pointers passed across isolation boundary into three categories: singleton, seq, wild. These classes are used in the IDL generation to correctly generate marshaling requirement for the pointers.
6. IDL generation -> takes information computed in steps 3, 4 and 5, and generate the final IDL that will be used to compile the communication code.

This picture below shows the overrall workflow:
- [  ] Add workflow diagram


## Getting Started
To replicate all KSplit experiments, please refer to our artifact page: https://github.com/mars-research/ksplit-artifacts

To experiment with the KSplit static analyses part, follow the instructions below.

Step 1: Build PDG
```bash
# build pdg
# Clone pdg repos
git clone https://github.com/ARISTODE/program-dependence-graph.git pdg --recursive --branch dev_ksplit
# build SVF, the key component of reasoning pointer alias in PDG
pushd ./pdg/SVF
mkdir -p build && cd build;
cmake .. && make -j $(nproc)
popd
# build PDG
mkdir -p build && cd build;
cmake .. && make -j $(nproc)
```

Step 2: 
Run different passes to obtain results from different stages. See [#available-passes] for more details.


### Available Passes

**\-pdg:** generate the program dependence graph (inter-procedural)

**\-output-boundary-info:** generate fields that desribe the isolation boundary

**\-shared-data:** compute shared struct fields

**\-daa:** comopute data accessed through references passed in cross-domain function calls

**\-atomic-region:** comopute atomic regions

**\-nescheck*:** run nescheck on pointers passed across isolation boundary

