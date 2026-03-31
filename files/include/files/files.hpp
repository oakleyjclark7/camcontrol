#pragma once

#include <QtCore/qstandardpaths.h>

#include <filesystem>
#include <print>

namespace camcontrol::files
{

inline void ensurePathExists(std::filesystem::path source, std::filesystem::path destination)
{
    if (!std::filesystem::exists(source)) {
        std::println("Source missing at {}", source.string());
        assert(false);
    }
    if (!std::filesystem::exists(destination)) {
        std::filesystem::create_directories(destination.parent_path());
        std::filesystem::copy_file(source, destination);
    }
}

// The home folder for all app data
inline std::filesystem::path appDirectory()
{
    return std::filesystem::path(
        QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation).toStdString() + "/camcontrol");
}

inline std::filesystem::path buildResourceDirectory()
{
    return std::filesystem::path("resources");
}

inline std::filesystem::path installResourceDirectory()
{
#ifdef DEBUG
    return buildResourceDirectory();
#else
    return std::filesystem::path(appDirectory() / "resources");
#endif
}

inline std::filesystem::path cameraConfig()
{
    auto source = std::filesystem::path(buildResourceDirectory() / "camera.txt");
    auto destination = std::filesystem::path(installResourceDirectory() / "camera.txt");
    ensurePathExists(source, destination);
    return destination;
}

inline std::filesystem::path faceDetectionModel()
{
    auto source = std::filesystem::path(buildResourceDirectory() / "face_detection_yunet_2023mar.onnx");
    auto destination = std::filesystem::path(installResourceDirectory() / "face_detection_yunet_2023mar.onnx");
    ensurePathExists(source, destination);
    return destination;
}

} // namespace camcontrol::files