#!/bin/bash

ACTION="${1}"

if [[ ${ACTION} == 'build' ]]; then

    echo "Building..."
    
    cd stm32_task
    doxygen

elif [[ ${ACTION} == 'deploy' ]]; then

    echo "Deploying..."

fi
