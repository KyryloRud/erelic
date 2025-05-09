FROM alpine:3.21

RUN apk add \
   clang \
   clang19-extra-tools \
   cmake \
   gtest-dev \
   lldb \
   make \
   python3 \
   zsh

ENTRYPOINT [ "/bin/zsh" ]
SHELL [ "/bin/zsh" ]
