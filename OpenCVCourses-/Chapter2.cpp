#include "Chapter2.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// ================= Basics Functions for image pre-processing ================

void imgFilters() {
	std::string path = "Resources/test.png";
	cv::Mat img = cv::imread(path);
	cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(img, imgBlur, cv::Size(3,3), 3, 0);
	cv::Canny(imgBlur, imgCanny, 25, 75);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2,2));
	cv::dilate(imgCanny, imgDil, kernel);
	cv::erode(imgDil, imgErode, kernel);

	cv::imshow("Imagem", img);
	cv::imshow("Imagem Gray", imgGray);
	cv::imshow("Imagem Blur", imgBlur);
	cv::imshow("Imagem Canny", imgCanny);
	cv::imshow("Imagem Dialation", imgDil);
	cv::imshow("Imagem Erode", imgErode);
	cv::waitKey(0);
}