#ifndef ROS_CAMERA_HPP
#define ROS_CAMERA_HPP

#include <thread>
#include <uvc_camera.hpp>
#include "ros_camera_app.hpp"
#include <dynamic_reconfigure/server.h>
#include <ros_camera_challenge/InterfaceConfig.h>

class RosCamera
{
public:
  RosCamera();
  UvcCamera camera_01_;


  void callback(ros_camera_challenge::InterfaceConfig &config, uint32_t level);
  void rosStartStream();
  //void rosStartStream(const char* device);
  void interfaceOfdynamic();
  //void changeThread();

//  static int cont;

};

#endif // ROS_CAMERA_HPP
