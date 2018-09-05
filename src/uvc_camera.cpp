#include "uvc_camera.hpp"


int UvcCamera::resolution_height() const
{
  return resolution_height_;
}

void UvcCamera::setResolution_height(int resolution_height)
{
  resolution_height_ = resolution_height;
}

int UvcCamera::resolution_width() const
{
  std::cout << "Get resolution_width_: " << resolution_width_ << std::endl;
  return resolution_width_;
}

void UvcCamera::setResolution_width(int resolution_width)
{
  std::cout << "Set resolution_width_: " << resolution_width_ << std::endl;
  resolution_width_ = resolution_width;
}

/* Default Constructor */
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

  //Check if camera opened successfully
  if(!cap.isOpened())
  {
    std::cout << "Error opening video stream or file" << std::endl;
  }

  while(true)
  {
    cv::Mat frame;

    //Define parameters
    cap.set(CV_CAP_PROP_FRAME_WIDTH, resolution_width());
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, resolution_height());

    // Capture frame-by-frame
    cap >> frame;

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

//--------------------------Matheus----------------------


namespace eff_cpp
{
BowlCamera::BowlCamera()
  : buffer_ptr_(nullptr)
  , grab_param_(nullptr)
  , callback_thread(nullptr)
{
}

BowlCamera::~BowlCamera()
{

}

BowlCamera::BowlCamera(const BowlCamera &obj)
  : buffer_ptr_ (obj.buffer_ptr_)
  , callback_thread (obj.callback_thread)
{
}

void BowlCamera::setResolution_width(int resolution_width)
{
  width_ = resolution_width;
}

void BowlCamera::setResolution_height(int resolution_height)
{
  height_ = resolution_height;
}

bool BowlCamera::cameraSetup(int width, int height, BowlEncoding encoding,
                             CallBackPtr fcnt_ptr, void* obj_ptr)
{
  switch(encoding)
  {
  case BowlEncoding::mono8:
    std::cout << "We get the Mono8\n";
    break;
  case BowlEncoding::rgb8:
    std::cout << "We get the RGB8\n";
    break;
  }

  grab_param_ = fcnt_ptr;

  callback_thread = new std::thread(frameThread, this);
}

void BowlCamera::frameThread(void* params)
{
  std::cout << "Teste" << std::endl;

  BowlCamera *pThis = (BowlCamera *) params;

  cv::VideoCapture video(0);

  if ( !video.isOpened() )
  {
    return;
  }

  cv::Mat frame;

  while(true)
  {
    //Define parameters
    video.set(CV_CAP_PROP_FRAME_WIDTH, pThis->width_);
    video.set(CV_CAP_PROP_FRAME_HEIGHT, pThis->height_);
    std::cout << "Width = " << pThis->width_ << std::endl;

    video >> frame;
    pThis->grab_param_(frame);
  }
}

}
