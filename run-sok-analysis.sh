#!/bin/bash

# SoK Experiment Analysis Runner Script

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RESULTS_DIR="$SCRIPT_DIR/results"
DOCKER_IMAGE="sok-analysis:latest"

# Create results directory if it doesn't exist
mkdir -p "$RESULTS_DIR"

# Function to show usage
show_usage() {
    echo "Usage: $0 [OPTIONS] [COMMAND]"
    echo ""
    echo "Commands:"
    echo "  build                           Build the Docker image"
    echo "  shell                          Start interactive shell"
    echo "  info                           Show system information"
    echo "  analyze <driver> [analysis]    Run analysis on specific driver"
    echo "  batch <subsystem> [analysis]   Run batch analysis on subsystem"
    echo "  jupyter                        Start Jupyter notebook server"
    echo ""
    echo "Options:"
    echo "  -h, --help                     Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 build                       # Build the Docker image"
    echo "  $0 shell                       # Interactive analysis session"
    echo "  $0 analyze coretemp risky-field"
    echo "  $0 batch hwmon risky-boundary"
    echo "  $0 jupyter                     # Start notebook at http://localhost:8888"
}

# Function to check if Docker image exists
check_image() {
    if ! docker image inspect "$DOCKER_IMAGE" &> /dev/null; then
        echo "Docker image '$DOCKER_IMAGE' not found."
        echo "Building image now..."
        build_image
    fi
}

# Function to build Docker image
build_image() {
    echo "Building SoK Analysis Docker image..."
    cd "$SCRIPT_DIR"
    docker build -t "$DOCKER_IMAGE" .
    echo "Build completed successfully!"
}

# Function to run Docker container
run_container() {
    local cmd="$1"
    shift
    
    check_image
    
    docker run -it --rm \
        -v "$RESULTS_DIR:/workspace/results" \
        -v "$SCRIPT_DIR/pdg/logs:/workspace/pdg/logs" \
        "$DOCKER_IMAGE" \
        $cmd "$@"
}

# Function to run Jupyter
run_jupyter() {
    check_image
    
    echo "Starting Jupyter notebook server..."
    echo "Access at: http://localhost:8888"
    echo "Press Ctrl+C to stop"
    
    docker run -it --rm \
        -p 8888:8888 \
        -v "$RESULTS_DIR:/workspace/results" \
        -v "$SCRIPT_DIR/pdg/logs:/workspace/pdg/logs" \
        "$DOCKER_IMAGE" \
        jupyter lab --ip=0.0.0.0 --port=8888 --no-browser --allow-root --NotebookApp.token=''
}

# Parse command line arguments
case "${1:-shell}" in
    "build")
        build_image
        ;;
    "shell")
        run_container bash
        ;;
    "info")
        run_container sok-info
        ;;
    "analyze")
        if [ $# -lt 2 ]; then
            echo "Error: Driver name required"
            echo "Usage: $0 analyze <driver> [analysis_type]"
            exit 1
        fi
        run_container run-analysis "${@:2}"
        ;;
    "batch")
        if [ $# -lt 2 ]; then
            echo "Error: Subsystem name required"
            echo "Usage: $0 batch <subsystem> [analysis_type]"
            exit 1
        fi
        run_container run-batch-analysis "${@:2}"
        ;;
    "jupyter")
        run_jupyter
        ;;
    "-h"|"--help"|"help")
        show_usage
        ;;
    *)
        echo "Unknown command: $1"
        show_usage
        exit 1
        ;;
esac