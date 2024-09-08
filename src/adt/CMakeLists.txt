add_library(adt SHARED 
  src/list/list.cpp
  src/node/node.cpp
  src/common/common.cpp
)

target_include_directories(adt INTERFACE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Enable CMake's testing framework
enable_testing()

# Install rules for library
#install(TARGETS adt DESTINATION lib)
#install(FILES adt.h DESTINATION include)

# Create unit test executable for libA
add_executable(adt_test test/adt_test.cpp)

# Link libA and GTest to the test executable
target_link_libraries(adt_test PRIVATE adt gtest gtest_main)

# Add the test
add_test(NAME adt_test COMMAND bin/adt_test)

