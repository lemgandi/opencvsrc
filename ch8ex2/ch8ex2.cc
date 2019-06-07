/*
 Exercise 2 chapter 8: pixel values at mouse location

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

#define DEFAULTFN "../images/lena.jpg"
#define CHS_SUCCESS 0
#define CHS_FAILURE -1
#define CHS_FINISHED 1

void usage(const char *pName)
{
   cout << "Usage: " << pName << " [-i imagename]" << endl;
   cout << "Default imagename is " << DEFAULTFN << endl;
}
/*
  Callback where we actually display the params.
 */
void write_coords(int event,int x,int y,int flags,void *param)
{
   Mat &thePicture = *(Mat *)param;

   Vec3b pixelValues = thePicture.at<Vec3b>(x,y);
   switch(event) {
   case EVENT_LBUTTONDOWN:
      cout << "Red: " << static_cast<unsigned>(pixelValues[2]) <<
	 " Green: " << static_cast<unsigned>(pixelValues[1]) << " Blue: " << static_cast<unsigned>(pixelValues[0]) << endl;
      break;
   default:
      break;
   }
   
   
   return;
}

// Main Line
int main(int argc, char *argv[])
{
   const char *optString="i:";
   char opt;   
   char inFileName[80];
   Mat theImage;
   int status=CHS_SUCCESS;
   const char *windowName="PixelValues";
   Mat reservedImage;
   
   memset(inFileName,0,sizeof(inFileName));
   strcpy(inFileName,DEFAULTFN);

      
   while((opt=getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'i':
	 strncpy(inFileName,optarg,sizeof(inFileName)-1);
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   theImage = imread(inFileName,IMREAD_COLOR);
   reservedImage = Mat(theImage);
   
   if(theImage.empty()) {
      cerr << "Cannot read image in [" << inFileName << "]" << endl;
      status=CHS_FAILURE;
   }
   
   if(CHS_SUCCESS == status ) {
      char c=0;
      namedWindow(windowName,WINDOW_AUTOSIZE);
      setMouseCallback(windowName,write_coords,&theImage);
      imshow(windowName,theImage);
      while((27 != c) && (CHS_SUCCESS == status)) {
	 imshow(windowName,theImage);
	 c = waitKey(0);
	 switch(c) {
	 case 27:
	    status = CHS_FINISHED;
	    break;
	 case 'r': // Redraw the window with no text visible.
	    reservedImage.copyTo(theImage);
	    break;
	 default:
	    break;
	 }
      }
   }
   
}
