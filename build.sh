#!/bin/bash
set -e

mkdir -p bin/

cd src/

gcc \
    event_listener.c \
    controller.c \
    config_loader.c \
    process_executor.c \
    -o ../bin/ctrl
