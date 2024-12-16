#ifndef COMMON_H
#define COMMON_H

// #include <experimental/source_location>
#include <concepts>
#include <string_view>

void test_common();

namespace Common {

struct Error {
  std::string_view message;
  std::string_view file;
  std::string_view function;
  std::size_t line;
  // std::experimental::source_location src;
};

void report_error(const Error &error);

// Concept that specifies the requirements for an item to be hashable
template <typename T>
concept Hashable = requires(T t) {
  { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
};

// Concept that specifies the requirements for an item to be storable in a STL
// container
template <typename T>
concept stl_container_storable =
    std::destructible<T> && std::default_initializable<T> &&
    std::move_constructible<T> && std::copy_constructible<T>;

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

template <typename T>
class Comparator {
 public:
  bool operator()(const T &lhs, const T &rhs) { return lhs < rhs; }
  int compare(const T &lhs, const T &rhs) {
    if (lhs < rhs) {
      return -1;
    } else if (rhs < lhs) {
      return 1;
    } else {
      return 0;
    }
  }
};

}  // namespace Common
#endif  // COMMON_H
