#include "../include/adt.h"

#include <gtest/gtest.h>

// Test case for libA
TEST(adtTest, Print_adt_message) {
  testing::internal::CaptureStdout();
  print_adt_message();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Hello from ADT!\n");
}
TEST(adtTest, CppCheckIntegrationTest) {
  //char a[10];
  char a[11];
  a[10] = 0;
}


TEST(adtTest, CreateSingleLinkList) {
  Lists::ListAdt<int>* list = Lists::createSingleLinkList<int>();
  EXPECT_EQ(list->isEmpty(), true);
  EXPECT_EQ(list->getSize(), 0);
}

TEST(adtTest, DoublySingleLinkList) {
  Lists::ListAdt<int>* list = Lists::createDoublyLinkedList<int>();
  EXPECT_EQ(list->isEmpty(), true);
  EXPECT_EQ(list->getSize(), 0);
}

TEST(adtTest, CircularLinkList) {
  Lists::ListAdt<int>* list = Lists::createCircularLinkedList<int>();
  EXPECT_EQ(list->isEmpty(), true);
  EXPECT_EQ(list->getSize(), 0);
}
