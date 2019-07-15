/*
 Exercise 3 from Intro to OpenCV: write downsampled avi from camera to disk

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

const char * defaultImgFN="../images/landscape.jpg";

void usage(const char *pname)
{
   cout << "Usage: " << pname << "-i imagename" << endl;
   cout << "imagename defaults to " << defaultImgFN << endl;
}
// Display an image smoothed in various ways.
// Note that theImage is passed on the stack, but this
// just passes the header,not the whole shebang.
void displaySmoothed(int windowSize,Mat theImage)
{
   Mat outputImage;
   
   GaussianBlur(theImage,outputImage,Size(windowSize,windowSize),0,0);

   stringstream theName;
   theName << "Blur" << windowSize;
   String windowName(theName.str());
   try {   
      if(-1 != getWindowProperty(windowName,0))
	 destroyWindow(windowName);
   }
   catch(Exception ex) {
      // If the window does not exist, we are still ok. If it _does_ exist, we kill it before recreating it.
   }
   
   
   namedWindow(windowName,WINDOW_AUTOSIZE);
   imshow(windowName,outputImage);
}

int main(int argc, char *argv[])
{
   const char *optString="i:";
   char opt;
   string imageFN(defaultImgFN);
   
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'i':
	 imageFN=optarg;
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   cout << "boop" << endl;
   
   Mat startImage=imread(imageFN,IMREAD_COLOR);
//   Mat reserveImage=startImage.clone();

   if(startImage.empty()) {
      cerr << "Cannot read image in [" << imageFN << "]" << endl;
      exit(1);
   }
   
   const char *OWindowName="Original";
   namedWindow(OWindowName,WINDOW_AUTOSIZE);
   char c=0;
   while(27 != c) {
      imshow(OWindowName,startImage);
      c=waitKey(0);
      switch(c) {
      case 27:
	 break;
      case '3':
	 displaySmoothed(3,startImage);
	 break;
      case '5':
	 displaySmoothed(5,startImage);
	 break;
      case '9':
	 displaySmoothed(9,startImage);
	 break;
      case '+':
	 displaySmoothed(11,startImage);
	 break;
      default:
	 break;	 
      }
   }
   
}
