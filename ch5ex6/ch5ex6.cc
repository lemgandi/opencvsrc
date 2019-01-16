/*
 Exercise 6 chapter 5 from Intro to OpenCV: Do some silly stuff with color separations

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
   vector<Mat>bgrImages;
   
   if(myImage.empty())
   {
      cout << "I could not load [" << imageName << "]" << endl;
      status=1;
   }
   split(myImage,bgrImages);
   
   const char *greenWindowName="Green Plane";
   
   namedWindow(greenWindowName,WINDOW_AUTOSIZE);
   imshow(greenWindowName,bgrImages[1]);
   Mat clone1 = bgrImages[1].clone();
   Mat clone2 = bgrImages[1].clone();
   double maxGreen;
   double minGreen;
   minMaxLoc(bgrImages[1],&minGreen, &maxGreen,0,0);
   uchar thresh = (unsigned char)((maxGreen-minGreen)/2.0);
   
   cout << "Minimum green value: " << minGreen << " Maximum green value: " << maxGreen;
   cout << " Threshold: " << (int)thresh << endl;


   clone1.setTo(thresh);
   
   clone2.setTo(0);
   compare(bgrImages[1],clone1,clone2,CMP_GE);
   Mat threshDisplay = bgrImages[1].clone();
   subtract(bgrImages[1],thresh/2,threshDisplay,clone2);

   const char *threshWindowName = "threshold";
   namedWindow(threshWindowName,WINDOW_AUTOSIZE);
   imshow(threshWindowName,threshDisplay);
   


   waitKey(0);
   destroyWindow(greenWindowName);
   destroyWindow(threshWindowName);
}
