#include <gtest/gtest.h>

#include "../src/map/map.h"

class SkipFixture : public ::testing::Test {
protected:
  void SetUp() override {
    GTEST_SKIP() << "Skipping all tests for this fixture";
  }
};

TEST_F(SkipFixture, SkipAllTests) { FAIL() << "This test should not be run"; }

// Test suite for Tree

// Test the constructor and isEmpty() method
TEST(MapTest, ConstructAndIsEmpty) {
  Maps::ArrayMap<int, int, 10> map = Maps::ArrayMap<int, int, 10>();
  EXPECT_TRUE(map.isEmpty());
  EXPECT_EQ(map.getSize(), 0);
}

TEST(MapTest, AddEntry) {
  Maps::ArrayMap<int, int, 10> map = Maps::ArrayMap<int, int, 10>();
  map.insert(1, 1);
  EXPECT_FALSE(map.isEmpty());
  EXPECT_EQ(map.getSize(), 1);
  EXPECT_EQ(map.get(1), 1);
}
