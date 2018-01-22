#include "Task1.h"
#include <cmath>
#include <cstdlib>


int getDistance(int i1, int j1, int i, int j) {
    int xdiff = pow((i - i1), 2);
    int ydiff = pow((j - j1), 2);
    int res = floor(sqrt(xdiff + ydiff));
    return res;
}

//Keep in mind, while instantiating this class we need to give height and
//width. IMP


void Task1::makeCircle(int x, int y) {
    int radius = std::min(floor(get_width() * 0.125),
            floor(get_height() * 0.125));
    Color b(0, 0, 0);
    Color w(255, 255, 255);
    for(int i = 0; i < get_height(); i++) {
        for(int j = 0; j < get_width(); j++) {
            int dis = getDistance(x, y, i, j);
            if(dis <= radius) {
                setColor(i, j, 0, 0, 0);
            }
            else {
                if(!get_Color_x_y(i, j).isequal(b)) {
                    setColor(i, j, 255, 255, 255);
                }
            }
        }
    }
}

//void Task1::setImage

void Task1::reverseImage(Image &i) {
    //*(get_tptr()) = new Pixel*[get_height()];
    //Pixel **dp = *(get_tptr());
    Pixel **dp1 = i.get_ptr();
    for(int i = 0; i < get_height(); i++) {
        //   dp[i] = (Pixel*) malloc(sizeof(Pixel) * get_width());
        for(int j = 0; j < get_width(); j++) {
            //dp[i][j].set_pixel(i, j, 
            Color c =  dp1[i][get_width() - j - 1].get_color();
            setColor(i, j, c.get_red(), c.get_green(), c.get_blue());
        }
    }
}

void Task1::imageClip(Image *i1, Image *i2) {
    //*(get_tptr()) = new Pixel*[get_height()];
    //Pixel **dp = *(get_tptr());
    Pixel **dp1 = i1->get_ptr();
    Pixel **dp2 = i2->get_ptr();
    Color b(0, 0, 0);
    Color w(255, 255, 255);
    for(int i = 0; i < get_height(); i++) {
        //   dp[i] = (Pixel*)malloc(sizeof(Pixel) * get_width());
        for(int j = 0; j < get_width(); j++) {
            if(dp2[i][j].get_color().isequal(w)) {
                //dp[i][j].set_pixel(i, j, w);
                setColor(i, j, 255, 255, 255);
            }
            else {
                // dp[i][j].set_pixel(i, j, dp1[i][j].get_color());
                Color c = dp1[i][j].get_color();
                setColor(i, j, c.get_red(), c.get_green(), c.get_blue());

            }
        }
    }
}


void Task1::imageStencil(Image *i1, Image *i2) {
    Pixel **dp1 = i1->get_ptr();
    Pixel **dp2 = i2->get_ptr();
    Color b(0, 0, 0);
    Color w(255, 255, 255);
    for(int i = 0; i < get_height(); i++) {
        for(int j = 0; j < get_width(); j++) {
            if(dp2[i][j].get_color().isequal(b)) {
                setColor(i, j, 255, 255, 255);
            }
            else {
                Color c = dp1[i][j].get_color();
                setColor(i, j, c.get_red(), c.get_green(), c.get_blue());
            }
        }
    }
}


