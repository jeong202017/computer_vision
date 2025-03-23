import cv2
import numpy as np

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

    cv2.imshow("canvas",canvas3)
    cv2.waitKey(0)

def main():
    show_blue()

if __name__ == "__main__":
    main()