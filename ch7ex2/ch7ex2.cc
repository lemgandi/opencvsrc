/*
    Chapter 7 exercise 2: random fills 
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
#include <unistd.h>

using namespace std;
using namespace cv;

RNG MyRNG;

void usage(const char *pname) {
   cerr << "Usage: -[abcd] " << pname << endl;
   cerr << "Arguments:" << endl;
   cerr << "a:  Fill array of 20 floating points uniform 0.0 to 1.0" << endl;
   cerr << "b:  Fill array of 20 floating points Gaussian centered 0.0 std dist 1.0"  << endl;
   cerr << "c:  Fill array of 20 unsigned bytes uniform distribution 0 to 255"  << endl;
   cerr << "d:  Fill array of 20 color triplets, each 3 bytes uniform 0 to 255" << endl;
}


void do_ex_a() {
   Mat myMat = Mat(1,20,CV_32F);
   
   MyRNG.fill(myMat,RNG::UNIFORM,0.0,1.0);
   cout << "Array of 20 floating points uniform 0.0 to 1.0" << endl;
   cout << myMat << endl;
   
}
void do_ex_b() {
   Mat myMat = Mat(1,20,CV_32F);
   
   MyRNG.fill(myMat,RNG::NORMAL,0.0,1.0);
   cout << "Array of 20 floating points Gaussian centered at 0.0 std dist of 1.0" << endl;
   cout << myMat << endl;
   
}
void do_ex_c() {
   Mat myMat = Mat(1,20,CV_8U);
   MyRNG.fill(myMat,RNG::UNIFORM,0,255);

   cout << "An array of 20 unsigned bytes uniform distribution from 0 to 255" << endl;
   cout << myMat << endl;
}
void do_ex_d() {
   Mat myMat = Mat(1,20,CV_8UC3);
   MyRNG.fill(myMat,RNG::UNIFORM,0,255);
   cout << "An array of 20 3-byte color triplets, uniform distribution 0-255" << endl;
   cout << myMat;
}
int main(int argc, char *argv[])
{
   int opt;
   bool done=false;
   MyRNG = RNG((uint64)time(NULL));
   
   while(-1 != (opt=getopt(argc,argv,"abcd"))) {
      switch(opt) {
      case 'a':
	 do_ex_a();
	 break;
      case 'b':
	 do_ex_b();
	 break;
      case 'c':
	 do_ex_c();
	 break;
      case 'd':
	 do_ex_d();
	 break;
      default:
	 usage(argv[0]);
	 break;
      }
      done=true;
   }
   if(false == done)
      usage(argv[0]);

}
