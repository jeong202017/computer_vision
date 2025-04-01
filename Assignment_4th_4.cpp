#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src= imread("/root/computer_vision/Lenna.png", IMREAD_COLOR);
	Mat dst= Mat();

        // Nearest-Neighbor = 0, Linear = 1, High-Order = 2
	resize(src, dst, Size(0,0), 4.0, 4.0, 0);

	imshow("Image", src);
	imshow("Scaled", dst);
        imwrite("/root/computer_vision/lenna_scaled0.bmp", dst); //확대된 영상을 저장해서 확인
	waitKey(0);
	return 1;
}