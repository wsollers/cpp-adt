#include "../src/stack/stack.h"
#include <gtest/gtest.h>

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










