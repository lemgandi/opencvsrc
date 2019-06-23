#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

static void help()
{
    cout << "\nThis program demonstrates the use of cv::CascadeClassifier class to detect objects (Face + eyes). You can use Haar or LBP features.\n"
            "This classifier can recognize many kinds of rigid objects, once the appropriate classifier is trained.\n"
            "It's most known use is for faces.\n"
            "Usage:\n"
            "./facedetect [--cascade=<cascade_path> this is the primary trained classifier such as frontal face]\n"
               "   [--scale=<image scale greater or equal to 1, try 1.3 for example>]\n"
               "   [--try-flip]\n"
               "   [filename|camera_index]\n\n"
            "see facedetect.cmd for one call:\n"
            "./facedetect --cascade=\"data/haarcascades/haarcascade_frontalface_alt.xml\" --nested-cascade=\"data/haarcascades/haarcascade_eye_tree_eyeglasses.xml\" --scale=1.3\n\n"
            "During execution:\n\tHit any key to quit.\n"
            "\tUsing OpenCV version " << CV_VERSION << "\n" << endl;
}

// Globals
string cascadeName;
/*
 */
void drawFaceOnFace(Mat fImg,Rect r,double scale,int faceNumber,Mat substFace)
{
   Mat newFace;

   Rect theRealROI = Rect(Point(cvRound(r.x*scale),cvRound(r.y*scale)),
			  Point(cvRound((r.x+r.width-1)*scale),cvRound((r.y+r.height-1)*scale)) );
   Mat facePlace(fImg,theRealROI);   
   
   resize(substFace,newFace,theRealROI.size());
   // addWeighted(newFace,0.1,facePlace,0.1,0.08,newFace);
   newFace.copyTo(facePlace);
}

/*
Draw rectangle around face ROI if no substitute picture is passed on command line.
 */
void drawRectaroundFace(Mat fImg,Rect r,double scale,int faceNumber)
{
   const static Scalar colors[] =
    {
        Scalar(255,0,0),
        Scalar(255,128,0),
        Scalar(255,255,0),
        Scalar(0,255,0),
        Scalar(0,128,255),
        Scalar(0,255,255),
        Scalar(0,0,255),
        Scalar(255,0,255)
    };
   Scalar color = colors[faceNumber % 8];
   rectangle( fImg, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
		   Point(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
		   color, 3, 8, 0);

}


/*
Find faces, draw around them.
 */
int detectAndDraw( Mat& img, CascadeClassifier& cascade,
		   double scale, bool tryflip,Mat substFace )
{
    double t = 0;
    vector<Rect> faces, faces2;
    int retVal; // Number of faces detected
    
    Mat gray, smallImg;

    cvtColor( img, gray, COLOR_BGR2GRAY );
    double fx = 1 / scale;
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
    equalizeHist( smallImg, smallImg );

    t = (double)getTickCount();
    cascade.detectMultiScale( smallImg, faces,
        1.1, 2, 0
        //|CASCADE_FIND_BIGGEST_OBJECT
        //|CASCADE_DO_ROUGH_SEARCH
        |CASCADE_SCALE_IMAGE,
        Size(30, 30) );

    if( tryflip )
    {
        flip(smallImg, smallImg, 1);
        cascade.detectMultiScale( smallImg, faces2,
                                 1.1, 2, 0
                                 //|CASCADE_FIND_BIGGEST_OBJECT
                                 //|CASCADE_DO_ROUGH_SEARCH
                                 |CASCADE_SCALE_IMAGE,
                                 Size(30, 30) );
        for( vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); ++r )
        {
            faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
        }
    }
    t = (double)getTickCount() - t;
    printf( "detection time = %g ms\n", t*1000/getTickFrequency());
    retVal = faces.size();
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
	if(substFace.empty())
	   drawRectaroundFace(img,r,scale,i);
	else
	   drawFaceOnFace(img,r,scale,i,substFace);
 	
    }
    
    imshow( "result", img );
    return retVal;
}

/*
Main Line
 */
int main( int argc, const char** argv )
{
    VideoCapture capture;
    Mat frame, image;
    string inputName;
    bool tryflip;
    CascadeClassifier cascade;
    double scale;
    string substFN;
    Mat substFace;
    cv::CommandLineParser parser(argc, argv,
        "{help h||}"
        "{cascade|data/haarcascades/haarcascade_frontalface_alt.xml|}"
	"{subst|null|}"
        "{scale|1|}{try-flip||}{@filename||}"
				
    );
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    cascadeName = parser.get<string>("cascade");
    scale = parser.get<double>("scale");
    if (scale < 1)
        scale = 1;
    tryflip = parser.has("try-flip");
    inputName = parser.get<string>("@filename");
    substFN = parser.get<string>("subst");
    if(substFN.size()) 
       substFace = imread(substFN,IMREAD_COLOR);
    
    cout << "substFN: " << substFN << endl;
    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }
    if (!cascade.load(samples::findFile(cascadeName)))
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        help();
        return -1;
    }
    if( inputName.empty() || (isdigit(inputName[0]) && inputName.size() == 1) )
    {
        int camera = inputName.empty() ? 0 : inputName[0] - '0';
        if(!capture.open(camera))
        {
            cout << "Capture from camera #" <<  camera << " didn't work" << endl;
            return 1;
        }
    }
    else if (!inputName.empty())
    {
        image = imread(samples::findFileOrKeep(inputName), IMREAD_COLOR);
        if (image.empty())
        {
            if (!capture.open(samples::findFileOrKeep(inputName)))
            {
                cout << "Could not read " << inputName << endl;
                return 1;
            }
        }
    }
    else
    {
        image = imread(samples::findFile("../images/lena.jpg"), IMREAD_COLOR);
        if (image.empty())
        {
            cout << "Couldn't read lena.jpg" << endl;
            return 1;
        }
    }
    int numFaces;
    
    if( capture.isOpened() )
    {
        cout << "Video capturing has been started ..." << endl;

        for(;;)
        {
            capture >> frame;
            if( frame.empty() )
                break;

            Mat frame1 = frame.clone();
            detectAndDraw( frame1, cascade, scale, tryflip,substFace );

            char c = (char)waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' )
                break;
        }
    }
    else
    {
        cout << "Detecting face(s) in " << inputName << endl;
        if( !image.empty() )
        {
	   numFaces = detectAndDraw( image, cascade, scale, tryflip,substFace );
	    cout << "number of faces detected: " << numFaces << endl;
            waitKey(0);
        }
        else if( !inputName.empty() )
        {
            /* assume it is a text file containing the
            list of the image filenames to be processed - one per line */
            FILE* f = fopen( inputName.c_str(), "rt" );
            if( f )
            {
                char buf[1000+1];
                while( fgets( buf, 1000, f ) )
                {
                    int len = (int)strlen(buf);
                    while( len > 0 && isspace(buf[len-1]) )
                        len--;
                    buf[len] = '\0';
                    cout << "file " << buf << endl;
                    image = imread( buf, 1 );
		   
                    if( !image.empty() )
                    {
		       numFaces = detectAndDraw( image, cascade, scale, tryflip,substFace );
                        char c = (char)waitKey(0);
                        if( c == 27 || c == 'q' || c == 'Q' )
                            break;
			cout << "Number of faces detected: " << numFaces << endl;
                    }
                    else
                    {
                        cerr << "Aw snap, couldn't read image " << buf << endl;
                    }
                }
                fclose(f);
            }
        }
    }

    return 0;
}
