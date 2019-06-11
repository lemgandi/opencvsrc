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
#include <sstream>
#include <string>

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
   cout << "Display color values at pixel mouse cursor is over.  'r' will redraw clean; <esc> will exit." << endl;
}
void writeValuesToMat(Mat &theMat,Point currentLoc,Vec3b pixelValues)
{
   string myText;
   ostringstream textStream(myText);
   
   textStream << "Red: " << static_cast<int>(pixelValues[2]) << " Green: " << static_cast<int>(pixelValues[1])  << " Blue: " << static_cast<int>(pixelValues[0]);

   Scalar drawColor = Scalar_<uchar>(~pixelValues[0],~pixelValues[1],~pixelValues[2]);
   int baseLine=0;
   bool leftOrigin = true;
   
   Size theSize=getTextSize(textStream.str(),FONT_HERSHEY_PLAIN,1.0,2,&baseLine);
   if((currentLoc.x + theSize.width) > theMat.cols)
      currentLoc.x -= theSize.width;
   if((currentLoc.y + theSize.height) > theMat.rows)
      currentLoc.y -= theSize.height;
   if(currentLoc.y < theSize.height)
      currentLoc.y += theSize.height;
   

   cout << textStream.str() << " leftOrigin: " << leftOrigin << " X: " << currentLoc.x << " Y: " << currentLoc.y << " Height: " << theSize.height << " Rows: " << theMat.rows  << endl;

   putText(theMat,textStream.str(),currentLoc,FONT_HERSHEY_PLAIN,1,drawColor,2,8,false);
   
   
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
      writeValuesToMat(thePicture,Point(x,y),pixelValues);
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
   reservedImage = theImage.clone();

   
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
