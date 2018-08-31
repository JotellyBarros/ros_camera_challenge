#include "uvc_camera.hpp"


// Default Constructor
cv::VideoCapture UvcCamera::getCap() const
{
  return cap;
}

void UvcCamera::setCap(const cv::VideoCapture &value)
{
  cap = value;
}

int UvcCamera::getExposive_time() const
{
  return exposive_time_;
}

void UvcCamera::setExposive_time(int exposive_time)
{
  exposive_time_ = exposive_time;
}

int UvcCamera::getResolution_height() const
{
  return resolution_height_;
}

void UvcCamera::setResolution_height(int resolution_height)
{
  resolution_height_ = resolution_height;
}

int UvcCamera::getResolution_width() const
{
  return resolution_width_;
}

void UvcCamera::setResolution_width(int resolution_width)
{
  resolution_width_ = resolution_width;
  //resolution_width(config.rescale_height);
}

int UvcCamera::getCodec() const
{
  return codec_;
}

void UvcCamera::setCodec(int codec)
{
  codec_ = codec;
}

int UvcCamera::getGain() const
{
  return gain_;
}

void UvcCamera::setGain(int gain)
{
  gain_ = gain;
}

int UvcCamera::getRotation() const
{
  return rotation_;
}

void UvcCamera::setRotation(int rotation)
{
  rotation_ = rotation;
}

int UvcCamera::getDepth_mode() const
{
  return depth_mode_;
}

void UvcCamera::setDepth_mode(int depth_mode)
{
  depth_mode_ = depth_mode;
}

int UvcCamera::getCrop_height() const
{
  return crop_height_;
}

void UvcCamera::setCrop_height(int crop_height)
{
  crop_height_ = crop_height;
}

int UvcCamera::getCrop_width() const
{
  return crop_width_;
}

void UvcCamera::setCrop_width(int crop_width)
{
  crop_width_ = crop_width;
}

UvcCamera::UvcCamera()
{
  exposive_time_ = 0;
  resolution_height_ = 0;
  resolution_width_ = 0;
  codec_ = 0;
  gain_ = 0;
  rotation_ = 0;
  depth_mode_ = 0;

  crop_height_ = 0;
  crop_width_ = 0;
}

void UvcCamera::startStream(const char* device)
{
  //Create a VideoCapture object and open the input file
  cv::VideoCapture cap(device);
  setCap(cap);

  //Check if camera opened successfully
  if(!getCap().isOpened())
  {
    std::cout << "Error opening video stream or file" << std::endl;
  }

  while(true)
  {
    cv::Mat frame;

    //Define parameters
    cap.set(CV_CAP_PROP_FRAME_WIDTH, getResolution_width());
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, getResolution_height());

    // Capture frame-by-frame
    getCap() >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    // Display the resulting frame
    cv::imshow( "Frame", frame );

    //Press  ESC on keyboard to exit
    char c=(char) cv::waitKey(25);
    if(c == 27)
      break;
  }
}

