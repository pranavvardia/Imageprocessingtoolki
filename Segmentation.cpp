#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include "Segmentation.h"
using namespace std;

Segmentation::Segmentation(){

}

Segmentation::~Segmentation(){

}

Segmentation::Segmentation(Image& img) : Image(img){
  Histogram4& h = *(new Histogram4(img));
  float medianThreshold = h.task6(img);
  cout << medianThreshold;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      int brightness = (img.get_Color_x_y(i,j).get_red() + img.get_Color_x_y(i,j).get_blue() + img.get_Color_x_y(i,j).get_green())/3;
      if(brightness < medianThreshold){
        img.setColor(i,j,0,0,0);
      }
      else{
        img.setColor(i,j,255,255,255);
      }
    }
  }
}

void Segmentation::findConnectedComponents(Image& img){

  int height = img.get_height();
  int width = img.get_width();
  int connectedComponent[height][width];
  int count = 1;
  vector<vector<int> > groups;

  for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
      connectedComponent[i][j]=0;
    }
  }
  for(int i=0;i<height;i++){
    int left=0,up=0;
    for(int j=0;j<width;j++){

        if(img.get_Color_x_y(i,j).get_red() == 0){

            if(i>0){
              up = connectedComponent[i-1][j];
              if(up!=0)
                connectedComponent[i][j] = up;
            }

            if(j>0){

              left = connectedComponent[i][j-1];
              if(left!=0){
                if(connectedComponent[i][j]== 0){
                  connectedComponent[i][j] = left;
                }
                else if(left!=up){
                    mergeGroups(groups, up, left);
                }
              }
            }

            if(connectedComponent[i][j]==0){
              connectedComponent[i][j] = count;
              vector<int> temp;
              temp.push_back(count);
              groups.push_back(temp);
              count++;
            }
        }
    }
  }

  int colorArray[9][3] = {
    {255,0,0},{0,255,0},{0,0,255},{0,255,255},{255,0,255},{255,255,0},{120,120,0},{0,120,120},{120,0,120}
  };


  for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
        int connectedComponentNumber = connectedComponent[i][j];
        img.setColor(i,j,0,0,0);
        for(int m=0;m<groups.size();m++){
          for(int n=0;n<groups[m].size();n++){
              if(connectedComponentNumber == groups[m][n]){
                // Color c(colorArray[m%9][0],colorArray[m%9][1],colorArray[m%9][2]);
                // img.getPix()[i][j].setCol(c);
                img.setColor(i,j,colorArray[m%9][0],colorArray[m%9][1],colorArray[m%9][2]);
              }
          }
        }
    }
  }

}

void Segmentation::mergeGroups(vector<vector<int> > &groups, int grp1, int grp2){

      int grp1Pos = -1,grp2Pos = -1;

      for(int i=0;i<groups.size();i++){             // find out in which collection of connected groups do the new groups belong
        for(int j=0;j<groups[i].size();j++){
          if(groups[i][j]==grp1){
            grp1Pos = i;
          }
          else if(groups[i][j]== grp2){
            grp2Pos = i;
          }
        }
      }

      if(grp1Pos!=grp2Pos){               // if both the groups are not same then merge the groups

        for(int i=0;i<groups[grp2Pos].size();i++){              // copy values of group2 to group1
            groups[grp1Pos].push_back(groups[grp2Pos][i]);
        }

        groups.erase(groups.begin()+grp2Pos);               // delete group2
      }

}
