/*
 Exercise 3 from Intro to OpenCV: write downsampled avi from camera to disk
 */

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

/*
Calculate frame rate of camera from actual capture.  CAP_PROP_FPS is often double the actual frame rate.
*/
float calculateFrameRate(VideoCapture& theCapture)
{
   const int num_frames=120;
   Mat timerFrame;
   double startTix = getTickCount();
   double endTix;
   
   for (int kk=0; kk < num_frames; ++kk)
      theCapture >> timerFrame;
   endTix=getTickCount();
   double tixTaken=endTix - startTix;
   double calculatedFPS=num_frames / (tixTaken / getTickFrequency());
   cout << "Calculated FPS:" << calculatedFPS << endl;
   return calculatedFPS;

}

int main(int argc, char *argv[]) {
   if(argc < 2)
   {
      cout << "Oops. Please provide output filename" << endl;
      exit(1);
   }
   namedWindow("output",cv::WINDOW_AUTOSIZE);
   
   VideoCapture capture(0);

   // We are pyrdowning the image, so it is half the size of the camera frame size.
   // Therefore, divide the frame in half.  Without this, the avi will not play properly
   // in players such as vlc or dragon.
   cv::Size size( (int)capture.get(CV_CAP_PROP_FRAME_WIDTH)/2,
		  (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT)/2
		  );
   
   VideoWriter writer;
   
   writer.open(argv[1],CV_FOURCC('M','J','P','G'),calculateFrameRate(capture),size);
   
   Mat bgr_frame;
   Mat pyrd_frame;
   char c;
   while(true) {
      capture >> bgr_frame;

      if(bgr_frame.empty())
	 break;
      pyrDown(bgr_frame,pyrd_frame);
      imshow("output",pyrd_frame);
      writer << pyrd_frame;
      c = (char)waitKey(33);
      if(27 == c)
	 break;
   }
   capture.release();
   
   
		  
}
