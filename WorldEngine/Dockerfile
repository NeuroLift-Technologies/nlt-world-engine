# NLT Fusion Dev Container
# Reproducible Linux dev environment for Unreal Engine 5.8 development.
# No GPU required — runs headless with web-based viewing.

FROM ubuntu:24.04

LABEL maintainer="NLT Fusion"
LABEL description="Unreal Engine 5.8 development environment for World Engine"

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    clang-20 \
    lld-20 \
    cmake \
    ninja-build \
    python3 \
    python3-pip \
    python3-venv \
    git \
    curl \
    wget \
    unzip \
    libicu-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libx11-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxi-dev \
    libfreetype6-dev \
    libfontconfig1-dev \
    libpulse-dev \
    libasound2-dev \
    libudev-dev \
    libdbus-1-dev \
    libxkbcommon-dev \
    libwayland-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    libvulkan-dev \
    libssl-dev \
    libcurl4-openssl-dev \
    libffi-dev \
    zlib1g-dev \
    libreadline-dev \
    libsqlite3-dev \
    libbz2-dev \
    liblzma-dev \
    libxml2-dev \
    libxslt1-dev \
    autoconf \
    automake \
    libtool \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Set clang as default
RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-20 100 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-20 100 \
    && update-alternatives --install /usr/bin/ld ld /usr/bin/lld-20 100

# Create dev user
RUN useradd -m -s /bin/bash developer && \
    echo "developer ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
USER developer
WORKDIR /home/developer

# Set up Python venv for tooling
RUN python3 -m venv /home/developer/.venv
ENV PATH="/home/developer/.venv/bin:$PATH"

# Install Python tooling
RUN pip install --upgrade pip && \
    pip install \
    requests \
    pyyaml \
    jinja2 \
    click \
    rich \
    watchdog

# Install uv (fast Python package manager)
RUN curl -LsSf https://astral.sh/uv/install.sh | sh
ENV PATH="/home/developer/.local/bin:$PATH"

# Set up directory structure
RUN mkdir -p /home/developer/projects
RUN mkdir -p /home/developer/engine

# Environment variables
ENV UE_ENGINE_DIR=/home/developer/engine
ENV UE_PROJECT_DIR=/home/developer/projects/WorldEngine
ENV PATH="/home/developer/engine/Engine/Binaries/Linux:$PATH"

# Default to bash
CMD ["/bin/bash"]
