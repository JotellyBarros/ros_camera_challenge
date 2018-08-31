#include <ros_camera_app.hpp>


int main(int argc, char **argv) {
  RosCamera ros_camera_obj;
  ros::init(argc, argv, "dynamic_reconfigure");

  std::thread streamThread(&RosCamera::rosStartStream, ros_camera_obj);
  std::thread dynamicThread(&RosCamera::interfaceOfdynamic, ros_camera_obj);

  streamThread.join();
  dynamicThread.join();

  return 0;
}
