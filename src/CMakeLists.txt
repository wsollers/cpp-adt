cmake_minimum_required(VERSION 3.22.1)

#https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CodeCoverage)

append_coverage_compiler_flags()
set(COVERAGE_EXCLUDES '${PROJECT_SOURCE_DIR}/lib/*')

#set(CMAKE_VERBOSE_MAKEFILE ON)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_C_COMPILER "/usr/bin/clang")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY bin )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY bin )

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)

# set the project name
project(adt-parent VERSION 0.0.1 DESCRIPTION "c++ experimental project")  

#libraries
add_subdirectory(adt)
add_subdirectory(log)

#applications
add_subdirectory(main)

#Google Test
add_subdirectory(lib/googletest)

# Enable CMake's testing framework
enable_testing()

install(TARGETS main adt log DESTINATION bin)

#Google Benchmark
add_subdirectory(lib/googlebenchmark)

set(CPPCHECK_EXCLUDES
    ${CMAKE_SOURCE_DIR}/lib/*
)
#${CMAKE_BINARY_DIR}/

#
#find_package(benchmark REQUIRED)

