/*
 Exercise 7 chapter 10:  smooth blue only

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
   cout << "Usage: " << pname << " -i imagename -s kernelsize" << endl;
   cout << "Smooth blue in picture." << endl;
   cout << "'-i  Image name to smooth" << endl;
   cout << "'-s' kernelsize for smoothing operation" << endl;
   
}

int main(int argc, char *argv[])
{
   const char *optString="i:s:";
   char opt;
   String imageFN;
   int kernelsize=7;
   istringstream converter;
   int theSize=7;
   
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'i':
	 imageFN=optarg;
	 break;
      case 's':
	 converter.str(optarg);
	 converter >> theSize;
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   
   if ( imageFN.empty()) {
      cout << "Please supply an image fiilename." << endl;
      exit(1);
   }
   
   Mat theImage;
   theImage = imread(imageFN,IMREAD_COLOR);
   if(theImage.empty()) {
      cout << "Cannot read image in [" << imageFN << "]" << endl;
      usage(argv[0]);
      exit(1);
   }
   cout << "theSize: " << theSize << endl;
   
   Mat smoothedImage = theImage.clone();
   vector<Mat> bgrImages;
   split(smoothedImage,bgrImages);
   blur(bgrImages[0],bgrImages[0],Size(theSize,theSize));
   merge(bgrImages,smoothedImage);
   
   
   const char * rawWindowName = "Raw";
   namedWindow(rawWindowName,WINDOW_AUTOSIZE);
   imshow(rawWindowName,theImage);

   const char *smoothedWindowName="BlueSmoothed";
   namedWindow(smoothedWindowName,WINDOW_AUTOSIZE);
   imshow(smoothedWindowName,smoothedImage);

   waitKey(0);
   destroyAllWindows();
   exit(0);

}
