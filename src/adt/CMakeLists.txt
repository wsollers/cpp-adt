
add_library(adt SHARED 
  src/list/list.cpp
  src/node/node.cpp
  src/common/common.cpp
)

add_library(adt-static 
  src/list/list.cpp
  src/node/node.cpp
  src/common/common.cpp
)
#target_include_directories(lib2 PUBLIC include)

# Enable CMake's testing framework
enable_testing()

# Install rules for library
#install(TARGETS adt DESTINATION lib)
#install(FILES adt.h DESTINATION include)

set(CMAKE_VERBOSE_MAKEFILE OFF)
add_executable(adt_test test/adt_test.cpp
)
target_link_libraries(adt_test PRIVATE adt gtest gtest_main)
add_test(NAME adt_test COMMAND bin/adt_test)

add_executable(adt_test_static test/list_test.cpp
)
target_include_directories(adt_test_static PRIVATE src/list src/node src/common)
#target_link_libraries(adt_test_static PRIVATE  adt-static gtest gtest_main)
target_link_libraries(adt_test_static PRIVATE  gtest gtest_main)
add_test(NAME adt_test_static COMMAND bin/adt_test_static)





