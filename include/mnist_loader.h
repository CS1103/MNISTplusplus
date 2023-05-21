#include "DigitImage.h"
#include <vector>
#include <string>
#include <bit>
#include <iostream>
#include <fstream>
#include "constants.h"

#ifndef MNISTPLUSPLUS_MNIST_LOADER_H
#define MNISTPLUSPLUS_MNIST_LOADER_H

class MNISTReader {
public:
    using v_images = std::vector<DigitImage> ;

    MNISTReader()=default;

    void loadTrainDataset(const std::string& img_path, const std::string& label_path) {

        std::ifstream images_file(img_path, std::ios::binary);
        std::ifstream labelsFile(label_path, std::ios::binary);

        if (images_file.is_open() && labelsFile.is_open()) {
            #include "constants.h"
            int magic_num, num_rows, num_cols, num_image = read::TRAIN_NUM;

            images_file.read(reinterpret_cast<char *>(&magic_num), sizeof(magic_num));
            images_file.read(reinterpret_cast<char *>(&num_image), sizeof(num_image));
            images_file.read(reinterpret_cast<char *>(&num_rows), sizeof(num_rows));
            images_file.read(reinterpret_cast<char *>(&num_cols), sizeof(num_cols));


            magic_num = __builtin_bswap32(magic_num);
            num_image = __builtin_bswap32(num_image);
            num_rows = __builtin_bswap32(num_rows);
            num_cols = __builtin_bswap32(num_cols);


            if (magic_num !=read::MN_IMG) throw std::invalid_argument("Magic number mismatch, expected 2051");

            int label_magic_number, num_labels;
            labelsFile.read(reinterpret_cast<char *>(&label_magic_number), sizeof(label_magic_number));
            labelsFile.read(reinterpret_cast<char *>(&num_labels), sizeof(num_labels));

            label_magic_number = __builtin_bswap32(label_magic_number);
            num_labels = __builtin_bswap32(num_labels);
            if (label_magic_number != read::MN_LABEL) throw std::invalid_argument("Magic number mismatch, expected 2049");

            for (int i = 0; i < num_image; ++i) {
                std::vector<float> img(num_rows * num_cols);

                for (int pixel = 0; pixel < num_rows * num_cols; ++pixel) {
                    unsigned char pixel_value;
                    images_file.read(reinterpret_cast<char *>(&pixel_value), sizeof(pixel_value));
                    img[pixel] = static_cast<float>(pixel_value) / 255.0f;
                }

                unsigned char label;
                labelsFile.read(reinterpret_cast<char *>(&label), sizeof(label));
                DigitImage new_img(num_rows, num_cols, label, img);
                train_images.push_back(new_img);
            }
            images_file.close();
            labelsFile.close();
        }else throw std::runtime_error("Invalid files or filepaths");
    }

    void loadTestDataset(const std::string& img_path, const std::string& label_path){
        std::ifstream images_file(img_path, std::ios::binary);
        std::ifstream labels_file(label_path, std::ios::binary);

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


            if (magic_num != read::MN_IMG) throw std::invalid_argument("Test images magic number mismatch, expected 2051");

            int label_magic_number, num_labels;
            labels_file.read(reinterpret_cast<char *>(&label_magic_number), sizeof(label_magic_number));
            labels_file.read(reinterpret_cast<char *>(&num_labels), sizeof(num_labels));

            label_magic_number = __builtin_bswap32(label_magic_number);
            num_labels = __builtin_bswap32(num_labels);

            if (label_magic_number != read::MN_LABEL) throw std::invalid_argument("Test labels  magic number mismatch, expected 2049");
            for (int i = 0; i < num_image; ++i) {
                std::vector<float> img(num_rows * num_cols);

                for (int pixel = 0; pixel < num_rows * num_cols; ++pixel) {
                    unsigned char pixel_value;
                    images_file.read(reinterpret_cast<char *>(&pixel_value), sizeof(pixel_value));
                    img[pixel] = static_cast<float>(pixel_value) / 255.0f;
                }

                unsigned char label;
                labels_file.read(reinterpret_cast<char *>(&label), sizeof(label));
                DigitImage new_img(num_rows, num_cols, label, img);
                test_images.push_back(new_img);
            }
        }
    }

    v_images getTrainImg() const {return train_images;}
    v_images getTestImg()  const {return test_images;}

private:
    v_images train_images ;
    v_images test_images;
};


#endif //MNISTPLUSPLUS_MNIST_LOADER_H
