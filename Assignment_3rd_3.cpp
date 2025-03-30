#include <opencv2/opencv.hpp>
#include <filesystem>
#include <iostream>

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

int main() {
    string folder_path = "/root/computer_vision/Lane"; // 이미지 폴더 경로
    string output_path = "/root/computer_vision/Lane/output"; // 결과 저장 폴더

    // 결과 폴더가 없으면 생성
    fs::create_directory(output_path);

    

    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (entry.path().extension() == ".jpg") {
            string image_path = entry.path().string();
            string filename = entry.path().filename().string();
            cout << "처리 중: " << filename << std::endl;

            // 이미지 불러오기
            Mat image = imread(image_path);
            if (image.empty()) {
                cerr << "이미지를 불러올 수 없습니다: " << filename << endl;
                continue;
            }

            // 1. 그레이스케일
            Mat gray;
            cvtColor(image, gray, COLOR_BGR2GRAY);

            // 2. 소벨 필터
            Mat grad_x, grad_y;
            Sobel(gray, grad_x, CV_32F, 1, 0, 3);
            Sobel(gray, grad_y, CV_32F, 0, 1, 3);

            // 3. 에지 강도, 방향
            Mat magnitude, angle;
            cartToPolar(grad_x, grad_y, magnitude, angle, true);  // degree = true

            // 4. 방향 조건 (차선 방향)
            Mat left_lane = (angle >= 30) & (angle <= 50);
            Mat right_lane = (angle >= 125) & (angle <= 150);
            Mat lane_mask = left_lane | right_lane;

            // 5. 에지 강도 조건
            Mat strong_edge = (magnitude > 50);

            // 6. 최종 마스크
            Mat final_mask;
            bitwise_and(lane_mask, strong_edge, final_mask);

            // 7. 결과 이미지 생성
            Mat result = Mat::zeros(gray.size(), CV_8UC1);
            gray.copyTo(result, final_mask);



        }
    }


    return 0;
}
