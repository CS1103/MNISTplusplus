#include <iostream>
#include <fstream>

#include "neural_network.h"
#include "utils.h"

int main() {
    neural_network nn;
    std::filesystem::path model_full_path = get_absolute_path("models/trained_100_epch.txt");
    nn.deserialize(model_full_path.string());

    Matrix<double> input_matrix(28, 28);
    std::filesystem::path matrix_full_path = get_absolute_path("cmake-build-debug/matrix.bin");

    std::ifstream input_file(matrix_full_path.string(), std::ios::binary);
    input_matrix.deserialize(input_file);

    Matrix<double> output_matrix = nn.inference(input_matrix);

    pair<int, int> output = argmax(output_matrix);
    cout << output.first << endl;
    return 0;
}
