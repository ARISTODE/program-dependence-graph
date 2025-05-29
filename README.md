# Program Dependence Graph (PDG)

## Introduction
This project builds a modular inter-procedural program dependence graph (PDG) for practical use. Our program dependence graph is field sensitive, context-insensitive and flow-insensitive. This is a key component of our PtrSplit and Program-mandering works.

For more details, welcome to read our CCS'17 paper about PtrSplit: [http://www.cse.psu.edu/~gxt29/papers/ptrsplit.pdf](http://www.cse.psu.edu/~gxt29/papers/ptrsplit.pdf) If you find this tool useful, please cite the PtrSplit and Program Mandering papers in your publication. Here's the bibtex entries:

@inproceedings{LiuTJ17Ptrsplit,
  author = {Shen Liu and Gang Tan and Trent Jaeger},
  title = {{PtrSplit}: Supporting General Pointers in Automatic Program Partitioning},
  booktitle = {24th ACM Conference on Computer and Communications Security ({CCS})},
  pages = {2359--2371},
  year = {2017}
}

@inproceedings{liu2019program,
  title={Program-mandering: Quantitative privilege separation},
  author={Liu, Shen and Zeng, Dongrui and Huang, Yongzhe and Capobianco, Frank and McCamant, Stephen and Jaeger, Trent and Tan, Gang},
  booktitle={Proceedings of the 2019 ACM SIGSAC Conference on Computer and Communications Security},
  pages={1023--1040},
  year={2019}
}

We have upgraded the implementation to LLVM 19. Currently, we support building PDGs for C programs.


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

## LLVM IR compilation
For simple C programs(e.g., test.c), do

> clang -emit-llvm -S -g test.c -o test.bc

Now you have a binary format LLVM bitcode file which can be directly used as the input for PDG generation.

For those large C software (e.g., wget), you can refer to this great article for help:

[Compiling Autotooled projects to LLVM Bitcode](http://gbalats.github.io/2015/12/10/compiling-autotooled-projects-to-LLVM-bitcode.html)

(We successfully compiled SPECCPU 2006 INT/thttpd/wget/telnet/openssh/curl/nginx/sqlite, thanks to the author!)

## User Guide

We can use the current PDG as a required pass through following steps:

### Compile PDG

1. download PDG repo: git clone https://github.com/ARISTODE/program-dependence-graph.git
2. cd program-dependence-graph  
3. mkdir build && cd build
4. cmake .. && make -j8

### Use PDG with New Pass Manager
```bash
opt -load-pass-plugin=./libpdg.so -passes="pdg" input.ll -o output.ll
```

### Useful APIs

**Query the reachability of two nodes:**

```cpp
ProgramGraph *g = getAnalysis<ProgramDependencyGraph>()->getPDG();

Value* src;
Value* dst;

pdg::Node* src_node = g->getNode(*src);
pdg::Node* dst_node = g->getNode(*dst);

if (g->canReach(src_node, dst_node)) 
{
  // do something...
}
```

**Traverse the PDG with path constrains**
This method is useful to traverse the graph through certain edge types. In the example, we put the edge types we want to exclude in the set **exclude_edges**. Then, pass that as an argument to the **canReach** function.

```cpp
ProgramGraph *g = getAnalysis<ProgramDependencyGraph>()->getPDG();

Value* src;
Value* dst;

pdg::Node* src_node = g->getNode(*src);
pdg::Node* dst_node = g->getNode(*dst);

std::set<pdg::EdgeType> exclude_edges;

if (g->canReach(src_node, dst_node, exclude_edges)) 
{
  // do something...
}
```
