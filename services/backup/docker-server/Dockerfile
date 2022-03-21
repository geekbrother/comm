FROM commapp/services-base:1.1

RUN apt-get update && \
  apt-get install -y uuid-dev && \
  rm -rf /var/lib/apt/lists/*

ARG COMM_TEST_SERVICES
ARG COMM_SERVICES_DEV_MODE

ENV COMM_TEST_SERVICES=${COMM_TEST_SERVICES}
ENV COMM_SERVICES_DEV_MODE=${COMM_SERVICES_DEV_MODE}

COPY services/backup/docker-server/contents /transferred
COPY native/cpp/CommonCpp/grpc/protos/backup.proto /transferred/server/protos/backup.proto

RUN /transferred/build_server.sh

CMD if [ "$COMM_TEST_SERVICES" -eq 1 ]; then /transferred/run_tests.sh; else /transferred/run_server.sh; fi
