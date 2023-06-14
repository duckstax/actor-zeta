Local build Docker image for `ubuntu:18.04` only, `bionic` release, according to https://releases.ubuntu.com/

LLVM Releases: https://apt.llvm.org/bionic/dists/ from `5.0` to `16`

* `export TOOLCHAIN_VERSION=5.0`
* `docker build -f Dockerfile -t llvm_clang:${TOOLCHAIN_VERSION} --build-arg UBUNTU_VERSION=18.04 --build-arg UBUNTU_RELEASE=bionic --build-arg TOOLCHAIN_VERSION=${TOOLCHAIN_VERSION} .`
