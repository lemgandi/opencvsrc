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


using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
   float negE=-2.71828;
   RNG myRNG = RNG(getCPUTickCount());
   

   cout << "Arbitrary Negative Float (negE): " << negE << " abs(negE) = " << abs(negE) << endl;
   cout << "negE Rounded = " << cvRound(negE) << " negE Ceiling = " << cvCeil(negE) << endl;
   cout << "negE floor = " << cvFloor(negE) << endl;
   cout << "Random Ints " << (int)myRNG << " " << (int)myRNG << endl;
   cout << "Random Floats " << (float)myRNG << " " << (float)myRNG << endl;
   Point2f myFltPoint = Point2f(3.14157,2.71828);
   Point myPoint = myFltPoint;
   cout << "Point2f: " << myFltPoint << endl;
   cout << "Point from point2f: " << myPoint << endl;
   Point otherWay = Point(17,23);
   Point2f otherWayFlt = otherWay;
   cout << "Point: " << otherWay << endl;
   cout << "Point2f from point: " << otherWayFlt << endl;
   
}
