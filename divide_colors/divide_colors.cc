#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

static void help()
{
    cout
        << "\n--------------------------------------------------------------------------" << endl
        << "This program takes an input image and divides the native color palette (255) with the "  << endl
        << "input argument, then writes it to \"divided.jpg\". "                           << endl
        << "Usage:"                                                                       << endl
        << "./how_to_scan_images <imageNameToUse> <divideWith> [G]"                       << endl
        << "if you add a G parameter the image is processed in gray scale"                << endl
        << "--------------------------------------------------------------------------"   << endl
        << endl;
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar * table);

int main( int argc, char* argv[])
{

    if (argc < 3)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    Mat I, J;
    if( argc == 4 && !strcmp(argv[3],"G") )
        I = imread(argv[1], IMREAD_GRAYSCALE);
    else
        I = imread(argv[1], IMREAD_COLOR);
    cv::imwrite("./Image.jpg",I);
    if (I.empty())
    {
        cout << "The image" << argv[1] << " could not be loaded." << endl;
        return -1;
    }

    //! [dividewith]
    int divideWith = 0; // convert our input string to number - C++ style
    stringstream s;
    s << argv[2];
    s >> divideWith;
    if (!s || !divideWith)
    {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }

    uchar table[256];
    for (int i = 0; i < 256; ++i)
       table[i] = (uchar)(divideWith * (i/divideWith));
    //! [dividewith]

    //    cv::Mat clone_i;
    

    //! [table-init]
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for( int i = 0; i < 256; ++i)
        p[i] = table[i];
    //! [table-init]

    LUT(I, lookUpTable, J);
    //    cv::imwrite("./divided.jpg",J);
    const char *windowName="divide_colors";
    cv::namedWindow(windowName, WINDOW_AUTOSIZE);
    cv::imshow(windowName,J);
    cv::waitKey(0);
    cv::destroyWindow(windowName);
    
    return 0;
}
