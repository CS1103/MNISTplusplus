#pragma once

#include "matrix.h"

template <typename T>
class ConfusionMatrix {
private:
    Matrix<T> matrix;
public:
    ConfusionMatrix(size_t rows = 10, size_t cols = 10){
        matrix = Matrix<T>(rows, cols);
    }
    double recall(T label){
        double recall = 0;
        for(int i = 0; i < matrix.getRows(); i++){
            recall += matrix(label,i);
        }
        return recall;
    }
    double precision(T label){
        double precision = 0;
        for(int i = 0; i < matrix.getCols(); i++){
            precision += matrix(i,label);
        }
        return precision;
    }

};