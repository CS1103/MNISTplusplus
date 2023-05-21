#include <gtest/gtest.h>

#include <iostream>
void printHello() {
    std::cout << "Hello, World!\n";
}
TEST(HelloWorldTest, PrintHello) {
// Arrange

// Act
// Redirect the output stream to capture the output
testing::internal::CaptureStdout();
    printHello();  // Assuming the function is defined in your hello_world.cpp file

// Assert
// Get the captured output and compare with the expected output
std::string output = testing::internal::GetCapturedStdout();
EXPECT_EQ(output, "Hello, World!\n");
}
