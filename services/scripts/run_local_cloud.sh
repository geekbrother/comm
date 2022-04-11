#!/bin/bash

set -e

docker-compose up -d --force-recreate localstack

pushd terraform

./run.sh

popd # terraform
