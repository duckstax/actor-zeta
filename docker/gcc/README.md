Local build Docker image for:`ubuntu`, according to https://releases.ubuntu.com/:

* `18.04`
    * GNU GCC `4.8`, `5`, `6`, `7`, `8`
* `20.04`
    * GNU GCC `9`, `10`, `11`, `12`

* `export TOOLCHAIN_VERSION=5`
* `export UBUNTU_VERSION=18.04`
* `docker build -f Dockerfile -t gnu_gcc:${TOOLCHAIN_VERSION} --build-arg UBUNTU_VERSION=${UBUNTU_VERSION} --build-arg TOOLCHAIN_VERSION=${TOOLCHAIN_VERSION} .`
