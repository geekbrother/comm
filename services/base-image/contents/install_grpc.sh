#!/bin/bash

set -e

echo "installing grpc..."

cd /tmp

git clone --recurse-submodules -b v1.39.1 https://github.com/grpc/grpc

pushd grpc
mkdir -p cmake/build
pushd cmake/build
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      ../..
make
make install
popd # cmake/build

# Explicitly install abseil-cpp because of https://github.com/grpc/grpc/issues/25949
# This should be removed after upgrading to v1.41
pushd third_party/abseil-cpp/
mkdir -p cmake/build
pushd cmake/build
cmake \
		-DCMAKE_POSITION_INDEPENDENT_CODE=TRUE \
		../..
make
make install
popd # cmake/build
popd # third_party/abseil-cpp/

popd # grpc

rm -rf grpc
