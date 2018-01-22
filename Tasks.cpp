#include "Tasks.h"

using namespace std;

class Task5{
private:
	Image A;
public:
	Task5(Image img){
		A = img;
	}
	Image get_image(){
		return A;
	}

};

vector <int> getInput(string s){
  vector <int> l;
  for(int i=0;i<s.size();i++){
    if(s[i] != ' '){
      l.push_back(s[i]-'0');
    }
  }
  return l;
}

void IMT2016012(char* fname){
  //Redirecting given image/file to input stream.
    std::ifstream in(fname);
    std::streambuf *cinbuf = std::cin.rdbuf();
    std::cin.rdbuf(in.rdbuf());
    //Redirecting output image/file to output stream.
    // std::ofstream out("outputnormal.ppm");
    std::streambuf *coutbuf = std::cout.rdbuf();
    // std::cout.rdbuf(out.rdbuf());

    //Reading Encoding.
    std::string encoding;
    std::cin >> encoding;

    //Reading width, height, maxval.
    int width, height, maxval;
    std::cin >> width >> height >> maxval;

    //Writing encoding, all related values to the output file.
    //std::cout << encoding << std::endl << width << std::endl
      //  << height << std::endl << maxval << std::endl;

    Task1 t1(width, height);
    Image *itask1 = &t1;
    std::cin >> *itask1;

    //std::cout << t1;


    Task1 t2(width, height);
    Image *itask2 = &t2;
    *itask2 = *itask1;

    //Circles at different locations.
    t2.makeCircle(floor(width * 0.5), floor(height * 0.5));
    t2.makeCircle(floor(width * 0.125), floor(height * 0.125));
    //std::cout << t2;

    Task1 t3(width, height);
    t3.imageClip(itask1, itask2); //CLIP.
    //std::cout << t3;

    //TILL CLIP - OK!

    Task1 t4(width, height);
    //Gives the reverse image.
    t4.reverseImage(*itask1);   //REVERSE IMAGING.
    //std::cout << t4;
    //t4.imageStencil(itask1, itask2);
    //std::cout << t4;
    //std::cout << t2;

    Task1 t5(width, height);
    t5.imageStencil(&t4, itask2); //STENCIL.

    std::cin.rdbuf(cinbuf);
    // std::cout.rdbuf(coutbuf);

    in.close();
    // out.close();

    std::ofstream outfinal("output_task1_IMT2016012.ppm");
    coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(outfinal.rdbuf());

    std::cout << encoding << std::endl << width << std::endl
        << height << std::endl << maxval << std::endl;

    //std::cout << t3.get_height() << " " << t5.get_height() << std::endl;
    CompositeImage c(t3, t5, 0.3);
    //Image t = c.getImage1();
    std::cout << c;
    outfinal.close();
    std::cout.rdbuf(coutbuf);
}

void IMT2016040(char* fname){
  ifstream file(fname);
  string mode;
  int width,ht,max_val;
  file>>mode>>width>>ht>>max_val;
  Image *input = new Image(width,ht);
  file>>*input;
  Segmentation *sg1 = new Segmentation(*input);
	// cout << "sup1" << endl;
  sg1->findConnectedComponents(*input);
  ofstream output("output_task6_IMT2016040.ppm");
  output<<mode<<endl;
  output <<width<<" "<<ht<<endl;
  output << max_val<<endl;
  output<<*input;
}

void IMT2016066(char* fname){
  ifstream input;
  ofstream output1,output2;
  input.open(fname);
  string type;
  int w,h,max;
  input>>type>>w>>h;
  input>>max;
  Image *img = new Image(w,h);
  input>>(*img);
  xAxisReflection *xref = new xAxisReflection((*img));
  GaussianFilter *g = new GaussianFilter(*xref);
  output1.open("output_task3_IMT2016066_gaussian.ppm");
  output1<<type<<"\n";
  output1<<w<<" "<<h<<"\n";
  output1<<max<<"\n";
  output1<<(*g);
  output2.open("output_task3_IMT2016066_Final.ppm");
  CompositeImage * res = new CompositeImage((*g),(*xref),0.6);
  output2<<type<<"\n";
  output2<<w<<" "<<h<<"\n";
  output2<<max<<"\n";
  output2<<(*res);
}

void IMT2016087(char* fname){
  string type;
  int height,width;
	int peak;
    // istream infile("fruit.ppm",ios::out);
	ifstream infile;
	infile.open(fname);
    infile >> type;
	infile >> width >> height;
	infile >> peak;
	Image* fruit =new Image (width,height);
	infile >> *fruit;
	ScaledImage* scam = new ScaledImage();
	vector<Image> vec = scam->Img(*fruit);
	// Image i1(width,height);
	// Image i2(width,height);
	// Image i3(width,height);
	Image i4(width,height);
  CompositeImage comp1(vec[0],vec[1],0.5);
  CompositeImage comp2(vec[2],vec[3],0.5);
  CompositeImage comp3(comp1,comp2,0.5);
	// i1 = vec[0] % vec[1];
	// i2 = vec[2] % vec[3];
	// i3 = i1 % i2;
	i4=scam->crop(comp3);
	ofstream outfile("output_task7_IMT2016087.ppm");
	outfile << type << endl;
	outfile << width << " " << height << endl;
	outfile << peak << endl;
	outfile << i4;
}

void IMT2016107(char* fname){
  ifstream fin(fname);
	string mode;
	int w, h, max;
	fin>>mode>>w>>h>>max;
	Image img(w,h);
	fin>>img;
	// cout<<img<<endl;
	Task5 t(img);
	Histogram4 histo(img);
	vector<int> minimas = histo.return_minimas();
	int T1 = minimas[1];
	int T2 = minimas[2];
	int Threshold1 = T1;
	int Threshold2 = T2;
	Image temp = t.get_image();
	// cout<<temp<<endl;
	// cout<<T1<<" "<<T2<<endl;
	Image img1(t.get_image().get_width(),t.get_image().get_height());
	if(Threshold1!=-1){
		Image img12 = t.get_image();
		for(int i=0; i<img12.get_height(); i++){
			// cout<<i<<endl;
			for(int j=0; j<img12.get_width(); j++){
				// cout<<i<<" "<<j<<endl;
				Color col = img.get_Color_x_y(i,j);
			  int brightness = (col.get_red() + col.get_blue() + col.get_green())/3;
			  if(brightness < Threshold1){
					img1.setColor(i,j,0,0,255);
			  }
			  else{
					img1.setColor(i,j,255,255,255);
			  }
			}
		}
	}
	else{
		img1 = img.reflectionAboutY();
	}
	Image img2(t.get_image().get_width(),t.get_image().get_height());
	if(Threshold2!=-1){
		Image img13 = t.get_image();
		for(int i=0; i<img13.get_height(); i++){
			for(int j=0; j<img13.get_width(); j++){
				Color col1 = img.get_Color_x_y(i,j);
			  int brightness = (col1.get_red() + col1.get_blue() + col1.get_green())/3;
			  if(brightness < Threshold2){
				img2.setColor(i,j,255, 255, 0);
			  }
			  else{
				img2.setColor(i,j,255,255,255);
			  }
			}
		}
	}
	else{
		img2 = img.reflectionAboutX();
	}
	// cout<<img1<<endl;
	// cout<<img2<<endl;
	CompositeImage ans(img1,img2,0.2);
	// cout<<ans<<endl;
	ofstream fout("output_task5_IMT2016107.ppm");
	fout<<"P3"<<endl;
	fout<<ans.get_width()<<" "<<ans.get_height()<<endl;
	fout<<ans;
	fout.close();
}

void IMT2016126(char* fname){
  Image img(fname);
  Histogram4 hist(img);
	hist.task4(img);
}
