#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <vector>

void project_2_image();
void project_2_camera();
cv::Mat preProssecing(cv::Mat& img);
std::vector<cv::Point> getContours(cv::Mat& imgDil);
void drawPoints(std::vector<cv::Point> points, cv::Scalar color);
std::vector<cv::Point> reorder(std::vector<cv::Point> points);
cv::Mat getWarp(cv::Mat img, std::vector<cv::Point> docPoints, float width, float heigh);