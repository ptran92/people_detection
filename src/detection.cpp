#include <iostream>
#include <cassert>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#define OUTPUT_FPS    20

int main(int argc, char* argv[]){

  std::cout << "Hello world" << "\n";

  cv::VideoCapture capture("nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)I420, framerate=(fraction)120/1 ! \
			nvvidconv flip-method=6 ! video/x-raw, format=(string)BGRx ! \
			videoconvert ! video/x-raw, format=(string)BGR ! \
			appsink");

  assert(capture.isOpened() == true);

  cv::VideoWriter outputVid("appsrc ! autovideoconvert ! omxh265enc ! matroskamux ! filesink location=camera.mkv",
                              // CV_FOURCC('A','V','C','1'),
                              0,
                              OUTPUT_FPS,
                              cv::Size((int)capture.get(cv::CAP_PROP_FRAME_WIDTH),(int)capture.get(cv::CAP_PROP_FRAME_HEIGHT)),
                              true
                            );
  assert(outputVid.isOpened() == true);

  std::cout << "Start recording" << '\n';

  cv::Mat inFrame;
  while(capture.read(inFrame) && outputVid.get(cv::CAP_PROP_FRAME_COUNT) <= 10 ){
    std::cout << "get " << outputVid.get(cv::CAP_PROP_FRAME_COUNT) << '\n';
    outputVid.write(inFrame);
    cv::waitKey(1000);
  }

  std::cout << "Stop recording" << '\n';

  return 0;
}
