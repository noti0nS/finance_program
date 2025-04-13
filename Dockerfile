FROM ubuntu:25.04@sha256:3fa335765c57a9ef67f62ef33b4411266c576f4dbdd9d5255f5da2ac306e021f

WORKDIR /app

COPY . ./


RUN apt-get update && apt-get install -y gcc libc-dev locales && rm -rf /var/lib/apt/lists/* \
    && localedef -i pt_BR -c -f UTF-8 -A /usr/share/locale/locale.alias pt_BR.UTF-8

ENV LANG=pt_BR.utf8

RUN gcc ./finance_program.c -o main.o

ENTRYPOINT [ "./main.o" ]