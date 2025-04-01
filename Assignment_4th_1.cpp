
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv; 
using namespace std;

void processCannyWithAutoThreshold(const Mat& src, const string& windowName) {
	// 평균 그래디언트 기반 자동 임계값
    if (src.empty()) {
        cout << "이미지를 읽을 수 없습니다: " << windowName << endl;
        return;
    }

    Mat grad_x, grad_y;
    Sobel(src, grad_x, CV_64F, 1, 0, 3);
    Sobel(src, grad_y, CV_64F, 0, 1, 3);

    Mat magnitude = abs(grad_x) + abs(grad_y);
    Scalar mean_grad = mean(magnitude);

    double lower = 0.66 * mean_grad[0];
    double upper = 1.33 * mean_grad[0];

    Mat edges;
    Canny(src, edges, lower, upper);

    cout << "▶ [" << windowName << "] lower 임계값: " << lower << ", upper 임계값: " << upper << endl;

    imshow(windowName + " - 원본", src);
    imshow(windowName + " - Canny", edges);
}


int main()
{
	Mat src = imread("/root/computer_vision/Lenna.png", CV_8U);

	Mat Circuit = imread("/root/computer_vision/circuit.bmp", CV_8U);

	Mat Lane1 = imread("/root/computer_vision/Lane/00001.jpg",CV_8U);

	Mat Lane2 = imread("/root/computer_vision/Lane/00002.jpg",CV_8U);

	Mat Lane3 = imread("/root/computer_vision/Lane/00003.jpg",CV_8U);

	Mat Lane4 = imread("/root/computer_vision/Lane/00004.jpg",CV_8U);



	if (src.empty()) {
		cout << "영상을 읽을 수 없음" << endl;
	}

	Mat canny = src.clone();
	Mat canny2 = src.clone();

	Canny(src, canny, 100, 150, 3);  //aperture_size = 3
	Canny(src, canny2, 180, 220, 3);

    imshow("image", src);  // 원본영상
    imshow("canny", canny); //"canny 에지"영상 화면에 출력
	imshow("canny2", canny2);


	// ================================================== //

	vector<pair<string, string>> imagePaths = {
        {"Lenna", "/root/computer_vision/Lenna.png"},
        {"Circuit", "/root/computer_vision/circuit.bmp"},
        {"Lane1", "/root/computer_vision/Lane/00001.jpg"},
        {"Lane2", "/root/computer_vision/Lane/00002.jpg"},
        {"Lane3", "/root/computer_vision/Lane/00003.jpg"},
        {"Lane4", "/root/computer_vision/Lane/00004.jpg"}
    };

    for (const auto& imgInfo : imagePaths) {
        Mat img = imread(imgInfo.second, IMREAD_GRAYSCALE);
        processCannyWithAutoThreshold(img, imgInfo.first);
    }

	waitKey(0);	//키 입력을 기다린다.

	return 0;
}
