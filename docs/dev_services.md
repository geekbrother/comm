# Comm services

## Requirements

### OS

At the moment, our services can be built and run on Linux and macOS operating systems.
Windows is not supported at this time.
We are using Ubuntu inside the service's Docker containers.

### Docker

To build and run the services you need to install [Docker](https://docs.docker.com/desktop/) on your system

### Node

We are using `yarn` package manager to install dependencies and run scripts. To install it, please follow the instruction from [dev_environment](https://github.com/CommE2E/comm/blob/master/docs/dev_environment.md#node).

### AWS

Our services use a couple of AWS services. To make them accessible [AWS credentials](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-files.html) in `~/.aws/credentials` file and AWS region in `~/.aws/config` file need to be provided.
You can use AWS CLI to update these files.

## Tunnelbroker specific configuration

### RabbitMQ

Tunnelbroker uses [RabbitMQ](https://www.rabbitmq.com/) as a message broker to communicate between running instances and delivering messages. It uses AMQP or secured AMQPS protocol to connect the message broker.

Make sure you provide credentials for a user that [have access](https://www.rabbitmq.com/access-control.html) to create queues and exchanges. You can add new users or edit permissions of existing ones using [RabbitMQ Management plugin](https://www.rabbitmq.com/management.html). Or you can add a new user to the RabbitMQ using CLI command `rabbitmqctl add_user "username"` and prompt for a password.

Tunnelbroker service uses its own configuration `INI` file located at `services/tunnelbroker/tunnelbroker.ini`
which needs to be edited in order to start the service.

There are a few required parameters that need to be provided to run the tunnelbroker:

**tunnelbroker.instance-id**

This is a tunnelbroker instance identification that needs to be unique for each running instance.

```
[tunnelbroker]
instance-id = tunnelbroker1
```

**amqp.uri**

You need to provide `URI` connection string to connect to the RabbitMQ message broker, using the [RabbitMQ URI scheme](https://www.rabbitmq.com/uri-spec.html).

```
[amqp]
uri = amqp://guest:guest@0.0.0.0/vhost
```

## Building and running

The `package.json` in `services` directory provides useful scripts to build and run services.
A `run` script will automatically build the service if necessary.

All services:

- build-all
- run-all-services
- test-all-services
- test-all-services-dev-mode
- run-all-services-dev-mode

Specific services:

- build-base-image
- build-tunnelbroker-base
- run-tunnelbroker-service
- test-tunnelbroker-service
- build-backup-base
- run-backup-service
- test-backup-service
- run-backup-service-dev-mode
- test-backup-service-dev-mode
- build-blob-base
- run-blob-service
- test-blob-service
- run-blob-service-dev-mode
- test-blob-service-dev-mode
