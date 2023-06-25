#include <gtest/gtest.h>
#include "mnist_loader.h"
#include "constants.h"

TEST(MNISTReaderTest, LoadTrainDatasetTest) {
    MNISTReader reader;
    reader.load_train_dataset();

    const auto& trainImages = reader.get_training_data();
    ASSERT_EQ(60000, trainImages.size());
}

TEST(MNISTReaderTest, LoadTestDatasetTest) {
    MNISTReader reader;
    reader.load_test_dataset();

    const auto& testData = reader.get_test_data();
    ASSERT_EQ(10000, testData.size());
}

