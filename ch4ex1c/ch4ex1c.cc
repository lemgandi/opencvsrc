/*
    Chapter 4 exercise 1: numeric typewriter redux

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

#include "colorPatch.hpp"


using namespace std;
using namespace cv;

// #define NUMDIGITS 2  // Change to 10 when we have all 10 digits.
#define NUMDIGITS 10
#define NUMDIR "numbers/"

#define TYPEBOX_COLSIZE 500
#define TYPEBOX_ROWSIZE 500
#define NUMBOX_WIDTH 10
#define NUMBOX_HEIGHT 20
#define RIGHTBORDER (TYPEBOX_COLSIZE - NUMBOX_WIDTH)
#define BOTTOMBORDER (TYPEBOX_ROWSIZE - NUMBOX_HEIGHT)


#ifdef CHSDEBUG
/*
What is going on in there?
*/
void printMat(const Mat &theMat, const char *matName)
{
   cout << matName << ": " <<  " elemsize: " << theMat.elemSize() << " Type: " << theMat.type() <<
      " Rows: " << theMat.rows << " Cols: " << theMat.cols << " Channels: " << theMat.channels() << endl; 
}
#endif

/*
   Read a patch off the disk.
 */
int readPatch(Mat *matp,patchType type,int patchNum)
{
   stringstream ss;
   string imgfn;
   int status = 0;
   
   if(number == type) 
      ss << NUMDIR << patchNum << ".jpg";   
   else 
      ss << NUMDIR << "C" << patchNum << ".jpg";      
   
   imgfn = ss.str();      

#ifdef CHSDEBUG      
   cout << "Image: [" << imgfn << "]" << endl;
#endif      
   errno = 0;
   *matp=imread(imgfn,IMREAD_COLOR);
   
   if(matp->empty()) {
      status=errno;
      cerr << "Oops. Cannot read [" << imgfn << "]" << endl;
   }

   return status;
}

/*
Fill in the numbers array.
 */
int fillNumbers(colorPatch *patchP,int numPatches)
{
   int ii=0;
   stringstream ss;
   string imgfnNumber;
   int status=0;
   Mat theMat(NUMBOX_HEIGHT,NUMBOX_WIDTH,CV_8UC3);
    
   for (ii=0;ii<numPatches;++ii) {
       if ( 0 == (status = readPatch(&theMat,number,ii)))
	 patchP->setPatch(theMat,number);      // *matP=imread(imgfn,IMREAD_GRAYSCALE);
      else
	 break;
      if( 0 == ( status = readPatch(&theMat,color,ii)))
	 patchP->setPatch(theMat,color);
      else
	 break;
      patchP->setNumber(ii);
      ++patchP;            
   }
   
   return status;
}
/*
Change mode from numbers to colors or back.
*/
void changeDisplayMode(patchType &theMode,Mat &typeDisplay,colorPatch *patchArray,int patchArraySize)
{
   int ii;
   
   vector<Rect>::const_iterator locIter;
   patchType newMode;
   
   if(theMode == number)
      newMode = color;
   else
      newMode=number;
   
   for(ii=0;ii<patchArraySize;++ii) {
      for(locIter=patchArray->getPatchLocationsBegin(); locIter != patchArray->getPatchLocationsEnd(); ++locIter) {
	 patchArray->getPatch(newMode).copyTo(typeDisplay(*locIter));
      }
      ++patchArray;
   }
   theMode = newMode;
}
/*
  Can I find a patch by its Mat member?
 */
colorPatch *findPatchByContents(Mat contents,colorPatch *patchArray, int patchArraySize, patchType typeOfPatch)
{
   colorPatch *retVal=0;
   int ii;

   for(ii=0;ii<patchArraySize;++ii) {
      if(! countNonZero(contents != patchArray->getPatch(number))) {
	 retVal=patchArray;
	 break;
      }
      ++patchArray;
   }
   return retVal;
}

// Main Line
int main(int argc, char *argv[])
{
   colorPatch patches[NUMDIGITS];
   int status=0;

   /*
    The commented-out line below compiles correctly, but when run it produces:
terminate called after throwing an instance of 'cv::Exception'
  what():  OpenCV(3.4.4) /home/devel/opencv/release_compiled/include/opencv2/core/mat.inl.hpp:579: error: (-215:Assertion failed) total() == 0 || data != NULL in function 'Mat'

Aborted
It works correctly with a non-zero number however.
   */
//   Mat typeDisplay(500,500,CV_8U,0);

   
   Mat typeDisplay(TYPEBOX_ROWSIZE,TYPEBOX_COLSIZE,CV_8UC3);
   typeDisplay.setTo(0);
   
   Mat spaceDisplay(NUMBOX_HEIGHT,NUMBOX_WIDTH,CV_8UC3);
   spaceDisplay.setTo(0);
    
   if(0 != (status = fillNumbers(patches,NUMDIGITS)))
      cerr << "Oops. Cannot read number images: " << status << endl;
   
   const char *windowName="Typewriter";
   int keyValue=0;
   
   namedWindow(windowName,WINDOW_AUTOSIZE);
   // namedWindow("Foo",WINDOW_AUTOSIZE);
   Point currentLoc(0,0);
   Size theSize(NUMBOX_WIDTH,NUMBOX_HEIGHT);
   Rect  currentRect(currentLoc,theSize);
   char numBuf[4];
   Rect lastRect=currentRect;
   bool cursorLit=false;
   colorPatch *patchP;
   patchType currentMode=number;
   Mat searchPatch;
   
#ifdef CHSDEBUG
   int patchNumber;
#endif

#ifdef CHSDEBUG
   printMat(typeDisplay,"typeDisplay");
#endif
 
   while('q' != keyValue) {
      if(! cursorLit)
      {
	 bitwise_not(typeDisplay(currentRect),typeDisplay(currentRect));
	 cursorLit=true;
      }
      lastRect=currentRect;
      imshow(windowName,typeDisplay);
      keyValue=waitKey(0);
#ifdef CHSDEBUG
      cout << "keyValue: " << keyValue << endl;
#endif

      if(isdigit(keyValue))
      {
	 memset(numBuf,0,sizeof(numBuf));
	 *numBuf=keyValue;
#ifdef CHSDEBUG
	 printMat(patches[atoi(numBuf)].getPatch(number),"numberMatrix");
#endif
	 patches[atoi(numBuf)].addPatchloc(currentRect);
	 patches[atoi(numBuf)].getPatch(number).copyTo(typeDisplay(currentRect));
	 currentRect.x += NUMBOX_WIDTH;
	 if(currentRect.x > RIGHTBORDER)
	 {	 
	    currentRect.x=0;
	    currentRect.y += NUMBOX_HEIGHT;
	 }
	 cursorLit=false;
      }
      else {
	 cursorLit=false;
	 switch(keyValue) { 
	 case 8: // backspace
         case 81:  // leftarrow
  	    if(currentRect.x) 
  	       currentRect.x -= NUMBOX_WIDTH;
#ifdef CHSDEBUG
	    patchP=findPatchByContents(typeDisplay(currentRect),patches,NUMDIGITS,currentMode);
	    if(patchP)
	       cout << "Current patch is: " << patchP->getNumber() << " patch loc count: " << patchP->countLocs()  << endl;
	    else
	       cout << "Currently on a blank patch" << endl;
#endif	    
  	    break;
	 case 99:   // 'c' -- change mode
	    changeDisplayMode(currentMode,typeDisplay,patches,NUMDIGITS);
	    break;
	 case 82:  // uparrow
	    if(currentRect.y) 
	       currentRect.y -= NUMBOX_HEIGHT;
	    break;
	 case 84:  // downarrow
	    if(currentRect.y < BOTTOMBORDER) 
	       currentRect.y += NUMBOX_HEIGHT;
	    break;
	 case 83:  // rightarrow
	    if(currentRect.x < RIGHTBORDER) 
	       currentRect.x += NUMBOX_WIDTH;
	    break;
	 case 32:  // Space -- blanks cell
	    cout << "Rectangle: " << currentRect << endl;
	    bitwise_not(typeDisplay(currentRect),searchPatch);
	    if(0 != (patchP=findPatchByContents(searchPatch,patches,NUMDIGITS,currentMode)))
	       patchP->removePatchloc(currentRect);
	    cout << "patchP: " << patchP << " currentMode " << currentMode << endl;
	    spaceDisplay.copyTo(typeDisplay(currentRect));
	    bitwise_not(typeDisplay(currentRect),typeDisplay(currentRect));
	    if(currentRect.x < RIGHTBORDER)
	       currentRect.x += NUMBOX_WIDTH;
	    break;
	 case 13:  // return
	    if(currentRect.y < BOTTOMBORDER)
	    {
	       currentRect.y += NUMBOX_HEIGHT;
	       currentRect.x = 0;
	    }
	    break;
	 default:
	    cursorLit=true;
	    break;
	 }
	 if((lastRect != currentRect) && (! cursorLit)) 
	    bitwise_not(typeDisplay(lastRect),typeDisplay(lastRect));	 
      }
   }
}
