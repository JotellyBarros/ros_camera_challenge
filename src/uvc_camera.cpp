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

int UvcCamera::getBrightness() const
{
  return brightness_;
}

void UvcCamera::setBrightness(float brightness)
{
  brightness_ = brightness;
}

int UvcCamera::getContrast() const
{
  return contrast_;
}

void UvcCamera::setContrast(float contrast)
{
  contrast_ = contrast;
}

int UvcCamera::getResolution_mode() const
{
  return resolution_mode_;
}

void UvcCamera::setResolution_mode(int resolution_mode)
{
  resolution_mode_ = resolution_mode;
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
  cv::VideoCapture video(0);

  if ( !video.isOpened() )
  {
    std::cout << "Video camera is disconnected" << std::endl;
  }

  //Configuration Beginner
  //  pThis->setBrightness(20);
  //  pThis->setContrast(10);
    //pThis->setResolution_height(640);
    //pThis->setResolution_width(480);

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

    if(pThis->getChangeFrame() == true)
    {

      /*if (pThis->getResolution_mode() == 0)
      {
        pThis->setResolution_height(320);
        pThis->setResolution_width(240);
      }
      else if (pThis->getResolution_mode() == 1)
      {
        pThis->setResolution_height(640);
        pThis->setResolution_width(480);
      }
      else if (pThis->getResolution_mode() == 2)
      {
        pThis->setResolution_height(950);
        pThis->setResolution_width(540);
      }*/

      //Define parameters
      //video.set(CV_CAP_PROP_FRAME_WIDTH, pThis->getResolution_width());
      //video.set(CV_CAP_PROP_FRAME_HEIGHT, pThis->getResolution_height());

      video.set(CV_CAP_PROP_CONTRAST, ((float)pThis->getContrast() / 100));
      video.set(CV_CAP_PROP_BRIGHTNESS, ((float)pThis->getBrightness() / 100));

      std::cout << "Resolution of the video :: " << video.get(CV_CAP_PROP_FRAME_WIDTH) << " x " << video.get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;
      cv::resize(frame, frame, cv::Size(pThis->getResolution_height() * 0.75,pThis->getResolution_width() * 0.75), 0, 0, CV_INTER_LINEAR);

      //cv::resize(pThis->grab_param_(frame), frame, cv::Size(100, 100), 0, 0, CV_INTER_LINEAR);

      //      CAP_PROP_POS_MSEC Current position of the video file in milliseconds or video capture timestamp.
      //      CAP_PROP_POS_FRAMES 0-based index of the frame to be decoded/captured next.
      //      CAP_PROP_POS_AVI_RATIO Relative position of the video file: 0 - start of the film, 1 - end of the film.
      //      CAP_PROP_FRAME_WIDTH Width of the frames in the video stream.
      //      CAP_PROP_FRAME_HEIGHT Height of the frames in the video stream.
      //      CAP_PROP_FPS Frame rate.
      //      CAP_PROP_FOURCC 4-character code of codec.
      //      CAP_PROP_FRAME_COUNT Number of frames in the video file.
      //      CAP_PROP_FORMAT Format of the Mat objects returned by retrieve() .
      //      CAP_PROP_MODE Backend-specific value indicating the current capture mode.
      //      CAP_PROP_BRIGHTNESS Brightness of the image (only for cameras).
      //      CAP_PROP_CONTRAST Contrast of the image (only for cameras).
      //      CAP_PROP_SATURATION Saturation of the image (only for cameras).
      //      CAP_PROP_HUE Hue of the image (only for cameras).
      //      CAP_PROP_GAIN Gain of the image (only for cameras).
      //      CAP_PROP_EXPOSURE Exposure (only for cameras).
      //      CAP_PROP_CONVERT_RGB Boolean flags indicating whether images should be converted to RGB.
      //      CAP_PROP_WHITE_BALANCE Currently not supported
      //      CAP_PROP_RECTIFICATION Rectification flag for stereo cameras (note: only supported by DC1394 v 2.x backend currently)

      //std::cout << "CODEC : " << video.get(CV_CAP_PROP_FORMAT) << std::endl;
      //std::cout << "CONTRAST : " << video.get(CV_CAP_PROP_CONTRAST) << std::endl;
      //std::cout << "BRIGHTNESS : " << video.get(CV_CAP_PROP_BRIGHTNESS) << std::endl;
      std::cout << "Resolution of the video : " << video.get(CV_CAP_PROP_FRAME_WIDTH) << " x " << video.get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;

      pThis->setChangeFrame(false);
    }
    pThis->grab_param_(frame);
  }
}

