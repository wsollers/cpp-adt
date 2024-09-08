add_executable(main 
  main.cpp
)

target_link_libraries(main PRIVATE adt log)

# Include directories for the libraries
target_include_directories(main PRIVATE ../adt ../log)
