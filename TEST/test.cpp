/*
cd {$workingspace}> g++ -o TEST/test TEST/test.cpp -I"C:/msys64/ucrt64/include/opencv4" -L"C:/msys64/ucrt64/lib" -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main(){
    cv::VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        cerr << "Error opening video stream" << endl;
        return -1;
    }
    else {
    cout << "Camera opened successfully." << endl;
    }

    cv::Mat frame;
    while(1){
        if(!cap.read(frame)){
            cout << "Video camera is disconnected" << endl;
            cin.get();
            break;
        };

        if (frame.empty()) {
            cerr << "Error: Empty frame captured." << std::endl;
            break;
        }

        // Display the frame
        cv::imshow("Video Capture TESTETS", frame);
        
        if (cv::waitKey(30) == 'q' || cv::waitKey(30) == 27) { // 27 is the ASCII code for ESC key
            break;
        }
    }

    // Release the video capture object and close any open windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}