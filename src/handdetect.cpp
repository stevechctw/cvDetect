/* Modified from https://www.andol.me/1830/detecting-hand-gestures-using-haarcascades-training/ */
#include <Rcpp.h>
#include "opencv2/opencv.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;
using namespace Rcpp;

RcppExport SEXP hand_detect(SEXP cameraId, SEXP xml1) {
BEGIN_RCPP
    Rcpp::RNGScope __rngScope;

    int camera = Rcpp::as<int>(cameraId);	
    Rcpp::CharacterVector fxml1(xml1);
    std::string handxml(fxml1[0]);		

	VideoCapture capture;
	Mat frame;
	CascadeClassifier cascade;


	if( !cascade.load( handxml ) )
	{
        Rcpp::Rcout << "ERROR: Could not load classifier cascade" << std::endl;
        return IntegerVector::create(-1);
	}

	if(!capture.open(camera))
	{	
		Rcpp::Rcout << "Capture from camera #" <<  camera << " didn't work" << std::endl;
		return IntegerVector::create(-1);
	} 
	else
		Rcpp::Rcout << "Capture from camera #" <<  camera << " OK!" << std::endl;

	int edge_thresh = 1;

	while ( capture.isOpened() )
	{
		capture >> frame;
	
		if( frame.empty() )
		{		
			break;
		}
		Mat img = frame.clone();

		Mat gray,edge;
		
		cvtColor( img, gray, COLOR_BGR2GRAY );                
	
		threshold(gray,gray,100,255,THRESH_BINARY);    
	
		GaussianBlur(gray, gray, Size(11, 11),0,0);

		Canny(gray, edge, (float)edge_thresh, (float)edge_thresh*3, 5); 

		vector<Rect> hand;
		cascade.detectMultiScale(img ,hand,
			1.2, 2,0 
			|CASCADE_DO_CANNY_PRUNING,
			Size(100,100) );
		
		for ( size_t i = 0; i < hand.size(); i++ )
		{
			Rect r = hand[i];
			
			rectangle( img, cvPoint(r.x, r.y),
               cvPoint(r.x + r.width, r.y + r.height),
               Scalar(255,0,0), 3,8, 0);				
   
		}			   
		
		imshow("camerawin",img);

		char c = (char)waitKey(10);
		if( c == 27 || c == 'q' || c == 'Q' )
			break;
	}

	return R_NilValue;
END_RCPP
}
