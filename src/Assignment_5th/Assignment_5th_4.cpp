#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat src, src_2, dst, open, close; // open, close 사용도?
	src = imread("/computer_vision/img/Lenna.png", IMREAD_GRAYSCALE); // 흑백 사진
    src_2 = imread("/computer_vision/img/letterj.png", IMREAD_GRAYSCALE);

	imshow("src", src);
    imshow("j-origin", src_2);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5)); //MORPH_RECT이 뭐임?? - 직사각형 커널 // 사이즈가 5x5이면 정사각형 아닌가?
	morphologyEx(src, open, MORPH_GRADIENT, element); //MORPH_GRADIENT가 뭐야? - 형태학적 외곽선 검출 연산을 실시함을 언급
    morphologyEx(src_2, dst, MORPH_GRADIENT, element);
    // MORPH_OPEN : 침식 후 팽창
    // MORPH_CLOSE : 팽창 후 침식
    // MORPH_GRADIENT : 팽창 - 침식 (외곽선 추출)
    // MORPH_TOPHAT : 원본 - 열림 결과
    // MORPH_BLACKHAT : 닫힘 결과 - 원본
	imshow("Gradient Demo", open);
    imshow("j-morphology", dst);

// GPT 방식
    // 이진화 처리 (명확하게 0 또는 255로)
    // cv::threshold(src, src, 128, 255, cv::THRESH_BINARY); // 이진화 처리를 안할 경우 더 잘 나옴

    // 구조 요소 정의
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    // 침식 & 팽창
    cv::Mat dilated, eroded, gradient;
    cv::dilate(src, dilated, kernel);
    cv::erode(src, eroded, kernel);

    // 형태학적 그래디언트 계산
    cv::subtract(dilated, eroded, gradient); //morphologyex 대신 단순 차연산 진행??

    // 결과 출력
    cv::imshow("Original", src);
    cv::imshow("GPT - Morphological Gradient", gradient);

	imshow("Gradient Demo", open);
    imshow("j-morphology", dst);

	waitKey(0);
	return 0;
}

