# SoK Experiment Deployment Guide

This guide provides step-by-step instructions for deploying and using the SoK analysis framework.

## System Requirements

### Minimum Requirements
- **OS**: Linux (Ubuntu 18.04+, CentOS 7+, or similar)
- **RAM**: 8GB minimum, 16GB recommended
- **Storage**: 20GB free space
- **CPU**: 4 cores recommended for parallel analysis

### Software Dependencies
- Docker (version 20.10+)
- Git
- Bash shell

## Quick Deployment

### 1. Clone and Setup
```bash
# Clone the repository
git clone https://github.com/ARISTODE/program-dependence-graph.git
cd program-dependence-graph

# Or if you have the SoK_experiment directory already:
cd SoK_experiment
```

### 2. Build the Container
```bash
# Make scripts executable
chmod +x build-docker.sh run-sok-analysis.sh

# Build the Docker image (takes 10-15 minutes)
./build-docker.sh
```

### 3. Verify Installation
```bash
# Test the setup
./run-sok-analysis.sh info

# Run a quick analysis test
./run-sok-analysis.sh analyze dummy risky-field
```

## Analysis Workflows

### Single Driver Analysis
```bash
# Analyze specific drivers
./run-sok-analysis.sh analyze coretemp risky-field
./run-sok-analysis.sh analyze i7core_edac risky-boundary

# View results
docker run --rm -v $(pwd)/pdg/logs:/workspace/pdg/logs sok-analysis:latest \
  cat /workspace/pdg/logs/GeneralRiskyDataStat.json
```

### Batch Analysis by Subsystem
```bash
# Analyze entire subsystems
./run-sok-analysis.sh batch hwmon risky-field
./run-sok-analysis.sh batch edac risky-boundary
./run-sok-analysis.sh batch net_ethernet shared-data

# Monitor progress
docker logs -f <container_id>
```

### Full Dataset Analysis
```bash
# Create comprehensive analysis script
cat > run_full_analysis.sh << 'EOF'
#!/bin/bash
SUBSYSTEMS="hwmon edac net_ethernet usb block sound gpu arch_x86 md"
ANALYSES="risky-field risky-boundary"

for subsys in $SUBSYSTEMS; do
    for analysis in $ANALYSES; do
        echo "Running $analysis on $subsys..."
        ./run-sok-analysis.sh batch $subsys $analysis
        sleep 5
    done
done
EOF

chmod +x run_full_analysis.sh
./run_full_analysis.sh
```

## Results Analysis

### View Comprehensive Summary
```bash
# View analysis summary
./run-sok-analysis.sh shell
# Inside container:
cat /workspace/pdg/ANALYSIS_SUMMARY.md
cat /workspace/pdg/SOK_PAPER_TABLES.md
```

### Extract Specific Metrics
```bash
# Create results extraction script
cat > extract_results.sh << 'EOF'
#!/bin/bash
RESULTS_DIR="./results/extracted"
mkdir -p $RESULTS_DIR

# Extract key metrics from all driver logs
./run-sok-analysis.sh shell << 'DOCKER_EOF'
cd /workspace
python3 << 'PYTHON_EOF'
import json
import glob
import os

# Collect all GeneralRiskyDataStat.json files  
stats = []
for file in glob.glob('/workspace/bc-files-12/*/logs/GeneralRiskyDataStat.json'):
    try:
        with open(file, 'r') as f:
            data = json.load(f)
            driver = file.split('/')[-3]
            data['driver'] = driver
            stats.append(data)
    except:
        pass

# Save consolidated results
with open('/workspace/results/consolidated_stats.json', 'w') as f:
    json.dump(stats, f, indent=2)

print(f"Extracted stats from {len(stats)} drivers")
PYTHON_EOF
DOCKER_EOF
EOF

chmod +x extract_results.sh
./extract_results.sh
```

### Jupyter Analysis Environment
```bash
# Start Jupyter for interactive analysis
./run-sok-analysis.sh jupyter

# Access at http://localhost:8888
# Create notebooks in /workspace/notebooks/
```

## Advanced Usage

### Custom Analysis Pass
```bash
# Develop new analysis passes
./run-sok-analysis.sh shell

# Inside container:
cd /workspace/pdg/src
# Edit source files
# Rebuild:
cd /workspace/pdg/build && make -j$(nproc)
```

### Performance Optimization
```bash
# Run with more resources
docker run -it --rm \
  --cpus="8" \
  --memory="16g" \
  -v $(pwd)/results:/workspace/results \
  sok-analysis:latest \
  run-batch-analysis hwmon risky-field
```

### Parallel Processing
```bash
# Run multiple subsystems in parallel
cat > parallel_analysis.sh << 'EOF'
#!/bin/bash
SUBSYSTEMS=("hwmon" "edac" "net_ethernet" "usb")

for subsys in "${SUBSYSTEMS[@]}"; do
    (
        echo "Starting $subsys analysis..."
        ./run-sok-analysis.sh batch $subsys risky-field > logs_${subsys}.txt 2>&1
        echo "$subsys analysis completed"
    ) &
done

# Wait for all background jobs
wait
echo "All parallel analyses completed"
EOF

chmod +x parallel_analysis.sh
./parallel_analysis.sh
```

## Data Export and Publication

### Generate Paper Tables
```bash
# Extract paper-ready tables
./run-sok-analysis.sh shell << 'EOF'
cd /workspace/pdg
# Tables are already generated in:
cat SOK_PAPER_TABLES.md
cat COMPREHENSIVE_SOK_SUMMARY.md

# Export to results directory
cp *.md /workspace/results/
EOF
```

### Export Raw Data
```bash
# Create data export
mkdir -p ./results/paper_data
./run-sok-analysis.sh shell << 'EOF'
cd /workspace

# Create CSV exports for statistical analysis
python3 << 'PYTHON_EOF'
import json
import csv
import glob

# Export driver statistics
drivers_data = []
for file in glob.glob('/workspace/bc-files-12/*/logs/GeneralRiskyDataStat.json'):
    try:
        with open(file, 'r') as f:
            data = json.load(f)
            driver = file.split('/')[-3]
            subsystem = file.split('/')[-4]
            
            drivers_data.append({
                'driver': driver,
                'subsystem': subsystem,
                'boundary_funcs': data.get('Num kernel boundary func', 0),
                'shared_fields': data.get('Shared fields', 0),
                'krdu_fields': data.get('KRDU fields', 0),
                'ptr_fields': data.get('ptr fields', 0),
                'func_ptr_fields': data.get('func ptr fields', 0)
            })
    except:
        pass

# Save as CSV
with open('/workspace/results/drivers_statistics.csv', 'w', newline='') as f:
    if drivers_data:
        writer = csv.DictWriter(f, fieldnames=drivers_data[0].keys())
        writer.writeheader()
        writer.writerows(drivers_data)

print(f"Exported {len(drivers_data)} driver records to CSV")
PYTHON_EOF
EOF
```

## Troubleshooting

### Common Issues

1. **Docker permission denied**
   ```bash
   # Add user to docker group
   sudo usermod -aG docker $USER
   # Log out and back in
   ```

2. **Container out of memory**
   ```bash
   # Increase Docker memory limit
   docker run --memory="8g" ...
   ```

3. **Analysis fails on specific driver**
   ```bash
   # Check driver BC file exists
   ./run-sok-analysis.sh shell
   find /workspace/bc-files-12 -name "driver_name.bc"
   
   # Check for corrupted files
   opt-12 -verify < /workspace/bc-files-12/path/to/driver.bc
   ```

4. **Missing analysis results**
   ```bash
   # Verify analysis completed successfully
   ./run-sok-analysis.sh shell
   ls -la /workspace/pdg/logs/
   
   # Check for analysis errors
   cat /workspace/pdg/logs/*.log
   ```

### Performance Tuning

```bash
# Monitor resource usage
docker stats

# Use faster storage for containers
docker run --tmpfs /tmp ...

# Enable BuildKit for faster builds
export DOCKER_BUILDKIT=1
./build-docker.sh
```

## Integration with CI/CD

### GitHub Actions Example
```yaml
name: SoK Analysis
on: [push, pull_request]

jobs:
  analysis:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v2
    - name: Build and test
      run: |
        ./build-docker.sh
        ./run-sok-analysis.sh analyze dummy risky-field
    - name: Upload results
      uses: actions/upload-artifact@v2
      with:
        name: analysis-results
        path: results/
```

## Security Considerations

- Container runs as root by default - consider using user namespaces for production
- Results directory is mounted with full access
- No network restrictions applied by default
- Sensitive driver code is accessible within container

## Support and Maintenance

For issues or questions:
1. Check the troubleshooting section above
2. Review container logs: `docker logs <container_id>`
3. Create an issue in the repository
4. Refer to the original research paper for methodology questions

## Updating the Framework

```bash
# Pull latest changes
git pull origin main

# Rebuild container with updates
docker rmi sok-analysis:latest
./build-docker.sh

# Verify updates
./run-sok-analysis.sh info
```