#include <gtest/gtest.h>
#include "digit_image.h"

TEST(DigitImageTest, ConstructorTest) {
    Matrix<double> imgData(28, 28);
    int label = 5;

    DigitImage image(imgData, label);

    ASSERT_EQ(10, image.get_label().get_rows());
    ASSERT_EQ(1, image.get_label().get_cols());
    ASSERT_EQ(28, image.get_width());
    ASSERT_EQ(28, image.get_height());
}

TEST(DigitImageTest, CopyConstructorTest) {
    Matrix<double> imgData(24, 24);
    int label = 9;

    DigitImage original(imgData, label);
    DigitImage copy(original);

    ASSERT_EQ(original.get_width(), copy.get_width());
    ASSERT_EQ(original.get_height(), copy.get_height());
    ASSERT_EQ(original.get_label(), copy.get_label());
    ASSERT_EQ(original.get_image(), copy.get_image());
}

TEST(DigitImageTest, SettersTest) {
    Matrix<double> imgData(32, 32);
    Matrix<double> label(10, 1);

    DigitImage image;
    image.set_image(imgData);
    image.set_label(label);

    ASSERT_EQ(32, image.get_width());
    ASSERT_EQ(32, image.get_height());
    ASSERT_EQ(10, image.get_label().get_rows());
    ASSERT_EQ(1, image.get_label().get_cols());
}

TEST(DigitImageTest, ImageGetterSetterTest) {
    Matrix<double> imgData(8, 8);
    int label = 4;

    DigitImage image(imgData, label);

    ASSERT_EQ(imgData, image.get_image());

    Matrix<double> newImgData(10, 10);
    image.set_image(newImgData);

    ASSERT_EQ(newImgData, image.get_image());
}

TEST(DigitImageTest, DefaultConstructorTest) {
    DigitImage image;

    ASSERT_EQ(0, image.get_width());
    ASSERT_EQ(0, image.get_height());
    ASSERT_EQ(Matrix<double>(), image.get_label());
    ASSERT_EQ(Matrix<double>(), image.get_image());
}

TEST(DigitImageTest, MoveConstructorTest) {
    Matrix<double> imgData(16, 16);
    int label = 2;

    DigitImage original(imgData, label);
    DigitImage moved(std::move(original));

    ASSERT_EQ(16, moved.get_width());
    ASSERT_EQ(16, moved.get_height());
    Matrix<double> l(10, 1);
    l[label][0] = 1;
    ASSERT_EQ(l, moved.get_label());
    ASSERT_EQ(imgData, moved.get_image());

    ASSERT_EQ(0, original.get_width());
    ASSERT_EQ(0, original.get_height());
    ASSERT_EQ(Matrix<double>(), original.get_label());
    ASSERT_EQ(Matrix<double>(), original.get_image());
}