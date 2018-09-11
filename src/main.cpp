#include <ros_camera_app.hpp>

int main(int argc, char **argv) {
  ros::init(argc, argv, "dynamic_cam");

  RosCamera ros_camera_obj;

  ros_camera_obj.interfaceOfdynamic();
  ros::spin();

  return 0;
}
