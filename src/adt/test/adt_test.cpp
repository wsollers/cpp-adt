#include "../include/adt.h"
#include <gtest/gtest.h>

// Test case for libA
TEST(adtTest, Print_adt_message) {
  testing::internal::CaptureStdout();
  print_adt_message();
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Hello from ADT!\n");
}
