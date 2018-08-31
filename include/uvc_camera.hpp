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

  cv::VideoCapture getCap() const;
  void setCap(const cv::VideoCapture &value);

  int getExposive_time() const;
  void setExposive_time(int exposive_time);
  int getResolution_height() const;
  void setResolution_height(int resolution_height);
  int getResolution_width() const;
  void setResolution_width(int resolution_width);
  int getCodec() const;
  void setCodec(int codec);
  int getGain() const;
  void setGain(int gain);
  int getRotation() const;
  void setRotation(int rotation);
  int getDepth_mode() const;
  void setDepth_mode(int depth_mode);
  int getCrop_height() const;
  void setCrop_height(int crop_height);
  int getCrop_width() const;
  void setCrop_width(int crop_width);
};

#endif // UVC_CAMERA_HPP
