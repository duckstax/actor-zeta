#!/bin/bash
COMPILER=$1
COMPILER_VER=$2
COMPILER_CXX=$3
COMPILER_C=$4
CMAKE_CXX_STANDARD=$5
workspace=$6
rm -rf ${workspace}/build
conan profile new actor-zeta --detect
conan profile update settings.compiler=${COMPILER} actor-zeta
conan profile update settings.compiler.version=${COMPILER_VER} actor-zeta
conan profile update env.CXX=${COMPILER_CXX} actor-zeta
conan profile update env.CC=${COMPILER_C} actor-zeta
mkdir -p ${workspace}/build
conan remote add -i 0 conancenter https://center.conan.io
conan install ${workspace}/build/.. -if ${workspace}/build --build=missing -s build_type=Release --profile actor-zeta
cd ${workspace}/build
export CC=${COMPILER_C}
export CXX=${COMPILER_CXX}
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD} -DALLOW_EXAMPLES=OFF -DALLOW_TESTS=ON -DALLOW_BENCHMARK=ON -DEXCEPTIONS_DISABLE=ON -DRTTI_DISABLE=OFF ..
cmake --build .
