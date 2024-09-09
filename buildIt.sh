#!/bin/bash

currentDir=$(pwd)

cd build || exit

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CPP_COMPILER=/usr/bin/clang++ \
  ../src/CMakeLists.txt

cd "$currentDir"
