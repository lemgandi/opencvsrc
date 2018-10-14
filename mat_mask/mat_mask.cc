/*
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

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include <getopt.h>

using namespace std;
using namespace cv;

static void usage(char* progName)
{
   cout << endl
	 <<  "This program applies a filter read from disk to an image with filter2d" << endl
	 <<  "Usage:"                                                                 << endl
        << progName << " -i imagepath -t tablepath [-g] "        << endl << endl
        << " Where imagepath is the name of a jpg uchar image, and tablepath is a"  << endl
        << " text file defining a table mask. Use the -g switch to read the image" << endl
        << " in grayscale" << endl;
}

//Read mask from file

int read_kernel( Mat &outkernel, const char *filename)
{
       outkernel = (Mat_<char>(3,3) <<  0, -1,  0,
                                   -1,  5, -1,
                                    0, -1,  0);
       return 0;       

}
int main( int argc, char* argv[])
{
   char default_filename[] = {"../images/lena.jpg"};   
   char *filename = 0;
   char *table_filename = 0;
   bool grayscale=false;
   Mat src, dst0, dst1;
   Mat kernel;
   const char *optstring = {"i:t:g?"};
   char opt;
   

   while((opt = getopt(argc,argv,optstring)) != -1) {
      switch(opt) {
      case 'i':
	 filename=optarg;
	 break;
      case 't':
	 table_filename=optarg;
	 break;
      case 'g':
	 grayscale=true;
	 break;
      case '?':
      default:
	 usage(argv[0]);
	 return 1;	       	   
      }
   }
   
   if(! filename ) {
      filename=default_filename;
   }
   
   if (! table_filename) {
      cerr << "Oops. I must have a table filename." << endl;
      return -1;
   }
    if (grayscale) 
       src = imread( filename, IMREAD_GRAYSCALE);
    else
        src = imread( filename, IMREAD_COLOR);
    if (src.empty())
    {
        cerr << "Can't open image ["  << filename << "]" << endl;
        return -1;
    }
    if(0 != read_kernel(kernel,table_filename)) {
       cerr << "Problem parsing table file [" << table_filename << "]" << endl;
       return -1;       
    }

    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);
    imshow( "Input", src );
    filter2D( src, dst1, src.depth(), kernel );
    imshow( "Output", dst1 );
    waitKey();
    
    return 0;
}
