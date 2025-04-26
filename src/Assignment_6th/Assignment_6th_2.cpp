#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("/root/computer_vision/img/rice.bmp", IMREAD_GRAYSCALE);
	Mat img, bin1, bin2, bin3;

	Mat src2 = imread("/root/computer_vision/img/book2.png", IMREAD_GRAYSCALE);
	Mat img2, bin4, bin5, bin6;

	if (src.empty()) {
		cerr << "❌ Error: src (rice.bmp) not loaded!" << endl;
		return -1;
	}
	if (src2.empty()) {
		cerr << "❌ Error: src2 (book2.png) not loaded!" << endl;
		return -1;
	}

	medianBlur(src, img, 5);

	threshold(img, bin1, 127, 255, THRESH_BINARY);
	adaptiveThreshold(img, bin2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2);
	adaptiveThreshold(img, bin3, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);

	medianBlur(src2, img2, 5);
	threshold(img2, bin4, 127, 255, THRESH_BINARY);
	adaptiveThreshold(img2, bin5, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2);
	adaptiveThreshold(img2, bin6, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);

	// block size 변경 - 7, 15, 30 (왜 7,5,30인가?)

    // Input arr : , Output arr :, maxValue :, adaptivemethod : threshold algorithm, thresholdType : 이진화 결과값
	// blockSize : 블록 크기, C 보정 상수 : (양수) - 보정 상수 빼기,(음수) - 보정 상수 더하기
	// 질문 사항 : 보정 상수가 양수일 때 빼는 이유

	imshow("rice-Original", src);
	imshow("rice-Global Thresholding", bin1);
	imshow("rice-Adaptive Mean", bin2);
	imshow("rice-Adaptive Gaussian", bin3);
	imshow("book-Original", src2);
	imshow("book-Global Thresholding", bin4);
	imshow("book-Adaptive Mean", bin5);
	imshow("book-Adaptive Gaussian", bin6);
	waitKey();

	return 0;
}