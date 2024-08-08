/*
g++ -o TEST/test TEST/test.cpp -I"C:/msys64/ucrt64/include/opencv4" -L"C:/msys64/ucrt64/lib" -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_objdetect
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <sstream>

using namespace std;

int main(){
    cv::Mat frame;  // store image data pixel value
    cv::VideoCapture cap(0);    // Capture device 0 
    cv::CascadeClassifier detectionClassifier;  // Load Classifier

    if(!detectionClassifier.load("../data/haarcascades/haarcascade_frontalface_default.xml")){
        cout << "XML file not loaded" << endl;
        exit(1);
    }

    if (!cap.isOpened()) {
        cerr << "Error opening video stream" << endl;
        return -1;
    }
    else {
        cout << "Camera opened successfully." << endl;
    }

    string winName = "Video Capture TEST";
    cv::namedWindow(winName, cv::WINDOW_GUI_NORMAL); // Create a named window with the WINDOW_NORMAL flag
    cv::resizeWindow(winName, 640, 480);
    
    // FPS
    double desire_fps = 60.0, fps = 0.0; // Desired FPS
    cap.set(cv::CAP_PROP_FPS, desire_fps); // Attempt to set FPS
    chrono::_V2::system_clock::time_point prev_frame_time = chrono::high_resolution_clock::now(), new_frame_time;
    int frameCount = 0;

    while(cap.read(frame)){
        if (frame.empty()) {
            cerr << "Captured an empty frame" << endl;
            break;
        }

        // Calculate FPS
        new_frame_time = chrono::system_clock::now();
        chrono::duration<double> elapsed = new_frame_time - prev_frame_time;
        frameCount++;
        if (elapsed.count() >= 0.2) { // Update FPS every second --> elapsed.count() >= 1 it's mean update every second if it was 0.5 --> every 0.5 sec
            fps = frameCount / elapsed.count();
            frameCount = 0;
            prev_frame_time = chrono::high_resolution_clock::now();;
        }

        // Display the FPS on the frame
        ostringstream oss;
        oss << fixed << setprecision(3) << fps; // set Precition decimal
        string fpsText = "FPS: " + oss.str();
        cv::putText(frame, fpsText, cv::Point(0, 10), cv::FONT_HERSHEY_SIMPLEX, 0.35, cv::Scalar(255, 200, 30), 1);

        // detection classifier
        vector<cv::Rect> _detection;
        cv::Mat outputframe;
        cv::cvtColor(frame, outputframe, cv::COLOR_BGR2GRAY);   // Convert the frame to grayscale
        detectionClassifier.detectMultiScale(outputframe, _detection);  // Detect objects in the frame

        // Draw a detections on the frame
        for (const auto& value : _detection) {
            cv::rectangle(frame, value, cv::Scalar(255, 0 ,0), 2, 8, 0); // Scalar is B G R (Blue, Green, Red)
        }

        // Display the frame
        cv::imshow(winName, frame);
        
        // Keys for exit
        if (cv::waitKey(10) == 'q' || cv::waitKey(10) == 27 || cv::getWindowProperty(winName, cv::WND_PROP_VISIBLE) < 1) { // 27 is the ASCII code for ESC key
            break;
        }
    }

    // Release the video capture object and close any open windows
    cout << "Camera Close successfully." << endl;
    cap.release();
    cv::destroyAllWindows();

    return 0;
}