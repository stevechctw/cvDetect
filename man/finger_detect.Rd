\name{finger_detect}
\alias{finger_detect}
\title{Simple OpenCV finger detection demo.}
\usage{
finger_detect(cameraId=0)
}
\arguments{
  \item{cameraId}{Your webcam id. For only one camera, this is usually 0. Try to use 1 if it does not work.}
}
\value{
if successes, return NULL.
}
\description{
A simple finger-detection demo of OpenCV. 
}
\details{
Press 'q' or 'Q' to stop.

The C++ code is modified from 
\url{https://picoledelimao.github.io/blog/2015/11/15/fingertip-detection-on-opencv/}
}

\examples{
# setting camera id = 1
finger_detect(1)
}
