#ifndef MNISTPLUSPLUS_TEST_MATRIX_HPP
#define MNISTPLUSPLUS_TEST_MATRIX_HPP

#include <iostream>
#include "../../include/matrix.h"

void test_constructor_default() {
    Matrix<int> m(3, 3);
}

void test_constructor_initializer_list() {
    Matrix<int> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    std::cout << m;
}

void test_copy_constructor() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2(m1);
    cout << m2;
}

void test_operator_plus() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    Matrix<int> m3 = m1 + m2;
    cout << m3;
}

void test_operator_minus() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    Matrix<int> m3 = m2 - m1;
    cout << m3;
}

void test_operator_multiply() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    Matrix<int> m3 = m1 * m2;
    cout << m3;
}

void test_operator_scalar_multiply() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2 = m1 * 2;
    cout << m2;
}


void test_operator_plus_equals() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    m1 += m2;
    cout << m1;
}

void test_operator_minus_equals() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    m2 -= m1;
    cout << m2;
}

void test_operator_multiply_equals() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    m1 *= m2;
    cout << m1;
}

void test_matrix_transpose(){
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}});
    m1 = m1.t();
    cout << m1;
}




#endif //MNISTPLUSPLUS_TEST_MATRIX_HPP
