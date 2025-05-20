#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat img = imread("/root/computer_vision/img/8th_assignment/book1.jpg", IMREAD_GRAYSCALE);
    int rows = img.rows;
    int cols = img.cols;
    const int size = rows * cols;

    // 2차 근사 모델: [x^2, y^2, xy, x, y, 1] → 6개 변수
    const int num_params = 6;
    double* A_dat = new double[size * num_params];
    double* B_dat = new double[size];

    int index = 0, count = 0;
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            A_dat[index++] = x * x;
            A_dat[index++] = y * y;
            A_dat[index++] = x * y;
            A_dat[index++] = x;
            A_dat[index++] = y;
            A_dat[index++] = 1;
            B_dat[count++] = (double)img.at<uchar>(y, x);
        }
    }

    Mat A_mat(size, num_params, CV_64FC1, A_dat);
    Mat B_mat(size, 1, CV_64FC1, B_dat);

    Mat X = (A_mat.t() * A_mat).inv() * A_mat.t() * B_mat;
    Mat B_hat = A_mat * X;

    Mat Background(rows, cols, CV_8UC1);
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            double val = B_hat.at<double>(y * cols + x, 0);
            Background.at<uchar>(y, x) = saturate_cast<uchar>(val);
        }
    }

    // 조명 제거 및 글씨 추출
    Mat diff_abs, text_only;
    absdiff(img, Background, diff_abs);
    threshold(diff_abs, text_only, 10, 255, THRESH_BINARY);

    // 시각화
    imshow("원본", img);
    imshow("2차 조명 모델링 배경", Background);
    imshow("조명 제거 후", diff_abs);
    imshow("글씨만 추출", text_only);
    waitKey(0);
    return 0;
}
