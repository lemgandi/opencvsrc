/*
 Exercise 10 from Intro to OpenCV: load and save with opencv

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
#include <string.h>

#include <stdio.h> // remove
using namespace std;
using namespace cv;
const char *defaultImgFN="../images/lena.jpg";

const char *DiskStuffTopMapName = "DiskStuff";

const char *DiskStuffLabels[] =
{
   "sequenceNumber",
   "drawColor",
   "drawnRect"
};

typedef struct {
   int sequenceNumber;
   Scalar_<uchar> drawColor;
   Rect drawnRect;   
} diskstuff;

vector<diskstuff> MyDiskStuff;
static Rect TheBox;

/*
Keep track of boxes drawn on the image.
 */
void addBoxtoVector(Rect thebox,Scalar_<uchar> drawColor)
{
   diskstuff myStuff;
   static int myseqNum = 0;

   myStuff.drawnRect = thebox;
   myStuff.drawColor = drawColor;
   myStuff.sequenceNumber = myseqNum;
   MyDiskStuff.insert(MyDiskStuff.end(),myStuff);
   ++myseqNum;

}
/*
Draw a box on the image
*/
void drawTheBox(Mat &image, Rect box,Scalar color)
{
   rectangle( image, box.tl(),box.br(), color,3);
}

/*
Mouse callback routine -- draw a rect on the screen.
 */
void drawRect(int event,int x, int y, int flags, void *param)
{
   Mat &thePicture = *(Mat *)param;
   static bool drawingBox = false;

   Vec3b pixelValues = thePicture.at<Vec3b>(x,y);
   // Rather than just red, make the rect the xor of the current pixel.  Not great, but good for visibility.
   Scalar drawColor = Scalar_<uchar>(~pixelValues(0),~pixelValues(1),~pixelValues(2));

   
   switch(event) {
   case EVENT_MOUSEMOVE:
      if(drawingBox) {
	 TheBox.width = (x - TheBox.x);
	 TheBox.height = (y - TheBox.y);
      }
      break;
   case EVENT_LBUTTONDOWN:
      drawingBox = true;
      TheBox = Rect(x,y,0,0);
      break;
   case EVENT_LBUTTONUP:
	 drawingBox = false;
	 if(0 > TheBox.width) {
	    TheBox.x += TheBox.width;
	    TheBox.width = -TheBox.width;
	 }
	 if( 0 > TheBox.height) {
	    TheBox.y += TheBox.height;
	    TheBox.height = -TheBox.height;
	 }
	 drawTheBox(thePicture,TheBox,drawColor);
	 addBoxtoVector(TheBox,drawColor);
      break;
   default:
      break;
   }
   
   
   return;
   
}
/*
Read boxes from disk
 */
void readDrawMyDiskStuff(Mat theImage, vector <diskstuff> &theStuff,const string &filename)
{
   FileStorage fs(filename,FileStorage::READ);
   FileNode rects = fs[DiskStuffTopMapName];
   
   diskstuff dataFromFile;

   FileNodeIterator iter = rects.begin();
   FileNodeIterator iterEnd = rects.end();

   while(iter != iterEnd) {
      (*iter)[DiskStuffLabels[0]] >> dataFromFile.sequenceNumber;
      (*iter)[DiskStuffLabels[1]] >> dataFromFile.drawColor;
      (*iter)[DiskStuffLabels[2]] >> dataFromFile.drawnRect;
      MyDiskStuff.insert(MyDiskStuff.end(),dataFromFile);
      ++iter;
   }
   vector<diskstuff>::iterator dsiter;
   dsiter = MyDiskStuff.begin();
   while(dsiter != MyDiskStuff.end()) {
      drawTheBox(theImage,dsiter->drawnRect,dsiter->drawColor);
//      cout << "Drawing " << dsiter->sequenceNumber << endl;
      ++dsiter;
   }
}
void clearBoxes(vector<diskstuff> &theStuff) {
   cout << "Clearing State.." << endl;
   
   theStuff.erase(theStuff.begin(),theStuff.end());

}

/*
Write boxes to disk.
 */
void writeMyDiskStuff(vector<diskstuff> &theStuff,const string &filename)
{

   int ii;
   FileStorage fs(filename,FileStorage::WRITE);
   if(! theStuff.empty()) {
      fs << DiskStuffTopMapName << "[" ;
      for(ii=0;ii<MyDiskStuff.size();++ii) {
	 fs << "{" ;
	 fs << DiskStuffLabels[0] << MyDiskStuff[ii].sequenceNumber;
	 fs << DiskStuffLabels[1] << MyDiskStuff[ii].drawColor;
	 fs << DiskStuffLabels[2] << MyDiskStuff[ii].drawnRect;
	 fs << "}";
      }
      fs.release();
      cout << "Wrote state to " << filename << endl;
   }
   else
   {
      cout << "State has been cleared; removing " << filename << endl;
      remove(filename.c_str());
   }
}

void usage(const char *pname)
{
   cout << "Usage: " << pname << " [-i imagename] " << endl;
   cout << "imagename defaults to " << defaultImgFN << endl;
   cout << "Read and write structs to disk with opencv" << endl;
   cout << "Structs are written to imagename.ocv " << endl;
   
}

int main(int argc, char *argv[])
{
   const char *optString="i:";
   char opt;
   string imageFN(defaultImgFN);
   string saveFN;
   
   while((opt = getopt(argc,argv,optString)) != -1) {
      switch(opt) {
      case 'i':
	 imageFN=optarg;
	 break;
      default:
	 usage(argv[0]);
	 return 1;
      }
   }
   saveFN=basename(imageFN.c_str());

   saveFN += ".yml";
   
   Mat myImage=imread(imageFN,IMREAD_COLOR);
   Mat reserveImage=myImage.clone();
   
   if(myImage.empty()) {
      cerr << "Cannot read image in [" << imageFN << "]" << endl;
      exit(1);
   }
   const char *windowName="saveTestWindow";
   namedWindow(windowName,WINDOW_AUTOSIZE);
   setMouseCallback(windowName,drawRect,&myImage);
   char c=0;
   while(27 != c) {
      imshow(windowName,myImage);
      c=waitKey(1);
      switch(c) {
      case 27:
	 destroyWindow(windowName);
	 break;
      case 'w':
	 writeMyDiskStuff(MyDiskStuff,saveFN);
	 break;
      case 'r':
	 readDrawMyDiskStuff(myImage,MyDiskStuff,saveFN);
	 break;
      case 'c':
	 clearBoxes(MyDiskStuff);
	 reserveImage.copyTo(myImage);
	 break;
      default:
	 break;
	 
      }
   }
}
