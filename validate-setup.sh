#!/bin/bash

# SoK Experiment Setup Validation Script

set -e

echo "=== SoK Experiment Setup Validation ==="
echo ""

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Function to print status
print_status() {
    local status=$1
    local message=$2
    if [ "$status" = "PASS" ]; then
        echo -e "${GREEN}✓ PASS${NC}: $message"
    elif [ "$status" = "FAIL" ]; then
        echo -e "${RED}✗ FAIL${NC}: $message"
    elif [ "$status" = "WARN" ]; then
        echo -e "${YELLOW}⚠ WARN${NC}: $message"
    else
        echo -e "ℹ INFO: $message"
    fi
}

# Track validation results
PASS_COUNT=0
FAIL_COUNT=0
WARN_COUNT=0

# Function to validate step
validate_step() {
    local test_name=$1
    local command="$2"
    local expected_result="$3"
    
    echo ""
    echo "Testing: $test_name"
    echo "Command: $command"
    
    if eval "$command" >/dev/null 2>&1; then
        print_status "PASS" "$test_name"
        ((PASS_COUNT++))
        return 0
    else
        print_status "FAIL" "$test_name"
        ((FAIL_COUNT++))
        return 1
    fi
}

# Function to validate file exists
validate_file() {
    local file_path=$1
    local description=$2
    
    if [ -f "$file_path" ]; then
        print_status "PASS" "$description exists: $file_path"
        ((PASS_COUNT++))
    else
        print_status "FAIL" "$description missing: $file_path"
        ((FAIL_COUNT++))
    fi
}

# Function to validate directory exists
validate_directory() {
    local dir_path=$1
    local description=$2
    
    if [ -d "$dir_path" ]; then
        print_status "PASS" "$description exists: $dir_path"
        ((PASS_COUNT++))
    else
        print_status "FAIL" "$description missing: $dir_path"
        ((FAIL_COUNT++))
    fi
}

echo "Starting validation of SoK experiment setup..."
echo ""

# 1. Validate file structure
echo "=== File Structure Validation ==="
validate_file "Dockerfile" "Docker configuration"
validate_file "docker-compose.yml" "Docker Compose configuration"
validate_file "README.md" "Project README"
validate_file "DEPLOYMENT_GUIDE.md" "Deployment guide"
validate_file "build-docker.sh" "Docker build script"
validate_file "run-sok-analysis.sh" "Analysis runner script"
validate_file ".dockerignore" "Docker ignore file"

# 2. Validate project directories
echo ""
echo "=== Directory Structure Validation ==="
validate_directory "pdg" "PDG analysis framework"
validate_directory "bc-files-12" "Driver bitcode files"
validate_directory "llvm-12-reference" "LLVM reference code"
validate_directory "pdg/src" "PDG source code"
validate_directory "pdg/include" "PDG headers"
validate_directory "pdg/SVF" "SVF framework"

# 3. Validate key source files
echo ""
echo "=== Source Code Validation ==="
validate_file "pdg/src/RiskyFieldAnalysis.cpp" "Risky field analysis implementation"
validate_file "pdg/src/RiskyBoundaryAPIAnalysis.cpp" "Risky boundary API analysis implementation"
validate_file "pdg/include/RiskyFieldAnalysis.hh" "Risky field analysis header"
validate_file "pdg/include/RiskyBoundaryAPIAnalysis.hh" "Risky boundary API analysis header"
validate_file "pdg/CMakeLists.txt" "PDG build configuration"

# 4. Validate build artifacts
echo ""
echo "=== Build Artifacts Validation ==="
if [ -d "pdg/build" ]; then
    validate_file "pdg/build/libpdg.so" "PDG shared library"
    if [ -f "pdg/build/libpdg.so" ]; then
        # Check if library is valid
        if file pdg/build/libpdg.so | grep -q "shared object"; then
            print_status "PASS" "PDG library is valid shared object"
            ((PASS_COUNT++))
        else
            print_status "FAIL" "PDG library is not a valid shared object"
            ((FAIL_COUNT++))
        fi
    fi
else
    print_status "WARN" "PDG not built yet - run build first"
    ((WARN_COUNT++))
fi

# 5. Validate SVF build
echo ""
echo "=== SVF Framework Validation ==="
if [ -d "pdg/SVF/build" ] || [ -d "pdg/SVF/Release-build" ]; then
    print_status "PASS" "SVF framework appears to be built"
    ((PASS_COUNT++))
else
    print_status "WARN" "SVF framework not built yet"
    ((WARN_COUNT++))
fi

# 6. Validate Docker environment
echo ""
echo "=== Docker Environment Validation ==="
validate_step "Docker command available" "command -v docker" ""

if command -v docker >/dev/null 2>&1; then
    validate_step "Docker daemon accessible" "docker info" ""
    
    # Check if image exists
    if docker image inspect sok-analysis:latest >/dev/null 2>&1; then
        print_status "PASS" "SoK analysis Docker image exists"
        ((PASS_COUNT++))
    else
        print_status "WARN" "SoK analysis Docker image not built yet"
        ((WARN_COUNT++))
    fi
else
    print_status "FAIL" "Docker not available or not accessible"
    ((FAIL_COUNT++))
fi

# 7. Validate analysis results
echo ""
echo "=== Analysis Results Validation ==="
validate_file "pdg/ANALYSIS_SUMMARY.md" "Comprehensive analysis summary"
validate_file "pdg/SOK_PAPER_TABLES.md" "Paper tables summary"
validate_file "pdg/COMPREHENSIVE_SOK_SUMMARY.md" "Executive summary"

# 8. Validate sample BC files
echo ""
echo "=== Sample Driver Validation ==="
SAMPLE_DRIVERS=("dummy" "coretemp" "i7core_edac")
for driver in "${SAMPLE_DRIVERS[@]}"; do
    BC_FILE=$(find bc-files-12 -name "${driver}.bc" 2>/dev/null | head -1)
    if [ -n "$BC_FILE" ]; then
        print_status "PASS" "Sample driver $driver found: $BC_FILE"
        ((PASS_COUNT++))
    else
        print_status "WARN" "Sample driver $driver not found"
        ((WARN_COUNT++))
    fi
done

# 9. Validate scripts are executable
echo ""
echo "=== Script Permissions Validation ==="
for script in "build-docker.sh" "run-sok-analysis.sh" "validate-setup.sh"; do
    if [ -x "$script" ]; then
        print_status "PASS" "$script is executable"
        ((PASS_COUNT++))
    else
        print_status "FAIL" "$script is not executable"
        ((FAIL_COUNT++))
    fi
done

# 10. Validate Git repository
echo ""
echo "=== Git Repository Validation ==="
if [ -d ".git" ]; then
    print_status "PASS" "Git repository initialized"
    ((PASS_COUNT++))
    
    if git remote -v | grep -q "origin"; then
        print_status "PASS" "Git remote origin configured"
        ((PASS_COUNT++))
    else
        print_status "WARN" "Git remote origin not configured"
        ((WARN_COUNT++))
    fi
else
    print_status "WARN" "Not a Git repository"
    ((WARN_COUNT++))
fi

# Final summary
echo ""
echo "=== Validation Summary ==="
echo "Total tests: $((PASS_COUNT + FAIL_COUNT + WARN_COUNT))"
echo -e "${GREEN}Passed: $PASS_COUNT${NC}"
echo -e "${YELLOW}Warnings: $WARN_COUNT${NC}"
echo -e "${RED}Failed: $FAIL_COUNT${NC}"
echo ""

# Provide recommendations
if [ $FAIL_COUNT -eq 0 ] && [ $WARN_COUNT -eq 0 ]; then
    echo -e "${GREEN}🎉 All validations passed! Setup is complete and ready to use.${NC}"
    echo ""
    echo "Next steps:"
    echo "1. ./build-docker.sh                    # Build Docker image"
    echo "2. ./run-sok-analysis.sh info           # Test the setup"
    echo "3. ./run-sok-analysis.sh analyze dummy risky-field  # Run sample analysis"
elif [ $FAIL_COUNT -eq 0 ]; then
    echo -e "${YELLOW}⚠ Setup is mostly complete with some warnings.${NC}"
    echo "You can proceed with building and testing."
    echo ""
    echo "To resolve warnings:"
    if [ $WARN_COUNT -gt 0 ]; then
        echo "- Build PDG: cd pdg && mkdir -p build && cd build && cmake .. && make"
        echo "- Build Docker: ./build-docker.sh"
    fi
else
    echo -e "${RED}❌ Setup has critical issues that need to be resolved.${NC}"
    echo ""
    echo "Please fix the failed validations before proceeding."
fi

echo ""
echo "For detailed deployment instructions, see: DEPLOYMENT_GUIDE.md"

# Exit with appropriate code
if [ $FAIL_COUNT -eq 0 ]; then
    exit 0
else
    exit 1
fi