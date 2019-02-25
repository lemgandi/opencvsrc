/*
 Exercise 3 from Intro to OpenCV: write downsampled avi from camera to disk

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

using namespace std;
using namespace cv;




int main(int argc, char *argv[])
{
   cout << "Start" << endl;
   
   VideoCapture myCamera(0);
   Mat theframe;
   const char *windowName="Camera";
   const int framesCalc=120;
   int framesShown=0;
   int currentFramerate=0;
   double startTix=0;
   double tixTaken;
   double currentFrameRate;
   String theText;
   char doubleArray[100];
   cout << "Init finished" << endl;


   char c;
   namedWindow(windowName,cv::WINDOW_AUTOSIZE);
   while(true) {
      myCamera >> theframe;
   
      ++framesShown;
      if(framesShown == framesCalc) {
	 tixTaken=getTickCount() - startTix;
	 currentFrameRate = framesShown / (tixTaken / getTickFrequency());
	 memset(doubleArray,0,sizeof(doubleArray)-1);
	 sprintf(doubleArray,"Frame Rate: %f",currentFrameRate);
	 theText=doubleArray;
	 startTix=getTickCount();
	 framesShown=0;
	 cout << theText << endl;
      }
      Scalar drawnColor = Scalar_<uchar>(66,128,98);
      putText(theframe,theText,Point(30,30),cv::FONT_HERSHEY_SCRIPT_SIMPLEX,1.0,drawnColor,2,cv::LINE_AA);
      

      imshow(windowName,theframe);
      cout << "Showing frame: " << framesShown << endl;
      c = (char)waitKey(2);
      if (27 == c)
	 break;
   }
   myCamera.release();
}
