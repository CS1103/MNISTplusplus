#ifndef MNISTPLUSPLUS_CONSTANTS_H
#define MNISTPLUSPLUS_CONSTANTS_H

#include <string>
enum read{MN_LABEL = 2049 , MN_IMG = 2051, TEST_NUM=10000,TRAIN_NUM = 60000};

extern std::string TRAIN_IMAGE_PATH;
extern std::string TRAIN_LABEL_PATH;
extern std::string TEST_IMAGE_PATH;
extern std::string TEST_LABEL_PATH;

extern float random_lower_limit;
extern float random_upper_limit;

#endif //MNISTPLUSPLUS_CONSTANTS_H
