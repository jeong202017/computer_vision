import cv2
import numpy as np

# 이미지 로드 및 전처리
img = cv2.imread("/root/computer_vision/img/lena.bmp")
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray = np.float32(gray)

# Harris 코너 계산
block_size = 6
ksize = 3
k = 0.04
dst = cv2.cornerHarris(gray, block_size, ksize, k)

# 0 ~ 255 정규화
dst_norm = np.empty(dst.shape, dtype=np.float32)
cv2.normalize(dst, dst_norm, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX)
dst_norm = np.uint8(dst_norm)

# 지역 최대값 + threshold 조건으로 코너 추출
threshold = 100
corners = []

for y in range(1, dst_norm.shape[0]-1):
    for x in range(1, dst_norm.shape[1]-1):
        local_patch = dst_norm[y-1:y+2, x-1:x+2]
        center_value = dst_norm[y, x]
        if center_value > threshold and center_value == local_patch.max():
            corners.append((x, y))

# 결과 시각화
img_result = img.copy()
for pt in corners:
    cv2.circle(img_result, pt, 2, (0, 0, 255), -1)

cv2.imshow('Harris with local maxima', img_result)
cv2.waitKey(0)
cv2.destroyAllWindows()
