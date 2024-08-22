#include "video_processing.h"
#include "object_detection.h"
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>
#include <chrono> // time
#include <sstream> // ostringstream

using namespace std;

namespace VDP{
    /* 
        public
    */  
    void video_process::process_video_stream(const int video_source){
        cv::VideoCapture cap(video_source); // Capture source
        
        OBJDT::load_cascade(); // load CascadeData

        if(!cap.isOpened()){
            cerr << "Error opening video stream: " << video_source << endl;
            return;
        }

        cv::Mat frame; // Matrix array store pixel
        string winName = "Video Capture"; // Windows Name
        cv::namedWindow(winName, cv::WINDOW_GUI_NORMAL); // Create Windows screen and use WINDOW_GUI_NORMAL screen form
        cv::resizeWindow(winName, 640, 480); // sized of windows screen WIDTH x HEIGHT
        
        // FPS
        double desire_fps = 60.0, fps = 0.0;
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

            // Parallel threads processing
            // two_threads_frame_region(frame);
            four_threads_quadrants_frame(frame);
            // define_thread_frame(frame, 8);
            

            // Display the frame
            cv::imshow(winName, frame);

            // Keys for exit
            if (cv::waitKey(10) == 'q' || cv::waitKey(10) == 27 || cv::getWindowProperty(winName, cv::WND_PROP_VISIBLE) < 1) { // 27 is the ASCII code for ESC key
                break;
            }
        }
    }
    
    /* 
        private
    */  
    void video_process::process_frame_in_region(cv::Mat& _frame, const cv::Rect& region){
        // cout << "Processing region: " << region << endl; // Debugging line
        cv::Mat  sub_frame = _frame(region).clone(); // Deep Copy
        OBJDT::object_detection(sub_frame);
        sub_frame.copyTo(_frame(region)); // Copy the processed sub_frame back to the original frame
    }

    void video_process::two_threads_frame_region(cv::Mat& _frame){
        // Split the frame into top and bottom halves for parallel processing
        cv::Rect top_half(0, 0, _frame.cols, _frame.rows / 2);
        cv::Rect bottom_half(0, _frame.rows / 2, _frame.cols, _frame.rows / 2);

        // Create threads to process each region
        thread top_thread(&video_process::process_frame_in_region, this, ref(_frame), top_half); // ref() is passing a reference memory || normal looks without thread process_frame_in_region(frame, top_half)
        thread bottom_thread(&video_process::process_frame_in_region, this, ref(_frame), bottom_half); // ref() is passing a reference memory || normal looks without thread process_frame_in_region(frame, bottom_half)
        
        // Wait for both threads to complete
        top_thread.join();
        bottom_thread.join();
    }

    void video_process::four_threads_quadrants_frame(cv::Mat& _frame){
        // Split the frame into top and bottom halves for parallel processing --> Axis_Correseponse_Images.jpg
        int rows = _frame.rows; // X_Rows corresponds to the height of the image.
        int cols = _frame.cols; // Y_Cols corresponds to the width of the image.
        int half_rows = rows / 2;
        int half_cols = cols / 2;

        cv::Rect regions[4] = {
            cv::Rect(0, 0, half_cols, half_rows), // Top Left --> (start_x_Pos, start_y_Pos, extend_to_width_y, extend_to_height_x)
            cv::Rect(half_cols, 0, cols - half_cols, half_rows), // Top Right --> (start_x_Pos, start_y_Pos, extend_to_width_y, extend_to_height_x)
            cv::Rect(0, half_rows, half_cols, rows - half_rows), // Bottom Left --> (start_x_Pos, start_y_Pos, extend_to_width_y, extend_to_height_x)
            cv::Rect(half_cols, half_rows, cols - half_cols, rows - half_rows), // Bottom Right --> (start_x_Pos, start_y_Pos, extend_to_width_y, extend_to_height_x)
        };

        // Create threads to process each quadrant
        vector<thread> threads;
        for(int i=0; i < sizeof(regions)/sizeof(regions[0]); ++i){
            threads.emplace_back(&video_process::process_frame_in_region, this, ref(_frame), regions[i]);
        }

        // Wait for all threads to complete
        for(thread& _thread: threads){
            if(_thread.joinable()){
                _thread.join();
            }
        }
    }

    void video_process::define_thread_frame(cv::Mat& _frame, int _threads){
        if((_threads % 2) != 0){
            cerr << "(int _threads) at define_thread_frame should be EVEN Value;" << endl;
            exit(1);
        };

        int rows = _frame.rows;
        int cols = _frame.cols;
        int sub_rows = rows / _threads;
        int sub_cols = cols / _threads;

        // Create threads and process each quadrant
        vector<thread> threads;
        for(int i=0; i < _threads; ++i){
            for(int j=0; j < _threads; ++j){
                cv::Rect region(j * sub_cols, i * sub_rows, sub_cols, sub_rows);
                threads.emplace_back(&video_process::process_frame_in_region, this, ref(_frame), region);
            }
        }

        // Wait for all threads to complete
        for(thread& _thread: threads){
            if(_thread.joinable()){
                _thread.join();
            }
        }
    }

    string video_process::fps_cal_tostring(chrono::high_resolution_clock::time_point& _prev_frame_time, chrono::high_resolution_clock::time_point _new_frame_time, int& _frameCount, double& _fps){
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
}