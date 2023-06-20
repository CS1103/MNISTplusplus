#ifndef MNISTPLUSPLUS_CONSTANTS_H
#define MNISTPLUSPLUS_CONSTANTS_H

#include <string>
enum read{MN_LABEL = 2049 , MN_IMG = 2051, TEST_NUM=10000,TRAIN_NUM = 60000};

extern std::string TRAIN_IMAGE_PATH;
extern std::string TRAIN_LABEL_PATH;
extern std::string TEST_IMAGE_PATH;
extern std::string TEST_LABEL_PATH;

constexpr float RANDOM_LOWER_LIMIT {0.0};
constexpr float RANDOM_UPPER_LIMIT {1.0};

constexpr int RANDOM_SEED {123};

constexpr const char* SERIALIZE_MAGIC_NUMBER {"2054"};

#endif //MNISTPLUSPLUS_CONSTANTS_H
