#include <gtest/gtest.h>
#include "matrix.h"
#include "dataset.h"

TEST(DatasetGetInstanceTest, GetInstance) {
    Dataset* instance1 = Dataset::GetInstance();
    Dataset* instance2 = Dataset::GetInstance();

    ASSERT_EQ(instance1, instance2);
}

TEST(DatasetTest, ExtractTrainingBatchTest) {
    Dataset* dataset = Dataset::GetInstance();

    size_t batchSize = 10;
    std::vector<DigitImage> batch = dataset->extract_training_batch(batchSize);

    ASSERT_EQ(batch.size(), batchSize);
}

TEST(DatasetTest, GetTrainingDataTest) {
    Dataset* dataset = Dataset::GetInstance();

    std::vector<DigitImage> trainingData = dataset->get_training_data();

    ASSERT_FALSE(trainingData.empty());
}

TEST(DatasetTest, GetTestDataTest) {
    Dataset* dataset = Dataset::GetInstance();

    std::vector<DigitImage> testData = dataset->get_test_data();

    ASSERT_FALSE(testData.empty());
}