#include "ros_camera_app.hpp"

RosCamera::RosCamera()
{
  camera_.cameraSetup(RosCamera::imageCallback, (void*) this);
}

void RosCamera::callback(ros_camera_challenge::InterfaceConfig &config, uint32_t level) {

  /*ROS_INFO_STREAM("Sets the Codec parameter: " << config.codec);
  ROS_INFO_STREAM("Sets the Gain parameter : " << config.gain);
  ROS_INFO_STREAM("Sets the Rotation       : " << config.rotation);
  ROS_INFO_STREAM("Sets the Resolution     : " << config.resolution);
  ROS_INFO_STREAM("Sets the Depth_mode     : " << config.depth_mode);
  ROS_INFO_STREAM("Sets the Rescale height : " << config.rescale_height << " width: " << config.rescale_width);
  ROS_INFO_STREAM("Sets the Crop height    : " << config.crop_height << " width: " << config.crop_width << std::endl);
*/
  camera_.setResolution_width(config.rescale_width);
  camera_.setResolution_height(config.rescale_height);


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
