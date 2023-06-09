#include <gtest/gtest.h>
#include "matrix.h"

TEST(MatrixConstructorDefaultTest, DefaultConstructor){
    Matrix<int> m;
    EXPECT_EQ(m.get_rows(),0);
    EXPECT_EQ(m.get_cols(),0);
    Matrix<double> m1;
    EXPECT_EQ(m1.get_rows(), 0);
    EXPECT_EQ(m1.get_cols(), 0);
}

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
    Matrix<int> m3 = 2 * m1;
    EXPECT_EQ(m2(0,0),2);
    EXPECT_EQ(m2(1,1),10);
    EXPECT_EQ(m3(0,0),2);
    EXPECT_EQ(m3(1,1),10);
    Matrix<double> m4({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    Matrix<double> m5 = m4 * 2.0;
    Matrix<double> m6 = 2.0 * m4;
    ASSERT_DOUBLE_EQ(m5(0,0), 2.0);
    ASSERT_DOUBLE_EQ(m5(1,1), 10.0);
    ASSERT_DOUBLE_EQ(m6(0,0), 2.0);
    ASSERT_DOUBLE_EQ(m6(1,1), 10.0);
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

TEST(MatrixFunctionEye, Eye){
    Matrix<int> m1(3,3);
    Matrix<int> m2 = m1.eye();
    EXPECT_EQ(m2(0,0),1);
    EXPECT_EQ(m2(1,1),1);
    EXPECT_EQ(m2(2,2),1);
    EXPECT_EQ(m2(0,1),0);
    EXPECT_EQ(m2(0,2),0);
    EXPECT_EQ(m2(1,0),0);
    EXPECT_EQ(m2(1,2),0);

    Matrix<double> m3(3,3);
    Matrix<double> m4 = m3.eye();
    EXPECT_EQ(m4(0,0),1.0);
    EXPECT_EQ(m4(1,1),1.0);
    EXPECT_EQ(m4(2,2),1.0);
    EXPECT_EQ(m4(0,1),0.0);
    EXPECT_EQ(m4(0,2),0.0);
    EXPECT_EQ(m4(1,0),0.0);
    EXPECT_EQ(m4(1,2),0.0);
}

TEST(MatrixFunctionOnes, Ones){
    Matrix<int> m1(3,3);
    m1.ones();
    EXPECT_EQ(m1(0,0),1);
    EXPECT_EQ(m1(1,1),1);
    EXPECT_EQ(m1(2,2),1);
    EXPECT_EQ(m1(0,1),1);
    EXPECT_EQ(m1(0,2),1);
    EXPECT_EQ(m1(1,0),1);
    EXPECT_EQ(m1(1,2),1);
    EXPECT_EQ(m1.shape(), std::make_pair(3,3));

    Matrix<double> m2(3,3);
    m2.ones();
    EXPECT_EQ(m2(0,0),1.0);
    EXPECT_EQ(m2(1,1),1.0);
    EXPECT_EQ(m2(2,2),1.0);
    EXPECT_EQ(m2(0,1),1.0);
    EXPECT_EQ(m2(0,2),1.0);
    EXPECT_EQ(m2(1,0),1.0);
    EXPECT_EQ(m2(1,2),1.0);
    EXPECT_EQ(m2.shape(), std::make_pair(3,3));
}

TEST(MatrixSliceTest, Slice){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2 = m1.slice(std::pair(0,1),std::pair(0,1));
    EXPECT_EQ(m2(0,0),1);
    EXPECT_EQ(m2(0,1),2);
    EXPECT_EQ(m2(1,0),4);
    EXPECT_EQ(m2(1,1),5);
    EXPECT_EQ(m2.shape(), std::make_pair(2,2));
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

TEST(RandomMatrix ,ReplicableRandomness){
    float seed_123[36] = {
            0.696469188, 0.712955296, 0.286139339, 0.428470939, 0.226851448, 0.690884829,
            0.551314771, 0.719150305, 0.719468951, 0.491118938, 0.423106462, 0.780027747,
            0.98076421, 0.410924375, 0.684829712, 0.579694271, 0.480931908, 0.139950767,
            0.39211753, 0.401017547, 0.343178004, 0.627317011, 0.729049683, 0.32415089,
            0.438572258, 0.244759277, 0.0596778989, 0.694755197, 0.398044258, 0.593902409,
            0.737995386, 0.631792009, 0.182491735, 0.440257192, 0.175451756, 0.0837264881
    };

    int seed_42[36]={
            0, 1, 1, 0, 1, 1,
            1, 1, 0, 0, 0, 0,
            0, 0, 1, 0, 1, 0,
            1, 1, 0, 0, 1, 1,
            1, 1, 0, 0, 0, 1,
            0, 1, 0, 1, 1, 0
    };

    Matrix<float> m1(3,3);
    m1.randomValues(123);

    Matrix<float> m2(3,3);
    m2.randomValues(123);

    Matrix<int> m3(4,3);
    m3.randomValues(42);

    Matrix<int> m4(4,3);
    m4.randomValues(42);

    ASSERT_DOUBLE_EQ(m1(0,0), seed_123[0]);
    ASSERT_DOUBLE_EQ(m1(0,1), seed_123[1]);
    ASSERT_DOUBLE_EQ(m1(0,2), seed_123[2]);
    ASSERT_DOUBLE_EQ(m1(1,0), seed_123[3]);
    ASSERT_DOUBLE_EQ(m1(1,1), seed_123[4]);
    ASSERT_DOUBLE_EQ(m1(1,2), seed_123[5]);
    ASSERT_DOUBLE_EQ(m1(2,0), seed_123[6]);
    ASSERT_DOUBLE_EQ(m1(2,1), seed_123[7]);
    ASSERT_DOUBLE_EQ(m1(2,2), seed_123[8]);
    EXPECT_EQ(m1, m2);

    ASSERT_DOUBLE_EQ(m3(0,0), seed_42[0]);
    ASSERT_DOUBLE_EQ(m3(0,1), seed_42[1]);
    ASSERT_DOUBLE_EQ(m3(0,2), seed_42[2]);
    ASSERT_DOUBLE_EQ(m3(1,0), seed_42[3]);
    ASSERT_DOUBLE_EQ(m3(1,1), seed_42[4]);
    ASSERT_DOUBLE_EQ(m3(1,2), seed_42[5]);
    ASSERT_DOUBLE_EQ(m3(2,0), seed_42[6]);
    ASSERT_DOUBLE_EQ(m3(2,1), seed_42[7]);
    ASSERT_DOUBLE_EQ(m3(2,2), seed_42[8]);
    EXPECT_EQ(m3, m4);

}

