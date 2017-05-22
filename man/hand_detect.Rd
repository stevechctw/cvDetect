\name{hand_detect}
\alias{hand_detect}
\title{Simple OpenCV hand/palm detection demo.}
\usage{
hand_detect(cameraId=0)
}
\arguments{
  \item{cameraId}{Your webcam id. For only one camera, this is usually 0. Try to use 1 if it does not work.}
}
\value{
if successes, return NULL.
}
\description{
A a simple palm-detection demo of OpenCV. 
}
\details{
Press 'q' or 'Q' to stop.

The C++ code is modified from 
\url{https://www.andol.me/1830/detecting-hand-gestures-using-haarcascades-training/}
}

\examples{
# setting camera id = 1
hand_detect(1)
}
