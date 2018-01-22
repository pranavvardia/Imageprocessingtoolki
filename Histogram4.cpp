#include "Histogram4.h"

using namespace std;

Histogram4::Histogram4(Image &im){
    // img = im;
    for (int i = 0; i < 256; ++i){
        hist_count.push_back(0);
    }
    c_arr[0] = new Color(255,0,0);
    c_arr[1] = new Color(0,255,0);
    c_arr[2] = new Color(0,0,255);
    c_arr[3] = new Color(255,255,0);
    c_arr[4] = new Color(255,0,255);
    c_arr[5] = new Color(0,255,255);
    c_arr[6] = new Color(0,0,0);
    // cout << im.get_height()<<' '<<im.get_width();
    get_brightness(im);
    int size = get_minima(im);
    if(size > 0){
      color_segments(im);
      write(im);
    }
    else{
      take_reflection(im);
    }
}
Histogram4::~Histogram4(){
}
// Histogram4::Histogram4(vector<vector<Pixel*> > &hist_data,
// vector<int> &hist_count):hist_data(hist_data),hist_count(hist_count){
// }
void Histogram4::task4(Image &im){
  get_brightness(im);
  int size = get_minima(im);
  if(size > 2){
    color_segments(im);
    write(im);
  }
  else{
    take_reflection(im);
  }
}
float Histogram4::task6(Image &img){
  return medianThreshold(img);

}
void Histogram4::get_brightness(Image &img){
    for (int i = 0; i < img.get_height(); i++){
        for (int j = 0; j < img.get_width(); j++) {
            Pixel &pix = img.get_ptr()[i][j];
            int brightness = (pix.get_color().get_red() + pix.get_color().get_green() + pix.get_color().get_blue()) / 3;
            hist_data[brightness].push_back(&pix);
            hist_count[brightness]++;
        }
    }
    // for (int i = 0; i < 256; ++i){
    //     cout<<hist_count[i]<<'\n';
    // }
}
int Histogram4::get_minima(Image &img){
    minimas.push_back(0);
    int flag;
    for (int i = 1; i < 255; ++i){
        // for(int j = 1; j < 2 ; j++){
        //     if(hist_count[i] < hist_count[i-j] && hist_count[i] <= hist_count[i+j])
        //         continue;
        //     else
        //         flag = 1;
        // }
        // if(flag == 0)
        //     minimas.push_back(i);
        if(hist_count[i-1] > hist_count[i] && hist_count[i+1] > hist_count[i]){
            minimas.push_back(i);
        }
    }
    minimas.push_back(255);
    // cout<<'\n' << minimas.size()<<'\n';
    // for (std::vector<int>::iterator it = minimas.begin() ; it != minimas.end(); ++it){
    //     cout << (*it)<< ' ';
    // }
    return minimas.size();
}
float Histogram4::medianThreshold(Image &img){
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
    hist_count.push_back(0);
  }
  for(int i = 0; i<height; i++)
  {
    for(int j = 0; j<width; j++)
    {
      hist_count[brightness[i][j]]++;
    }
  }
  for(int i = 5; i<251; i++)
  {
    int flag = 0;
    for(int j = 1; j<5; j++)
    {
      if(hist_count[i] < hist_count[i-j] && hist_count[i] <= hist_count[i+j])
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
      hist_count.push_back(i);
    }
  }
  int size = minimas.size();
  // sort(.begin() , threshold.end());
  if(size == 2){
    return 122;
  }
  else if((size)%2 == 0)
    return (minimas[size/2] + minimas[size/2 -1])/2;
  else
    return minimas[size/2];
}

void Histogram4::take_reflection(Image &img){
  Image ref(img.get_width(),img.get_height());
  for (int i = 0; i < img.get_height(); i++){
      for (int j = 0,k = img.get_width(); j < img.get_width(); j++,k--){
          ref.get_ptr()[i][j].set_color(img.get_ptr()[i][k].get_color());
          // Pixel &pix = img.get_ptr()[i][j];
          // int brightness = (pix.get_color().get_red() + pix.get_color().get_green() + pix.get_color().get_blue()) / 3;
          // hist_data[brightness].push_back(&pix);
          // hist_count[brightness]++;
      }
  }
  CompositeImage cmp(img,ref,0.4);
  write(cmp);
}
vector<int> Histogram4::return_minimas(){
	return minimas;
}
void Histogram4::color_segments(Image &img){
  // cout<<'\n'<<minimas.size()<<'\n';
    for (int i = 0; i < 6 && i < minimas.size(); ++i){
        // cout<<minimas[i]<<'\n';
        for (int j = minimas[i]; j < minimas[i+1]; ++j){
          // cout <<i << ' '<< j << '\n';
            for (std::vector<Pixel*>::iterator it = hist_data[j].begin() ; it != hist_data[j].end(); ++it){
                (*it) -> set_color(*(c_arr[i]));
                // cout << (*it) -> get_color().get_red() << ' '<<(*it) -> get_color().get_green() << ' '<<(*it) -> get_color().get_blue() << '\n';
            }
        }
    }
    if(minimas.size() > 6){
        for (int j = minimas[6]; j < 256; ++j){
            for (std::vector<Pixel*>::iterator it = hist_data[j].begin() ; it != hist_data[j].end(); ++it){
                (*it) -> set_color(*(c_arr[6]));
            }
        }
    }
}
void Histogram4::write(Image &im){
    ofstream output("output_task4_IMT2016126.ppm");
    output << "P3" << endl << im.get_width()<<' '<<im.get_height()<<endl<<255<<endl;
    // cout << '\n' << h.get_img().get_height() << ' '<< h.get_img().get_width()<<'\n';
    for (int i = 0; i < im.get_height(); i++){
        for (int j = 0; j < im.get_width(); j++){
            Color col = im.get_Color_x_y(i,j);
            // cout<< i << ' '<<j << ' '<<col;
            output << col.get_red()<<' '<<col.get_green()<<' '<<col.get_blue()<<' ';
        }
    }
}
ostream& operator << (ostream& os , Histogram4 h){
    ofstream output("imt2016126.ppm");
    output << "P3" << endl << h.get_img().get_width()<<' '<<h.get_img().get_height()<<endl<<255<<endl;
    // cout << '\n' << h.get_img().get_height() << ' '<< h.get_img().get_width()<<'\n';
    for (int i = 0; i < h.get_img().get_height(); i++){
        for (int j = 0; j < h.get_img().get_width(); j++){
            Color col = h.get_img().get_Color_x_y(i,j);
            cout<< i << ' '<<j << ' '<<col;
            output << col.get_red()<<' '<<col.get_green()<<' '<<col.get_blue()<<' ';
        }
    }
    // output << h.get_img();
    return os;
}
