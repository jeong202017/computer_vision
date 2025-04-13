import cv2
import numpy as np
import os


img1 = cv2.imread("/home/abc/Desktop/computer_vision/Lenna.jpg")

img2 = cv2.imread("/home/abc/Desktop/computer_vision/Lenna.jpg", cv2.CV_8UC1) #흑백 이미지


def show_blue ():

    # img1 = cv2.rectangle(pt1=640,pt2=480,color=(255,0,0)) ## 베이스 img 누락

    # canvas = np.ones((480,640,3)) * 255 # 흰색 배경 

    # canvas2 = np.ones((480,640,3)) * 0 # 검정 배경
    
    canvas3 = np.ones((480,640,3)) * (255,0,0) # 파란 배경

    # start_point = (100,100) # 왼쪽 위 꼭짓점
    # end_point = (540, 380) # 오른쪽 아래 꼭짓점
    # color = (255, 0, 0) # BGR
    # thickness = 2

    # cv2.rectangle(canvas, start_point, end_point, color) ## 채움 없는 사각형 
    
    img_show(canvas3)

def img_check(img):
    if img is None:
        print("이미지를 불러올 수 없습니다.")
    
    height, width, channels = img1.shape
    total_pixels = img1.size
    dtype = img1.dtype

    print("영상의 해상도 :", height ,"x", width )
    print("전체 화소수 : ", total_pixels)
    print("영상의 타입 :", dtype)

def crop(x1,y1,dx,dy, img):
    if img is None:
        print("이미지를 불러올 수 없습니다.")

    x2 = x1+dx
    y2 = y1+dy

    crop_img = img1[y1:y2, x1:x2]

    return crop_img

def invert(img):
    invert_img = 255 - img

    return invert_img


def img_show(img):
    cv2.imshow("canvas",img)
    cv2.waitKey(0)

def binarization(img):
    thres_val = 100
    max_val = 255

    retval, binary = cv2.threshold(img, thres_val, max_val, cv2.THRESH_BINARY)
    retval, binary_inv = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY_INV)
    retval, trunc = cv2.threshold(img, 127, 255, cv2.THRESH_TRUNC)
    retval, tozero = cv2.threshold(img, 127, 255, cv2.THRESH_TOZERO)
    retval, tozero_inv = cv2.threshold(img, 127, 255, cv2.THRESH_TOZERO_INV)


    retval, otsu_thresh = cv2.threshold(img2, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    

    # > THRESH_OTSU mode:
    # >     'src_type == CV_8UC1 || src_type == CV_16UC1'
    # > where
    # >     'src_type' is 16 (CV_8UC3)

    # 대충 3채널 이미지라 안된다는 내용
                                                                                           
    cv2.imshow("binary", binary)
    cv2.imshow("binary_inv", binary_inv)
    cv2.imshow("trunc", trunc)
    cv2.imshow("tozero", tozero)
    cv2.imshow("tozero_inv", tozero_inv)
    cv2.imshow("otsu_thresh",otsu_thresh)

    cv2.waitKey(0)


def trinarize(img, thresh1=150, thresh2=200, low_val=0, mid_val=100, high_val=255):
    trinary_img = np.zeros_like(img) # 동일 형태, 타입을 가진 0들로 채워진 배열 생성

    trinary_img[img < thresh1] = low_val # 가장 낮은 레벨의 이미지 변환
    trinary_img[(img >= thresh1) & (img <= thresh2)] = mid_val # 다음 레벨의 이미지 변환
    trinary_img[img > thresh2] = high_val # 마지막 레벨의 이미지 변환

    return trinary_img



def main():
    
    ## 1st_Assignment
    show_blue()

    ## 2nd_Assignmnet
    img_check(img1)
    crop_img = crop(200,200,100,100,img1)
    cv2.imshow("img1",img1)
    img_show(crop_img)
    invert_img = invert(crop_img)
    img_show(invert_img)

    # 3rd_Assignment
    binarization(img1)

    # 4th_Assignment
    trinary_img = trinarize(img1)
    img_show(trinary_img)
 
    trinary_img2 = trinarize(img2)
    img_show(trinary_img2)



if __name__ == "__main__":
    main()