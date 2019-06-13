/*
 Exercise 2 chapter 8: Draw a box and compute pixel color histogram inside it.

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

#include <getopt.h>

using namespace std;
using namespace cv;

#define DEFAULTFN "../images/lena.jpg"
#define CHS_SUCCESS 0
#define CHS_FAILURE -1
#define CHS_FINISHED 1

// Globals for mouse callback routine


/*
Usage message
 */
void usage(const char *pName)
{
   cout << "Usage: " << pName << " [-i imagename]" << endl;
   cout << "Default imagename is " << DEFAULTFN << endl;
   cout << "Draw a box and compute pixel histogram iside it.  'r' will redraw clean; <esc> will exit." << endl;
}

/*
Draw a baox on the image
*/
void drawTheBox(Mat &image, Rect box,Scalar color)
{
   rectangle( image, box.tl(),box.br(), color);
}

/*
  Mouse callback -- draw rectangle 
 */
void drawRect(int event,int x,int y,int flags,void *param)
{
   Mat &thePicture = *(Mat *)param;
   static Rect theBox;
   static bool drawingBox = false;

   Vec3b pixelValues = thePicture.at<Vec3b>(x,y);
   
   switch(event) {
   case EVENT_MOUSEMOVE:
      if(drawingBox) {
	 theBox.width = (x - theBox.x);
	 theBox.height = (y - theBox.y);
      }
      break;
   case EVENT_LBUTTONDOWN:
      drawingBox = true;
      theBox = Rect(x,y,0,0);
      break;
   case EVENT_LBUTTONUP:
      drawingBox = false;
      if(0 > theBox.width) {
	 theBox.x += theBox.width;
	 theBox.width = -theBox.width;
      }
      if( 0 > theBox.height) {
	 theBox.y += theBox.height;
	 theBox.height = -theBox.height;
      }
      drawTheBox(thePicture,theBox,Scalar(0,0,255));
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
   
   if(theImage.empty()) {
      cerr << "Cannot read image in [" << inFileName << "]" << endl;
      status=CHS_FAILURE;
   }
   
   reservedImage = theImage.clone();
   if(CHS_SUCCESS == status ) {
      char c=0;
      namedWindow(windowName,WINDOW_AUTOSIZE);
      setMouseCallback(windowName,drawRect,&theImage);
      imshow(windowName,theImage);
      while((27 != c) && (CHS_SUCCESS == status)) {
	 imshow(windowName,theImage);
	 c = waitKey(1);
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
