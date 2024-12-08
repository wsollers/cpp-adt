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

TEST(MapTest, AddRemoveEntry) {
  Maps::ArrayMap<int, int, 10> map = Maps::ArrayMap<int, int, 10>();
  map.insert(1, 1);
  EXPECT_FALSE(map.isEmpty());
  EXPECT_EQ(map.getSize(), 1);
  EXPECT_EQ(map.get(1), 1);
  map.remove(1);
  EXPECT_TRUE(map.isEmpty());
  EXPECT_EQ(map.getSize(), 0);
  EXPECT_FALSE(map.contains(1));
}

TEST(MapTest, KeysShouldBeHashable) {
    // Static assertions to check that certain types satisfy the Hashable concept
    static_assert(Common::Hashable<int>, "int should satisfy Hashable concept");
    static_assert(Common::Hashable<std::string>, "std::string should satisfy Hashable concept");

    // Negative test case: static_assert will fail if we uncomment this because float is not hashable
    // static_assert(Common::hashable<float>, "float should NOT satisfy Hashable concept");
}

struct TestStruct {
  int x;
  int y;
};

TEST(MapTest, TestStructIsNotHashable) {
  static_assert(!Common::Hashable<TestStruct>, "TestStruct should NOT satisfy Hashable concept");
}
