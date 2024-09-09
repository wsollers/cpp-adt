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

add_executable(main 
  main.cpp
)

target_link_libraries(main PRIVATE adt log)

# Include directories for the libraries
target_include_directories(main PRIVATE ../adt ../log)
