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


int main(int argc, char *argv[])
{
//   RNG myRNG = RNG(getCpuTickCount());
     RNG myRNG = RNG();

     Matx33f matThreebythreeFloat = Matx33f (
      (float)myRNG,(float)myRNG,(float)myRNG,
      (float)myRNG,(float)myRNG,(float)myRNG,
      (float)myRNG,(float)myRNG,(float)myRNG
	);   
   cout << "Mat<float,3,3> " << matThreebythreeFloat << endl;
   matThreebythreeFloat = matThreebythreeFloat * 10;
   cout << "Matx33f * 10: " << matThreebythreeFloat << endl;
   Vec3f vectorThreeFloat = Vec3f(3.0,5.0,7.0);
   cout << "Vec3f: " << vectorThreeFloat << endl;
   // Will not work -- no conversion (operator=) between Mat and Vec types
   // matThreebythreeFloat = matThreebythreeFloat * vectorThreeFloat;
   // cout << "vectorThreeFloat * vectorThreeFloat " << matThreebythreeFloat << endl;
   // matThreebythreeFloat = matThreebythreeFloat * (Matx<float,3,3>)vectorThreeFloat;
   // cout << "vectorThreeFloat * (mat3x1f)vectorThreeFloat " << matThreebythreeFloat << endl;
   
}
