cmake_minimum_required(VERSION 3.20)
project(MNISTplusplus)

set(CMAKE_CXX_STANDARD 20)
if(APPLE OR UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

include_directories(include)

add_subdirectory(Google_tests)

add_executable(mnistReader
        include/constants.h
        include/matrix.h
        include/mnist_loader.h
        include/neural_layer.h
        include/neural_network.h
        include/digit_image.h
        include/utils.h
        src/matrix.cpp
        src/mnist_loader.cpp
        src/neural_layer.cpp
        src/neural_network.cpp
        src/digit_image.cpp
        src/constants.cpp
        apps/MNISTReader/test_reader.cpp
        src/constants.cpp
        src/dataset.cpp
        src/utils.cpp)

add_executable(Trainer
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
        apps/Trainer/train.cpp
        src/utils.cpp)

add_executable(inference
        apps/inference/inference.cpp
        include/neural_network.h
        src/neural_network.cpp
        include/constants.h
        src/constants.cpp
        include/utils.h
        src/utils.cpp)

