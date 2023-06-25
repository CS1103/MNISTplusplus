#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include "matrix.h"


class DigitImage {
    using Mat=Matrix<double>;

private:
    Mat label;
    Mat image;
public:
    //Constructors
    DigitImage()=default;
    DigitImage(Mat img, int _label): image(std::move(img)){
        label = Mat(10, 1);
        label[_label][0] = 1;
    }
    DigitImage(const DigitImage& other): label(other.label), image(other.image) {}
    DigitImage(DigitImage&& other) noexcept: label(std::move(other.label)), image(std::move(other.image)) {}

    //Destructors
    virtual ~DigitImage()=default;

    //Getters
    unsigned int get_width() const {return image.get_cols();}
    unsigned int get_height() const {return image.get_rows();}
    Mat get_label() const{return label;}
    Mat get_image(){return image;}

    //Setters
    void set_image(Mat px){image = std::move(px);}
    void set_label(Mat _l){label = std::move(_l);}

    //Operators Overloads
    friend std::ostream& operator << (std::ostream& o, const DigitImage& img ){
        std::cout <<"\nMatriz de pixeles del numero : " << img.label << '\n';

        for(int i = 0; i < img.get_width(); i++){
            for(int j = 0; j < img.get_height(); j++){
                std::string ch = img.image[i][j] != 0 ? "0" : "&&";
                std::cout << ch << std::setw(4);
            }
            std::cout << '\n';
        }
        return o;
    }
};
