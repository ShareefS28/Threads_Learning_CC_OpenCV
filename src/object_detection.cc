#include "object_detection.h"
#include <opencv2/opencv.hpp>
#include <cstddef>  // std::size_t

using namespace std;

namespace OBJDT{
    cv::CascadeClassifier cascadeData; // Load Classifier
    string pathOfdata;

    void load_cascade(){
        if(!cascadeData.load(pathOfdata)){
            std::cerr << "Error loading cascade classifier" << std::endl;
            exit(1);
        }
    };

    void object_detection(cv::Mat& _frame){
        vector<cv::Rect> _detection;
        cv::Mat outputFrameGray;
        cv::cvtColor(_frame, outputFrameGray, cv::COLOR_BGR2GRAY); // Convert the frame to grayscale
        cv::equalizeHist(outputFrameGray, outputFrameGray); // Histogram equalization --> contrast adjustment
        cascadeData.detectMultiScale(outputFrameGray, _detection); // Detect objects in the frame

        for(size_t i=0; i<_detection.size(); ++i){
            cv::rectangle(_frame, _detection[i], cv::Scalar(255, 0 ,0), 2, 8, 0); // Scalar is B G R --> Scalar(Blue, Green, Red)
        }
    }
}