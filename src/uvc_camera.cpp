#include "uvc_camera.hpp"

// Default Constructor
int UvcCamera::exposive_time() const
{
  return exposive_time_;
}

void UvcCamera::setExposive_time(int exposive_time)
{
  exposive_time_ = exposive_time;
}

int UvcCamera::resolution() const
{
  return resolution_;
}

void UvcCamera::setResolution(int resolution)
{
  resolution_ = resolution;
}

int UvcCamera::codec() const
{
  return codec_;
}

void UvcCamera::setCodec(int codec)
{
  codec_ = codec;
}

int UvcCamera::gain() const
{
  return gain_;
}

void UvcCamera::setGain(int gain)
{
  gain_ = gain;
}

int UvcCamera::rotation() const
{
  return rotation_;
}

void UvcCamera::setRotation(int rotation)
{
  rotation_ = rotation;
}

int UvcCamera::depth_mode() const
{
  return depth_mode_;
}

void UvcCamera::setDepth_mode(int depth_mode)
{
  depth_mode_ = depth_mode;
}

int UvcCamera::rescale_height() const
{
  return rescale_height_;
}

void UvcCamera::setRescale_height(int rescale_height)
{
  rescale_height_ = rescale_height;
}

int UvcCamera::rescale_width() const
{
  return rescale_width_;
}

void UvcCamera::setRescale_width(int rescale_width)
{
  rescale_width_ = rescale_width;
}

int UvcCamera::crop_height() const
{
  return crop_height_;
}

void UvcCamera::setCrop_height(int crop_height)
{
  crop_height_ = crop_height;
}

int UvcCamera::crop_width() const
{
  return crop_width_;
}

void UvcCamera::setCrop_width(int crop_width)
{
  crop_width_ = crop_width;
}

cv::VideoCapture UvcCamera::getCap() const
{
  return cap;
}

void UvcCamera::setCap(const cv::VideoCapture &value)
{
  cap = value;
}

UvcCamera::UvcCamera()
{
  exposive_time_ = 0;
  resolution_ = 0;
  codec_ = 0;
  gain_ = 0;
  rotation_ = 0;
  depth_mode_ = 0;
  rescale_height_ = 0;
  rescale_width_ = 0;
  crop_height_ = 0;
  crop_width_ = 0;
}

void UvcCamera::startStream(const char* device)
{
  std::cout << "Hello Jotelly, va estudar mais!" << std::endl;
  // Create a VideoCapture object and open the input file
  //cv::VideoCapture cap(device);
  //setCap(device);

  // Check if camera opened successfully
//  if(!cap.isOpened())
//  {
//    std::cout << "Error opening video stream or file" << std::endl;
//  }

//  while(1)
//  {
//    cv::Mat frame;

//    // Capture frame-by-frame
//    getCap() >> frame;

//    // If the frame is empty, break immediately
//    if (frame.empty())
//      break;

//    // Display the resulting frame
//    cv::imshow( "Frame", frame );

//    //Press  ESC on keyboard to exit
//    char c=(char) cv::waitKey(25);
//    std::cout << c << std::endl;
//    if(c == 27)
//      break;
//  }
}

void UvcCamera::stopStream()
{
  // When everything done, release the video capture object

  // Closes all the frames
//  destroyAllWindows();
}

void UvcCamera::setExpose(int value)
{

}
