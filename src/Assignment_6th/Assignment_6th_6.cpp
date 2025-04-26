#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <iomanip>  // std::setw, std::setfill
#include <sstream>  // std::stringstream

using namespace cv;
using namespace std;

// 블록매칭과 결과 그리기 함수
Point trackTemplate(Mat& frame, const Mat& template_img, int method)
{
    Mat result(frame.rows - template_img.rows + 1, frame.cols - template_img.cols + 1, CV_32FC1);

    matchTemplate(frame, template_img, result, method);

    double minVal, maxVal;
    Point minLoc, maxLoc, matchLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    if (method == TM_SQDIFF || method == TM_SQDIFF_NORMED)
        matchLoc = minLoc;
    else
        matchLoc = maxLoc;

    rectangle(frame, matchLoc, Point(matchLoc.x + template_img.cols, matchLoc.y + template_img.rows), Scalar(0, 0, 255), 2);

    return matchLoc;
}

string getFilename(int frame_num)
{
    stringstream ss;
    ss << setw(5) << setfill('0') << frame_num << ".jpg";  // 예: 00100.jpg
    return ss.str();
}

int main()
{
    // 템플릿 이미지 로딩
    Mat template_car = imread("/root/computer_vision/img/Template_Car_100.png", IMREAD_COLOR);
    if (template_car.empty()) {
        cerr << "❌ Template_Car_100.png 파일을 열 수 없습니다." << endl;
        return -1;
    }

    // 매칭 방법 선택
    int method = TM_CCOEFF_NORMED;

    // 결과 저장용
    VideoWriter writer("tracking_result_from_images.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), 30, Size(640, 480));

    for (int frame_num = 101; frame_num <= 260; ++frame_num) {
        string filepath = "/root/computer_vision/img/Lane2/" + getFilename(frame_num);
        Mat frame = imread(filepath, IMREAD_COLOR);

        if (frame.empty()) {
            cerr << "⚠️ " << filepath << " 파일을 열 수 없습니다. 스킵합니다." << endl;
            continue;
        }

        if (frame.cols < template_car.cols || frame.rows < template_car.rows) {
            cerr << "⚠️ 프레임이 템플릿보다 작습니다. 스킵합니다." << endl;
            continue;
        }

        // 템플릿 매칭 및 추적
        trackTemplate(frame, template_car, method);

        // 결과 출력
        imshow("Tracking", frame);
        writer.write(frame);

        if (waitKey(30) == 27) break; // ESC 누르면 중단
    }

    writer.release();
    destroyAllWindows();
    return 0;
}
