/*
 Exercise 5 from chapter 5 of Intro to OpenCV: load an image, bitwise_not a couple of regions, display result.

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

const char *defaultImage="../images/lena.jpg";


int main(int argc, char *argv[])
{

   Mat myImage;
   const char *imageName;
   int status=0;
   
   if(argc < 2)
      imageName=defaultImage;
   else
      imageName=argv[1];
   
   myImage=imread(imageName,IMREAD_COLOR);
   
   if(myImage.empty())
   {
      cout << "I could not load [" << imageName << "]" << endl;
      status=1;
   }
   
   if((myImage.rows < 100) || (myImage.cols < 100))
   {
      cout << "The image " << imageName << " is too small. It needs to be at least 100 x 100 pixels." << endl;
      status=2;
   }
   
   if(0 == status)
   {
      const char *windowName="chapter5ex5";
      
      Mat roiFirst=Mat(myImage,Rect(Point(5,10),Size(20,30)));
      Mat roiTwost=Mat(myImage,Rect(Point(50,60),Size(20,30)));
      
      bitwise_not(roiFirst,roiFirst);
      bitwise_not(roiTwost,roiTwost);

      namedWindow(windowName,WINDOW_AUTOSIZE);
      imshow(windowName,myImage);
      waitKey(0);
      destroyWindow(windowName);
      
      
   }
   
}
