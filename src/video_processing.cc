#include "video_processing.h"
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <chrono> // time
#include <sstream> // ostringstream

using namespace std;

namespace VDP{
    void process_video_stream(const string& video_source){
        // Capture source
        cv::VideoCapture cap(video_source);
        if(!cap.isOpened()){
            cerr << "Error opening video stream: " << video_source << endl;
            return;
        }

        cv::Mat frame; // Matrix array store pixel
        string winName = "Video Capture"; // Windows Name
        cv::namedWindow(winName, cv::WINDOW_GUI_NORMAL); // Create Windows screen and use WINDOW_GUI_NORMAL screen form
        cv::resizeWindow(winName, 640, 480); // sized of windows screen
        
        // FPS
        double desire_fps = 60.0, fps = 0.0; // Desired FPS
        cap.set(cv::CAP_PROP_FPS, desire_fps); // Attempt to set FPS
        chrono::_V2::system_clock::time_point prev_frame_time = chrono::high_resolution_clock::now();
        int frameCount = 0;

        while(cap.read(frame)){
            if (frame.empty()) {
                cerr << "Captured an empty frame" << endl;
                break;
            }
            string fpsText = fps_cal_tostring(prev_frame_time, chrono::high_resolution_clock::now(), frameCount, fps);

            // Display the FPS on the frame
            cv::putText(frame, fpsText, cv::Point(0, 10), cv::FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(255, 200, 30), 1);
        }
    }
}


string fps_cal_tostring(chrono::high_resolution_clock::time_point& _prev_frame_time, chrono::high_resolution_clock::time_point _new_frame_time, int& _frameCount, double& _fps){
    
    // Calculate FPS
    chrono::duration<double> elapsed = _new_frame_time - _prev_frame_time;
    _frameCount++;
    if (elapsed.count() >= 0.2) { // Update FPS every 0.2 sec 
        _fps = _frameCount / elapsed.count();
        _frameCount = 0;
        _prev_frame_time = chrono::high_resolution_clock::now();;
    }

    // return double FPS to string with precision 3
    ostringstream oss;
    oss << fixed << setprecision(3) << _fps; // set Precition decimal
    string current_fps = "FPS: " + oss.str();
    return current_fps;
}