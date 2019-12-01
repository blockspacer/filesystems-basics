FROM ubuntu:18.04

WORKDIR /usr/src/

RUN apt-get update && apt-get upgrade -y && apt-get install -yq g++ make

COPY utils.hpp hide_arg.cpp ps.cpp lsof.cpp Makefile ./

RUN make
