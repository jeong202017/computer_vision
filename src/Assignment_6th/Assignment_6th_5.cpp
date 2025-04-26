#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void runTemplateMatching(const Mat& src, const Mat& tmp, const string& prefix) {
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
        Mat result(src.rows - tmp.rows + 1, src.cols - tmp.cols + 1, CV_32FC1);
        matchTemplate(src, tmp, result, match_methods[i]);

        double minVal, maxVal;
        Point minLoc, maxLoc, matchLoc;
        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

        if (match_methods[i] == TM_SQDIFF || match_methods[i] == TM_SQDIFF_NORMED)
            matchLoc = minLoc;
        else
            matchLoc = maxLoc;

        Mat display;
        cvtColor(src, display, COLOR_GRAY2BGR);
        rectangle(display, matchLoc, Point(matchLoc.x + tmp.cols, matchLoc.y + tmp.rows), Scalar(0, 0, 255), 2);

        imshow(prefix + "_" + method_names[i], display);
    }
}

int main()
{
    Mat src1 = imread("/root/computer_vision/img/test1.bmp", IMREAD_GRAYSCALE);
    Mat tmp1 = imread("/root/computer_vision/img/test1_ref.bmp", IMREAD_GRAYSCALE);
    Mat src2 = imread("/root/computer_vision/img/test2.bmp", IMREAD_GRAYSCALE);
    Mat tmp2 = imread("/root/computer_vision/img/test2_ref.bmp", IMREAD_GRAYSCALE);

    if (src1.empty() || tmp1.empty() || src2.empty() || tmp2.empty()) {
        cerr << "❌ 이미지 로딩 실패" << endl;
        return -1;
    }

    runTemplateMatching(src1, tmp1, "test1");
    runTemplateMatching(src2, tmp2, "test2");

    imshow("템플릿1", tmp1);
    imshow("템플릿2", tmp2);
    waitKey(0);
    return 0;
}
