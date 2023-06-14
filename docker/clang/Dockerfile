ARG UBUNTU_VERSION

FROM ubuntu:${UBUNTU_VERSION}

ARG UBUNTU_RELEASE
ARG LLVM_TOOLCHAIN

RUN apt update && apt-get install -y \
    software-properties-common ca-certificates \
    ninja-build \
    python3-pip python3 python3-dev python3-setuptools \
    zlib1g-dev wget

RUN add-apt-repository ppa:ubuntu-toolchain-r/test

RUN python3 -m pip install --upgrade pip
RUN python3 -m pip install --no-cache-dir conan==1.59 cmake

RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN add-apt-repository "deb http://apt.llvm.org/${UBUNTU_RELEASE}/ llvm-toolchain-${UBUNTU_RELEASE}-${LLVM_TOOLCHAIN} main"

RUN wget https://apt.llvm.org/${UBUNTU_RELEASE}/dists/llvm-toolchain-${UBUNTU_RELEASE}-${LLVM_TOOLCHAIN}/main/binary-amd64/Packages
RUN cat Packages \
    | grep -Po "^Package: [a-zA-Z0-9-.\+ ]+$" \
    | sed -e 's/Package:/ /g' \
    | sed -e 's/[+\.a-zA-Z0-9-]*wasm[+\.a-zA-Z0-9-]*$/ /g' \
    | sed -e 's/[+\.a-zA-Z0-9-]*-tools$/ /g' \
    | sed -e 's/[+\.a-zA-Z0-9-]*polly[+\.a-zA-Z0-9-]*$/ /g' \
    | sed -e 's/[+\.a-zA-Z0-9-]*python[+\.a-zA-Z0-9-]*$/ /g' \
    > pkglist
RUN cat pkglist
RUN apt update && apt-get install -y $(cat pkglist)
