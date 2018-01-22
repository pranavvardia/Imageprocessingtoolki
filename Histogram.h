#ifndef Histogram_H_
#define Histogram_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include "Color.h"
#include "Image.h"
#include "Pixel.h"
using namespace std;

class Histogram{
private:
  vector <int> histogram;
  vector <int> threshold;
public:
  Histogram();

  ~Histogram();

  Histogram(Image& img);

  float medianThreshold();
};

#endif
