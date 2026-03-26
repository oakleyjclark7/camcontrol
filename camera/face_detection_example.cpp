#include <camera/find_faces.hpp>
#include <camera/streaming.hpp>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <chrono>
#include <print>
#include <thread>

using namespace camcontrol;

int main()
{
    try {
        camera::Streaming stream;

        std::filesystem::path modelPath{
            "C:/Projects/camcontrol/camera/face_detection_yunet_2023mar.onnx"}; // todo(OC) move this to a sensible
                                                                                // place
        camera::Resolution resolution{.width = 640, .height = 480};             // todo(OC) move to config file
        camera::FaceDetection fd{modelPath, resolution};

        stream.connect();
        stream.startStreaming([&fd](camera::CameraImage img) {
            auto faces = fd.findFaces(img);
            cv::Mat cvframe(img.rows, img.cols, CV_8UC3, img.data.data());
            for (const auto &face : faces) {
                cv::drawMarker(
                    cvframe,
                    cv::Point(face.xpix, face.ypix),
                    cv::Scalar(0, 255, 0),
                    cv::MARKER_CROSS,
                    25,
                    4);
            }
            cv::imshow("camera streaming example", std::move(cvframe));
            cv::waitKey(1);
        });
        std::this_thread::sleep_for(std::chrono::minutes{1});
        stream.disconnect();
        return 0;
    } catch (std::exception &e) {
        std::println("{}", e.what());
        return 1;
    } catch (...) {
        std::println("Unknown error");
        return 1;
    }
}