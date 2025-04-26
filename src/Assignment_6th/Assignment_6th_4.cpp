#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat src = imread("/root/computer_vision/img/lena.bmp", IMREAD_GRAYSCALE);
    Mat tmp = imread("/root/computer_vision/img/lena_ref.bmp", IMREAD_GRAYSCALE);

    if (src.empty() || tmp.empty()) {
        cerr << "이미지를 불러오지 못했습니다." << endl;
        return -1;
    }

    // 결과 저장용
    vector<int> match_methods = {
        TM_SQDIFF, TM_SQDIFF_NORMED,
        TM_CCORR, TM_CCORR_NORMED,
        TM_CCOEFF, TM_CCOEFF_NORMED
    };

    vector<string> method_names = {
        "TM_SQDIFF", "TM_SQDIFF_NORMED",
        "TM_CCORR", "TM_CCORR_NORMED",
        "TM_CCOEFF", "TM_CCOEFF_NORMED"
    };

    for (size_t i = 0; i < match_methods.size(); ++i) {
        int method = match_methods[i];
        string name = method_names[i];

        Mat result(src.rows - tmp.rows + 1, src.cols - tmp.cols + 1, CV_32FC1);
        matchTemplate(src, tmp, result, method);

        double minVal, maxVal;
        Point minLoc, maxLoc, matchLoc;

        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

        // 매칭 위치 결정 방식: TM_SQDIFF 계열은 최소값, 나머지는 최대값
        if (method == TM_SQDIFF || method == TM_SQDIFF_NORMED)
            matchLoc = minLoc;
        else
            matchLoc = maxLoc;

        // 원본 이미지 복사 후 사각형 표시
        Mat display;
        cvtColor(src, display, COLOR_GRAY2BGR); // 회색이면 흰 사각형 안보일 수 있으므로 컬러로 변경
        rectangle(display, matchLoc, Point(matchLoc.x + tmp.cols, matchLoc.y + tmp.rows), Scalar(0, 0, 255), 2);

        imshow(name + " 결과", display);
    }

    imshow("템플릿", tmp);
    waitKey(0);
    return 0;
}