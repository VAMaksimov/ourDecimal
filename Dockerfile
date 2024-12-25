FROM alpine:3.20

# FROM ubuntu

RUN apk --no-cache --upgrade add \
    git \
    git-lfs \
    curl \
    jq \
    bash \
    build-base \
    python3 \
    valgrind \
    cppcheck \
    alpine-sdk \
    pcre-dev \
    pcre2 \
    clang18-extra-tools \
    check \
    check-dev

# RUN apt-get update
# RUN apt-get install -y gcc
# RUN apt-get install -y valgrind
# RUN apt-get install -y make
# RUN apt-get install -y vim
# RUN apt-get install -y check
# RUN apt-get install -y clang-format
# RUN apt-get install -y lcov

COPY . /project
