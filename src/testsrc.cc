/*
g++ -o src/testsrc src/testsrc.cc src/config.cc src/object_detection.cc -I"C:/msys64/ucrt64/include/opencv4" -L"C:/msys64/ucrt64/lib" -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_objdetect
*/

#include <iostream>
#include "config.h"

int main(){
    config::load_config("../config/config.txt");
    return 0;
}