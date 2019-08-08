/*
    Chapter 3 exercise 3: compact matrix

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

     Matx<int,3,3> matThreebythreeInt;
     matThreebythreeInt <<	myRNG(50),myRNG(50),myRNG(50),
      myRNG(50),myRNG(50),myRNG(50),
      myRNG(50),myRNG(50),myRNG(50)
      ;   
   cout << "Matx<int,3,3> " << matThreebythreeInt << endl;
   // Multiply matrix by a scalar -- apply scalar to all members
   matThreebythreeInt = matThreebythreeInt * 10;
   cout << "Matx<int,3,3> * 10: " << matThreebythreeInt << endl;
   
   // Apply vector to matrix...
   Vec<int,3> vectorThreeInt;
   vectorThreeInt << 3,5,7;
   cout << "VectorThreeInt: " << vectorThreeInt << endl;
   // Will not work -- no conversion (operator=) between Mat and Vec types
   // matThreebythreeFloat = matThreebythreeFloat * vectorThreeFloat;
   // cout << "vectorThreeFloat * vectorThreeFloat " << matThreebythreeFloat << endl;
   // force an explicit conversion from vector to matrix:
   Matx<int,3,3> multMatx;
   multMatx << vectorThreeInt[0],vectorThreeInt[1],vectorThreeInt[2],
      vectorThreeInt[0],vectorThreeInt[1],vectorThreeInt[2],
      vectorThreeInt[0],vectorThreeInt[1],vectorThreeInt[2]
      ;
   cout << "multMatx: " << multMatx << endl;
   // then multiply 2 matrices together.  NB that each member of the multiplied matrix
   // is the "dot product" of the corresponding members of the input matrices
   // ( corresponding cols multiplied + corresponding rows multiplied)
   matThreebythreeInt = matThreebythreeInt * multMatx;
   cout << "matThreebythreeInt * multMatx: " << matThreebythreeInt << endl;
   
}
