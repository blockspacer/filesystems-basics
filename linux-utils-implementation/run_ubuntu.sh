#!/usr/bin/env bash

docker build -t ubuntu .
docker run -it --rm --privileged ubuntu sh
