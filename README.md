# cvDetect : Simple OpenCV Image/Webcam Detections for R
Simple R package for OpenCV face/hand/finger detection demo, with the help of [ROpenCVLite](https://github.com/swarm-lab/ROpenCVLite) and Rcpp packages. Currently Windows only.

(Also check http://steve-chen.tw/?p=737  (Traditional Chinese page) )

![3 Detection](http://steve-chen.tw/wp-content/uploads/2017/05/all000.jpg)

## Related tool/package/library versions for creating this package

__Winodws 7 OS 64 bit__  
__R__: 3.4.0  
__Rtools__: Rtools34.exe  
__Rcpp__: 0.12.10  
__OpenCV__: 3.2.0  
__ROpenCVLite__: 0.1.1

## Install cvDetect binary package (Windows only)

1. __Download ROpencv_x64.zip +/- ROpencv_x86_part.zip__

   These are compiled OpenCV 3.2.0 binaries/libraries for Windows by Rtools34 mingw G++, using ROpenCVLite package.
   
   ROpencv_x64.zip includes etc, include, and x64 sub-directories.
   
   ROpencv_x86.zip only includes x87 sub-directory   

2. __Uncompress zip file(s) in some directory, e.g., d:\ROpencv__

   Under d:\ROpencv, there should be etc, include, x64, and/or x86 subdirectories.

__Note:__ 

If you feel uncomfortable to download binary files in 1. and 2. in this page, you can build them yourself by installing [ROpenCVLite](https://github.com/swarm-lab/ROpenCVLite)  package and copy all the files and sub-directories under the compiled "opencv" directory it builds to a new directory (e.g. d:\ROpencv). The compiled "opencv" directory can be located in, e.g., d:\R\R-3.4.0\library\ROpenCVLite .

3. __Modify PATH environment variable via Windows Control Panel:__

   add ROpencv binray directories to __PATH__ environment variable.     
   This ensures R to find related OpenCV dll files when running cvDetect.  
   e.g.  
<pre>
   d:\ROpencv\x64\mingw\bin;d:\ROpencv\x86\mingw\bin;............... 
   or only
   d:\ROpencv\x64\mingw\bin;............... 
</pre>   
   

4. __Download cvDetect_0.1.1.zip:__

   In R, install zip file via "Install package(s) from local files..." menu

## Compile and install cvDetect source package (Windows only) 

We have to install [Rtools](https://cran.r-project.org/bin/windows/Rtools/) if we want to compile cvDetect from source.

1. __Follow Stepe 1 to Step 3 in above binary package installation procedure.__ 

2. __Add an OPENCV environment variable via Windows Control Panel:__

   add, e.g., "d:\Ropencv" , to a new  __OPENCV__ environment variable.

   This OPENCV environment varible is used in Makevars.win inside src directory.
   
3. __Download  cvDetect_0.1.1.tar.gz in this page.__

4. __In R:__ 

   Suppose we save cvDetect_0.1.1.tar.gz under d:\temp directory:  
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
