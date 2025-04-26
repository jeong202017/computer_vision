#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("/root/computer_vision/img/book1.jpg", IMREAD_GRAYSCALE);
	Mat img, bin1, bin2, bin3;
	Mat bin4, bin5;
	Mat bin6, bin7;

	medianBlur(src, img, 5);

	threshold(img, bin1, 127, 255, THRESH_BINARY);
	adaptiveThreshold(img, bin2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 2);
	adaptiveThreshold(img, bin3, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, 2);

	adaptiveThreshold(img, bin4, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 2);
	adaptiveThreshold(img, bin5, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 2);

	adaptiveThreshold(img, bin6, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 21, 2);
	adaptiveThreshold(img, bin7, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 21, 2);

    // Input arr : , Output arr :, maxValue :, adaptivemethod : threshold algorithm, thresholdType : 이진화 결과값
	// blockSize : 블록 크기(홀수여야 함 - 이유가 뭐였더라), C 보정 상수 : (양수) - 보정 상수 빼기,(음수) - 보정 상수 더하기
	// 질문 사항 : 보정 상수가 양수일 때 빼는 이유
	// 30이 
    
	imshow("7-Original", src);
	imshow("7-Global Thresholding", bin1);
	imshow("7-Adaptive Mean", bin2);
	imshow("7-Adaptive Gaussian", bin3);
	imshow("15-Adaptive Mean", bin4);
	imshow("15-Adaptive Gaussian", bin5);
	imshow("21-Adaptive Mean",bin6);
	imshow("21-Adaptive Gasussian",bin7);
	waitKey();

	return 0;
}