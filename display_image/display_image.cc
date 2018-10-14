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
