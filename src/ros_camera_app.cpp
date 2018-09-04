#include "ros_camera_app.hpp"

RosCamera::RosCamera()
{
  //  RosCamera::cont = 0;

}

void RosCamera::rosStartStream()
{
  std::cout << "Start rosStartStream ";
  camera_01_.startStream("/dev/video0");
}

void RosCamera::callback(ros_camera_challenge::InterfaceConfig &config, uint32_t level) {

  ROS_INFO_STREAM("Sets the Codec parameter: " << config.codec);
  ROS_INFO_STREAM("Sets the Gain parameter : " << config.gain);
  ROS_INFO_STREAM("Sets the Rotation       : " << config.rotation);
  ROS_INFO_STREAM("Sets the Resolution     : " << config.resolution);
  ROS_INFO_STREAM("Sets the Depth_mode     : " << config.depth_mode);
  ROS_INFO_STREAM("Sets the Rescale height : " << config.rescale_height << " width: " << config.rescale_width);
  ROS_INFO_STREAM("Sets the Crop height    : " << config.crop_height << " width: " << config.crop_width << std::endl);

  camera_01_.setResolution_width(config.crop_width);
  camera_01_.setResolution_height(config.crop_height);

}

void RosCamera::interfaceOfdynamic()
{
  // Set up a dynamic reconfigure server.
  dynamic_reconfigure::Server<ros_camera_challenge::InterfaceConfig> server;
  dynamic_reconfigure::Server<ros_camera_challenge::InterfaceConfig>::CallbackType f;

  f = boost::bind(&RosCamera::callback, this, _1, _2);
  server.setCallback(f);
  ros::spinOnce();
}
