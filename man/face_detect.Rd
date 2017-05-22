\name{face_detect}
\alias{face_detect}
\title{Simple OpenCV face detection demo.}
\usage{
face_detect(cameraId=0,imgFile="",imgScale=1.0)
}
\arguments{
  \item{cameraId}{Your webcam id. For only one camera, this is usually 0. Try to use 1 if it does not work.}

  \item{imgFile}{Full path of the image file you want to detect faces with.}
  
  \item{imgScale}{the height/width scale of images. Setting 1.0 is ok for most cases.}
}
\value{
if successes, return NULL.
}
\description{
A simple face-detection demo of OpenCV. 
}
\details{
Press 'q' or 'Q' to stop.

The C++ code is modified from 
\url{https://github.com/opencv/opencv_attic/blob/master/opencv/samples/cpp/multicascadeclassifier.cpp}
}
\examples{
# setting camera id = 1
face_detect(1)
face_detect(imgFile="d:/pic/testpic.jpg")
}
