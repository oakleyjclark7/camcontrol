#include <camera/camera_image.hpp>

#include <opencv2/objdetect/face.hpp>

#include <filesystem>

namespace camcontrol::camera
{

struct FacePosition {
    uint16_t xpix;
    uint16_t ypix;
};

class FaceDetection
{
    std::shared_ptr<cv::FaceDetectorYN> faceDetector_;
    Resolution resolution_;

  public:
    FaceDetection(std::filesystem::path modelPath, Resolution resolution);

    std::vector<FacePosition> findFaces(CameraImage &img);
};

} // namespace camcontrol::camera