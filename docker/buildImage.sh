#!/bin/bash
#docker build -t wsollers/cpp-adt:0.0.1 .
#--platform linux/amd64,linux/arm64
if dpkg -l | grep -q "^ii  docker-buildx"; then
    echo "The docker-buildx package is installed."
else
    echo "The docker-buildx package is NOT installed."
    sudo apt-get install docker-buildx
fi

currentDir=$(pwd)

cd ../src || exit

docker buildx build -f ../docker/clang-dockerfile -t wsollers/cpp-adt:0.0.1 .

cd "$currentDir"
