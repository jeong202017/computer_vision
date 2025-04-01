#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat src = imread("/root/computer_vision/Lenna.png", IMREAD_COLOR);

    if (src.empty()) {
        cout << "이미지를 읽을 수 없습니다." << endl;
        return -1;
    }

    // 1. (100, 100) 만큼 평행 이동
    Mat translated;
    Mat transMat = (Mat_<double>(2, 3) << 1, 0, 100, 0, 1, 100);  // x: +100, y: +100
    warpAffine(src, translated, transMat, Size(src.cols + 100, src.rows + 100));

    // 2. 이동된 이미지의 중심을 기준으로 45도 반시계 회전
    Point2f center(translated.cols / 2.0f, translated.rows / 2.0f);
    double angle = 45.0;
    double scale = 1.0;

    Mat rotMat = getRotationMatrix2D(center, angle, scale);

    // 회전 후 잘림 방지: 새로운 bounding box 계산
    Rect2f bbox = RotatedRect(center, translated.size(), angle).boundingRect2f();

    // 이동 보정
    rotMat.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rotMat.at<double>(1, 2) += bbox.height / 2.0 - center.y;

    Mat rotated;
    warpAffine(translated, rotated, rotMat, bbox.size());

    // 결과 출력
    imshow("원본 이미지", src);
    imshow("1. 평행 이동", translated);
    imshow("2. 평행 이동 후 45도 회전", rotated);

    waitKey(0);
    return 0;
}
