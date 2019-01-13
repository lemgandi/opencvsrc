/*
 Exercise 4 chapter 5 from Learning OpenCV:  display pyramid of values with ROI

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

const int displaySize = 210;

const char *windowName = "ROITest";


void fillROI(Mat & theDisplay, int filler,int roiSize)
{

   Mat theROI=Mat(theDisplay,Rect(roiSize/2,roiSize/2,(displaySize-roiSize),(displaySize-roiSize)));

   
   theROI.setTo(filler);
   
   return;
		  
}

int main(int argc, char *argv[])
{
   Mat display = Mat(displaySize,displaySize,CV_8U);
   display.setTo(0);
   
   for(int kk=0; kk<displaySize; kk += 10)
   {
      fillROI(display,kk,kk);
   }
//   cout << "Display: " << endl;
//   cout << display;
   namedWindow(windowName,WINDOW_AUTOSIZE);
   imshow(windowName,display);
   int keyValue = waitKey(0);
   
}
