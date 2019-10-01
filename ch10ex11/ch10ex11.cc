/*
 Exercise 11 chapter 10.  Play with tophat filter.

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
   cout << "Usage: " << pname << "-i imagename" << endl;
   cout << "Load greyscale image and play with Tophat." << endl;
}

int getKshape(const char *kshapeT) {
   int retVal=-1;
   int status=0;
   
   if(strlen(kshapeT) > 1) 
      status=-1;
   
   if(0 == status) {
      switch(*kshapeT) {
      case 'r':
	 retVal=MORPH_RECT;
	 break;
      case 'e':
	 retVal=MORPH_ELLIPSE;
	 break;
      case 'c':
	 retVal=MORPH_CROSS;
	 break;
      default:
	 break;
      }
   }
   
   if(-1 == retVal) 
      cout << "kernel shape must be one of 'r','e', or 'c'." << endl;	    
   return retVal;
}
int main(int argc, char *argv[])
{
   const char *optString="i:t:s:";
   char opt;
   char *imageFN=0;
   int kShape=MORPH_RECT;
   int kSize=9;
   istringstream digitsConverter;
   
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'i':
	 imageFN=strdup(optarg);
	 break;
      case 's':
	 digitsConverter.str(optarg);
	 digitsConverter >> kSize;
	 break;
      case 't':
	 kShape=getKshape(optarg);
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   if(! imageFN) {
      usage(argv[0]);
      exit(1);
   }
   
   if(! kSize % 2) {
      cout << "Kernel size must be odd " << kSize << " is not." << endl;
      usage(argv[0]);
      exit(2);
   }
   
   if(-1 == kShape) {
      usage(argv[0]);
      exit(3);
   }
   Mat grayscaleImage = imread(imageFN,IMREAD_GRAYSCALE);
   Mat openedImage;
   Mat kernel=getStructuringElement(kShape,Size(kSize,kSize));
   morphologyEx(grayscaleImage,openedImage,MORPH_OPEN,kernel);
   Mat topHatImage=grayscaleImage - openedImage;
   
   const char *originalName="Original";
   namedWindow(originalName, WINDOW_AUTOSIZE);
   imshow(originalName,grayscaleImage);
   
   const char *openedName="Opened";
   namedWindow(openedName,WINDOW_AUTOSIZE);
   imshow(openedName,openedImage);

   const char *topHatName="topHat";
   namedWindow(topHatName,WINDOW_AUTOSIZE);
   imshow(topHatName,topHatImage);
   
   char c;   
   c=(char)waitKey();
}
