/*
    Chapter 5 exercise 1: draw a circle or so
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

const int displayHsize = 500;
const int displayVsize = 500;

int main(int argc, char *argv[])
{
   RNG myRNG = RNG(getCPUTickCount());
   
   Mat display = Mat(displayHsize,displayVsize,CV_8UC3);
   display.setTo(0);
   
   Point circleCenter = Point();
   Scalar circleColor = Scalar(255,0,153);
   const char *windowName="Circles";
   


   namedWindow(windowName,WINDOW_AUTOSIZE);
   int keyValue=0;
   int diameter=myRNG.uniform(10,40);
   
   circleCenter.x=myRNG.uniform(diameter,displayVsize);
   circleCenter.y=myRNG.uniform(diameter,displayHsize);
      
   while (keyValue != 'q') {
      
      cout << "Center: " << circleCenter << " Diameter: " << diameter << " Color: " << circleColor << endl;
	   
      circle(display,circleCenter,diameter,circleColor,7,LINE_8,0);
      imshow(windowName,display);
      
      keyValue=waitKey(0);
      switch(keyValue) {
      case ' ':
	 diameter=myRNG.uniform(10,40);
	 circleCenter.x=myRNG.uniform(diameter,displayVsize);
	 circleCenter.y=myRNG.uniform(diameter,displayHsize);
	 break;
      case 'c':
	 circleColor[0]=myRNG.uniform(1,255);
	 circleColor[1]=myRNG.uniform(1,255);
	 circleColor[2]=myRNG.uniform(1,255);
	 break;
      default:
	 break;	 
      }
   }
   
}
