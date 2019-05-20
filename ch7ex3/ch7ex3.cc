/*
 Exercise 3 chapter 7 from Learning OpenCV 3: make a bunch of random matrices and
 glom them together.

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
#include <time.h>
#define CHS_DEBUG

using namespace std;
using namespace cv;

RNG MyRNG;

// Main Line
int main(int argc, char *argv[])
{
   
   MyRNG = RNG((uint64)time(NULL));
   Mat outputMat = Mat(1,100,CV_8UC3);
   Mat inptMatrices[3];
   const int inOutChannels[] =  {0,0,1,1,2,2};

   inptMatrices[0] =  Mat(1,100,CV_8U);
   inptMatrices[1] = Mat(1,100,CV_8U);
   inptMatrices[2] =  Mat(1,100,CV_8U);

    
   MyRNG.fill(inptMatrices[0],RNG::NORMAL,64,10);
   MyRNG.fill(inptMatrices[1],RNG::NORMAL,192,10);
   MyRNG.fill(inptMatrices[2],RNG::NORMAL,128,2);
   
   // After creating and filling single-channel matrices, make the 3-channel
   // matrix out of them.
   mixChannels(inptMatrices,3,&outputMat,1,inOutChannels,3);
   
#ifdef CHS_DEBUG
   cout << "Input Matrix 0" << endl;
   cout << inptMatrices[0] << endl;
   cout << "Input Matrix 1" << endl;
   cout << inptMatrices[1] << endl;
   cout << "Input Matrix 2" << endl;
   cout << inptMatrices[2] << endl;

   cout << "Output matrix" << endl;
   cout << outputMat;
#endif
   
   
}
