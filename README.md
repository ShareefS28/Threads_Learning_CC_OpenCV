## Realtime_object_detection with Concurrent && Caching in C++ Windows OS

### Requirements On Windows
###### MSYS2 installed
```bash
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```
```bash
pacman -S mingw-w64-ucrt-x86_64-opencv
```
```bash
pacman -S mingw-w64-ucrt-x86_64-qt6-base
```

### Test Run files
###### Compile test.cpp
```bash
g++ -o TEST/test TEST/test.cpp -I"C:/msys64/ucrt64/include/opencv4" -L"C:/msys64/ucrt64/lib" -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_objdetect
```
try __```test.exe```__ if you installed correctly it would show window of Video Capture TEST.