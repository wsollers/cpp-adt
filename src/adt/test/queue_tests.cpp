#include <gtest/gtest.h>

#include "../src/queue/queue.h"

class SkipFixture : public ::testing::Test {
protected:
  void SetUp() override {
    GTEST_SKIP() << "Skipping all tests for this fixture";
  }
};

TEST_F(SkipFixture, SkipAllTests) { FAIL() << "This test should not be run"; }

// Test suite for Stack

// Test the constructor and isEmpty() method
TEST(QueueTest, ConstructAndIsEmpty) {
  Queues::ArrayQueue<int> queue(10);
  EXPECT_TRUE(queue.isEmpty());
  EXPECT_EQ(queue.getSize(), 0);
}

TEST(QueueTest, CanAddToEmptyQueue) {
  Queues::ArrayQueue<int> queue(10);
  queue.enqueue(1);
  EXPECT_EQ(queue.getSize(), 1);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_EQ(queue.peek(), 1);
}

TEST(QueueTest, CanEmptyQueue) {
  Queues::ArrayQueue<int> queue(10);
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  queue.enqueue(4);
  EXPECT_EQ(queue.getSize(), 4);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_EQ(queue.peek(), 1);
  auto item = queue.dequeue();
  EXPECT_EQ(item, 1);
  item = queue.dequeue();
  EXPECT_EQ(item, 2);
  item = queue.dequeue();
  EXPECT_EQ(item, 3);
  item = queue.dequeue();
  EXPECT_EQ(item, 4);
  EXPECT_TRUE(queue.isEmpty());
  EXPECT_EQ(queue.getSize(), 0);
  auto item2 = queue.dequeue();
  EXPECT_FALSE(item2.has_value());
}
