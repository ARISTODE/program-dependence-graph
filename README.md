# PDG Document

## Introduction

This project is a key component of our PtrSplit and Program-mandering works. It aims at building a modular inter-procedural program dependence graph (PDG) for practical use. Our program dependence graph is field senstive, context-insensitive and flow-insensitive. For more details, welcome to read our CCS'17 paper about PtrSplit: \[[http://www.cse.psu.edu/~gxt29/papers/ptrsplit.pdf\]](http://www.cse.psu.edu/~gxt29/papers/ptrsplit.pdf%5D) If you find this tool useful, please cite the PtrSplit paper in your publication. Here's the bibtex entry:

@inproceedings{LiuTJ17Ptrsplit,

author = {Shen Liu and Gang Tan and Trent Jaeger},

title = {{PtrSplit}: Supporting General Pointers in Automatic Program Partitioning},

booktitle = {24th ACM Conference on Computer and Communications Security ({CCS})},

pages = {2359--2371},

year = {2017}

}

We have upgraded the implementation to LLVM 12.0.0. Currently, we only support building PDGs for C programs.

A PDG example looks like this (the blue part corresponds to the parameter tree):


## Getting Started
```
mkdir build
cd build
cmake ..
make
opt -load libpdg.so -dot-pdg < test.bc
```

### Available Passes

**\-pdg:** generate the program dependence graph (inter-procedural)

**\-cdg:** generate the control dependence graph (intra-procedural)

**\-ddg:** generate the data dependence graph (intra-procedural)

**\-dot-\*:** for visualization. (dot)

For those large software, generating a visualizable PDG is not easy. Graphviz often fails to generate the .dot file for a program with more than 1000 lines of C code. Fortunately, we rarely need such a large .dot file but only do kinds of analyses on the PDG, which is always in memory.
