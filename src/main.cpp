#include <ros_camera_app.hpp>

int main(int argc, char **argv) {
  ros::init(argc, argv, "dynamic_reconfigure");
  RosCamera ros_camera_obj;

  //ros_camera_obj.interfaceOfdynamic();

  std::thread streamThread(&RosCamera::rosStartStream, ros_camera_obj);
  //std::thread dynamicThread(&RosCamera::interfaceOfdynamic, ros_camera_obj);

  ros::spin();
  return 0;
}
