/*
 Exercise 3 from Intro to OpenCV: diff a pair of images and display results with various postprocessing

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
enum diffType {Dirty,Clean,Null};

void usage(const char *pname)
{
   cout << "Usage: " << pname << "-1 infilename -2 infilename" << endl;
   cout << "Display the differenct between two images." << endl;
   cout << "Commands: " << endl;
   cout << "'c' -- erode then dilate (clean)" << endl;
   cout << "'d' -- dilate then erode (dirty)" << endl;
}

/*
Do clean or dirty diff depending on difftype
 */
void doDiff(Mat &imageFirst, Mat & imageTwost,Mat &outputImage,diffType typeOfDiff) {
   Mat erodeKernel;
   Mat dilateKernel;

   subtract(imageFirst,imageTwost,outputImage);
   switch(typeOfDiff) {
   case Clean:
      cout << "Clean" << endl;
      erode(outputImage,outputImage,erodeKernel);
      dilate(outputImage,outputImage,dilateKernel);
      break;
   case Dirty:
      cout << "Dirty" << endl;
      dilate(outputImage,outputImage,dilateKernel);
      erode(outputImage,outputImage,erodeKernel);
      break;
   default:  // Null
      cout << "Null" << endl;
   }
   
}


int main(int argc, char *argv[])
{
   const char *optString="1:2:";
   char opt;

   char *img1FN=0;
   char *img2FN=0;
   
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case '1':
	 img1FN=optarg;
	 break;
      case '2':
	 img2FN=optarg;
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
   Mat imageFirst = imread(img1FN,IMREAD_COLOR);
   if(imageFirst.empty()) {
      cout << "Oops. Cannot read [" << img1FN << "]" << endl;
      usage(argv[0]);
      exit(1);
      
   }
   Mat imageTwost = imread(img2FN,IMREAD_COLOR);
   if(imageTwost.empty()) {
      cout << "Oops. Cannot read [" << img2FN << "]" << endl;
      usage(argv[0]);
      exit(1);
   }
   Mat imageSubtracted;
   char c=0;
   const char *windowName="Subtracted";
   namedWindow(windowName,WINDOW_AUTOSIZE);
   diffType whatToDo=Null;
   
   while( 27 != c) {     
      switch(c) {
      case 'c':
	 whatToDo=Clean;
	 break;
      case 'd':
	 whatToDo=Dirty;
	 break;
      case 'n':
	 whatToDo=Null;
      }
      doDiff(imageFirst,imageTwost,imageSubtracted,whatToDo);
      imshow(windowName,imageSubtracted);
      c=(char)waitKey();
   }
}
