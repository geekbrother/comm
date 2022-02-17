# Comm services

## Requirements

### OS

At the moment, our services can be built and run on Linux and macOS operating systems via Docker.
Windows is not supported at this time.
We're using Ubuntu as the base Docker image for services.

### Docker

To build and run the services you need to install [Docker](https://docs.docker.com/desktop/) on your system.

### Node

We use the `yarn` package manager to install dependencies and run scripts. Installation instructions can be found in the [dev_environment](https://github.com/CommE2E/comm/blob/master/docs/dev_environment.md#node) docs.

### AWS

Some of our services access AWS resources via the AWS C++ SDK. To access these resources, you'll need to configure the `~/.aws/credentials` and `~/.aws/config` files correctly on your host machine. Instructions for setting these configuration files can be found here: [AWS configuration and credential file settings](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-files.html).
We recommend running `aws configure`, which will prompt you for the necessary configuration values.

## Tunnelbroker specific

### RabbitMQ

[RabbitMQ](https://www.rabbitmq.com/) is an open source message broker service. We use RabbitMQ in Tunnelbroker to facilitate communication between devices and keyservers. We use the secure AMPQS protocol to connect to RabbitMQ instances hosted on AWS.

In order to access and manage RabbitMQ instances, you'll need credentials and the [proper permissions](https://www.rabbitmq.com/access-control.html). You can add new users--or edit permissions for existing ones--through the [RabbitMQ Management plugin](https://www.rabbitmq.com/management.html).
Alternatively, you can manage credentials and permissions from the `rabbitmqctl` CLI. For example, to add a new user you can run the following command:

```
rabbitmqctl add_user {username}
```

Tunnelbroker-specific configuration is handled in the `services/tunnelbroker/tunnelbroker.ini` file. **This file needs to be correctly configured in order to start the tunnelbroker service.**
The following fields are required to start the tunnelbroker service:

`tunnelbroker.instance-id`

Provide a unique ID for each running instance of the tunnelbroker service.

```
[tunnelbroker]
instance-id = tunnelbroker1
```

`amqp.uri`

Provide the [RabbitMQ URI](https://www.rabbitmq.com/uri-spec.html) to the desired RabbitMQ instance.

```
[amqp]
uri = amqp://guest:guest@0.0.0.0/vhost
```

## Building and running

`services/package.json` provides useful scripts to build and run services. The `run` scripts will automatically build the service first if necessary. For the full list of scripts you can check [services/package.json](https://github.com/CommE2E/comm/blob/master/services/package.json) `scripts` section.
