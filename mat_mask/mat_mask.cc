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
#include <fstream>

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

int read_kernel( Mat &outKernel, const char *filename)
{

   int retVal=0;
   
   outKernel = (Mat_<char>(3,3) <<  0, -1,  0,
		-1,  5, -1,
		0, -1,  0);
   
   ifstream input_kernel(filename,ios_base::in);
   if( (! input_kernel.good()) || (! input_kernel.is_open()) ) {
      cout << "Oops. File [" << filename << "] will not open." << endl;
	  retVal=1;
   }
   enum parseState {Started,Comment,Matsize,Row,Done};
   parseState myState = Started;
   char theline[255];
   char *numberP;   
   istringstream number;
   int numRows;
   int numCols;
   int currentRow=0;
   int currentCol=0;
   
   while (Done != myState) {
      input_kernel.getline(theline,sizeof(theline));
      if(input_kernel.eof())
	 myState=Done;
      else {
	 if( ('#' == *theline) || (0 == *theline))
	 myState=Comment;
      else if(('/' == *theline) && ('/' == theline[1]))
	 myState=Matsize;
      else
	 myState=Row;
      }
      
      switch(myState) {
      case Started:
	 cout << "Oops. Parse error. I do not know what this line [" << theline << "]  means" << endl;
	 myState = Done;
	 break;
      case Comment:
	 break;
      case Matsize:
	 numberP = strtok(theline," /:abcdefghijklmnopqrstuvwxyz:");
	 numRows=atoi(numberP);
	 numberP = strtok(NULL," ,:abcdefghijklmnopqrstuvwxyz");
	 numCols = atoi(numberP);
	 outKernel.create(numRows,numCols,CV_8S);
	 break;
      case Row:
	 currentCol=0;	 
	 numberP=strtok(theline,", ;\t");
	 while(currentCol < numCols) {
   	    outKernel.at<uchar>(currentRow,currentCol) = atoi(numberP);
	    numberP=strtok(NULL,", ;\t");
	    ++currentCol;
	 }
	 ++currentRow;
	 if(currentRow > numRows)
	    myState=Done;
	 break;	 
      case Done:
	 break;
      default:
	 cout << "Oops. Parse error. State = [" << myState << "]" << endl;
	 myState=Done;
	 break;	 
      }
      
   }
   
   return retVal;
   

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
    cout << "Kernel table:" << endl << kernel << endl;
    namedWindow("Output", WINDOW_AUTOSIZE);
    imshow( "Input", src );
    filter2D( src, dst1, src.depth(), kernel );
    imshow( "Output", dst1 );
    waitKey();
    
    return 0;
}
