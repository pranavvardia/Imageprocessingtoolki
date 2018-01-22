#ifndef TASK1_H_
#define TASK1_H_

#include "Image.h"


class Task1 : public Image {
    public:
        Task1() = default;
        ~Task1() {};
        Task1(int width, int hei) :
            Image(width, hei) { };
        void makeCircle(int x, int y);
        void reverseImage(Image &x);
        void imageClip(Image *i1, Image *i2);
        void imageStencil(Image *i1, Image *i2);
    protected:
    private:
};

#endif

