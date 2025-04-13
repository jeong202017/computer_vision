#include <opencv2/opencv.hpp>
#include <iostream>

#include <filesystem>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;


int main() {

    Mat src= imread("/root/computer_vision/Lenna.png", 1);

    Mat circuit = imread("/root/computer_vision/circuit.bmp", CV_8UC1); // utsu 를 위한 흑백 영상 처리

    Mat rice = imread("/root/computer_vision/rice.bmp", CV_8UC1); // 

	Mat dst;
    Mat median_dst;
	imshow("src", src);

	Mat sobel16 = Mat::zeros(src.size(), CV_8U); // 
	Mat sobel8 = Mat::zeros(src.size(), CV_8U); //
	Mat canny = Mat::zeros(src.size(), CV_8U); //

  	Sobel(src, sobel16, CV_16S, 1, 1); //X, Y축에 대해 1차 미분을 수행한다. - 부호있는 16비트 이미지
    convertScaleAbs(sobel16, sobel8, 1, 0); //16비트 영상을 8비트 영상으로 바꾼다.
  
	imshow("sobel8", sobel8); //"sobel8"영상을 화면에 출력
	waitKey(0);	//키 입력을 기다린다.



    // =====================================================================================

    // 3-2

    Mat cir_dst;
    Mat rice_dst;

    // circuit 소벨 (엣지 추출)
    Sobel(circuit, sobel16, CV_16S, 1, 1);
    convertScaleAbs(sobel16, sobel8, 1, 0);

    imshow("circuit", circuit);
    imshow("sobel8", sobel8);
    waitKey(0);

    // otsu(이진화)
    threshold(circuit, cir_dst, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    imshow("circuit_binary", cir_dst);



    // rice 소벨
    Sobel(rice, sobel16, CV_16S, 1, 1); //
    convertScaleAbs(sobel16, sobel8, 1, 0);

    imshow("rice", rice);
    imshow("sobel8", sobel8);
    waitKey(0);

    threshold(rice, rice_dst, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    
    imshow("rice_binary", rice_dst);
    waitKey(0);

    return 0;
    }