#include "xAxisReflection.h"

xAxisReflection::xAxisReflection() {

}

xAxisReflection::xAxisReflection(Image& a):
  Image(a.get_width(), a.get_height()) {
    for(int i=0;i<height;i++) {
      for(int j=0;j<width;j++) {
        Color c = a.get_ptr()[height-1-i][j].get_color();
        ptr[i][j]=Pixel(j,i,c);
      }
    }
}

xAxisReflection::~xAxisReflection() {

}

xAxisReflection::xAxisReflection(const xAxisReflection& other):
  Image(other.width, other.height) {
    for(int i=0;i<height;i++) {
      for(int j=0;j<width;j++) {
        ptr[i][j] = other.ptr[i][j];
      }
    }
}
