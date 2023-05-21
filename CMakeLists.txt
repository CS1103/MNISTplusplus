cmake_minimum_required(VERSION 3.25)
project(MNISTplusplus)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(hello_world
        include/constants.h
        include/matrix.h
        include/mnist_loader.h
        include/neural_layer.h
        include/neural_network.h
        src/matrix.cpp
        src/mnist_loader.cpp
        src/neural_layer.cpp
        src/neural_network.cpp
        test/init/hello_world.cpp)

add_executable(mnistReader
        include/constants.h
        include/matrix.h
        include/mnist_loader.h
        include/neural_layer.h
        include/neural_network.h
        src/matrix.cpp
        src/mnist_loader.cpp
        src/neural_layer.cpp
        src/neural_network.cpp
        include/DigitImage.h
        test/MNISTReader/test_reader.cpp
        )

add_subdirectory(Google_tests)
