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
Get read-only iterator of patch locations.
 */
vector<Rect>::const_iterator colorPatch::getPatchLocationsBegin(void)
{
   return patchLocations.begin();
}

/*
Get read-only iterator of patch locations.
 */
vector<Rect>::const_iterator colorPatch::getPatchLocationsEnd(void)
{
   return patchLocations.end();
}


/*
  Get a patch
 */
Mat colorPatch::getPatch(patchType which)
{
   Mat retVal;
   retVal = patches[which];
   return retVal;
}

/*
  Add a location to the list of places containing this patch
 */
void colorPatch::addPatchloc(const Rect loc)
{
   if( ! foundPatchloc(loc) )
      patchLocations.push_back(loc);
   
   return;
}

/*
   Remove a locatoin from the list of places containing this patch
 */
void colorPatch::removePatchloc(Rect loc)
{
   vector<Rect>::iterator iter=patchLocations.begin();
   
   while( (iter != patchLocations.end()) && (*iter != loc)) 
      ++iter;

   if (patchLocations.end() != iter)
      patchLocations.erase(iter);
   
   return;
}
int colorPatch::getNumber(void)
{
   return patchNumber;
}
void colorPatch::setNumber(int theNumber)
{
   patchNumber=theNumber;
}
/*
  Is this patch location in the list of locations for this patch?
 */
bool colorPatch::foundPatchloc(Rect loc)
{
   bool retVal=false;
   vector<Rect>::iterator iter=patchLocations.begin();
   
   while( (iter != patchLocations.end()) && (*iter != loc))
      ++iter;
   if (patchLocations.end() != iter)
      retVal=true;
   return retVal;
}
/*
How many locations is this patch in?
 */
int colorPatch::countLocs(void)
{
   return patchLocations.size();
}
