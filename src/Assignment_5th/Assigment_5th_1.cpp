#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat src = imread("/home/abc/Desktop/computer_vision/img/Lenna.jpg", IMREAD_COLOR);

    if (src.empty()) {
        cout << "이미지를 읽을 수 없습니다." << endl;
        return -1;
    }

    # 수평 미러링 (y축 기준)
    mirror_horizontal = cv2.flip(img, 1)

    # 수직 미러링 (x축 기준)
    mirror_vertical = cv2.flip(img, 0)
    
    cv2.imshow('Original', img)
    cv2.imshow('Horizontal Mirror', mirror_horizontal)
    cv2.imshow('Vertical Mirror', mirror_vertical)

    waitKey(0);
    return 0;
}
