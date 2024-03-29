ARG UBUNTU_VERSION

FROM ubuntu:${UBUNTU_VERSION}

ARG TOOLCHAIN_VERSION
ARG PYINSTALL_SCRIPT

ENV DEBIAN_FRONTEND noninteractive

ADD $PYINSTALL_SCRIPT ./pyinstall.sh

RUN apt update && apt-get install -y \
    software-properties-common ca-certificates \
    ninja-build make \
    zlib1g-dev wget

RUN add-apt-repository ppa:ubuntu-toolchain-r/test

RUN bash ./pyinstall.sh $(cat /etc/os-release | grep -a UBUNTU_CODENAME | sed -e 's/UBUNTU_CODENAME=//g')

RUN python3 -m pip install --upgrade pip
RUN python3 -m pip install --no-cache-dir conan==1.59 cmake

# https://linuxize.com/post/how-to-install-gcc-compiler-on-ubuntu-18-04/
RUN apt update && apt-get install -y gcc-${TOOLCHAIN_VERSION} g++-${TOOLCHAIN_VERSION}

RUN update-alternatives \
    --install /usr/bin/gcc gcc /usr/bin/gcc-${TOOLCHAIN_VERSION} 90 \
    --slave /usr/bin/g++ g++ /usr/bin/g++-${TOOLCHAIN_VERSION} \
    --slave /usr/bin/gcov gcov /usr/bin/gcov-${TOOLCHAIN_VERSION}
RUN update-alternatives --config gcc

ENV CC gcc-${TOOLCHAIN_VERSION}
ENV CXX g++-${TOOLCHAIN_VERSION}
