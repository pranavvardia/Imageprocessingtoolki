#ifndef CompositeImage_H_
#define CompositeImage_H_
#include "Image.h"

class CompositeImage: public Image {
  public:
    CompositeImage();
    CompositeImage(Image a, Image b, float alpha);
    ~CompositeImage();
    CompositeImage(const CompositeImage& other);
  private:
    Image C;
};

#endif
