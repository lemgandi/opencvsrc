#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>


class imageWindow {
public:
   imageWindow(const char *name,const cv::Mat &image);
   ~imageWindow();
private:
   bool displayed;
   char *wName;
};
   
#endif
