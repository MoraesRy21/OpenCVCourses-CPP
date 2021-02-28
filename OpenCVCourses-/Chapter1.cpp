#include "Chapter1.h"

void showImage() {
    std::string path = "Resources/test.png";
    cv::Mat img = cv::imread(path);
    cv::imshow("Image", img);
    cv::waitKey(0);
}

void showVideo() {
    std::string path = "Resources/test_video.mp4";
    cv::VideoCapture capture(path);
    cv::Mat img;

    while (true) {
        capture.read(img);
        cv::imshow("Video", img);
        cv::waitKey(33);
    }
}

void cameraCapture() {
    cv::VideoCapture capture(0);
    cv::Mat img;

    while (true) {
        capture.read(img);
        cv::imshow("Image", img);
        cv::waitKey(1);
    }
}