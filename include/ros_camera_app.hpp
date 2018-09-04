#ifndef ROS_CAMERA_HPP
#define ROS_CAMERA_HPP

#include <thread>
#include <uvc_camera.hpp>
#include "ros_camera_app.hpp"
#include <dynamic_reconfigure/server.h>
#include <ros_camera_challenge/InterfaceConfig.h>
#include <boost/shared_ptr.hpp>

class RosCamera
{
public:
  ros::NodeHandle node;

  typedef ros_camera_challenge::InterfaceConfig Config;
  typedef dynamic_reconfigure::Server<Config> ReconfigureServer;
  boost::shared_ptr<ReconfigureServer> reconfigure_server_;
  Config config_;


  RosCamera();
  UvcCamera camera_01_;

  void rosStartStream();
  void interfaceOfdynamic();
  void callback(ros_camera_challenge::InterfaceConfig &config, uint32_t level);
};

#endif // ROS_CAMERA_HPP
