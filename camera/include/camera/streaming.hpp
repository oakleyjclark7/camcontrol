#pragma once

#include <camera/camera_image.hpp>

#include <opencv2/videoio.hpp>

#include <chrono>
#include <thread>

namespace camcontrol::camera
{

class Streaming
{

    cv::VideoCapture vc_;
    int cameraIndex_ = 0;

    std::jthread captureThread_;
    cv::Mat currentImage_;

    std::chrono::milliseconds reconnectionWaitTime_{1000};

  public:
    Streaming();
    ~Streaming();
    Streaming &operator=(const Streaming &other) = delete;
    Streaming &operator=(Streaming &&other) = delete;
    Streaming(const Streaming &other) = delete;
    Streaming(Streaming &&other) = delete;

    void connect();
    void startStreaming(std::function<void(CameraImage)> cb);
    void stopStreaming();
    void disconnect();
};

} // namespace camcontrol::camera