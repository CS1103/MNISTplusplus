#ifndef MNISTPLUSPLUS_NEURAL_LAYER_H
#define MNISTPLUSPLUS_NEURAL_LAYER_H

#include <vector>
#include <cmath>
#include <algorithm>
#include "matrix.h"
#include "constants.h"

template<typename T>
class neural_layer {
private:
    size_t input_size = 0;
    size_t output_size = 0;

    Matrix<T> w;
    Matrix<T> b;

    Matrix<T> dw;
    Matrix<T> db;
public:

    //Constructors
    neural_layer(size_t input_sz, size_t out_sz): input_size(input_sz), output_size(out_sz){
        w = Matrix<T>(input_sz,out_sz);
        w.randomValues(0);
        dw = Matrix<T>(input_sz,out_sz);

        b= Matrix<T>(out_sz,1);
        b.randomValues(0);
        db = Matrix<T>(out_sz,1);

    }
    neural_layer(size_t input_sz, size_t out_sz, Matrix<T>& w, Matrix<T>& b)
    : input_size(input_sz), output_size(out_sz), w(std::move(w)), b(std::move(b)){
        dw = Matrix<T>(input_sz,out_sz);
        db = Matrix<T>(out_sz,1);
    }

    neural_layer(const neural_layer& other)
            : input_size(other.input_size), output_size(other.output_size), w(other.w), b(other.b){
        dw = Matrix<T>(input_size, output_size);
        db = Matrix<T>(output_size, 1);
    }

    // Constructor de movimiento
    neural_layer(neural_layer&& other) noexcept
            : input_size(other.input_size), output_size(other.output_size), w(std::move(other.w)), b(std::move(other.b))
    {
        dw = Matrix<T>(input_size, output_size);
        db = Matrix<T>(output_size, 1);

        other.input_size = 0;
        other.output_size = 0;
    }

    ~neural_layer() =default;

    // Forward propagation functions


    Matrix<T> relu(const Matrix<T>& X){
        Matrix<T> result(X.get_rows(), X.get_cols());
        for (int i = 0; i < X.get_rows(); ++i) {
            for (int j = 0; j < X.get_cols(); ++j) {
                result(i,j) = std::max(0.0, (double)X(i,j));
            }
        }
        return result;
    }
    Matrix<T> relu_prime(Matrix<T>& X){
        Matrix<T> result(X.get_rows(), X.get_cols());
        for (auto i = 0; i < X.get_rows(); ++i) {
            for (auto j = 0; j < X.get_cols(); ++j) {
                result(i,j) = (X(i,j) > 0.0) ? 1.0 : 0.0;
            }
        }
        return result;
    }

    Matrix<T> softmax (const Matrix<T>& X ){
        Matrix<T> result((int)X.get_rows(), (int)X.get_cols());

        double sum = 0.0;
        for (auto i = 0; i < X.get_rows(); ++i) {
            for (auto j = 0; j < X.get_cols(); ++j) {
                sum += exp(X(i,j));
            }
        }

        for (auto i = 0; i < X.get_rows(); ++i) {
            for (auto j = 0; j < X.get_cols(); ++j) {
                result(i,j) = exp(X(i,j)) / sum;
            }
        }
        return result;
    }

    std::pair<Matrix<T>,Matrix<T>> forward(const Matrix<T>& input, bool is_output = false){
        auto Z = w.t()*input + b;
        if (is_output){
            return {Z, softmax(Z)};
        }
        return {Z, relu(Z)};
    }

    // Backward propagation functions

    Matrix<double> backward_relu(Matrix<T>& delta, const Matrix<T>& prev_A, Matrix<T>& prev_Z){

        Matrix<double> dz = delta ^ relu_prime(prev_Z);
        Matrix<double> da = w * dz;

        dw+= prev_A * dz.t() ;
        db+= dz;

        return da;
        //return (prev_W*delta) ^ mtx_sigmoid_derivative(output);
    }

    Matrix<double> backward_softmax(Matrix<double>& delta, Matrix<double>& prev_output){
        Matrix<double> dz = delta ;
        Matrix<double> da = w * dz;

        dw+= prev_output* dz.t();
        db+= dz;

        return da;
    }

    void gradient_descent( double learning_rate, int batch_size){
        dw = (dw/batch_size);
        db = (db/batch_size);
        w-= dw*learning_rate;
        b-= db*learning_rate;
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

    const Matrix<T>& get_dw()  {
        return dw;
    }
    const Matrix<T>& get_db(){
        return db;
    }

};


#endif //MNISTPLUSPLUS_NEURAL_LAYER_H