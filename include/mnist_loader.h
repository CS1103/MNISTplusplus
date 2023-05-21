#include "DigitImage.h"
#include <vector>
#include <string>
#include <bit>
#include <iostream>
#include <fstream>

#ifndef MNISTPLUSPLUS_MNIST_LOADER_H
#define MNISTPLUSPLUS_MNIST_LOADER_H


class MNISTReader {
public:
    using v_images = std::vector<DigitImage> ;

    MNISTReader()=default;

    void loadTrainDataset(const std::string& imgPath, const std::string& labelPath) {

        std::ifstream imagesFile(imgPath, std::ios::binary);
        std::ifstream labelsFile(labelPath, std::ios::binary);

        if (imagesFile.is_open() && labelsFile.is_open()) {
            int magicNum, numRows, numCols, numImage = 60000;

            imagesFile.read(reinterpret_cast<char *>(&magicNum), sizeof(magicNum));
            imagesFile.read(reinterpret_cast<char *>(&numImage), sizeof(numImage));
            imagesFile.read(reinterpret_cast<char *>(&numRows), sizeof(numRows));
            imagesFile.read(reinterpret_cast<char *>(&numCols), sizeof(numCols));


            magicNum = __builtin_bswap32(magicNum);
            numImage = __builtin_bswap32(numImage);
            numRows = __builtin_bswap32(numRows);
            numCols = __builtin_bswap32(numCols);


            if (magicNum != 2051) throw std::invalid_argument("Magic number mismatch, expected 2051");

            int labelMagicNumber, numLabels;
            labelsFile.read(reinterpret_cast<char *>(&labelMagicNumber), sizeof(labelMagicNumber));
            labelsFile.read(reinterpret_cast<char *>(&numLabels), sizeof(numLabels));

            labelMagicNumber = __builtin_bswap32(labelMagicNumber);
            numLabels = __builtin_bswap32(numLabels);
            if (labelMagicNumber != 2049) throw std::invalid_argument("Magic number mismatch, expected 2049");

            for (int i = 0; i < numImage; ++i) {
                std::vector<float> img(numRows * numCols);

                for (int pixel = 0; pixel < numRows * numCols; ++pixel) {
                    unsigned char pixelValue;
                    imagesFile.read(reinterpret_cast<char *>(&pixelValue), sizeof(pixelValue));
                    img[pixel] = static_cast<float>(pixelValue) / 255.0f;
                }

                unsigned char label;
                labelsFile.read(reinterpret_cast<char *>(&label), sizeof(label));
                DigitImage new_img(numRows, numCols, label, img);
                trainImages.push_back(new_img);
            }
            imagesFile.close();
            labelsFile.close();
        }else throw std::runtime_error("Invalid files or filepaths");
    }

    void loadTestDataset(const std::string& imgPath, const std::string& labelPath){
        std::ifstream imagesFile(imgPath, std::ios::binary);
        std::ifstream labelsFile(labelPath, std::ios::binary);

        if (imagesFile.is_open() && labelsFile.is_open()) {
            int magicNum, numRows, numCols, numImage = 10000;

            imagesFile.read(reinterpret_cast<char *>(&magicNum), sizeof(magicNum));
            imagesFile.read(reinterpret_cast<char *>(&numImage), sizeof(numImage));
            imagesFile.read(reinterpret_cast<char *>(&numRows), sizeof(numRows));
            imagesFile.read(reinterpret_cast<char *>(&numCols), sizeof(numCols));

            magicNum = __builtin_bswap32(magicNum);
            numImage = __builtin_bswap32(numImage);
            numRows = __builtin_bswap32(numRows);
            numCols = __builtin_bswap32(numCols);


            if (magicNum != 2051) throw std::invalid_argument("Test images magic number mismatch, expected 2051");

            int labelMagicNumber, numLabels;
            labelsFile.read(reinterpret_cast<char *>(&labelMagicNumber), sizeof(labelMagicNumber));
            labelsFile.read(reinterpret_cast<char *>(&numLabels), sizeof(numLabels));

            labelMagicNumber = __builtin_bswap32(labelMagicNumber);
            numLabels = __builtin_bswap32(numLabels);

            if (labelMagicNumber != 2049) throw std::invalid_argument("Test labels  magic number mismatch, expected 2049");
            for (int i = 0; i < numImage; ++i) {
                std::vector<float> img(numRows * numCols);

                for (int pixel = 0; pixel < numRows * numCols; ++pixel) {
                    unsigned char pixelValue;
                    imagesFile.read(reinterpret_cast<char *>(&pixelValue), sizeof(pixelValue));
                    img[pixel] = static_cast<float>(pixelValue) / 255.0f;
                }

                unsigned char label;
                labelsFile.read(reinterpret_cast<char *>(&label), sizeof(label));
                DigitImage new_img(numRows, numCols, label, img);
                testImages.push_back(new_img);
            }
        }
    }

    v_images getTrainImg() const {return trainImages;}
    v_images getTestImg()  const {return testImages;}


    /*friend std::ostream& operator<<(std::ostream& o, const MNISTReader& reader){
        for(int i = 0; i <5 ; i++){
            std::cout << reader.trainImages[i];
        }
    }*/
private:
    v_images trainImages ;
    v_images testImages;
};


#endif //MNISTPLUSPLUS_MNIST_LOADER_H
