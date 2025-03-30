#include <opencv2/opencv.hpp>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    std::string folder_path = "/root/computer_vision/Lane"; // 이미지 폴더 경로

    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.path().extension() == ".jpg") {
            std::string image_path = entry.path().string();
            std::string filename = entry.path().filename().string();
            std::cout << "처리 중: " << filename << std::endl;

            // 이미지 불러오기
            cv::Mat image = cv::imread(image_path);
            if (image.empty()) {
                std::cerr << "이미지를 불러올 수 없습니다: " << filename << std::endl;
                continue;
            }

            // 1. 그레이스케일
            cv::Mat gray;
            cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

            // 2. 소벨 필터
            cv::Mat grad_x, grad_y;
            cv::Sobel(gray, grad_x, CV_32F, 1, 0, 3);
            cv::Sobel(gray, grad_y, CV_32F, 0, 1, 3);

            // 3. 에지 강도, 방향
            cv::Mat magnitude, angle;
            cv::cartToPolar(grad_x, grad_y, magnitude, angle, true);  // degree = true

            // 4. 방향 조건 (차선 방향)
            cv::Mat left_lane = (angle >= 30) & (angle <= 50);
            cv::Mat right_lane = (angle >= 125) & (angle <= 150);
            cv::Mat lane_mask = left_lane | right_lane;

            // 5. 에지 강도 조건
            cv::Mat strong_edge = (magnitude > 50);

            // 6. 최종 마스크
            cv::Mat final_mask;
            cv::bitwise_and(lane_mask, strong_edge, final_mask);

            // 7. 결과 이미지 생성
            cv::Mat result = cv::Mat::zeros(gray.size(), CV_8UC1);
            gray.copyTo(result, final_mask);

            // 8. 시각화
            cv::imshow("Original Image", image);
            cv::imshow("Detected Lane Pixels", result);

            std::cout << "아무 키나 누르면 다음 이미지로, ESC를 누르면 종료합니다." << std::endl;
            int key = cv::waitKey(0);
            if (key == 27) { // ESC 키
                break;
            }

            cv::destroyAllWindows();
        }
    }

    std::cout << "모든 이미지 처리 완료!" << std::endl;
    return 0;
}
