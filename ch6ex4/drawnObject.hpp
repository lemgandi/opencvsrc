#ifndef DRAWNOBJECT_HPP
#define DRAWNOBJECT_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

// An object drawn on the canvas -- nose, left eye, right eye, mouth, outline
class drawnObject {
public:   
   drawnObject(Map &canvas);
   ~drawnObject();
   void draw();
   void reLocate(Point &newLocation);
   
private:
   Map &myCanvas;
   Point currentLocation;
};
#endif
