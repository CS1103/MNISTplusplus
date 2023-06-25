#include "utils.h"
using namespace std;

std::pair<int, int> argmax(Matrix<double> mat) {
    pair<int, int> result;
    double max = mat[0][0];
    for (int i = 0; i < mat.get_rows(); i++)
        for (int j = 0; j < mat.get_cols(); j++)
            if (mat[i][j] > max) {
                max = mat[i][j];
                result.first = i;
                result.second = j;
            }
    return result;
}