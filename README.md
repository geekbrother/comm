# [Comm](https://github.com/CommE2E/comm)'s optimized services build and dev environment fork

# Why ?

The current implementation of the services development build flow can be optimized in many ways. The main reason for creating this fork is to make the dev environment and dev setup easy to use and optimize the C++ services build process across the multiple optimizations and make it universal. These changes are proposals based on my [comm-services-playground](https://github.com/geekbrother/comm-services-playground) which is used for personal development purposes.

## **The problems and solutions:**

## C++ development inside the docker on macOS is very slow and ineffective.

Docker has a long story with the performance problems on macOS. The C++ build system is heavy. Spin up and attach to the NodeJS inside the running docker container using the VSCode (or other IDE) is slow but it's ok because you can have live reloads, etc. When developing in C++ you rely only on the IDE's IntelliSense to prevent the errors and warnings BEFORE the build. When attaching to the Docker container using VSCode IntelliSense is so slow that you need to wait for a long time before it put up some suggestions. When you have a long list of libraries and includes it takes a couple of minutes to re-index after each save even on the latest M1 Macbook Pro. the only way to see the errors or warnings, in this case, is to rebuild the comm service which takes a time even with the incremental build. Rebuilding every time and checking is not an effective approach when we have an effective IntelliSense.

We can not use AI-based IDE extensions like **tabnine** when attaching to the Docker container because of its slowness. We are living in 2022 and using AI helpers saves the developers time which is costly. Using the latest AI-base extensions can help to achieve goals faster and spend less time on them.

## Solution: Universal CMakeLists.txt.

Instead of using a quirky build system specifically inside the Docker container, we can use the single CMakeLists.txt file to build on Linux, inside the Docker and macOS locally without using the Docker.

When using the local C++ development environment on macOS the speed and productivity are much improved compared to the Docker attaching. We can use any plugins and use the blazing speed IntelliSense and errors checks. The build time is also very improved compared to the Docker (In some build cases almost 10x).

Using the local C++ development environment you can fully use Debug capabilities in your IDE.

## Dependencies installation by bash scripts.

At the moment to install the code dependencies sources we are using the list of the bash scripts that pull the code and build it. Using the bunch of the bash script with the hardcoded path we can't make the build system universal and OS-agnostic. The bash scripts were temporary solutions at the start of the development of the services.

## Solution: C++ package manager.

C++ has a few very good and time-proven package managers that simplify dependency management a lot (vcpkg, conan, etc.). In this fork, I've used the VCPKG package manager that can be used to install the dependencies in the Docker container or local on Linux, macOS, and Windows.

The build system is now universal for Linux, Docker Linux containers, and local macOS dev environments. Because we use a universal package manager and not hardcoded bash scripts the services can be built on any system that the package manager is available on.

Using the package manager we can use the latest OS versions instead of sticking to the old ones like we already use Ubuntu 20.04 inside the Docker container.
This fork uses the latest 22.04 instead.

## Unoptimized and big binaries.

In the build system, we don't use any optimization or build-type flags. We always build unoptimized debug version binary because this is a Cmake default policy.
It's big, slower, and build much longer than the Release one.

## Solution: Debug and Release build.

Use `Release` and `Debug` rules in the CMakeLists.txt file to build small and optimized binaries and add additional verbose output if we build a Debug one.

## Small build improvements:

Protobuf files generation during the build using the CMakeLists "library approach" instead of calling the command.

Using `ninja` to build instead of make. They are interchangeable between each other and no additional dependencies are necessary. The ninja is more productive to build the medium and big C-projects.

## **Docker related improvements:**

Use the single Docker file for the release and dev containers.

Instead of using the bunch of the bash scripts to run the containers in package.json we can just launch the docker-compose commands.

The service files reside in the `/opt/service_name` instead of `/transferred` to make a clear their location in the container.

There are a few dependencies services needed to use the dev environment: **aws dynamodb** and **rabbitmq** servers. It's a good point to run them as independent containers instead of hardcoding their installation into the service dev container. Because in this case, we can use them along with the dev container running and when using the local dev environment without Docker. It's flexible in use. When starting the dev container we are starting the localstack and rabbitmq containers as well.
When using the local dev environment we can start them by the `dev-services-only` command.

## Small docker suggestions:

When building the Release container it's a good point to squash the container to reduce the size and we don't need the layers in it. When using the [docker-squash](https://github.com/goldmann/docker-squash) utility the tunnelbroker release container size reduces to only 450 Mb. Maybe it's a good point to add it to the package.json scripts.

# How to develop and build

## Local macOS + IDE

To develop and build using the local dev environment you can just open the `services/tunnelbroker` folder using your IDE like VSCode or Clion. The IntelliSense will work out of the box if the Cmake and C++ plugins are installed.

You can spin up the required services locally using the docker containers by running the following command inside the `services` directory:

`yarn run dev-services-only`

That will start the localstack and rabbitMQ services to use locally.

## Building docker containers

To build the Docker container with the dev sources inside you can run the following command inside the `services` directory:

`yarn run tunnelbroker-server-dev`

To build the production container without sources (which are removed after the build and cleanup proceeded) you can run the following command inside the `services` directory:

`yarn run tunnelbroker-server`

## Local macOS service building showcase:

Based on the VSCode with the Cmake, C++, Tabnine extension.

https://user-images.githubusercontent.com/11191291/165935461-84179765-a2a7-4135-b631-44e3e1f7ca23.mp4

## Modification commits list:

1. [[services][build system] Removing other services than Tunnelbroker to make the changes clear](https://github.com/geekbrother/comm/commit/4c89c70dbdc52c62d7e0fb3a5905623dca34edf6)
2. [[services][build system] CmakeLists changes to use vcpkg and Debug/Release build mode](https://github.com/geekbrother/comm/commit/874dd53eed5e449284813a4d494fee33beb5fad8)
3. [[services][build system] Docker configuration changes to use a single docker file instead of a lot of bash scripts. Docker-compose changed to use a single Docker file. Localstack and RabbitMQ images added to the dev env stack](https://github.com/geekbrother/comm/commit/bf119887e3c2520f8390f93a441ae2b395351e59)
4. [[services][build system] Add VCPKG manifest and configuration files](https://github.com/geekbrother/comm/commit/e73215094420f48d9c467fdec91fafb6d03f338f)
5. [[services][build system] Add build and bin to the gitignore for the local builds without Docker](https://github.com/geekbrother/comm/commit/1227290995a87c7f676f1ef95b14b13752d1852b)
6. [[services][build system] Make a protobuf file as a hard link and place it to the `protos` directory](https://github.com/geekbrother/comm/commit/6d03d3dbadf6270998ae1cc6808c2d6f9e69ac7d)
7. [[services][build system] Package.json changes to use docker compose commands instead of the bash scripts.](https://github.com/geekbrother/comm/commit/20baf2651c26d3d074ea90e05d650c6af9a3d5e0)
