#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("/root/computer_vision/img/Lenna.jpg");
    if (img.empty()) {
        cerr << "[❌] 이미지 로딩 실패: 경로를 확인하세요." << endl;
        return -1;
    }

    // 컬러맵 결과 저장 변수들 선언
    Mat img_color_hot, img_color_autumn, img_color_bone, img_color_jet;
    Mat img_color_winter, img_color_rainbow, img_color_ocean, img_color_summer;
    Mat img_color_spring, img_color_cool, img_color_pink, img_color_parula;

    // 컬러맵 적용
    applyColorMap(img, img_color_hot, COLORMAP_HOT);
    applyColorMap(img, img_color_autumn, COLORMAP_AUTUMN);
    applyColorMap(img, img_color_bone, COLORMAP_BONE);
    applyColorMap(img, img_color_jet, COLORMAP_JET);
    applyColorMap(img, img_color_winter, COLORMAP_WINTER);
    applyColorMap(img, img_color_rainbow, COLORMAP_RAINBOW);
    applyColorMap(img, img_color_ocean, COLORMAP_OCEAN);
    applyColorMap(img, img_color_summer, COLORMAP_SUMMER);
    applyColorMap(img, img_color_spring, COLORMAP_SPRING);
    applyColorMap(img, img_color_cool, COLORMAP_COOL);
    applyColorMap(img, img_color_pink, COLORMAP_PINK);
    applyColorMap(img, img_color_parula, COLORMAP_PARULA);

    // 결과 출력
    imshow("original_image", img);
    imshow("Hot", img_color_hot);
    imshow("Autumn", img_color_autumn);
    imshow("Bone", img_color_bone);
    imshow("Jet", img_color_jet);
    imshow("Winter", img_color_winter);
    imshow("Rainbow", img_color_rainbow);
    imshow("Ocean", img_color_ocean);
    imshow("Summer", img_color_summer);
    imshow("Spring", img_color_spring);
    imshow("Cool", img_color_cool);
    imshow("Pink", img_color_pink);
    imshow("Parula", img_color_parula);

    waitKey(0);
    return 0;
}
