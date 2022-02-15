FROM commapp/services-base:1.0

ENV SHELL=/bin/bash

COPY services/backup/docker-base/contents /transferred

RUN apt-get update
RUN sudo apt-get install -y libcurl-dev libssl-dev
RUN apk add curl-dev openssl-dev uuid-dev zlib-dev
RUN cd /
RUN /transferred/install_aws_sdk.sh

CMD /bin/bash
