/*
 Exercise 3 chapter 8:  video transformation

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

void usage(char * pname,char *deftFN) {
   cout << "Usage: " << pname << " [-s] [-1 firstthreshold] [-2 twostthreshold] [-f filename] [-h number]" << endl;
   cout << "Display video in original, grayscale, and canny() transformations" << endl;
   cout << "-s flag specifies a single window, otherwise in three different windows" << endl;
   cout << "-f specifies input video filename; default is " << deftFN << endl;
   cout << "-1 and -2 specify thresholds for the Canny edge detection transform" << endl;
   cout << "-h: number of times to halve size of output window" << endl;
   
}


/*
Shirink picture to fit display as directed by argument value
'*/

void shrink_as_necessary(Mat &picture,int pyrDownCount)
{
   while(pyrDownCount) {
      pyrDown(picture,picture);
      --pyrDownCount;
   }
}

//
// 1: display in three different windows
//
void displayWindows(float threshOne,float threshTwo,int pyrDownCount,VideoCapture &inputFrames) {
   Mat natFrame;
   Mat greyscaleFrame;
   Mat cannyFrame;

   char natName[] = {"natural"};
   char greyName[] = {"greyscale"};
   char cannyName[] = {"canny"};
   
   namedWindow(natName,WINDOW_AUTOSIZE);
   namedWindow(greyName,WINDOW_AUTOSIZE);
   namedWindow(cannyName,WINDOW_AUTOSIZE);
   char c;
   moveWindow(natName,0,0);
   inputFrames >> natFrame;
   shrink_as_necessary(natFrame,pyrDownCount);
   // imshow("foo",natFrame);

   if(pyrDownCount) {
      moveWindow(greyName,natFrame.cols+5,0);
      moveWindow(cannyName,(2 * natFrame.cols)+5,0);
   }
   while(! natFrame.empty()) {

      shrink_as_necessary(natFrame, pyrDownCount);

      cvtColor(natFrame,greyscaleFrame,CV_BGR2GRAY);
      Canny(natFrame,cannyFrame,threshOne,threshTwo);
      imshow(natName,natFrame);
      imshow(cannyName,cannyFrame);
      imshow(greyName,greyscaleFrame);
      
      inputFrames >> natFrame;
      // The waitKey here is apparently necessary. Without it, the first
      // namedWindow does not show up at all, and no windows display any
      // frames. Just black. I don't understand why this is.
      c=(char)waitKey(2);
      if(27 == c)
	 break;
   }
}

//
//1ab: Wfite everything to one window in three regions, labeled.
//
void displayOneWindow(float threshOne,float threshTwo,int pyrDownCount,VideoCapture &inputFrames)
{

   Mat picture;
   int pydctr;
   const char *windowName={"Display"};

   namedWindow(windowName,WINDOW_AUTOSIZE);
   inputFrames >> picture;
   shrink_as_necessary(picture,pyrDownCount);

   cout << "Rows: " << picture.rows << " Cols: " << picture.cols << " elemSize: " << picture.elemSize() << endl;
   cout << "CV_8UC3 " << CV_8UC3 << endl;
   
   Mat displayFrame(picture.rows,(picture.cols*3),picture.type());
   Mat natFrame(displayFrame,Rect(0,0,picture.cols,picture.rows));
   Mat greyFrame(displayFrame,Rect(picture.cols,0,picture.cols,picture.rows));
   Mat cannyFrame(displayFrame,Rect((picture.cols)*2,0,picture.cols,picture.rows));

/*
   Scalar natFrameColor = Scalar_<uchar>(66,128,98);
   natFrame.setTo(natFrameColor);

   Scalar greyFrameColor = Scalar_<uchar>(208,0,22);
   greyFrame.setTo(greyFrameColor);

   Scalar cannyFrameColor = Scalar_<uchar>(77,4,202);
   cannyFrame.setTo(cannyFrameColor);
   
   imshow(windowName,displayFrame);
 
   char c=0;
   c = waitKey(0);
*/
   char c=0;
   Mat greyPicture;
   Mat cannyPicture;
   Scalar textColor = Scalar_<char>(82,82,50);
   Point textOrigin = Point(10,45);
   while(! picture.empty()) {
      picture.copyTo(natFrame);
      putText(natFrame,"Natural",textOrigin,FONT_HERSHEY_SIMPLEX,1,textColor,3);
      
      cvtColor(picture,greyPicture,CV_BGR2GRAY);
      cvtColor(greyPicture,greyFrame,CV_GRAY2BGR);
      putText(greyFrame,"Grey",textOrigin,FONT_HERSHEY_SIMPLEX,1,textColor,3);
      
      Canny(picture,cannyPicture,threshOne,threshTwo);
      cvtColor(cannyPicture,cannyFrame,CV_GRAY2BGR);
      putText(cannyFrame,"Canny",textOrigin,FONT_HERSHEY_SIMPLEX,1,textColor,3);
      
      imshow(windowName,displayFrame);
      inputFrames >> picture;
      if(! picture.empty())
	 shrink_as_necessary(picture,pyrDownCount);
      c=(char)waitKey(2);
      if(27 == c)
	 break;
      else if ('s' == c)
	 c=(char)waitKey(0);
   }
	
   return;
}

int main(int argc, char *argv[])
{
   char optString[]={"sf:1:2:h:"};
   char opt;
   bool singleWindow=false;
   char defaultFN[] = {"../images/Otto_first_steps.mp4"};
   char infileName[80];
   int  status = 0;
   VideoCapture inputFrames;
   double threshOne=100.0;
   double threshTwo=3.0;
   int pyrDownCount=0;
   
   memset(infileName,0,sizeof(infileName));
   strncpy(infileName,defaultFN,sizeof(infileName)-1);
   istringstream convert;
   
   while((opt=getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 's':
	 singleWindow=true;
	 break;
      case 'f':
	 strncpy(infileName,optarg,sizeof(infileName)-1);
	 break;
      case '1':
	 convert.str(optarg);
	 convert >> threshOne;
	 break;
      case '2':
	 convert.str(optarg);
	 convert >> threshTwo;
	 break;
      case 'h':
	 convert.str(optarg);
	 convert >> pyrDownCount;
	 break;
      default:
	 usage(argv[0],defaultFN);
	 return 1;
      }
   }
   cout << "Args: " << "singleWindow is " << singleWindow << endl;
   cout << "infileName is " << infileName << endl;
   cout << "threshOne: " << threshOne << endl;
   cout << "threshTwo: " << threshTwo << endl;
   

   inputFrames.open(infileName);
   
   if(! inputFrames.isOpened() ) {
      cout << "Something Bad Happened trying to open " << infileName << endl;
      usage(argv[0],defaultFN);
      status = -1;
   }
   
   if(0 == status)
   {
      if(! singleWindow) 
	 displayWindows(threshOne,threshTwo,pyrDownCount,inputFrames);
      else
	 displayOneWindow(threshOne,threshTwo,pyrDownCount,inputFrames);
   }
      
   
   // VideoCapture object automagically closed when its destructor is called.
}
