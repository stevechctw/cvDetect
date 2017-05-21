# cvDetect
simple R package for OpenCV face/hand/finger detection demo

(Also check http://steve-chen.tw/?p=737 )

## cvDetect binary file install

1. __Download ROpencv_x64.zip +/- ROpencv_x86_part.zip__

   These are compiled OpenCV 3.2.0 binary/libraries by Rtools34 mingw G++ for Windows
   
   ROpencv_x64.zip includes etc, include, x64 sub-directories.
   
   ROpencv_x86.zip only includes x87 sub-directory   

2. __Uncompress zip file(s) in some directory, e.g., d:\Ropencv__

   Under d:\ROpencv, there should be etc, include, x64, x86 subdirectories.

3. __Modify Windows Environment Variables:__

   add ROpencv binray directories to PATH environment variable:
<pre>
   d:\Ropencv\x64\mingw\bin;d:\Ropencv\x86\mingw\bin
</pre>   

4. __Download cvDetect_0.1.0.zip:__

   In R, install zip file by "Install package(s) from local files..." menu

## Usage

<pre>
library(cvDetect)

?face_detect
?hand_detect
?finger_detect

# face detection via webcam
# If cameraId = 0 does not work, try 1, 2,....
face_detect(cameraId=0)

# face detection in Photo 
face_detect(imgFile="d:/pic/somePeople.jpg")

# hand/palm detection via webcam
hand_detect(cameraId=0)

# finger detection via webcam
finger_detect(cameraId=0)
</pre>

