Local build Docker image for:`ubuntu`, according to https://releases.ubuntu.com/:

* `18.04`, `bionic`: https://apt.llvm.org/bionic/dists/
    * LLVM `5.0`, `6.0`, `7`, `8`, `9`, `10`, `11`, `12`, `13`, `14`, `15`, `16`
* `20.04`, `focal`: https://apt.llvm.org/focal/dists/
    * LLVM `9`, `10`, `11`, `12`, `13`, `14`, `15`, `16`
* `22.04`, `jammy`: https://apt.llvm.org/jammy/dists/
    * LLVM `13`, `14`, `15`, `16`

Example Docker build:

* `export TOOLCHAIN_VERSION=16`
* `export UBUNTU_VERSION=20.04`
* `export UBUNTU_RELEASE=focal`
* `docker build -f Dockerfile -t llvm_clang:${TOOLCHAIN_VERSION} --build-arg UBUNTU_VERSION=${UBUNTU_VERSION} --build-arg UBUNTU_RELEASE=${UBUNTU_RELEASE} --build-arg TOOLCHAIN_VERSION=${TOOLCHAIN_VERSION} .`
