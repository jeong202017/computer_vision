#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    std::string video_path = "/root/computer_vision/img/9th_assignmnet/Tennis_ball2.mp4";
    VideoCapture cap(video_path);

    if (!cap.isOpened()) {
        cerr << "❌ 비디오 파일을 열 수 없습니다: " << video_path << endl;
        return -1;
    }

    Mat frame, hsv_frame, mask;
    int frame_count = 0;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // BGR → HSV 변환
        cvtColor(frame, hsv_frame, COLOR_BGR2HSV);

        // HSV 기준 초록색 범위 이진화
        // 예시 범위: Hue 50~70, Saturation 100~255, Value 100~255
        inRange(hsv_frame, Scalar(8, 67, 53), Scalar(32, 145, 137), mask);
         // 8 67 53 / 32 145 137
        // 결과 출력
        imshow("원본 프레임", frame);
        imshow("HSV 변환", hsv_frame);
        imshow("이진화 마스크", mask);

        char key = waitKey(30);
        if (key == 27) break; // ESC 누르면 종료

        frame_count++;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}