#include "Tasks.h"

using namespace std;

int main(int argc, char* argv[]) {
  // cout << "sup";
  if(argc != 2) {
    cout<<"Wrong imput format"<<endl;
    cout<<"Usage : <executable> <input filename.ppm>"<<endl;
    return 0;
  }
  string input;
  cout<<"Our group task ID combination is: 1, 3 ,4 ,5, 6, 7"<<endl;
  getline(cin, input);
  vector<int> ip = getInput(input);
  for(int i=0;i<ip.size();i++) {
    switch(ip[i]) {
      case 1:
        try {
          IMT2016012(argv[1]);
        }
        catch(int e) {
          cout<<"An exception occured in task 1 " << e << endl;
        }
        break;
      case 3:
        try {
          IMT2016066(argv[1]);
        }
        catch(int e) {
          cout<<"An exception occured in task 3 " << e << endl;
        }
        break;
      case 4:
        try {
          IMT2016126(argv[1]);
        }
        catch(int e) {
          cout<<"An exception occured in task 4 " << e << endl;
        }
        break;
      case 5:
        try {
          IMT2016107(argv[1]);
        }
        catch(int e) {
          cout<<"An exception occured in task 5 " << e << endl;
        }
        break;
      case 6:
        try {
          IMT2016040(argv[1]);
        }
        catch(int e) {
          cout<<"An exception occured in task 6 " << e << endl;
        }
        break;
      case 7:
        try {
          IMT2016087(argv[1]);
        }
        catch(int e) {
          cout<<"An exception occured in task 7 " << e << endl;
        }
        break;
      default:
        cout<<"Not a valid input";
    }
  }
  return 0;
}
