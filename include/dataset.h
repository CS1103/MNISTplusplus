#pragma once

#include "constants.h"
#include "mnist_loader.h"
#include "matrix.h"
#include <algorithm>
#include <mutex>
#include <random>
#include <utility>
#include <vector>

class Dataset {
private:
    static Dataset *instance;
    static std::mutex mutex_;
protected:
    vector<DigitImage> train_data;
    vector<DigitImage> test_data;
    Dataset() {
        MNISTReader mnist_data;
        mnist_data.load_train_dataset();
        mnist_data.load_test_dataset();
        train_data = mnist_data.get_training_data();
        test_data = mnist_data.get_test_data();
    }
    ~Dataset() {}
public:
    Dataset(Dataset &other) = delete;
    void operator=(const Dataset &) = delete;
    
    std::vector<DigitImage> extract_training_batch(size_t batch_size, int seed = RANDOM_SEED) {
        std::vector<DigitImage> batch;

        std::mt19937 gen(seed == -1 ? std::random_device{}() : seed);
        std::uniform_int_distribution<size_t> dist(0, train_data.size() - 1);

        for (size_t i = 0; i < batch_size; i++) {
            batch.push_back(train_data[dist(gen)]);
        }

        return batch;
    }

    std::vector<DigitImage> get_training_data() {
        return train_data;
    }

    std::vector<DigitImage> get_test_data() {
        return test_data;
    }

    static Dataset *GetInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance == nullptr) {
            instance = new Dataset();
        }
        return instance;
    }
};

Dataset *Dataset::instance{nullptr};
std::mutex Dataset::mutex_;

