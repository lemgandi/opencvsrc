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


const char *defaultImage = "../images/lena.jpg";

void drawStuff(Mat canvas)
{

   Scalar drawnColor = Scalar_<uchar>(66,128,98);
   const Point polyPoints[] = { Point(300,208),Point(340,220),Point(370,100)};
   // nb that book is wrong about line().  It's
   // line(Mat &,Point,Point,color,int thickness,int lineType),
   // not line(Mat &,Point,Point,color,int lineType).
   line(canvas,Point(22,40),Point(77,30),drawnColor,1,8);
   line(canvas,Point(22,40),Point(77,45),drawnColor,1,4);
   line(canvas,Point(22,40),Point(80,115),drawnColor,1,cv::LINE_AA);

   circle(canvas,Point(110,90),13,drawnColor);
   ellipse(canvas,Point(200,108),Size(25,48),45,0,360,drawnColor,3,cv::LINE_AA);
   
   // Book is wrong here too.  Correct prototype is
   // rectangle(Mat &,Point,Point,color,int thickness,int lineType)
   rectangle(canvas,Point(245,90),Point(320,120),drawnColor,3,cv::LINE_AA);
   fillConvexPoly(canvas,polyPoints,3,drawnColor,cv::LINE_AA);
   
}

// Main Line
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
   
   drawStuff(image);
   
   namedWindow(argv[1],WINDOW_AUTOSIZE);
   imshow(argv[1],image);
   waitKey(0);
   destroyWindow(argv[1]);
   exit(0);

}
