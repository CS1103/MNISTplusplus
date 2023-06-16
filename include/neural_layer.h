#ifndef MNISTPLUSPLUS_NEURAL_LAYER_H
#define MNISTPLUSPLUS_NEURAL_LAYER_H

#include <vector>
#include "matrix.h"
#include "constants.h"

template<typename T>
class neural_layer {
private:
    size_t input_size = 0;
    size_t output_size = 0;

    Matrix<T> w;
    Matrix<T> b;


public:

    //Constructors
    neural_layer(size_t n, size_t m): input_size(n), output_size(m){
        w = Matrix<T>(m,n);
        w.randomValues(123);

        b= Matrix<T>(m,1);
        b.randomValues(123);
    }
    neural_layer(size_t n, size_t m, Matrix<T>& w, Matrix<T>& b): input_size(n), output_size(m), w(std::move(w)), b(std::move(b)){}

    neural_layer(const neural_layer& other)
            : input_size(other.input_size), output_size(other.output_size), w(other.w), b(other.b)
    {
    }

    // Constructor de movimiento
    neural_layer(neural_layer&& other) noexcept
            : input_size(other.input_size), output_size(other.output_size), w(std::move(other.w)), b(std::move(other.b))
    {
        other.input_size = 0;
        other.output_size = 0;
    }

    virtual ~neural_layer() =default;

    // Forward propagation functions

    T sigmoid(T& x){
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
        return input_size;
    }

    size_t get_output_size() const {
        return output_size;
    }

    const Matrix<T>& get_w()  {
        return w;
    }
    const Matrix<T>& get_b(){
        return b;
    }

};


#endif //MNISTPLUSPLUS_NEURAL_LAYER_H