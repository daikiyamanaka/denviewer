#ifndef CAMERACAPTURE_H
#define CAMERACAPTURE_H

#include<opencv2/opencv.hpp>

class CameraCapture
{
public:
    CameraCapture();
    ~CameraCapture();

    void captureImage(cv::Mat &img);

private:
    cv::Mat buf;
    void init();
};

#endif // CAMERACAPTURE_H
