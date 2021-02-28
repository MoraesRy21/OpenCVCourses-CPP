#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void shapesCounterDetection();

void getCouters(cv::Mat& imgDil, cv::Mat& img_out);
