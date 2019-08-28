/*
 Exercise 

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
   cout << "Usage: " << pname << " -1 imagefile -2 imagefile [-t threshold -l lowthresh -h highthresh]" << endl;
   cout << "Display a mask of the difference between two images." << endl;
   cout << "threshold is the threshold value for noise cancellation" << endl;
   cout << "lowthresh is the low threshold value for floodFill." << endl;
   cout << "highthresh is the high threshold value for floodFill." << endl;
   cout << "(lowthresh must be equal to or smaller than highthresh)" << endl;
}

/* 
Convert difference between two images into a mask
*/
void doProcessing( Mat &imageOne, Mat &imageTwo, Mat &outputImage, double thresholdValue,int lothresh, int highthresh,uchar passedV,bool verbose)
{
   Mat eroded;
   Mat morphArray;

   
   subtract(imageOne,imageTwo,outputImage);
   erode(outputImage,eroded,morphArray);
   bitwise_xor(outputImage,eroded,outputImage);
   
   threshold(outputImage,outputImage,thresholdValue,255,THRESH_BINARY_INV);

   const char *checkWindowName="Check";
   namedWindow(checkWindowName,WINDOW_AUTOSIZE);
   imshow(checkWindowName,outputImage);
   imwrite("./testimage.jpg",outputImage);

   Point prevPoint(0,0);
   Point seedPoint(0,0);
   int irow;
   int icol;
   uchar pixValue=0;
   int filledPixelCount = 0;
   int largestPC = 0;
   // int flagval=4+65280+FLOODFILL_FIXED_RANGE;
   // int flagval = 4 | (255 < 8 ) | FLOODFILL_FIXED_RANGE;
   int flagval=4;
   
   
   for(irow=0; irow < outputImage.rows; ++irow) {
      for (icol=0;icol < outputImage.cols; ++icol) {
	 pixValue=outputImage.at<uchar>(icol,irow);
	 if((passedV == pixValue)) {
	    seedPoint = Point(icol,irow);
	    if(verbose)
	       cout << "seedPoint at " << seedPoint << " PrevPoint at: " << prevPoint << endl;	    
	    filledPixelCount = floodFill(outputImage,seedPoint,Scalar(100,100,100),0,
					 Scalar(lothresh,lothresh,lothresh),
					 Scalar(highthresh,highthresh,highthresh),flagval);
	    if(verbose)
	       cout << "filledPixelCount: " << filledPixelCount << endl;
	    if((largestPC < filledPixelCount)) {
	       if(verbose)
		  cout << "largestPC: " <<  largestPC << " filledPixelCount: " << filledPixelCount << endl;
	       if(0 != largestPC)
		  floodFill(outputImage,prevPoint,Scalar(100,100,100),0,Scalar(lothresh,lothresh,lothresh),
			    Scalar(highthresh,highthresh,highthresh),flagval);
	       prevPoint=seedPoint;
	       largestPC = filledPixelCount;
	    }
	    else  {
	       int fpc;
	       fpc = floodFill(outputImage,seedPoint,Scalar(100,100,100),0,Scalar(lothresh,lothresh,lothresh),
			       Scalar(highthresh,highthresh,highthresh),flagval);
	       if(verbose)
		  cout << "Floodfill: " << seedPoint <<  " pixelcount: " << fpc << endl;
	    }
	 }
      }
   }
   if(verbose)
      cout << "Largest filled region: " << largestPC << " Largest Point: " << seedPoint << endl;
   
}

int main(int argc, char *argv[])
{
   const char *optString="1:2:t:l:h:p:v";
   char opt;
   
   char *img1FN=0;
   char *img2FN=0;
   double threshVal=40;
   istringstream threshConverter;
   int lothresh=0;
   int highthresh=0;
   uchar pixelV = 255;
   bool verbose = false;
   
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
      case 'l':
	 threshConverter.str(optarg);
	 threshConverter >> highthresh;
	 break;
      case 'h':
	 threshConverter.str(optarg);
	 threshConverter >> lothresh;
	 break;
      case 'p':
	 threshConverter.str(optarg);
	 threshConverter >> pixelV;
	 break;
      case 'v':
	 verbose=true;
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
   Mat maskImage;
   /*  
   if(lothresh > highthresh) {
      cout << "Low threshold cannot be larger than high threshold." << endl;
      usage(argv[0]);
      exit(1);
   }
   */
   doProcessing(imageFirst,imageTwost,maskImage,threshVal,lothresh,highthresh,pixelV,verbose);
   char c=0;
   const char *windowName="Mask";
   namedWindow(windowName,WINDOW_AUTOSIZE);
   imshow(windowName,maskImage);
   c=(char)waitKey();
   
}
