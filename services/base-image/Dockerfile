FROM ubuntu:20.04

ENV SHELL=/bin/bash

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
	cmake \
	git \
	build-essential \
	autoconf \
	libtool \
	pkg-config \
	libboost-all-dev \
	libfmt-dev \
	libgtest-dev \
	&& rm -rf /var/lib/apt/lists/*

RUN mkdir -p /transferred/scripts
WORKDIR /transferred/scripts

COPY contents/install_grpc.sh .
RUN ./install_grpc.sh

CMD /bin/bash
