FROM commapp/backup-base:1.0

COPY services/tunnelbroker/docker-base/contents /transferred

RUN sudo apt-get install -y libssl-dev
RUN /transferred/install_folly.sh

CMD /bin/bash
