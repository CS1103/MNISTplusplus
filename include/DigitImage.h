#include <vector>
#include <iostream>
#include <iomanip>

#ifndef PROYECTO_FINAL_TE02_202301_PF0220231_GRUPO1_SUB_1_DIGITIMAGE_H
#define PROYECTO_FINAL_TE02_202301_PF0220231_GRUPO1_SUB_1_DIGITIMAGE_H

class DigitImage {
public:
    using vPixels= std::vector<float>;
    //Constructors
    DigitImage()=default;
    DigitImage(int _w, int _h, unsigned int _l, vPixels pixels): width(_w), height(_h), label(_l), image(std::move(pixels)){}
    DigitImage(const DigitImage& other) : width(other.width), height(other.height), label(other.label), image(other.image) {}
    DigitImage(DigitImage&& other) noexcept : width(other.width), height(other.height), label(other.label), image(std::move(other.image)) {
        other.width = 0;
        other.height = 0;
        other.label = 0;
    }


    //Desctructors
    virtual ~DigitImage()=default;

    //Getters
    unsigned int get_width(){return width;}
    unsigned int get_height(){return height;}
    unsigned int get_label(){return label;}
    vPixels get_image(){return image;}

    //Setters
    void set_image(vPixels px){image = std::move(px);}
    void set_label(unsigned int _l){label = _l;}

    //Operators Overloads
    friend std::ostream& operator << (std::ostream& o, const DigitImage& img ){
        std::cout <<"\nMatriz de pixeles del numero : " << img.label << '\n';

        for(int i = 0; i < img.height; i++){
            for(int j = 0; j < img.width; j++){
                std::string ch = img.image[i * img.width + j] != 0 ? "0" : "&&";
                std::cout << ch << std::setw(4);
            }
            std::cout << '\n';
        }
        return o;
    }

private:
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int label = 10;
    vPixels image;
};


#endif //PROYECTO_FINAL_TE02_202301_PF0220231_GRUPO1_SUB_1_DIGITIMAGE_H
