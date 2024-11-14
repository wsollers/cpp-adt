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

struct PriorityContainer
{
  int priority;
  int data;
  int getPriority() const { return priority; }

  // Define comparison operators based on priority
  auto operator<=>(const PriorityContainer& other) const = default;
  bool operator==(const PriorityContainer& other) const = default;
};

// Test the constructor and isEmpty() method
TEST(HeapTest, ConstructAndIsEmpty) {
  PriorityQueues::ArrayPriorityQueue<PriorityContainer> pq(10);
  EXPECT_TRUE(pq.isEmpty());
  EXPECT_EQ(pq.getSize(), 0);
}


