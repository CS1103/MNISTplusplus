#include "../../include/mnist_loader.h"
#include <iostream>
#include <time.h>

int main() {
    srand(time(0));

    MNISTReader dataset;
    dataset.loadTrainDataset("../data/train-images.idx3-ubyte","../Data/train-labels.idx1-ubyte" );
    dataset.loadTestDataset("../data/t10k-images.idx3-ubyte","../Data/t10k-labels.idx1-ubyte" );

    auto trainImages = dataset.getTrainImg();
    auto testImages = dataset.getTestImg();

    std::cout << "\nLoad train images test\n";
    for(int i = 0; i<10 ; ++i){
        int idx = rand()%read::train_num +1;
        std::cout << trainImages[idx];
    }

    std::cout << "\nLoad test images test\n";
    for(int i = 0; i<10 ; ++i){
        int idx = rand()%read::test_num+1;
        std::cout << testImages[idx];
    }
    return 0;
}