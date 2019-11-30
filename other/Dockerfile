FROM ubuntu:18.04

WORKDIR /usr/src/

RUN apt-get update && apt-get upgrade -y && apt-get install -yq g++

COPY hide_arg.cpp .

RUN g++ hide_arg.cpp -o hide_arg


