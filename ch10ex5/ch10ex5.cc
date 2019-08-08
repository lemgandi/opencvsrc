/*
    Chapter 10 extercise 5, greyscale outlines.

    This file is part of opencvsrc.
    opencvsrc is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    opencvsrc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with opencvsrc.  If not, see <http://www.gnu.org/licenses/>.

 */

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <getopt.h>

using namespace std;
using namespace cv;

enum diffType {Absolute,Binary,MopOpen,EXor};

void usage(const char *pname)
{
      cout << "Usage: " << pname << "-1 infilename -2 infilename [-t threshval]" << endl;
   cout << "Display the difference between two images." << endl;
   cout << "threshval is the threshold value for noise cancellation." << endl;
   cout << "Commands: " << endl;
   cout << "'a' absolute value of difference" << endl;
   cout << "'t' Binary threshold" << endl;
   cout << "'o' CV_MOP_OPEN" << endl;
   cout << "'x' Erosion and XOR" << endl;

}

/*
Do difference operation to display object
*/
void doDiff(Mat &imageFirst,Mat &imageTwost,Mat &outputImage,diffType whatToDo,double threshVal)
{
   Mat morphArray;
   Mat eroded;
   
   subtract(imageFirst,imageTwost,outputImage);
   switch(whatToDo) {
   case Absolute: // Just show untreated subtracted image
      cout << "Absolute" << endl;
      break;
   case Binary:
      threshold(outputImage,outputImage,threshVal,255,THRESH_BINARY);
      cout << "Binary" << endl;
      break;
   case MopOpen:
      threshold(outputImage,outputImage,threshVal,255,THRESH_BINARY);
      morphologyEx(outputImage,outputImage,MORPH_OPEN,morphArray);
      cout << "MORPH_OPEN" << endl;
      break;
   default:  //EXor
      cout << "Erode and xor" << endl;
      erode(outputImage,eroded,morphArray);
      bitwise_xor(outputImage,eroded,outputImage);
      break;
   }
}
   
int main(int argc, char *argv[])
{
   const char *optString="1:2:t:";
   char opt;
   
   char *img1FN=0;
   char *img2FN=0;
   double threshVal=40;
   istringstream threshConverter;
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
	       case '1':
	 img1FN=optarg;
	 break;
      case '2':
	 img2FN=optarg;
	 break;
      case 't':
	 threshConverter.str(optarg);
	 threshConverter >> threshVal;
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   if((0 == img1FN) || (0 == img2FN)) {
      cout << "I need two filenames." << endl;
      usage(argv[0]);
      exit(1);     
   }
   Mat imageFirst = imread(img1FN,IMREAD_GRAYSCALE);
   if(imageFirst.empty()) {
      cout << "Oops. Cannot read [" << img1FN << "]" << endl;
      usage(argv[0]);
      exit(1);
      
   }
   Mat imageTwost = imread(img2FN,IMREAD_GRAYSCALE);
   if(imageTwost.empty()) {
      cout << "Oops. Cannot read [" << img2FN << "]" << endl;
      usage(argv[0]);
      exit(1);
   }
   Mat imageSubtracted;
   char c=0;
   const char *windowName="Subtracted";
   namedWindow(windowName,WINDOW_AUTOSIZE);   
   diffType whatToDo=Absolute;
   
   while( 27 != c) {     
      switch(c) {
      case 'a':
	 whatToDo=Absolute;
	 break;
      case 't':
	 whatToDo=Binary;
	 break;
      case 'o':
	 whatToDo=MopOpen;
	 break;
      case 'x':
	 whatToDo=EXor;
	 break;
      default:
	 break;
      }
      doDiff(imageFirst,imageTwost,imageSubtracted,whatToDo,threshVal);
      imshow(windowName,imageSubtracted);
      c=(char)waitKey();
   }   
}
