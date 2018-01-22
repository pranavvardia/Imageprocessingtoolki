#include "GaussianFilter.h"
#include <iostream>

using namespace std;

int const GaussianFilter::gauss_array[5][5] = {{1,4,7,4,1},{4,16,26,16,4},{7,26,41,26,7},{4,16,26,16,4},{1,4,7,4,1}};
GaussianFilter::GaussianFilter(){

}

GaussianFilter::GaussianFilter(Image& a):
  Image(a) {
   /*for(int i=0;i<height;i++) {
      for(int j=0;j<width;j++) {
        ptr[i][j] = a.get_ptr()[i][j];
      }
    }*/
    (*this).apply_gaussian();
  }

GaussianFilter::GaussianFilter(int w,int h):
  Image(w,h) {

  }

GaussianFilter::~GaussianFilter() {

}

GaussianFilter::GaussianFilter(const GaussianFilter& other):
  Image(other) {

}

float get_saturation(Pixel& p){
  Color c = p.get_color();
  int M,m;
  M = max(max(c.get_red(),c.get_green()),c.get_blue());
  m = min(min(c.get_red(),c.get_green()),c.get_blue());
  if(M == 0)
    return 0;
  return (M-m)/M;
}

vector<Pixel*> GaussianFilter::local_maxima() {
  std::vector<Pixel*> pix;
  for(int i=0;i<height;i++) {
    for(int j=0;j<width;j++) {
      if(is_max(i,j)) {
        pix.push_back(&ptr[i][j]);
      }
    }
  }
  return pix;
}

bool GaussianFilter::is_max(int y,int x) {
  for(int i=-1;i<=1;i++) {
    for(int j=-1;j<=1;j++) {
      if(!(i==0 && j==0)){
        if(is_valid_coor(x+j,y+i)) {
          if(get_saturation(ptr[y+i][x+j])>=get_saturation(ptr[y][x]))
            return false;
          }
        }
      }
    }
  return true;
}

std::vector<Pixel*> GaussianFilter::neighbourhood_24_color() {
  int x,y;
  Color w(255,255,255);
  Color b(0,0,0);
  std::vector<Pixel*> max = local_maxima();
  for(int i=0;i<height;i++) {
    for(int j=0;j<width;j++) {
      this->setColor(i,j,b.get_red(),b.get_green(),b.get_blue());
    }
  }
  for(int k=0;k<max.size();k++) {
    std::vector<Pixel*> pixels = neighbourhood_24(max[k]);
    for(int i=0;i<pixels.size();i++) {
      x = pixels[i]->get_x();
      y = pixels[i]->get_y();
      this->setColor(y,x,w.get_red(),w.get_green(),w.get_blue());
    }
    pixels.clear();
  }
  return max;
}

std::vector<Pixel*> GaussianFilter::neighbourhood_24(Pixel* p) {
  int x = p->get_x();
  int y = p->get_y();
  std::vector<Pixel*> pix;
  for(int i=-2;i<=2;i++) {
    for(int j=-2;j<=2;j++) {
      if(is_valid_coor(x+j,y+i))
        pix.push_back(&ptr[y+i][x+j]);
    }
  }
  return pix;
}

bool GaussianFilter::is_valid_coor(int x,int y)
{
  if(x>=0 && x<width) {
    if(y>=0 && y<height)
      return true;
    return false;
  }
  return false;
}

bool is_in_24_neighbourhood(Pixel* p1,Pixel* p2) {
  int p1_x=p1->get_x();
  int p1_y=p1->get_y();
  int p2_x=p2->get_x();
  int p2_y=p2->get_y();
  int x=p2_x-p1_x;
  int y=p2_y-p1_y;
  if(x<=2 && x>=-2) {
    if(y<=2 && y>=-2) {
      return true;
    }
    return false;
  }
  return false;
}
void GaussianFilter::apply_gaussian() {
  Color w(255,255,255);
  int x1,x2,y1,y2;
  std::vector<float> color;
  float col = 0;
  std::vector<Pixel*> max = neighbourhood_24_color();
  for(int k=0;k<max.size();k++) {
    std::vector<Pixel*> pixels = neighbourhood_24(max[k]);
    for(int i=0;i<pixels.size();i++) {
      int x = pixels[i]->get_x();
      int y = pixels[i]->get_y();
      if(ptr[y][x].get_color().get_red() == 255 && ptr[y][x].get_color().get_green() == 255 &&ptr[y][x].get_color().get_blue() == 255 )  {
        for(int j=k;j<max.size();j++) {
          if(is_in_24_neighbourhood(max[j],pixels[i])) {
            x1=max[j]->get_x();x2=pixels[i]->get_x();
            y1=max[j]->get_y();y2=pixels[i]->get_y();
            color.push_back(gauss_array[x2-x1+2][y2-y1+2]);
          }
        }
        col=0;
        for(int l=0;l<color.size();l++) {
          col+=color[l];
        }
        col/=color.size();
        col*=255;
        col/=273;
        Color c(col,col,col);
        this->setColor(y,x,c.get_red(),c.get_green(),c.get_blue());
        color.clear();
      }
    }
    pixels.clear();
  }
}
