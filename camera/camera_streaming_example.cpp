#include <camera/streaming.hpp>

#include <opencv2/highgui.hpp>

#include <chrono>
#include <print>
#include <thread>

using namespace camcontrol;

int main()
{
    try {
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
    } catch (std::exception &e) {
        std::println("Error while streaming from camera: {}", e.what());
        return 1;
    } catch (...) {
        std::println("Uknown error while streaming from camera");
        return 1;
    }
}