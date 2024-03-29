#include <gtest/gtest.h>
#include "neural_layer.h"

TEST(test_layer, test_forward){
    Matrix<int> input(28*28,1 );
    input.randomValues(123);

    neural_layer<int> layer(input.get_rows(), 10 );
    std::pair<Matrix<int>,Matrix<int>> output = layer.forward(input);

    Matrix<float> input_float (50,1);
    input_float.randomValues(123);

    neural_layer<float> layer_float(input_float.get_rows(), 21 );
    std::pair<Matrix<float>, Matrix<float>> output_float = layer_float.forward(input_float);

    ASSERT_EQ(output.second.get_rows(), 10);
    ASSERT_EQ(output.second.get_cols(), 1);
    ASSERT_EQ(output_float.second.get_rows(), 21);
    ASSERT_EQ(output_float.second.get_cols(), 1);


}