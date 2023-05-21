#include "../include/matrix.h"

void test_operator_multiply() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    Matrix<int> m3 = m1 * m2;
    if (m3(0,0) != 30 || m3(2,2) != 90) {
        std::cout << "Error en test_operator_multiply\n";
    }
}

void test_operator_scalar_multiply() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2 = m1 * 2;
    if (m2(0,0) != 2 || m2(2,2) != 18) {
        std::cout << "Error en test_operator_scalar_multiply\n";
    }
}


void test_operator_plus_equals() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    m1 += m2;
    if (m1(0,0) != 10 || m1(2,2) != 10) {
        std::cout << "Error en test_operator_plus_equals\n";
    }
}

void test_operator_minus_equals() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    m1 -= m2;
    if (m1(0,0) != -8 || m1(2,2) != 8) {
        std::cout << "Error en test_operator_minus_equals\n";
    }
}

void test_operator_multiply_equals() {
    Matrix<int> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Matrix<int> m2({{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});
    m1 *= m2;
    if (m1(0,0) != 30 || m1(2,2) != 90) {
        std::cout << "Error en test_operator_multiply_equals\n";
    }
}

int main(){
    test_operator_multiply();
    std::cout << "Paso test_operator_multiply\n";

    test_operator_scalar_multiply();
    std::cout << "Paso test_operator_scalar_multiply\n";

    test_operator_plus_equals();
    std::cout << "Paso test_operator_plus_equals\n";

    test_operator_minus_equals();
    std::cout << "Paso test_operator_minus_equals\n";

    test_operator_multiply_equals();
    std::cout << "Paso test_operator_multiply_equals\n";
    return 0;
}