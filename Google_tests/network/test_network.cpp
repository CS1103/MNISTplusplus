#include <gtest/gtest.h>
#include <fstream>
#include "neural_layer.h"
#include "neural_network.h"

TEST(NeuralNetworkTest, AddLayerWithInstanceTest) {
    neural_network nn;
    neural_layer<double> layer(10, 5);
    nn.add_layer(layer);
    EXPECT_EQ(nn.size(), 1);
}

TEST(NeuralNetworkTest, AddLayerWithSizeTest) {
    neural_network nn;
    nn.add_layer(10,5);
    EXPECT_EQ(nn.size(), 1);
}

TEST(NeuralNetworkTest, OperatorBracketTest) {
    neural_network nn;
    nn.add_layer(10,5);
    nn.add_layer(5,2);
    EXPECT_EQ(nn[0].get_input_size(), 10);
    EXPECT_EQ(nn[0].get_output_size(), 5);
    EXPECT_EQ(nn[1].get_input_size(), 5);
    EXPECT_EQ(nn[1].get_output_size(), 2);
}

TEST(NeuralNetworkTest, ForwardTest) {
    neural_network nn;
    nn.add_layer(10,5);
    nn.add_layer(5,2);
    Matrix<double> input(10, 1);
    input.randomValues();
    Matrix<double> output = nn.forward(input);
    EXPECT_EQ(output.get_rows(), 2);
    EXPECT_EQ(output.get_cols(), 1);
}

TEST(NeuralNetworkTest, InitializerListConstructorTest) {
    neural_layer<double> layer1(10, 5);
    neural_layer<double> layer2(5, 2);
    neural_network nn{layer1, layer2};
    EXPECT_EQ(nn.size(), 2);
}

TEST(NeuralNetworkTest, GetLayersTest) {
    neural_network nn;
    nn.add_layer(10,5);
    nn.add_layer(5,2);
    std::vector<neural_layer<double>>& layers = nn.get_layers();
    EXPECT_EQ(layers.size(), 2);
}

TEST(NeuralNetworkTest, SerializerTest){
    neural_network nn;
    nn.add_layer(10,5);
    nn.add_layer(5,2);
    nn.serialize("test.txt");
    EXPECT_EQ(nn[0].get_input_size(), 10);
    EXPECT_EQ(nn[0].get_output_size(), 5);
    EXPECT_EQ(nn[1].get_input_size(), 5);
    EXPECT_EQ(nn[1].get_output_size(), 2);
}

TEST(NeuralNetworkTest, SerializeTest) {
    neural_network nn;
    nn.add_layer(5, 5);
    nn.add_layer(5, 5);
    nn.serialize("./test.txt");
    neural_network nn2;
    nn2.deserialize("./test.txt");

    Matrix<double> input(5, 1);
    input.randomValues(123);
    Matrix<double> input2(5,1);
    input2.randomValues(123);
    auto f1 = nn.forward(input);
    auto f2 = nn2.forward(input2);

    for (int i = 0; i< f1.get_rows(); i++){
        for(int j = 0; j < f1.get_cols(); j++){
            EXPECT_NEAR(f1(i,j), f2(i,j),1e-5);
        }
    }

}