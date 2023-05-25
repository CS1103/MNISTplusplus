#ifndef MNISTPLUSPLUS_MATRIX_H
#define MNISTPLUSPLUS_MATRIX_H


#include <iostream>
//#include <utility>
#include <random>
#include <type_traits>
#include "constants.h"
using namespace std;

template <typename T>
class Matrix {
private:
    T** data;
    size_t rows;
    size_t cols;
public:
    // Constructor 1
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for(int j = 0; j < cols; j++){
                data[i][j] = 0;
            }
        }
    }

    Matrix(const std::initializer_list<std::initializer_list<T>>& init) {
        rows = init.size();
        if (rows == 0) {
            throw std::runtime_error("Initializer list is empty.");
        }

        cols = init.begin()->size();
        if (cols == 0) {
            throw std::runtime_error("Initializer list is empty.");
        }

        data = new T*[rows];
        int i = 0;
        for (const auto& row : init) {
            if (row.size() != cols) {
                throw std::runtime_error("Initializer list has inconsistent number of columns.");
            }
            data[i] = new T[cols];
            int j = 0;
            for (const auto& value : row) {
                data[i][j] = value;
                j++;
            }
            i++;
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    Matrix(Matrix&& other) noexcept : data(other.data), rows(other.rows), cols(other.cols) {
        other.data = nullptr;
        other.rows = 0;
        other.cols = 0;
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            Matrix temp(other);
            std::swap(data, temp.data);
            std::swap(rows, temp.rows);
            std::swap(cols, temp.cols);
        }
        return *this;
    }

    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;

            data = other.data;
            rows = other.rows;
            cols = other.cols;

            other.data = nullptr;
            other.rows = 0;
            other.cols = 0;
        }
        return *this;
    }

    // Destructor
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    T& operator()(int row, int col) {
        return data[row][col];
    }

    const T& operator()(int row, int col) const {
        return data[row][col];
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw runtime_error("Matrices must have the same size for += operation.");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = data[i][j] + other(i, j);
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw runtime_error("Matrices must have the same size for -= operation.");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = data[i][j] - other(i, j);
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::runtime_error("Matrices cannot be multiplied. Incompatible sizes.");
        }

        int resultRows = rows;
        int resultCols = other.cols;
        Matrix result(resultRows, resultCols);
        for (int i = 0; i < resultRows; i++) {
            for (int j = 0; j < resultCols; j++) {
                T sum = 0;
                for (int k = 0; k < cols; k++) {
                    sum += data[i][k] * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    Matrix operator*(T scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = data[i][j] * scalar;
            }
        }
        return result;
    }
    Matrix& operator+=(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw std::runtime_error("Matrices must have the same size for += operation.");
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] += other(i, j);
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw std::runtime_error("Matrices must have the same size for -= operation.");
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] -= other(i, j);
            }
        }
        return *this;
    }

    Matrix& operator*=(const T& scalar) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] *= scalar;
            }
        }
        return *this;
    }

    Matrix& operator*=(const Matrix& other) {
        if (cols != other.rows) {
            throw std::runtime_error("Matrices cannot be multiplied. Incompatible sizes.");
        }

        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                T sum = 0;
                for (int k = 0; k < cols; k++) {
                    sum += data[i][k] * other(k, j);
                }
                result(i, j) = sum;
            }
        }

        *this = result;
        return *this;
    }



    Matrix<T> t() const {
        Matrix<T> result(cols, rows);
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                result(i, j) = data[j][i];
            }
        }
        return result;
    }

    std::pair<int,int> shape() const{return {rows, cols};}

    Matrix& randomValues(int seed){

        //pseudo-random number generator using merssene twister algorithm and a specific seed
        std::mt19937 gen(seed);

        if constexpr(std::is_same<T,int>::value){
            //defines an integer number uniform distribution in a specific range
            std::uniform_int_distribution<int> distribution(0, 1);
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    data[i][j] = distribution(gen);
                }
            }
        }else{
            //defines a real number uniform distribution in a specific range
            std::uniform_real_distribution<float> distribution(0.0, 1.0);
            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    data[i][j] = distribution(gen);
                }
            }
        }
        return *this;
    }

    class Proxy {
    private:
        T* rowData;
        int cols;

    public:
        Proxy(T* rowData, int cols) : rowData(rowData), cols(cols) {}

        T& operator[](int col) {
            if (col < 0 || col >= cols) {
                throw std::out_of_range("Column index out of range.");
            }
            return rowData[col];
        }
    };

    Proxy operator[](int row) {
        if (row < 0 || row >= rows) {
            throw std::out_of_range("Row index out of range.");
        }
        return Proxy(data[row], cols);
    }

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &matrix);

    template <typename A, typename B>
    friend bool operator == (const Matrix<A>& m1, const Matrix<B>& m2);

    template <typename A, typename B>
    friend bool operator != (const Matrix<A>& m1, const Matrix<B>& m2);

};

template <typename U>
std::ostream &operator<<(std::ostream &os, const Matrix<U> &matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            os << matrix(i,j) << ' ';
        }
        os << '\n';
    }
    return os;
}

template <typename A, typename B>
bool operator == (const Matrix<A>& m1, const Matrix<B>& m2){
    if constexpr(!std::is_same<A,B>::value) return false;
    if (m1.rows!= m2.rows || m1.cols!=m2.cols) return false;
    for(int i = 0;i<m1.rows;i++){
        for(int j = 0; j<m1.cols ; j++){
            if (m1.data[i][j] != m2.data[i][j]) return false;
        }
    }
    return true;
}

template <typename A, typename B>
bool operator != (const Matrix<A>& m1, const Matrix<B>& m2){
    if constexpr(!std::is_same<A,B>::value) return true;
    if (m1.rows!= m2.rows || m1.cols!=m2.cols) return true;
    for(int i = 0;i<m1.rows;i++){
        for(int j = 0; j<m1.cols ; j++){
            if (m1.data(i,j) != m2.data(i,j)) {
                return true;
            }
        }
    }
    return false;
}


#endif //MNISTPLUSPLUS_MATRIX_H