#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <vector>

struct PositionPoint {
	int x;
	int y;
	int value;
};

struct ColorRangeDetection {
	//array struct [_H_min, _S_min, _V_min, _H_max, _S_max, _V_max]
	int _H_min;
	int _S_min;
	int _V_min;
	int _H_max;
	int _S_max;
	int _V_max;
};

void project_1();
void findColor();
void drawOnCanvas();
void drawLineOnCanvas();
cv::Point getCouters(cv::Mat& imgDil);
