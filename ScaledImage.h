#ifndef ScaledImage_H_
#define ScaledImage_H_
#include "Image.h"
#include <vector>
using namespace std;
class ScaledImage :public Image{
    public:
        ScaledImage();
        ~ScaledImage();
        vector<Image> Img(Image image);
        Image ReflectionY(Image image);
        Image ReflectionX(Image image);
        Image crop(Image image);
};
#endif
