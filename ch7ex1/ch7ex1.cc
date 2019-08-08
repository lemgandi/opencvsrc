/*
    Chapter 7 exercise 1: random number generator functor

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
#include <time.h>

using namespace std;
using namespace cv;

RNG MyRNG;

void usage(const char *pname) {
   cerr << "Usage: " << pname << endl;
   cerr << "Arguments:" << endl;
   cerr << "a:  Generate 3 floating point numbers uniform between 0.0 and 1.0" << endl;
   cerr << "b:  Generate 3 double precision numbers, Gaussian distribution of 1.0 centered at 0.0" << endl;
   cerr << "c:  Generate 3 unsigned bytes uniform distribution 0 - 255" << endl;
}

/*
Three floating points uniform between 0.0 and 1.0
 */
void do_ex_a() {
   
   cout << "Three Floating Points uniform between 0.0 and 1.0" << endl;
   cout << MyRNG.uniform(0.0,1.0) << endl;
   cout << MyRNG.uniform(0.0,1.0) << endl;
   cout << MyRNG.uniform(0.0,1.0) << endl;
}
/*
Three double-precision gaussian centered at 0.0 std dev 1.0
 */
void do_ex_b() {
   
   cout << "Three double-precisions Gaussian centered at 0.0 std dev 1.0" << endl;
   cout << MyRNG.gaussian(1.0) << endl;
   cout << MyRNG.gaussian(1.0) << endl;
   cout << MyRNG.gaussian(1.0) << endl;
   
		  
   return;
}
/*
Three unsigned bytes uniform 0-255
 */
void do_ex_c() {
   
   cout << "Three unsigned bytes uniform between 0 and 255" << endl;
   cout << MyRNG.uniform((uchar)0,(uchar)255) << endl;
   cout << MyRNG.uniform((uchar)0,(uchar)255) << endl;
   cout << MyRNG.uniform((uchar)0,(uchar)255) << endl;
   
}
// Main Line
int main(int argc, char *argv[])
{
   int opt;
   bool done=false;
   MyRNG = RNG((uint64)time(NULL));
   
   while(-1 != (opt=getopt(argc,argv,"abc"))) {
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
      default:
	 usage(argv[0]);
	 break;
      }
      done=true;
   }
   if(false == done)
      usage(argv[0]);
}
