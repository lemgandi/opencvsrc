/*
 Exercise 3 from Intro to OpenCV: twist picture forward and back.with warpPerspective

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

const char *DefaultFN = "../images/lena.jpg";

void usage(const char *pname)
{
   cout << "Usage: " << pname << "[-i filename]" << endl;
   cout << "Warp perspective of image in filename; default name is " << DefaultFN << endl;
}
char convert_shifted(char c,bool *shifted)
{
   // )!@#$%&*
   char converted=c;
   *shifted=false;
   switch(c) {
   case ')': //0
      converted = '0';
      *shifted=true;
      break;
   case '!': //1
      converted = '1';
      *shifted=true;
      break;
   case '@':
      converted = '2';
      *shifted=true;
      break;
   case '#':
      converted = '3';
      *shifted=true;
      break;
   case '$':
      converted = '4';
      *shifted=true;
      break;
   case '%':
      converted = '5';
      *shifted=true;
      break;
   case '^':
      converted = '6';
      *shifted=true;
      break;
   case '&':
      converted = '7';
      *shifted=true;
      break;
   case '*':
      converted = '8';
      *shifted=true;
      break;
   default:
      break;
   }
   return converted;
}
// Main Line
int main(int argc, char *argv[])
{
   const char *optString="i:";
   char opt;
   char *optarg;
   char inFN[80];

   memset(inFN,0,sizeof(inFN));
   strncpy(inFN,DefaultFN,sizeof(inFN)-1);
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'f':
	 memset(inFN,0,sizeof(inFN));
	 strncpy(inFN,optarg,sizeof(inFN)-1);
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   Mat theImage;
   theImage=imread(inFN,IMREAD_COLOR);
   if(theImage.empty()) {
      cerr << "Cannot read image file [" << inFN << "]" << endl;
      exit(1);
   }
   Mat reservedImage;
   reservedImage = theImage.clone();
   Point2f sourceQuadPts[] = {
      Point2f(0,0), // Top Left
      Point2f((theImage.cols-1),0), //Top right
      Point2f((theImage.cols-1),(theImage.rows-1)), // Bottomr right
      Point2f(0,(theImage.rows-1))  // Bottom Left
   };
/*
   Point2f destQuadPts[] = {
      Point2f((theImage.cols*0.05f),(theImage.cols*0.33f)),
      Point2f((theImage.cols*0.9f),(theImage.rows*0.25f)),
      Point2f((theImage.cols*0.8f),(theImage.rows*0.9f)),
      Point2f((theImage.cols*0.2f),(theImage.rows*0.7f))      
   };   
   Mat theWarpMat = getPerspectiveTransform(sourceQuadPts,destQuadPts);
*/
/*
   Point2f destQuadPts[] = {
      Point2f(0,0),
      Point2f((theImage.cols-1),0),
      Point2f((theImage.cols-1),(theImage.rows-1)),
      Point2f(0,(theImage.rows-1))      
   };   
   Mat theWarpMat = getPerspectiveTransform(sourceQuadPts,destQuadPts);
*/
   Mat theWarpMat = (Mat_<float>(3,3) << 1,0,0,
		                         0,1,0,
		                         0,0,1.);

   cout << "Warp Mat: " << endl;
   cout << theWarpMat << endl;

   
   Mat destMat;
   warpPerspective(theImage,destMat,theWarpMat,theImage.size(),INTER_LINEAR,BORDER_CONSTANT,Scalar());
   const char *windowName="Warp Test";
   namedWindow(windowName,WINDOW_AUTOSIZE);
   int rowNum;
   int colNum;
   char c=0;
   bool shifted=false;
   int inputNum;
   float incrementAmt=0.1;
   while(27 != c) {
      imshow(windowName,destMat);
      c = convert_shifted(c,&shifted);
      cout << "c: " << c << "shifted: " << shifted << endl;
      switch(c) {
      case '0':  // 0,0
      case '1':  // 0,1
      case '2':  // 0,2
      case '3':  // 1,0
      case '4':  // 1.1
      case '5':  // 1.2
      case '6':  // 2,0
      case '7':  // 2,1
      case '8':  // 2,2
	 inputNum = static_cast<int>(c-48);
	 rowNum=inputNum / theWarpMat.rows;
	 colNum=inputNum % theWarpMat.cols;
	 if(shifted)
	    theWarpMat.at<float>(rowNum,colNum) = theWarpMat.at<float>(rowNum,colNum)-incrementAmt;	    
	 else
	    theWarpMat.at<float>(rowNum,colNum) = theWarpMat.at<float>(rowNum,colNum)+incrementAmt;
	 cout << "theWarpMat.at(" << rowNum << "," << colNum << ") = " << theWarpMat.at<float>(rowNum,colNum) << endl;
	 warpPerspective(theImage,destMat,theWarpMat,theImage.size(),INTER_LINEAR,BORDER_CONSTANT,Scalar());
	 break;
      }
      c=waitKey();
   }
   return 0;
}
