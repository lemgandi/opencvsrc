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
   cout << "Usage: " << pname << " -i infile" << endl;
}

int main(int argc, char *argv[])
{
   const char *optString="i:";
   char opt;
   char *imageFN = 0;

   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'i':
	 imageFN = strdup(optarg);
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   
   if(0 == imageFN)
      imageFN=strdup(defaultImageFN);
   
   Mat theImage=imread(imageFN);
   if (theImage.empty())
   {
      cout << "Oops. Cannot read [" << imageFN << "]" << endl;
      usage(argv[0]);
      exit(1);
   }
   else
      cout << "Read image of type " << type2str(theImage.type()) << endl;
   
   imageWindow *oWindow = new imageWindow("original",theImage);
   char c;
   c = (char)waitKey();

   delete oWindow;
   free(imageFN);
   
					 
}
