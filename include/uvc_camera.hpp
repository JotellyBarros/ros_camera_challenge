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
  int resolution_;
  int codec_;
  int gain_;
  int rotation_;
  int depth_mode_;
  int rescale_height_;
  int rescale_width_;
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
  void setExpose(int value);


  //Getts and Setts
  int exposive_time() const;
  void setExposive_time(int exposive_time);
  int resolution() const;
  void setResolution(int resolution);
  int codec() const;
  void setCodec(int codec);
  int gain() const;
  void setGain(int gain);
  int rotation() const;
  void setRotation(int rotation);
  int depth_mode() const;
  void setDepth_mode(int depth_mode);
  int rescale_height() const;
  void setRescale_height(int rescale_height);
  int rescale_width() const;
  void setRescale_width(int rescale_width);
  int crop_height() const;
  void setCrop_height(int crop_height);
  int crop_width() const;
  void setCrop_width(int crop_width);
  cv::VideoCapture getCap() const;
  void setCap(const cv::VideoCapture &value);
};

#endif // UVC_CAMERA_HPP
