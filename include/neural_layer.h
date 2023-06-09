#ifndef MNISTPLUSPLUS_NEURAL_LAYER_H
#define MNISTPLUSPLUS_NEURAL_LAYER_H

#include <vector>
#include "matrix.h"
#include "constants.h"

template<typename T>
class neural_layer {
private:
    size_t _n = 0;
    size_t _m = 0;

    Matrix<T> w;
    Matrix<T> b;


public:

    //Constructors
    neural_layer(size_t n, size_t m): _n(n), _m(m){
        w = Matrix<T>(m,n);
        w.randomValues(123);

        b= Matrix<T>(m,1);
        b.randomValues(123);
    }

    neural_layer(const neural_layer& other)
            : _n(other._n), _m(other._m), w(other.w), b(other.b)
    {
    }

    // Constructor de movimiento
    neural_layer(neural_layer&& other) noexcept
            : _n(other._n), _m(other._m), w(std::move(other.w)), b(std::move(other.b))
    {
        other._n = 0;
        other._m = 0;
    }

    virtual ~neural_layer() =default;

    // Forward propagation functions

    T sigmoid(T x){
        return 1.0/(1.0+exp(-x));
    }

    Matrix<T> mtx_sigmoid(Matrix<T> x){
        Matrix<T> result(x.get_rows(), x.get_cols());
        for (size_t i = 0; i < x.get_rows(); ++i) {
            for (size_t j = 0; j < x.get_cols(); ++j) {
                result(i,j) = sigmoid(x(i,j));
            }
        }
        return result;
    }

    Matrix<T> forward(Matrix<T> input){
        return mtx_sigmoid((w * input )+ b);
    }

    // Backward propagation functions
    T sigmoid_derivative(T& x ){
        return x *(1.0 - x);
    }

    T mtx_sigmoid_derivative(Matrix<T>& x){
        Matrix<T> result(x.get_rows(), x.get_cols());
        for (size_t i = 0; i < x.get_rows(); ++i) {
            for (size_t j = 0; j < x.get_cols(); ++j) {
                result(i,j) = sigmoid_derivative(x(i,j));
            }
        }
        return result;
    }

    size_t get_input_size() const {
        return _n;
    }

    size_t get_output_size() const {
        return _m;
    }

};


#endif //MNISTPLUSPLUS_NEURAL_LAYER_H
