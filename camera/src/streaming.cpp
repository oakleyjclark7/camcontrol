#include <camera/camera_image.hpp>
#include <camera/streaming.hpp>

#include <opencv2/core/utils/logger.hpp>

#include <print>

namespace camcontrol::camera
{

Streaming::Streaming()
{
    // be quiet please
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
}

Streaming::~Streaming()
{
    stopStreaming();
}

void Streaming::connect()
{
    captureThread_ = std::jthread([this]() {
        try {
            if (vc_.open(cameraIndex_)) {
                std::println("Connected to camera");
            } else {
                std::println("Connection to camera failed");
            }
        } catch (std::exception &e) {
            std::println("Error while connecting to camera: {}", e.what());
        } catch (...) {
            std::println("Unknown error while connecting to camera");
        }
    });
    if (captureThread_.joinable()) {
        captureThread_.join();
    }
}

void Streaming::startStreaming(std::function<void(CameraImage)> cb)
{
    captureThread_ = std::jthread([this, cb = std::move(cb)](std::stop_token streamingStopToken) {
        try {
            std::println("Starting camera stream");
            cv::Mat frame;
            while (!streamingStopToken.stop_requested()) {
                if (vc_.read(frame)) {
                    CameraImage img(frame);
                    cb(std::move(img));
                } else {
                    // If read fails, we have disconnected. Until stopStreaming_ is called, this will continue to try to
                    // reconnect when disconnected
                    if (vc_.isOpened()) {
                        vc_.release();
                    }
                    std::println("Unabled to retreive camera frame, trying to reconnect");
                    std::this_thread::sleep_for(reconnectionWaitTime_);
                    if (vc_.open(cameraIndex_)) {
                        std::println("Reconnected to camera");
                    }
                }
            }
        } catch (std::exception &e) {
            std::println("Error while streaming from camera: {}", e.what());
        } catch (...) {
            std::println("Unknown error while streaming from camera");
        }
    });
}

void Streaming::stopStreaming()
{
    if (captureThread_.joinable()) {
        captureThread_.get_stop_source().request_stop();
        captureThread_.join();
    }
    captureThread_ = std::jthread([this]() {
        try {
            if (vc_.isOpened()) {
                vc_.release();
            }
        } catch (std::exception &e) {
            std::println("Error while stopping streaming: {}", e.what());
        } catch (...) {
            std::println("Unknown error while stopping streaming");
        }
    });
}

void Streaming::disconnect()
{
    stopStreaming();
}

} // namespace camcontrol::camera