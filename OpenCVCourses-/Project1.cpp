#include "Project1.h"

// ======================= Project 1 - Virtual Painter ========================

//Global Variables
cv::Mat img;
std::vector<ColorRangeDetection> myColor = {
		{ 25, 118, 134, 179, 255, 255 }, // Pink
		{ 60, 100, 120, 101, 255, 200 } // Green
};

std::vector<cv::Scalar> myColorValues = {
	{ 255, 0, 255 }, // Pink
	{ 0, 255, 0 } // Green
};

std::vector<PositionPoint> newPoint;

void findColor() {
	cv::Mat imgHSV;
	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

	for (int i = 0; i < myColor.size(); i++) {
		cv::Scalar lower(myColor[i]._H_min, myColor[i]._S_min, myColor[i]._V_min);
		cv::Scalar upper(myColor[i]._H_max, myColor[i]._S_max, myColor[i]._V_max);
		cv::Mat mask;
		cv::inRange(imgHSV, lower, upper, mask);

		cv::Point myPoint = getCouters(mask);

		if (myPoint.x != 0 && myPoint.y != 0) {
			newPoint.push_back({ myPoint.x , myPoint.y, i });
		}
	}
}

void drawOnCanvas() {
	for (int i = 0; i < newPoint.size(); i++) {
		cv::circle(img, cv::Point(newPoint[i].x, newPoint[i].y), 10, myColorValues[newPoint[i].value], cv::FILLED);
	}
}

void drawLineOnCanvas() {
	if (newPoint.size() > 2) {
		for (int i = 0; i < newPoint.size(); i++) {
			if(i > 1)
				cv::line(img, cv::Point(newPoint[(i - 1)].x, newPoint[(i - 1)].y), cv::Point(newPoint[i].x, newPoint[i].y), myColorValues[newPoint[i].value], 5);
		}
	}
}

cv::Point getCouters(cv::Mat& imgDil) {

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//cv::drawContours(img_out, contours, -1, cv::Scalar(255, 0, 255), 2); // Draw contours of the shapes

	std::vector<std::vector<cv::Point>> contourPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	cv::Point myPoint(0, 0);

	for (int i = 0; i < contours.size(); i++) {
		int area = cv::contourArea(contours[i]);
		std::cout << "Area: " << area << std::endl;

		if (area > 1000) { // remove noise

			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);

			std::cout << contourPoly[i].size() << std::endl;
			boundRect[i] = cv::boundingRect(contourPoly[i]);

			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;

			cv::drawContours(img, contourPoly, i, cv::Scalar(255, 0, 255), 2);
			cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 2);
		}
	}
	return myPoint;
}

void project_1() {
	cv::VideoCapture videoCapture(0);
	cv::Mat flipedImage;
	while (true) {
		videoCapture.read(img);
		findColor();
		//drawOnCanvas();
		drawLineOnCanvas(); 

		cv::flip(img, flipedImage, 1);
		cv::imshow("Image", flipedImage);

		cv::waitKey(1);
	}
}