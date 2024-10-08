#include <iostream>

#include "../../include/adt.h"

#include "common.h"

void print_adt_message() {
  std::cout << "Hello from ADT!" << std::endl;
}

void report_error(const Error& error) {
  std::cout << "Error: " << error.message << std::endl;
  std::cout << "\tFile: " << error.file << std::endl;
  std::cout << "\tFunction: " << error.function << std::endl;
  std::cout << "\tLine: " << error.line << std::endl;
  //std::cout << "Source: " << error.src.file_name() << std::endl;
}

void test_common() {
  Error error = {"Test error", "common.cpp", "test_common", 20};
  report_error(error);
}
