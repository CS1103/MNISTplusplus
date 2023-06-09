#ifndef MNISTPLUSPLUS_NEURAL_NETWORK_H
#define MNISTPLUSPLUS_NEURAL_NETWORK_H

#include "neural_layer.h"
#include <vector>
#include <initializer_list>

class neural_network {
private:
    std::vector<neural_layer<double>> layers;

public:
    neural_network() = default;

    neural_network(std::initializer_list<neural_layer<double>> list) : layers(list) {}

    void add_layer(neural_layer<double>& layer) {
        layers.push_back(layer);
    }

    void add_layer(size_t n, size_t m) {
        layers.emplace_back(n, m);
    }

    Matrix<double> forward(Matrix<double>& input) {
        Matrix<double> activation = input;
        for (auto& layer : layers) {
            activation = layer.forward(activation);
        }
        return activation;
    }



    std::vector<neural_layer<double>>& get_layers() {
        return layers;
    }

    neural_layer<double>& operator[](size_t pos) {
        return layers[pos];
    }

    size_t size() {
        return layers.size();
    }
};



#endif //MNISTPLUSPLUS_NEURAL_NETWORK_H
