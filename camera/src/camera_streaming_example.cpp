#include <camera/streaming.hpp>

#include <opencv2/highgui.hpp>

#include <chrono>
#include <thread>

using namespace camcontrol;

int main()
{
    camera::Streaming stream;
    stream.connect();
    stream.startStreaming([](camera::CameraImage img) {
        cv::Mat cvframe(img.rows, img.cols, CV_8UC3, img.data.data());
        cv::imshow("camera streaming example", cvframe);
        cv::waitKey(1);
    });
    std::this_thread::sleep_for(std::chrono::milliseconds{5000});
    stream.disconnect();
    return 0;
}