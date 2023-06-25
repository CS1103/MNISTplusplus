#pragma once

#include <string>
#include <filesystem>

enum read{MN_LABEL = 2049 , MN_IMG = 2051, TEST_NUM=10000,TRAIN_NUM = 60000};
std::filesystem::path find_project_root();
constexpr const char* TRAIN_IMAGE_PATH {"data/train-images.idx3-ubyte"};
constexpr const char* TRAIN_LABEL_PATH {"data/train-labels.idx1-ubyte"};
constexpr const char* TEST_IMAGE_PATH {"data/t10k-images.idx3-ubyte"};
constexpr const char* TEST_LABEL_PATH {"data/t10k-labels.idx1-ubyte"};

constexpr float RANDOM_LOWER_LIMIT {0.0};
constexpr float RANDOM_UPPER_LIMIT {1.0};

constexpr int RANDOM_SEED {123};

constexpr const char* SERIALIZE_MAGIC_NUMBER {"2054"};
