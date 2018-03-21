#include <iostream>
#include <cassert>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char* argv[]){
	
	/* Read video stream */
  cv::VideoCapture capture("nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)I420, framerate=(fraction)60 ! nvvidconv ! video/x-raw, format=(string)I420 ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");

  assert(capture.isOpened() == true);

	/* Write video to file */
  cv::VideoWriter outputVid("appsrc ! videoconvert ! omxh264enc ! mpegtsmux ! filesink location=camera.mp4 ", 0, 60, cv::Size((int)capture.get(cv::CAP_PROP_FRAME_WIDTH),(int)capture.get(cv::CAP_PROP_FRAME_HEIGHT)),true);

  assert(outputVid.isOpened() == true);

	/* Start reading */
  std::cout << "Start recording" << '\n';

  cv::Mat inFrame;
	int count = 0;
  while(capture.read(inFrame) && count <= 100 ){
    outputVid.write(inFrame);
		count++;
  }

  std::cout << "Stop recording" << '\n';

  return 0;
}
