/* Original source: https://github.com/opencv/opencv_attic/blob/master/opencv/samples/cpp/multicascadeclassifier.cpp */
#include <Rcpp.h>
// OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;
using namespace Rcpp;

void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, bool tryflip );

string cascadeName;
string nestedCascadeName;

/* int main( int argc, const char** argv ) */
RcppExport SEXP face_detect( SEXP cameraId, SEXP imgFile, SEXP flip, SEXP imgScale, SEXP xml1, SEXP xml2) {
BEGIN_RCPP
    Rcpp::RNGScope __rngScope;
  
    Rcpp::CharacterVector fname(imgFile);
    std::string inputName(fname[0]);
	
    int camera = Rcpp::as<int>(cameraId);
    bool tryflip = Rcpp::as<bool>(flip);
    double scale = Rcpp::as<double>(imgScale);
	
    Rcpp::CharacterVector fxml1(xml1);
    std::string cascadeName(fxml1[0]);	

    Rcpp::CharacterVector fxml2(xml2);
    std::string nestedCascadeName(fxml2[0]);		
	
    VideoCapture capture;
    Mat frame, image;
    CascadeClassifier cascade, nestedCascade;
	
    /* string inputName; 
     bool tryflip; 
     double scale; */

/*	
    cv::CommandLineParser parser(argc, argv,
        "{help h||}"
        "{cascade|../../data/haarcascades/haarcascade_frontalface_alt.xml|}"
        "{nested-cascade|../../data/haarcascades/haarcascade_eye_tree_eyeglasses.xml|}"
        "{scale|1|}{try-flip||}{@filename||}"
    );
    if (parser.has("help"))
    {
        help();
        return 0;
    }
*/	
    /* cascadeName = parser.get<string>("cascade"); */
	
	/*
	cascadeName = "haarcascade_frontalface_alt.xml";
    nestedCascadeName = "haarcascade_eye_tree_eyeglasses.xml";
	*/

	/*
    scale = parser.get<double>("scale");
    if (scale < 1)
        scale = 1;

    tryflip = parser.has("try-flip"); 
    inputName = parser.get<string>("@filename");

    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }

	inputName = parser.get<string>("@filename");
	*/
	
    if ( !nestedCascade.load( nestedCascadeName ) )		
        Rcpp::Rcout << "WARNING: Could not load classifier cascade for nested objects" << std::endl;
		/*cerr << "WARNING: Could not load classifier cascade for nested objects" << endl; */
	
    if( !cascade.load( cascadeName ) )
    {
        Rcpp::Rcout << "ERROR: Could not load classifier cascade" << std::endl;
		/* cerr << "ERROR: Could not load classifier cascade" << endl; 
        help();
		*/
        return IntegerVector::create(-1);
    }
	
    /* if( inputName.empty() || (isdigit(inputName[0]) && inputName.size() == 1) ) */
	if( inputName.empty() || (isdigit(camera))) 
    {
        /* int camera = inputName.empty() ? 0 : inputName[0] - '0'; */
		/* int camera = cameraId; */
        if(!capture.open(camera))
            Rcpp::Rcout << "Capture from camera #" <<  camera << " didn't work" << std::endl;
		    /* cout << "Capture from camera #" <<  camera << " didn't work" << endl; */
    }
	
    else if( inputName.size() )
    {
        image = imread( inputName, 1 );
        if( image.empty() )
        {
            if(!capture.open( inputName ))
                Rcpp::Rcout << "Could not read " << inputName << std::endl;
			    /* cout << "Could not read " << inputName << endl; */
        }
    }
	/*
    else
    {
        image = imread( "../data/lena.jpg", 1 );
        if(image.empty()) cout << "Couldn't read ../data/lena.jpg" << endl;
    }
	*/

    if( capture.isOpened() )
    {
        Rcpp::Rcout << "Video capturing has been started ..." << std::endl;
		/* cout << "Video capturing has been started ..." << endl; */

        for(;;)
        {
            capture >> frame;
            if( frame.empty() )
                break;

            Mat frame1 = frame.clone();
            detectAndDraw( frame1, cascade, nestedCascade, scale, tryflip ); 			

            char c = (char)waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' )
                break;
        }
    }
    else
    {
        Rcpp::Rcout << "Detecting face(s) in " << inputName << std::endl;
		
        if( !image.empty() )
        {
            detectAndDraw( image, cascade, nestedCascade, scale, tryflip );
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
                    /* cout << "file " << buf << endl; */
					Rcpp::Rcout << "file " << buf << std::endl;
					
                    image = imread( buf, 1 );
                    if( !image.empty() )
                    {
						detectAndDraw( image, cascade, nestedCascade, scale, tryflip );
                        char c = (char)waitKey(0);
                        if( c == 27 || c == 'q' || c == 'Q' )
                            break;
                    }
                    else
                    {
                        /* cerr << "Aw snap, couldn't read image " << buf << endl; */
						Rcpp::Rcout << "Aw snap, couldn't read image " << buf << std::endl;
                    }
                }
                fclose(f);
            }
        }
    }

    /* return 0; */
	return R_NilValue;
END_RCPP  	
}

void detectAndDraw( Mat& img, CascadeClassifier& cascade,
                    CascadeClassifier& nestedCascade,
                    double scale, bool tryflip )
{
    double t = 0;
    vector<Rect> faces, faces2;
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
    Mat gray, smallImg;

    cvtColor( img, gray, COLOR_BGR2GRAY );
    double fx = 1 / scale;
    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR );
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
	
    /* printf( "detection time = %g ms\n", t*1000/getTickFrequency()); */
	
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Scalar color = colors[i%8];
        int radius;

        double aspect_ratio = (double)r.width/r.height;
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
        {
            center.x = cvRound((r.x + r.width*0.5)*scale);
            center.y = cvRound((r.y + r.height*0.5)*scale);
            radius = cvRound((r.width + r.height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );
        }
        else
            rectangle( img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
                       cvPoint(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
                       color, 3, 8, 0);
        if( nestedCascade.empty() )
            continue;
        smallImgROI = smallImg( r );
        nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
            1.1, 2, 0
            //|CASCADE_FIND_BIGGEST_OBJECT
            //|CASCADE_DO_ROUGH_SEARCH
            //|CASCADE_DO_CANNY_PRUNING
            |CASCADE_SCALE_IMAGE,
            Size(30, 30) );
			
        for ( size_t j = 0; j < nestedObjects.size(); j++ )
        {
            Rect nr = nestedObjects[j];
            center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
            center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
            radius = cvRound((nr.width + nr.height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );
        }
    }
    imshow( "result", img );
}
