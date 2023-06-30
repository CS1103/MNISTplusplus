#include "../../include/mnist_loader.h"
#include "constants.h"
#include "utils.h"
#include <iostream>
#include <time.h>

int main() {
    srand(time(NULL));
    MNISTReader dataset;
    dataset.load_train_dataset(TRAIN_IMAGE_PATH, TRAIN_LABEL_PATH);
    dataset.load_test_dataset(TEST_IMAGE_PATH,TEST_LABEL_PATH);

    auto trainImages = dataset.get_training_data();
    auto testImages = dataset.get_test_data();

    std::cout << "\nLoad train images test\n";
    for(int i = 0; i<10 ; ++i){
        int idx = rand()%read::TRAIN_NUM + 1;
        std::cout << trainImages[idx];
    }

    std::cout << "\nLoad test images test\n";
    for(int i = 0; i<10 ; ++i){
        int idx = rand()%read::TEST_NUM + 1;
        std::cout << testImages[idx];
    }
    return 0;
}