#ifndef OBJECT_DETECTION_H
#define OBJECT_DETECTION_H

#include <string>
#include <opencv2/opencv.hpp>

namespace OBJDT{
    extern std::string pathOfdata;

    void load_cascade();
    void object_detection(cv::Mat& _frame);
}

#endif