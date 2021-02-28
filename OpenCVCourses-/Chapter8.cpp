#include "Chapter8.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

// ================= Detect Faces ================

void detectFaces() {
    std::string path = "Resources/test.png";
    cv::Mat img = cv::imread(path);

    cv::CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");

    if (faceCascade.empty())
        std::cout << "XML file not loaded !\n";

    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);

    for(int i=0; i < faces.size(); i++)
        cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(0, 255, 0), 3);

    cv::imshow("Image", img);
    cv::waitKey(0);
}

void detectFacesVideo() {
    cv::VideoCapture capture(0);
    cv::Mat img;

    cv::CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");

    if (faceCascade.empty())
        std::cout << "XML file not loaded !\n";


    while (true) {
        capture.read(img);

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(img, faces, 1.05, 7);

        for (int i = 0; i < faces.size(); i++)
            cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(0, 255, 0), 3);

        cv::imshow("Image", img);
        cv::waitKey(1);
    }
}