#include "Chapter7.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// ================= Shapes and Counter Detection ================

void getCouters(cv::Mat& imgDil, cv::Mat& img_out) {

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE); 
	//cv::drawContours(img_out, contours, -1, cv::Scalar(255, 0, 255), 2); // Draw contours of the shapes

	std::vector<std::vector<cv::Point>> contourPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());
	std::string objectType;

	for (int i = 0; i < contours.size(); i++) {
		int area = cv::contourArea(contours[i]);
		std::cout << "Area: " << area << std::endl;

		if (area > 1000) { // remove noise

			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);

			std::cout << contourPoly[i].size() << std::endl;
			boundRect[i] = cv::boundingRect(contourPoly[i]);

			int objVertexCorners = (int) contourPoly[i].size();

			if (objVertexCorners == 3) {
				objectType = "Trialgule";
			}
			else if (objVertexCorners == 4) {
				float aspRatio = boundRect[i].width / boundRect[i].height;
				std::cout << aspRatio << std::endl;
				aspRatio > 0.95 && aspRatio < 1.1 ? objectType = "Square" : objectType = "Rectangule";
			}
			else if (objVertexCorners > 4) {
				objectType = "Circle";
			}

			cv::drawContours(img_out, contourPoly, i, cv::Scalar(255, 0, 255), 2);
			cv::rectangle(img_out, boundRect[i].tl(), boundRect[i].br(), 5);
			cv::putText(img_out, objectType, { boundRect[i].x, boundRect[i].y - 5 }, cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0, 255, 0), 1);
		}
	}
}

void shapesCounterDetection() {
	std::string path = "Resources/shapes.png";
	cv::Mat img = cv::imread(path);
	cv::Mat imgGray, imgBlur, imgCanny, imgDil;

	//Preprocessing
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
	cv::Canny(imgBlur, imgCanny, 25, 75);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel);

	getCouters(imgDil, img);

	cv::imshow("Imagem", img);
	//cv::imshow("Imagem Gray", imgGray);
	//cv::imshow("Imagem Blur", imgBlur);
	//cv::imshow("Imagem Canny", imgCanny);
	//cv::imshow("Imagem Dialation", imgDil);
	cv::waitKey(0);
}