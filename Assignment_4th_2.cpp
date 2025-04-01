#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("/root/computer_vision/Lenna.png",IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(Size(src.cols * 2, src.rows * 2), src.type());

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			const int newX = x * 2;
			const int newY = y * 2;
			dst.at<uchar>(newY, newX) = src.at<uchar>(y, x);
		}
	}
	imshow("Image", src);
	imshow("Scaled", dst);
	waitKey(0);
	return 1;
}