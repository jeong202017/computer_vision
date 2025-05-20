import cv2
import numpy as np
import os

# 분석 대상 이미지 목록
image_paths = [
    "/root/computer_vision/img/lena.bmp",
    "/root/computer_vision/img/fiigure.bmp",
    "/root/computer_vision/img/chessboard.png"
]

# 다양한 파라미터 조합
block_sizes = [2, 3, 5]
ksizes = [3, 5, 7]
k_values = [0.04, 0.06, 0.08]

# 결과 저장 폴더
output_dir = "/root/computer_vision/output_harris"
os.makedirs(output_dir, exist_ok=True)

# 코너 감지 및 시각화 함수
def detect_and_save(image_path):
    img_name = os.path.basename(image_path)
    src = cv2.imread(image_path)
    gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
    gray = np.float32(gray)

    for block_size in block_sizes:
        for ksize in ksizes:
            for k in k_values:
                dst = cv2.cornerHarris(gray, block_size, ksize, k)
                dst = cv2.dilate(dst, None)  # 코너 강조

                result = src.copy()
                result[dst > 0.01 * dst.max()] = [0, 0, 255]  # 코너에 빨간 점 표시

                out_name = f"{os.path.splitext(img_name)[0]}_bs{block_size}_ks{ksize}_k{k:.2f}.png"
                out_path = os.path.join(output_dir, out_name)
                cv2.imwrite(out_path, result)
                print(f"[+] Saved: {out_path}")

# 전체 이미지에 대해 수행
for path in image_paths:
    detect_and_save(path)
