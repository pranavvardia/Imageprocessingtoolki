#ifndef Histogram4_h
#define Histogram4_h
#include <fstream>
#include <vector>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
// #include <array>
#include "Pixel.h"
#include "Color.h"
#include "Image.h"
#include "CompositeImage.h"

using namespace std;

class Histogram4{
private:
    Image imga;
    vector<Pixel*> hist_data[256];
    vector<int > hist_count;
    vector<int> minimas;
    Color *c_arr[7];
public:
    Histogram4(Image &im);
    ~Histogram4();
    // Histogram4(array<vector<Pixel*> > &hist_data,
    // vector<int> &hist_count);
    Image get_img(){
        return imga;
    }
    void task4(Image &im);
    float task6(Image &img);
    vector<int> return_minimas();
    float medianThreshold(Image &img);
    void get_brightness(Image &img);
    int get_minima(Image &img);
    void color_segments(Image &img);
    void take_reflection(Image &img);
    void write(Image &im);
    friend ostream& operator << (ostream& os , Histogram4 h);
};

#endif
