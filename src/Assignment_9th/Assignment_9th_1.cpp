#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat image;
	image = imread("/root/computer_vision/img/9th_assignmnet/rcube.png", IMREAD_COLOR);

	Mat bgr[3];
	split(image, bgr);  // BGR 영상을 B, G, R 성분으로 분리한다.

	imshow("src", image); 
	imshow("blue",bgr[0]); 
	imshow("green",bgr[1]); 
	imshow("red",bgr[2]); 
	waitKey(0);
	return 0;
}