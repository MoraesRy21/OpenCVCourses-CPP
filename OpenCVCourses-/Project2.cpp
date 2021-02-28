#include "Project2.h"

cv::Mat imgOriginal, imgGray, imgBlur, imgCanny, imgThreshold, imgDil, imgErode, imgWarp, imgCrop;
std::vector<cv::Point> initialPoints, docPoints;

float width = 420, heigh = 596;

void project_2_image() {
	imgOriginal = cv::imread("Resources/paper.jpg");
	cv::resize(imgOriginal, imgOriginal, cv::Size(), 0.5, 0.5);

	//1ª Preprocessing
	imgThreshold = preProssecing(imgOriginal);

	//2º Get the contours - Biggest
	initialPoints = getContours(imgThreshold);
	//drawPoints(initialPoints, cv::Scalar(0,0,255));
	docPoints = reorder(initialPoints);
	drawPoints(docPoints, cv::Scalar(0,255,0));

	//3º Warp
	imgWarp = getWarp(imgOriginal, docPoints, width, heigh);

	//Crop
	int cropValue = 5;
	cv::Rect roi(cropValue, cropValue, width - (2 * cropValue), heigh - (2 * cropValue));
	imgCrop = imgWarp(roi);

	cv::resize(imgOriginal, imgOriginal, cv::Size(), 0.6, 0.6);
	cv::imshow("Image", imgOriginal);
	cv::imshow("Image Dilation", imgThreshold);
	cv::imshow("Image Canny", imgCanny);
	cv::imshow("Image Warp", imgWarp);
	cv::imshow("Image Crop", imgCrop);
	cv::waitKey(0);
}

void project_2_camera() {
	cv::Mat img;
	cv::VideoCapture videoCapture(0);
	while (true) {
		videoCapture.read(img);

		imgOriginal = img;
		//cv::resize(imgOriginal, imgOriginal, cv::Size(), 0.5, 0.5);

		//1ª Preprocessing
		imgThreshold = preProssecing(imgOriginal);

		//2º Get the contours - Biggest
		initialPoints = getContours(imgThreshold);
		//drawPoints(initialPoints, cv::Scalar(0,0,255));
		docPoints = reorder(initialPoints);
		//drawPoints(docPoints, cv::Scalar(0,255,0));

		//3º Warp
		imgWarp = getWarp(imgOriginal, docPoints, width, heigh);

		//Crop
		int cropValue = 5;
		cv::Rect roi(cropValue, cropValue, width - (2 * cropValue), heigh - (2 * cropValue));
		imgCrop = imgWarp(roi);

		cv::imshow("Image", imgOriginal);
		//cv::imshow("Image Dilation", imgThreshold);
		//cv::imshow("Image Warp", imgWarp);
		cv::imshow("Image Crop", imgCrop);

		cv::waitKey(1);
	}
}

cv::Mat preProssecing(cv::Mat& img) {
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(img, imgBlur, cv::Size(3, 3), 3, 0);
	cv::Canny(imgBlur, imgCanny, 25, 75);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
	cv::dilate(imgCanny, imgDil, kernel);
	//cv::erode(imgDil, imgErode, kernel);
	return imgDil;
}

std::vector<cv::Point> getContours(cv::Mat& imgDil) {

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//cv::drawContours(img_out, contours, -1, cv::Scalar(255, 0, 255), 2); // Draw contours of the shapes

	std::vector<std::vector<cv::Point>> contourPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	std::vector<cv::Point> biggest;
	int maxArea = 0;

	for (int i = 0; i < contours.size(); i++) {
		int area = cv::contourArea(contours[i]);
		std::cout << "Area: " << area << std::endl;

		if (area > 1000) { // remove noise

			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);

			if (area > maxArea && contourPoly[i].size() == 4) {
				//cv::drawContours(imgOriginal, contourPoly, i, cv::Scalar(255, 0, 255), 2);
				//cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 2);
				biggest = { contourPoly[i][0], contourPoly[i][1], contourPoly[i][2], contourPoly[i][3] };
				maxArea = area;
			}

		}
	}
	return biggest;
}

void drawPoints(std::vector<cv::Point> points, cv::Scalar color) {
	for (int i = 0; i < points.size(); i++) {
		cv::circle(imgOriginal, points[i], 5, color, cv::FILLED);
		cv::putText(imgOriginal, std::to_string(i), points[i], cv::FONT_HERSHEY_PLAIN, 2, color, 2);

	}
}

std::vector<cv::Point> reorder(std::vector<cv::Point> points) {
	std::vector<cv::Point> newPoints;
	std::vector<int> sumPoints, subPoints;
	for (int i = 0; i < points.size(); i++) {
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}
	newPoints.push_back(points[std::min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
	newPoints.push_back(points[std::max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[std::min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[std::max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
	return newPoints;
}

cv::Mat getWarp(cv::Mat img, std::vector<cv::Point> docPoints, float width, float heigh) {
	cv::Point2f src[4] = { docPoints[0], docPoints[1], docPoints[2], docPoints[3] };
	cv::Point2f dest[4] = { {0.0f, 0.0f}, {width, 0.0f}, {0.0f, heigh}, {width, heigh} };

	cv::Mat matrix = cv::getPerspectiveTransform(src, dest);
	cv::warpPerspective(img, imgWarp, matrix, cv::Point(width, heigh));

	return imgWarp;
}