#pragma once

#include <opencv2/videoio.hpp>

#include <vector>

namespace camcontrol::camera
{

struct CameraImage {

    int rows = 0;
    int cols = 0;
    std::vector<uint8_t> data;

    CameraImage() = default;

    CameraImage(const cv::Mat &mat)
    {
        cv::Mat tmp = mat.isContinuous() ? mat : mat.clone();

        rows = tmp.rows;
        cols = tmp.cols;

        // Only accept cameras which output 3 channel's of 8 bit unsigned ints
        assert(tmp.depth() == CV_8U);
        assert(tmp.channels() == 3);

        size_t numberOfElements = tmp.total() * tmp.channels();
        const uint8_t *first = reinterpret_cast<const uint8_t *>(tmp.data);
        data.assign(first, first + numberOfElements);
    }
};

} // namespace camcontrol::camera