#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 이진 이미지 읽기 (흑백으로)
    cv::Mat img = cv::imread("/computer_vision/img/fingerprint.bmp", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "이미지를 불러올 수 없습니다!" << std::endl;
        return -1;
    }

    // 임계값 적용 (0 또는 255인 이진화 이미지로 보장)
    cv::threshold(img, img, 128, 255, cv::THRESH_BINARY);

    // 구조 요소 (3x3 사각형 커널)
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    // 침식 연산
    cv::Mat eroded;
    cv::erode(img, eroded, kernel);

    // 팽창 연산
    cv::Mat dilated;
    cv::dilate(img, dilated, kernel);

    // 결과 출력
    cv::imshow("Original", img);
    cv::imshow("Erosion", eroded);
    cv::imshow("Dilation", dilated);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
