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
#define CHSDEBUG  // How do I get cmake to include this in the compile command line?

#include <cerrno>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

// #define NUMDIGITS 2  // Change to 10 when we have all 10 digits.
#define NUMDIGITS 10
#define NUMDIR "numbers/"

#ifdef CHSDEBUG
/*
What is going on in there?
*/
void printMat(Mat &theMat, const char *matName)
{
   cout << matName << ": " <<  " elemsize: " << theMat.elemSize() << " Type: " << theMat.type() <<
      " Rows: " << theMat.rows << " Cols: " << theMat.cols << " Channels: " << theMat.channels() <<  " CV_8U = " << CV_8U << endl; 
}
#endif

int fillNumbers(Mat *matP,int matLen)
{
   int ii=0;
   stringstream ss;
   string imgfn;
   int status=0;
   
   for (ii=0;ii<matLen;++ii) {
      stringstream().swap(ss);
      ss << NUMDIR << ii << ".jpg";
      imgfn = ss.str();
#ifdef CHSDEBUG      
      cout << "Image: [" << imgfn << "]" << endl;
#endif      
      errno = 0;
      *matP=imread(imgfn,IMREAD_GRAYSCALE);
      // *matP=imread(imgfn,IMREAD_COLOR);
      if(matP->empty()) {
	 status=errno;
	 cerr << "Oops. Cannot read [" << imgfn << "]" << endl;
	 break;
      }
      ++matP;            
   }
   return status;
}


// Main Line
int main(int argc, char *argv[])
{
   Mat numbers[NUMDIGITS];
   int status=0;
   /*
    The commented-out line below compiles correctly, but when run it produces:
terminate called after throwing an instance of 'cv::Exception'
  what():  OpenCV(3.4.4) /home/devel/opencv/release_compiled/include/opencv2/core/mat.inl.hpp:579: error: (-215:Assertion failed) total() == 0 || data != NULL in function 'Mat'

Aborted
It works correctly with a non-zero number however.
   */
//   Mat typeDisplay(500,500,CV_8U,0);

   
   Mat typeDisplay(500,500,CV_8U);
   typeDisplay.setTo(0);
   
   if(0 != (status = fillNumbers(numbers,NUMDIGITS)))
   {
      cerr << "Oops. Cannot read number images: " << status << endl;
   }
   const char *windowName="Typewriter";
   int keyValue=0;
   
   namedWindow(windowName,WINDOW_AUTOSIZE);
   // namedWindow("Foo",WINDOW_AUTOSIZE);
   int rowStart=0;
   int rowEnd=20;
   Range rowRange(0,20);
   Range colRange(0,10);
#ifdef CHSDEBUG
   printMat(typeDisplay,"typeDisplay");
#endif
   
   while('q' != keyValue) {
      imshow(windowName,typeDisplay);
      keyValue=waitKey(0);
      if(isdigit(keyValue))
      {
#ifdef CHSDEBUG	 
	 printMat(numbers[atoi((char *)&keyValue)],"numberMatrix");
#endif
	 numbers[atoi((char *)&keyValue)].copyTo(typeDisplay(rowRange,colRange));
	 colRange.start += 10;
	 colRange.end += 10;
	 if(colRange.start > 490)
	 {
	    colRange.start=0;
	    colRange.end=10;
	 }
      }
      
   }
   

      
}
