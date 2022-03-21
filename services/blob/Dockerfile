FROM commapp/services-base:1.1

RUN apt-get update && \
  apt-get install -y uuid-dev && \
  rm -rf /var/lib/apt/lists/*

ARG COMM_SERVICES_DEV_MODE
ENV COMM_SERVICES_DEV_MODE=${COMM_SERVICES_DEV_MODE}

ARG COMM_TEST_SERVICES
ENV COMM_TEST_SERVICES=${COMM_TEST_SERVICES}

WORKDIR /transferred

COPY native/cpp/CommonCpp/grpc/protos/blob.proto protos/blob.proto
COPY services/blob/docker/ scripts/
COPY services/blob/ .

RUN scripts/build_server.sh

CMD scripts/run_server.sh
