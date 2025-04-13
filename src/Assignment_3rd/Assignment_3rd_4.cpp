#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 1. 영상 열기
    cv::VideoCapture cap("/root/computer_vision/Cat.mp4");
    if (!cap.isOpened()) {
        std::cerr << "영상을 열 수 없습니다." << std::endl;
        return -1;
    }

    int target_frame_index = 50; // 저장하고 싶은 프레임 번호 (0부터 시작)

    // 2. 프레임 수 확인
    int total_frames = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
    std::cout << "총 프레임 수: " << total_frames << std::endl;

    if (target_frame_index >= total_frames) {
        std::cerr << "지정한 프레임 번호가 영상 길이를 초과합니다." << std::endl;
        return -1;
    }

    // 3. 해당 프레임으로 이동
    cap.set(cv::CAP_PROP_POS_FRAMES, target_frame_index);

    cv::Mat frame, red_frame;
    cap >> frame;
    if (frame.empty()) {
        std::cerr << "프레임을 불러올 수 없습니다." << std::endl;
        return -1;
    }

    // 4. 빨간색 추가
    red_frame = frame.clone();
    std::vector<cv::Mat> channels;
    cv::split(red_frame, channels);
    channels[2] = cv::min(channels[2] + 100, 255);  // R 채널 증가
    cv::merge(channels, red_frame);

    // 5. 이미지로 저장
    if (!cv::imwrite("RedFrame50.jpg", red_frame)) {
        std::cerr << "프레임 저장 실패!" << std::endl;
        return -1;
    }

    // 6. 시각화 (선택)
    cv::imshow("Red Frame 50", red_frame);
    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "50번째 프레임을 저장했습니다: RedFrame50.jpg" << std::endl;
    return 0;
}
