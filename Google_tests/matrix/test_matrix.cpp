#include <gtest/gtest.h>
#include "test_matrix.hpp"


TEST(MatrixInitializerTest, ConstructorInitializerList){
    testing::internal::CaptureStdout();
    test_constructor_initializer_list();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1 2 3 \n4 5 6 \n7 8 9 \n");
}
TEST(MatrixCopyConstructorTest, CopyConstructor){
    testing::internal::CaptureStdout();
    test_copy_constructor();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1 2 3 \n4 5 6 \n7 8 9 \n");
}
TEST(MatrixOperatorPlusTest, OperatorPlus){
    testing::internal::CaptureStdout();
    test_operator_plus();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 10 10 \n10 10 10 \n10 10 10 \n");
}
TEST(MatrixOperatorMinusTest, OperatorMinus){
    testing::internal::CaptureStdout();
    test_operator_minus();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "8 6 4 \n2 0 -2 \n-4 -6 -8 \n");
}


TEST(MatrixOperatorMultiplyTest, OperatorMultiply){
    testing::internal::CaptureStdout();
    test_operator_multiply();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "30 24 18 \n84 69 54 \n138 114 90 \n");
}

TEST(MatrixOperatorScalarMultiplyTest, OperatorScalarMultiply){
    testing::internal::CaptureStdout();
    test_operator_scalar_multiply();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "2 4 6 \n8 10 12 \n14 16 18 \n");
}

TEST(MatrixOperatorPlusEqualsTest, OperatorPlusEquals){
    testing::internal::CaptureStdout();
    test_operator_plus_equals();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 10 10 \n10 10 10 \n10 10 10 \n");
}

TEST(MatrixOperatorMinusEqualsTest, OperatorMinusEquals){
    testing::internal::CaptureStdout();
    test_operator_minus_equals();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "8 6 4 \n2 0 -2 \n-4 -6 -8 \n");
}

TEST(MatrixOperatorMultiplyEqualsTest, OperatorMultiplyEquals){
    testing::internal::CaptureStdout();
    test_operator_multiply_equals();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "30 24 18 \n84 69 54 \n138 114 90 \n");
}


TEST(MatrixTransposeTest, Transpose){
    testing::internal::CaptureStdout();
    test_matrix_transpose();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1 4 \n2 5 \n3 6 \n");
}
