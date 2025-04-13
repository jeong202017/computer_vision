#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 그레이스케일 영상 로드
    cv::Mat src = cv::imread("gray_image.jpg", cv::IMREAD_GRAYSCALE);
    if (src.empty()) {
        std::cerr << "이미지를 불러올 수 없습니다." << std::endl;
        return -1;
    }

    // 3x3 사각형 커널 생성
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    // 팽창과 침식 결과 저장용 변수
    cv::Mat dilated, eroded;

    // 팽창 (Dilation): 커널 영역 내 최대값
    cv::dilate(src, dilated, kernel);

    // 침식 (Erosion): 커널 영역 내 최소값
    cv::erode(src, eroded, kernel);

    // 결과 출력
    cv::imshow("원본 영상", src);
    cv::imshow("팽창 영상", dilated);
    cv::imshow("침식 영상", eroded);

    cv::waitKey(0);
    return 0;
}
