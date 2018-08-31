#ifndef UVC_CAMERA_HPP
#define UVC_CAMERA_HPP


class uvc_camera
{
private:
  int exposive_time;
  int resolution;

public:
  //Method Constructor
  uvc_camera();

  startStream("/dev/video1");
  stopStream();
  setStream();


};

#endif // UVC_CAMERA_HPP
