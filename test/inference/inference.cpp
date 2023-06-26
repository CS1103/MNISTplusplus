//
// Created by Samanta on 25/06/2023.
//

#include <iostream>
#include <fstream>

#include "neural_network.h"

int main() {
    neural_network nn;
    nn.deserialize("../models/trained_100_epch.txt");

    Matrix<double> input_matrix(28, 28);
    std::ifstream input_file("matrix.bin", std::ios::binary);
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
