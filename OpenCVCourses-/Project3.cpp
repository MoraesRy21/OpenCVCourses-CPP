#include "Project3.h"

// ================= Detect Faces ================

void project_3_camera() {
    cv::VideoCapture capture(0);
    cv::Mat img;

    cv::CascadeClassifier plateCascade;
    plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

    if (plateCascade.empty())
        std::cout << "XML file not loaded !\n";

    std::vector<cv::Rect> plates;

    while (true) {
        capture.read(img);

        plateCascade.detectMultiScale(img, plates, 1.05, 7);

        for (int i = 0; i < plates.size(); i++) {
            cv::Mat imgCrop = img(plates[i]);
            cv::imshow("plate " + std::to_string(i), imgCrop);
            cv::imwrite("Resources/Plates/plate_" + std::to_string(i)+".png", imgCrop);
            cv::rectangle(img, plates[i].tl(), plates[i].br(), cv::Scalar(0, 255, 0), 3);
        }

        cv::imshow("Image", img);
        cv::waitKey(1);
    }
}

void project_3_image() {
    cv::Mat img = cv::imread("Resources/Plates/unnamed.jpg");

    cv::CascadeClassifier plateCascade;
    plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

    if (plateCascade.empty())
        std::cout << "XML file not loaded !\n";

    std::vector<cv::Rect> plates;

    plateCascade.detectMultiScale(img, plates, 1.05, 7);

    for (int i = 0; i < plates.size(); i++) {
        cv::Mat imgCrop = img(plates[i]);
        cv::imshow("plate " + std::to_string(i), imgCrop);
        cv::imwrite("Resources/Plates/plate_" + std::to_string(i) + ".png", imgCrop);
        cv::rectangle(img, plates[i].tl(), plates[i].br(), cv::Scalar(0, 255, 0), 3);
    }

    cv::imshow("Image", img);
    cv::waitKey(0);
}