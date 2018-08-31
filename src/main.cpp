#include <ros/ros.h>
#include "std_msgs/String.h"
#include <dynamic_reconfigure/server.h>
#include <ros_camera_challenge/InterfaceConfig.h>
#include <thread>
#include <boost/thread/thread.hpp>
#include <opencv2/core.hpp>
#include "opencv2/core/version.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

void callback(ros_camera_challenge::InterfaceConfig &config, uint32_t level) {
  ROS_INFO_STREAM("Sets the Codec parameter: " << config.codec);
  ROS_INFO_STREAM("Sets the Gain parameter : " << config.gain);
  ROS_INFO_STREAM("Sets the Rotation       : " << config.rotation);
  ROS_INFO_STREAM("Sets the Resolution     : " << config.resolution);
  ROS_INFO_STREAM("Sets the Depth_mode     : " << config.depth_mode);
  ROS_INFO_STREAM("Sets the Rescale height : " << config.rescale_height << " width: " << config.rescale_width);
  ROS_INFO_STREAM("Sets the Crop height    : " << config.crop_height << " width: " << config.crop_width);
}

void interfaceOfCamera()
{
  // Create a VideoCapture object and open the input file
  cv::VideoCapture cap("/dev/video1");

  // Check if camera opened successfully
  if(!cap.isOpened()){
    std::cout << "Error opening video stream or file" << std::endl;
  }

  while(1){

    cv::Mat frame;
    // Capture frame-by-frame
    cap >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
      break;


    // Display the resulting frame
    cv::imshow( "Frame", frame );


    //Press  ESC on keyboard to exit
    char c=(char) cv::waitKey(25);
    std::cout << c << std::endl;
    if(c == 27)
      break;
  }
}

void interfaceOfdynamic()
{

  dynamic_reconfigure::Server<ros_camera_challenge::InterfaceConfig> server;
  dynamic_reconfigure::Server<ros_camera_challenge::InterfaceConfig>::CallbackType f;

  while(true){
    f = boost::bind(&callback, _1, _2);
    server.setCallback(f);

    sleep(10);
    ros::spin();
  }
}


int main(int argc, char **argv) {
  ros::init(argc, argv, "dynamic_reconfigure");

  std::thread first (interfaceOfCamera);   // spawn new thread
  std::thread second (interfaceOfdynamic); // spawn new thread

  // synchronize threads:
  first.join();  // pauses until first finishes
  second.join(); // pauses until second finishes

  //http://www.cplusplus.com/reference/thread/thread/
  return 0;
}
