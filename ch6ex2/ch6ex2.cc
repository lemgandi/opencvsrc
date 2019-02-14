/*
  Chapter 6 exercise 2 from Learning openCV 3 -- greyscale load a color image and display color text

Still a Work in Progress.

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

const char *defaultImage = "../images/lena.jpg";
const char *lenaText="Oh, Lena!";
int main(int argc, char *argv[])
{

      const char *imageFN;
   
   if(argc == 1)
      imageFN=defaultImage;
   else if(argc == 2) 
      imageFN=argv[1];
   else {
      cout << "Usage: " << *argv << " [image_name]" << endl;      
      exit(1);
   }
   
   Mat image;
   image=imread(imageFN,1);
   if(! image.data ) {
      perror("Oops. No image data: ");
      exit(1);
   }
   cvtColor(image,image,cv::COLOR_BGR2GRAY,0);
   
   Point textOrigin = Point(310,85);
   Size textSize=getTextSize(lenaText,cv::FONT_HERSHEY_SCRIPT_SIMPLEX,1.0,2,0);
   cout << textSize << endl;
   Mat textMat = Mat(image,Rect(textOrigin,textSize));

   cvtColor(textMat,textMat,cv::COLOR_GRAY2BGR);
   Scalar drawnColor = Scalar_<uchar>(66,128,98);
   putText(textMat,lenaText,Point(0,textMat.rows-1),cv::FONT_HERSHEY_SCRIPT_SIMPLEX,1.0,drawnColor,2,cv::LINE_AA,false);
   //   textMat.copyTo(Mat(image,Rect(textOrigin,textSize)));
   
   namedWindow(argv[1],WINDOW_AUTOSIZE);
   imshow(argv[1],image);
   waitKey(0);
   destroyWindow(argv[1]);
   exit(0);

   
}
