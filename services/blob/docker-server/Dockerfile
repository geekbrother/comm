FROM commapp/services-base:1.1

RUN apt-get update && \
  apt-get install -y uuid-dev && \
  rm -rf /var/lib/apt/lists/*

ARG COMM_SERVICES_DEV_MODE
ENV COMM_SERVICES_DEV_MODE=${COMM_SERVICES_DEV_MODE}

ARG COMM_TEST_SERVICES
ENV COMM_TEST_SERVICES=${COMM_TEST_SERVICES}

WORKDIR /transferred

COPY services/blob/docker-server/contents .
COPY native/cpp/CommonCpp/grpc/protos/blob.proto server/protos/blob.proto

RUN ./build_server.sh

CMD ./run_server.sh
