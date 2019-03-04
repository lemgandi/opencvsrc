/*
 Chapter 6 exercise 4 from intro to opencv 3

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

using namespace std;
using namespace cv;

#define CHSDEBUG

#define CANVAS_COLSIZE 500
#define CANVAS_ROWSIZE 500
#define BOX_WIDTH 3
#define BOX_HEIGHT 4
#define RIGHTBORDER (CANVAS_COLSIZE - BOX_WIDTH)
#define BOTTOMBORDER (CANVAS_ROWSIZE - BOX_HEIGHT)



int main(int argc, char *argv[])
{
   int keyValue=0;
   bool cursorLit=false;
   Point currentLoc(0,0);
   Size theSize(BOX_WIDTH,BOX_HEIGHT);
   Rect currentRect(currentLoc,theSize);
   Rect lastRect=currentRect;
   Mat canvas(CANVAS_ROWSIZE,CANVAS_COLSIZE,CV_8UC3);
   const char *windowName = "Canvas";
   canvas.setTo(0);
   while('q' != keyValue)
   {
      bitwise_not(canvas(currentRect),canvas(currentRect));

      lastRect=currentRect;
      imshow(windowName,canvas);
      keyValue=waitKey(0);
      
#ifdef CHSDEBUG
      cout << "keyValue: " << keyValue << endl;
#endif
      switch(keyValue)
      {
      case 8:  // Backspace
      case 81: // Leftarrow
	 if(currentRect.x)
	    currentRect.x -= BOX_WIDTH;
	 break;
      case 82:  // Uparrow
	 if (currentRect.y)
	    currentRect.y -= BOX_HEIGHT;
	 break;
      case 84:  // Downarrow
      case 13:
	 if (currentRect.y < BOTTOMBORDER)
	    currentRect.y += BOX_HEIGHT;
	 break;
      case 83: //Rightarrow
      case 32:
	 if (currentRect.x < RIGHTBORDER)
	    currentRect.x += BOX_WIDTH;
	 break;
      default:  // Compensate for the bitwise_not at the top of the keyboard input loop
	 bitwise_not(canvas(currentRect),canvas(currentRect));
	 break;
      }
      if(lastRect != currentRect)
	 bitwise_not(canvas(lastRect),canvas(lastRect));
   }
}
