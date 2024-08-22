#ifndef VIDEO_PROCESSING_H
#define VIDEO_PROCESSING_H

#include <opencv2/opencv.hpp>
#include <string>
#include <chrono>

namespace VDP{
    class video_process{
        public:
            void process_video_stream(const int video_source = 0);
        private:
            void process_frame_in_region(cv::Mat& _frame, const cv::Rect& region);
            void two_threads_frame_region(cv::Mat& _frame);
            void four_threads_quadrants_frame(cv::Mat& _frame);
            void define_thread_frame(cv::Mat& _frame, int _threads);
            std::string fps_cal_tostring(std::chrono::high_resolution_clock::time_point& _prev_frame_time, std::chrono::high_resolution_clock::time_point _new_frame_time, int& _frameCount, double& _fps);
    };
}

#endif