/*
 Exercise 10 chapter 10: create low-variance image, show image with bilateral filtering.

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

enum task { Create,Show };

void usage(const char *pname)
{
   cout << "Usage: " << pname << "-{c imagfile} {-i imagefile}" << endl;
   cout << "Use '-c imagefile' to create a low-variance random image." << endl;
   cout << "Use '-i imagefile' to display the image with bilateral filtering." << endl;
   cout << "The '-c . . .' and '-i . . .' flags are mutually exclusive." << endl;
   
}
void createImage(const char * imageFN) {
   Mat theImage(200,200,CV_8U);
   RNG myRNG=RNG(getCPUTickCount());

   myRNG.fill(theImage,RNG::UNIFORM,0,4);
   imwrite(imageFN,theImage);
   
   cout << "Image [" << imageFN << "] written" << endl;
  
   
}
void filterAndShowImage(const char *imageFN,double NS,double sC)
{
   Mat theImage=imread(imageFN,IMREAD_COLOR);

   
   int status=0;
   
   if (theImage.empty()) {
      cout << "Cannot read [" << imageFN << "]" << endl;
      status = 1;
   }
   if( 0 == status) {
      Mat outputImage(theImage.size(),theImage.type());
      bilateralFilter(theImage,outputImage,NS,sC,-1);
      const char *windowName="Filtered";
      namedWindow(windowName,WINDOW_AUTOSIZE);
      imshow(windowName,outputImage);
      const char *rawWindowName="Raw";
      namedWindow(rawWindowName,WINDOW_AUTOSIZE);
      imshow(rawWindowName,theImage);
      waitKey(0);
   }
}
int main(int argc, char *argv[])
{
   const char *optString="c:i:n:o:";
   char opt;
   char *imageFileName;
   task whatToDo=Create;
   istringstream doubleConverter;
   double ns=10.0;
   double sc=20.0;
   
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'c':
	 whatToDo=Create;
	 imageFileName = strdup(optarg);
	 break;
      case 'i':
	 whatToDo=Show;
	 imageFileName = strdup(optarg);
	 break;
      case 'n':
	 doubleConverter.str(optarg);
	 doubleConverter >> ns;
	 break;
      case 'o':
	 doubleConverter.str(optarg);
	 doubleConverter >> sc;
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   switch(whatToDo) {
   case Create:
      createImage(imageFileName);
      break;
   case Show:
      filterAndShowImage(imageFileName,ns,sc);
      break;
   default:
      cout << "Oops." << endl;
   }
}
