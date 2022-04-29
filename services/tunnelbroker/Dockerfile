FROM ubuntu:22.04

# BUILD_TYPE available options:
# Release - Optimized and exclude debug, removing the build environment after built.
#           Produces slim production image.
# Debug - Optimization disabled, debug information included, and build environment. 
#         Can be used as an attached container for development purposes.
ARG BUILD_TYPE="Release"

ENV SERVICE_NAME="tunnelbroker"
ENV INSTALL_DIR="/opt/${SERVICE_NAME}"
ENV VCPKG_ROOT="/opt/vcpkg"
ENV TZ="US/Eastern"
RUN ln -snf /usr/share/zoneinfo/${TZ} /etc/localtime && echo ${TZ} > /etc/timezone

ENV APT_PACKAGES_LIST="build-essential gcc cmake git curl git \
  unzip tar zip libssl-dev ninja-build pkg-config python3"
RUN apt update && DEBIAN_FRONTEND=noninteractive apt -y install ${APT_PACKAGES_LIST}

# Vcpkg installation
RUN git clone https://github.com/Microsoft/vcpkg.git ${VCPKG_ROOT}
WORKDIR ${VCPKG_ROOT}
ENV VCPKG_FORCE_SYSTEM_BINARIES 1
RUN ./bootstrap-vcpkg.sh
RUN ./vcpkg integrate install
RUN ./vcpkg integrate bash && echo "export PATH=\$PATH:${VCPKG_ROOT}" >>~/.bashrc

# Vcpkg pre-install packages
ENV VCPKG_PACKAGES_LIST="folly cryptopp libuv glog protobuf grpc gtest \ 
  double-conversion boost-program-options boost-uuid aws-sdk-cpp"
RUN ./vcpkg install ${VCPKG_PACKAGES_LIST} --recurse

# Server building
RUN mkdir ${INSTALL_DIR}
WORKDIR ${INSTALL_DIR}
COPY ./tunnelbroker ./
RUN ./clean
RUN cmake -B build -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -G Ninja
RUN ninja -C build

# Remove the build environment in Release mode
WORKDIR ${INSTALL_DIR}
RUN if [ "${BUILD_TYPE}" = "Release" ]; then \
  echo "Cleaning up the build environment on release mode..." && \
  ${VCPKG_ROOT}/vcpkg integrate remove && \
  rm -dfr "build" "/root/.cache" "/root/.vcpkg" ${VCPKG_ROOT}; \
  fi

CMD ["${INSTALL_DIR}/bin/${SERVICE_NAME}"]
