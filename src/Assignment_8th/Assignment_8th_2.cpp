#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
   Mat img = imread("/root/computer_vision/img/8th_assignment/src.bmp",IMREAD_GRAYSCALE);
   int rows = img.rows;               // 영상 행
   int columns = img.cols;            // 영상의 열
   const int size = rows * columns;   // 전체 영상의 화소수, 크기
   
   // AX = B에서 A 행렬: n x 3, B 행렬: n x 1 행렬, X = 3 x 1 행렬
  double *A_dat = new double[size * 3]; // A 행렬 데이터 : n x 3 임
  double *B_dat = new double[size];  // B행렬: 입력영상의 (x,y)의 밝기값으로 nx1 행렬

  int index = 0, count = 0;
 
  // 샘플영상(src.bmp)을 통해 A행렬과, B 행렬 생성
  for (int y = 0; y < rows; y++)
 {
   for (int x = 0; x < columns; x++)
   {
	A_dat[index++] = x;
	A_dat[index++] = y;
	A_dat[index++] = 1;
        B_dat[count++] = (double)img.at<uchar>(y, x);
    }
 }

	Mat A_mat(size, 3, CV_64FC1, A_dat);  // A 행렬: n x 3 
	Mat B_mat(size, 1, CV_64FC1, B_dat);  // B 행렬: n x 1

	Mat A_trans = A_mat.t();  // A^T 행렬
	Mat Square_A = A_trans * A_mat;  // A^T x A : 정방행렬 계산 

	Mat invA = Square_A.inv();   // pseudo inverse 행렬계산

	double Params[3][1] = {0.,0.,0. }; // X 행렬 3개의 파라미터를 위한 초기값

	Mat X(3, 1, CV_64FC1, Params);  // 파라미터 X 행렬

	Mat Temp(Size(3, 1), CV_64FC1);  // 3 x 1 임시 행렬

 	Temp = A_trans * B_mat;
	X = invA * Temp;              // 최종파라미터 행렬

	Mat B_hat = B_mat.clone();

	B_hat = A_mat * X;      // Background Intensity Estimation (n x 1) matrix
	
	Mat Background(Size(rows, columns),CV_8UC1);  // Real Background Image matrix, rows x columns  해상도
	
	double temp = 0;
	// (n x 1) data를  (rows, columns) 영상데이터로 행렬 변환
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			 temp = B_hat.at<double>(y*columns + x, 0);
			
			 if (temp >= 255.0) Background.at<uchar>(y, x) = 255;
			 else if (temp <= 0.0) Background.at<uchar>(y, x) = 0;
			 else  

				Background.at<uchar>(y, x) = (uchar)temp;
		}
	}
	
	imshow("원본영상", img); 
	imshow("Estimation image", Background);  
	waitKey(0);

    // 배경 조명 제거를 위한 차영상
    Mat img_16S, bg_16S, diff_16S, result;

    img.convertTo(img_16S, CV_16S);
    Background.convertTo(bg_16S, CV_16S);

    diff_16S = img_16S - bg_16S;

    // 클리핑 및 타입 복원
    diff_16S.convertTo(result, CV_8U);

    imshow("조명 제거 영상", result);
    waitKey(0);

    // 조명 모델링 결과 Background와 원본 영상의 절댓값 차이 계산
    Mat diff_abs, text_only;
    absdiff(img, Background, diff_abs);

    // 글씨만 추출하기 위해 threshold 적용 (필요시 값 조절)
    threshold(diff_abs, text_only, 10, 255, THRESH_BINARY);  // 10은 임계값, 필요시 조절

    // 결과 출력
    imshow("조명 제거 영상 (절댓값)", diff_abs); //클리핑
    imshow("글씨만 남긴 영상", text_only); //이진화
    waitKey(0);


    // // 배경 조명 제거를 위한 차영상
    // Mat img_16S, bg_16S, diff_16S, result;

    // img.convertTo(img_16S, CV_16S);
    // Background.convertTo(bg_16S, CV_16S);

    // diff_16S = img_16S - bg_16S;

    // // 음수 값 방지를 위한 클리핑 (0~255 범위)
    // diff_16S.convertTo(result, CV_8U);

    // // 🔥 글씨만 남기기 위한 Threshold 적용
    // Mat text_only;
    // threshold(result, text_only, 30, 255, THRESH_BINARY);  // 30은 임계값, 필요시 조정

    // imshow("조명 제거 영상", result);
    // imshow("글씨만 남긴 영상", text_only);
    // waitKey(0);

	return 0;
}