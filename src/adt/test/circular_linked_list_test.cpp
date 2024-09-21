#include <gtest/gtest.h>
#include <stdexcept>
#include "../src/list/list.h"


// Test suite for CircularLinkedList

// Test the constructor and isEmpty() method
TEST(CircularLinkedListTest, ConstructAndIsEmpty) {
    Lists::CircularLinkedList<int> list;
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 0);
}

// Test add(T data) method (adding elements to the end of the list)
TEST(CircularLinkedListTest, AddElementsToEnd) {
    Lists::CircularLinkedList<int> list;
    EXPECT_TRUE(list.add(1));
    EXPECT_TRUE(list.add(2));
    EXPECT_TRUE(list.add(3));
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
    EXPECT_EQ(list.get(2), 3);
}

// Test add(size_t index, T data) method (inserting elements at a specific index)
TEST(CircularLinkedListTest, AddElementsAtIndex) {
    Lists::CircularLinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(4);
    EXPECT_TRUE(list.add(2, 3));  // Insert 3 at index 2
    EXPECT_EQ(list.getSize(), 4);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
    EXPECT_EQ(list.get(2), 3);
    EXPECT_EQ(list.get(3), 4);
}

// Test add(size_t index, T data) method (out of bounds)
TEST(CircularLinkedListTest, AddElementAtInvalidIndex) {
    Lists::CircularLinkedList<int> list;
    EXPECT_THROW(list.add(2, 5), std::out_of_range);  // List is empty, index 2 is invalid
}

// Test remove(size_t index) method
TEST(CircularLinkedListTest, RemoveElementByIndex) {
    Lists::CircularLinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    EXPECT_EQ(list.remove(1), 2);  // Remove element at index 1 (value 2)
    EXPECT_EQ(list.getSize(), 2);
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 3);
}

// Test remove(size_t index) method (out of bounds)
TEST(CircularLinkedListTest, RemoveElementAtInvalidIndex) {
    Lists::CircularLinkedList<int> list;
    list.add(1);
    EXPECT_THROW(list.remove(5), std::out_of_range);  // Index out of bounds
}

// Test remove(T data) method (removing by value)
TEST(CircularLinkedListTest, RemoveElementByValue) {
    Lists::CircularLinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    EXPECT_TRUE(list.remove(2));  // Remove value 2
    EXPECT_FALSE(list.contains(2));
    EXPECT_EQ(list.getSize(), 2);
}

// Test remove(T data) method (removing non-existent value)
TEST(CircularLinkedListTest, RemoveNonExistentElement) {
    Lists::CircularLinkedList<int> list;
    list.add(1);
    EXPECT_FALSE(list.remove(100));  // Value 100 does not exist
}

// Test contains() method
TEST(CircularLinkedListTest, ContainsElement) {
    Lists::CircularLinkedList<int> list;
    list.add(1);
    list.add(2);
    EXPECT_TRUE(list.contains(1));
    EXPECT_FALSE(list.contains(3));
}

// Test get(size_t index) method
TEST(CircularLinkedListTest, GetElementByIndex) {
    Lists::CircularLinkedList<int> list;
    list.add(10);
    list.add(20);
    EXPECT_EQ(list.get(0), 10);
    EXPECT_EQ(list.get(1), 20);
}

// Test get(size_t index) method (out of bounds)
TEST(CircularLinkedListTest, GetElementAtInvalidIndex) {
    Lists::CircularLinkedList<int> list;
    list.add(5);
    EXPECT_THROW(list.get(2), std::out_of_range);  // Index out of bounds
}

// Test set(size_t index, T data) method
TEST(CircularLinkedListTest, SetElementByIndex) {
    Lists::CircularLinkedList<int> list;
    list.add(1);
    list.add(2);
    EXPECT_EQ(list.set(1, 5), 2);  // Set value at index 1 to 5, expect old value 2
    EXPECT_EQ(list.get(1), 5);
}

// Test set(size_t index, T data) method (out of bounds)
TEST(CircularLinkedListTest, SetElementAtInvalidIndex) {
    Lists::CircularLinkedList<int> list;
    list.add(1);
    EXPECT_THROW(list.set(3, 5), std::out_of_range);  // Index out of bounds
}

// Test indexOf(T data) method
TEST(CircularLinkedListTest, IndexOfElement) {
    Lists::CircularLinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    EXPECT_EQ(list.indexOf(2), 1);
    EXPECT_EQ(list.indexOf(4), -1);  // Element not found
}

// Test lastIndexOf(T data) method
TEST(CircularLinkedListTest, LastIndexOfElement) {
    Lists::CircularLinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(2);
    list.add(3);
    EXPECT_EQ(list.lastIndexOf(2), 2);
    EXPECT_EQ(list.lastIndexOf(4), -1);  // Element not found
}

// Test isEmpty() method
TEST(CircularLinkedListTest, IsEmpty) {
    Lists::CircularLinkedList<int> list;
    EXPECT_TRUE(list.isEmpty());
    list.add(1);
    EXPECT_FALSE(list.isEmpty());
}

// Test getSize() method
TEST(CircularLinkedListTest, GetSize) {
    Lists::CircularLinkedList<int> list;
    EXPECT_EQ(list.getSize(), 0);
    list.add(1);
    list.add(2);
    EXPECT_EQ(list.getSize(), 2);
}

// Test clear() method
TEST(CircularLinkedListTest, ClearList) {
    Lists::CircularLinkedList<int> list;
    list.add(1);
    list.add(2);
    list.clear();
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 0);
}

// Test edge case: Adding/removing a single element and checking list behavior
TEST(CircularLinkedListTest, AddRemoveSingleElement) {
    Lists::CircularLinkedList<int> list;
    list.add(100);
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list.remove(0), 100);  // Remove the only element
    EXPECT_TRUE(list.isEmpty());
    EXPECT_THROW(list.get(0), std::out_of_range);  // List is now empty
}

