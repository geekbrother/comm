FROM commapp/services-base:1.1

ENV SHELL=/bin/bash

COPY services/blob/docker-base/contents /transferred

RUN apt-get update && apt-get install -y uuid-dev

CMD /bin/bash
