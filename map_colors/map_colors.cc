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
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <sstream>
#include <fstream>

#include <getopt.h>


using namespace std;
using namespace cv;



static void usage(char *pname)
{
    cout
        << "\n--------------------------------------------------------------------------" << endl
        << "Usage: " << pname << " -i infilename -t tablename [-g]  " << endl << endl
        << "-i: input picture " << endl
	<< "-t: new color table" << endl
	<< "-g: Read picture in greyscale if specified" << endl
        << "--------------------------------------------------------------------------"   << endl
        << endl;
}

// Read color lookup table from disk
int read_table_file(uchar *theTable,int tableSize,char * filename)
{
   int retVal=0;
   
   //   cout << filename;
   
   ifstream input_table(filename,ios_base::in);

   if((! input_table.good()) || (! input_table.is_open()) ) {
      cout << "Oops. File " << filename << " will not open." << endl;      
      retVal=1;      
   }
   
   uchar mychar;
   char numberString[5];
   char *numberP=numberString;
   uchar *table_ptr=theTable;
   int tableCtr=0;
   int digitCounter=0;
   int theNumber;
   enum parseState {Reading,Digits,Comment};
   parseState theState=Reading;
   
   memset(numberString,0,sizeof(numberString));
   while ( (! input_table.eof()) && (0 == retVal) && (digitCounter < (tableSize-1)) ) {
      
      mychar = input_table.get();
      if(Comment != theState)
	 theState=Reading;
      if ( (isdigit(mychar)) && (Comment != theState))
	 theState=Digits;      
      if(('\n' == mychar) && (Comment == theState))
	 theState=Reading;
      if('#' == mychar)
	 theState=Comment;

      switch(theState) {
      case Reading:
	 if(digitCounter) {
	    theNumber=atoi(numberString);
	    if(theNumber > 255)
	       theNumber=theNumber % 255;
	    *table_ptr=theNumber;
	    ++table_ptr;
	    ++tableCtr;
	    
	    memset(numberString,0,sizeof(numberString));
	    numberP=numberString;
	    digitCounter=0;
	 }
	    break;
	 case Comment:
	    break;
	 case Digits:
	    *numberP=mychar;
	    ++numberP;
	    ++digitCounter;
	    break;
	 default:
	    cout << "Oops. Parser error. " << theState << " should never happen." << endl;
	    retVal=1;
	    break;
      }
   }
   return retVal;
   
}

int main( int argc, char* argv[])
{

    char*infilename=0;
    char *table_filename=0;
    int grayscale=0;
    Mat I, J;
    char optstring[]={"i:t:g"};
    char opt;
    
    while((opt=getopt(argc,argv,optstring)) != -1) {
       switch(opt) {
       case 'i':
	  infilename=optarg;
	  break;
       case 't':
	  table_filename=optarg;
	  break;
       case 'g':
	  grayscale=1;
	  break;
       default:
	  usage(argv[0]);
	  return 1;
       }
    }

    if(! infilename || ! table_filename) {
       usage(argv[0]);
       return 1;       
    }
    
    if(grayscale)
        I = imread(infilename, IMREAD_GRAYSCALE);
    else
        I = imread(infilename, IMREAD_COLOR);

    if (I.empty())
    {
        cout << "The image " << infilename << " could not be loaded." << endl;
        return -1;
    }


    uchar table[256];
    if(read_table_file(table,sizeof(table),table_filename)) {
       cout << "Oops. Trouble reading color table." << endl;
       return -1;
    }
    /*    
    for (int i = 0; i < 256; ++i)
       table[i] = (uchar)(divideWith * (i/divideWith));
    //! [dividewith]
    */
    //    cv::Mat clone_i;
    

    //! [table-init]
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for( int i = 0; i < 256; ++i)
        p[i] = table[i];
    //! [table-init]
    cout << "LUT :" << format(lookUpTable,Formatter::FMT_C) << endl;
    LUT(I, lookUpTable, J);
    
    const char *dividedW="Divided";
    cv::namedWindow(dividedW, WINDOW_AUTOSIZE);
    cv::imshow(dividedW,J);
    const char *originalW="Original";
    cv::namedWindow(originalW,WINDOW_AUTOSIZE);
    cv::imshow(originalW,I);
    cv::waitKey(0);
    cv::destroyWindow(dividedW);
    cv::destroyWindow(originalW);
    
    return 0;
}
