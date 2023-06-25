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
        w.randomValues(123);
        dw = Matrix<T>(input_sz,out_sz);

        b= Matrix<T>(out_sz,1);
        b.randomValues(123);
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


    Matrix<double> relu(Matrix<double>& X){
        Matrix<double> result(X.get_rows(), X.get_cols());
        for (int i = 0; i < X.get_rows(); ++i) {
            for (int j = 0; j < X.get_cols(); ++j) {
                result(i,j) = std::max(0.0, X(i,j));
            }
        }
        return result;
    }
    Matrix<double> relu_prime(Matrix<double>& X){
        Matrix<double> result(X.get_rows(), X.get_cols());
        for (auto i = 0; i < X.get_rows(); ++i) {
            for (auto j = 0; j < X.get_cols(); ++j) {
                result(i,j) = (X(i,j) > 0.0) ? 1.0 : 0.0;
            }
        }
        return result;
    }

    Matrix<double> softmax (Matrix<double>& X ){
        Matrix<double> result((int)X.get_rows(), (int)X.get_cols());

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

    std::pair<Matrix<double>,Matrix<double>> forward(Matrix<double>& input, bool is_output = false){
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

        dw += prev_A * dz.t() ;
        db += dz;

        return da;
        //return (prev_W*delta) ^ mtx_sigmoid_derivative(output);
    }

    Matrix<double> backward_softmax(Matrix<double>& delta, Matrix<double>& prev_output){
        Matrix<double> dz = delta ;
        Matrix<double> da = w * dz;

        dw += prev_output* dz.t();
        db += dz;

        return da;
    }

    Matrix<double> loss (Matrix<double>& output, Matrix<double>& target){
        Matrix<double> res((int)output.get_rows(), (int)output.get_cols());

        for(int row = 0; row < output.get_rows(); row++){
            for(int col = 0; col < output.get_cols(); col++ ){
                res(row,col) = -( target(row,col) * log(output(row, col)) + (1 - target(row, col)) * log(1 - output(row, col)) );
            }
        }
        return res;
    }

    void gradient_descent( double learning_rate, int batch_size){
        w -= (dw/batch_size)*learning_rate;
        b -= (db/batch_size);
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