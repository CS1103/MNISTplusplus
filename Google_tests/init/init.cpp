#include <gtest/gtest.h>

#include <iostream>
void printHello() {
    std::cout << "Hello, World!\n";
}
TEST(HelloWorldTest, PrintHello) {
    testing::internal::CaptureStdout();
    printHello();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Hello, World!\n");
}
