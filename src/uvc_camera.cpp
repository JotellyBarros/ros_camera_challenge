#include "uvc_camera.hpp"

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

void UvcCamera::setContrast(int contrast)
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

double_t UvcCamera::getRescale_factor() const
{
  return rescale_factor_;
}

void UvcCamera::setRescale_factor(double_t rescale_factor)
{
  rescale_factor_ = rescale_factor;
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

  cv::Mat frame;
  cv::Mat r; //using rotation

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

      // Define parameters Resolution
      if (pThis->getResolution_mode() == 0)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,160);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,120);
      }
      else if (pThis->getResolution_mode() == 1)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,360);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,640);
      }
      else if (pThis->getResolution_mode() == 2)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,640);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,480);
      }
      else if (pThis->getResolution_mode() == 3)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,720);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,480);
      }
      else if (pThis->getResolution_mode() == 4)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,800);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,600);
      }
      else if (pThis->getResolution_mode() == 5)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,1024);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,768);
      }
      else if (pThis->getResolution_mode() == 6)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,1280);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,720);
      }
      else if (pThis->getResolution_mode() == 7)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,1366);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,768);
      }
      else if (pThis->getResolution_mode() == 8)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,1440);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,900);
      }
      else if (pThis->getResolution_mode() == 9)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,1600);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,900);
      }
      else if (pThis->getResolution_mode() == 10)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,1680);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,1050);
      }
      else if (pThis->getResolution_mode() == 10)
      {
        video.set(CV_CAP_PROP_FRAME_WIDTH,1920);
        video.set(CV_CAP_PROP_FRAME_HEIGHT,1080);
      }

      // Define parameters Contrast and Brightness
      video.set(CV_CAP_PROP_CONTRAST, ((float)pThis->getContrast() / 100));
      video.set(CV_CAP_PROP_BRIGHTNESS, ((float)pThis->getBrightness() / 100));

      pThis->setChangeFrame(false);
    }

    //Rotation
    cv::Point2f pt(frame.cols/2., frame.rows/2.);
    cv::Mat r = getRotationMatrix2D(pt, pThis->getRotation() * -1, 1.0);
    cv::warpAffine(frame, frame, r, cv::Size(frame.cols, frame.rows));

    cv::resize(frame, frame, cv::Size((float)(video.get(CV_CAP_PROP_FRAME_WIDTH) * (pThis->getRescale_factor() * 5)), (float)(video.get(CV_CAP_PROP_FRAME_HEIGHT) * (pThis->getRescale_factor() * 5))));

    pThis->grab_param_(frame);
  }
}

