# cvDetect
simple R package for OpenCV face/hand/finger detection demo

Please check http://steve-chen.tw/?p=737

[cvDetect binary file install]

1. Download ROpencv_x64.zip +/- ROpencv_x86_part.zip from

   https://github.com/stevechctw/cvDetect/

2. Uncompress zip file in some directory, e.g., d:\Ropencv

   Under d:\Opencv, there should be etc, include, x64, x86 subdirectories.

3. Modify Windows Environmental Variables:
   add the following new paths to PATH variable:

   d:\Ropencv\x64\mingw\bin;d:\Ropencv\x86\mingw\bin

4. Download cvDetect_0.1.0.zip

5. Enter R, install above zip file with "Install package(s) from local files..." menu

[Simple Usage]

library(cvDetec)
# face detection via webcam
face_detect(cameraId=0)
# face detection in Photo 
face_detect(imgFile="d:/pic/somePeople.jpg")

# hand/palm detection via webcam
hand_detect(cameraId=0)

# finger detection via webcam
finger_detect(cameraId=0)


