/*
 Exercise 3 from Intro to OpenCV: write downsampled avi from camera to disk

    This file is part of opencvsr.
    opencvsr is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    opencvsr is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with opencvsr.  If not, see <http://www.gnu.org/licenses/>.

 */

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

const int PYRDOWNMAX=8;
int CurrentPyrdownNum=0;

int SliderPos=0;


/*
 Callback when trackbar is moved.
 */
void onTrackBarSlide(int pos, void *)
{
   CurrentPyrdownNum=pos;
}

int main(int argc, char *argv[]) {
   if(argc > 1)
   {
      cout << "Oops. This program takes no arguments." << endl;
      exit(1);
   }


  
   namedWindow("output",cv::WINDOW_AUTOSIZE);
   createTrackbar("Downsample","output",&SliderPos,PYRDOWNMAX,onTrackBarSlide);
   
   VideoCapture capture(0);

   Mat bgr_frame;
   Mat pyrd_frame;
   char c;
   
   while(true) {
      capture >> bgr_frame;

      if(bgr_frame.empty())
	 break;
      if(CurrentPyrdownNum)
	 pyrDown(bgr_frame,pyrd_frame);
      else
	 pyrd_frame=bgr_frame;
      for(int kk=0;kk<(CurrentPyrdownNum-1);++kk)
	 pyrDown(pyrd_frame,pyrd_frame);
      
      // This checks if the window itself has been closed.  If so, I exit the loop.
      // Without this check, imshow() recreates the window without the slider bar and
      // the only way out is to ctrl-c the program. It doesn't matter which property you
      // get, except that WND_PROP_VISIBLE seems to be -1 if the window is on-screen.
      if(-1 == getWindowProperty("output",WND_PROP_AUTOSIZE))
	 break;

      imshow("output",pyrd_frame);
      
      
      c = (char)waitKey(33);
      if(27 == c)
	 break;
      
   }
   
   capture.release();
   
   
		  
}
