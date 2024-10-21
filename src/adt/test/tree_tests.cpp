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
TEST(BinarySearchTreeTest, SpecificCustomComparator) {
  Trees::BinarySearchTree<int, ComparatorX<int>> bst;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  EXPECT_TRUE(!bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 3);
  EXPECT_TRUE(bst.contains(3));
}

TEST(BinarySearchTreeTest, FindMatchingElementsEven) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  bst.insert(4);
  bst.insert(5);
  bst.insert(6);

  // Define a predicate (find elements greater than 7)
  auto predicate = [](const int &value) { return value % 2 == 0; };

  // Get all matching elements
  std::vector<int> result = bst.findMatchingElements(predicate);

  EXPECT_EQ(result.size(), 3);
}

TEST(BinarySearchTreeTest, FindMatchingElementsMultOfThree) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  bst.insert(4);
  bst.insert(5);
  bst.insert(6);

  // Define a predicate (find elements greater than 7)
  auto predicate = [](const int &value) { return value % 3 == 0; };

  // Get all matching elements
  std::vector<int> result = bst.findMatchingElements(predicate);

  EXPECT_EQ(result.size(), 2);
}

TEST(BinarySearchTreeTest, preOrderTraversalElementsEven) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  bst.insert(4);
  bst.insert(5);
  bst.insert(6);

  // Define a predicate (find elements greater than 7)
  auto predicate = [](const int &value) { return value % 2 == 0; };

  // Get all matching elements
  std::vector<int> result;

  bst.preOrderWithPredicate(predicate, result);

  EXPECT_EQ(result.size(), 3);
}

TEST(BinarySearchTreeTest, postOrderTraversalElementsEven) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  bst.insert(4);
  bst.insert(5);
  bst.insert(6);

  // Define a predicate (find elements greater than 7)
  auto predicate = [](const int &value) { return value % 2 == 0; };

  // Get all matching elements
  std::vector<int> result;

  bst.postOrderWithPredicate(predicate, result);

  EXPECT_EQ(result.size(), 3);
}


TEST(BinarySearchTreeTest, inOrderTraversalElementsEven) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  bst.insert(2);
  bst.insert(3);
  bst.insert(4);
  bst.insert(5);
  bst.insert(6);

  // Define a predicate (find elements greater than 7)
  auto predicate = [](const int &value) { return value % 2 == 0; };

  // Get all matching elements
  std::vector<int> result;

  bst.inOrderWithPredicate(predicate, result);

  EXPECT_EQ(result.size(), 3);
}


//cmake/cmp to find depss???
TEST (BinarySearchTreeTest, DeleteRoot) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  bst.remove(1);
  EXPECT_TRUE(bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 0);

}

TEST (BinarySearchTreeTest, DeleteRootLeft) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(2);
  bst.insert(1);
  bst.remove(1);
  EXPECT_FALSE(bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 1);

}

TEST (BinarySearchTreeTest, DeleteRootRight) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(1);
  bst.insert(2);
  bst.remove(1);
  EXPECT_FALSE(bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 1);

}

TEST (BinarySearchTreeTest, DeleteSubTrees) {
  Trees::BinarySearchTree<int> bst;
  bst.insert(12);
  bst.insert(6);
  bst.insert(4);
  bst.insert(2);
  bst.insert(7);
  bst.insert(5);
  bst.insert(3);
  bst.remove(6);
  bst.remove(7);
  EXPECT_FALSE(bst.isEmpty());
  EXPECT_EQ(bst.getSize(), 5);

}
