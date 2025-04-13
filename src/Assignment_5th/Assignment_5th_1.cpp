#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 이미지 읽기
    cv::Mat img = cv::imread("/computer_vision/img/Lenna.jpg");  // 파일명에 맞게 수정하세요
    if (img.empty()) {
        std::cerr << "이미지를 불러올 수 없습니다!" << std::endl;
        return -1;
    }

    // 수평 미러링 (y축 기준)
    cv::Mat mirror_horizontal;
    cv::flip(img, mirror_horizontal, 1);  // flipCode: 1

    // 수직 미러링 (x축 기준)
    cv::Mat mirror_vertical;
    cv::flip(img, mirror_vertical, 0);  // flipCode: 0

    // 수평 + 수직 미러링 (180도 회전과 유사)
    cv::Mat mirror_both;
    cv::flip(img, mirror_both, -1);  // flipCode: -1

    // 결과 출력
    cv::imshow("Original", img);
    cv::imshow("Horizontal Mirror", mirror_horizontal);
    cv::imshow("Vertical Mirror", mirror_vertical);
    cv::imshow("Both Axes Mirror", mirror_both);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
