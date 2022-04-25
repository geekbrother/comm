PROJECT(tunnelbroker C CXX)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(CMAKE_CXX_STANDARD 17)

if(DEFINED ENV{VCPKG_ROOT})
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

set(BUILD_TESTING OFF CACHE BOOL "Turn off tests" FORCE)
set(WITH_GFLAGS OFF CACHE BOOL "Turn off gflags" FORCE)

file(GLOB SOURCE_CODE "./src/*.cpp" "./src/**/*.cpp")

include_directories(
  ./src
  ./src/Database
  ./src/DeliveryBroker
  ./src/Service
  ./src/Tools
  ./src/Amqp
)

set(
  SOURCE_CODE
  ${SOURCE_CODE}
)

#SERVER
add_executable(
  tunnelbroker
  ${SOURCE_CODE}
)

find_package(folly CONFIG REQUIRED)
find_package(amqpcpp CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
find_package(unofficial-libuv CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)

target_link_libraries(tunnelbroker PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)
target_link_libraries(tunnelbroker PRIVATE amqpcpp cryptopp-static unofficial::libuv::libuv glog::glog)

find_package(double-conversion CONFIG REQUIRED)
target_link_libraries(tunnelbroker PRIVATE double-conversion::double-conversion)

find_package(Protobuf CONFIG REQUIRED)
target_link_libraries(tunnelbroker PRIVATE ${Protobuf_LIBRARIES})

find_package(gRPC CONFIG REQUIRED)
target_link_libraries(tunnelbroker PRIVATE gRPC::grpc++ gRPC::grpc++_reflection)

target_link_libraries(tunnelbroker PRIVATE re2::re2 c-ares::cares)

find_package(OpenSSL REQUIRED)
target_link_libraries(tunnelbroker PRIVATE OpenSSL::SSL OpenSSL::Crypto)

find_package(aws-cpp-sdk-core REQUIRED)
target_include_directories(tunnelbroker PRIVATE aws-cpp-sdk-core)
target_link_libraries(tunnelbroker PRIVATE aws-cpp-sdk-core)

find_package(aws-cpp-sdk-s3 REQUIRED)
target_include_directories(tunnelbroker PRIVATE aws-cpp-sdk-s3)
target_link_libraries(tunnelbroker PRIVATE aws-cpp-sdk-s3)

find_package(aws-cpp-sdk-dynamodb REQUIRED)
target_include_directories(tunnelbroker PRIVATE aws-cpp-sdk-dynamodb)
target_link_libraries(tunnelbroker PRIVATE aws-cpp-sdk-dynamodb)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(tunnelbroker PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

install(
  TARGETS tunnelbroker
  RUNTIME DESTINATION bin/
)

# TEST
if ($ENV{COMM_TEST_SERVICES} MATCHES 1)
  file(GLOB TEST_CODE "./test/*.cpp")
  list(FILTER SOURCE_CODE EXCLUDE REGEX "./src/server.cpp")
  enable_testing()

  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIR})

  add_executable(
    runTests

    ${SOURCE_CODE}
    ${TEST_CODE}
  )
  target_link_libraries(
    runTests

    ${LIBS}
    gtest
    gtest_main
  )

  add_test(
    NAME runTests
    COMMAND runTests
  )
endif()
