//
// Created by Samanta on 25/06/2023.
//

#include <iostream>
#include <fstream>
#include "../../include/constants.h"

#include "../../include/neural_network.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw std::invalid_argument("Invalid argument: no argument was provided");
    }
    neural_network nn;
    std::filesystem::path model_path = get_absolute_path("model.json");
//    nn.loadModel("model.json");

    std::filesystem::path input_path = get_absolute_path(argv[1]);
    Matrix<double> input_matrix(28, 28);
    std::ifstream input_file(input_path, std::ios::binary);
    input_matrix.deserialize(input_file);

//    Matrix<double> output_matrix = nn.inference(input_matrix);

    std::filesystem::path fileName = input_path.filename();
    std::filesystem::path outputPath = "/outputs/" / fileName;

    std::ofstream output_file(outputPath, std::ios::binary);
//    output_matrix.serialize(output_file);
    std::cout << "1";
    return 0;
}