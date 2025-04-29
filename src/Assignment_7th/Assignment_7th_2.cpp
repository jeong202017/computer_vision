#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>  // C++17 이상 필요

namespace fs = std::filesystem;
using namespace cv;
using namespace std;

vector<int> blockSizes = {2, 3, 5};
vector<int> kSizes = {3, 5, 7};
vector<double> kValues = {0.04, 0.06, 0.08};

// Harris 코너 검출 함수
void detectAndSave(const string& imagePath, const string& outputDir) {
    Mat src = imread(imagePath);
    if (src.empty()) {
        cerr << "이미지 로드 실패: " << imagePath << endl;
        return;
    }

    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    gray.convertTo(gray, CV_32FC1);  // float으로 변환

    string baseName = fs::path(imagePath).stem().string();

    for (int blockSize : blockSizes) {
        for (int ksize : kSizes) {
            for (double k : kValues) {
                Mat dst;
                cornerHarris(gray, dst, blockSize, ksize, k);

                // 정규화
                Mat dst_norm, dst_norm_u8;
                normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1);
                convertScaleAbs(dst_norm, dst_norm_u8);  // 시각화용

                // 시각화용 결과 이미지: 원본 위에 코너점 표시
                Mat result = src.clone();
                double maxVal;
                minMaxLoc(dst, nullptr, &maxVal);
                for (int y = 0; y < dst.rows; y++) {
                    for (int x = 0; x < dst.cols; x++) {
                        if (dst.at<float>(y, x) > 0.01 * maxVal) {
                            circle(result, Point(x, y), 2, Scalar(0, 0, 255), FILLED);
                        }
                    }
                }

                // 결과 저장
                char result_name[300], norm_name[300];
                snprintf(result_name, sizeof(result_name), "%s/%s_bs%d_ks%d_k%.2f.png",
                         outputDir.c_str(), baseName.c_str(), blockSize, ksize, k);
                snprintf(norm_name, sizeof(norm_name), "%s/%s_bs%d_ks%d_k%.2f_norm.png",
                         outputDir.c_str(), baseName.c_str(), blockSize, ksize, k);

                imwrite(result_name, result);
                imwrite(norm_name, dst_norm_u8);

                cout << "[+] Saved: " << result_name << " (with corners)" << endl;
                cout << "[+] Saved: " << norm_name << " (normalized)" << endl;
            }
        }
    }
}

int main() {
    vector<string> imagePaths = {
        "/root/computer_vision/img/lena.bmp",
        "/root/computer_vision/img/fiigure.bmp",
        "/root/computer_vision/img/chessboard.png"
    };

    string outputDir = "/root/computer_vision/output_harris";
    fs::create_directories(outputDir);  // 결과 저장 폴더 생성

    for (const auto& path : imagePaths) {
        detectAndSave(path, outputDir);
    }

    return 0;
}
