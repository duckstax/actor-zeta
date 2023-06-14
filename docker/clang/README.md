Local build Docker image for `ubuntu:18.04` only, `bionic` release, according to https://releases.ubuntu.com/

LLVM Releases: https://apt.llvm.org/bionic/dists/ from `5.0` to `16`

* `export LLVM_TOOLCHAIN=5.0`
* `docker build -f Dockerfile -t llvm_clang:${LLVM_TOOLCHAIN} --build-arg UBUNTU_VERSION=18.04 --build-arg UBUNTU_RELEASE=bionic --build-arg LLVM_TOOLCHAIN=${LLVM_TOOLCHAIN} .`
