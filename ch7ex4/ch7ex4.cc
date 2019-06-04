/*
 Exercise 4 from Intro to OpenCV chapter 7: experiment with SVD

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

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{

   Mat arrayToAnalyze = (Mat_<float>(3,2) << 1.,1.,0.,1.,-1.,1.);
   cout << "Rows: " << arrayToAnalyze.rows << " Cols: " << arrayToAnalyze.cols << endl;
   cout << arrayToAnalyze << endl;
   SVD svdAnalyzer = SVD();
   Mat outputW;
   Mat outputU;
   Mat outputVt;
   Mat solutionZ;
   
   svdAnalyzer.compute(arrayToAnalyze,outputW,outputU,outputVt,SVD::FULL_UV);
   cout << "outputW array rows " << outputW.rows << " cols " << outputW.cols << endl;
   cout << outputW << endl;
   cout << "outputU array rows " << outputU.rows << " cols " << outputU.cols << endl;
   cout << outputU << endl;
   cout << "outputVt array rows " << outputVt.rows << " cols " << outputVt.cols << endl;
   cout << outputVt << endl;
   svdAnalyzer.solveZ(arrayToAnalyze,solutionZ);
   cout << "Solved for Z rows " << solutionZ.rows << " Cols " << solutionZ.cols << endl;
   cout << solutionZ << endl;
}
