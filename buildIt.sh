#!/bin/bash

# Initialize variables
clean=0

# Parse command line options
while [[ "$#" -gt 0 ]]; do
    case $1 in
        --clean) clean=1 ;;
        *) echo "Unknown option: $1" ;;
    esac
    shift
done


currentDir=$(pwd)
#
# If --clean was provided, run git clean
if [[ "$clean" -eq 1 ]]; then
    echo "Running git clean..."
    # Purge stuff not in source control
    git clean -d -f -x
    # put the build dir back
    mkdir build
else
    echo "Skipping git clean..."
fi

mkdir build
cd build || exit

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

cmake \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
  -DCMAKE_C_COMPILER=/usr/bin/clang \
  -DCMAKE_CPP_COMPILER=/usr/bin/clang++ \
  -DCMAKE_BUILD_TYPE=Debug \
  ../src/CMakeLists.txt

cd "$currentDir"
