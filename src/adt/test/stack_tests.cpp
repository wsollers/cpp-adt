#include <gtest/gtest.h>

#include "../src/stack/stack.h"

class SkipFixture : public ::testing::Test {
protected:
  void SetUp() override {
    GTEST_SKIP() << "Skipping all tests for this fixture";
  }
};

TEST_F(SkipFixture, SkipAllTests) { FAIL() << "This test should not be run"; }

// Test suite for Stack

// Test the constructor and isEmpty() method
TEST(StackTest, ConstructAndIsEmpty) {
  Stacks::ArrayStack<int> stack(10);
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_EQ(stack.getSize(), 0);
}

TEST(StackTest, EmptyPop) {
  Stacks::ArrayStack<int> stack(10);
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_FALSE(stack.pop().has_value());
}

TEST(StackTest, EmptyPeek) {
  Stacks::ArrayStack<int> stack(10);
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_FALSE(stack.peek().has_value());
}

TEST(StackTest, TopItemIsPeekable) {
  Stacks::ArrayStack<int> stack(10);
  stack.push(1);
  EXPECT_EQ(stack.peek(), 1);
}

TEST(StackTest, TopItemIsPeekableMultiItems) {
  Stacks::ArrayStack<int> stack(10);
  stack.push(11);
  stack.push(12);
  stack.push(1);
  EXPECT_EQ(stack.peek(), 1);
}

TEST(StackTest, TopItemIsPopableMultiItems) {
  Stacks::ArrayStack<int> stack(10);
  stack.push(11);
  stack.push(12);
  stack.push(1);
  auto item = stack.pop();
  EXPECT_EQ(item, 1);
}









TEST(LinkedStackTest, ConstructAndIsEmpty) {
  Stacks::LinkedStack<int> stack;
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_EQ(stack.getSize(), 0);
}

TEST(LinkedStackTest, EmptyPop) {
  Stacks::LinkedStack<int> stack;
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_FALSE(stack.pop().has_value());
}

TEST(LinkedStackTest, EmptyPeek) {
  Stacks::LinkedStack<int> stack;
  EXPECT_TRUE(stack.isEmpty());
  EXPECT_FALSE(stack.peek().has_value());
}

TEST(LinkedStackTest, TopItemIsPeekable) {
  Stacks::LinkedStack<int> stack;
  stack.push(1);
  EXPECT_EQ(stack.peek(), 1);
}

TEST(LinkedStackTest, TopItemIsPeekableMultiItems) {
  Stacks::LinkedStack<int> stack;
  stack.push(11);
  stack.push(12);
  stack.push(1);
  EXPECT_EQ(stack.peek(), 1);
}

TEST(LinkedStackTest, TopItemIsPopableMultiItems) {
  Stacks::LinkedStack<int> stack;
  stack.push(11);
  stack.push(12);
  stack.push(1);
  auto item = stack.pop();
  EXPECT_EQ(item, 1);
}











