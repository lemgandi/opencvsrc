/*
 Exercise 4.2 from Intro to OpenCV: create mat of summed rectangles from origin of input mat

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

// const int Hsize = 10;
// const int Vsize = 20;

const int Hsize = 100;
const int Vsize = 200;

/*
Sum a rectangle from origin
 */
float rectSum(const Mat &inputRect)
{
   float retVal=0;
   MatConstIterator_<uchar> it;
   MatConstIterator_<uchar> end=inputRect.end<uchar>();
      
   for(it = inputRect.begin<uchar>(); it != end; ++it)
      retVal += *it;
   
   return retVal;
   
}
/*
Create float mat of rect sums from origin
 */
void matSum(const Mat &inputMat, Mat &outputMat)
{
   Rect sumRect = Rect(Size(0,0),Point(0,0));
   float amt=0;

   for(int xx=0; xx<inputMat.rows; ++xx)
      for(int yy=0; yy<inputMat.cols; ++yy)
      {
	 sumRect.height=xx+1;
	 sumRect.width=yy+1;
	 amt=rectSum(inputMat(sumRect));
 	 outputMat.at<float>(xx,yy)=amt;		    
      }		   
}

/*
Main Line
 */
int main(int argc, char *argv[])
{
   RNG myRNG=RNG(getCPUTickCount());
   
   Mat inputMat(Vsize,Hsize,CV_8U);
   
   //   inputMat.setTo(1);
   myRNG.fill(inputMat,RNG::UNIFORM,0,UCHAR_MAX);
   
   Mat outputMat(Vsize,Hsize,CV_32F);
   outputMat.setTo(0);
   
   matSum(inputMat,outputMat);
   cout << "inputMat: " << "---------------" << endl;
   cout << inputMat << endl;
   
   cout << "outputMat: ----------- " << endl;
   cout << outputMat << endl;
   cout << "-------------" << endl;
   
}
