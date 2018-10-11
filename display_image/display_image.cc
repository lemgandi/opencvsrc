#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[] ) {
   if(argc != 2) {
      printf("Usage: display_image image_name\n");
      exit(1);
   }
   Mat image;
   image=imread(argv[1],1);
   if(! image.data ) {
      printf("Oops. No image data?\n");
      exit(1);
   }
   //   cout << "CSV Data = [" << endl << format(image,Formatter::FMT_PYTHON) << endl << "]" << endl << endl;
   namedWindow(argv[1],WINDOW_AUTOSIZE);
   imshow(argv[1],image);
   waitKey(0);
   destroyWindow(argv[1]);
   exit(0);
}
