FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive

LABEL org.opencontainers.image.title="IPC-Bridge Build Environment"
LABEL org.opencontainers.image.description="Reproducible host and CI build environment for the IPC-Bridge project"
LABEL org.opencontainers.image.source="https://github.com/sheteshreyash/IPC-Bridge"
LABEL org.opencontainers.image.licenses="MIT"

RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    cmake \
    ninja-build \
    pkg-config \
    gcc-aarch64-linux-gnu \
    g++-aarch64-linux-gnu \
    device-tree-compiler \
    clang \
    clang-format \
    cppcheck \
    python3 \
    python3-pip \
    python3-venv \
    kmod \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["/bin/bash"]
