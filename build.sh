#!/bin/bash

# HAM Build Script
# Build and install HAM to Desktop (macOS) or current directory (Linux)

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}🎹 Building HAM - Happy Accident Machine${NC}"
echo "========================================"

# Detect platform
if [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macOS"
    INSTALL_DIR="$HOME/Desktop"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    PLATFORM="Linux"
    INSTALL_DIR="$PWD"
else
    echo -e "${RED}❌ Unsupported platform: $OSTYPE${NC}"
    exit 1
fi

echo -e "${YELLOW}📋 Platform: $PLATFORM${NC}"
echo -e "${YELLOW}📦 Install directory: $INSTALL_DIR${NC}"

# Check prerequisites
echo -e "${YELLOW}🔍 Checking prerequisites...${NC}"

# Check CMake
if ! command -v cmake &> /dev/null; then
    echo -e "${RED}❌ CMake not found. Please install CMake 3.22 or later.${NC}"
    exit 1
fi

CMAKE_VERSION=$(cmake --version | head -n1 | cut -d' ' -f3)
echo -e "${GREEN}✅ CMake $CMAKE_VERSION found${NC}"

# Check Git
if ! command -v git &> /dev/null; then
    echo -e "${RED}❌ Git not found. Please install Git.${NC}"
    exit 1
fi

echo -e "${GREEN}✅ Git found${NC}"

# Check for Xcode Command Line Tools on macOS
if [[ "$PLATFORM" == "macOS" ]]; then
    if ! xcode-select -p &> /dev/null; then
        echo -e "${RED}❌ Xcode Command Line Tools not found.${NC}"
        echo "Install with: xcode-select --install"
        exit 1
    fi
    echo -e "${GREEN}✅ Xcode Command Line Tools found${NC}"
fi

# Create build directory
echo -e "${YELLOW}📁 Creating build directory...${NC}"
rm -rf build
mkdir -p build
cd build

# Configure build
echo -e "${YELLOW}⚙️  Configuring build...${NC}"

CMAKE_ARGS=""
# Parse command line arguments for CMake options
for arg in "$@"; do
    if [[ $arg == -D* ]]; then
        CMAKE_ARGS="$CMAKE_ARGS $arg"
    fi
done

cmake .. -DCMAKE_BUILD_TYPE=Release $CMAKE_ARGS

# Build
echo -e "${YELLOW}🔨 Building HAM...${NC}"
cmake --build . --config Release -j $(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Install/Copy
echo -e "${YELLOW}📦 Installing HAM...${NC}"

if [[ "$PLATFORM" == "macOS" ]]; then
    # Copy .app bundle to Desktop
    if [ -d "HAM.app" ]; then
        cp -R HAM.app "$INSTALL_DIR/"
        echo -e "${GREEN}✅ HAM.app installed to $INSTALL_DIR${NC}"
        echo -e "${GREEN}🚀 Launch with: open $INSTALL_DIR/HAM.app${NC}"
    else
        echo -e "${YELLOW}⚠️  HAM.app not found, copying executable instead${NC}"
        cp HAM "$INSTALL_DIR/"
        echo -e "${GREEN}✅ HAM executable installed to $INSTALL_DIR${NC}"
        echo -e "${GREEN}🚀 Launch with: $INSTALL_DIR/HAM${NC}"
    fi
else
    # Copy executable
    cp HAM "$INSTALL_DIR/"
    echo -e "${GREEN}✅ HAM executable installed to $INSTALL_DIR${NC}"
    echo -e "${GREEN}🚀 Launch with: $INSTALL_DIR/HAM${NC}"
fi

echo -e "${GREEN}🎉 Build completed successfully!${NC}"
echo ""
echo -e "${YELLOW}📊 Build Summary:${NC}"
echo "   Platform: $PLATFORM"
echo "   Install Location: $INSTALL_DIR"
echo "   Configuration: Release"
if [[ ! -z "$CMAKE_ARGS" ]]; then
    echo "   CMake Options: $CMAKE_ARGS"
fi

echo ""
echo -e "${GREEN}🎹 HAM is ready to create some happy accidents!${NC}"