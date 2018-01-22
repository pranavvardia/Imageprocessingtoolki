#ifndef Segmentation_H_
#define Segmentation_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include "Color.h"
#include "Image.h"
#include "Pixel.h"
#include "Histogram4.h"

using namespace std;

class Segmentation : public Image{
public:
  Segmentation();

  ~Segmentation();

  Segmentation(Image& img);

  void findConnectedComponents(Image& img);

  void mergeGroups(vector<vector<int> > &groups, int grp1, int grp2);

};

#endif
