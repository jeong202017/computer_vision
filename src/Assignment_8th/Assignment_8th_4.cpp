#include <opencv2/opencv.hpp>
using namespace cv;

// 함수: 주어진 차수의 배경 모델을 이용해 밝기 추정
Mat estimate_background(const Mat& img, int order) {
    int rows = img.rows, cols = img.cols;
    int size = rows * cols;

    Mat A_mat;
    const int num_params = (order == 1) ? 3 : 6;
    double* A_dat = new double[size * num_params];
    double* B_dat = new double[size];

    int index = 0, count = 0;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (order == 1) {
                A_dat[index++] = x;
                A_dat[index++] = y;
                A_dat[index++] = 1;
            } else {
                A_dat[index++] = x * x;
                A_dat[index++] = y * y;
                A_dat[index++] = x * y;
                A_dat[index++] = x;
                A_dat[index++] = y;
                A_dat[index++] = 1;
            }
            B_dat[count++] = (double)img.at<uchar>(y, x);
        }
    }

    A_mat = Mat(size, num_params, CV_64FC1, A_dat);
    Mat B_mat(size, 1, CV_64FC1, B_dat);
    Mat X = (A_mat.t() * A_mat).inv() * A_mat.t() * B_mat;
    Mat B_hat = A_mat * X;

    Mat background(rows, cols, CV_8UC1);
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            double val = B_hat.at<double>(y * cols + x, 0);
            background.at<uchar>(y, x) = saturate_cast<uchar>(val);
        }
    }

    delete[] A_dat;
    delete[] B_dat;

    return background;
}

int main() {
    Mat img = imread("/root/computer_vision/img/8th_assignment/book1.jpg", IMREAD_GRAYSCALE);
    if (img.empty()) {
        printf("이미지를 불러올 수 없습니다.\n");
        return -1;
    }

    // 1차 모델
    Mat background1 = estimate_background(img, 1);
    Mat diff1, bin1;
    absdiff(img, background1, diff1);
    threshold(diff1, bin1, 10, 255, THRESH_BINARY);

    // 2차 모델
    Mat background2 = estimate_background(img, 2);
    Mat diff2, bin2;
    absdiff(img, background2, diff2);
    threshold(diff2, bin2, 10, 255, THRESH_BINARY);

    // 결과 출력
    imshow("원본 영상", img);
    imshow("1차 모델 배경", background1);
    imshow("1차 모델 조명 제거 결과", diff1);
    imshow("1차 모델 이진화 결과", bin1);
    imshow("2차 모델 배경", background2);
    imshow("2차 모델 조명 제거 결과", diff2);
    imshow("2차 모델 이진화 결과", bin2);
    waitKey(0);
    return 0;
}
