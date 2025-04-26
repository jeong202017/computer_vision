#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>  // for CSV file output
#include <string>
#include <iomanip>  // for std::setw
#include <sstream>  // for std::stringstream
#include <vector>

using namespace cv;
using namespace std;

// 블록매칭과 결과 그리기 함수
pair<Mat, double> trackTemplate(const Mat& frame, const Mat& template_img, int method)
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

    // 결과 프레임 만들기
    Mat display = frame.clone();  
    rectangle(display, matchLoc, Point(matchLoc.x + template_img.cols, matchLoc.y + template_img.rows), Scalar(0, 0, 255), 2);

    // (표시용 프레임, 매칭 점수) 반환
    if (method == TM_SQDIFF || method == TM_SQDIFF_NORMED)
        return { display, minVal };
    else
        return { display, maxVal };
}

string getFilename(int frame_num)
{
    stringstream ss;
    ss << setw(5) << setfill('0') << frame_num << ".jpg"; // 00100.jpg 형식
    return ss.str();
}

int main()
{
    Mat template_car = imread("/root/computer_vision/img/Template_Car_100.png", IMREAD_COLOR);
    if (template_car.empty()) {
        cerr << "❌ Template_Car_100.png 파일을 열 수 없습니다." << endl;
        return -1;
    }

    int method = TM_CCOEFF_NORMED;  // 사용할 블록매칭 기준
    vector<double> match_scores;    // 매칭 점수 기록용

    // 결과 영상 저장 설정
    Size videoSize(640, 480);  // 프레임 크기 (네 상황에 맞춰 조정)
    VideoWriter writer("tracking_result.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), 30, videoSize);

    if (!writer.isOpened()) {
        cerr << "❌ 비디오 파일을 열 수 없습니다." << endl;
        return -1;
    }

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

        // 매칭 결과 프레임 생성
        auto [result_frame, score] = trackTemplate(frame, template_car, method);

        match_scores.push_back(score);

        // 결과 프레임에 스코어 텍스트 추가
        stringstream ss;
        ss << fixed << setprecision(4) << "Score: " << score;
        putText(result_frame, ss.str(), Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 255, 0), 2);

        // 결과 프레임을 동영상으로 저장
        Mat resized_frame;
        resize(result_frame, resized_frame, videoSize);  // 크기 맞추기
        writer.write(resized_frame);

        // (화면에도 잠깐 보여줄 수 있음)
        imshow("Tracking", resized_frame);
        if (waitKey(1) == 27) break; // ESC 누르면 중단
    }

    destroyAllWindows();
    writer.release();

    // 매칭 점수 CSV로 저장
    ofstream file("match_scores.csv");
    file << "Frame,Score\n";
    for (size_t i = 0; i < match_scores.size(); ++i) {
        file << (101 + i) << "," << match_scores[i] << "\n";
    }
    file.close();

    cout << "✅ tracking_result.mp4 저장 완료!" << endl;
    cout << "✅ match_scores.csv 저장 완료!" << endl;

    return 0;
}
