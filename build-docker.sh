#!/bin/bash

# SoK Experiment Docker Build Script

set -e

echo "=== SoK Experiment Docker Build ==="

# Check if Docker is available
if ! command -v docker &> /dev/null; then
    echo "Error: Docker is not installed or not in PATH"
    exit 1
fi

# Check if user can run Docker
if ! docker info &> /dev/null; then
    echo "Error: Cannot connect to Docker daemon."
    echo "Please ensure:"
    echo "1. Docker daemon is running"
    echo "2. User is in docker group: sudo usermod -aG docker \$USER"
    echo "3. Log out and back in after adding to docker group"
    exit 1
fi

echo "Building SoK Analysis Framework Docker image..."

# Build the image
docker build -t sok-analysis:latest .

echo "Build completed successfully!"
echo ""
echo "To run the container:"
echo "  docker run -it --rm sok-analysis:latest"
echo ""
echo "To run specific analysis:"
echo "  docker run -it --rm sok-analysis:latest run-analysis coretemp risky-field"
echo ""
echo "To mount results directory:"
echo "  docker run -it --rm -v \$(pwd)/results:/workspace/results sok-analysis:latest"