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

TEST (adtTest, SmokeTest) {
  oogabooga listo;
  listo.a = 1;
  EXPECT_EQ(listo.a, 1);
}

TEST (adtTest, ConstructListInt) {
  SinglyLinkedList<int> list;
  EXPECT_EQ(list.getSize(), 0);
}
/*
//not sure this is a good test
TEST (adtTest, CanDestroyList) {
  {
    SinglyLinkedList<int> list;
    list.getSize();
  }
}
*/

TEST (adtTest, ConstructListString) {
  SinglyLinkedList<std::string> list;
  EXPECT_EQ(list.getSize(), 0);
}

TEST (adtTest, PrintEmptyList) {
  SinglyLinkedList<std::string> list;
  testing::internal::CaptureStdout();
  list.print();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "\n");
}

TEST (adtTest, AddOneElement) {
  SinglyLinkedList<int> list;
  list.add(1);
  EXPECT_EQ(list.getSize(), 1);
}

TEST (adtTest, AddTwoElements) {
  SinglyLinkedList<int> list;
  list.add(1);
  list.add(2);
  EXPECT_EQ(list.getSize(), 2);
}

TEST (adtTest, AddAndRemoveElement) {
  SinglyLinkedList<int> list;
  list.add(1);
  list.remove(1);
  EXPECT_EQ(list.getSize(), 0);
}

TEST (adtTest, AddTwoElementsAndRemoveBoth) {
  SinglyLinkedList<int> list;
  list.add(1);
  list.add(2);
  list.remove(1);
  list.remove(2);
  EXPECT_EQ(list.getSize(), 0);
}

TEST (adtTest, PrintListOneStringElement) {
  SinglyLinkedList<std::string> list;
  testing::internal::CaptureStdout();
  list.add("Hello");
  list.print();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Hello \n");
}

TEST (adtTest, PrintListTwoStringElements) {
  SinglyLinkedList<std::string> list;
  testing::internal::CaptureStdout();
  list.add("Hello");
  list.add("World");
  list.print();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Hello World \n");
}
