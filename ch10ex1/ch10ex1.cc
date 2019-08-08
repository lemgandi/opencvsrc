/*
   Chapter 10 exercise 1: smoothing

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
   cout << "Window commands:" << endl;
   cout << "'3' - gaussian blur kernel size 3" << endl;
   cout << "'5' - gaussian blur kernel size 5" << endl;
   cout << "'9' - gaussian blur kernel size 9" << endl;
   cout << "'+' - gaussian blur kernel size 11" << endl;
   cout << "'b' - Compare 11 gaussian blur to bilateral filter 11" << endl;
   
}



/*
Ugh. The only way to figure out if a window has been created ( and may or may not be displayed) is
a try/catch block.
*/
bool window_exists(const char *windowName)
{
   bool retVal=true;

   
   try {
      getWindowProperty(windowName,0);
   }
   catch (Exception ex) {
      retVal=false;
   }
   return retVal;
}
/*
Display a processed image in a windowname.
 */
void displayImage(Mat image,const String &windowName)
{
   if(window_exists(windowName.c_str()))
      destroyWindow(windowName);
   namedWindow(windowName,WINDOW_AUTOSIZE);
   imshow(windowName,image);
   
}

/*
Compare GaussianBlur and bilateral smooth
 */
void displayComparision(Mat theImage)
{
   Mat fiveByFive;
   String windowNameFivexFive("FiveByFiveTwice");
   Mat elevenBlurred;

   
   GaussianBlur(theImage,fiveByFive,Size(5,5),0,0);
   GaussianBlur(fiveByFive,fiveByFive,Size(5,5),0,0);
   displayImage(fiveByFive,String("FiveByFiveTwice"));
   
   // The sigmaColor and sigmaSpace params here are calculated from the formula given on p 266.
   // I think the book is wrong on this and the errata back me up.  Correct formula is:
   // sigma = (((ksize.width - 1)/2)*0.3)+0.8
   
   bilateralFilter(theImage,elevenBlurred,11,3.8,3.8);
   displayImage(elevenBlurred,String("elevenBlurred"));
   
   
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
   
   displayImage(outputImage,windowName);

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
      case 'b':
	 displayComparision(startImage);
	 break;
      default:
	 break;	 
      }
   }
   
}
