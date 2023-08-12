#!/bin/bash

UBUNTU_CODENAME=$1

echo $UBUNTU_CODENAME

if [[ $UBUNTU_CODENAME == "xenial" ]]; then

    add-apt-repository -y ppa:jblgf0/python

    apt update && apt-get install -y \
        python3.7 python3.7-dev

    wget https://bootstrap.pypa.io/get-pip.py && python3.7 get-pip.py

    rm -rf /usr/local/bin/python3 && ln -s /usr/bin/python3.7 /usr/local/bin/python3
    rm -rf /usr/local/bin/pip3 && ln -s /usr/local/bin/pip /usr/local/bin/pip3
else
    apt update && apt-get install -y \
        python3-pip python3 python3-dev python3-setuptools
fi
