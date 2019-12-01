FROM ubuntu:18.04

WORKDIR /usr/src/

RUN apt-get update && apt-get upgrade -y && apt-get install -yq g++ make

COPY utils.cpp utils.h hide_arg.cpp ps.cpp lsof.cpp Makefile ./

RUN make
