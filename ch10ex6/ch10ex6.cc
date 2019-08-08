/*
 Exercise 6, chapter 10: adaptive brightness filter

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
#include <sstream>
#include <string>
#include <fstream>

#include <getopt.h>

using namespace std;
using namespace cv;

void usage(const char *pname)
{
   cout << "Usage: " << pname << " -i imagefilename [-v] [-g] [-b blocksize] [-o offset] " << endl;
   cout << "Adaptive brightness filter for images" << endl;
   cout << "'-v' -- use inverse binary threshold" << endl;
   cout << "'-g' -- use gaussian adaptive threshold" << endl;
   cout << "'-b' blocksize -- blocksize of adaptive filter (blocksize must be odd)" << endl;
   cout << "'-o' offset -- offset of adaptive filter" << endl;
   cout << "'-s' subtract -- subtract filtered from original" << endl;
}

int main(int argc, char *argv[])
{
   const char *optString="i:b:o:vgs";
   char opt;

   String imageFN;
   int threshType=THRESH_BINARY;
   int adaptiveMethod=ADAPTIVE_THRESH_MEAN_C;
   double blockSize = 15;
   double offset = 10;
   istringstream converter;
   bool do_subtract=false;
   
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'i':
	 imageFN=optarg;
	 break;
      case 'b':
	 converter.str(optarg);
	 converter >> blockSize;
	 break;
      case 'o':
	 converter.str(optarg);
	 converter >> offset;
	 break;
      case 'v':
	 threshType=THRESH_BINARY_INV;
	 break;
      case 'g':
	 adaptiveMethod=ADAPTIVE_THRESH_GAUSSIAN_C;
	 break;
      case 's':
	 do_subtract = true;
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   
   if(imageFN.empty()) {
      cout << "You must provide an image filename" << endl;
      usage(argv[0]);
      exit(1);
   }
   if(! (remainder(blockSize,2.0))) {
      cout << "Oops. Blocksize must be odd.  You put in " << blockSize << endl;
      usage(argv[0]);
      exit(1);
   }
   Mat theImage;
   theImage = imread(imageFN,IMREAD_GRAYSCALE);
   if(theImage.empty()) {
      cout << "Cannot read image in [" << imageFN << "]" << endl;
      usage(argv[0]);
      exit(1);
   }
   const char *rawWindowName = "Raw";
   namedWindow(rawWindowName,WINDOW_AUTOSIZE);
   imshow(rawWindowName,theImage);
   Mat filtered;
   Mat subtracted;   
   adaptiveThreshold(theImage,filtered,255,adaptiveMethod,threshType,blockSize,offset);
   
   if(do_subtract) 
      subtract(theImage,filtered,subtracted);
   else
      subtracted=filtered;
   
   const char *filteredWindowName = "Filtered";
   namedWindow(filteredWindowName,WINDOW_AUTOSIZE);
   imshow(filteredWindowName,subtracted);
   waitKey(0);
   destroyAllWindows();
   exit(0);
   
}
