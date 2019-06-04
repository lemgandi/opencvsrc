/*
 Exercise 3 chapter 8:  video transformation

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
#include <fstream>

#include <getopt.h>

using namespace std;
using namespace cv;

void usage(char * pname,char *deftFN) {
   cout << "Usage: " << pname << " [-s] [-f filename]" << endl;
   cout << "Display video in original, grayscale, and canny() transformations" << endl;
   cout << "-s flag specifies a single window, otherwise in three different windows" << endl;
   cout << "-f specifies input video filename; default is " << deftFN << endl;
   
}

int main(int argc, char *argv[])
{
   char optString[]={"sf:"};
   char opt;
   bool singleWindow=false;
   char defaultFN[] = {"../images/Otto_first_steps.mp4"};
   char infileName[80];
   int  status = 0;
   VideoCapture inputFrames;

   memset(infileName,0,sizeof(infileName));
   strncpy(infileName,defaultFN,sizeof(infileName)-1);
   
   while((opt=getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 's':
	 singleWindow=true;
	 break;
      case 'f':
	 strncpy(infileName,optarg,sizeof(infileName)-1);
	 break;
      default:
	 usage(argv[0],defaultFN);
	 return 1;
      }
   }
   cout << "Args: " << "singleWindow is " << singleWindow << endl;
   cout << "infileName is " << infileName << endl;
  

   inputFrames.open(infileName);
   
   if(! inputFrames.isOpened() ) {
      cout << "Something Bad Happened trying to open " << infileName << endl;
      usage(argv[0],defaultFN);
      status = -1;
   }
   
   if(0 == status) {
      
      Mat natFrame;
      Mat greyscaleFrame;
      Mat cannyFrame;

      char natName[] = {"natural"};
      char greyName[] = {"greyscale"};
      char cannyName[] = {"canny"};

      namedWindow("foo",cv::WINDOW_AUTOSIZE);
      namedWindow(natName,cv::WINDOW_AUTOSIZE);
      namedWindow(greyName,cv::WINDOW_AUTOSIZE);
      namedWindow(cannyName, cv::WINDOW_AUTOSIZE);
    
      
      inputFrames >> natFrame;
      // imshow("foo",natFrame);
      
      while(! natFrame.empty()) {
	 cvtColor(natFrame,greyscaleFrame,CV_BGR2GRAY);
	 Canny(natFrame,cannyFrame,5.0,7.0);
	 imshow(natName,natFrame);
	 imshow(cannyName,cannyFrame);
	 imshow(greyName,greyscaleFrame);
	 
	 inputFrames >> natFrame;
      }
   }
   
   // VideoCapture object automagically closed when its destructor is called.
}
