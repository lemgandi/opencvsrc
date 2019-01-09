/*
    Exercise 2 from chapter 5 of _Learning_Opencv_3:  Draw a rectangle with Mat.at<>().

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

const int hSize = 80;
const int vSize = 80;

const int rectWidth = 45;
const int rectHeight = 30;
const int rectX = 20;
const int rectY = 25;
const char * windowName = "Rectangle";


/*
 Main Line
*/
int main(int argc, char *argv[])
{
   
   Mat display = Mat(hSize,vSize,CV_8UC3);
   Vec3b lineColor = Vec3b(84,155,0);

   display.setTo(0);
   Vec3b theVal;
   int ii;
   
   for(ii = 0; ii < rectWidth; ++ii) 
      display.at<Vec3b>(rectX,rectY+ii) = lineColor;
   
   for(ii=0;ii<rectHeight;++ii) 
      display.at<Vec3b>(rectX+ii,rectY) = lineColor;
   
   for(ii=0;ii<rectWidth;++ii)
      display.at<Vec3b>(rectX+rectHeight,rectY+ii) = lineColor;

   for(ii=0;ii<rectHeight;++ii)
      display.at<Vec3b>(rectX+ii,rectY+rectWidth) = lineColor;
   
   
   namedWindow(windowName,WINDOW_AUTOSIZE);
   imshow(windowName,display);
   int keyValue=0;
   keyValue=waitKey(0);
   return 0;
   
}
