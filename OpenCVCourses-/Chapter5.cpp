#include "Chapter5.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// ================= Image Warp ================

void imageWarp() {
	std::string path = "Resources/cards.jpg";
	cv::Mat img = cv::imread(path);
	cv::Mat matrix, imgWarp;
	float width = 290, heigh = 390;

	cv::Point2f src[4] = { {529, 142}, {771, 190}, {405, 395}, {674, 457} };
	cv::Point2f dest[4] = { {0.0f, 0.0f}, {width, 0.0f}, {0.0f, heigh}, {width, heigh} };

	matrix = cv::getPerspectiveTransform(src, dest);
	cv::warpPerspective(img, imgWarp, matrix, cv::Point(width, heigh));

	int size = sizeof(src) / sizeof(*src);
	for (int i = 0; i < size; i++)
		cv::circle(img, src[i], 10, cv::Scalar(0, 0, 255), cv::FILLED);

	cv::imshow("Imagem", img);
	cv::imshow("Imagem Warp", imgWarp);
	cv::waitKey(0);
}