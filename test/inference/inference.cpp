//
// Created by Samanta on 25/06/2023.
//

#include <iostream>
#include <fstream>

#include "neural_network.h"

int main() {
    neural_network nn;
    std::filesystem::path model_full_path = get_absolute_path("models/trained_100_epch.txt");
    nn.deserialize(model_full_path.string());

    Matrix<double> input_matrix(28, 28);
    std::filesystem::path matrix_full_path = get_absolute_path("cmake-build-debug/matrix.bin");

    std::ifstream input_file(matrix_full_path.string(), std::ios::binary);
    input_matrix.deserialize(input_file);

    Matrix<double> output_matrix = nn.inference(input_matrix);

    int max = 0;
    for (int i = 0; i < output_matrix.get_rows(); i++){
        if(output_matrix[i][0] > output_matrix[max][0])
            max = i;
    }
    cout << max << endl;
    return 0;
}
