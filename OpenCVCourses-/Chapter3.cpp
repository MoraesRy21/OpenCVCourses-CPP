#include "Chapter3.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// ================= Image Manipulation ================

void imageManipulation() {
	std::string path = "Resources/test.png";
	cv::Mat img = cv::imread(path);
	cv::Mat imgResize, imgResize2, imgCrop;

	std::cout << img.size();
	cv::resize(img, imgResize, cv::Size(640, 480));
	cv::resize(img, imgResize2, cv::Size(), 0.5, 0.5);

	cv::Rect roi(100, 100, 300, 250);
	imgCrop = img(roi);

	cv::imshow("Imagem", img);
	cv::imshow("Imagem Resize", imgResize);
	cv::imshow("Imagem Resize 2", imgResize2);
	cv::imshow("Imagem Crop", imgCrop);
	cv::waitKey(0);
}