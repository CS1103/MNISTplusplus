#pragma once

#include "digit_image.h"
#include "matrix.h"
#include <vector>
#include <string>
#include <bit>
#include <iostream>
#include <fstream>
#include "digit_image.h"
#include "constants.h"


class MNISTReader {
    using v_images = std::vector<DigitImage> ;
private:
    v_images train_images;
    v_images test_images;
public:

    MNISTReader()=default;

    v_images load_dataset(const char* img_path, const char* label_path) {
        std::filesystem::path _img_path = get_absolute_path(img_path);
        std::filesystem::path _label_path = get_absolute_path(label_path);

        std::ifstream images_file(_img_path, std::ios::binary);
        std::ifstream labels_file(_label_path, std::ios::binary);

        v_images return_value;

        if (images_file.is_open() && labels_file.is_open()) {
            int magic_num, num_rows, num_cols, num_image = read::TRAIN_NUM;

            images_file.read(reinterpret_cast<char *>(&magic_num), sizeof(magic_num));
            images_file.read(reinterpret_cast<char *>(&num_image), sizeof(num_image));
            images_file.read(reinterpret_cast<char *>(&num_rows), sizeof(num_rows));
            images_file.read(reinterpret_cast<char *>(&num_cols), sizeof(num_cols));

            magic_num = __builtin_bswap32(magic_num);
            num_image = __builtin_bswap32(num_image);
            num_rows = __builtin_bswap32(num_rows);
            num_cols = __builtin_bswap32(num_cols);


            if (magic_num != read::MN_IMG) throw std::invalid_argument("Image magic number mismatch, expected 2051");

            int label_magic_number, num_labels;
            labels_file.read(reinterpret_cast<char *>(&label_magic_number), sizeof(label_magic_number));
            labels_file.read(reinterpret_cast<char *>(&num_labels), sizeof(num_labels));

            label_magic_number = __builtin_bswap32(label_magic_number);
            num_labels = __builtin_bswap32(num_labels);

            if (label_magic_number != read::MN_LABEL) throw std::invalid_argument("Label magic number mismatch, expected 2049");

            for (int i = 0; i < num_image; ++i) {
                std::vector<float> img(num_rows * num_cols);

                for (int pixel_index = 0; pixel_index < num_rows * num_cols; ++pixel_index) {
                    unsigned char pixel_value;
                    images_file.read(reinterpret_cast<char *>(&pixel_value), sizeof(pixel_value));
                    img[pixel_index] = static_cast<float>(pixel_value) / 255.0f;
                }

                Matrix<double> mat(num_rows, num_cols, img);
                unsigned char label;
                labels_file.read(reinterpret_cast<char *>(&label), sizeof(label));
                DigitImage digit_image(mat, label);

                return_value.emplace_back(digit_image);
            }
            images_file.close();
            labels_file.close();
        }
        else throw std::runtime_error("Invalid files or filepaths");

        return return_value;
    }

    void load_train_dataset(const char* img_path = TRAIN_IMAGE_PATH, const char* label_path = TRAIN_LABEL_PATH) {
        train_images = load_dataset(TRAIN_IMAGE_PATH, TRAIN_LABEL_PATH);
    }

    void load_test_dataset(const char* img_path=TEST_IMAGE_PATH, const char* label_path=TEST_LABEL_PATH){
        test_images = load_dataset(TEST_IMAGE_PATH, TEST_LABEL_PATH);
    }

    v_images get_training_data() const {return train_images;}
    v_images get_test_data()  const {return test_images;}
};
