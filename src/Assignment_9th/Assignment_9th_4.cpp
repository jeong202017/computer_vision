#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("/root/computer_vision/img/9th_assignmnet/00001.jpg");
    if (img.empty()) {
        cerr << "[❌] 이미지 로딩 실패: 경로를 확인하세요." << endl;
        return -1;
    }

    Mat img2 = imread("/root/computer_vision/img/9th_assignmnet/Lane_Blue.png");
    if (img2.empty()) {
        cerr << "[❌] 이미지 로딩 실패: 경로를 확인하세요." << endl;
        return -1;
    }

    Mat img3 = imread("/root/computer_vision/img/9th_assignmnet/Lane_Yellow.png");
    if (img3.empty()) {
        cerr << "[❌] 이미지 로딩 실패: 경로를 확인하세요." << endl;
        return -1;
    }

    Mat hsv;
    cvtColor(img, hsv, COLOR_BGR2HSV);

    Mat hsv2;
    cvtColor(img2, hsv2, COLOR_BGR2HSV);

    Mat hsv3;
    cvtColor(img3, hsv3, COLOR_BGR2HSV);


    // ------------------------------
    // 차선 색상 범위 설정 (Hue, Saturation, Value)
    // ------------------------------

    // 흰색 차선: 채도 낮고 밝은 값
    Mat white_mask;
    inRange(hsv, Scalar(0, 0, 100), Scalar(180, 150, 200), white_mask);

    Mat blue_mask;
    inRange(hsv2,Scalar(95, 67, 111), Scalar(112, 151, 155), blue_mask);

    Mat yellow_mask;
    inRange(hsv3, Scalar(15, 100, 100), Scalar(40, 255, 255), yellow_mask);

    // // 노란색 차선
    // Mat yellow_mask;
    // inRange(hsv, Scalar(15, 80, 80), Scalar(35, 255, 255), yellow_mask);

    // // 파란색 차선 (일부 지역)
    // Mat blue_mask;
    // inRange(hsv, Scalar(100, 100, 100), Scalar(130, 255, 255), blue_mask);

    // // 세 마스크를 하나로 합침
    // Mat lane_mask = white_mask | yellow_mask | blue_mask;

    // // 차선만 추출
    // Mat result;
    // bitwise_and(img, img, result, white_mask);

    // 결과 시각화
    imshow("Original Image_white", img);
    imshow("Lane Mask", white_mask);

    imshow("Original Image_blue", img2);
    imshow("Lane Mask_2", blue_mask);

    imshow("Original Image_yellow", img3);
    imshow("Lane Mask_3", yellow_mask);
    // imshow("Lane Detection Result", result);

    waitKey(0);
    return 0;
}