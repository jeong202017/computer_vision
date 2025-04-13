# 베이스 이미지
FROM ubuntu:22.04

# 비대화 모드 설정
ENV DEBIAN_FRONTEND=noninteractive

# 필수 패키지 설치 및 업데이트
RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    unzip \
    pkg-config \
    software-properties-common \
    sudo \
    ffmpeg \
    libsm6 \
    libxext6 \
    libgl1-mesa-glx \
    libgtk-3-dev \
    python3 \
    python3-pip \
    python3-dev \
    python3-opencv \
    && rm -rf /var/lib/apt/lists/*

# GUI (OpenCV imshow 등) 관련 라이브러리
RUN apt-get update && apt-get install -y \
    libgtk2.0-dev \
    libcanberra-gtk* \
    libx11-xcb1 \
    libxcomposite-dev \
    libxcursor-dev \
    libxdamage-dev \
    libxfixes-dev \
    libxi-dev \
    libxtst-dev \
    libnss3 \
    libxrandr-dev \
    x11-apps

# pip 최신화 및 기본 패키지 설치
RUN python3 -m pip install --upgrade pip && \
    pip install \
    numpy \
    scipy \
    matplotlib \
    opencv-python \
    opencv-contrib-python \
    jupyterlab \
    ipython

# 작업 디렉토리
WORKDIR /workspace

# 컨테이너 진입 시 bash 실행
CMD ["/bin/bash"]
