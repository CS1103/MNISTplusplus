#pragma once

#include "constants.h"
#include "mnist_loader.h"
#include "matrix.h"
#include <algorithm>
#include <mutex>
#include <random>
#include <utility>
#include <vector>
#include <unordered_set>

class Dataset {
private:
    static Dataset *instance;
    static std::mutex mutex_;
protected:
    vector<DigitImage> train_data;
    vector<DigitImage> test_data;
    std::vector<size_t> unique_indices;
    Dataset() {
        MNISTReader mnist_data;
        mnist_data.load_train_dataset();
        mnist_data.load_test_dataset();
        train_data = mnist_data.get_training_data();
        training_data_size = train_data.size();
        test_data = mnist_data.get_test_data();
        test_data_size = test_data.size();

        unique_indices.resize(train_data.size());
        std::iota(unique_indices.begin(), unique_indices.end(), 0);
    }
    ~Dataset() {}
public:
    size_t training_data_size;
    size_t test_data_size;

    Dataset(Dataset &other) = delete;
    void operator=(const Dataset &) = delete;
    
    std::vector<DigitImage> extract_training_batch(size_t batch_size, int seed = RANDOM_SEED) {
        std::vector<DigitImage> batch;
        std::mt19937 gen(seed == -1 ? std::random_device{}() : seed);

        while (batch.size() < batch_size) {
            std::uniform_int_distribution<size_t> dist(0, unique_indices.size() - 1);

            size_t random_index = dist(gen);

            size_t selected_index = unique_indices[random_index];
            batch.push_back(train_data[selected_index]);

            unique_indices.erase(unique_indices.begin() + random_index);
            if (unique_indices.empty()) {
                unique_indices.resize(train_data.size());
                std::iota(unique_indices.begin(), unique_indices.end(), 0);
            }
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

