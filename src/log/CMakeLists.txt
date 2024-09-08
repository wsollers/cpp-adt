add_library(log SHARED 
  log.cpp
)

target_include_directories(log INTERFACE 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
