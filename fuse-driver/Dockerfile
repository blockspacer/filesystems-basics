FROM ubuntu:18.04

WORKDIR /usr/src/

COPY hello.c .

RUN apt-get update && apt-get upgrade -y && \
	apt-get install -yq gcc e2fslibs-dev pkg-config libfuse-dev build-essential wget meson udev

RUN wget -O fuse.tar.xz https://github.com/libfuse/libfuse/releases/download/fuse-3.8.0/fuse-3.8.0.tar.xz && \
	tar -xf fuse.tar.xz && rm -f fuse.tar.xz && mv fuse-3.8.0 fuse

RUN cd fuse && mkdir build && cd build && meson .. && \
    meson configure -D prefix=/usr -D libdir=lib && ninja install && cd /usr/src

RUN ln -s /usr/local/lib/x86_64-linux-gnu/libfuse3.so.3 /lib/x86_64-linux-gnu/libfuse3.so.3

RUN gcc -Wall hello.c `pkg-config fuse3 --cflags --libs` -o hello
