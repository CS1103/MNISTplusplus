#include <gtest/gtest.h>
#include "matrix.h"

TEST(MatrixConstructorTest, ParameterConstructor){
    Matrix<int> m(3, 3);
    EXPECT_EQ(m(0,0),0);
    EXPECT_EQ(m(1,1),0);
    Matrix<double> m1(3, 3);
    EXPECT_EQ(m1(0,0), 0.0);
    EXPECT_EQ(m1(1,1), 0.0);
}

TEST(MatrixInitializerTest, ConstructorInitializerList){
    Matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    EXPECT_EQ(m(0,0),1);
    EXPECT_EQ(m(1,1),5);
    Matrix<double> m1({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    EXPECT_EQ(m1(0,0), 1.0);
    EXPECT_EQ(m1(1,1), 5.0);
}
TEST(MatrixCopyConstructorTest, CopyConstructor){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2(m1);
    EXPECT_EQ(m2(0,0),1);
    EXPECT_EQ(m2(1,1),5);
    Matrix<double> m3({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    Matrix<double> m4(m3);
    EXPECT_EQ(m4(0,0), 1.0);
    EXPECT_EQ(m4(1,1), 5.0);
}
TEST(MatrixOperatorPlusTest, OperatorPlus){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    Matrix<int> m3 = m1 + m2;
    EXPECT_EQ(m3(0,0),10);
    EXPECT_EQ(m3(1,1),10);
    Matrix<double> m4({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    Matrix<double> m5({{9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0}});
    Matrix<double> m6 = m4 + m5;
    EXPECT_EQ(m6(0,0), 10.0);
    EXPECT_EQ(m6(1,1), 10.0);
}
TEST(MatrixOperatorMinusTest, OperatorMinus){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    Matrix<int> m3 = m2 - m1;
    EXPECT_EQ(m3(0,0),8);
    EXPECT_EQ(m3(1,1),0);
    Matrix<double> m4({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    Matrix<double> m5({{9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0}});
    Matrix<double> m6 = m5 - m4;
    EXPECT_EQ(m6(0,0), 8.0);
    EXPECT_EQ(m6(1,1), 0.0);
}


TEST(MatrixOperatorMultiplyTest, OperatorMultiply){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    Matrix<int> m3 = m1 * m2;
    EXPECT_EQ(m3(0,0),30);
    EXPECT_EQ(m3(1,1),69);
    Matrix<double> m4({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    Matrix<double> m5({{9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0}});
    Matrix<double> m6 = m4 * m5;
    EXPECT_EQ(m6(0,0), 30.0);
    EXPECT_EQ(m6(1,1), 69.0);

}

TEST(MatrixOperatorScalarMultiplyTest, OperatorScalarMultiply){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2 = m1 * 2;
    EXPECT_EQ(m2(0,0),2);
    EXPECT_EQ(m2(1,1),10);
    Matrix<double> m3({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    Matrix<double> m4 = m3 * 2.0;
    EXPECT_EQ(m4(0,0), 2.0);
    EXPECT_EQ(m4(1,1), 10.0);

}

TEST(MatrixOperatorPlusEqualsTest, OperatorPlusEquals){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    m1 += m2;
    EXPECT_EQ(m1(0,0),10);
    EXPECT_EQ(m1(1,1),10);
    Matrix<double> m3({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    Matrix<double> m4({{9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0}});
    m3 += m4;
    EXPECT_EQ(m3(0,0), 10.0);
    EXPECT_EQ(m3(1,1), 10.0);

}

TEST(MatrixOperatorMinusEqualsTest, OperatorMinusEquals){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    m2 -= m1;
    EXPECT_EQ(m2(0,0),8);
    EXPECT_EQ(m2(1,1),0);
    Matrix<double> m3({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    Matrix<double> m4({{9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0}});
    m4 -= m3;
    EXPECT_EQ(m4(0,0), 8.0);
    EXPECT_EQ(m4(1,1), 0.0);

}

TEST(MatrixOperatorMultiplyEqualsTest, OperatorMultiplyEquals){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    m1 *= m2;
    EXPECT_EQ(m1(0,0),30);
    EXPECT_EQ(m1(1,1),69);
    Matrix<double> m3({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    Matrix<double> m4({{9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0}});
    m3 *= m4;
    EXPECT_EQ(m3(0,0), 30.0);
    EXPECT_EQ(m3(1,1), 69.0);

}


TEST(MatrixTransposeTest, Transpose){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}});
    m1 = m1.t();
    EXPECT_EQ(m1(0,0),1);
    EXPECT_EQ(m1(0,1),4);
    EXPECT_EQ(m1(1,0),2);
    EXPECT_EQ(m1(1,1),5);
    EXPECT_EQ(m1(2,0),3);
    EXPECT_EQ(m1(2,1),6);
    EXPECT_EQ(m1.shape(), std::make_pair(3,2));

    Matrix<double> m2({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}});
    m2 = m2.t();
    EXPECT_EQ(m2(0,0),1.0);
    EXPECT_EQ(m2(0,1),4.0);
    EXPECT_EQ(m2(1,0),2.0);
    EXPECT_EQ(m2(1,1),5.0);
    EXPECT_EQ(m2(2,0),3.0);
    EXPECT_EQ(m2(2,1),6.0);
    EXPECT_EQ(m2.shape(), std::make_pair(3,2));

}

TEST(MatrixShapeTest, Shape){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}});
    Matrix<double> m2({{1.0, 2.0, 3.0, 5.0, 6.0}, {4.0, 5.0, 6.0, 7.0, 8.0}});
    Matrix<double> m3(5,1);
    Matrix<double> m4(m2);

    EXPECT_EQ(m1.shape(), std::make_pair(2,3));
    EXPECT_EQ(m2.shape(), std::make_pair(2,5));
    EXPECT_EQ(m3.shape(), std::make_pair(5,1));
    EXPECT_EQ(m4.shape(), std::make_pair(2,5));
}
