#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat image, hsv, dst;
	image = imread("/root/computer_vision/img/9th_assignmnet/rcube.png", IMREAD_COLOR);
	cvtColor(image, hsv, COLOR_BGR2HSV);

	Mat array[3];
	split(hsv, array);
	imshow("src", image);
	imshow("hue", array[0]);
	imshow("saturation", array[1]);
	imshow("value", array[2]);

	waitKey(0);
	return 0;
}