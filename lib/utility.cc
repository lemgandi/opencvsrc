/*
    Various utility functions for learning OpenCV 3

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
#include <string>
using namespace std;

/*
Given the retval from Mat.type(), translate it into a Mat type string.
*/
string type2str(int type) {
   string r;

   uchar depth = type & CV_MAT_DEPTH_MASK;
   uchar chans = 1 + (type >> CV_CN_SHIFT);

   switch ( depth ) {
   case CV_8U:  r = "8U"; break;
   case CV_8S:  r = "8S"; break;
   case CV_16U: r = "16U"; break;
   case CV_16S: r = "16S"; break;
   case CV_32S: r = "32S"; break;
   case CV_32F: r = "32F"; break;
   case CV_64F: r = "64F"; break;
   default:     r = "User"; break;
   }

   r += "C";
   r += (chans+'0');

   return r;
}
