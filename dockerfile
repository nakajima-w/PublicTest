FROM ubuntu:20.04

# Environment Setting
ENV DEBIAN_FRONTEND=noninteractive

# pre set timezone
RUN apt-get update && apt install -y tzdata && apt-get clean && rm -rf /var/lib/apt/lists/*
ENV TZ Asia/Tokyo

# pre installed tools for c/c++ dev
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    git \
    net-tools \
    iputils-ping \
    clang \
    libssl-dev \
    gdb \
    wget \
    autoconf \
    libtool \
    pkg-config \
    iproute2 \
    kmod \
    can-utils \
    vim \
    swig \
    python3-dev \
    python3-pip
	
RUN apt-get install -y \
	x11-apps \
	x11-utils

RUN pip install --upgrade pip
RUN pip install grpcio==1.39.0
RUN pip install grpcio-tools==1.26.0

RUN pip install cpplint

