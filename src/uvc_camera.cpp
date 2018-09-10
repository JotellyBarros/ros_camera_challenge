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

double_t UvcCamera::getExpousure_time() const
{
  return expousure_time_;
}

void UvcCamera::setExpousure_time(const double_t &expousure_time)
{
  expousure_time_ = expousure_time;
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
  cv::Mat r; //Using rotation
  cv::Rect roi; //Using Crop

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

      // Define parameters Exposure time
      //      video.set(CV_CAP_PROP_EXPOSURE, pThis->getExpousure_time()); //-1 is auto, values range from 0 to 100
      //      std::cout << "getExpousure_time: " << pThis->getExpousure_time() << std::endl;
      //      std::cout << "CV_CAP_PROP_EXPOSURE: " << video.get(CV_CAP_PROP_EXPOSURE) << std::endl;

      pThis->setChangeFrame(false);
    }

    /* Rotation */
    cv::Point2f pt(frame.cols/2., frame.rows/2.);
    cv::Mat r = getRotationMatrix2D(pt, pThis->getRotation() * -1, 1.0);
    cv::warpAffine(frame, frame, r, cv::Size(frame.cols, frame.rows));

    /* Resize */
    cv::resize(frame, frame, cv::Size((float)(video.get(CV_CAP_PROP_FRAME_WIDTH) * (pThis->getRescale_factor() * 5)), (float)(video.get(CV_CAP_PROP_FRAME_HEIGHT) * (pThis->getRescale_factor() * 5))));

    /* Crop */
    roi.x = pThis->getCrop_width();
    roi.y = pThis->getCrop_height();
    roi.width = frame.size().width - (pThis->getCrop_width()*2);
    roi.height = frame.size().height - (pThis->getCrop_height()*2);

    /* Crop the original image to the defined */
    cv::Mat crop = frame(roi);

    pThis->grab_param_(crop);
  }
}
