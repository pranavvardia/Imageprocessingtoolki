#ifndef Image_H_
#define Image_H_

#include "Pixel.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Image {
  public:
    Image();
    Image(char *file);
    Image(int w, int h);
    ~Image();
    Image(const Image& other);
    int get_width() const;
    int get_height() const;
    Color get_Color_x_y(int x, int y) const;
    Pixel **get_ptr();
    void setColor(int i, int j, int r, int g, int b);
    Image& operator=(Image const &other);
    friend Image operator+(Image const &image1, Image const &image2);
    friend Image operator*(float const &f, Image const &image);
    friend istream& operator>>(istream &is, Image &image);
    friend ostream& operator<<(ostream &os, Image &image);
    Image reflectionAboutY();

    Image reflectionAboutX();
  protected:
    int width, height;
    int maxColor;
    Pixel **ptr;
};

#endif
