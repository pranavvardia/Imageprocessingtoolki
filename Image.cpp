#include "Image.h"
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

Image::Image() {

}
Image::Image(char * file){
    ifstream fin;
    fin.open(file);
    char type[10];
    fin >> type;
    // if (strcmp(type, "P3") != 0) {
    //     cout << "WRONG FORMAT" << endl;
    // }
    fin >> width;
    fin >> height;
    fin >> maxColor;
    // Pixel ** pix = ptr;
    // cout <<"got the image : " << type << ' '<<width << ' '<<height<< ' '<<maxColor<<'\n';
    ptr = new Pixel*[height];
    for(int i=0;i<height;i++){
        ptr[i] = new Pixel[width];
    }
    int r, g, b;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            fin >> r >> g >> b;
            Color c(r,g,b);
            // pix[i][j].set_loc(i,j);
            // cout<<i<<' '<<j<<' ';
            ptr[i][j].set_color(c);
            // cout << ptr[i][j];
        }
    }
    // cout<<"tanishqqq\n";
    // cout << get_height()<<' '<<get_width();
}
Image::Image(int w, int h) {
  width = w;
  height = h;
  ptr = new Pixel*[height];
  for(int i=0;i<height;i++) {
    ptr[i] = new Pixel[width]();
  }
}

Image::~Image() {
}

Image Image::reflectionAboutY(){
  Image answer = *this;
  for(int i = 0 ; i < answer.height ; i++){
    int start=0,end=width-1;
    while(start < end)
    {
      Pixel temp = answer.ptr[i][start];
      answer.ptr[i][start] = answer.ptr[i][end];
      answer.ptr[i][end] = temp;
      start++;
      end--;
    }
  }
  return answer;
}

Image Image::reflectionAboutX(){
  Image answer = *this;
  for(int i = 0 ; i < answer.width ; i++){
    int start=0,end=height-1;
    while(start < end)
    {
      Pixel temp = answer.ptr[start][i];
      answer.ptr[start][i] = answer.ptr[end][i];
      answer.ptr[end][i] = temp;
      start++;
      end--;
    }
  }
  return answer;
}

Image::Image(const Image& other) {
  width = other.width;
  height = other.height;
  ptr = new Pixel*[height];
  for(int i=0;i<height;i++) {
    ptr[i] = new Pixel[width]();
  }
  for(int i=0;i<height;i++) {
    for(int j=0;j<width;j++) {
      ptr[i][j] = other.ptr[i][j];
    }
  }
}

int Image::get_width() const{
  return width;
}

int Image::get_height() const{
  return height;
}

Color Image::get_Color_x_y(int x, int y) const{
  return ptr[x][y].get_color();
}

Pixel** Image::get_ptr() {
  return ptr;
}

void Image::setColor(int i, int j, int r, int g, int b) {
  ptr[i][j].set_color(r, g, b);
}

Image& Image::operator=(Image const &other) {
  height = other.height;
  width = other.width;
  ptr = new Pixel*[height];
  for(int i=0;i<height;i++){
      ptr[i] = new Pixel[width];
  }
  for(int i=0;i<height;i++) {
    for(int j=0;j<width;j++) {
      ptr[i][j] = other.ptr[i][j];
    }
  }
  return *(this);
}

Image operator+(Image const &image1, Image const &image2) {
  if(image1.get_width() == image2.get_width() && image1.get_height() == image2.get_height()) {
    int w1 = image1.get_width();
    int h1 = image1.get_height();
    Image result(w1, h1);
    for(int i=0;i<result.get_height();i++) {
      for(int j=0;j<result.get_width();j++) {
        int new_r = image1.get_Color_x_y(i, j).get_red() + image2.get_Color_x_y(i, j).get_red();
        int new_g = image1.get_Color_x_y(i, j).get_green() + image2.get_Color_x_y(i, j).get_green();
        int new_b = image1.get_Color_x_y(i, j).get_blue() + image2.get_Color_x_y(i, j).get_blue();
        result.setColor(i, j, new_r, new_g, new_b);
      }
    }
    return result;
  }
}

Image operator*(float const &f, Image const &image) {
  Image tmp_image(image.get_width(), image.get_height());
  for(int i=0;i<image.get_height();i++) {
    for(int j=0;j<image.get_width();j++) {
      int new_red = f*(image.ptr[i][j].get_color().get_red());
      int new_green = f*(image.ptr[i][j].get_color().get_green());
      int new_blue = f*(image.ptr[i][j].get_color().get_blue());
      tmp_image.setColor(i, j, new_red, new_green, new_blue);
    }
  }
  return tmp_image;
}

istream& operator>>(istream &is, Image &image) {
  for(int i=0;i<image.height;i++) {
    for(int j=0;j<image.width;j++) {
      int r, g, b;
      is>>r>>g>>b;
      image.ptr[i][j].set_color(r, g, b);
    }
  }
  return is;
}

ostream& operator<<(ostream &os, Image &image) {
  Pixel **p = image.get_ptr();
  for(int i=0;i<image.height;i++) {
    for(int j=0;j<image.width;j++) {
      os<<p[i][j]<<" ";
    }
    os<<endl;
  }
  return os;
}
