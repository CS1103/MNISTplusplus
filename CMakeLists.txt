cmake_minimum_required(VERSION 3.20)
project(MNISTplusplus)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_EXE_LINKER_FLAGS "-static")

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
        src/constants.cpp
        test/init/hello_world.cpp
        include/dataset.h src/utils.cpp include/utils.h)

add_executable(mnistReader
        include/constants.h
        include/matrix.h
        include/mnist_loader.h
        include/neural_layer.h
        include/neural_network.h
        include/digit_image.h
        src/matrix.cpp
        src/mnist_loader.cpp
        src/neural_layer.cpp
        src/neural_network.cpp
        src/digit_image.cpp
        src/constants.cpp
        test/MNISTReader/test_reader.cpp
        src/constants.cpp
        src/dataset.cpp)

add_executable(TrainTest
        include/constants.h
        include/matrix.h
        include/mnist_loader.h
        include/neural_layer.h
        include/neural_network.h
        include/utils.h
        src/matrix.cpp
        src/mnist_loader.cpp
        src/neural_layer.cpp
        src/neural_network.cpp
        src/constants.cpp
        test/TrainTest/train.cpp
        src/utils.cpp include/confution_matrix.h)

add_executable(inference
        test/inference/inference.cpp
        include/neural_network.h
        src/neural_network.cpp
        include/constants.h
        src/constants.cpp
        include/utils.h
        src/utils.cpp)

add_subdirectory(Google_tests)