#ifndef COMMON_H
#define COMMON_H

//#include <experimental/source_location>
#include <string_view>

struct Error {
  std::string_view message;
  std::string_view file;
  std::string_view function;
  std::size_t line;
  //std::experimental::source_location src;
};

void report_error(const Error& error);

void test_common();

#endif // COMMON_H
