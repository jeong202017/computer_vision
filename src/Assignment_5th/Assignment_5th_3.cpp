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

    // 침식 후 팽창

    // 침식 연산
    cv::Mat eroded_1;
    cv::erode(img, eroded_1, kernel);

    // 팽창 연산
    cv::Mat dilated_1;
    cv::dilate(eroded_1, dilated_1, kernel);

    cv::imshow("침식 후 팽창 - Original", img);
    cv::imshow("침식 후 팽창 - 침식", eroded_1);
    cv::imshow("침식 후 팽창 - 팽창", dilated_1);


    // 팽창 후 침식

    // 팽창 연산
    cv::Mat dilated_2;
    cv::dilate(img, dilated_2, kernel);

    // 침식 연산
    cv::Mat eroded_2;
    cv::erode(dilated_2, eroded_2, kernel);

    // 결과 출력
    cv::imshow("팽창 후 침식 - Original", img);
    cv::imshow("팽창 후 침식 - 팽창", dilated_2);
    cv::imshow("팽창 후 침식 - 침식", eroded_2);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
