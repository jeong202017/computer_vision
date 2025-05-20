#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
   Mat chroma = imread("/root/computer_vision/img/9th_assignmnet/chroma.jpg", IMREAD_COLOR);
   Mat background = imread("/root/computer_vision/img/9th_assignmnet/beach.png", IMREAD_COLOR);
   
   Mat bg_hsv;   // 백그라운드 영상 HSV 모델 변환 영상
   cvtColor(chroma, bg_hsv, COLOR_BGR2HSV);
   Mat greenScreen = bg_hsv.clone();  // 백그라운드 Green Screen 영상
   inRange(bg_hsv, Scalar(60 - 10, 100, 100), Scalar(60 + 10, 255, 255), greenScreen);

   Mat dst1;   // 1차 Foreground 검출영상
   Mat dst2;   // 2차 Background 검출영상
   Mat dst;    // 최종결과 영상
   Mat green_inverted;  // 백그라운드 green screen 반전: green 배경(0), 물체(255)

   bitwise_not(greenScreen, green_inverted);  // green 배경(0), 물체(255)
   bitwise_and(chroma, chroma, dst1, green_inverted);  // 1차. foreground 검출
   bitwise_or(background, background, dst2, greenScreen);    // 2차. background 검출
   bitwise_or(dst1, dst2, dst);    // Foreground + Background 영상 최종합성 결과

   imshow("물체영상", chroma);      // Foreground choroma 영상
   imshow("배경영상", background);  // 배경영상
   imshow("물체 HSV", bg_hsv);  
   imshow("Green Screen 영상", greenScreen); // 배경 마스크 영상(배경(255), 물체(0)
   imshow("배경(0)물체(255)", green_inverted); // 배경(0)과 물체(255)
   imshow("Foreground 영상", dst1);
   imshow("Background 영상", dst2);
   imshow("최종합성영상", dst);
   waitKey(0);
   return 0;
}