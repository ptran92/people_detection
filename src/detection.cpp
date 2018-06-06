#include <iostream>
#include <memory>
#include <cassert>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <darknet.h>

#define CHECK_SIGN(a, b, s, msg)			\
				do{\
					if(a s b){\
						std::cerr << "[ERR] " << msg << '\n';\
						return -1;\
					}\
				}while(0);

#define CHECK_GRT(a, b, msg) 			CHECK_SIGN(a, b, >, msg)
#define CHECK_EQL(a, b, msg)			CHECK_SIGN(a, b, ==, msg)
#define CHECK_NEQL(a, b, msg)			CHECK_SIGN(a, b, !=, msg)
#define CHECK_LESS(a, b, msg)			CHECK_SIGN(a, b, <, msg)

int main(int argc, char* argv[]){

	/* Set up parameters */
	CHECK_LESS(argc, 3, "Required config file and weight file");
	int idx 			= 1;
	char* cfgFile = argv[idx++];
	char* wgtFile = argv[idx++];

	/* Build and load network */
	network* net;
	net = load_network(cfgFile, wgtFile, 0);
	set_batch_network(net, 1);

	/* Open video source */
	cv::VideoCapture capture(0);
	CHECK_NEQL(capture.isOpened(), true, "Cannot open video source");
	capture.set(CV_CAP_PROP_FRAME_WIDTH	,	network_width(net));
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, network_height(net));

	/* Wait for user start signal */
	std::string input;
	std::cout << "Press any key to proceed......" << '\n';
	std::cin >> input;

	/* Read and preprocess frame */
	cv::Mat inFrame;
	capture.read(inFrame);

	// preprocess input: convert from interleave to planar format
	cv::Mat planarInput;
	std::vector<cv::Mat> channels(3);
	cv::split(inFrame, channels);
	cv::merge(channels, planarInput);

	// convert to float type and normalize data
	cv::Mat fPlanarInput;
	planarInput.convertTo(fPlanarInput, CV_32FC3, 1.0/255);


	/* Feed forward */
	float* outputs = network_predict(net, fPlanarInput.ptr<float>());

	/* Post processing model outputs */
	// TODO: post processing here


	/* Display output */
	cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);
	cv::imshow("Output", inFrame);
	cv::waitKey(0);

	/* Finish */
	capture.release();
	std::cout << "Finish!!!" << '\n';






#if 0

	/* Read video stream */
  // cv::VideoCapture capture("nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720, format=(string)I420, framerate=(fraction)60 ! nvvidconv ! video/x-raw, format=(string)I420 ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");
	cv::VideoCapture capture(0);

  assert(capture.isOpened() == true);

	/* Write video to file */
  //cv::VideoWriter outputVid("appsrc ! videoconvert ! omxh264enc ! mpegtsmux ! filesink location=camera.mp4 ", 0, 60, cv::Size((int)capture.get(cv::CAP_PROP_FRAME_WIDTH),(int)capture.get(cv::CAP_PROP_FRAME_HEIGHT)),true);
	//cv::VideoWriter outputVid("appsrc ! videoconvert ! omxh264enc ! mpegtsmux ! filesink location=camera.mp4 ", 0, 60, cv::Size((int)capture.get(cv::CAP_PROP_FRAME_WIDTH),(int)capture.get(cv::CAP_PROP_FRAME_HEIGHT)),true);

  //assert(outputVid.isOpened() == true);

	/* Start reading */
  std::cout << "Start recording" << '\n';
	cv::namedWindow("output", cv::WINDOW_AUTOSIZE);
  cv::Mat inFrame;
	int count = 0;
  while(capture.read(inFrame) && count <= 100 ){
    // outputVid.write(inFrame);
		cv::imshow("output", inFrame);
		cv::waitKey(100);
		// count++;
  }

  std::cout << "Stop recording" << '\n';
#endif

  return 0;
}
