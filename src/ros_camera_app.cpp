#include "ros_camera_app.hpp"

RosCamera::RosCamera()
{
  camera_.cameraSetup(RosCamera::imageCallback, (void*) this);
}

void RosCamera::callback(ros_camera_challenge::InterfaceConfig &config, uint32_t level)
{
  camera_.setRescale_factor(config.rescale_factor);
  camera_.setResolution_mode(config.resolution);
  camera_.setContrast(config.contrast);
  camera_.setBrightness(config.brightness);
  camera_.setGain(config.gain);
  camera_.setRotation(config.rotation);

  //Flag return InterfaceConfig
  camera_.setChangeFrame(true);
}

void RosCamera::interfaceOfdynamic()
{
  dynamic_reconfigure::Server<Config>::CallbackType f;
  f = boost::bind(&RosCamera::callback, this, _1, _2);
  srv.setCallback(f);
}

void RosCamera::imageCallback(cv::Mat& frame)
{  
  //Display the resulting frame
  cv::imshow( "My First Video", frame );
  cv::waitKey(30);
}
