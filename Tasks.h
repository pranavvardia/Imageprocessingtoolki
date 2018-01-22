#ifndef Tasks_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Histogram.h"
#include "Segmentation.h"
#include "CompositeImage.h"
#include "xAxisReflection.h"
#include "GaussianFilter.h"
#include "Task1.h"
#include "ScaledImage.h"
#include "Histogram4.h"
#include "Image.h"

using namespace std;

vector<int> getInput(string s);

void IMT2016012(char* fname);
void IMT2016040(char* fname);
void IMT2016066(char* fname);
void IMT2016087(char* fname);
void IMT2016107(char* fname);
void IMT2016126(char* fname);

#endif
