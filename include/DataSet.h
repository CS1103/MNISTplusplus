//
// Created by Samanta on 23/06/2023.
//

#ifndef MNISTPLUSPLUS_DATASET_H
#define MNISTPLUSPLUS_DATASET_H

#include "constants.h"
#include "matrix.h"
#include <algorithm>
#include <mutex>
#include <random>
#include <utility>
#include <vector>

class DataSet {
private:
    static DataSet *instance;
    static std::mutex mutex_;
protected:
    DataSet() {}
    ~DataSet() {}
    std::vector<std::pair<Matrix<double>, Matrix<double>>> TrainingData;
    std::vector<std::pair<Matrix<double>, Matrix<double>>> TestData;
public:
    DataSet(DataSet &other) = delete;
    void operator=(const DataSet &) = delete;

    void add_training_image(int _w, int _h, unsigned int _l, std::vector<float> pixels) {
        Matrix<double> imagen(_h, _w, std::move(pixels));
        Matrix<double> label(1, 10);
        label[0][_l] = 1;
        TrainingData.emplace_back(imagen, label);
    }

    void add_test_image(int _w, int _h, std::vector<float> pixels) {
        Matrix<double> imagen(_h, _w, std::move(pixels));
        Matrix<double> label(1, 10);
        TestData.emplace_back(imagen, label);
    }

    std::vector<std::vector<std::pair<Matrix<double>, Matrix<double>>>>
    extract_training_batch(size_t cant_batches, int seed = RANDOM_SEED) {
        std::vector<std::vector<std::pair<Matrix<double>, Matrix<double>>>> batches(cant_batches);

        std::vector<std::pair<Matrix<double>, Matrix<double>>> temporal(
                TrainingData.begin(), TrainingData.end());

        std::mt19937 gen(seed == -1 ? std::random_device{}() : seed);
        std::shuffle(temporal.begin(), temporal.end(), gen);

        size_t dataSize = temporal.size();
        size_t batchSize = dataSize / cant_batches;
        size_t remainingSize = dataSize % cant_batches;

        size_t startIdx = 0;
        for (size_t i = 0; i < cant_batches; i++) {
            size_t currentBatchSize = batchSize;
            if (remainingSize > 0) {
                currentBatchSize++;
                remainingSize--;
            }

            for (size_t j = 0; j < currentBatchSize; j++) {
                batches[i].emplace_back(temporal[startIdx]);
                startIdx++;
            }
        }

        return batches;
    }

    size_t getTrainingDataSize() {
        return TrainingData.size();
    }

    size_t getTestDataSize() {
        return TestData.size();
    }

    void clearTrainingData() {
        TrainingData.clear();
    }

    void clearTestData() {
        TestData.clear();
    }

    static DataSet *GetInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance == nullptr) {
            instance = new DataSet();
        }
        return instance;
    }
};

DataSet *DataSet::instance{nullptr};
std::mutex DataSet::mutex_;

#endif //MNISTPLUSPLUS_DATASET_H
