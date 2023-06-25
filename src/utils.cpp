#include "utils.h"

double reduce_mean(Matrix<double> mat){
    double mean = 0;
    for(int i = 0; i < mat.get_rows(); i++)
        for (int j = 0; j < mat.get_cols(); j++)
            mean += mat[i][j];
    return mean/((double) mat.get_rows() * (double) mat.get_cols());
}