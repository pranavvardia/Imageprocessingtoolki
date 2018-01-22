#include<iostream>
#include<vector>
#include<string>
#include "ScaledImage.h"
using namespace std;
#include<sstream>
ScaledImage::ScaledImage(){}
ScaledImage::~ScaledImage(){}
vector<Image> ScaledImage::Img(Image image){
    vector<Image> images;
    Image image1(image.get_width(),image.get_height());
    Image image2(image.get_width(),image.get_height());
    Image image3(image.get_width(),image.get_height());
    Image image4(image.get_width(),image.get_height());
    for(int i=0;i<image.get_height();i++){
        for(int j=0;j<image.get_width();j++){
            image1.setColor(i,j,255,255,255);
            image2.setColor(i,j,255,255,255);
            image3.setColor(i,j,255,255,255);
            image4.setColor(i,j,255,255,255);            
        }
    }
    for(int i=0;i<image.get_width();i+=2){
        for(int j=0;j<image.get_height();j+=2){
            if(j==image.get_height()-1&&i==image.get_width()-1){
                image1.setColor(i/2,j/2,image.get_Color_x_y(i,j).get_red(),image.get_Color_x_y(i,j).get_green(),image.get_Color_x_y(i,j).get_blue());
            }
            else if(j==image.get_height()-1){
                image1.setColor(i/2,j/2,(image.get_Color_x_y(i,j).get_red()+image.get_Color_x_y(i+1,j).get_red())/2,(image.get_Color_x_y(i,j).get_green()+image.get_Color_x_y(i+1,j).get_green())/2,(image.get_Color_x_y(i,j).get_blue()+image.get_Color_x_y(i+1,j).get_blue())/2);
            }
            else if(i==image.get_width()-1){
                image1.setColor(i/2,j/2,(image.get_Color_x_y(i,j).get_red()+image.get_Color_x_y(i,j+1).get_red())/2,(image.get_Color_x_y(i,j).get_green()+image.get_Color_x_y(i,j+1).get_green())/2,(image.get_Color_x_y(i,j).get_blue()+image.get_Color_x_y(i,j+1).get_blue())/2);    
            }
            else{
                image1.setColor(i/2,j/2,(image.get_Color_x_y(i,j).get_red()+image.get_Color_x_y(i+1,j).get_red()+image.get_Color_x_y(i+1,j+1).get_red()+image.get_Color_x_y(i,j+1).get_red())/4,(image.get_Color_x_y(i,j).get_green()+image.get_Color_x_y(i+1,j).get_green()+image.get_Color_x_y(i+1,j+1).get_green()+image.get_Color_x_y(i,j+1).get_green())/4,(image.get_Color_x_y(i,j).get_blue()+image.get_Color_x_y(i+1,j).get_blue()+image.get_Color_x_y(i+1,j+1).get_blue()+image.get_Color_x_y(i,j+1).get_blue())/4);
            }
        }
    }
    image2=ReflectionY(image1);
    image3=ReflectionX(image2);
    image4=ReflectionY(image3);
    images.push_back(image1);
    images.push_back(image2);
    images.push_back(image3);
    images.push_back(image4);
    return images;
}
Image ScaledImage::ReflectionY(Image image){
    Image image1(image.get_width(),image.get_height());
    for(int i=0;i<image.get_width();i++){
        for(int j=0;j<image.get_height();j++){    
            image1.setColor(image.get_width()-i-1,j,image.get_Color_x_y(i,j).get_red(),image.get_Color_x_y(i,j).get_green(),image.get_Color_x_y(i,j).get_blue());
        }
    }
    return image1;
}
Image ScaledImage::ReflectionX(Image image){
    Image image1(image.get_width(),image.get_height());
    for(int i=0;i<image.get_width();i++){
        for(int j=0;j<image.get_height();j++){
            image1.setColor(i,image.get_height()-j-1,image.get_Color_x_y(i,j).get_red(),image.get_Color_x_y(i,j).get_green(),image.get_Color_x_y(i,j).get_blue());
        }
    }
    return image1;
}
Image ScaledImage::crop(Image image){
    for(int i=0;i<image.get_width();i++){
        for(int j=0;j<image.get_height();j++){
            if(i<image.get_width()/4||i>(3*image.get_width())/4||j<image.get_height()/4||j>(3*image.get_height())/4){
                image.setColor(i,j,255,255,255);
            }
        }
    }
    return image;
}
