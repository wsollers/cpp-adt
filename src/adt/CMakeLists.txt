if (CMAKE_CXX_CPPCHECK)
    list(
        APPEND CMAKE_CXX_CPPCHECK 
            "--enable=warning"
            "--inconclusive"
            "--force" 
            "--inline-suppr"
            "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
    )
endif()

add_library(adt SHARED 
  src/list/list.cpp
  src/tree/tree.cpp
  src/node/node.cpp
  src/common/common.cpp
  src/graph/graph.cpp
  src/map/map.cpp
  src/set/set.cpp
  src/queue/queue.cpp
  src/stack/stack.cpp
  src/heap/priority_queue.cpp
)

add_library(adt-static 
  src/list/list.cpp
  src/tree/tree.cpp
  src/node/node.cpp
  src/common/common.cpp
  src/graph/graph.cpp
  src/map/map.cpp
  src/set/set.cpp
  src/queue/queue.cpp
  src/stack/stack.cpp
  src/heap/priority_queue.cpp
)
#target_include_directories(lib2 PUBLIC include)

# Enable CMake's testing framework
enable_testing()

# Install rules for library
#install(TARGETS adt DESTINATION lib)
#install(FILES adt.h DESTINATION include)

#
# Testing as dynamic library
#
add_executable(adt_test test/adt_test.cpp
)
target_link_libraries(adt_test PRIVATE adt gtest gtest_main)
add_test(NAME adt_test COMMAND bin/adt_test)

#
# Testing SLL as static library
#
add_executable(adt_sll_test_static test/single_linked_list_test.cpp
)
target_include_directories(adt_sll_test_static 
  PRIVATE src/list src/queue src/stack src/tree src/node src/common src/heap)
#target_link_libraries(adt_test_static PRIVATE  adt-static gtest gtest_main)
target_link_libraries(adt_sll_test_static PRIVATE  gtest gtest_main PUBLIC adt-static)
add_test(NAME adt_sll_test_static COMMAND bin/adt_test_static)


#
# Testing DLL as static library
#
add_executable(adt_dll_test_static test/double_linked_list_test.cpp
)
target_include_directories(adt_dll_test_static 
  PRIVATE src/list src/queue src/stack src/tree src/node src/common src/heap)
#target_link_libraries(adt_dll_test_static PRIVATE  adt-static gtest gtest_main)
target_link_libraries(adt_dll_test_static PRIVATE  gtest gtest_main PUBLIC adt-static)
add_test(NAME adt_dll_test_static COMMAND bin/adt_test_static)

#
# Testing CLL as static library
#
add_executable(adt_cll_test_static test/double_linked_list_test.cpp
)
target_include_directories(adt_cll_test_static 
  PRIVATE src/list src/queue src/stack src/tree src/node src/common src/heap)
#target_link_libraries(adt_cll_test_static PRIVATE  adt-static gtest gtest_main)
target_link_libraries(adt_cll_test_static PRIVATE  gtest gtest_main PUBLIC adt-static)
add_test(NAME adt_cll_test_static COMMAND bin/adt_test_static)

#
# Testing stack as static library
#
add_executable(adt_stack_test_static test/stack_tests.cpp)
target_include_directories(adt_stack_test_static 
  PRIVATE src/list src/queue src/stack src/tree src/map src/node src/common src/heap)
target_link_libraries(adt_stack_test_static PRIVATE  gtest gtest_main PUBLIC adt-static)
add_test(NAME adt_stack_test_static COMMAND bin/adt_test_static)

#
# Testing queue as static library
#
add_executable(adt_queue_test_static test/queue_tests.cpp)
target_include_directories(adt_queue_test_static 
  PRIVATE src/list src/queue src/stack src/tree src/map src/node src/common src/heap)
target_link_libraries(adt_queue_test_static PRIVATE  gtest gtest_main PUBLIC adt-static)
add_test(NAME adt_queue_test_static COMMAND bin/adt_test_static)

#
# Testing tree as static library
#
add_executable(adt_tree_test_static test/tree_tests.cpp)
target_include_directories(adt_tree_test_static 
  PRIVATE src/list src/queue src/stack src/tree src/map src/node src/common src/heap)
target_link_libraries(adt_tree_test_static PRIVATE  gtest gtest_main PUBLIC adt-static)
add_test(NAME adt_tree_test_static COMMAND bin/adt_test_static)

#
# Testing map  as static library
#
add_executable(adt_map_test_static test/map_tests.cpp)
target_include_directories(adt_map_test_static 
  PRIVATE src/list src/queue src/stack src/tree src/map src/node src/common src/heap)
target_link_libraries(adt_map_test_static PRIVATE  gtest gtest_main PUBLIC adt-static)
add_test(NAME adt_map_test_static COMMAND bin/adt_test_static)


#
# Testing heap  as static library
#
add_executable(adt_heap_test_static test/heap_tests.cpp)
target_include_directories(adt_heap_test_static 
  PRIVATE src/list src/queue src/stack src/tree src/map src/node src/common src/heap)
target_link_libraries(adt_heap_test_static PRIVATE  gtest gtest_main PUBLIC adt-static)
add_test(NAME adt_heap_test_static COMMAND bin/adt_test_static)


#
# Testing graph  as static library
#
add_executable(adt_graph_test_static test/graph_tests.cpp)
target_include_directories(adt_graph_test_static 
  PRIVATE src/list src/queue src/stack src/tree src/map src/node src/common src/heap src/graph)
target_link_libraries(adt_graph_test_static PRIVATE  gtest gtest_main PUBLIC adt-static)
add_test(NAME adt_graph_test_static COMMAND bin/adt_test_static)


#
# Fuzz Testing 
#
add_executable(fuzz_tester test/fuzz_test.cpp)
#  PRIVATE myproject_options
#          myproject_warnings
target_link_libraries(
  fuzz_tester
  PRIVATE 
          -coverage
          -fsanitize=fuzzer)
target_compile_options(fuzz_tester PRIVATE -fsanitize=fuzzer)

# Allow short runs during automated testing to see if something new breaks
set(FUZZ_RUNTIME
    10
    CACHE STRING "Number of seconds to run fuzz tests during ctest run") # Default of 10 seconds

add_test(NAME fuzz_tester_run COMMAND fuzz_tester -max_total_time=${FUZZ_RUNTIME})

#
# Benchmarking`
#

add_executable(sll_benchmark test/single_linked_list_benchmark.cpp)
set_property(TARGET ${sll_benchmark} PROPERTY CXX_EXTENSIONS ON)
target_include_directories(sll_benchmark PRIVATE src/list src/node src/common)
target_link_libraries(sll_benchmark PRIVATE /usr/local/lib/libbenchmark.a /usr/local/lib/libbenchmark_main.a PUBLIC adt-static)
add_test(NAME sll_benchmark_run COMMAND sll_benchmark)


add_executable(dll_benchmark test/double_linked_list_benchmark.cpp)
set_property(TARGET ${dll_benchmark} PROPERTY CXX_EXTENSIONS ON)
target_include_directories(dll_benchmark PRIVATE src/list src/node src/common)
target_link_libraries(dll_benchmark PRIVATE /usr/local/lib/libbenchmark.a /usr/local/lib/libbenchmark_main.a PUBLIC adt-static)
add_test(NAME dll_benchmark_run COMMAND dll_benchmark)


add_executable(cll_benchmark test/circular_linked_list_benchmark.cpp)
set_property(TARGET ${cll_benchmark} PROPERTY CXX_EXTENSIONS ON)
target_include_directories(cll_benchmark PRIVATE src/list src/node src/common)
target_link_libraries(cll_benchmark PRIVATE /usr/local/lib/libbenchmark.a /usr/local/lib/libbenchmark_main.a PUBLIC adt-static)
add_test(NAME cll_benchmark_run COMMAND cll_benchmark)


