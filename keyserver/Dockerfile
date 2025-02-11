FROM node:16.13-bullseye

WORKDIR /app

#-------------------------------------------------------------------------------
# STEP 0: INSTALL PREREQS
# Install prereqs first so we don't have to reinstall them if anything changes
#-------------------------------------------------------------------------------

# We need python2 for a build script that the sqlite3 npm package uses
# We use rsync in the prod-build yarn script
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
  python2 \
  rsync \
  && rm -rf /var/lib/apt/lists/*
RUN update-alternatives --install /usr/bin/python python /usr/bin/python2 2

# We use nvm to make sure we're running the right Node version
ENV NVM_DIR /root/.nvm
RUN curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.1/install.sh \
  | bash

#-------------------------------------------------------------------------------
# STEP 1: YARN CLEANINSTALL
# We run yarn cleaninstall before copying most of the files in for build caching
#-------------------------------------------------------------------------------

# Copy in package.json and yarn.lock files
COPY package.json yarn.lock .
COPY keyserver/package.json keyserver/.flowconfig keyserver/
COPY lib/package.json lib/.flowconfig lib/
COPY web/package.json web/.flowconfig web/
COPY native/package.json native/.flowconfig native/
COPY landing/package.json landing/.flowconfig landing/

# Copy in files needed for patch-package and pod-patch
COPY patches patches/
COPY native/ios/pod-patch native/ios/pod-patch/
COPY native/ios/Podfile native/ios/

# Actually run yarn
RUN yarn cleaninstall

#-------------------------------------------------------------------------------
# STEP 2: COPY IN SOURCE FILES
# We run this later so the above layers are cached if only source files change
#-------------------------------------------------------------------------------

COPY . .

#-------------------------------------------------------------------------------
# STEP 3: RUN BUILD SCRIPTS
# We need to populate keyserver/dist, among other things
#-------------------------------------------------------------------------------

WORKDIR /app/keyserver
RUN yarn prod-build

#-------------------------------------------------------------------------------
# STEP 4: RUN THE SERVER
# Actually run the Node.js keyserver using nvm
#-------------------------------------------------------------------------------

EXPOSE 3000
CMD bash/run-prod.sh
