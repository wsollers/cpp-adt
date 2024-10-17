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

TEST(BinarySearchTreeTest, AddARootNode) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  EXPECT_TRUE(!bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 1);
}


TEST(BinarySearchTreeTest, FindARootNode) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  EXPECT_TRUE(!bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 1);
  EXPECT_TRUE(bst.contains(1));
}

TEST(BinarySearchTreeTest, FindALeafNode) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  EXPECT_TRUE(!bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 3);
  EXPECT_TRUE(bst.contains(3));
}

TEST(BinarySearchTreeTest, DoesNotFindALeafNode) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  EXPECT_TRUE(!bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 3);
  EXPECT_FALSE(bst.contains(5));
}

TEST(BinarySearchTreeTest, DefaultComparator) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  EXPECT_TRUE(!bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 3);
  EXPECT_TRUE(bst.contains(3));
}

TEST(BinarySearchTreeTest, SpecificCommonComparator) {
  Trees::BinarySearchTree<int, Common::Comparator<int>> bst;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  EXPECT_TRUE(!bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 3);
  EXPECT_TRUE(bst.contains(3));
}

template <typename T> class ComparatorX {
public:
  bool operator()(const T &lhs, const T &rhs) {
    return lhs < rhs;
  }
  int compare(const T &lhs, const T &rhs) {
    if ( lhs < rhs) {
      return -1;
    } else if ( rhs < lhs ) {
      return 1;
    } else {
      return 0;
    }
  }
};
TEST(BinarySearchTreeTest, SpecificCustomComparator) {
  Trees::BinarySearchTree<int, ComparatorX<int>> bst;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  EXPECT_TRUE(!bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 3);
  EXPECT_TRUE(bst.contains(3));
}
