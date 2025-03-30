#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

    Mat src= imread("/root/computer_vision/Lenna.png", 1);
	Mat dst;
    Mat median_dst;

	imshow("src", src);

	for (int i= 1; i<61; i= i+ 2) //
	{
	// GaussianBlur(src, dst, Size(i, i), 0, 0);

    GaussianBlur(src, dst, Size(i, i), 3.0, 2.5);

    // 
    //     src : 원본 영상, dst : 결과영상
    //     size : 스무딩 윈도우의 크기
    //     param1 : 커널의 시그마값(표준편차)를 지정
    //     param2 : 시그마값을 지정하고, 비대칭 모양의 커널 윈도우를 사용할때 사용
    // 

	imshow("Gaussian filter", dst);
	waitKey(1);
	}

    // medianBlur(src, median_dst, 3);
    medianBlur(src, median_dst, 11); // 커널의 크기는 홀수만 가능하다.
    imshow("median_blur", median_dst);
    waitKey(0);


    return 0;
}