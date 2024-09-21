#include "../src/list/list.h"

#include <gtest/gtest.h>

class SkipFixture : public ::testing::Test {
 protected:
  void SetUp() override {
    GTEST_SKIP() << "Skipping all tests for this fixture";
  }
};

TEST_F(SkipFixture, SkipAllTests) {
  FAIL() << "This test should not be run";
}

TEST (circularListTest, SmokeTest) {
  oogabooga listo;
  listo.a = 1;
  EXPECT_EQ(listo.a, 1);
}

TEST (circularListTest, ConstructList) {
  Lists::CircularLinkedList<std::string> list;
  EXPECT_EQ(list.getSize(), 0);
}


TEST (circularListTest, addToFrontList) {
  Lists::CircularLinkedList<std::string> list;
  list.insertAtFront("hello");
  EXPECT_EQ(list.getSize(), 1);
}
