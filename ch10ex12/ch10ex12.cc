/*
 Exercise 

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

#include "imageWindow.hpp"

using namespace std;
using namespace cv;

const char *defaultImageFN="../images/lena.jpg";

void usage(const char *pname)
{
   cout << "Usage: " << pname << "-i imagename [-n ntimes]" << endl;
   cout << "Display image pyrdowned and resized. Pass ntimes to control how many times image should be shrunk by 4x." << endl;
   
}
   
/*
Main Line
*/
int main(int argc, char *argv[])
{
   const char *optString="i:n:";
   char opt;
   Mat startImage;
   char * imageFN = 0;
   int numTimes=1;
   istringstream digitsConverter;
   
   
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'i':
	 imageFN=strdup(optarg);
	 break;
      case 'n':
	 digitsConverter.str(optarg);
	 digitsConverter >> numTimes;
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   if ( ! imageFN)
      imageFN = strdup(defaultImageFN);
   
   Mat theImage=imread(imageFN);
   if (theImage.empty())
   {
      cout << "Oops. Cannot read [" << imageFN << "]" << endl;
      usage(argv[0]);
      exit(1);
   }
   
   Mat resizeImage;
   int loopNum=numTimes;
   resize(theImage,resizeImage,Size(),0.5,0.5);
   while(0 < loopNum) {
      resize(resizeImage,resizeImage,Size(),0.5,0.5);
      --loopNum;
   }

   Mat pyrDownImage;
   loopNum=numTimes;   
   pyrDown(theImage,pyrDownImage);
   while(0 < loopNum) {
      pyrDown(pyrDownImage,pyrDownImage);
      --loopNum;
   }


   imageWindow *oWindow = new imageWindow( "original",theImage);
   imageWindow *rWindow = new imageWindow("Resized",resizeImage);
   imageWindow *pWindow = new imageWindow("Pyrdowned",pyrDownImage);
   
   char c;
   c = (char)waitKey();

   delete oWindow;
   delete rWindow;
   delete pWindow;
   
   free(imageFN);
	 
}
