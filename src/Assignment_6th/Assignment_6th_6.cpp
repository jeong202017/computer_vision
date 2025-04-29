#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace cv;
using namespace std;

// 블록매칭 + 매칭 박스 그리기
Mat matchTemplateAndDraw(Mat frame, const Mat& template_img, int method)
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
    return frame;
}

string getFilename(int frame_num)
{
    stringstream ss;
    ss << setw(5) << setfill('0') << frame_num << ".jpg"; 
    return ss.str();
}

int main()
{
    Mat template_car = imread("/root/computer_vision/img/Template_Car_100.png", IMREAD_COLOR);
    if (template_car.empty()) {
        cerr << "❌ Template_Car_100.png 파일을 열 수 없습니다." << endl;
        return -1;
    }

    vector<int> methods = {
        TM_SQDIFF, TM_SQDIFF_NORMED,
        TM_CCORR, TM_CCORR_NORMED,
        TM_CCOEFF, TM_CCOEFF_NORMED
    };
    vector<string> method_names = {
        "SQDIFF", "SQDIFF_NORMED",
        "CCORR", "CCORR_NORMED",
        "CCOEFF", "CCOEFF_NORMED"
    };

    Size single_frame_size(320, 240); // 각 작은 화면 크기
    Size video_size(single_frame_size.width * 3, single_frame_size.height * 2); // 전체 영상 크기 (960x480)

    VideoWriter writer("tracking_result_multi6_show.avi", VideoWriter::fourcc('X', 'V', 'I', 'D'), 30, video_size);
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

        vector<Mat> results;

        for (size_t i = 0; i < methods.size(); ++i) {
            Mat frame_copy = frame.clone();
            Mat matched_frame = matchTemplateAndDraw(frame_copy, template_car, methods[i]);
            resize(matched_frame, matched_frame, single_frame_size); // 작은 사이즈로 resize

            putText(matched_frame, method_names[i], Point(10, 30),
                    FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);

            results.push_back(matched_frame);
        }

        // 2행 3열로 배치
        Mat top_row, bottom_row, final_display;
        hconcat(vector<Mat>{results[0], results[1], results[2]}, top_row);
        hconcat(vector<Mat>{results[3], results[4], results[5]}, bottom_row);
        vconcat(top_row, bottom_row, final_display);

        writer.write(final_display);
        imshow("Tracking Multi-6 Result", final_display);

        if (waitKey(1) == 27) break; // ESC 누르면 중단
    }

    destroyAllWindows();
    writer.release();

    cout << "✅ tracking_result_multi6_show.mp4 저장 완료!" << endl;
    return 0;
}
