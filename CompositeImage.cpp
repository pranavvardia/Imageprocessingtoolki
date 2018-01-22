#include "CompositeImage.h"

CompositeImage::CompositeImage() {

}

CompositeImage::CompositeImage(Image a, Image b, float alpha) :
    Image(a.get_width(), a.get_height()) {
    if(a.get_width() == b.get_width() && a.get_height() == b.get_height()){
      for(int i=0; i<a.get_height(); i++){
        for(int j=0; j<a.get_width(); j++){
          int red = alpha*(a.get_ptr()[i][j].get_color().get_red())
              + (1-alpha)*(b.get_ptr()[i][j].get_color().get_red());
          int green = alpha*(a.get_ptr()[i][j].get_color().get_green()) +
              (1-alpha)*(b.get_ptr()[i][j].get_color().get_green());
          int blue  = alpha*(a.get_ptr()[i][j].get_color().get_blue()) +
              (1-alpha)*(b.get_ptr()[i][j].get_color().get_blue());
          setColor(i,j,red,green,blue);
        }
      }
    }
}

CompositeImage::~CompositeImage() {

}

CompositeImage::CompositeImage(const CompositeImage& other):
  Image(other.get_width(), other.get_height()) {
    for(int i=0;i<height;i++) {
      for(int j=0;j<width;j++) {
        ptr[i][j] = other.ptr[i][j];
      }
    }
}
