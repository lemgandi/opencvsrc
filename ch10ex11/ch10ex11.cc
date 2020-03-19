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


string type2str(int type) {
   string r;

   uchar depth = type & CV_MAT_DEPTH_MASK;
   uchar chans = 1 + (type >> CV_CN_SHIFT);

   switch ( depth ) {
   case CV_8U:  r = "8U"; break;
   case CV_8S:  r = "8S"; break;
   case CV_16U: r = "16U"; break;
   case CV_16S: r = "16S"; break;
   case CV_32S: r = "32S"; break;
   case CV_32F: r = "32F"; break;
   case CV_64F: r = "64F"; break;
   default:     r = "User"; break;
   }

   r += "C";
   r += (chans+'0');

   return r;
}

/*
Given mask, original, and greyscale, copy greyscale to original where mask > 0.
*/
void doMask ( Mat & input, Mat & mask, Mat & output,int gsVal )
{
   int irow;
   int icol;
   uchar pixValue;



   output = input.clone();
      

   for (irow=0; irow < mask.rows; ++irow) {
      for (icol=0; icol < mask.cols;++icol) {
         pixValue = mask.at<uchar>(irow,icol);
	 if (0 == pixValue)
	    output.at<uchar>(irow,icol) = (uchar)gsVal;
      }
   }
   
}


/*
Usage Message
*/
void usage(const char *pname)
{
   cout << "Usage: " << pname << "-i imagename [ -t {r|e|c} ] [ -s {kernelsize} ] [ -g {greyscalevalue} ] " << endl;
   cout << "Load greyscale image and play with Tophat." << endl;
   cout << "imagename is the image; -t gives the kernel shape ( r=MORPH_RECT,e=MORPH_ELLIPSE,c=MORPH_CROSS,default is MORPH_RECT)" << endl;
   cout << "kernelsize is an odd integer; default is 9" << endl;
   cout << "greyscalevalue is arbitrary value to copy from tophat mask to original (must be 0-255)" << endl;
}



/*
Get kernel shape from argument.
*/
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
   const char *optString="i:t:s:g:";
   char opt;
   char *imageFN=0;
   int kShape=MORPH_RECT;
   int kSize=9;
   int gsVal=180;
   
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
      case 'g':
	 digitsConverter.str(optarg);
	 digitsConverter >> gsVal;
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
   if ( grayscaleImage.empty()) {
	 cout << "Oops.  Cannot read [" << imageFN << "]" << endl;
	 usage(argv[0]);
	 exit(1);
   }
      
   Mat openedImage;
   Mat kernel=getStructuringElement(kShape,Size(kSize,kSize));
   morphologyEx(grayscaleImage,openedImage,MORPH_OPEN,kernel);
   Mat topHatImage=grayscaleImage - openedImage;

   
   Mat topHatMask;
   threshold(topHatImage,topHatMask,0,255,THRESH_BINARY);

   const char *maskName="Mask";
   namedWindow(maskName,WINDOW_AUTOSIZE);
   imshow(maskName,topHatMask);

   Mat tophatFiltered;

   doMask(grayscaleImage,topHatMask,tophatFiltered, gsVal);

   const char*thFilteredName="TopHatFiltered";
   namedWindow(thFilteredName,WINDOW_AUTOSIZE);
   imshow(thFilteredName,tophatFiltered);
   
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
