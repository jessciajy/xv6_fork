FROM --platform=linux/arm64 ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Shanghai

RUN echo "deb http://mirrors.aliyun.com/ubuntu-ports/ jammy main restricted universe multiverse" > /etc/apt/sources.list && \
    echo "deb http://mirrors.aliyun.com/ubuntu-ports/ jammy-updates main restricted universe multiverse" >> /etc/apt/sources.list && \
    echo "deb http://mirrors.aliyun.com/ubuntu-ports/ jammy-security main restricted universe multiverse" >> /etc/apt/sources.list

RUN apt update && apt install -y \
    build-essential \
    git \
    wget \
    curl \
    unzip \
    pkg-config \
    libglib2.0-dev \
    libpixman-1-dev \
    gdb-multiarch \
    qemu-system-misc \
    qemu-user \
    vim

WORKDIR /xv6
CMD ["/bin/bash"]