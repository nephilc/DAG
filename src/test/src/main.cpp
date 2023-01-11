#include<iostream>
/*
int main(int argc, char** argv)
{
	std::cout<<"hello world"<<std::endl;
	return 0;
}
*/
#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
//with these equality assertions one can test any function that returns a value
//tests that are dependent on data on disk.
TEST(HelloTest, MoreAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
//mock functions and actions