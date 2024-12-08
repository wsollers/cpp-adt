#include <gtest/gtest.h>

#include "../src/heap/priority_queue.h"

class SkipFixture : public ::testing::Test {
protected:
  void SetUp() override {
    GTEST_SKIP() << "Skipping all tests for this fixture";
  }
};

TEST_F(SkipFixture, SkipAllTests) { FAIL() << "This test should not be run"; }

// Test suite for Tree

template <typename T>
struct xx {
  PriorityQueues::Priority priority;
  T data;

  PriorityQueues::Priority getPriority() const { return priority; }

  // Define comparison operators based on priority
  auto operator<=>(const xx &other) const { return priority <=> other.priority; }

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
