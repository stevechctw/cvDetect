
face_detect <- function(cameraId=0,imgFile="",imgScale=1.0) {
  if(cameraId < 0 & !file.exists(imgFile))
      stop(file, "No cameraId provided or image file not found")

  packagePath = find.package("cvDetect")
  xml1 = paste0(packagePath,"/other/haarcascade_frontalface_alt.xml")
  xml2 = paste0(packagePath,"/other/haarcascade_eye_tree_eyeglasses.xml")
	  
  .Call("face_detect", cameraId,imgFile,FALSE,imgScale,xml1,xml2,PACKAGE="cvDetect")	  
}


