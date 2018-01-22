#ifndef xAxisReflection_H_
#define xAxisReflection_H_
#include "Image.h"

class xAxisReflection: public Image {
  public:
    xAxisReflection();
    xAxisReflection(Image& a);
    ~xAxisReflection();
    xAxisReflection(const xAxisReflection& other);
};

#endif
