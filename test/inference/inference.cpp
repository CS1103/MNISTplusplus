//
// Created by Samanta on 25/06/2023.
//

#include <iostream>
#include <fstream>

#include "constants.h"
#include "neural_network.h"

int main() {

    neural_network nn;
//    std::filesystem::path model_path = get_absolute_path("model.json");
//    nn.loadModel("model.json");

    std::filesystem::path input_path = get_absolute_path("matrix.bin");
    Matrix<double> input_matrix(28, 28);
    std::ifstream input_file(input_path, std::ios::binary);

    input_matrix.deserialize(input_file);

//    Matrix<double> output_matrix = nn.inference(input_matrix);
    Matrix<double> output_matrix(10, 1);
    output_matrix[5][0] = 1;

    for (int i = 0; i < output_matrix.get_rows(); i++) {
        if (output_matrix(i, 0) == 1) {
            std::cout << i;
            break;
        }
    }

    return 0;
}