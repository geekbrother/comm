FROM commapp/services-base:1.0

ENV SHELL=/bin/bash

RUN apk update
RUN apk add curl-dev openssl-dev zlib-dev

# Install SDKs
COPY services/tunnelbroker/docker/install_folly.sh /transferred/
RUN /transferred/install_folly.sh

COPY services/tunnelbroker/docker/install_aws_sdk.sh /transferred/
RUN /transferred/install_aws_sdk.sh

COPY services/tunnelbroker/docker/install_amqp_cpp.sh /transferred/
RUN /transferred/install_amqp_cpp.sh

COPY services/tunnelbroker/docker/install_cryptopp.sh /transferred/
RUN /transferred/install_cryptopp.sh

COPY services/tunnelbroker/docker/install_libuv.sh /transferred/
RUN /transferred/install_libuv.sh

ARG COMM_TEST_SERVICES
ENV COMM_TEST_SERVICES=${COMM_TEST_SERVICES}

COPY services/tunnelbroker/docker-server/contents /transferred
COPY native/cpp/CommonCpp/grpc/protos/tunnelbroker.proto /transferred/server/protos/tunnelbroker.proto

RUN /transferred/build_server.sh

CMD if [ "$COMM_TEST_SERVICES" -eq 1 ]; then /transferred/run_tests.sh; else /transferred/run_server.sh; fi
