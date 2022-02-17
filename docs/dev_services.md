# Requirements

At the moment, our services can be built and run on Linux and macOS via Docker. Unfortunately, Windows is not supported at this time. You’ll ideally want a machine with at least 16 GiB of RAM because running a Docker container can consume up to 4 GiB of RAM.

We use Ubuntu as the base Docker image for services.

# Prerequisites

## Docker

To build and run the services you need to install [Docker](https://docs.docker.com/desktop/) and [Docker Compose](https://docs.docker.com/compose/install) on your system.

## Node

We use the `yarn` package manager to install dependencies and run scripts. Installation instructions can be found in the [dev_environment doc](https://github.com/CommE2E/comm/blob/master/docs/dev_environment.md#node).

## AWS

Some of our services access AWS resources via the AWS C++ SDK. To access these resources, you'll need to configure the `~/.aws/credentials` and `~/.aws/config` files correctly on your host machine. Instructions for setting these configuration files can be found [here](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-files.html).

We recommend running `aws configure`, which will prompt you for the necessary configuration values.

## RabbitMQ (Tunnelbroker only)

[RabbitMQ](https://www.rabbitmq.com/) is an open-source message broker service. We use RabbitMQ in Tunnelbroker to facilitate communication between devices and keyservers. We use the secure AMQPS protocol to connect to RabbitMQ instances hosted on AWS.

In order to access and manage RabbitMQ instances, you'll need credentials and the [proper permissions](https://www.rabbitmq.com/access-control.html). You can add new users or edit permissions for existing ones through the [RabbitMQ Management plugin](https://www.rabbitmq.com/management.html).

Alternatively, you can manage credentials and permissions from the `rabbitmqctl` CLI. For example, to add a new user you can run the following command:

```
rabbitmqctl add_user {username}
```

Tunnelbroker-specific configuration is handled in the `services/tunnelbroker/tunnelbroker.ini` file. This file needs to be correctly configured in order to start the tunnelbroker service. The following fields are required to start the tunnelbroker service:

Provide a unique ID for each running instance of the tunnelbroker service.

```
[tunnelbroker]
instance-id = tunnelbroker1
```

Provide the RabbitMQ URI according to https://www.rabbitmq.com/uri-spec.htm
specification.

```
[amqp]
uri = amqp://guest:guest@0.0.0.0/vhost
```

# Building and running

`services/package.json` provides useful scripts to build and run services. The `run` scripts will automatically build the services if necessary and run them. The `dev-mode` scripts will invoke the service development mode which allow you to use local running instances of the S3 storage and DynamoDB instead of using the production one.

You can find the full list of scripts [here](https://github.com/CommE2E/comm/blob/master/services/package.json) in the `scripts` section.

# Developing and debugging

## VSCode

If you are using VSCode as your code editor you can [attach to a Docker container](https://code.visualstudio.com/docs/remote/attach-container) and develop right inside it. That will save you time and resources neither deploy the code into container every time.
