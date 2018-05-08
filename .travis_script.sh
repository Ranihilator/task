#!/bin/bash

ACTION="${1}"

if [[ ${ACTION} == 'build' ]]; then

    echo "Building..."

    cd simple_chat

    cmake -H. -Bbuild
    cmake --build build
    cmake --build build --target package

elif [[ ${ACTION} == 'deploy' ]]; then

    echo "Deploying..."

fi
