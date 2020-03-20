/*
 * Display image in window.
 */

#include "imageWindow.hpp"

imageWindow::imageWindow(const char *name,const cv::Mat & image)
{
   wName = strdup(name);
   cv::namedWindow(name,cv::WINDOW_AUTOSIZE);
   cv::imshow(name,image);
}

imageWindow::~imageWindow()
{
   cv::destroyWindow(wName);
   free(wName);
}
