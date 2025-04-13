Mat img1;

Mat img2(CV_8UC1)) // 흑백 ?  Untitled C~~~?
Mat img3(CV_8UC3)) // 컬러 ?

Mat img4(Size(640,480), CV_8UC3); //size 지정


Mat mat1 = Mat::zeros()

float data[] = {1,2,3,4,5,6}
Mat mat4(2,3,)


mat4.create() // 


Mat 객체 깊은 복사 얕은 복사

// 깊은 복사

Mat clone() 
Mat copyto()

// 얕은 복사

Mat img1 = imread();
Mat img2 = img1(Rect(, , , ,)); // 얕은 복사 크롭??

'''
이미지 반전 img2 = ~img2
'''
Mat img2 = img1().clone; // 깊은 복사??


Mat::at() // 템플릿 함수 "" 행렬 원소 자료형을 명시적으로 지정해야 함


int Mat::channels() // 이미지 채널
int Mat::depth() // 깊이???



img1.convertTo(img1f, CV_32FC1); //
