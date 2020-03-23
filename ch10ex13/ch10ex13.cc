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

#include <imageWindow.hpp>
#include <utility.hpp>


using namespace std;
using namespace cv;

const char *defaultImageFN = "../images/lena.jpg";

/*
Usage Message
 */
void usage(const char *pname)
{
   cout << "Usage: " << pname << " -i infile [-m maximum] [-t threshold] [-a]" << endl;
   cout << "Show image threshold transformations. maximum is the highest value, threshold is the threshold value." << endl;
   cout << "The a switch converts to adaptive threshold; for this, the threshold argument becores the weighting constant" << endl;
   cout << "It seems to have good results at if maximum =~ 25" << endl;
   
}

/*
Shpw image with threshold type and threshold given.
 */
imageWindow * makeImageWindow(const Mat & image,int threshtype,int maxval,int threshval,const char *wname,bool adaptive)
{
   Mat myImage;
   
   if(adaptive)
      adaptiveThreshold(image,myImage,(double)maxval,ADAPTIVE_THRESH_MEAN_C,threshtype,5,(double)threshval);
   else
      threshold(image,myImage,threshval,maxval,threshtype);
   
   imageWindow * retVal = new imageWindow(wname,myImage);
   return retVal;
      
}
/*
Main Line
 */
int main(int argc, char *argv[])
{
   int threshold = 128;
   int maximum = 128;
   bool adaptive = false;
   const char *optString="i:t:m:a";
   char opt;
   char *imageFN = 0;
   istringstream digitsConverter;
   
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'a':
	 adaptive=true;
	 break;
      case 'i':
	 imageFN = strdup(optarg);
	 break;
      case 'm':
	 digitsConverter.str(optarg);
	 digitsConverter >> maximum;
	 break;
      case 't':
	 digitsConverter.str(optarg);
	 digitsConverter >> threshold;
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   
   if(0 == imageFN)
      imageFN=strdup(defaultImageFN);
   
   Mat theImage=imread(imageFN,IMREAD_GRAYSCALE);
   if (theImage.empty())
   {
      cout << "Oops. Cannot read [" << imageFN << "]" << endl;
      usage(argv[0]);
      exit(1);
   }
   else
      cout << "Read image of type " << type2str(theImage.type()) << endl;
   
   imageWindow *oWindow = new imageWindow("original",theImage);
   imageWindow *binWindow = makeImageWindow(theImage,THRESH_BINARY,threshold,maximum,"Binary",adaptive);
   imageWindow *binvWindow = makeImageWindow(theImage,THRESH_BINARY_INV,threshold,maximum,"Binary Inverse",adaptive);
   
   imageWindow * truncWindow = 0;
   imageWindow * tozeroWindow = 0;
   imageWindow * tozeroInvWindow = 0;
   
   if(! adaptive)
   {
      truncWindow = makeImageWindow(theImage,THRESH_TRUNC,threshold,maximum,"Trunc",adaptive);
      tozeroWindow = makeImageWindow(theImage,THRESH_TOZERO,threshold,maximum,"Trunc to zero",adaptive);
      tozeroInvWindow = makeImageWindow(theImage,THRESH_TOZERO_INV,threshold,maximum,"trunc to zero inverse",adaptive);
   }
				     
   char c;
   
   c = (char)waitKey();

   delete oWindow;
   delete binWindow;
   delete binvWindow;
   
   if(! adaptive)
   {      
   delete truncWindow;
   delete tozeroWindow;
   delete tozeroInvWindow;
   }
   free(imageFN);
   
					 
}
