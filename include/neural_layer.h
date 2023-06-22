#ifndef MNISTPLUSPLUS_NEURAL_LAYER_H
#define MNISTPLUSPLUS_NEURAL_LAYER_H

#include <vector>
#include <cmath>
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
        w = Matrix<T>(out_sz,input_sz);
        w.randomValues(123);
        dw = Matrix<T>(out_sz,input_sz);

        b= Matrix<T>(out_sz,1);
        b.randomValues(123);
        db = Matrix<T>(out_sz,1);

    }
    neural_layer(size_t input_sz, size_t out_sz, Matrix<T>& w, Matrix<T>& b): input_size(input_sz), output_size(out_sz), w(std::move(w)), b(std::move(b)){

    }

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

    ~neural_layer() =default;

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

    Matrix<T> mtx_sigmoid_derivative(Matrix<T>& x){
        Matrix<T> result(x.get_rows(), x.get_cols());
        for (size_t i = 0; i < x.get_rows(); ++i) {
            for (size_t j = 0; j < x.get_cols(); ++j) {
                result(i,j) = sigmoid_derivative(x(i,j));
            }
        }
        return result;
    }

    Matrix<double> loss (Matrix<double>& output, Matrix<double>& target){
        Matrix<double> res((int)output.get_rows(), (int)output.get_rows());

        for(int row = 0; row < output.get_rows(); row++){
            for(int col = 0; col < output.get_cols(); col++ ){
                res(row,col) = -( target(row,col) * log(output(row, col)) + (1 - target(row, col)) * log(1 - output(row, col)) );
            }
        }
        return res;
    }

    T loss_derivative(T target, T prediction){
        return -(target / prediction - (1.0 - target) / (1.0 - prediction));
    }

    Matrix<T> mtx_loss_derivative(Matrix<T> ground_truth, Matrix<T> prediction){
        if(ground_truth.get_rows() != prediction.get_rows() || ground_truth.get_cols() != prediction.get_cols())
            throw std::invalid_argument("Matrix dimensions must match");

        Matrix<T> result(ground_truth.get_rows(), ground_truth.get_cols());
        for (size_t i = 0; i < ground_truth.get_rows(); ++i) {
            for (size_t j = 0; j < ground_truth.get_cols(); ++j) {
                result(i,j) = loss_derivative(ground_truth(i,j), prediction(i,j));
            }
        }

        return result;
    }

    Matrix<T> backward(Matrix<T> input, Matrix<T> target, double alpha){
        Matrix<T> da = mtx_loss_derivative(target, input);
        Matrix<T> dz = target - input; // Debe de ser element wise
        dw = dz * input.t();
        db = dz;

        w -= alpha* dw;
        b -= alpha* db;
        return w.t() * dz;
    }


/*
    Matrix<T> backward(Matrix<T>& input, Matrix<T>& output, Matrix<T>& output_error, T learning_rate){
        Matrix<T> input_error = (w.transpose() * output_error);
        Matrix<T> d_output = mtx_sigmoid_derivative(output);
        Matrix<T> d_output_error = output_error * d_output;
        Matrix<T> d_input = input.transpose() * d_output_error;

        w -= d_input * learning_rate;
        b -= d_output_error * learning_rate;

        return input_error;
    }
*/
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