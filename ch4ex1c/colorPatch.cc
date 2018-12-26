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

#include "colorPatch.hpp"

using namespace cv;
using namespace std;

/*
  Set color or number patch
 */
void colorPatch::setPatch(const Mat& patch,patchType which)
{
   patches[which]=patch;
   return;
}
/*
  Get a patch
 */
void colorPatch::getPatch(Mat& patch,patchType which)
{
   patch=patches[which];
   return;
}


void colorPatch::addPatchloc(cv::Rect loc)
{
   return;
}

void colorPatch::removePatchloc(cv::Rect loc)
{
   return;
}

cv::Rect colorPatch::findPatchloc(cv::Rect loc)
{
}
