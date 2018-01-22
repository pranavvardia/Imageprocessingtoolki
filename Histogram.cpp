#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include "Image.h"
#include "Histogram.h"

using namespace std;

Histogram::Histogram(){

}

Histogram::~Histogram(){

}

Histogram::Histogram(Image& img){
  int height = img.get_height();
  int width = img.get_width();
  vector < vector <int> > brightness(height,vector <int> (width));
  for(int i = 0; i<height; i++)
  {
    for(int j = 0; j<width; j++)
    {
        brightness[i][j] = (img.get_Color_x_y(i,j).get_red() + img.get_Color_x_y(i,j).get_blue() + img.get_Color_x_y(i,j).get_green())/3;
    }
  }
  for(int i=0;i<256;i++){
    histogram.push_back(0);
  }
  for(int i = 0; i<height; i++)
  {
    for(int j = 0; j<width; j++)
    {
      histogram[brightness[i][j]]++;
    }
  }
    for(int i = 5; i<251; i++)
    {
      int flag = 0;
      for(int j = 1; j<5; j++)
      {
        if(histogram[i] < histogram[i-j] && histogram[i] <= histogram[i+j])
        {
          continue;
        }
        else
        {
          flag = 1;
        }
      }
      if(flag == 0)
      {
        threshold.push_back(i);
      }
    }
}

float Histogram::medianThreshold(){
  int size = threshold.size();
  sort(threshold.begin() , threshold.end());
  if(size == 0){
    return 122;
  }
  else if(size%2 == 0)
    return (threshold[size/2] + threshold[size/2 -1])/2;
  else
    return threshold[size/2];
}
