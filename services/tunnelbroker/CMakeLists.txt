cmake_minimum_required(VERSION 3.0.0)
cmake_policy(SET CMP0058 NEW)

# Use vcpkg cmake toolchain
if(DEFINED ENV{VCPKG_ROOT})
  set(VCPKG_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
  set(
    CMAKE_TOOLCHAIN_FILE
    ${VCPKG_TOOLCHAIN_FILE}
    CACHE STRING ""
  )
  message("Using vcpkg toolchain file from ${VCPKG_TOOLCHAIN_FILE}")
elseif(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  message(
    FATAL_ERROR 
    "Please provide vcpkg path using `export VCPKG_ROOT=/path/vcpkg` \
    or by `-DCMAKE_TOOLCHAIN_FILE` argument"
  )
endif()
set(VCPKG_MANIFEST_MODE ON)
set(VCPKG_INSTALL_OPTIONS "--recurse")
if(CMAKE_BUILD_TYPE MATCHES Release)
  set(VCPKG_INSTALL_OPTIONS "--clean-after-build")
  set(VCPKG_BUILD_TYPE release)
endif()

# Project settings
project(tunnelbroker VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
include(CPack)

# Make cmake verbose on Debug release type
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

# Protocol Buffers files generation
set(PROTO_FILES protos/tunnelbroker.proto)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

get_target_property(
  gRPC_CPP_PLUGIN_EXECUTABLE
  gRPC::grpc_cpp_plugin
  IMPORTED_LOCATION_RELEASE
)

include_directories(${Protobuf_INCLUDE_DIRS})
add_library(protobufLib ${PROTO_FILES})

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET protobufLib LANGUAGE cpp)
protobuf_generate(
  TARGET protobufLib
  LANGUAGE grpc
  GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
  PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
)

target_link_libraries(
  protobufLib PUBLIC
  protobuf::libprotobuf gRPC::grpc gRPC::grpc++ gRPC::grpc++_reflection
)

# Server requirements
find_package(folly CONFIG REQUIRED)
find_package(amqpcpp CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
find_package(unofficial-libuv CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)
find_package(double-conversion CONFIG REQUIRED)
find_package(re2 CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED)
find_package(AWSSDK CONFIG COMPONENTS core dynamodb s3 REQUIRED)
find_package(GTest CONFIG REQUIRED)

file(GLOB SOURCE_CODE "./src/*.cpp" "./src/**/*.cpp")
include_directories(
  ./src 
  ./src/Database
  ./src/DeliveryBroker
  ./src/Service
  ./src/Tools
  ./src/Amqp
  ${CMAKE_CURRENT_BINARY_DIR}
  ${Folly_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${CRYPTOPP_INCLUDE_DIRS}
  ${LIBUV_INCLUDE_DIRS}
  ${AWSSDK_INCLUDE_DIRS}
)

set(
  SOURCE_CODE
  ${SOURCE_CODE}
)

add_executable(
  ${PROJECT_NAME}
  ${SOURCE_CODE}
)

target_link_libraries(${PROJECT_NAME} PRIVATE protobufLib)
target_link_libraries(${PROJECT_NAME} PRIVATE Folly::folly Folly::folly_deps)
target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp-static)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::libuv::libuv)
target_link_libraries(${PROJECT_NAME} PRIVATE amqpcpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glog::glog)
target_link_libraries(${PROJECT_NAME} PRIVATE double-conversion::double-conversion)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gmock GTest::gtest)
target_link_libraries(${PROJECT_NAME} PRIVATE re2::re2 c-ares::cares)
target_link_libraries(${PROJECT_NAME} PRIVATE ${AWSSDK_LIBRARIES})

install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ../bin
)
