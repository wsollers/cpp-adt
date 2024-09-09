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

add_library(log SHARED 
  log.cpp
)

target_include_directories(log INTERFACE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
