//
// Created by Samanta on 23/06/2023.
//

#include <gtest/gtest.h>
#include "matrix.h"
#include "DataSet.h"

TEST(DataSetGetInstanceTest, GetInstance) {
    DataSet* instance1 = DataSet::GetInstance();
    DataSet* instance2 = DataSet::GetInstance();

    ASSERT_EQ(instance1, instance2);
}

TEST(DataSetTrainingImageTest, TrainingImage) {
    DataSet* dataset = DataSet::GetInstance();
    std::vector<float> pixels = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f};
    dataset->add_training_image(2, 3, 1, pixels);

    ASSERT_EQ(dataset->getTrainingDataSize(), 1);
}

TEST(DataSetTestImageTest, TestImage) {
    DataSet* dataset = DataSet::GetInstance();
    std::vector<float> pixels = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f};
    dataset->add_test_image(2, 3, pixels);

    ASSERT_EQ(dataset->getTestDataSize(), 1);
}

TEST(DataSetClearTrainingDataTest, ClearTrainingData) {
    DataSet* dataset = DataSet::GetInstance();
    dataset->clearTrainingData();

    ASSERT_EQ(dataset->getTrainingDataSize(), 0);
}

TEST(DataSetClearTestDataTest, ClearTestData) {
    DataSet* dataset = DataSet::GetInstance();
    dataset->clearTestData();

    ASSERT_EQ(dataset->getTestDataSize(), 0);
}

TEST(DataSetExtractTrainingBatchTest, ExtractTrainingBatch) {
    DataSet* dataset = DataSet::GetInstance();
    dataset->clearTrainingData();

    std::vector<float> pixels1 = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f};
    dataset->add_training_image(2, 3, 1, pixels1);
    std::vector<float> pixels2 = {0.7f, 0.8f, 0.9f, 0.11f, 0.12f, 0.13f};
    dataset->add_training_image(2, 3, 2, pixels2);
    std::vector<float> pixels3 = {0.14f, 0.15f, 0.16f, 0.17f, 0.18f, 0.19f};
    dataset->add_training_image(2, 3, 3, pixels3);
    std::vector<float> pixels4 = {0.20f, 0.21f, 0.22f, 0.23f, 0.24f, 0.25f};
    dataset->add_training_image(2, 3, 4, pixels4);
    std::vector<float> pixels5 = {0.26f, 0.27f, 0.28f, 0.29f, 0.30f, 0.31f};
    dataset->add_training_image(2, 3, 4, pixels5);

    std::vector<std::vector<std::pair<Matrix<double>, Matrix<double>>>> batches = dataset->extract_training_batch(3);
    ASSERT_EQ(batches.size(), 3);

    ASSERT_EQ(batches[0].size(), 2);
    ASSERT_EQ(batches[1].size(), 2);
    ASSERT_EQ(batches[2].size(), 1);
}

TEST(DataSetExtractTrainingBatch2Test, ExtractTrainingBatch2) {
    DataSet* dataset = DataSet::GetInstance();
    dataset->clearTrainingData();

    std::vector<float> pixels = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f};
    dataset->add_training_image(2, 3, 1, pixels);

    std::vector<std::vector<std::pair<Matrix<double>, Matrix<double>>>> batches = dataset->extract_training_batch(2);
    ASSERT_EQ(batches.size(), 2);

    ASSERT_EQ(batches[0].size(), 1);
    ASSERT_EQ(batches[1].size(), 0);
}

TEST(DataSetExtractTrainingBatch3Test, ExtractTrainingBatch3) {
    DataSet* dataset = DataSet::GetInstance();
    dataset->clearTrainingData();

    std::vector<float> pixels1 = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f};
    dataset->add_training_image(2, 3, 1, pixels1);
    std::vector<float> pixels2 = {0.7f, 0.8f, 0.9f, 0.10f, 0.11f, 0.12f};
    dataset->add_training_image(2, 3, 1, pixels2);

    std::vector<std::vector<std::pair<Matrix<double>, Matrix<double>>>> batches = dataset->extract_training_batch(2);
    ASSERT_EQ(batches.size(), 2);

    ASSERT_EQ(batches[0].size(), 1);
    ASSERT_EQ(batches[1].size(), 1);
}