#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("/root/computer_vision/img/lena.bmp", IMREAD_GRAYSCALE);
	Mat tmp = imread("/root/computer_vision/img/lena_ref.bmp", IMREAD_GRAYSCALE);

	//결과 영상
	Mat dst = Mat(Size(src.cols - tmp.cols + 1, src.rows - tmp.rows+ 1), CV_32FC1, 1);

	matchTemplate(src, tmp, dst, TM_SQDIFF);

	double minVal;//최소값
	Point minPoint;//최소값을 가지고 있는 지점
	minMaxLoc(dst, &minVal, 0, &minPoint, 0);

	//결과를 사각형으로 그려준다.
	rectangle(src, minPoint, Point(minPoint.x + tmp.cols, minPoint.y + tmp.rows), Scalar(255));

	imshow("검색결과", src);
	imshow("템플릿", tmp);

	waitKey(0);
}