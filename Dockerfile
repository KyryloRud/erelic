FROM alpine:3.21

RUN apk add \
   clang \
   clang19-extra-tools \
   cmake \
   gtest-dev \
   make \
   python3
