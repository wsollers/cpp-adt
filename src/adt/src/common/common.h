#ifndef COMMON_H
#define COMMON_H

// #include <experimental/source_location>
#include <concepts>
#include <string_view>

struct Error {
  std::string_view message;
  std::string_view file;
  std::string_view function;
  std::size_t line;
  // std::experimental::source_location src;
};

void report_error(const Error &error);

void test_common();

namespace Common {

//Concept that specifies the requirements for an item to be storable in a STL container
template <typename T>
concept stl_container_storable =
    std::destructible<T> && std::default_initializable<T> &&
    std::move_constructible<T> && std::copy_constructible<T>;

}

// constructible_from
// default_initializable
// move_constructible
// copy_constructible

/*
Destructible
MoveConstructible
MoveAssignable
Optionally CopyConstructible and CopyAssignable depending on how you use the
container EqualityComparable or LessThanComparable
*/

#endif // COMMON_H
