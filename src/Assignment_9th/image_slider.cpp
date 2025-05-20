#include <opencv2/opencv.hpp>
using namespace cv;

Mat img, hsv, mask, result;

int lowH = 85, highH = 110;     // Hue range
int lowS = 40, highS = 255;     // Saturation range
int lowV = 60, highV = 255;     // Value range

void on_trackbar(int, void*)
{
    Scalar lowerb(lowH, lowS, lowV);
    Scalar upperb(highH, highS, highV);

    inRange(hsv, lowerb, upperb, mask);
    bitwise_and(img, img, result, mask);

    imshow("Mask", mask);
    imshow("Result", result);
}

int main()
{
    img = imread("/root/computer_vision/img/9th_assignmnet/frame_Tennis_ball2_0001.png");
    if (img.empty()) {
        printf("Image load error\n");
        return -1;
    }

    cvtColor(img, hsv, COLOR_BGR2HSV);

    namedWindow("Trackbars", WINDOW_AUTOSIZE);

    // 슬라이더 생성
    createTrackbar("LowH", "Trackbars", &lowH, 180, on_trackbar);
    createTrackbar("HighH", "Trackbars", &highH, 180, on_trackbar);
    createTrackbar("LowS", "Trackbars", &lowS, 255, on_trackbar);
    createTrackbar("HighS", "Trackbars", &highS, 255, on_trackbar);
    createTrackbar("LowV", "Trackbars", &lowV, 255, on_trackbar);
    createTrackbar("HighV", "Trackbars", &highV, 255, on_trackbar);

    // 초기 결과 표시
    on_trackbar(0, 0);

    imshow("Original", img);
    waitKey(0);
    return 0;
}