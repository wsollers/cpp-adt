#include <concepts>
#include <ranges>

#include "../src/list/list.h"
#include "../src/common/common.h"


#include <gtest/gtest.h>

class SkipFixture : public ::testing::Test {
protected:
  void SetUp() override {
    GTEST_SKIP() << "Skipping all tests for this fixture";
  }
};

TEST_F(SkipFixture, SkipAllTests) { FAIL() << "This test should not be run"; }

// Test suite for SinglyLinkedList

// Test the constructor and isEmpty() method
TEST(SinglyLinkedListTest, ConstructAndIsEmpty) {
  Common::Error error = {"Error message", "file", "function", 1};
  Common::report_error(error);
  test_common();
  Lists::SinglyLinkedList<int> list;
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.getSize(), 0);
}

// Test add(T data) method (adding elements to the end of the list)
TEST(SinglyLinkedListTest, AddElementsToEnd) {
  Lists::SinglyLinkedList<int> list;
  EXPECT_TRUE(list.add(1));
  EXPECT_EQ(list.getSize(), 1);
}

// Test add(size_t index, T data) method (inserting elements at specific index)
TEST(SinglyLinkedListTest, AddElementsAtIndex) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  list.add(2);
  list.add(4);
  EXPECT_TRUE(list.add(2, 3)); // Insert 3 at index 2
  EXPECT_EQ(list.getSize(), 4);
  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 2);
  EXPECT_EQ(list.get(2), 3);
  EXPECT_EQ(list.get(3), 4);
}

// Test add(size_t index, T data) method (out of bounds)
TEST(SinglyLinkedListTest, AddElementAtInvalidIndex) {
  Lists::SinglyLinkedList<int> list;
  std::optional<bool> retVal = list.add(2, 5);
  EXPECT_FALSE(retVal.value()); // Index out of bounds
}

// Test remove(size_t index) method
TEST(SinglyLinkedListTest, RemoveElementByIndex) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  list.add(2);
  list.add(3);
  EXPECT_TRUE(list.remove(static_cast<size_t>(1))); 
  EXPECT_EQ(list.getSize(), 2);
  EXPECT_EQ(list.get(0), 1);
  EXPECT_EQ(list.get(1), 3);
}

// Test remove(size_t index) method (out of bounds)
TEST(SinglyLinkedListTest, RemoveElementAtInvalidIndex) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  auto retVal = list.remove(5); // Index out of bounds
  EXPECT_FALSE(retVal); // Index out of bounds
}

// Test remove(T data) method (removing by value)
TEST(SinglyLinkedListTest, RemoveElementByValue) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  list.add(2);
  list.add(3);
  EXPECT_TRUE(list.remove(2)); // Remove value 2
  EXPECT_FALSE(list.contains(2));
  EXPECT_EQ(list.getSize(), 2);
}

// Test remove(T data) method (removing non-existent value)
TEST(SinglyLinkedListTest, RemoveNonExistentElement) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  EXPECT_FALSE(list.remove(100)); // Value 100 does not exist
}

// Test contains() method
TEST(SinglyLinkedListTest, ContainsElement) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  list.add(2);
  EXPECT_TRUE(list.contains(1));
  EXPECT_FALSE(list.contains(3));
}

// Test get(size_t index) method
TEST(SinglyLinkedListTest, GetElementByIndex) {
  Lists::SinglyLinkedList<int> list;
  list.add(10);
  list.add(20);
  EXPECT_EQ(list.get(0), 10);
  EXPECT_EQ(list.get(1), 20);
}

// Test get(size_t index) method (out of bounds)
TEST(SinglyLinkedListTest, GetElementAtInvalidIndex) {
  Lists::SinglyLinkedList<int> list;
  list.add(5);
  auto retVal = list.get(2);
  EXPECT_FALSE(retVal.has_value());
}

// Test set(size_t index, T data) method
TEST(SinglyLinkedListTest, SetElementByIndex) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  list.add(2);
  EXPECT_EQ(list.set(1, 5), 2); // Set value at index 1 to 5, expect old value 2
  EXPECT_EQ(list.get(1), 5);
}

// Test set(size_t index, T data) method (out of bounds)
TEST(SinglyLinkedListTest, SetElementAtInvalidIndex) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  EXPECT_TRUE(list.contains(1));
  EXPECT_EQ(list.getSize(), 1);
}

// Test indexOf(T data) method
TEST(SinglyLinkedListTest, IndexOfElement) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  list.add(2);
  list.add(3);
  EXPECT_EQ(list.indexOf(2), 1);
  EXPECT_EQ(list.indexOf(4), -1); // Element not found
}

// Test lastIndexOf(T data) method
TEST(SinglyLinkedListTest, LastIndexOfElement) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  list.add(2);
  list.add(2);
  list.add(3);
  EXPECT_EQ(list.lastIndexOf(2), 2);
  EXPECT_EQ(list.lastIndexOf(4), -1); // Element not found
}

// Test isEmpty() method
TEST(SinglyLinkedListTest, IsEmpty) {
  Lists::SinglyLinkedList<int> list;
  EXPECT_TRUE(list.isEmpty());
  list.add(1);
  EXPECT_FALSE(list.isEmpty());
}

// Test getSize() method
TEST(SinglyLinkedListTest, GetSize) {
  Lists::SinglyLinkedList<int> list;
  EXPECT_EQ(list.getSize(), 0);
  list.add(1);
  list.add(2);
  EXPECT_EQ(list.getSize(), 2);
}

// Test clear() method
TEST(SinglyLinkedListTest, ClearList) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  list.add(2);
  list.clear();
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.getSize(), 0);
}

// Test edge case: Adding/removing a single element and checking list behavior
TEST(SinglyLinkedListTest, AddRemoveSingleElement) {
  Lists::SinglyLinkedList<int> list;
  list.add(100);
  EXPECT_EQ(list.getSize(), 1);
  EXPECT_TRUE(list.remove(100)); // Remove the only element
  EXPECT_TRUE(list.isEmpty());
  auto opt = list.get(0);
  EXPECT_FALSE(opt.has_value());
}

TEST(SinglyLinkedListTest, IterateOverList) {
  Lists::SinglyLinkedList<int> list;
  list.add(1);
  list.add(2);
  list.add(3);

  auto it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, list.end());
}

TEST(SinglyLinkedListTest, SortList) {
  Lists::SinglyLinkedList<int> list;
  list.add(3);
  list.add(2);
  list.add(1);

  auto begin = list.rand_begin();
  auto end = list.rand_begin();
  std::sort(begin, end);
  EXPECT_EQ(list.get(0), 1);
}

TEST(SinglyLinkedListTest, ConstructFromStdRange) {
  auto range = std::views::iota(0, 1024); // Generates values from 0 to 1024 (inclusive)

  Lists::SinglyLinkedList<int> list(range); // Pass the range to your constructor

  EXPECT_EQ(list.getSize(), 1024);
  EXPECT_TRUE(list.remove(0)); // Remove the only element
}

/*
TEST(SinglyLinkedListTest, Destructor) {
  struct non_copyable {
    non_copyable() = default;
    ~non_copyable() = delete;
    non_copyable(const non_copyable &) = delete;
    non_copyable(non_copyable &&) = default;
  };

  static_assert(std::destructible<non_copyable>);
  Lists::SinglyLinkedList<non_copyable> list;
}
*/
