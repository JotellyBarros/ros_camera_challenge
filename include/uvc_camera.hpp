#ifndef UVC_CAMERA_HPP
#define UVC_CAMERA_HPP

#include "std_msgs/String.h"
#include <opencv2/core.hpp>
#include "opencv2/core/version.hpp"
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <thread>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class UvcCamera
{
public:
  /**
     * @brief Default Constructor.
     *
     * BowlCamera default constructor.
     *
     * @return nothing.
     */
  explicit UvcCamera();
  /**
     * @brief BowlCamera destructor.
     *
     * BowlCamera destructor.
     *
     * @return nothing.
     */
  virtual ~UvcCamera();
  /**
     * @brief BowlCamera copy constructor.
     * @return nothing.
     */
  UvcCamera(const UvcCamera& obj);

  /**
     * \typedef Typedef to a callback function pointer.
     */
  typedef void (*CallBackPtr)(cv::Mat&);

  /**
     * @brief Setups the camera regular parameters.
     * @param width Image width.
     * @param height Image height.
     * @param encoding Image encoding.
     * @param fcnt_ptr Pointer to a function to receive the acquired images.
     * @return bool.0
     */
  bool cameraSetup(CallBackPtr fcnt_ptr, void *obj_ptr);

  static void frameThread(void* params);

  bool getChangeFrame() const;
  void setChangeFrame(bool changeFrame);

  int getBrightness() const;
  void setBrightness(float brightness);

  int getContrast() const;
  void setContrast(int contrast);

  int getResolution_mode() const;
  void setResolution_mode(int resolution_mode);

  int getRotation() const;
  void setRotation(int rotation);

  double_t getRescale_factor() const;
  void setRescale_factor(double_t rescale_factor);

  int getResolution_height() const;
  void setResolution_height(int resolution_height);

  int getResolution_width() const;
  void setResolution_width(int resolution_width);

  int getCrop_height() const;
  void setCrop_height(int crop_height);

  int getCrop_width() const;
  void setCrop_width(int crop_width);

  double_t getExpousure_time() const;
  void setExpousure_time(const double_t &expousure_time);

private:
  int *buffer_ptr_;
  std::thread *callback_thread;
  CallBackPtr grab_param_;

  double_t rescale_factor_;
  double_t expousure_time_;
  bool changeFrame_ = false;
  int resolution_mode_;
  int brightness_;
  int contrast_;
  int rotation_;
  int crop_height_;
  int crop_width_;

};
#endif // UVC_CAMERA_HPP
