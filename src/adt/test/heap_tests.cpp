#include <gtest/gtest.h>

#include "../src/heap/heap.h"
#include "../src/heap/priority_queue.h"

class SkipFixture : public ::testing::Test {
protected:
  void SetUp() override {
    GTEST_SKIP() << "Skipping all tests for this fixture";
  }
};

TEST_F(SkipFixture, SkipAllTests) { FAIL() << "This test should not be run"; }

// Test suite for Tree

template <typename T> struct xx {
  PriorityQueues::Priority priority;
  T data;

  PriorityQueues::Priority getPriority() const { return priority; }

  // Define comparison operators based on priority
  auto operator<=>(const xx &other) const {
    return priority <=> other.priority;
  }
};
// Test the constructor and isEmpty() method
TEST(ArrayPriorityQTest, ConstructAndIsEmpty) {
  PriorityQueues::ArrayPriorityQueue<xx<int>> pq(10);
  EXPECT_TRUE(pq.isEmpty());
  EXPECT_EQ(pq.getSize(), 0);
}

TEST(LinkedPriorityQTest, ConstructAndIsEmpty) {
  PriorityQueues::LinkedPriorityQueue<xx<int>> pq;
  EXPECT_TRUE(pq.isEmpty());
  EXPECT_EQ(pq.getSize(), 0);
}

TEST(LinkedPriorityQTest, addElement) {
  PriorityQueues::LinkedPriorityQueue<xx<int>> pq;
  EXPECT_TRUE(pq.isEmpty());
  EXPECT_EQ(pq.getSize(), 0);
  pq.insert(1, xx<int>{1, 1});
  EXPECT_FALSE(pq.isEmpty());
  EXPECT_EQ(pq.getSize(), 1);
}

// MinHeap Tests
TEST(MinHeapTests, InitialState) {
  Heaps::MinHeap<int> minHeap;
  EXPECT_TRUE(minHeap.isEmpty());
  EXPECT_EQ(minHeap.size(), 0);
}

TEST(MinHeapTests, InsertAndTop) {
  Heaps::MinHeap<int> minHeap;
  minHeap.insert(10);
  minHeap.insert(5);
  minHeap.insert(15);
  minHeap.insert(1);

  EXPECT_EQ(minHeap.size(), 4);
  EXPECT_EQ(minHeap.top(), 1); // Smallest element is at the top
}

TEST(MinHeapTests, RemoveAndTop) {
  Heaps::MinHeap<int> minHeap;
  minHeap.insert(10);
  minHeap.insert(5);
  minHeap.insert(15);
  minHeap.insert(1);

  EXPECT_EQ(minHeap.top(), 1);
  minHeap.remove();
  EXPECT_EQ(minHeap.top(), 5);

  minHeap.remove();
  EXPECT_EQ(minHeap.top(), 10);

  minHeap.remove();
  EXPECT_EQ(minHeap.top(), 15);

  minHeap.remove();
  EXPECT_TRUE(minHeap.isEmpty());
}

TEST(MinHeapTests, ClearHeap) {
  Heaps::MinHeap<int> minHeap;
  minHeap.insert(10);
  minHeap.insert(5);
  minHeap.insert(15);

  minHeap.clear();
  EXPECT_TRUE(minHeap.isEmpty());
  EXPECT_EQ(minHeap.size(), 0);
}

TEST(MinHeapTests, EdgeCases) {
  Heaps::MinHeap<int> minHeap;
  EXPECT_THROW(minHeap.top(), std::runtime_error);
  EXPECT_THROW(minHeap.remove(), std::runtime_error);
}

// MaxHeap Tests
TEST(MaxHeapTests, InitialState) {
  Heaps::MaxHeap<int> maxHeap;
  EXPECT_TRUE(maxHeap.isEmpty());
  EXPECT_EQ(maxHeap.size(), 0);
}

TEST(MaxHeapTests, InsertAndTop) {
  Heaps::MaxHeap<int> maxHeap;
  maxHeap.insert(10);
  maxHeap.insert(5);
  maxHeap.insert(15);
  maxHeap.insert(20);

  EXPECT_EQ(maxHeap.size(), 4);
  EXPECT_EQ(maxHeap.top(), 20); // Largest element is at the top
}

TEST(MaxHeapTests, RemoveAndTop) {
  Heaps::MaxHeap<int> maxHeap;
  maxHeap.insert(10);
  maxHeap.insert(5);
  maxHeap.insert(15);
  maxHeap.insert(20);

  EXPECT_EQ(maxHeap.top(), 20);
  maxHeap.remove();
  EXPECT_EQ(maxHeap.top(), 15);

  maxHeap.remove();
  EXPECT_EQ(maxHeap.top(), 10);

  maxHeap.remove();
  EXPECT_EQ(maxHeap.top(), 5);

  maxHeap.remove();
  EXPECT_TRUE(maxHeap.isEmpty());
}

TEST(MaxHeapTests, ClearHeap) {
  Heaps::MaxHeap<int> maxHeap;
  maxHeap.insert(10);
  maxHeap.insert(5);
  maxHeap.insert(15);

  maxHeap.clear();
  EXPECT_TRUE(maxHeap.isEmpty());
  EXPECT_EQ(maxHeap.size(), 0);
}

TEST(MaxHeapTests, EdgeCases) {
  Heaps::MaxHeap<int> maxHeap;
  EXPECT_THROW(maxHeap.top(), std::runtime_error);
  EXPECT_THROW(maxHeap.remove(), std::runtime_error);
}

// Generic Tests for Heap Behavior
TEST(HeapTests, ConsistentBehavior) {
  Heaps::MinHeap<int> minHeap;
  Heaps::MaxHeap<int> maxHeap;
  std::vector<int> elements = {10, 5, 15, 20, 1};

  for (int elem : elements) {
    minHeap.insert(elem);
    maxHeap.insert(elem);
  }

  EXPECT_EQ(minHeap.top(), 1);  // MinHeap smallest element
  EXPECT_EQ(maxHeap.top(), 20); // MaxHeap largest element
}
