#ifndef COLORPATCH_H
#define COLORPATCH_H

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
/*
  Link number and color mats with areas on typescript.
 */
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

enum patchType {color,number};

class colorPatch {
   Mat patches[2];
   vector<Rect> patchLocations;
   cv::Rect findPatchloc(cv::Rect);   
public:
   void setPatch(const cv::Mat &, patchType);
   void getPatch(cv::Mat &, patchType);
   void addPatchloc( cv::Rect);
   void removePatchloc( cv::Rect);

};
#endif
