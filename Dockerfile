# SoK Experiment - Driver Isolation Analysis Framework
# Based on KSplit static analysis for kernel driver security research

FROM ubuntu:20.04

# Prevent interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Install system dependencies
RUN apt-get update && apt-get install -y \
    # Build essentials
    build-essential \
    cmake \
    git \
    python3 \
    python3-pip \
    # LLVM 12 toolchain
    llvm-12 \
    llvm-12-dev \
    clang-12 \
    opt-12 \
    # Additional tools
    wget \
    curl \
    vim \
    htop \
    # JSON processing
    jq \
    # Clean up
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set LLVM 12 as default
RUN update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-12 100 \
    && update-alternatives --install /usr/bin/opt opt /usr/bin/opt-12 100 \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-12 100

# Install Python dependencies
RUN pip3 install \
    numpy \
    pandas \
    matplotlib \
    seaborn \
    jupyter \
    scipy

# Create working directory
WORKDIR /workspace

# Copy the entire SoK experiment
COPY . /workspace/

# Build SVF framework
RUN cd pdg/SVF && \
    chmod +x build.sh && \
    ./build.sh

# Build PDG analysis passes
RUN cd pdg && \
    mkdir -p build && \
    cd build && \
    cmake .. && \
    make -j$(nproc)

# Verify the build
RUN cd pdg && \
    ls -la build/libpdg.so && \
    echo "PDG library built successfully"

# Set up environment variables
ENV PATH="/usr/bin:${PATH}"
ENV LLVM_DIR="/usr/lib/llvm-12"
ENV PDG_HOME="/workspace/pdg"
ENV BC_FILES_DIR="/workspace/bc-files-12"

# Create convenience scripts
RUN echo '#!/bin/bash\n\
cd /workspace/pdg\n\
if [ $# -eq 0 ]; then\n\
    echo "Usage: run-analysis <driver_name> [analysis_type]"\n\
    echo "Available analysis types: risky-field, risky-boundary, shared-data, boundary-info"\n\
    echo "Example: run-analysis coretemp risky-field"\n\
    exit 1\n\
fi\n\
\n\
DRIVER=$1\n\
ANALYSIS_TYPE=${2:-risky-field}\n\
\n\
# Find the driver BC file\n\
BC_FILE=$(find /workspace/bc-files-12 -name "${DRIVER}.bc" | head -1)\n\
if [ -z "$BC_FILE" ]; then\n\
    echo "Error: Driver $DRIVER not found"\n\
    exit 1\n\
fi\n\
\n\
echo "Running $ANALYSIS_TYPE analysis on $DRIVER..."\n\
echo "BC file: $BC_FILE"\n\
\n\
opt-12 -load build/libpdg.so -${ANALYSIS_TYPE} < "$BC_FILE"\n\
' > /usr/local/bin/run-analysis && chmod +x /usr/local/bin/run-analysis

RUN echo '#!/bin/bash\n\
cd /workspace/pdg\n\
echo "=== SoK Experiment Analysis Framework ==="\n\
echo "PDG Home: $PDG_HOME"\n\
echo "BC Files: $BC_FILES_DIR"\n\
echo "LLVM Version: $(opt-12 --version | head -1)"\n\
echo ""\n\
echo "Available drivers:"\n\
find /workspace/bc-files-12 -name "*.bc" | wc -l | xargs echo "Total BC files:"\n\
echo ""\n\
echo "Usage:"\n\
echo "  run-analysis <driver_name> [analysis_type]  - Run analysis on specific driver"\n\
echo "  ls /workspace/bc-files-12/                   - Browse available drivers"\n\
echo "  cat /workspace/pdg/ANALYSIS_SUMMARY.md       - View analysis results summary"\n\
echo ""\n\
echo "Example: run-analysis coretemp risky-field"\n\
' > /usr/local/bin/sok-info && chmod +x /usr/local/bin/sok-info

# Create analysis runner for batch processing
RUN echo '#!/bin/bash\n\
cd /workspace/pdg\n\
\n\
SUBSYSTEM=${1:-hwmon}\n\
ANALYSIS_TYPE=${2:-risky-field}\n\
\n\
echo "Running batch analysis on $SUBSYSTEM subsystem with $ANALYSIS_TYPE analysis..."\n\
\n\
for bc_file in /workspace/bc-files-12/$SUBSYSTEM/*/*.bc; do\n\
    if [ -f "$bc_file" ]; then\n\
        driver_name=$(basename "$bc_file" .bc)\n\
        echo "Analyzing $driver_name..."\n\
        timeout 300 opt-12 -load build/libpdg.so -${ANALYSIS_TYPE} < "$bc_file" > /dev/null 2>&1\n\
        if [ $? -eq 0 ]; then\n\
            echo "  ✓ $driver_name completed"\n\
        else\n\
            echo "  ✗ $driver_name failed or timed out"\n\
        fi\n\
    fi\n\
done\n\
\n\
echo "Batch analysis completed."\n\
' > /usr/local/bin/run-batch-analysis && chmod +x /usr/local/bin/run-batch-analysis

# Set default command
CMD ["sok-info"]

# Expose any ports if needed (for Jupyter notebook, etc.)
EXPOSE 8888

# Add labels for documentation
LABEL maintainer="SoK Experiment Team"
LABEL description="Static analysis framework for kernel driver isolation security research"
LABEL version="1.0"
LABEL paper="SoK: Understanding the Attack Surface in Device Driver Isolation Frameworks"

# Health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
    CMD cd /workspace/pdg && ls build/libpdg.so > /dev/null 2>&1 || exit 1