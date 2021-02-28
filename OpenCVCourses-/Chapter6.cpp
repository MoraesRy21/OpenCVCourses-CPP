#include "Chapter6.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// ================= Color Detection ================

void colorDetection() {
    int _H_min = 0, _S_min = 110, _V_min = 153;
    int _H_max = 19, _S_max = 240, _V_max = 255;

    std::string path = "Resources/lambo.png";
    cv::Mat img = cv::imread(path);
    cv::Mat imgHSV, mask;

    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    cv::Scalar lower(_H_min, _S_min, _V_min);
    cv::Scalar upper(_H_max, _S_max, _V_max);
    cv::inRange(imgHSV, lower, upper, mask);

    cv::imshow("Image", img);
    cv::imshow("Image HSV", imgHSV);
    cv::imshow("Image Mask", mask);
    cv::waitKey(0);
}

void colorDetectionTrackBar() {
    int _H_min = 0, _S_min = 110, _V_min = 153;
    int _H_max = 19, _S_max = 240, _V_max = 255;

    int imageChoice = 2;
    std::string path;

    switch (imageChoice) {
        case 1 :
            path = "Resources/lambo.png";
            break;
        case 2:
            path = "Resources/shapes.png";
            break;
    }

    cv::Mat img = cv::imread(path);
    cv::Mat imgHSV, mask;

    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    cv::namedWindow("Trackbars", (640, 200));
    cv::createTrackbar("Hue Min", "Trackbars", &_H_min, 179);
    cv::createTrackbar("Hue Max", "Trackbars", &_H_max, 179);
    cv::createTrackbar("Sat Min", "Trackbars", &_S_min, 255);
    cv::createTrackbar("Sat Max", "Trackbars", &_S_max, 255);
    cv::createTrackbar("Val Min", "Trackbars", &_V_min, 255);
    cv::createTrackbar("Val Max", "Trackbars", &_V_max, 255);

    while (true) {

        cv::Scalar lower(_H_min, _S_min, _V_min);
        cv::Scalar upper(_H_max, _S_max, _V_max);
        cv::inRange(imgHSV, lower, upper, mask);

        cv::imshow("Image", img);
        cv::imshow("Image HSV", imgHSV);
        cv::imshow("Image Mask", mask);
        cv::waitKey(1);
    }
}

void colorDetectionTrackBarInCamera() {
    int _H_min = 0, _S_min = 0, _V_min = 0;
    int _H_max = 179, _S_max = 255, _V_max = 255;

    cv::VideoCapture capture(0);
    cv::Mat img;
    cv::Mat imgHSV, mask;

    capture.read(img);

    cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

    cv::namedWindow("Trackbars", (640, 200));
    cv::createTrackbar("Hue Min", "Trackbars", &_H_min, 179);
    cv::createTrackbar("Hue Max", "Trackbars", &_H_max, 179);
    cv::createTrackbar("Sat Min", "Trackbars", &_S_min, 255);
    cv::createTrackbar("Sat Max", "Trackbars", &_S_max, 255);
    cv::createTrackbar("Val Min", "Trackbars", &_V_min, 255);
    cv::createTrackbar("Val Max", "Trackbars", &_V_max, 255);

    while (true) {
        capture.read(img);

        cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

        cv::Scalar lower(_H_min, _S_min, _V_min);
        cv::Scalar upper(_H_max, _S_max, _V_max);
        cv::inRange(imgHSV, lower, upper, mask);

        std::cout << _H_min << ", " << _S_min << ", " << _V_min << ", " << _H_max << ", " << _S_max << ", " << _V_max << std::endl;

        cv::imshow("Image", img);
        //cv::imshow("Image HSV", imgHSV);
        cv::imshow("Image Mask", mask);
        cv::waitKey(1);
    }
}