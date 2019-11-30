#!/usr/bin/env bash

docker build -t hider .
docker run -it --rm --privileged hider sh
