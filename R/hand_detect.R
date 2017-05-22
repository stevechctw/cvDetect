
hand_detect <- function(cameraId=0) {

  if(cameraId == -1)
      stop(file, "No cameraId provided")

  packagePath = find.package("cvDetect")
  xml1 = paste0(packagePath,"/other/1256617233-2-haarcascade-hand.xml")
	    
  .Call("hand_detect", cameraId,xml1,PACKAGE="cvDetect")	  
}


