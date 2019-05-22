/*
 Exercise 3 chapter 7 from Learning OpenCV 3: make a bunch of random matrices and
 glom them together.

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

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <fstream>
#include <time.h>
#define CHS_DEBUG

using namespace std;
using namespace cv;

RNG MyRNG;

// Main Line
int main(int argc, char *argv[])
{
   
//   MyRNG = RNG((uint64)time(NULL));
   MyRNG = RNG();
   Mat dataMat(0,0,CV_8U);
   Mat inptMatrices[3];
      
   inptMatrices[0] =  Mat(1,100,CV_8U);
   inptMatrices[1] = Mat(1,100,CV_8U);
   inptMatrices[2] =  Mat(1,100,CV_8U);

    
   MyRNG.fill(inptMatrices[0],RNG::NORMAL,64,10);
   MyRNG.fill(inptMatrices[1],RNG::NORMAL,192,10);
   MyRNG.fill(inptMatrices[2],RNG::NORMAL,128,2);
      
   dataMat.push_back(inptMatrices[0]);
   dataMat.push_back(inptMatrices[1]);
   dataMat.push_back(inptMatrices[2]);
/*
   // This segment computes means as if data is cv::PCA::DATA_AS_COLS.
   // A means matrix for cv::PCA::DATA_AS_ROWS would be 1 x 100, with 
   // arithmetic mean for each column in each slot. We will let PCA 
   // compute that for us.  I don't understand what the value of
   // passing the matrixMeans in is.   
   float matrixMeans[3];
   matrixMeans[0] = (sum(inptMatrices[0])/inptMatrices[0].cols)[0];
   matrixMeans[1] = (sum(inptMatrices[1])/inptMatrices[1].cols)[0];
   matrixMeans[2] = (sum(inptMatrices[2])/inptMatrices[2].cols)[0];
   
   Mat means(3,1,CV_8U);
   means.at<uchar>(0,0)=(uchar)matrixMeans[0];
   means.at<uchar>(1,0)=(uchar)matrixMeans[1];
   means.at<uchar>(2,0)=(uchar)matrixMeans[2];
// Pass this to the PCA constructor and get:
// terminate called after throwing an instance of 'cv::Exception'
//  what():  OpenCV(3.4.4) /home/devel/opencv/opencv-3.4.4/modules/core/src/pca.cpp:104:
//  error: (-215:Assertion failed) _mean.size() == mean_sz in function 'operator()'
*/
   
#ifdef CHS_DEBUG
/*  
   cout << "Mean of inptMatrices[0]: " <<  matrixMeans[0] << endl;
   cout << "Mean of inptMatrices[1]: " <<  matrixMeans[1] << endl;
   cout << "Mean of inptMatrices[2]: " <<  matrixMeans[2] << endl;

   cout << "Means:" << endl;
   cout << means << endl;
   cout << "Mean size: " << means.size << endl;
*/
   cout << "Input Matrix 0" << endl;
   cout << inptMatrices[0] << endl;
   cout << "Input Matrix 1" << endl;
   cout << inptMatrices[1] << endl;
   cout << "Input Matrix 2" << endl;
   cout << inptMatrices[2] << endl;

   cout << "Output matrix row 0" << endl;
   cout << dataMat.row(0) << endl;
   cout << "Output matrix row 1" << endl;
   cout << dataMat.row(1) << endl;
   cout << "Output matrix row 2" << endl;
   cout << dataMat.row(2) << endl;
   cout << "DataMat Size:" << dataMat.size << endl;
   
#endif

//   PCA myAnalysis(dataMat,means,PCA::DATA_AS_ROW,2);
   // Pass empty Mat object as means.
   PCA myAnalysis(dataMat,Mat(),PCA::DATA_AS_ROW,2);
//   PCA myAnalysis(dataMat,means,PCA::DATA_AS_COL,2);
#ifdef CHS_DEBUG   
   Mat returnedMeans = myAnalysis.mean.clone();
   cout << "PCA Means: " << endl;
   cout << returnedMeans << endl;
   cout << "PCA Means Size: " <<  returnedMeans.size << endl;
   Point centerOfDist = Point(static_cast<int>(myAnalysis.mean.at<float>(0,0)),
			      static_cast<int>(myAnalysis.mean.at<float>(0,1)));
   cout << "Center: " << endl;
   cout << centerOfDist << endl;
#endif
   
   Mat projectedData = myAnalysis.project(dataMat);

   cout << "Projected Data:" << endl;
   cout << projectedData << endl;
   cout << "Projected data gives the end points of lines which would encompass \
all of the variances of the input data if plotted  on a 3d cartesian coordinate \
plane. The lines are long in the x and y dimensions, but short in the Z dimension. \
This is because the data created with RNG had larger ranges in the X and Y \
coordinates (e.g. rows 0 and 1) but a verysmall range (\"128,2\") in the Z coordinate."\
	<< endl;

}
