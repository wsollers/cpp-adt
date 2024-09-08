cmake_minimum_required(VERSION 3.22.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#pass option
set(CMAKE_CXX_FLAGS "")

# set the project name
project(adt-parent VERSION 0.0.1 DESCRIPTION "c++ experimental project")  

#libraries
add_subdirectory(adt)
add_subdirectory(log)

#applications
add_subdirectory(main)

add_subdirectory(lib/googletest)

# Enable CMake's testing framework
enable_testing()

# Optionally define where to install the project

install(TARGETS main adt log DESTINATION bin)
