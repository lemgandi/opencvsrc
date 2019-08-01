/*
 Chapter 10 exercise 2 from Intro to OpenCV: 100 x 100 image

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

void usage(const char *pname)
{
   cout << "Usage: " << pname << "-a|b|c" << endl << endl;
   cout << "Experiment with smoothing filters on a 101x101 pixel image of all zeros" << endl;
   cout << "with a single center pixel set to 255" << endl;
   cout << "'-a': 5x5 gaussian filter" << endl;
   cout << "'-b': 9x9 gaussian filter" << endl;
   cout << "'-c': 5x5 gaussian filter applied twice" << endl;
}

int main(int argc, char *argv[])
{
   const char *optString="abc";
   char opt;
   
   bool aFilter=false;
   bool bFilter=false;
   bool cFilter=false;
   bool optOK=false;
   
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'a':
	 aFilter=true;
	 optOK=true;
	 break;
      case 'b':
	 bFilter=true;
	 optOK=true;
	 break;
      case 'c':
	 cFilter=true;
	 optOK=true;
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   if(! optOK) {
      usage(argv[0]);
      exit(1);
   }
   Mat myImage = Mat::zeros(100,100,CV_8U);
   // Make the blob a little bigger so I can see it on my tiny screen.
   myImage.at<uchar>(50,50)=255;
   myImage.at<uchar>(49,50)=255;
   myImage.at<uchar>(51,50)=255;
   myImage.at<uchar>(50,49)=255;
   myImage.at<uchar>(50,51)=255;
   
   Mat blurredImage;
   if(aFilter) 
      GaussianBlur(myImage,blurredImage,Size(5,5),0,0);
   if(bFilter)
      GaussianBlur(myImage,blurredImage,Size(9,9),0,0);
   if(cFilter) {
      GaussianBlur(myImage,blurredImage,Size(5,5),0,0);
      GaussianBlur(blurredImage,blurredImage,Size(5,5),0,0);
   }
      
   const char *oWindowName="Original";
   namedWindow(oWindowName,WINDOW_AUTOSIZE);
   imshow(oWindowName,myImage);
   const char *blWindowName="Blurred";
   namedWindow(blWindowName,WINDOW_AUTOSIZE);
   imshow(blWindowName,blurredImage);
   
   char keyValue=0;
   while('q' != keyValue) {
      keyValue=waitKey(0);
   }
   destroyWindow(oWindowName);
   destroyWindow(blWindowName);
}
