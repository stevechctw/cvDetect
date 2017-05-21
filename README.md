# cvDetect : Simple OpenCV Image/Webcam Detections for R
Simple R package for OpenCV face/hand/finger detection demo, with the help of Rcpp package. Currently Windows only.

(Also check http://steve-chen.tw/?p=737  (Traditional Chinese page) )

## Install cvDetect binary package (Windows only)

1. __Download ROpencv_x64.zip +/- ROpencv_x86_part.zip__

   These are compiled OpenCV 3.2.0 binary/libraries for Windows by Rtools34 mingw G++ 
   
   ROpencv_x64.zip includes etc, include, and x64 sub-directories.
   
   ROpencv_x86.zip only includes x87 sub-directory   

2. __Uncompress zip file(s) in some directory, e.g., d:\Ropencv__

   Under d:\ROpencv, there should be etc, include, x64, and/or x86 subdirectories.

3. __Modify Windows environment variables:__

   add ROpencv binray directories to __PATH__ environment variable. e.g.  
<pre>
   d:\Ropencv\x64\mingw\bin;d:\Ropencv\x86\mingw\bin
</pre>   

4. __Download cvDetect_0.1.1.zip:__

   In R, install zip file via "Install package(s) from local files..." menu

## Compile and install cvDetect source package (Windows only) 

You have to install Rtools package if you want to compile yourself.

1. __Follows Stepe 1 to Step 3 in above binary package installation procedure.__ 

2. __Add OPENCV Windows environment variables:__

   add, e.g., "d:\Ropencv" , to a new  __OPENCV__ environment variable.
   
3. __Download  cvDetect_0.1.1.tar.gz here.__

4. __In R:__ 

<pre>
install.packages("d:/temp/cvDetect_0.1.1.tar.gz",repos=NULL,type="source")
</pre>

## Usage

Enter 'q' or 'Q' to stop these funcitons.

If cameraId = 0 does not work, try 1, 2,.... 

<pre>
library(cvDetect)

?face_detect
?hand_detect
?finger_detect

# face detection via webcam
face_detect(cameraId=0)

# face detection in Photo 
face_detect(imgFile="d:/pic/somePeople.jpg")

# hand/palm detection via webcam
hand_detect(cameraId=0)

# finger detection via webcam
finger_detect(cameraId=0)
</pre>

## Original C++ detection source codes used in cvDetect

__Face detection:__  OpenCV library demo code  
https://github.com/opencv/opencv_attic/blob/master/opencv/samples/cpp/multicascadeclassifier.cpp

__Hand/Palm detection:__  by Andol Li  
https://www.andol.me/1830/detecting-hand-gestures-using-haarcascades-training/

__Finger detection:__ by Abner Matheus  
https://picoledelimao.github.io/blog/2015/11/15/fingertip-detection-on-opencv/
