
finger_detect <- function(cameraId=0) {

  if(cameraId < 0)
      stop(file, "No valid cameraId provided")

  .Call("finger_detect", cameraId,PACKAGE="cvDetect")	    
}
