#!/bin/bash -e

cmake_version="${1}"
echo "Installing CMake ${cmake_version}"

curl -o /tmp/cmake.tar.gz -L https://cmake.org/files/v${cmake_version%.*}/cmake-${cmake_version}-Linux-x86_64.tar.gz
mkdir -p /opt/local/cmake
tar -C /opt/local/cmake --strip-components=1 -xf /tmp/cmake.tar.gz
rm -f /tmp/cmake.tar.gz

