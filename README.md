# SoK Experiment: Driver Isolation Analysis Framework

This repository contains the static analysis framework for the research paper "SoK: Understanding the Attack Surface in Device Driver Isolation Frameworks". The framework analyzes Linux kernel drivers to identify security vulnerabilities in driver isolation systems.

## Overview

The analysis framework consists of:
- **PDG (Program Dependence Graph)** analysis passes built on LLVM 12.0.1
- **SVF (Static Value-Flow)** framework for pointer analysis
- **474 kernel driver bitcode files** from various subsystems
- **Comprehensive analysis results** and paper table generation

## Quick Start with Docker

### Prerequisites
- Docker and Docker Compose installed
- At least 8GB RAM and 20GB disk space

### Build and Run

1. **Build the container:**
   ```bash
   docker-compose build sok-analysis
   ```

2. **Run interactive analysis:**
   ```bash
   docker-compose run --rm sok-analysis
   ```

3. **Start Jupyter notebook (optional):**
   ```bash
   docker-compose up sok-jupyter
   # Access at http://localhost:8888
   ```

## Analysis Commands

Once inside the container, you can use these commands:

### Basic Analysis
```bash
# Get system information
sok-info

# Run analysis on a specific driver
run-analysis coretemp risky-field
run-analysis i7core_edac risky-boundary

# Available analysis types:
# - risky-field: Analyze security-sensitive struct fields
# - risky-boundary: Analyze risky kernel API usage
# - shared-data: Identify shared data structures
# - boundary-info: Compute isolation boundaries
```

### Batch Analysis
```bash
# Run batch analysis on a subsystem
run-batch-analysis hwmon risky-field
run-batch-analysis edac risky-boundary

# Available subsystems:
# hwmon, edac, net_ethernet, usb, block, sound, gpu, arch_x86, md
```

### Results Analysis
```bash
# View comprehensive analysis summary
cat /workspace/pdg/ANALYSIS_SUMMARY.md

# View paper tables
cat /workspace/pdg/SOK_PAPER_TABLES.md

# Check analysis logs
ls /workspace/pdg/logs/
```

## Project Structure

```
/workspace/
├── pdg/                      # PDG analysis framework
│   ├── src/                  # Source code for analysis passes
│   ├── include/              # Header files
│   ├── build/                # Compiled binaries
│   ├── SVF/                  # SVF framework
│   └── logs/                 # Analysis output
├── bc-files-12/              # Driver bitcode files
│   ├── hwmon/                # Hardware monitoring drivers
│   ├── edac/                 # Error detection drivers
│   ├── net_ethernet/         # Network drivers
│   └── ...                   # Other subsystems
├── llvm-12-reference/        # LLVM 12 reference code
└── results/                  # Persistent analysis results
```

## Key Analysis Passes

### RiskyFieldAnalysis (`-risky-field`)
Identifies security-sensitive struct fields that could be exploited:
- Pointer fields (function pointers, data pointers)
- Control variables
- Memory management fields
- Reference counting fields

### RiskyBoundaryAPIAnalysis (`-risky-boundary`)
Analyzes risky kernel API usage across driver-kernel boundaries:
- Memory management APIs (kfree, kmalloc)
- Concurrency APIs (mutex_lock, spinlock)
- Bus operations (PCI, USB)
- Reference counting (kobject_get/put)

## Analysis Results

The framework generates JSON output files:
- `GeneralRiskyDataStat.json`: Overall statistics
- `RiskyBoundaryAPI.json`: Detailed risky API analysis
- `BoundaryStructFieldsStats.json`: Field classification
- `BoundaryParamTaint.json`: Parameter taint analysis

## Development

### Building Manually
```bash
# Build SVF framework
cd pdg/SVF
./build.sh

# Build PDG passes
cd ../build
cmake ..
make -j$(nproc)
```

### Running Tests
```bash
# Test on simple drivers
opt-12 -load build/libpdg.so -risky-field < ../bc-files-12/net_ethernet/dummy/dummy.bc

# Verify output
ls logs/
```

## Research Paper Integration

This framework generates data for the following paper tables:
- **Table 1**: Driver vulnerability statistics by subsystem
- **Table 2**: Risky field classification results  
- **Table 3**: Boundary API vulnerability analysis
- **Table 4**: Overall security metrics across drivers

View the complete analysis summary:
```bash
cat /workspace/pdg/ANALYSIS_SUMMARY.md
```

## Troubleshooting

### Common Issues

1. **LLVM version mismatch**: Ensure LLVM 12.0.1 is used
2. **SVF build fails**: Check C++14 compiler compatibility
3. **Analysis crashes**: Increase container memory limits
4. **Missing drivers**: Verify BC file paths in bc-files-12/

### Debug Commands
```bash
# Check LLVM version
opt-12 --version

# Verify PDG library
ls -la /workspace/pdg/build/libpdg.so

# Test simple analysis
echo | opt-12 -load /workspace/pdg/build/libpdg.so -help | grep risky
```

## Citation

If you use this framework in your research, please cite:

```bibtex
@article{huang2024sok,
  title={SoK: Understanding the Attack Surface in Device Driver Isolation Frameworks},
  author={Huang, Yongzhe and Huang, Kaiming and Ennis, Matthew and Narayanan, Vikram and Burtsev, Anton and Jaeger, Trent and Tan, Gang},
  journal={arXiv preprint arXiv:2412.16754},
  year={2024}
}
```

## License

This project is released under the terms specified in the original research.

## Contact

For questions about the analysis framework or research methodology, please refer to the paper or create an issue in this repository.