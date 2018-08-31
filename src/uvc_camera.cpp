#include "uvc_camera.hpp"

// Default Constructor
uvc_camera::uvc_camera()
{
  exposive_time = 0;
  resolution = 0;
}

void uvc_camera::startStream(std::string device)
{
  // Create a VideoCapture object and open the input file
  cv::VideoCapture cap(device);

  // Check if camera opened successfully
  if(!cap.isOpened())
  {
    std::cout << "Error opening video stream or file" << std::endl;
  }

}

void uvc_camera::stopStream()
{

}

void uvc_camera::setStream()
{

}
