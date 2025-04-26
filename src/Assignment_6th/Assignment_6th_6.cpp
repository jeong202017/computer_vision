#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace cv;
using namespace std;

// 블록매칭과 결과 그리기 함수
Mat trackTemplate(const Mat& frame, const Mat& template_img, int method)
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

    Mat display;
    cvtColor(frame, display, COLOR_BGR2RGB); // 보기 좋게 색 변경
    rectangle(display, matchLoc, Point(matchLoc.x + template_img.cols, matchLoc.y + template_img.rows), Scalar(255, 0, 0), 2);

    return display;
}

string getFilename(int frame_num)
{
    stringstream ss;
    ss << setw(5) << setfill('0') << frame_num << ".jpg";
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

    // 매칭 방법 리스트
    vector<int> methods = { TM_SQDIFF, TM_SQDIFF_NORMED, TM_CCORR, TM_CCORR_NORMED, TM_CCOEFF, TM_CCOEFF_NORMED };
    vector<string> method_names = { "SQDIFF", "SQDIFF_NORMED", "CCORR", "CCORR_NORMED", "CCOEFF", "CCOEFF_NORMED" };

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

        // 모든 매칭 방법 결과를 저장할 벡터
        vector<Mat> results;

        for (size_t i = 0; i < methods.size(); ++i) {
            Mat result_img = trackTemplate(frame, template_car, methods[i]);
            putText(result_img, method_names[i], Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 255, 0), 2); // 방법 이름 표시
            results.push_back(result_img);
        }

        // 결과를 가로로 붙이기 (3개씩)
        Mat top, bottom, final_display;
        hconcat(vector<Mat>{results[0], results[1], results[2]}, top);
        hconcat(vector<Mat>{results[3], results[4], results[5]}, bottom);
        vconcat(top, bottom, final_display);

        // 결과 보여주기
        imshow("Tracking Comparison", final_display);

        if (waitKey(30) == 27) break; // ESC 누르면 종료
    }

    destroyAllWindows();
    return 0;
}
