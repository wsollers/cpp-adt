#include <gtest/gtest.h>

#include "../src/tree/tree.h"

class SkipFixture : public ::testing::Test {
protected:
  void SetUp() override {
    GTEST_SKIP() << "Skipping all tests for this fixture";
  }
};

TEST_F(SkipFixture, SkipAllTests) { FAIL() << "This test should not be run"; }

// Test suite for Tree

// Test the constructor and isEmpty() method
TEST(BinarySearchTreeTest, ConstructAndIsEmpty) {
  Trees::BinarySearchTree<int> bst;
  EXPECT_TRUE(bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 0);
}
