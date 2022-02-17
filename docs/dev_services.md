# Comm services

## Requirements

### OS

Our services can be built and run on Nix operating system including Linux and Mac.
Windows is not supported at this time.
We are using Ubuntu inside the service's Docker containers.

### Docker

To build and run the services you need to install [Docker](https://docs.docker.com/desktop/) on your system

### Node

We are using `yarn` package manager to install build dependencies and provide run and build scripts. You need to install it according to [dev_environment](https://github.com/CommE2E/comm/blob/master/docs/dev_environment.md#node).

### AWS

Our services heavily use AWS Services: S3 for blob storage and DynamoDB as a database. That's why you need to provide your [AWS credentials](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-files.html) in `~/.aws/credentials` file and your AWS region in `~/.aws/config` file. You can use AWS CLI to update these files.

### RabbitMQ (Tunnelbroker only)

Tunnelbroker uses [RabbitMQ](https://www.rabbitmq.com/) as a message broker to communicate between running instances and delivering messages. It uses AMQP or secured AMQPS protocol to connect the message broker.
Make sure your message broker credentials [have access](https://www.rabbitmq.com/access-control.html) to create queues and exchanges.

## Service specific configuration

### **Tunnelbroker**

Tunnelbroker service uses its own configuration `INI` file located at `services/tunnelbroker/tunnelbroker.ini`
which needs to be edited before the service runs.

There are a few required parameters that need to be provided to run the tunnelbroker:

**tunnelbroker.instance-id**

This is unique tunnelbroker instance identification that needs to be unique for each running instance.

```
[tunnelbroker]
instance-id = tunnelbroker1
```

**amqp.uri**

You need to provide `URI` connection string to connect to the RabbitMQ message broker.

```
[amqp]
uri = amqp://guest:guest@0.0.0.0/vhost
```

## Building and running

Service's `yarn` provides useful scripts to build and run services. If the service was not built before it will be built before any run script.

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
