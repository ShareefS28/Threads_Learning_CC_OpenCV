/*
g++ -o src/main src/main.cc src/config.cc src/object_detection.cc src/video_processing.cc -I"C:/msys64/ucrt64/include/opencv4" -L"C:/msys64/ucrt64/lib" -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_objdetect
*/

#include <iostream>
#include "config.h"
#include  "video_processing.h"

using namespace std;

int main(){
    config::load_config("../config/config.txt"); 
    VDP::video_process vp;
    vp.process_video_stream();
    return 0;
}