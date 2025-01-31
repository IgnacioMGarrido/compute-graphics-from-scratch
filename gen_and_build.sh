#!/bin/bash

# Default generator (change this if needed)
DEFAULT_GENERATOR="Ninja"

# Check if a generator was provided as an argument
if [ "$#" -eq 1 ]; then
    GENERATOR="$1"
else
    GENERATOR="$DEFAULT_GENERATOR"
fi

# Check if a target was provided (second argument)
if [ "$#" -ge 2 ]; then
    TARGET="$2"
else
    TARGET=""
fi

# Create the build directory if it doesn't exist
mkdir -p build
cd build || exit 1

# Run CMake with the selected generator
echo "Generating project with generator: $GENERATOR"
cmake -G "$GENERATOR" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

# Move compile_commands.json to the root directory
if [ -f "compile_commands.json" ]; then
    mv compile_commands.json ..
    echo "Moved compile_commands.json to the project root."
fi

# Detect number of CPU cores
if command -v nproc &>/dev/null; then
    CORES=$(nproc)
elif command -v sysctl &>/dev/null; then
    CORES=$(sysctl -n hw.ncpu)
else
    CORES=1
fi

# Build the project
if [ -z "$TARGET" ]; then
    echo "Building the entire project..."
    cmake --build . --parallel "$CORES"
else
    echo "Building target: $TARGET"
    cmake --build . --target "$TARGET" --parallel "$CORES"
fi

# Return to root directory
cd ..

echo "Project successfully generated in 'build/' directory!"
