#ifndef UVC_CAMERA_HPP
#define UVC_CAMERA_HPP

#include "std_msgs/String.h"
#include <opencv2/core.hpp>
#include "opencv2/core/version.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include <thread>
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

//---------------------------------Matheus-----------------------------------------
namespace eff_cpp
{

enum BowlEncoding
{
  mono8,
  rgb8,
  bgr8,
  bayer_rg8,
  bayer_gr8,
  bayer_bg8,
  yuv_422
};

class BowlCamera
{
public:
  /**
     * @brief Default Constructor.
     *
     * BowlCamera default constructor.
     *
     * @return nothing.
     */
  explicit BowlCamera();
  /**
     * @brief BowlCamera destructor.
     *
     * BowlCamera destructor.
     *
     * @return nothing.
     */
  virtual ~BowlCamera();
  /**
     * @brief BowlCamera copy constructor.
     * @return nothing.
     */
  BowlCamera(const BowlCamera& obj);

  /**
     * \typedef Typedef to a callback function pointer.
     */
  typedef void (*CallBackPtr)(cv::Mat&);

  void setResolution_width(int resolution_width);
  void setResolution_height(int resolution_height);

  /**
     * @brief Setups the camera regular parameters.
     * @param width Image width.
     * @param height Image height.
     * @param encoding Image encoding.
     * @param fcnt_ptr Pointer to a function to receive the acquired images.
     * @return bool.0
     */
  bool cameraSetup(int width, int height, BowlEncoding encoding,
                   CallBackPtr fcnt_ptr, void *obj_ptr);

  static void frameThread(void* params);

private:

  int *buffer_ptr_;
  std::thread *callback_thread;
  CallBackPtr grab_param_;
  float width_;
  float height_;

};

} //eff_cpp
#endif // UVC_CAMERA_HPP
