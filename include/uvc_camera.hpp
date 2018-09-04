#ifndef UVC_CAMERA_HPP
#define UVC_CAMERA_HPP

#include "std_msgs/String.h"
#include <opencv2/core.hpp>
#include "opencv2/core/version.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

class UvcCamera
{
private:
  int exposive_time_;
  int resolution_height_;
  int resolution_width_;
  int codec_;
  int gain_;
  int rotation_;
  int depth_mode_;
  int crop_height_;
  int crop_width_;

  // Create a VideoCapture object and open the input file
  cv::VideoCapture cap;

public:
  //Method Constructor
  UvcCamera();

  //void startStream(const char* device);
  void startStream(const char* device);
  void stopStream();

  int resolution_height() const;
  void setResolution_height(int resolution_height);
  int resolution_width() const;
  void setResolution_width(int resolution_width);
};

#endif // UVC_CAMERA_HPP
