#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>

using namespace cv;


int main() {
    Mat img = imread("/root/computer_vision/Lenna.png", cv::IMREAD_COLOR);
    imshow("img",img);
    waitKey(0);


    return 0;
}
