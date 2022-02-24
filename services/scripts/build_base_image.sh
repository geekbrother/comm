#!/usr/bin/env bash

set -e

. ./scripts/services_config.sh

docker-compose build $1
