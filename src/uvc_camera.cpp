#include "uvc_camera.hpp"

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
}

bool UvcCamera::getChangeFrame() const
{
  return changeFrame_;
}

void UvcCamera::setChangeFrame(bool changeFrame)
{
  changeFrame_ = changeFrame;
}

UvcCamera::UvcCamera()
  : buffer_ptr_(nullptr)
  , grab_param_(nullptr)
  , callback_thread(nullptr)
{
}

UvcCamera::~UvcCamera()
{

}

UvcCamera::UvcCamera(const UvcCamera &obj)
  : buffer_ptr_ (obj.buffer_ptr_)
  , callback_thread (obj.callback_thread)
{
}

bool UvcCamera::cameraSetup(CallBackPtr fcnt_ptr, void* obj_ptr)
{
  grab_param_ = fcnt_ptr;
  callback_thread = new std::thread(frameThread, this);
}

void UvcCamera::frameThread(void* params)
{
  UvcCamera *pThis = (UvcCamera *) params;
  cv::VideoCapture video(1);
  int contSet = 0;

  if ( !video.isOpened() )
  {
    return;
  }

  cv::Mat frame;
  while(true)
  {
    bool bSuccess = video.read(frame); // read a new frame from video

    //Breaking the while loop if the frames cannot be captured
    if (bSuccess == false)
    {
      std::cout << "Video camera is disconnected" << std::endl;
      std::cin.get(); //Wait for any key press
      break;
    }

    if(pThis->getChangeFrame() == true) {
      //Define parameters
      video.set(CV_CAP_PROP_FRAME_WIDTH, pThis->getResolution_width());
      video.set(CV_CAP_PROP_FRAME_HEIGHT, pThis->getResolution_height());

      //std::cout << "Resolution of the video : " << video.get(CV_CAP_PROP_FPS) << std::endl;

      //    CV_CAP_PROP_POS_MSEC
      //    CV_CAP_PROP_POS_FRAMES
      //    CV_CAP_PROP_POS_AVI_RATIO
      //    CV_CAP_PROP_FRAME_WIDTH
      //    CV_CAP_PROP_FRAME_HEIGHT
      //    CV_CAP_PROP_FPS
      //    CV_CAP_PROP_FOURCC
      //    CV_CAP_PROP_FRAME_COUNT
      //    CV_CAP_PROP_FORMAT
      //    CV_CAP_PROP_MODE
      //    CV_CAP_PROP_BRIGHTNESS
      //    CV_CAP_PROP_CONTRAST
      //    CV_CAP_PROP_SATURATION
      //    CV_CAP_PROP_HUE
      //    CV_CAP_PROP_GAIN
      //    CV_CAP_PROP_EXPOSURE
      //    CV_CAP_PROP_CONVERT_RGB
      //    CV_CAP_PROP_WHITE_BALANCE
      //    CV_CAP_PROP_RECTIFICATION

      std::cout << "Resolution of the video : " << video.get(CV_CAP_PROP_FRAME_WIDTH) << " x " << video.get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;

      pThis->setChangeFrame(false);
    }
    pThis->grab_param_(frame);
  }
}

