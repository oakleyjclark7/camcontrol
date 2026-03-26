#include <camera/find_faces.hpp>

#include <print>

namespace camcontrol::camera
{

FaceDetection::FaceDetection(std::filesystem::path modelPath, Resolution resolution)
    : resolution_(resolution)
{
    faceDetector_ = cv::FaceDetectorYN::create(modelPath.string(), "", cv::Size(resolution.width, resolution.height));
}

std::vector<FacePosition> FaceDetection::findFaces(CameraImage &img)
{
    cv::Mat faces;
    cv::Mat cvImage(
        static_cast<int>(resolution_.height),
        static_cast<int>(resolution_.width),
        CV_8UC3,
        img.data.data());
    assert(cv::Size(resolution_.width, resolution_.height) == cvImage.size());
    faceDetector_->detect(cvImage, faces);

    int numFaces = faces.rows;
    std::vector<FacePosition> facePositions;
    for (int i = 0; i < numFaces; i++) {
        float xLeft = faces.at<float>(i, 0);
        float yTop = faces.at<float>(i, 1);
        float width = faces.at<float>(i, 2);
        float height = faces.at<float>(i, 3);
        uint16_t centerX = static_cast<uint16_t>(xLeft + 0.5 * width);
        uint16_t centerY = static_cast<uint16_t>(yTop + 0.5 * height);
        facePositions.push_back({centerX, centerY});
    }
    return facePositions;
}

} // namespace camcontrol::camera