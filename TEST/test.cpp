/*
g++ -o TEST/test TEST/test.cpp -I"C:/msys64/ucrt64/include/opencv4" -L"C:/msys64/ucrt64/lib" -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_objdetect
*/

#include <opencv2/opencv.hpp>
#include <iostream>

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

    while(cap.read(frame)){
        if (frame.empty()) {
            cerr << "Captured an empty frame" << endl;
            break;
        }

        vector<cv::Rect> _detection;
        cv::Mat outputframe;
        cv::cvtColor(frame, outputframe, cv::COLOR_BGR2GRAY);   // Convert the frame to grayscale
        detectionClassifier.detectMultiScale(outputframe, _detection);  // Detect objects in the frame

        // Draw a detections on the frame
        for (const auto& value : _detection) {
            cv::rectangle(frame, value, cv::Scalar(255, 0 ,0), 2, 8, 0); // Scalar is B G R (Blue, Green, Red)
        }

        // Display the frame
        cv::imshow("Video Capture TESTETS", frame);
        
        if (cv::waitKey(10) == 'q' || cv::waitKey(10) == 27) { // 27 is the ASCII code for ESC key
            break;
        }
    }

    // Release the video capture object and close any open windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}